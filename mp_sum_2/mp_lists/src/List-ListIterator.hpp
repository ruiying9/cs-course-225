
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        position_=position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        ListIterator newList = *this;
        position_ = position_->next;
        return newList;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        if (position_ && position_->prev) {
            position_ = position_->prev;
        } else if (position_==nullptr){
            position_=this->tail_;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        ListIterator newList = *this;
        position_ = position_->prev;
        return newList;
    }

    bool operator!=(const ListIterator& rhs) {
        return position_!=rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
