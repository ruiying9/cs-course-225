/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) return true;
    else if (first[curDim] > second[curDim]) return false;
    return first < second;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    int curr=0;
    int pote=0;
    for(int i=0; i<Dim; i++){
      curr+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
      pote+=(potential[i]-target[i])*(potential[i]-target[i]);
    }
    if (curr>pote) return true;
    else if (curr==pote) return potential<currentBest;
    return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints) {
  root = nullptr;
  if (!newPoints.empty()) {
    size = newPoints.size();
    if (size != 0) {
      root = buildTree(0, size-1, 0, const_cast<vector<Point<Dim>>&>(newPoints));
    }
  }else{
    size = 0;
  }
}
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(int left, int right, int curr, vector<Point<Dim>>& newPoints) {
  if (left > right) {
    return NULL;
  }
  int median = (left + right) / 2;
  Point<Dim> medianPoint = quickSelect(left, right, median, curr, newPoints);
  KDTreeNode* node = new KDTreeNode(medianPoint);
  node->left = buildTree(left, median-1, (curr+1)%Dim, newPoints);
  node->right = buildTree(median+1, right, (curr+1)%Dim, newPoints);
  return node;
}
template <int Dim>
Point<Dim> quickSelect(int left, int right, int find, int curr, vector<Point<Dim>>& newPoints) {
  if(left == right) return newPoints[left];
  int pivIn = (left + right) / 2;
  pivIn = partition(left, right, pivIn, curr, newPoints);
  if (find == pivIn) return newPoints[find];
  else if (find < pivIn) return quickSelect(left, pivIn-1, find, curr, newPoints);
  else return quickSelect(pivIn+1, right, find, curr, newPoints);
}
template <int Dim>
int partition(int left, int right, int pivIn, int curr, vector<Point<Dim>>& newPoints) {
  Point<Dim> pivotV = newPoints[pivIn];
  std::swap(newPoints[pivIn], newPoints[right]);
  int inde = left;
  for (int i = left; i < right; i++) {
    if (smallerDimVal(newPoints[i], pivotV, curr)) {
      std::swap(newPoints[i], newPoints[inde]);
      inde++;
    }
  }
  std::swap(newPoints[inde], newPoints[right]);
  return inde;
}
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  this->root = Copy(other.root);
  this->size = other.size;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::Copy(KDTreeNode* node) {
  if (!node) return nullptr;
  KDTreeNode* newOne = new KDTreeNode(node->point);
  newOne->left = Copy(node->left);
  newOne->right = Copy(node->right);
  return newOne;
}
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
		clear(root);
		this->root = Copy(rhs.root);
    this->size = rhs.size;
	}
	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}
template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) {
  if (root == nullptr) return nullptr;
  KDTreeNode* curr = root;
  std::vector<KDTreeNode*> v;
  int nextDim = 0;
  while (curr->left != nullptr || curr->right != nullptr) {
    if (smallerDimVal(query, curr->point, nextDim)) {
      v.push_back(curr);
      if(curr->left){
        curr = curr->left;
      } else{
        break;
      }
    } else {
      v.push_back(curr);
      if(curr->right){
        curr = curr->right;
      } else{
        break;
      }
    }
    nextDim = (nextDim + 1) % Dim;
  }
  KDTreeNode* previous=curr;
  Point<Dim> nearest = curr->point;
  double bestD = distance(query, nearest);
  int test=0;
  while (!v.empty()) {
    if(Dim<3){
      KDTreeNode* current = v.back();
      v.pop_back();
      double currentD = distance(query, current->point);
      if (currentD < bestD) {
        nearest = current->point;
        bestD = currentD;
      }
      double planeD = abs(current->point[nextDim] - query[nextDim]);
      if (planeD < bestD) {
        KDTreeNode* other;
        if(previous == current->left){
          other=current->right;
        } else{
          other=current->left;
        }
        if (other) {
          double otherD = distance(query, other->point);
          if (otherD < bestD) {
            nearest = other->point;
            bestD = otherD;
          }
          // v.push_back(other);
        }
        previous = current;
      }
      nextDim = (nextDim + 1) % Dim;
    } else{
      KDTreeNode* current;
      current = v.back();
      v.pop_back();
      if(current == root){
        test=1;
      }
      if (test==1) {
        double newDis = distance(query, current->point);
        if(newDis<bestD){
          bestD=newDis;
          nearest=current->point;
        }
        KDTreeNode* other = nullptr;
        if (current->left) {
          v.push_back(current->left);
          other = current->right;
        } else if (current->right) {
          v.push_back(current->right);
          other = current->left;
        }
        if (other) {
          double otherD = distance(query, other->point);
          if (otherD <= bestD) {
            nearest = other->point;
            bestD = otherD;
          }
        }
      } else {
        double currentD = distance(query, current->point);
        if (currentD < bestD) {
          nearest = current->point;
          bestD = currentD;
        }
        if(current->right){
          if(distance(query, current->right->point)<bestD){
            nearest=current->right->point;
            bestD=distance(query, current->right->point);
          }
        }
        KDTreeNode* other;
        if (previous == current->left) {
          other = current->right;
        } else {
          other = current->left;
        }
        if (other) {
          double otherD = distance(query, other->point);
          if (otherD < bestD) {
            nearest = other->point;
            bestD = otherD;
          }
          v.push_back(other);
        }
        previous = current;
      }
      nextDim = (nextDim + 1) % Dim;
    }
  }
  return nearest;
}
template <int Dim>
double distance(const Point<Dim>& query, const Point<Dim>& curr){
  double dist=0.0;
  for(int i =0; i< Dim; i++){
    dist+=(curr[i]-query[i])*(curr[i]-query[i]);
  }
  dist=sqrt(dist);
  return dist;
}
template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp) {
  if (start == end) return;
  while (start + 1 != end) {
    RandIter middle = start + (end - start) / 2;
    middle = partition(start, end, middle, cmp);
    if (k == middle) return;
    if (cmp(*k, *middle)) end = middle;
    else start = middle + 1;
  }
}
template <typename RandIter, typename Comparator>
RandIter partition(RandIter start, RandIter end, RandIter middle, Comparator cmp) {
  RandIter last = end - 1;
  std::swap(*middle, *last);
  RandIter inde = start;
  for (RandIter it = start; it != last; it++) {
    if (cmp(*it, *last)) {
      std::swap(*it, *inde);
      inde++;
    }
  }
  std::swap(*inde, *last);
  return inde;
}