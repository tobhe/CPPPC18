#include <iostream>

class SemanticSurprise {
public:
  SemanticSurprise(int value) : _value(value) {}

  SemanticSurprise(const SemanticSurprise &other) : _value(other._value) {}

  bool operator==(const SemanticSurprise &other) const {
    return _value == other._value;
  }

  bool operator!=(const SemanticSurprise &other) const {
    return !(_value == other._value);
  }

  int value() { return _value; }

private:
  int _value;
};

int main() {
  SemanticSurprise s2(4);          // <-- Op?
  std::cout << s2.value() << '\n'; // <-- value?

  SemanticSurprise s3 = s2;        // <-- Op?
  std::cout << s3.value() << '\n'; // <-- value?

  SemanticSurprise s4(s3); // <-- Op?
  if (s4 == s3) {
    std::cout << "Equal: True" << '\n';
  } else {
    std::cout << "Equal: False" << '\n';
  }
  if (s2 != s3) {
    std::cout << "Not equal: True" << '\n';
  } else {
    std::cout << "Not equal: False" << '\n';
  }

  return 0;
}
