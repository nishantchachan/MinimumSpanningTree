// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// UndirectedGraph.hpp

#ifndef _HW3_UNDIRECTED_GRAPH_H_
#define _HW3_UNDIRECTED_GRAPH_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <limits>
#include <chrono>
#include <random>

#include "PriorityQueue.hpp"
#include "DisjointSet.hpp"

using namespace std;

class UndirectedGraph
{
public:
  // Constructor.
  // @param numNodes The number of nodes in this graph.
  // @param density The edge density of this graph, from 0.0 to 1.0.
  // @param distRange The edge distance range (min and max values).
  UndirectedGraph(int numNodes, double density, pair<double, double> distRange);

  // Construcor.
  // @param filename The string representing the name of the file to open.
  UndirectedGraph(const char* filename);

  // Returns the number of nodes in this graph.
  // @return The number of nodes in this graph.
  int getNumNodes();

  // Returns the number of edges in this graph.
  // @return The number of edges in this graph.
  int getNumEdges();

  // Test if there is an edge between two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @return True if an edge exists, otherwise false.
  bool isAdjacent(int node1, int node2);

  // Get all nodes connected to the given node.
  // @param node The node to check for any connections.
  // @param neighbors The reference vector of neighbors returned; any existing content will be cleared.
  void getNeighbors(int node, vector<int> &neighbors);

  // Adds an edge between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @param dist The non-zero edge distance.
  void addEdge(int node1, int node2, double dist);

  // Delete the edge between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  void deleteEdge(int node1, int node2);

  // Returns the value associated with the node.
  // @param node The node whose value we want.
  // @return The value at that node.
  double getNodeValue(int node);

  // Sets the value associated with the node.
  // @param node The node whose value we want to set.
  // @param value The value to set.
  void setNodeValue(int node, double value);

  // Returns the value associated with the edge between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @return The edge value.
  double getEdgeValue(int node1, int node2);

  // Sets the edge value between the two nodes.
  // @param node1 The first node.
  // @param node2 The second node.
  // @param dist The edge value to set.
  void setEdgeValue(int node1, int node2, double value);

  // Run Prim's Algorithm to find the Minimum Spanning Tree of this graph.
  // @param edges The reference vector of edges (as pairs of node indices) returned; any existing content will be cleared.
  // @param cost The reference vector of costs (associated with the edges) returned; any existing content will be cleared.
  void runPrimAlgorithm(vector<pair<int, int>> &edges, vector<double> &cost);

  // Run Kruskal's Algorithm to find the Minimum Spanning Tree of this graph.
  // @param edges The reference vector of edges (as pairs of node indices) returned; any existing content will be cleared.
  // @param cost The reference vector of costs (associated with the edges) returned; any existing content will be cleared.
  void runKruskalAlgorithm(vector<pair<int, int>> &edges, vector<double> &cost);

private:
  // The number of nodes in this undirected graph.
  int numNodes;

  // The number of edges in this undirected graph.
  int numEdges;

  // The graph, represented by an adjacency matrix.
  // Each value in the matrix represents the distance between
  // the nodes (which are represented by the vector indices).
  vector<vector<double>> adjacencyMatrix;

  // The value of each node in this undirected graph.
  vector<double> nodeValues;

};

// Inline function definitions placed here to avoid linker errors.

inline int UndirectedGraph::getNumNodes()
{
  return numNodes;
}

inline int UndirectedGraph::getNumEdges()
{
  return numEdges;
}

inline bool UndirectedGraph::isAdjacent(int node1, int node2)
{
  return adjacencyMatrix[node1][node2] != 0.0;
}

inline void UndirectedGraph::addEdge(int node1, int node2, double dist)
{
  setEdgeValue(node1, node2, dist);
}

inline void UndirectedGraph::deleteEdge(int node1, int node2)
{
  adjacencyMatrix[node1][node2] = 0.0;
  adjacencyMatrix[node2][node1] = 0.0;

  numEdges--; // update the number of edges
}

inline double UndirectedGraph::getNodeValue(int node)
{
  return nodeValues.at(node);
}

inline void UndirectedGraph::setNodeValue(int node, double value)
{
  nodeValues.at(node) = value;
}

inline double UndirectedGraph::getEdgeValue(int node1, int node2)
{
  return adjacencyMatrix[node1][node2];
}

inline void UndirectedGraph::setEdgeValue(int node1, int node2, double value)
{
  // increment the number of edges if the nodes are not already connected
  if (!isAdjacent(node1, node2))
    numEdges++;

  adjacencyMatrix[node1][node2] = value;
  adjacencyMatrix[node2][node1] = value;
}

#endif // _HW3_UNDIRECTED_GRAPH_H_

