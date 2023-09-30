#include <bits/stdc++.h>
using namespace std;

/* -------------- BITS -------------- */

template<typename T>
struct bit_counter {
  static const int BIT_COUNT = sizeof(T) * 8;

  int counts[sizeof(T) * 8];

  void reset()
  {
    memset(counts, 0, sizeof(counts));
  }

  void add(T value)
  {
    for (int i = 0; i < sizeof(T) * 8; i++)
      counts[i] += (value >> i) & 1;
  }

  int operator[](int idx) const {
    return counts[idx];
  }
};

/* -------------- ---- -------------- */

int main() {
  bit_counter<int> counter = {};
  counter.add(19);
  for (int i = 0; i < bit_counter<int>::BIT_COUNT; i++) {
    cout << counter[i] << " ";
  }
}
