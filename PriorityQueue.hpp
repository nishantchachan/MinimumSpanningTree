// Homework 3: Compute the Minimum Spanning Tree for an Inputted Graph
// PriorityQueue.hpp

#ifndef _HW3_PRIORITY_QUEUE_H_
#define _HW3_PRIORITY_QUEUE_H_

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T1, typename T2>
class PriorityQueue
{
public:
  // Constructor; creates a priority queue with elements type T1 and values type T2.
  // @param preferHighValues True if you want high values to have higher priority, otherwise
  //                         low values will have higher priority.
  PriorityQueue(bool preferHighValues = true);

  // Sets the comparator function such that the ordering is ascending or descending.
  // @param preferHighValues True if you want high values to have higher priority, otherwise
  //                         low values will have higher priority.
  void setComparator(bool preferHighValues);

  // Access the top element in this priority queue.
  // @return Returns the element with the highest priority without removing it from the queue.
  T1 top();

  // Remove the top element in this priority queue.
  // @return Removes and returns the element with the highest priority from the queue.
  T1 pop();

  // Insert an element into this priority queue.
  // @param element The element to insert into the queue.
  // @param value The value of the element (determines its priority).
  void push(T1 element, T2 value);

  // Gets the size of this priority queue.
  // @return The number of elements in the queue.
  int size();

  // Tests if the priority queue is empty.
  // @return True if the priority queue is empty, otherwise false.
  bool empty();

  // Clears the contents of the priority queue.
  void clear();

  // Checks for the first occurrence of a specific element in the the queue.
  // @param element The element whose existence in the queue is to be determined.
  // @return True if the element exists, false otherwise.
  bool contains(T1 element);

  // Changes the value of the first occurrence of a specific element.
  // @param element The element whose value we wish to change.
  // @param value The new value of the element.
  void changePriority(T1 element, T2 value);

  // Access the top element's priority in this priority queue.
  // @return Returns the current highest priority in the queue.
  T2 getTopPriority();

private:
  // The vector of elements in this queue; the first item in the pair is
  // the actual element of type T, while the second item is the priority.
  vector<pair<T1, T2>> elements;

  // The comparison function used to determine the order of the elements in
  // the priority queue. Can choose between:
  //   a. Higher values have higher priority
  //   b. Lower values have higher priority
  function<bool(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)> comparison;

  // Comparison function where the smaller values have higher priority.
  static bool CompareAscending(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

  // Comparison function where larger values have higher priority.
  static bool CompareDescending(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs);

  // Function object that is used to find the first matching element (compares the first item of the pair).
  class FindFirst
  {
  public:
    explicit FindFirst(T1 item) : item(item) {}
    inline bool operator()(const pair<T1, T2> &elem) { return item == elem.first; }
  private:
    T1 item;
  };

};

// Method definitions placed here to avoid clutter.

template <typename T1, typename T2>
PriorityQueue<T1, T2>::PriorityQueue(bool preferHighValues /*=true*/)
{
  setComparator(preferHighValues);
}

template <typename T1, typename T2>
void PriorityQueue<T1, T2>::setComparator(bool preferHighValues)
{
  comparison = preferHighValues ? CompareDescending : CompareAscending;
}

template <typename T1, typename T2>
inline T1 PriorityQueue<T1, T2>::top()
{
  return elements.front().first; // return the element at the top of the heap
}

template <typename T1, typename T2>
T1 PriorityQueue<T1, T2>::pop()
{
  pop_heap(elements.begin(), elements.end(), comparison); // pop the top element from the heap range

  // save and delete the element
  T1 topElement = elements.back().first;
  elements.pop_back();

  return topElement;
}

template <typename T1, typename T2>
void PriorityQueue<T1, T2>::push(T1 element, T2 value)
{
  // insert the element and place it in the correct position in the heap
  elements.push_back(pair<T1, T2>(element, value));
  push_heap(elements.begin(), elements.end(), comparison);
}

template <typename T1, typename T2>
inline int PriorityQueue<T1, T2>::size()
{
  return elements.size();
}

template <typename T1, typename T2>
inline bool PriorityQueue<T1, T2>::empty()
{
  return elements.empty();
}

template <typename T1, typename T2>
inline void PriorityQueue<T1, T2>::clear()
{
  elements.clear();
}

template <typename T1, typename T2>
inline bool PriorityQueue<T1, T2>::contains(T1 element)
{
  return find_if(elements.begin(), elements.end(), FindFirst(element)) != elements.end();
}

template <typename T1, typename T2>
void PriorityQueue<T1, T2>::changePriority(T1 element, T2 value)
{
  typename vector<std::pair<T1, T2> >::iterator it = find_if(elements.begin(), elements.end(), FindFirst(element));
  if (it != elements.end()) {
    (*it).second = value;
    make_heap(elements.begin(), elements.end(), comparison);
  }
}

template <typename T1, typename T2>
bool PriorityQueue<T1, T2>::CompareAscending(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  return lhs.second > rhs.second;
}

template <typename T1, typename T2>
bool PriorityQueue<T1, T2>::CompareDescending(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  return lhs.second < rhs.second;
}

template <typename T1, typename T2>
inline T2 PriorityQueue<T1, T2>::getTopPriority()
{
  return elements.front().second; // return the element's priority at the top of the heap
}

#endif // _HW3_PRIORITY_QUEUE_H_

