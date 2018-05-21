#include "lazy_list_test.h"
#include <solution/lazy_sequence.h>
#include <gtest/gtest.h>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>

using namespace cpppc;


TEST_F(LazyListTest, StandardConcept)
{
  LOG_MESSAGE("LazyListTest.StandardConcept: ctor");
  lazy_sequence<int> sa1{10, [](int i){return 2*i;}};
  lazy_sequence<int> sa2{10, [](int i){return 3*i;}};

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
