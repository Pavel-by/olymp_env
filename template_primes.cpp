#include <bits/stdc++.h>
using namespace std;

struct Primes {
  vector<int> grid;
  vector<int> primes;

  void init(int n) {
    grid.resize(n);
    primes.resize(0);
    fill(grid.begin(), grid.end(), 0);
    for(int i = 1; i < n; i++) {
      if (!grid[i]) {
        primes.push_back(i + 1);
        for (int j = i + i + 1; j < n; j += i + 1) {
          grid[j] = 1;
        }
      }
    }
  }
};