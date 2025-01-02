/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_=0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
    ListNode* cur = head_;
    while (cur != nullptr) {
        ListNode* next = cur->next;
        delete cur;
        cur = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if(empty()){
    head_=tail_=newNode;
    newNode -> next = newNode -> prev = NULL;
  }else{
    newNode -> next = head_;
    newNode -> prev = NULL;
    head_->prev=newNode;
    head_=newNode;
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
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if(empty()){
    head_=tail_=newNode;
    newNode -> next = newNode -> prev = NULL;
  }else{
    tail_->next=newNode;
    newNode->prev=tail_;
    newNode->next=nullptr;
    tail_=newNode;
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
  if(start==nullptr || splitPoint<=0){
    return start;
  }
  ListNode * curr = start;
  for (int i = 1; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if(curr == nullptr || curr->next==nullptr){
    return curr;
  }
  ListNode* newNode=curr->next;
  curr->next=nullptr;
  return newNode;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  if(head_==nullptr || head_->next==nullptr){
    return;
  }
  ListNode* curr=head_;
  ListNode* nex=head_->next;
  while(nex!=nullptr && nex!=tail_){
    curr->next=nex->next;
    nex->next->prev=curr;
    curr=curr->next;
    if(nex==tail_) {
      tail_ = nex;
      break;
    }
    tail_->next=nex;
    nex->prev=tail_;
    tail_=nex;
    tail_->next=nullptr;
    nex=curr->next;
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
  ListNode * endNex;
  if (endPoint && endPoint->next) {
    endNex = endPoint->next;
  }else{
    endNex = nullptr;
  }
  endPoint->next=startPoint;
  ListNode * startPrev;
  if (startPoint && startPoint->prev) {
    startPrev = startPoint->prev;
  }else{
    startPrev=nullptr;
  }
  startPoint->prev=endPoint;
  ListNode * current=startPoint;
  while(current!=endPoint){
    ListNode* temp=current->next;
    current->next=current->prev;
    current->prev=temp;
    current=current->prev;
  }
  ListNode* te=current->next;
  current->next=current->prev;
  current->prev=te;
  startPoint->next=endNex;
  endPoint->prev=startPrev;
  if(endNex){
    endNex->prev=startPoint;
  }
  if(startPrev){
    startPrev->next=endPoint;
  }
  if (startPoint == head_) {
    head_ = endPoint;
  }
  if (endPoint == tail_) {
    tail_ = startPoint;
  }
  // ListNode* just=tail_;
  // for(int i=0;i<20;i++){
  //   if(just) cout << "data: " << just->data;
  //   cout <<" previous: ";
  //   if(just->prev) cout << just->prev->data;
  //   else cout << "NULL";
  //   cout << " next: ";
  //   if(just->next) cout << just->next->data << '\n';
  //   else cout << "NULL" << '\n';
  //   just=just->prev;
  // }
  // cout <<"-------------";
}
// template <typename T>
// void List<T>::rever() {
//   ListNode* just=tail_;
//   for(int i=0;i<20;i++){
//     if(just) cout << "data: " << just->data;
//     cout <<" previous: ";
//     if(just->prev) cout << just->prev->data;
//     else cout << "NULL";
//     cout << " next: ";
//     if(just->next) cout << just->next->data << '\n';
//     else cout << "NULL" << '\n';
//     just=just->prev;
//   }
// }

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  int rest=length_/n;
  auto start=head_;
  auto end=head_;
  while(rest!=0){
    for(int i=0; i<(n-1);++i){
      end=end->next;
    }
    reverse(start, end);
    end=start;
    end=end->next;
    start=end;
    rest-=1;
  }
  if(length_%n!=0){
    reverse(start, tail_);
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
  ListNode * cur=nullptr;
  ListNode* start=nullptr;
  ListNode * temp=nullptr;
  while(first!=nullptr&&second!=nullptr){
    if(first->data<second->data){
      if(cur==nullptr){
        cur=first;
        start=first;
        first=first->next;
        continue;
      }
      cur->next=first;
      first->prev=cur;
      cur=cur->next;
      first=first->next;
    } else{
      if(cur==nullptr){
        cur=second;
        start=second;
        second=second->next;
        continue;
      }
      cur->next=second;
      second->prev=cur;
      cur=cur->next;
      second=second->next;
    }
  }
  while(second!=nullptr){
    cur->next=second;
    second->prev=cur;
    cur=cur->next;
    second=second->next;
  }
  while(first!=nullptr){
    cur->next=first;
    first->prev=cur;
    cur=cur->next;
    first=first->next;
  }
  return start;
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
  if (chainLength <= 1) {
    return start;
  }
  ListNode* leftHalf = start;
  ListNode* rightHalf = split(start, chainLength/2);
  leftHalf = mergesort(leftHalf, chainLength/2);
  rightHalf = mergesort(rightHalf, chainLength - chainLength/2);
  start = merge(leftHalf, rightHalf);
  if (start != nullptr) {
    start->prev = nullptr;
  }
  ListNode* newT = start;
  while (newT->next != nullptr) {
    newT = newT->next;
  }
  head_ = start;
  tail_ = newT;
  return start;
}
