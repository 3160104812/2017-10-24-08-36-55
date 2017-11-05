void PercolateUp(int p, PriorityQueue H)
{
  int tmp;
  while (H->Elements[p / 2] > H->Elements[p])
  {
    tmp = H->Elements[p];
    H->Elements[p] = H->Elements[p / 2];
    H->Elements[p / 2] = tmp;
    p /= 2;
  }
  return;
}
void PercolateDown(int p, PriorityQueue H)
{
  int i, Child;
  ElementType LastElement;
  LastElement = H->Elements[p]; /* take last and reset size */
  for (i = p/*p==1*/; i * 2 <= H->Size; i = Child)
  { /* Find smaller child */
    Child = i * 2;
    if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
      Child++;
    if (LastElement > H->Elements[Child]) /* Percolate one level */
      H->Elements[i] = H->Elements[Child];
    else
      break; /* find the proper position */
  }
  H->Elements[i] = LastElement;
}