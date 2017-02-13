// UC Santa Cruz C++ For C Programmers
// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// Main.cpp
// Runs Prim's and Kruskal's algorithm on a graph specified from an input file.

#include <iostream>
#include <numeric>

#include "UndirectedGraph.hpp"

using namespace std;

int main(int argc, char **argv)
{
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }

  UndirectedGraph graph(argv[1]);
  vector<pair<int, int>> edges;
  vector<double> cost;

  graph.runPrimAlgorithm(edges, cost);
  cout << "Prim's algorithm's total cost: " << accumulate(cost.begin(), cost.end(), 0.0) << endl;
  for (int i = 0; i < edges.size(); ++i)
    cout << edges[i].first << " -> " << edges[i].second << " (" << cost[i] << ")" << endl;

  cout << endl;

  graph.runKruskalAlgorithm(edges, cost);
  cout << "Kruskal's algorithm's total cost: " << accumulate(cost.begin(), cost.end(), 0.0) << endl;
  for (int i = 0; i < edges.size(); ++i)
    cout << edges[i].first << " -> " << edges[i].second << " (" << cost[i] << ")" << endl;

  return 0;
}

