#include <bits/stdc++.h>

using namespace std;

#define ld long double
#define ll long long
#define pb push_back
#define fcout cout << fixed << setprecision(27)
#define _hash (1e9 + 9)
#define _for(name, start, end) for (int name = start; name < end; name++)

#define DESYNC_IO_STREAMS  \
  ios::sync_with_stdio(0); \
  cin.tie(0);              \
  cout.tie(0);
#define OVERRIDE_INPUT(filename) freopen(filename, "r", stdin);
#define OVERRIDE_OUTPUT(filename) freopen(filename, "w", stdout);

#define SOLVE_TESTS(read_count) \
  if (read_count)               \
  {                             \
    int _t;                     \
    cin >> _t;                  \
    _for(_i, 0, _t)             \
        solve();                \
  }                             \
  else                          \
  {                             \
    solve();                    \
  }

void solve();

int main()
{
  DESYNC_IO_STREAMS;
  // OVERRIDE_INPUT("input.txt");
  // OVERRIDE_OUTPUT("output.txt");

  SOLVE_TESTS(false);
  return 0;
}

// ------------------------------------------------------------

void solve()
{
  cout << "Hello solve!" << endl;
}