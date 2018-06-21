#include <celero/Celero.h>

class BaseBlub
{
public:
  virtual int get_val_minus_ten() { return lol - 10; }
  int         lol = 99;
};

class Blub : public BaseBlub
{
public:
  virtual int get_val_minus_ten() { return lol - 20; }
};

template <class DerivedT>
class BaseBlubCRTP
{
public:
  int get_val_minus_ten() { return lol - 10; };
  int lol = 99;
};

class BlubCRTP : public BaseBlubCRTP<BlubCRTP>
{
public:
  int get_val_minus_ten() { return lol - 20; };
};


CELERO_MAIN

BASELINE(Base, Baseline, 10, 1000000) {
  BaseBlub b{};
  celero::DoNotOptimizeAway(b.get_val_minus_ten());
}

BASELINE(Virtual, Baseline, 10, 1000000) {
  Blub b{};
  celero::DoNotOptimizeAway(b.get_val_minus_ten());
}

BASELINE(CRTP, Baseline, 10, 1000000) {
  BlubCRTP b{};
  celero::DoNotOptimizeAway(b.get_val_minus_ten());
}
