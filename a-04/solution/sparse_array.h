#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

#include <iterator>
#include <type_traits>
#include <unordered_map>

namespace cpppc {

namespace detail {

template <class T, std::size_t N> class sparse_array;

template <class SparseArrayT> class sparse_array_proxy_ref {
public:
  using self_t = sparse_array_proxy_ref<SparseArrayT>;
  using value_type = typename SparseArrayT::value_type;
  using index_t = typename SparseArrayT::index_t;

public:
  // Constructors
  sparse_array_proxy_ref() = delete;
  sparse_array_proxy_ref(SparseArrayT &array, index_t index)
      : _arr(array), _index(index) {}

  // Element Access
  void operator=(const value_type &rhs) {
    auto iter = _arr._data.find(_index);
    if (iter == _arr._data.end()) {
      _arr._data.insert({_index, rhs});
      return;
    }
    iter->second = rhs;
  }

  operator value_type () const { return _arr.at(_index); }

  void swap(self_t &rhs) {
    std::swap(_arr, rhs._arr);
    std::swap(_index, rhs._index);
  }

private:
  SparseArrayT &_arr;
  index_t _index;
};

template <class SparseArrayT> class sparse_array_iterator {
  using index_t = typename SparseArrayT::index_t;
  using self_t = sparse_array_iterator<SparseArrayT>;
  using proxy_reference = sparse_array_proxy_ref<SparseArrayT>;

public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename SparseArrayT::value_type;
  using pointer = value_type *;
  using reference = proxy_reference;
  using const_reference = const value_type &;
  using difference_type = typename SparseArrayT::difference_type;

public:
  // Constructors
  sparse_array_iterator(SparseArrayT *arr, index_t index)
      : _arr(arr), _index(index) {}

  // Comparison
  bool operator==(const self_t &rhs) const {
    return (_arr == rhs._arr && _index == rhs._index);
  }

  bool operator!=(const self_t &rhs) const { return !(*this == rhs); }

  bool operator<(const self_t &rhs) const { return _index < rhs._index; }

  bool operator>(const self_t &rhs) const { return _index > rhs._index; }

  // Element Access
  reference operator*() { return proxy_reference(*_arr, _index); }

  const_reference operator*() const {
    auto iter = _arr->_data.find(index);
    if (iter == _arr->_data.end()) {
      return _arr->def;
    }
    return iter->second;
  }

  reference operator[](difference_type offset) {
    return proxy_reference(_arr, offset);
  }

  // Arithmetic
  self_t &operator++() {
    ++_index;
    return *this;
  }

  self_t operator++(int) {
    self_t old = *this;
    ++_index;
    return old;
  }

  self_t &operator--() {
    --_index;
    return *this;
  }

  self_t operator--(int) {
    self_t old = *this;
    --_index;
    return old;
  }

  self_t &operator+=(const difference_type offset) {
    _index += offset;
    return *this;
  }

  self_t &operator-=(const difference_type offset) {
    _index -= offset;
    return *this;
  }

  self_t operator+(const difference_type offset) const {
    return self_t(_arr, _index + offset);
  }

  self_t operator-(const difference_type offset) const {
    return self_t(_arr, _index - offset);
  }

  difference_type operator-(const self_t &rhs) const {
    return _index - rhs._index;
  }

private:
  SparseArrayT *_arr;
  index_t _index;
};

} // namespace detail

template <class T, std::size_t N> class sparse_array {
  using self_t = sparse_array<T, N>;
  using proxy_reference = typename detail::sparse_array_proxy_ref<self_t>;
  using const_proxy_reference =
      typename detail::sparse_array_proxy_ref<const self_t>;

public:
  using index_t = int;
  using value_type = T;
  using iterator = detail::sparse_array_iterator<self_t>;
  using const_iterator = detail::sparse_array_iterator<const self_t>;
  using difference_type = index_t;
  using reference = proxy_reference;
  using const_reference = const value_type &;
  using size_type = size_t;

  friend iterator;
  friend proxy_reference;
  friend const_proxy_reference;

public:
  // Constructors
  sparse_array() = default;
  ~sparse_array() = default;

  sparse_array(const self_t &other) = default;
  sparse_array(self_t &&other) = default;

  self_t &operator=(const self_t &other) = default;
  self_t &operator=(self_t &&other) = default;

  // Element access
  reference operator[](index_t index) { return reference(*this, index); }

  const_reference operator[](index_t index) const {
    return _value_or_default(index);
  }

  const_reference at(index_t index) const {
    return _value_or_default(index);
  }

  reference front() { return reference(*this, 0); }

  reference back() { return reference(*this, size() - 1); }

  const_reference front() const { return *begin(); }

  const_reference back() const { return *rbegin(); }

  // Iterators
  iterator begin() { return iterator(this, 0); }

  iterator end() { return iterator(this, _size); }

  iterator rbegin() { return iterator(this, size() - 1); }

  iterator rend() { return iterator(this, -1); }

  const_iterator rbegin() const { return iterator(this, size() - 1); }

  const_iterator rend() const { return iterator(this, -1); }

  const_iterator begin() const { return const_iterator(this, 0); }

  const_iterator end() const { return const_iterator(this, _size); }

  const_iterator cbegin() const { return const_iterator(this, 0); }

  const_iterator cend() const { return const_iterator(this, _size); }

  // Capacity
  size_type max_size() const { return size(); }

  size_type size() const { return _size; }

  bool empty() const { return _size == 0; }

  // Comparison
  bool operator==(const self_t &rhs) const {
    // identity
    if (this == &rhs) {
      return true;
    }
    // equality
    if (_size != rhs.size() || def != rhs.def) {
      return false;
    }
    return std::equal(_data.begin(), _data.end(), rhs._data.begin());
  }

  bool operator!=(const self_t &rhs) const { return !(*this == rhs); }

  bool operator<(const self_t &rhs) const {
    return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
  }

  bool operator>(const self_t &rhs) const {
    return std::lexicographical_compare(rhs.begin(), rhs.end(), begin(), end());
  }

  // Operations
  void fill(const value_type &value) {
    _data.clear();
    def = value;
  }

  void swap(self_t &rhs) {
    _data.swap(rhs._data);
    std::swap(_size, rhs._size);
    std::swap(def, rhs.def);
  }

  void sort() {
    difference_type index = 0;
    for (auto i : _data) {
      _data[index] = *i;
      _data.erase(i);
    }
  }

private:
  const_reference _value_or_default(index_t index) const {
    if (_data.find(index) != _data.end()) {
      return _data.at(index);
    }
    return def;
  }

private:
  std::unordered_map<index_t, T> _data{};
  size_type _size = N;
  value_type def{};
};

template <class T, std::size_t N>
void swap(sparse_array<T, N> a, sparse_array<T, N> b) {
  a.swap(b);
}

template <class T, std::size_t N>
void swap(detail::sparse_array_proxy_ref<sparse_array<T, N>> a,
          detail::sparse_array_proxy_ref<sparse_array<T, N>> b) {
  a.swap(b);
}

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
