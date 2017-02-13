// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// DisjointSet.hpp

#ifndef _HW3_DISJOINT_SET_H_
#define _HW3_DISJOINT_SET_H_

#include <vector>

using namespace std;

class DisjointSet
{
public:
  // Constructor; creates an empty disjoint set data structure.
  DisjointSet();

  // Constructor; creates a disjoint set data structure with the given number of
  // elements, where the element ID's range from 0 to n - 1.
  // @param numElements The number of elements (n).
  DisjointSet(int numElements);

  // Destructor.
  ~DisjointSet();

  // Determines if the two given nodes are connected.
  // @param nodeID1 The index of the first node.
  // @param nodeID2 The index of the second node.
  // @return True if the nodes are in the same set, false otherwise.
  bool isConnected(int nodeID1, int nodeID2);

  // Combines the two sets that the given nodes belong to into a single set.
  // @param nodeID1 The index of the first node.
  // @param nodeID2 The index of the second node.
  void merge(int nodeID1, int nodeID2);

  // Gets the current number of elements in this disjoint set.
  // @return The number of elements.
  int getNumElements();

  // Gets the current number of sets in this disjoint set.
  // @return The number of sets.
  int getNumSets();

private:
  // Internal representation of a node.
  class Node {
  public:
    Node() : parent(this), rank(0) {}

    Node *parent; // the parent node of this node
    int rank; // roughly represents the depth of this node's subtree
  };

  // Finds the representative node of the set.
  Node* find(Node *node);

  // The current number of sets.
  int numSets;

  // Stores the nodes.
  vector<Node*> nodes;

};

// Inline function definitions placed here to avoid linker errors.

inline int DisjointSet::getNumElements()
{
  return nodes.size();
}

inline int DisjointSet::getNumSets()
{
  return numSets;
}

#endif // _HW3_DISJOINT_SET_H_

