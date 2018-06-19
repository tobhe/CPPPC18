## 7-2 Act Like You Got a Pair

- How do comparison operators of pair<A,B> depend on types A and B?

decltype(lhs.first) must be decltype(rhs.first) and decltype(rhs.first) must be decltype(rhs.first)

- How can we specify comparison of pair<A0,B0> and pair<A1,B1>?

specify comparison between As and Bs

- What is the benefit of std::get over pair.first / pair.second
(use compiler explorer)

Not sure how compiler explorer could help me here: https://godbolt.org/g/gb1tsg gives the same result.
One advantage for sure is the overload by type.

- Why don’t we just always use std::get?

No idea, i guess i'm missing the real answer to the above question

## 7-3-1 Algorithm Categories

- Non modifying can change the value of elements but never changes the structure of a container or introduces copies,
  partition and sort do not change the structure of the data in a container -> not modifying

- Are there algorithms that return their result as a new sequence? Why? Discuss a minimal use-case to illustrate this.

yes, std::transform does. One reason is the overload for two ranges:

```
vector<int> numbers1 = {1, 5, 42, 7, 8};
vector<int> numbers2 = {10, 7, 4, 2, 2};
vector<int> results;
std::transform(numbers1.begin(), numbers1.end(),
               numbers2.begin(),
               std::back_inserter(results),
               [](int i, int j) {return i+j;});
```

there is no obvious solution to where the results should be saved -> better make copy

## 7-3-2 Iterator Invalidation

- Which algorithms allow to add or remove elements from their input ranges?

Modifying ones

- Explain how std::list, std::deque, std::vector and std::map differ in iterator invalidation rules.

std::vector does not invalidate iterators, std::list invalidates iterators of deleted elements, surrounding elements are fine,
deque invalidates all the iterators and references to elements of the deque on insert in the middle.
