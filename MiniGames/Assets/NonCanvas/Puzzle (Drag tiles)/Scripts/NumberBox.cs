using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Drag_Tiles_Puzzle
{

    [RequireComponent(typeof(SpriteRenderer))]
    public class NumberBox : MonoBehaviour
    {
        public int x { get; private set; } = 0;
        public int y { get; private set; } = 0;

        private int winX, winY = 0;

        private SpriteRenderer renderer;

        private void Awake()
        {
            renderer = GetComponent<SpriteRenderer>();
        }

        public bool InTruePoint
        {
            get
            {
                if (x == winX && y == winY)
                    return true;
                return false;
            }
        }

        public void Init(int x, int y, Sprite sprite)
        {
            winX = x;
            winY = y;
            UpdatePos(x, y);

            renderer.sprite = sprite;
        }

        public void UpdatePos(int x, int y)
        {
            this.x = x;
            this.y = y;

            ResetPos();
        }

        public void ResetPos()
        {
            transform.localPosition = new Vector2(x, y);
        }

        public void ChangeLayer(int layer)
        {
            renderer.sortingOrder = layer;
        }


    }
}
