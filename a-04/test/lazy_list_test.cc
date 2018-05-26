#include "lazy_list_test.h"
#include <gtest/gtest.h>
#include <solution/lazy_sequence.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>

using namespace cpppc;

TEST_F(LazyListTest, StandardConcept) {
  LOG_MESSAGE("LazyListTest.StandardConcept: ctor");
  lazy_sequence<int> sa1{10, [](int i) { return 2 * i; }};
  lazy_sequence<int> sa2{10, [](int i) { return 3 * i; }};

  LOG_MESSAGE("LazyListTest.StandardConcept: ==");
  ASSERT_EQ(false, sa1 == sa2);

  ASSERT_EQ(10, sa1.size());
  ASSERT_EQ(10, sa2.size());

  ASSERT_EQ(4, sa1[2]);
  ASSERT_EQ(6, sa2[2]);

  ASSERT_EQ(0, *sa1.begin());
  ASSERT_EQ(0, *sa2.begin());

  ASSERT_EQ(2, *(++sa1.begin()));
}

TEST_F(LazyListTest, SequenceConcept) {
  lazy_sequence<int> sa1{10, [](int i) { return 2 * i; }};

  LOG_MESSAGE("LazyListTest.SequenceConcept: begin()");
  ASSERT_EQ(0, *sa1.begin());

  LOG_MESSAGE("LazyListTest.SequenceConcept: end()");
  ASSERT_EQ(18, *(sa1.end() - 1));

  LOG_MESSAGE("LazyListTest.SequenceConcept: ()");
  ASSERT_EQ(10, sa1.size());

  LOG_MESSAGE("LazyListTest.SequenceConcept: s[i]");
  ASSERT_EQ(0, sa1[0]);
  ASSERT_EQ(2, sa1[1]);
  ASSERT_EQ(4, sa1[2]);
  ASSERT_EQ(6, sa1[3]);
  ASSERT_EQ(8, sa1[4]);

  int count = 0;
  for (auto i : sa1) {
    ASSERT_EQ(i, 2*count);
    ++count;
  }
}
