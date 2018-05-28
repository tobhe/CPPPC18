#include <functional>
namespace cpppc {

namespace detail {
template <class LazySequence> class lazy_sequence_iterator {
  using self_t = lazy_sequence_iterator<LazySequence>;

public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename LazySequence::value_type;
  using pointer = value_type *;
  using reference = value_type &;
  using difference_type = typename LazySequence::size_type;

public:
  // Constructor
  lazy_sequence_iterator(LazySequence *seq, difference_type index)
      : _seq(seq), _index(index) {}

  // Element Access
  value_type operator*() const { return (*_seq)[_index]; }

  value_type operator[](int offset) const {
    return(*_seq)[_index + offset];
  }

  // Arithmetic

  self_t &operator++() {
    ++_index;
    return *this;
  }

  self_t operator++(int) {
    self_t copy = *this;
    ++_index;
    return copy;
  }

  self_t &operator--() {
    --_index;
    return *this;
  }

  self_t operator--(int) {
    self_t copy = *this;
    --_index;
    return copy;
  }

  self_t &operator+=(int offset) const {
    _index += offset;
    return *this;
  }

  self_t &operator-=(int offset) const {
    _index -= offset;
    return *this;
  }

  self_t operator+(int offset) const { return self_t(_seq, _index + offset); }

  self_t operator-(int offset) const { return self_t(_seq, _index - offset); }

  // Comparison
  bool operator==(const self_t &rhs) {
    return (_seq == rhs._seq && _index == rhs._index);
  }

  bool operator!=(const self_t &rhs) { return !(*this == rhs); }

private:
  LazySequence *_seq;
  difference_type _index;
};
} // namespace detail

template <class T> class lazy_sequence {
  using self_t = lazy_sequence<T>;

public:
  using size_type = size_t;
  using value_type = T;
  using iterator = typename detail::lazy_sequence_iterator<self_t>;
  using const_iterator = typename detail::lazy_sequence_iterator<const self_t>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  // Constructors
  lazy_sequence(size_type size, std::function<value_type(size_type)> fun)
      : _size(size), _fun(fun) {}

  // Iterators
  iterator begin() { return iterator(this, 0); }

  iterator end() { return iterator(this, _size); }

  const_iterator begin() const { return const_iterator(this, 0); }

  const_iterator end() const { return const_iterator(this, _size); }

  reverse_iterator rbegin() { return reverse_iterator(this, 0); }

  reverse_iterator rend() { return reverse_iterator(this, _size); }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(this, 0);
  }

  const_reverse_iterator rend() const {
    return const_reverse_iterator(this, _size);
  }

  // Element Access
  value_type operator[](const size_type index) const { return _fun(index); }

  value_type &front() const { return *begin(); }

  value_type &back() const { return *rbegin(); }

  // Capacity
  size_type size() const { return _size; }

  bool empty() const { return _size == 0; }

  // Comparison
  bool operator==(const self_t &rhs) const {
    if (_size != rhs.size()) {
      return false;
    }
    return std::equal(begin(), end(), rhs.begin());
  }

  bool operator!=(const self_t &rhs) const { return !(*this == rhs); }

private:
  size_type _size;
  std::function<int(int)> _fun;
};
} // namespace cpppc
