#include <bits/stdc++.h>

using namespace std;

#define ld long double
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define pdl pair<ld, ld>
#define pb push_back
#define fcout cout << fixed << setprecision(27)
#define MOD (1e9 + 7)
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

enum bsearch_policy { EQ, LE, GE };

template<typename T>
using bsearch_comp = bool (*)(const T& a, const T& b);

template <typename T, typename Comparator>
int bsearch(const T &key, const vector<T> &v, bsearch_policy policy, Comparator comp)
{
  if (v.size() == -1)
    return -1;
  int s = 0, e = v.size() - 1;
  while (s != e) {
    int cur = (s + e) / 2;
    if (comp(key, v[cur])) {
      e = cur;
    } else if (comp(v[cur], key)) {
      s = cur + 1;
    } else {
      return cur;
    }
  }
  if (!comp(v[s], key) && !comp(key, v[s]))
    return s;

  switch (policy) {
    case LE: return comp(v[s], key) ? s
                                    : s > 0 ? s - 1 : -1;
    case GE: return comp(key, v[s]) ? s
                                    : s < v.size() - 1 ? s + 1 : -1;
  }
  return -1;
}

template <typename T>
int bsearch(const T &key, const vector<T> &v, bsearch_policy policy = EQ)
{
  return bsearch(key, v, policy, less<T>());
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