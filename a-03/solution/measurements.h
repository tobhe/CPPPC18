#ifndef CPPPC__A03__MEASUREMENTS_H__INCLUDED
#define CPPPC__A03__MEASUREMENTS_H__INCLUDED

#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace cpppc {

template <typename T> class Measurements {

  typedef Measurements<T> self_t;
  typedef T value_t;

  typedef T &reference;
  typedef const T &const_reference;
  using size_type = typename std::vector<T>::size_type;
  typedef typename std::vector<T>::iterator iterator;
  typedef typename std::vector<T>::const_iterator const_iterator;

public:
  // Sequence Container

  // Iterators
  inline iterator begin() { return _values.begin(); }
  inline iterator end() { return _values.end(); }
  inline const_iterator begin() const { return _values.begin(); }
  inline const_iterator end() const { return _values.end(); }

  // Comparison
  bool operator==(const self_t &rhs) const { return (_values == rhs._values); }
  bool operator!=(const self_t &rhs) const { return !(_values == rhs._values); }

  // Modifiers
  iterator insert(const T &value) {
    _values.push_back(value);
    return --_values.end();
  }

  template <class InputIt> iterator insert(InputIt first, InputIt second) {
    return _values.insert(end(), first, second);
  }

  template <class first_t, class second_t>
  iterator insert(first_t first, second_t second) {
    return _values.insert(first, second);
  }
  void clear() { _values.clear(); }

  // Element access
  inline reference front() { return _values.front(); }
  inline reference back() { return _values.back(); }
  inline const_reference back() const { return _values.back(); }
  inline const_reference front() const { return _values.front(); }
  inline reference operator[](size_type pos) { return _values[pos]; }
  inline reference at(size_type pos) { return _values[pos]; }

  // Capacity
  inline size_type size() const { return _values.size(); }
  inline bool empty() const { return _values.empty(); }

  // MeasurementsConcept
  value_t median() const {
    if (size() == 0) {
      return 0;
    }
    size_t n = size() / 2;
    auto cpy = _values;
    std::nth_element(cpy.begin(), cpy.begin() + n, cpy.end());
    return cpy[n];
  }
  double mean() const {
    return size() == 0 ? 0 : std::accumulate(begin(), end(), 0.0) / size();
  }
  double variance() const {
    if (size() == 0) {
      return 0;
    }
    // Copy values to double vector
    std::vector<double> cpy(begin(), end());
    double m = mean();
    std::for_each(cpy.begin(), cpy.end(),
                  [m](double &val) { val = std::pow(val - m, 2.0); });
    return std::accumulate(cpy.begin(), cpy.end(), 0.0) / size();
  }
  double sigma() { return std::sqrt(variance()); }

public:
private:
  std::vector<T> _values;
};

} // namespace cpppc

#endif // CPPPC__A03__MEASUREMENTS_H__INCLUDED
