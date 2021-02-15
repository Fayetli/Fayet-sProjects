using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace ClickMovePuzzle
{

    public class Puzzle : MonoBehaviour
    {
        [SerializeField] private NumberBox boxPrefab;

        [SerializeField] private int width;
        [SerializeField] private int height;

        [SerializeField] private Sprite[] sprites;

        private NumberBox[,] boxes;


        private void Start()
        {
            Init();

            StartCoroutine(Shuffling(boxes, 5000));
        }

        void Init()
        {
            boxes = new NumberBox[width, height];

            for (int y = height - 1, index = 0; y >= 0; y--)
            {
                for (int x = 0; x < width; x++)
                {
                    var box = Instantiate(boxPrefab, transform);
                    box.Init(x, y, sprites[index++], ClickToSwap);
                    boxes[x, y] = box;

                }
            }

        }

        public IEnumerator Shuffling(NumberBox[,] arr, int depth)
        {
            Vector2 emptyPos = new Vector2(width - 1, height - 1);

            int n = depth / 100;

            for (int i = 1; i < depth + 1; i++)
            {
                int dx = 0;
                int dy = 0;

                if (emptyPos.x + 1 < width && Random.Range(0, 2) == 0)
                    dx = 1;
                else if (emptyPos.x - 1 >= 0 && Random.Range(0, 2) == 0)
                    dx = -1;
                else if (emptyPos.y + 1 < height && Random.Range(0, 2) == 0)
                    dy = 1;
                else if (emptyPos.y - 1 >= 0 && Random.Range(0, 2) == 0)
                    dy = -1;

                Vector2 newPos = emptyPos + new Vector2(dx, dy);
                ClickToSwap((int)newPos.x, (int)newPos.y);
                emptyPos = newPos;


                if (i % n == 0)
                    yield return new WaitForFixedUpdate();
            }
        }

        void ClickToSwap(int x, int y)
        {
            int dx = getDx(x, y);
            int dy = getDy(x, y);

            var from = boxes[x, y];
            var target = boxes[x + dx, y + dy];

            boxes[x, y] = target;
            boxes[x + dx, y + dy] = from;

            from.UpdatePos(x + dx, y + dy);
            target.UpdatePos(x, y);

        }

        int getDx(int x, int y)
        {
            if (x < width - 1 && boxes[x + 1, y].IsEmpty())
                return 1;
            if (x > 0 && boxes[x - 1, y].IsEmpty())
                return -1;
            return 0;
        }

        int getDy(int x, int y)
        {
            if (y < height - 1 && boxes[x, y + 1].IsEmpty())
                return 1;
            if (y > 0 && boxes[x, y - 1].IsEmpty())
                return -1;
            return 0;
        }
    }

}