using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

namespace ClickMovePuzzle
{
    [RequireComponent(typeof(SpriteRenderer))]
    public class NumberBox : MonoBehaviour
    {
        private  SpriteRenderer renderer;

        private int x, y = 0;

        private Action<int, int> swapFunc = null;

        private void Awake()
        {
            renderer = GetComponent<SpriteRenderer>();
        }

        public void Init(int x, int y, Sprite sprite, Action<int, int> swapFunc)
        {
            UpdatePos(x, y);
            this.swapFunc = swapFunc;

            renderer.sprite = sprite;
        }

        public void UpdatePos(int x, int y)
        {
            this.x = x;
            this.y = y;

            transform.localPosition = new Vector2(x, y);
        }

        private void OnMouseDown()
        {
            if (Input.GetMouseButtonDown(0) && swapFunc != null)
                swapFunc(x, y);
        }

        public bool IsEmpty()
        {
            return renderer.sprite == null;
        }
    }

}