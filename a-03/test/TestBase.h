#ifndef CPPPC__TEST__TEST_BASE_H_
#define CPPPC__TEST__TEST_BASE_H_

#include <gtest/gtest.h>


namespace testing {
namespace internal {

enum GTestColor {
    COLOR_DEFAULT,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW
};

extern void ColoredPrintf(
  GTestColor color,
  const char* fmt,
  ...);

} // namespace internal
} // namespace testing

#define LOG_MESSAGE(...) do { \
  char buffer[300]; \
  const char * filepath = __FILE__; \
  const char * filebase = strrchr(filepath, '/'); \
  const char * filename = (filebase != 0) ? filebase + 1 : filepath; \
  sprintf(buffer, __VA_ARGS__); \
  testing::internal::ColoredPrintf( \
    testing::internal::COLOR_YELLOW, \
    "[=   LOG  =] %*s :%*d | %s \n", \
    24, filename, 4, __LINE__, buffer); \
} while(0)

#endif // CPPPC__TEST__TEST_BASE_H_
