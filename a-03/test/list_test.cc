
/* ------------------------------------------------------------------------ *
 *                       DO NOT MODIFIY THIS FILE                           *
 * -------------------------------------------------------------------------*/

#include "list_test.h"

#include <gtest/gtest.h>
#include <iostream>
#include <solution/list.h>

namespace cpppc {

TEST_F(ListTest, StandardConcept) {
  LOG_MESSAGE("listTest.StandardConcept: default_constructor");
  list<int, 0> v1{};
  list<int, 0> v2{};

  LOG_MESSAGE("listTest.StandardConcept: operator==");
  ASSERT_EQ(true, v1 == v2);

  v1.push_front(12);
  v1.push_front(34);

  for (auto v = v1.begin(); v == v1.end(); v++) {
    std::cout << *v << std::endl;
  }

  ASSERT_EQ(false, v1 == v2);
  ASSERT_EQ(true, v1 != v2);

  LOG_MESSAGE("listTest.StandardConcept: operator=");
  v2 = v1;

  ASSERT_EQ(true, v1 == v2);
  ASSERT_EQ(false, v1 != v2);

  LOG_MESSAGE("listTest.StandardConcept: copy_constructor");
  list<int, 0> v3(v1);

  ASSERT_EQ(1, v1 == v3);
}

TEST_F(ListTest, ListConcept) {
  LOG_MESSAGE("ListTest.ListConcept: n-defaults constructor");
  list<int, 0> l0{6};
  ASSERT_EQ(true, std::distance(l0.begin(), l0.end()) == 6);

  LOG_MESSAGE("ListTest.ListConcept: n-copies constructor");
  list<int, 0> l1{6, 0};
  ASSERT_EQ(true, l0 == l1);

  LOG_MESSAGE("ListTest.ListConcept: range constructor");
  list<int, 0> l2{l1.begin(), l1.end()};
  ASSERT_EQ(true, std::distance(++l2.begin(), l2.end()) == 5);

  LOG_MESSAGE("ListTest.ListConcept: empty, size");
  list<int, 0> v{};

  ASSERT_EQ(0, v.size());
  ASSERT_EQ(1, v.empty());

  LOG_MESSAGE("ListTest.ListConcept: begin, end");
  ASSERT_EQ(v.begin(), v.end());

  LOG_MESSAGE("ListTest.ListConcept: list_push_front(56)");
  v.push_front(56);
  LOG_MESSAGE("ListTest.ListConcept: list_push_front(78)");
  v.push_front(78);
  LOG_MESSAGE("ListTest.ListConcept: list_push_front(90)");
  v.push_front(90);

  ASSERT_EQ(v.size(), 3);

  LOG_MESSAGE("ListTest.ListConcept: list.front()");
  v.push_front(11);
  ASSERT_EQ(v.front(), 11);
  v.push_front(22);
  ASSERT_EQ(v.front(), 22);
  v.push_front(33);
  ASSERT_EQ(v.front(), 33);
  v.push_front(44);
  ASSERT_EQ(v.front(), 44);

  LOG_MESSAGE("ListTest.ListConcept: list_pop_front");
  v.pop_front();
  ASSERT_EQ(v.front(), 33);
  LOG_MESSAGE("ListTest.ListConcept: list_pop_front");
  v.pop_front();
  ASSERT_EQ(v.front(), 22);
  LOG_MESSAGE("ListTest.ListConcept: list_pop_front");
  v.pop_front();
  ASSERT_EQ(v.front(), 11);

  LOG_MESSAGE("ListTest.ListConcept: list__copy");
  auto vcopy = list<int, 0>(v);

  LOG_MESSAGE("ListTest.ListConcept: list__begin, list__end");
  ASSERT_EQ(true, v == vcopy);

  LOG_MESSAGE("ListTest.ListConcept: list__assign(v_empty)");
  list<int, 0> vempty{};
  v = vempty;

  ASSERT_EQ(1, v == vempty);
  ASSERT_EQ(0, v.size());
  ASSERT_EQ(1, v.empty());
}

TEST_F(ListTest, MoveSemantics) {

  list<int, 0> l0{6};
  l0.push_front(56);
  l0.push_front(46);
  l0.push_front(36);

  LOG_MESSAGE("ListTest.ListConcept: Move constructor");
  list<int, 0> l1{std::move(l0)};

  ASSERT_EQ(36, l1.front());
  l1.pop_front();
  ASSERT_EQ(46, l1.front());
  l1.pop_front();
  ASSERT_EQ(56, l1.front());
  l1.pop_front();

  LOG_MESSAGE("ListTest.ListConcept: Move assignment");
  list<int, 0> l3{6};
  l1.push_front(56);
  l1.push_front(46);
  l1.push_front(36);

  l3 = std::move(l1);

  ASSERT_EQ(36, l3.front());
  l3.pop_front();
  ASSERT_EQ(46, l3.front());
  l3.pop_front();
  ASSERT_EQ(56, l3.front());
  l3.pop_front();
}
} // namespace cpppc
