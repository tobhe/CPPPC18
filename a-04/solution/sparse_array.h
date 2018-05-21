#ifndef CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
#define CPPPC__S03__SPARSE_ARRAY_H__INCLUDED

#include <unordered_map>
#include <iterator>
#include <type_traits>

namespace cpppc {

namespace detail {

template <class SparseArrayT, class ValueT>
class sparse_array_iterator {
  using proxy_reference = typename SparseArrayT::proxy_reference;
  using index_t = typename SparseArrayT::index_t;
  using self_t = sparse_array_iterator<SparseArrayT, ValueT>;
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = ValueT;
  using pointer = value_type*;
  using reference = proxy_reference;
  using difference_type = typename SparseArrayT::difference_type;

public:
  // Constructor
  sparse_array_iterator(SparseArrayT *arr, index_t index) : _arr(arr), _index(index) {}

  // Comparison
  bool operator==(const self_t& rhs) const
  {
    return (*_arr == *rhs._arr && _index == rhs._index);
  }

  bool operator!=(const self_t &rhs) const
  {
    return !(*this==rhs);
  }

  bool operator<(const self_t &rhs) const {
    return _index < rhs._index;
  }

  bool operator>(const self_t &rhs) const {
    return _index > rhs._index;
  }

  // Element Access
  proxy_reference operator*() {
      return (*_arr)[_index];
  }

  // Arithmetic
  self_t &operator++()
  {
    ++_index;
    return *this;
  }

  self_t operator++(int)
  {
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

  self_t &operator+=(const difference_type& rhs)
  {
    _index = _index + rhs;
    return *this;
  }

  self_t &operator-=(const difference_type& rhs)
  {
    _index = _index - rhs;
    return *this;
  }

  self_t &operator+(const difference_type& rhs)
  {
    _index = _index + rhs;
    return *this;
  }

  self_t operator-(const difference_type& rhs)
  {
    _index = _index - rhs;
    return *this;
  }

  difference_type operator-(const self_t &rhs) const { return _index - rhs._index; }

private:
  SparseArrayT *_arr;
  index_t _index;
};

template <class SparseArrayT>
class sparse_array_proxy_ref {
public:
  using self_t = sparse_array_proxy_ref<SparseArrayT>;
  using value_type = typename SparseArrayT::value_type;
  using index_t = typename SparseArrayT::index_t;

public:
  sparse_array_proxy_ref(SparseArrayT &array, index_t index) : _arr(array), _index(index) {}
  ~sparse_array_proxy_ref() = default;

  sparse_array_proxy_ref(sparse_array_proxy_ref &other) = default;
  sparse_array_proxy_ref(sparse_array_proxy_ref &&other) = default;
  self_t& operator=(self_t &&other) = default;

  // Nope because reference member
  sparse_array_proxy_ref() = delete;
  self_t& operator=(self_t& rhs) = delete;

  // Element Access
  void operator=(const value_type &rhs) {
    _arr._data[_index] = rhs;
  }

  operator value_type () const {
    return _arr.at(_index);
  }

private:
  SparseArrayT &_arr;
  index_t _index;
};


} // namespace detail

template <class T, std::size_t N>
class sparse_array {
  using self_t = sparse_array<T, N>;

public:
  using index_t = int;
  using value_type = T;
  using iterator = detail::sparse_array_iterator<self_t, value_type>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_iterator = detail::sparse_array_iterator<const self_t, const value_type>;
  using difference_type = index_t;
  using reference = value_type&;
  using proxy_reference = detail::sparse_array_proxy_ref<self_t>;
  using const_reference = const value_type&;
  using size_type = size_t;

  friend iterator;
  friend const_iterator;
  friend proxy_reference;

public:
  // Constructors
  sparse_array() = default;

  // Element access
  const_reference operator[](index_t index) const
  {
    return at(index);
  }

  proxy_reference operator[](index_t index)
  {
    return proxy_reference(*this, index);
  }

  value_type at(const index_t& index)
  {
    auto iter = _data.find(index);
    if (iter == _data.end()) {
        return def;
    }
    return iter->second;
  }

  const_reference at(const index_t& index) const
  {
    auto iter = _data.find(index);
    if (iter == _data.end()) {
      return def;
    }
    return iter->second;
  }

  proxy_reference front()
  {
    return proxy_reference(*this, 0);
  }

  proxy_reference back()
  {
    return proxy_reference(*this, size()-1);
  }

  const_reference front() const
  {
    return at(0);
  }

  const_reference back() const
  {
    return at(size()-1);
  }

  // Iterators
  iterator begin() {
    return iterator(this, 0);
  }

  iterator end()
  {
    return iterator(iterator(this, _size));
  }

  reverse_iterator rbegin()
  {
    return reverse_iterator(end());
  }

  reverse_iterator rend()
  {
    return reverse_iterator(begin());
  }

  const_iterator begin() const
  {
    return const_iterator(this, 0);
  }

  const_iterator end() const { return const_iterator(this, _size); }

  const_iterator cbegin() const
  {
    return const_iterator(this, 0);
  }

  const_iterator cend() const
  {
    return const_iterator(this, _size);
  }

  // Capacity
  size_type max_size() const
  {
    return size();
  }

  size_type size() const
  {
    return _size;
  }

  bool empty() const
  {
    return _size == 0;
  }

  // Comparison
  bool operator==(const self_t &rhs) const {
    if (_size != rhs.size() || def != rhs.def) {
      return false;
    }
    return std::equal(_data.begin(), _data.end(), rhs._data.begin());
  }

  bool operator!=(const self_t& rhs) const {
    return !(*this == rhs);
  }

  bool operator<(const self_t& rhs) const {
    return std::lexicographical_compare(begin(), end(), rhs.begin(), rhs.end());
  }

  bool operator>(const self_t& rhs) const {
    return std::lexicographical_compare(rhs.begin(), rhs.end(), begin(), end());
  }

  // Operations
  void fill(const value_type& value) {
    _data.clear();
    def = value;
  }

private:
  std::unordered_map<index_t, T> _data{};
  size_type _size = N;
  value_type def{};
};

} // namespace cpppc

#endif // CPPPC__S03__SPARSE_ARRAY_H__INCLUDED
