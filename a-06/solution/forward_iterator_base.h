#ifndef CPPPC__S06__FORWARD_ITERATOR_BASE_H__INCLUDED
#define CPPPC__S06__FORWARD_ITERATIR_BASE_H__INCLUDED

#include <iterator>

namespace cpppc {

template <class IteratorType> class ForwardIteratorBase {

  using self_t = ForwardIteratorBase<IteratorType>;
  using derived_t = IteratorType;

private:
  derived_t &derived() { return static_cast<IteratorType &>(*this); }
  constexpr const derived_t &derived() const {
    return static_cast<const derived_t &>(*this);
  }

public:
  constexpr ForwardIteratorBase() = default;
  constexpr ForwardIteratorBase(self_t &&) = default;
  constexpr ForwardIteratorBase(const self_t &) = default;
  ~ForwardIteratorBase() = default;
  
  constexpr auto operator*() { return derived().dereference(); }

  constexpr auto operator*() const { return derived().dereference(); }

  constexpr auto operator-> () const { return derived().dereference(); }

  derived_t &operator++() {
    derived().increment(1);
    return derived();
  }

  derived_t operator++(int) {
    auto old = derived();
    derived().increment(1);
    return old;
  }

};

} // namespace cpppc

#endif
