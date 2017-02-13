// Testing framework for the DisjointSet class.

#include <iostream>

#include "DisjointSet.hpp"
#include "CustomAssert.hpp"

int main()
{
  std::cerr << "Running Test for Disjoint Set..." << std::endl;

  DisjointSet test(10);

  for (int i = 0; i < 9; ++i) {
    for (int j = i + 1; j < 10; ++j) {
      ASSERT_CONDITION(test.isConnected(i, j) == false, "No connectivity check");
    }
  }

  ASSERT_CONDITION(test.getNumElements() == 10, "Number of elements check");
  ASSERT_CONDITION(test.getNumSets() == 10, "Number of sets check");

  test.merge(1, 2);
  test.merge(1, 5);
  test.merge(2, 6);
  test.merge(8, 5);
  test.merge(3, 4);
  test.merge(9, 7);

  ASSERT_CONDITION(test.getNumElements() == 10, "Number of elements (after merge) check");
  ASSERT_CONDITION(test.getNumSets() == 4, "Number of sets (after merge) check");

  ASSERT_CONDITION(test.isConnected(1, 2) == true, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(1, 5) == true, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(1, 6) == true, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(1, 8) == true, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(3, 4) == true, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(7, 9) == true, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(0, 1) == false, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(0, 3) == false, "Connectivity (after merge) check");
  ASSERT_CONDITION(test.isConnected(0, 7) == false, "Connectivity (after merge) check");

  return 0;
}

