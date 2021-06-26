#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * tmp = head_;
  ListNode * tmp2 = tmp;
  while (tmp != NULL) {
    tmp2 = tmp2->next;
    delete tmp;
    tmp = tmp2;
  }
  tmp = NULL;
  tmp2 = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ != NULL) {
    newNode->next = head_;
    newNode->prev = NULL;
    head_->prev = newNode;
    head_ = newNode;
  } else {
    head_ = newNode;
    tail_ = newNode;
    newNode->next = NULL;
    newNode->prev = NULL;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * NewNode = new ListNode(ndata);
  if (tail_ != NULL) {
    tail_->next = NewNode;
    NewNode->next = NULL;
    NewNode->prev = tail_;
    tail_ = NewNode;
  } else {
    tail_ = NewNode;
    head_ = NewNode;
    tail_->next = NULL;
    tail_->prev = NULL;
  }

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */

template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1

  ListNode * curr = start;
    for (int i = 0; i < splitPoint && curr != NULL; i++) {
      curr = curr->next;
    }

    if (curr != NULL && curr->prev != NULL) {

      curr->prev->next = NULL;
      curr->prev = NULL;
    }

    return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode * first = head_;
  ListNode * second = head_->next;
  ListNode * third = second->next;
  ListNode * tmp_tail;
  int n;
  if (length_ % 3 == 0) {
    n = length_/3;
  } else {
    n = (int)(length_/3);
  }
  if (n < 1) {
    return;
  }
  for (int i = 0; i < n; i++) {
    if (i == 0) {
      first->next = third->next;
      third->next = first;
      first->prev = third;
      second->prev = nullptr;
      head_ = second;
      tmp_tail = first;
    } else {
      first = tmp_tail->next;
      second = tmp_tail->next->next;
      third = tmp_tail->next->next->next;
      if (third->next != nullptr) {
        first->next = third->next;
      } else {
        first->next = nullptr;
      }
      third->next = first;
      first->prev = third;
      second->prev = tmp_tail;
      tmp_tail->next = second;
      tmp_tail = first;
    }
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL) {
    return;
  }
  ListNode * tmp;
  ListNode * current = startPoint;
  ListNode * start_prev = startPoint->prev;
  ListNode * end_next = endPoint->next;
  ListNode * initial_start = startPoint;
  ListNode * initial_end = endPoint;

  while (current != end_next) {
    tmp = current->prev;
    current->prev = current->next;
    current->next = tmp;
    current = current->prev;
  }  

  initial_end->prev = start_prev;
  initial_start->next = end_next;

  if (start_prev != NULL) {
    start_prev->next = initial_end;
  } 

  if (end_next != NULL) {
    end_next->prev = initial_start;
  }

  startPoint = initial_end;
  endPoint = initial_start;

  if (head_ == initial_start) {
    head_ = initial_end;
  }
  if (tail_ == initial_end) {
    tail_ = initial_start; 
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n >= length_) {
    reverse(head_, tail_);
    return;
  }
  if (n <= 1) {
    return;
  }
  int blocks;
  if (length_%n > 0) {
    blocks = length_/n + 1;
  } 
  if (length_%n == 0) {
    blocks = length_/n;
  }

  for (int i = 1; i < blocks + 1; i++) {
    ListNode * tmp_end = head_;
    ListNode * tmp_start = head_;
    for (int k = 0; k < i*n - 1; k++) {
      if (tmp_end->next != NULL) {
        tmp_end = tmp_end->next;
      }
    }
    for (int m = 0; m < (i-1)*n; m++) {
        tmp_start = tmp_start->next;
    }
    reverse(tmp_start, tmp_end);
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  if (second == NULL && first == NULL) {
    return NULL;
  }
  ListNode * head;
  if (first->data < second->data) {
    head = first;
    first = first->next;
  } else {
    head = second;
    second = second->next;
  }
  ListNode * current = head;
  while (first != NULL && second != NULL) {
    if (first->data < second->data) {
      current->next = first;
      first->prev = current;
      current = first;
      first = first->next;
    } else {
      current->next = second;
      second->prev = current;
      current = second;
      second = second->next;
    }
  }

  if (first == NULL && second != NULL) {
    current->next = second;
    second->prev = current;
  }
  if (second == NULL && first != NULL) {
    current->next = first;
    first->prev = current;
  }
  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 0 || chainLength == 1) {
    return start;
  } else {
    int length = chainLength/2;
    ListNode * middle = split(start, length);
    ListNode * left_part = mergesort(start, length);
    ListNode * right_part = mergesort(middle, chainLength - length);
    return merge(left_part, right_part);
  }
}
