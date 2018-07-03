#ifndef CPPPC_CHUNKS_H
#define CPPPC_CHUNKS_H

#include <array>
#include <cstddef>
#include <iterator>
#include <vector>

namespace cpppc {

template <size_t B, class T, class Container>
class chunks
{
  class iterator
  {
  public:
    using value_type        = std::array<T, B / sizeof(T)>;
    using iterator_category = std::random_access_iterator_tag;
    using reference         = value_type &;
    using const_reference   = value_type const &;
    using pointer           = value_type *;
    using difference_type   = std::ptrdiff_t;

    // Construct
    iterator() = delete;
    iterator(size_t index, T * data) : _index(index), _data(data) {}

    // Dereference
    reference operator*() {
      return *reinterpret_cast<value_type *>(_data + (B / sizeof(T)));
    }

    reference operator*() const {
      return *reinterpret_cast<value_type *>(_data + (B / sizeof(T)));
    }

    auto operator[](difference_type i) { return _data[i]; }

    auto operator[](difference_type i) const { return _data[i]; }

    // Increment
    iterator & operator++() {
      _index += B;
      return *this;
    }

    iterator operator++(int) {
      auto tmp = *this;
      _index++;
      return tmp;
    }

    iterator operator--() {
      _index--;
      return *this;
    }

    // Compare
    bool operator==(iterator & rhs) {
      return (this == &rhs || _index == rhs._index);
    }

    bool operator!=(iterator & rhs) { return !(*this == rhs); }

    // Iterators
    auto begin() {
      return reinterpret_cast<value_type *>(_data + (B / sizeof(T)))->begin();
    }

    auto end() {
      return *reinterpret_cast<value_type *>(_data + (B / sizeof(T)))->end();
    }

    auto data() { return _data; }

  private:
    T *    _data;
    size_t _index;
  };

public:
  // Constructors
  chunks() = delete;
  chunks(Container & c) : _container(c) {}

  // Iterators
  iterator begin() { return iterator(0, _container.data()); }
  iterator end() { return iterator(size(), _container.data()); }

  size_t size() { return _container.size(); }

  auto operator[](size_t index) { return iterator(index, _container.data()); }

  auto operator[](size_t index) const {
    return iterator(index, _container.data());
  }

private:
  Container & _container;
  std::size_t _chunksize = B;
};

}  // namespace cpppc

#endif
