namespace cpppc {

// Iterate over chunks
template <size_t B, class T> class chunks_iterator {

  using self_t = chunks_iterator;

public:
  // Construct
  chunks_iterator(T *data) : _data{data} {}

  // Dereference
  auto operator*() {}

  // Increment
  self_t &operator++() {
    _data++;
    blocksize -= sizeof(T);
    return this;
  }
  self_t operator++(int) {}


private:
  T *_data;
  size_t blocksize;
};

template <size_t B, class T, class Container> class chunks {

  using iterator = chunks_iterator;

public:
  // Constructors
  chunks() = delete;
  chunks(Container c) : _container(c) {}
  chunks(const chunks &other) = default;
  chunks(const chunks &&other) = default;

  // Iterators
  auto begin() { return _container.begin(); }
  auto end() { return _container.end(); }

private:
  Container _container;
}

} // namespace cpppc
