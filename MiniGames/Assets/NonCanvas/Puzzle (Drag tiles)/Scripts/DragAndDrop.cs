using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Drag_Tiles_Puzzle
{
    public class DragAndDrop : MonoBehaviour
    {
        [SerializeField] private Puzzle puzzle;
        private NumberBox dragBox;

        void Update()
        {
            if (Input.GetMouseButtonDown(0))
            {
                RaycastHit2D hit = Physics2D.Raycast(Camera.main.ScreenToWorldPoint(Input.mousePosition), Vector2.zero);
                if (!hit)
                    return;
                if (hit.transform.gameObject.TryGetComponent(out NumberBox box))
                {
                    if (box.InTruePoint == false)
                    {
                        dragBox = box;
                        box.ChangeLayer(10);
                        Debug.Log(dragBox);
                    }
                }
            }
            if (dragBox != null)
            {
                var pos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
                pos.z = 0;
                dragBox.gameObject.transform.position = pos;
            }
            if (Input.GetMouseButtonUp(0))
            {
                if (dragBox != null)
                {
                    var pos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
                    var otherBox = puzzle.GetByPos(pos);
                    
                    if (otherBox != null && otherBox != dragBox && otherBox.InTruePoint == false)
                    {
                        puzzle.Swap(dragBox, otherBox);
                        dragBox.ChangeLayer(0);
                    }
                    else
                    {
                        dragBox.ChangeLayer(0);
                        dragBox.ResetPos();
                    }
                    dragBox = null;
                }
            }
        }
    }

}
