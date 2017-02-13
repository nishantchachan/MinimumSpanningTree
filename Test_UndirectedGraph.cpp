// Testing framework for the UndirectedGraph class.

#include <iostream>
#include <algorithm>
#include <utility>

#include "UndirectedGraph.hpp"
#include "CustomAssert.hpp"

void UndirectedGraph_TestNodeSanity()
{
  std::cerr << "Running Test for Node Sanity..." << std::endl;

  for (int i = 0; i < 100; i++) {
    UndirectedGraph test(i, 0.0, std::pair<double, double>(0.0, 0.0));
    ASSERT_CONDITION(test.getNumNodes() == i, "Node initialization check");
  }
}

void UndirectedGraph_TestDensitySanity()
{
  std::cerr << "Running Test for Density Sanity..." << std::endl;

  UndirectedGraph test1(100, 0.0, std::pair<double, double>(0.0, 0.0));
  ASSERT_CONDITION_SHOW_PASS(test1.getNumEdges() == 0, "No edge check");

  UndirectedGraph test2(100, 1.0, std::pair<double, double>(0.0, 0.0));
  ASSERT_CONDITION_SHOW_PASS(test2.getNumEdges() == 100 * (100 - 1) / 2, "Complete graph check");

  for (double i = 0.01; i < 1.00; i += 0.01) {
    UndirectedGraph test(100, 0.0, std::pair<double, double>(0.0, 0.0));
    ASSERT_CONDITION(test.getNumEdges() >= 0, "Min edge-count bounds check");
    ASSERT_CONDITION(test.getNumEdges() <= 100 * (100 - 1) / 2, "Max edge-count bounds check");
  }
}

void UndirectedGraph_TestEdgeDistanceSanity()
{
  std::cerr << "Running Test for Edge Distance Sanity..." << std::endl;

  for (double i = 1.0; i < 10.0; i += 0.1) {
    UndirectedGraph test(100, 1.0, std::pair<double, double>(i, 10.0));
    for (int j = 0; j < 100; j++) {
      for (int k = 0; k < 100; k++) {
        if (test.isAdjacent(j, k)) {
          ASSERT_CONDITION(test.getEdgeValue(j, k) >= i, "Min edge distance bounds check: varying min limit");
          ASSERT_CONDITION(test.getEdgeValue(j, k) <= 10.0, "Max edge distance bounds check: varying min limit");
        }
      }
    }
  }

  for (double i = 10.0; i > 1.0; i -= 0.1) {
    UndirectedGraph test(100, 1.0, std::pair<double, double>(1.0, i));
    for (int j = 0; j < 100; j++) {
      for (int k = 0; k < 100; k++) {
        if (test.isAdjacent(j, k)) {
          ASSERT_CONDITION(test.getEdgeValue(j, k) >= 1.0, "Min edge distance bounds check: varying max limit");
          ASSERT_CONDITION(test.getEdgeValue(j, k) <= i, "Max edge distance bounds check: varying max limit");
        }
      }
    }
  }
}

// Helper function to count edges based on adjacency.
int countEdges(UndirectedGraph &g)
{
  int count = 0;
  for (int i = 0; i < g.getNumNodes(); i++) {
    for (int j = 0; j < g.getNumNodes(); j++) {
      count += g.isAdjacent(i, j) ? 1 : 0;
    }
  }
  return count / 2;
}

void UndirectedGraph_TestAdjacency()
{
  std::cerr << "Running Test for Adjacency..." << std::endl;

  // Full graph.
  UndirectedGraph test1(100, 1.0, std::pair<double, double>(1.0, 1.0));
  ASSERT_CONDITION_SHOW_PASS(countEdges(test1) == 100 * (100 - 1) / 2, "Complete graph adjacency count check");
  vector<int> neighbors;
  for (int i = 0; i < 100; i++) {
    test1.getNeighbors(i, neighbors);
    ASSERT_CONDITION(neighbors.size() == 99, "Neighbor count check");
    int j = 0;
    while (j < 100) {
      if (j != i)
        ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), j) != neighbors.end(), "Neighbor correctness check");
      j++;
    }
  }

  // Empty graph.
  UndirectedGraph test2(100, 0.0, std::pair<double, double>(1.0, 1.0));
  ASSERT_CONDITION_SHOW_PASS(countEdges(test2) == 0, "Graph with no edges adjacency count check");

  // Graph with some edges added.
  for (int i = 25; i < 75; i++)
    test2.addEdge(0, i, 1.0);
  ASSERT_CONDITION_SHOW_PASS(countEdges(test2) == 50, "Edges added: adjacency count check");
  test2.getNeighbors(0, neighbors);
  ASSERT_CONDITION_SHOW_PASS(neighbors.size() == 50, "Edges added: neighbor count check");
  for (int i = 25; i < 75; i++)
    ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), i) != neighbors.end(), "Edges added: neighbor correctness check");
  ASSERT_CONDITION_SHOW_PASS(test2.getNumEdges() == 50, "Edges added: edge count check");

  for (int i = 0; i < 100; i++) {
    if (i >= 25 && i < 75) {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == true, "Edges added: connected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == true, "Edges added: connected nodes adjacency test, reversed");
    }
    else {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == false, "Edges added: unconnected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == false, "Edges added: unconnected nodes adjacency test, reversed");
    }
  }

  // Graph with some edges deleted.
  for (int i = 35; i < 65; i++)
    test2.deleteEdge(0, i);
  ASSERT_CONDITION_SHOW_PASS(countEdges(test2) == 20, "Edges deleted: adjacency count check");
  test2.getNeighbors(0, neighbors);
  ASSERT_CONDITION_SHOW_PASS(neighbors.size() == 20, "Edged deleted: neighbor count check");
  for (int i = 25; i < 35; i++)
    ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), i) != neighbors.end(), "Edges deleted: neighbor correctness check 1");
  for (int i = 65; i < 75; i++)
    ASSERT_CONDITION(find(neighbors.begin(), neighbors.end(), i) != neighbors.end(), "Edges deleted: neighbor correctness check 2");
  ASSERT_CONDITION_SHOW_PASS(test2.getNumEdges() == 20, "Edges deleted: edge count check");

  for (int i = 0; i < 100; i++) {
    if ((i >= 25 && i < 35) || (i >= 65 && i < 75)) {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == true, "Edges deleted: connected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == true, "Edges deleted: connected nodes adjacency test, reversed");
    }
    else {
      ASSERT_CONDITION(test2.isAdjacent(0, i) == false, "Edges deleted: unconnected nodes adjacency test");
      ASSERT_CONDITION(test2.isAdjacent(i, 0) == false, "Edges deleted: unconnected nodes adjacency test, reversed");
    }
  }
}

void UndirectedGraph_TestReadFromFile()
{
  std::cerr << "Running Test for File Reading..." << std::endl;

  UndirectedGraph test("SampleTestData.txt");

  ASSERT_CONDITION(test.isAdjacent(0, 1) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(0, 2) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(0, 3) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(1, 0) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(2, 0) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(3, 0) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(19, 16) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(19, 17) == true, "Adjacency test");
  ASSERT_CONDITION(test.isAdjacent(19, 18) == true, "Adjacency test");

  ASSERT_CONDITION(test.getEdgeValue(10, 12) == 27.0, "Edge value test");
  ASSERT_CONDITION(test.getEdgeValue(10, 13) == 13.0, "Edge value test");
  ASSERT_CONDITION(test.getEdgeValue(10, 14) == 25.0, "Edge value test");
}

int main()
{
  UndirectedGraph_TestNodeSanity();
  UndirectedGraph_TestDensitySanity();
  UndirectedGraph_TestEdgeDistanceSanity();
  UndirectedGraph_TestAdjacency();

  UndirectedGraph_TestReadFromFile();

  return 0;
}

