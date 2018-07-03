#include <cmath>
#include <iostream>

void log10(int num) {
  std::cout << std::log10(num) << '\n';
}

void log10(float num) {
  std::cout << std::log10(sqrt(num)) << '\n';
}
