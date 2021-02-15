using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Drag_Tiles_Puzzle
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
            var camera = Camera.main;
            var pos = camera.transform.position;

            camera.transform.position = new Vector3((float)width / 2 - 0.5f, (float)height / 2 - 0.5f, pos.z);

            Init();

            Shuffle();
        }

        void Init()
        {
            boxes = new NumberBox[width, height];

            for (int y = height - 1, index = 0; y >= 0; y--)
            {
                for (int x = 0; x < width; x++)
                {
                    var box = Instantiate(boxPrefab, transform);
                    box.Init(x, y, sprites[index++]);
                    boxes[x, y] = box;
                }
            }

        }

        public void Shuffle()
        {
            int lengthRow = boxes.GetLength(1);


                for (int i = boxes.Length - 1; i > 0; i--)
                {
                    int i0 = i / lengthRow;
                    int i1 = i % lengthRow;

                    int jr = Random.Range(0, i + 1);
                    int j0 = jr / lengthRow;
                    int j1 = jr % lengthRow;

                    NumberBox temp = boxes[i0, i1];
                    boxes[i0, i1] = boxes[j0, j1];
                    boxes[j0, j1] = temp;

                    boxes[i0, i1].UpdatePos(i0, i1);
                    boxes[j0, j1].UpdatePos(j0, j1);

                }
        }

        public NumberBox GetByPos(Vector2 pos)
        {
            int x = (int)(pos.x + 0.5f);
            int y = (int)(pos.y + 0.5f);

            Debug.Log(pos);
            Debug.Log(new Vector2(x, y));

            if (x >= 0 && x < width && y >= 0 && y < height)
                return boxes[x, y];
            return null;
        }

        public void Swap(NumberBox a, NumberBox b)
        {
            Debug.Log(new Vector2(a.x, a.y) + " <-> " + new Vector2(b.x, b.y));

            var a0 = a.x;
            var a1 = a.y;
            var b0 = b.x;
            var b1 = b.y;

            var from = boxes[a0, a1];
            var target = boxes[b0, b1];

            boxes[a0, a1] = target;
            boxes[b0, b1] = from;

            from.UpdatePos(b0, b1);
            target.UpdatePos(a0, a1);

        }

    }
}
