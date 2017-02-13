// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// UndirectedGraph.cpp

#include "UndirectedGraph.hpp"

UndirectedGraph::UndirectedGraph(int numNodes, double density, pair<double, double> distRange)
{
  this->numNodes = numNodes;
  this->numEdges = 0;

  adjacencyMatrix.resize(numNodes);
  for (auto it = adjacencyMatrix.begin(); it != adjacencyMatrix.end(); ++it)
    it->resize(numNodes, 0.0);

  nodeValues.resize(numNodes, numeric_limits<double>::max());

  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // seed value based on the current time
  default_random_engine generator(seed);

  // initialize uniform distributions for the graph density and edge distance calculations
  uniform_real_distribution<double> densityDistribution(0.0, 1.0);
  uniform_real_distribution<double> edgeDistDistribution(distRange.first, distRange.second);

  // iterate all pairs of nodes, checking pairs only once and omitting nodes where i == j
  for (int i = 0; i < numNodes - 1; ++i) {
    for (int j = i + 1; j < numNodes; ++j) {
      if (densityDistribution(generator) < density) // probability calculation is less than the density
        addEdge(i, j, edgeDistDistribution(generator)); // add an edge between the nodes with a distance given by the distribution
    }
  }
}

UndirectedGraph::UndirectedGraph(const char* filename)
{
  ifstream infile(filename);

  infile >> numNodes;
  numEdges = 0;

  adjacencyMatrix.resize(numNodes);
  for (auto it = adjacencyMatrix.begin(); it != adjacencyMatrix.end(); ++it)
    it->resize(numNodes, 0.0);

  nodeValues.resize(numNodes, numeric_limits<double>::max());

  // read the two integer nodes and the cost as a double; process each set
  int node1, node2;
  double cost;
  while (infile >> node1 >> node2 >> cost)
    addEdge(node1, node2, cost);
}

void UndirectedGraph::getNeighbors(int node, vector<int> &neighbors)
{
  neighbors.clear();
  for (auto it = adjacencyMatrix[node].begin(); it != adjacencyMatrix[node].end(); ++it) {
    if (*it != 0.0)
      neighbors.push_back(it - adjacencyMatrix[node].begin());
  }
}

void UndirectedGraph::runPrimAlgorithm(vector<pair<int, int>> &edges, vector<double> &cost)
{
  if (numNodes == 0) return; // account for empty graph

  edges.clear();
  cost.clear();

  PriorityQueue<pair<int, int>, double> pq(false);
  unordered_set<int> visitedNodes;
  vector<int> neighbors;
  double edgeValue;
  pair<int, int> edge; // as a pair of nodes

  visitedNodes.insert(0); // initialize the starting node
  getNeighbors(0, neighbors);
  for (auto it = neighbors.begin(); it != neighbors.end(); ++it) // initialize candidate edges
    pq.push(pair<int, int>(0, *it), getEdgeValue(0, *it));

  // repeat until we have visited all the nodes
  while (visitedNodes.size() != numNodes) {
    edgeValue = pq.getTopPriority();
    edge = pq.pop();

    // start again if we have already visited the destination node
    if (visitedNodes.count(edge.second) > 0) continue;

    visitedNodes.insert(edge.second); // mark the destination node as visited

    // record the edge and its cost
    cost.push_back(edgeValue);
    edges.push_back(edge);

    // add condidate edges, ignoring visited nodes
    getNeighbors(edge.second, neighbors);
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
      if (visitedNodes.count(*it) == 0)
        pq.push(pair<int, int>(edge.second, *it), getEdgeValue(edge.second, *it));
    }
  }
}

void UndirectedGraph::runKruskalAlgorithm(vector<pair<int, int>> &edges, vector<double> &cost)
{
  if (numNodes == 0) return; // account for empty graph

  edges.clear();
  cost.clear();

  DisjointSet ds(numNodes);
  PriorityQueue<pair<int, int>, double> pq(false);
  double edgeValue;
  pair<int, int> edge; // as a pair of nodes

  for (int i = 0; i < numNodes - 1; ++i) {
    for (int j = i + 1; j < numNodes; ++j) {
      if (isAdjacent(i, j))
        pq.push(pair<int, int>(i, j), getEdgeValue(i, j));
    }
  }

  while (!pq.empty()) {
    edgeValue = pq.getTopPriority();
    edge = pq.pop();

    if (!ds.isConnected(edge.first, edge.second)) {
      // record the edge and its cost
      cost.push_back(edgeValue);
      edges.push_back(edge);

      ds.merge(edge.first, edge.second); // connect the two sets
    }
  }
}

