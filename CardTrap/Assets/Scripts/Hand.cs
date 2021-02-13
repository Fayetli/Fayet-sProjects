using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Linq;
using System;

public class Hand : MonoBehaviour
{
    private List<Card> cards;

    [SerializeField] private float rotateBorder;

    public Card CurrentCard { get; private set; }

    private void Awake()
    {
        cards = GetComponentsInChildren<Card>().ToList();
        Locate();
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.R))
        {
            cards = GetComponentsInChildren<Card>().ToList();
            Locate();
        }
    }

    private void Locate()
    {
        var fullAngle = rotateBorder * 2;
        var angle = fullAngle / ((cards.Count - 1) == 0 ? 1 : cards.Count - 1);

        float middle;
        if (cards.Count % 2 == 1)
        {
            middle = cards.Count / 2 + 1;
        }
        else
            middle = cards.Count / 2 + 0.5f;

        angle = Mathf.Min(angle, 20);

        var aroundPos = transform.position;

        for(int i = 0; i < cards.Count; i++)
        {
            cards[i].ChangeLayer(i);
            cards[i].ChangeHand(this);
            var c = cards[i].transform;

            c.localPosition = Vector3.up;
            c.rotation = Quaternion.identity;

            c.RotateAround(aroundPos, Vector3.forward, (middle - (i + 1)) * angle );
        }
    }

    public void AddCard(Card card)
    {
        cards.Add(card);
        card.transform.parent = transform;

        Locate();
    }

    public void ChangeCurrentCard(Card card)
    {
        CurrentCard = card;
    }
}
