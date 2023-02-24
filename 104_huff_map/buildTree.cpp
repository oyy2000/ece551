#include "node.h"

Node *buildTree(uint64_t *freqs)
{
  priority_queue_t pq;
  for (unsigned i = 0; i < 257; i++)
  {
    if (freqs[i])
      pq.push(new Node(i, freqs[i]));
  }

  while (pq.size() > 1)
  {
    Node *leftChild = pq.top();
    pq.pop();
    Node *rightChild = pq.top();
    pq.pop();
    Node *root = new Node(leftChild, rightChild);
    pq.push(root);
  }

  return pq.top();
}
