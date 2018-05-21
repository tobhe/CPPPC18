#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <iterator>
#include <set>
#include <unordered_map>

template <class Iter>
inline Iter histogram(Iter first, Iter last) {
  typedef typename std::iterator_traits<Iter>::value_type value_t;
  typedef typename std::iterator_traits<Iter>::difference_type index_t __attribute__ ((used));

  if (first == last ) {
    return first;
  }

  std::unordered_map<value_t, size_t> map;

  auto new_end = std::remove_if(first, last, [&map, first, last](value_t &in) {
      if (map.find(in) == map.end()) {
        map.insert({in, std::count(first, last, in)});
        return false;
      }
      return true;
  });

  std::for_each(first, new_end, [&map](value_t &in){ in = map[in]; });
  return new_end;
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
