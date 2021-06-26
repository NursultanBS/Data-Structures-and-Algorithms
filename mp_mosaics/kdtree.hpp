/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <iostream>

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if (curDim > (Dim - 1) || curDim < 0) {
      return false;
    }
    if (first[curDim] < second[curDim]) {
      return true;
    } 
    if (first[curDim] > second[curDim]) {
      return false;
    }
    return (first < second);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double distance_current = distance(currentBest, target);
    double distance_potential = distance(potential, target);
    if (distance_current < distance_potential) {
      return false;
    }
    if (distance_current > distance_potential) {
      return true;
    }
    return (potential < currentBest);
}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim>& point_1, const Point<Dim>& point_2) const {
    double distance = 0;
    for (unsigned i = 0; i < Dim; ++i) {
      distance += (point_1[i] - point_2[i]) * (point_1[i] - point_2[i]);
    }
    return distance;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    vector<Point<Dim>> list_copy; 
    list_copy.assign(newPoints.begin(), newPoints.end());
    root = construct_tree(list_copy, 0, 0, list_copy.size() - 1);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::construct_tree(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right) {
  size = 0;
  if (list.empty() || left > right || left<0 || right<0 || left >=list.size() || right>=list.size()) {
    return NULL;
  }
  unsigned median = (left + right)/2;
  KDTreeNode * subroot = new KDTreeNode(quickselect(list, dimension % Dim, left, right, median));
  dimension++; 
  size++;
  subroot->left = construct_tree(list, dimension % Dim, left, median - 1);
  subroot->right = construct_tree(list, dimension % Dim, median + 1, right);
  return subroot;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned z) {
    if (left == right) {
      return list[left];
    }
    unsigned pivotIndex = partition(list, dimension, left, right, z);
    if (z == pivotIndex) {
      return list[z];
    } else if (z < pivotIndex) {
      return quickselect(list, dimension, left, pivotIndex - 1, z);
    } else {
      return quickselect(list, dimension, pivotIndex + 1, right, z);
    }
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned pivotIndex) {
    Point<Dim> pivotValue = list[pivotIndex];
    swap (list[pivotIndex], list[right]);
    unsigned storeIndex = left;
    for (unsigned i = left; i < right; ++i) {
      if (smallerDimVal(list[i], pivotValue, dimension)) {
        swap(list[storeIndex], list[i]);
        storeIndex++;
      }
    }
    swap(list[right], list[storeIndex]);
    return storeIndex;
}

template <int Dim>
void KDTree<Dim>::swap(Point<Dim> & point_1, Point<Dim> & point_2) {
  Point<Dim> tmp = point_1;
  point_1 = point_2;
  point_2 = tmp;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  copy(this->root, other.root);
  size = other.size;
}

template <int Dim>
void KDTree<Dim>::copy(KDTree<Dim> * subroot_1, KDTree<Dim> * subroot_2) {
  if (subroot_2 != NULL) {
    subroot_1 = new KDTreeNode();
    subroot_1->point = subroot_2->point;
    copy(subroot_1->left, subroot_2->left);
    copy(subroot_1->right, subroot_2->right);
  } else {
    subroot_1 = NULL;
  }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  clear(this->root);
  copy(this->root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  clear(this->root);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode *& node) {
  if (node != NULL) {
    clear(node->left);
    clear(node->right);
    delete node;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    return findNearestNeighbor(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, KDTreeNode * node, int dimension) const {
  if (node->left == NULL && node->right == NULL) {
    return node->point;
  }
  Point<Dim> curbest = node->point;
  Point<Dim> closest = curbest;
  bool left_side = smallerDimVal(query, curbest, dimension);
  if (left_side == true && node->left != NULL) {
    closest = findNearestNeighbor(query, node->left, (dimension+1) % Dim);
  } else if (left_side == false && node->right != NULL) {
    closest = findNearestNeighbor(query, node->right, (dimension+1) % Dim);
  }

  if (shouldReplace(query, curbest, closest)) {
    curbest = closest;
  }

  double radius = distance(query, closest);
  double dimension_radius = (query[dimension] - node->point[dimension])*(query[dimension] - node->point[dimension]);

  if(dimension_radius <= radius) {
    if (left_side == false && node->left != NULL) {
      closest = findNearestNeighbor(query, node->left, (dimension+1) % Dim);
      if (shouldReplace(query, curbest, closest)) {
        curbest = closest;
      }
    } else if (left_side == true && node->right != NULL) {
      closest = findNearestNeighbor(query, node->right, (dimension+1) % Dim);
      if (shouldReplace(query, curbest, closest)) {
        curbest = closest;
      }
    }
  }
  return curbest;
}