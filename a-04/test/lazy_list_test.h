#ifndef CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED
#define CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED

#include <gtest/gtest.h>
#include "TestBase.h"

class LazyListTest : public ::testing::Test {

public:

  LazyListTest() {
    LOG_MESSAGE("Opening test suite: lazylistTest");
  }

  virtual ~LazyListTest() {
    LOG_MESSAGE("Closing test suite: lazylistTest");
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

};

#endif // CPPPC__A03__SPARSE_ARRAY_TEST_H__INCLUDED
