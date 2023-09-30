#include <bits/stdc++.h>
using namespace std;

/* --------------- BSEARCH --------------- */

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

/* --------------- ------- --------------- */