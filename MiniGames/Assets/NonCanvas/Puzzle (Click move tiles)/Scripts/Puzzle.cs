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
            Shuffle(boxes);
            UpdateTilesPos();
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

        public static void Shuffle<T>(T[,] array)
        {
            int lengthRow = array.GetLength(1);

            for (int i = array.Length - 1; i > 0; i--)
            {
                int i0 = i / lengthRow;
                int i1 = i % lengthRow;

                int j = Random.Range(0, i + 1);
                int j0 = j / lengthRow;
                int j1 = j % lengthRow;

                T temp = array[i0, i1];
                array[i0, i1] = array[j0, j1];
                array[j0, j1] = temp;
            }
        }

        private void UpdateTilesPos()
        {
            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    boxes[x, y].UpdatePos(x, y);
                }
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