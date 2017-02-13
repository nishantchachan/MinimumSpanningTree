// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// DisjointSet.cpp

#include "DisjointSet.hpp"

DisjointSet::DisjointSet()
{
  numSets = 0;
}

DisjointSet::DisjointSet(int numElements)
{
  this->numSets = numElements;

  for (int i = 0; i < numElements; ++i)
    nodes.push_back(new Node());
}

DisjointSet::~DisjointSet()
{
  for (auto it = nodes.begin(); it != nodes.end(); ++it)
    delete *it;
  nodes.clear();
  numSets = 0;
}

bool DisjointSet::isConnected(int nodeID1, int nodeID2)
{
  return find(nodes[nodeID1]) == find(nodes[nodeID2]);
}

void DisjointSet::merge(int nodeID1, int nodeID2)
{
  Node *root1 = find(nodes[nodeID1]);
  Node *root2 = find(nodes[nodeID2]);
  if (root1 == root2) return; // already in the same set

  // merge the smaller tree into the larger tree (union by rank)
  if (root1->rank < root2->rank)
    root1->parent = root2;
  else if (root1->rank > root2->rank)
    root2->parent = root1;
  else { // if they are the same rank, increment the rank
    root2->parent = root1;
    root1->rank += 1;
  }

  numSets--;
}

DisjointSet::Node* DisjointSet::find(Node *node)
{
  // recursively follows the parent node until it reaches the root
  // simultaneously flattens the tree structure (path compression) for optimization
  if (node->parent != node)
    node->parent = find(node->parent);
  return node->parent;
}

