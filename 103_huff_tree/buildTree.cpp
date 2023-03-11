#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (uint64_t i = 0; i < 257; i++) {
    if (counts[i] == 0)
      continue;
    pq.push(new Node(i, counts[i]));
  }
  while (pq.size() > 1) {
    Node * one = pq.top();
    pq.pop();
    Node * two = pq.top();
    pq.pop();
    Node * newNode = new Node(one, two);
    pq.push(newNode);
  }
  return pq.top();
}
