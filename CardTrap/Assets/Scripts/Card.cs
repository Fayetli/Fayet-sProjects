using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Card : MonoBehaviour
{
    [SerializeField] private SpriteRenderer sprite;
    public bool OnLook { get; private set; }
    private Hand hand;
    private int order;
    private float posY;

    private void Awake()
    {
        order = sprite.sortingOrder;
    }

    public void ChangeLayer(int i)
    {
        sprite.sortingOrder = i;
        order = i;
    }

    public void ChangeHand(Hand hand)
    {
        this.hand = hand;
    }

    private void OnMouseOver()
    {
        if (hand.CurrentCard == null)
        {
            posY = sprite.transform.localPosition.y;
            sprite.transform.localPosition += Vector3.up * .1f;

            sprite.sortingOrder = 100;
            hand.ChangeCurrentCard(this);

            OnLook = true;
        }

    }

    private void OnMouseExit()
    {
        if (hand.CurrentCard == this)
        {
            var pos = sprite.transform.localPosition;
            pos.y = posY;
            sprite.transform.localPosition = pos;

            sprite.sortingOrder = order;
            hand.ChangeCurrentCard(null);

            OnLook = false;
        }
    }

}
