namespace cpppc {

template <class ValueT, ValueT default_value> class list;
template <class _list_value_t, class list_node_t> class _list_iterator;

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

  using iterator = _list_iterator<ValueT, list_node>;
  using const_iterator = _list_iterator<const ValueT, const list_node>;

public:
  // Constructors
  list() = default;
  list(const self_t &other) = default; // Copy

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
  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }

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

// _list_iterator<ValueT, list_node>
template <class list_value_t, class list_node_t> class _list_iterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = list_value_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using self_t = _list_iterator<list_value_t, list_node_t>;

public:
  // Constructors
  _list_iterator() = default;
  _list_iterator(const self_t &it) = default;
  _list_iterator(list_node_t &node) : _list_node(&node) {}
  _list_iterator(list_node_t *node) : _list_node(node) {}

  // Operators
  _list_iterator &operator++() {
    _list_node = _list_node->next;
    return *this;
  }

  _list_iterator operator++(int) {
    _list_iterator old = *this;
    _list_node = _list_node->next;
    return old;
  }

  reference operator*() { return _list_node->value; }

  bool operator==(const self_t &rhs) const {
    return (this == &rhs || _list_node == rhs._list_node);
  }

  bool operator!=(const self_t &rhs) const { return !(*this == rhs); }

private:
  list_node_t *_list_node;
};

} // namespace cpppc
