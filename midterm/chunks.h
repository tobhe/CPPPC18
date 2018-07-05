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
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type *;
    using reference         = value_type &;

    iterator() = delete;
    iterator(T * data, difference_type offset)
     : _data(data), _offset(offset / (B / sizeof(T))) {}

    auto & operator++() {
      ++_offset;
      return *this;
    }

    auto & operator--() {
      --_offset;
      return *this;
    }

    auto operator-(iterator & rhs) { return _offset - rhs._offset; }

    reference operator[](difference_type index) {
      return nonstd::span<T>(_data + (_offset * (B / sizeof(T))), B)[index];
    }

    auto operator*() { return nonstd::span<T>(_data + _offset, B); }

    bool operator==(iterator & rhs) const {
      return (this == &rhs || _offset == rhs._offset);
    }

    bool operator!=(iterator & rhs) const { return !(*this == rhs); }

  private:
    T *             _data;
    difference_type _offset;
  };

  using difference_type = std::ptrdiff_t;

  // Constructors
  chunks() = delete;
  chunks(Container & c) : _c(c) {}

  // Iterators
  auto begin() { return iterator(_c.data(), 0); }
  auto end() { return iterator(_c.data(), size()); }

  size_t size() const { return _c.size(); }

  auto operator[](difference_type index) {
    return nonstd::span<T>(_c.data() + (index * B), B);
  }

private:
  Container & _c;
  size_t      _size;
};

}  // namespace cpppc

#endif
