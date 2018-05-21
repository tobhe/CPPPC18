namespace cpppc
{

namespace detail {
    template<class LazySequence>
    class lazy_sequence_iterator
    {
      using self_t = lazy_sequence_iterator<LazySequence>;

    public:
      using iterator_category = std::random_access_iterator_tag;
      using value_type = typename LazySequence::value_type;
      using pointer = value_type*;
      using reference = value_type&;
      using difference_type = typename LazySequence::size_type;

    public:
      lazy_sequence_iterator(LazySequence &seq, difference_type index) : _seq(seq), _index(index) {}

    private:
      LazySequence& _seq;
      difference_type _index;
    };
} // namespace detail

template <class T>
class lazy_sequence
{
  using self_t = lazy_sequence<T>;
public:
  using size_type = size_t;
  using value_type = T;

public:
  // Constructors
  lazy_sequence(size_type size, std::function<value_type(value_type)> fun) : _size(size), _fun(fun) {}

  // Iterators

  // iterator begin()
  // {
  // }

  // const_iterator end()
  // {

  // }

  // Capacity
  size_type size()
  {
    return _size;
  }

  bool empty()
  {
    return _size == 0;
  }

  // Comparison
  bool operator==(const self_t &rhs) 
  {
    return (_fun == rhs.fun && _size == rhs._size);
  }

  bool operator!=(const self_t &rhs)
  {
    return !(*this == rhs);
  }


private:
  size_type _size;
  std::function<int(int)> _fun;
};
}
