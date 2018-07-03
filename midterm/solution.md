# 1. Types, Classes, Objects and their State

## 1.1 Object Definition

Assuming you are confronted with a class that supports the following use case:

```cpp
DateParser date_parser;
date_parser.set_date(today);

auto day = date_parser.day_of_week();
```

What is your objection to this? How would you change the interface of class DateParser?

#### Answer:
Setting the date as member variable does not make sense to me as it is no state that 
should be held by the parser. A better solution would be:


```cpp
DateParser date_parser;

auto day = date_parser.day_of_week(today);
```

If the output format is not assumed to change to often it might make sense saving
it in the parser object:


```cpp
DateParser date_parser;
date_parser.set_format(date_parser_format::day_of_week);

auto day = date_parser.parse(today);
```

## 1.2 Standard Object Semantics


- Are there compiler errors? If so: why?

- Name the method/operation on SemanticSurprise in every line marked with Op?, including those that lead to compiler errors.

- Which values are returned in the lines marked with value? (given the line does not lead to a compiler error). Explain why these values are returned.

- How can this implementation be simplified? What is the requirement for this simplification?


```cpp
SemanticSurprise s1;          // Compiler error, no default constructor
s1.value();                   // Does not exist

SemanticSurprise s2(4);       // <- SemanticSurprise(int)
s2.value();                   // <-- 4, because it was initialized to 4

SemanticSurprise s3 = s2;     // <-- SemanticSurprise(SemanticSurprise const&)
s3.value();                   // <-- 4, because it is a copy of s2

SemanticSurprise s4(s3);      // <-- SemanticSurprise(SemanticSurprise const&)
s4 == s3;                     // <-- True, because it is a copy of s3
s2 != s3;                     // Compiler error: not defined
```

Given the implementation of SemanticSurprise above, the following use case leads to a compiler error:

```cpp
void print_surprise(const SemanticSurprise & s) {
  std::cout << "SemanticSurprise.value: " << s.value() << std::endl;
}

print_surprise(SemanticSurprise(10));
```

- Explain the compiler error and how the implementation of SemanticSurprise has to be corrected.

#### Answer:

For this to work value() must be const.

## 1.3 Resource Ownership

Consider the following use case:

```cpp
// ...
if (condition) {
        LogFileReader log_reader("performance.log");
        if (log_reader.lines().size() > 1024) { return; }
}
// ...
```
- Judging from its usage illustrated above: which rule must be satisfied in the 
implementation of class LogFileReader (or one of its members)?

**Answer:** LogFileReader must open a filedescriptor on construction to be able to get the number of lines

- Name a popular technique in resource management that depends on this rule, and briefly 
explain its principle.

**Answer:** RAII (Resource acquisition is initialization), the object holds the resource, in this case the file descriptor from initialization until the end of it's lifetime

# 2. Iterators

## 2.1 Algorithm Basics

The following algorithm dereferences and returns a given iterator’s successor unless the successor’s referenced value matches some condition. The algorithm is semantically correct but does not compile for iterators of some containers.

- Which containers? Briefly explain why the algorithm does not work for these and how it has to be changed.

```cpp
template <typename Iterator, typename Value = typename Iterator::value_type>
Value next_value_or_default(Iterator it, Iterator end, Value default) {
  if (it == end || it+1 == end) { return default; }
  return it[1];
}
```

**Answer:** Only works for random access iterators and consequently for containers with 
random access iterators, better:

```cpp
template <typename Iterator, typename Value = typename Iterator::value_type>
Value next_value_or_default(Iterator it, Iterator end, Value default) {
  if (it == end || ++it == end) { return default; }
  return *it;
}
```

## 2.2 Container Wrapper

The STL’s `std::vector` guarantess that its elements are stored in a contiguous memory region and is therefore compatible to C-style arrays. The member function `.data()` returns a pointer to the vector’s underlying raw memory.

For many hardware-tuning techniques, data is accessed in chunks. Assuming a `std::vector<uint32_t>` and 64 bytes per cache line, for example, vector elements could be loaded in chunks of 64/(32/8) = 16 elements.

- Write a container wrapper
```
cpppc::chunks<B, T, Container>
```
that provides a sequential container interface on elements in Container in chunks of maximum size B bytes.

The template signature is derived from `std::stack`, a similar wrapper type defined in the STL:

http://en.cppreference.com/w/cpp/container/stack

You only need to implement a minimal interface like constructors and begin(), end(), however.

Example use case:

```cpp
std::vector<uint16_t> v_us;

//                                    ,-- wrapped container
//                                    |
cpppc::chunks<128, uint16t_t, std::vector<uint16_t>> v_chunks(v_us);
//             |      |
//             |      '-- element type
//             |
//             '-- maximum size of a
//                 single chunk in bytes

// Iterate chunks:
auto first_chunk = v_chunks.begin();
auto chunk_size  = std::distance(v_chunks.begin(), v_chunks.end());
                   // --> 128/(16/8) = 64

// Iterators on elements in a chunk:
uint16_t first_chunk_elem = *first_chunk.begin();
uint16_t third_chunk_elem = first_chunk[2];

// Pointer to data in second chunk:
uint16_t chunk_1_data = v_chunks[1].data();
// Pointer to data in third chunk (= end pointer of data in second chunk):
uint16_t chunk_2_data = v_chunks[2].data();
```

Note that you need two iterator types:
- `cpppc::chunks<...>::iterator` for iterating chunks; it references `cpppc::chunks<...>::value_type` (= type of single chunks)
- and another iterator type to access chunk elements.

It might be best if you use existing STL containers like `std::vector<T>` or `std::array<T, ChunkSize>**` as chunk type: these would already provide the sequence container interface to chunk elements you need.

**Note**

The `cpppc::chunks` container adapter can (and should) be implemented as a view, that is: without copying elements of the underlying vector.

# 4. Thread-Safety

## 4.1 Parallelism and STL Containers

Given the following operations on an instance of `std::vector`, consider operations in the same table row to be executed by multiple threads in parallel:

```
// Shared vector instance accessed by thread A and thread B:
std::vector<int> v;

// thread A:                    | thread B:
// =============================|==============================
   std::vector<int> a;          | std::vector<int> b;           
//  
// Two vectors are constructed
// Different containers -> can be called concurrently
// -----------------------------|------------------------------
   int xa = v[3];               | int xb = v[4];
//
// Two elements of v are assigned to different variables:
// Read only and different elements -> can be called concurrently
// -----------------------------|------------------------------
   v[3] = 123;                  | v[4] = 345;
// two elements of the same vector are written to at the same time
// Different elements in the same container can be modified concurrently by different threads
// -----------------------------|------------------------------
   v[3] = 123;                  | int xb = v[3];
// The same element is read and written to by different threads
// No guarantees -> don't do this
// -----------------------------|------------------------------
   v.push_back(24);             | v.size();
// Concurrent read and write access
// same as above
// -----------------------------|------------------------------
   v.back();                    | v.push_back(54);
// Concurrent read of last element and insertion of last element
// no guarantee which element is read with back()
// -----------------------------|------------------------------
   v.begin();                   | v.push_back(34);
// Construct iterator to first element and push element to back
// Container operations that invalidate any iterators modify the 
// container and cannot be executed concurrently with any operations 
// on existing iterators even if those iterators are not invalidated.
// -----------------------------|------------------------------
   v.back();                    | v.pop_back();
// -----------------------------|------------------------------
// Concurrent read of last element and deletion of last element
// no guarantee which element is read with back()
```
