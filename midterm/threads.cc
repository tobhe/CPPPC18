#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

int main() {
  int        c    = 0;
  bool       done = false;
  queue<int> goods;
  mutex      mut;

  thread producer([&]() {
    for (int i = 0; i < 500; ++i) {
      lock_guard lock(mut);
      goods.push(i);
      c++;
    }

    done = true;
  });

  thread consumer([&]() {
    while (!done) {
      while (!goods.empty()) {
        lock_guard lock(mut);
        goods.pop();
        c--;
      }
    }
  });

  producer.join();
  consumer.join();
  cout << "Net: " << c << endl;
}
