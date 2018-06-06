#ifndef CPPPC__S06__LIST_H__INCLUDED
#define CPPPC__S06__LIST_H__INCLUDED

#include "forward_iterator_base.h"

namespace cpppc {

template <class ValueT, ValueT default_value> class list;
template <class ListType> class ListIterator;

// list<int32_t, -1>
template <class ValueT, ValueT default_value = ValueT()> class list {

  using self_t = list<ValueT, default_value>;

public:
  // Container concept
  using value_type = ValueT;
  using reference = ValueT &;
  using const_reference = const ValueT &;
  using size_type = size_t;

  struct list_node {
    list_node *next;
    ValueT value;
  };

  using iterator = ListIterator<self_t>;
  using const_iterator = ListIterator<const self_t>;

public:
  // Constructors
  list() = default;

  list(const self_t &other) {
    // This is so stupid, but it werks
    if (other.size() == 0) {
      return;
    }

    self_t l1;
    for (auto i : other) {
      l1.push_front(i);
    }
    for (auto i : l1) {
      push_front(i);
    }
  }

  list(const size_type count, const ValueT &value) {
    for (size_type i = 0; i < count; ++i) {
      push_front(value);
    }
  }

  template <class InputIt, class value_type = typename std::iterator_traits<
                               InputIt>::value_type>
  list(InputIt first, InputIt last) {
    for (; first != last; ++first) {
      push_front(*first);
    }
  }
  list(const size_type count) {
    for (size_type i = 0; i < count; ++i) {
      push_front(default_value);
    }
  }

  // Operators
  self_t &operator=(const self_t &rhs) = default;

  bool operator==(const self_t &other) {
    return std::equal(begin(), end(), other.begin());
  }

  bool operator!=(const self_t &other) { return !(*this == other); }

public:
  // Iterators
  iterator begin() { return iterator{_head}; }
  iterator end() { return iterator{_back}; }
  const_iterator begin() const { return const_iterator{_head}; }
  const_iterator end() const { return const_iterator{_back}; }

  // Modifiers
  void push_front(const ValueT &value) { _head = new list_node{_head, value}; }
  void pop_front() {
    auto tmp = _head;
    _head = _head->next;
    delete tmp;
  }

  // Element access
  value_type front() { return *begin(); }
  // const_reference front() const { return *begin(); }

  // Capacity
  bool empty() const { return begin() == end(); }
  size_type size() const { return std::distance(begin(), end()); }
  size_type max_size() const { return std::numeric_limits<size_type>::max(); }

private:
  static list_node _back;
  list_node *_head = &_back;
};

template <class ValueT, ValueT default_value>
typename list<ValueT, default_value>::list_node
    list<ValueT, default_value>::_back = {nullptr, default_value};

template <class ListType>
class ListIterator : public ForwardIteratorBase<ListIterator<ListType>> {

  using self_t = ListIterator<ListType>;
  using base_t = ForwardIteratorBase<self_t>;
  using list_node_t = typename ListType::list_node;

public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = typename ListType::value_type;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_reference = const reference;

public:
  // Constructors
  ListIterator() = default;
  ListIterator(const self_t &it) = default;
  ListIterator(list_node_t &node) : _list_node(&node) {}
  ListIterator(list_node_t *node) : _list_node(node) {}

  constexpr reference dereference() { return _list_node->value; }

  constexpr void increment(difference_type count) {
    for (auto i = 0; i < count; ++i) {
      _list_node = _list_node->next;
    }
  }

  bool operator==(const self_t &rhs) const {
    return (this == &rhs || _list_node == rhs._list_node);
  }

  bool operator!=(const self_t &rhs) const { return !(*this == rhs); }

private:
  list_node_t *_list_node;
};

} // namespace cpppc

#endif
