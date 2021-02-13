using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Deck : MonoBehaviour
{
    [SerializeField] private List<Card> deckCards;
    [SerializeField] private Hand hand;

    private void OnMouseDown()
    {
        if(deckCards.Count != 0)
        {
            hand.AddCard(deckCards[0]);
            deckCards.RemoveAt(0);
        }
    }
}
