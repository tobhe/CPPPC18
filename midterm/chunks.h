#ifndef CPPPC_CHUNKS_H
#define CPPPC_CHUNKS_H

#include <array>
#include <cstddef>
#include <iterator>
#include <vector>
#include "span.h"

namespace cpppc {

template <size_t B, class T, class Container>
class chunks
{
public:
  class iterator
  {
  public:
    using iterator_tag    = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;

    iterator() = delete;
    iterator(T * data, difference_type offset) : _data(data), _offset(offset) {}

    auto & operator++() {
      _offset += B / sizeof(T);
      return *this;
    }

    auto & operator--() {
      _offset -= B / sizeof(T);
      return *this;
    }

    auto operator[](difference_type index) {
      return nonstd::span<T>(_data + _offset, B)[index];
    }

    auto operator*() { return nonstd::span<T>(_data + _offset, B); }

  private:
    T * _data;
    difference_type _offset;
  };

  using difference_type = std::ptrdiff_t;

  // Constructors
  chunks() = delete;
  chunks(Container & c) : _data(c.data()), _size(c.size()) {}

  // Iterators
  auto begin() { return iterator(_data, 0); }
  auto end() { return iterator(_data, size()); }

  auto & first() { return *begin(); }

  size_t size() { return _size; }

  auto operator[](difference_type index) {
    return nonstd::span<T>(_data + (index * B), B);
  }

private:
  T *    _data;
  size_t _size;
};

}  // namespace cpppc

#endif
