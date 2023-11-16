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

/* -------------- BINARY TREE ------------ */

template <typename Item, typename Accumulate>
void btree_init(const vector<Item> &data, vector<vector<Item>> &cache, Accumulate accumulate)
{
  if (data.size() <= 1)
    return;

  while (cache.empty() || cache.back().size() > 1)
  {
    cache.push_back({});
    vector<Item> &cur = cache[cache.size() - 1];
    const vector<Item> &prev = cache.size() >= 2 ? cache[cache.size() - 2] : data;
    cur.resize((prev.size() - 1) / 2 + 1);
    for (int i = 0; i < prev.size(); i += 2)
      if (i < prev.size() - 1)
        accumulate(prev[i], prev[i + 1], cur[i / 2]);
      else
        cur[i / 2] = prev[i];
  }
}

template <typename Item, typename Accumulate, typename Check>
int btree_find_idx(const vector<Item> &data, const vector<vector<Item>> &cache, const Item &emptyItem, Accumulate accumulate, Check check)
{
  Item left = emptyItem, right;
  int idx = 0;
  for (int i = cache.size() - 1; i >= 0; i--)
  {
    accumulate(left, cache[i][idx], right);
    if (check(right))
      idx = idx * 2;
    else
    {
      if (idx + 1 == cache[i].size())
      {
        cout << "BTREE: INVALID CHECK\n";
        while (true){}
      }
      left = right;
      idx = (idx + 1) * 2;
    }
  }

  accumulate(left, data[idx], right);
  return check(right) ? idx : idx + 1;
}

template <typename Item, typename Accumulate>
void btree_recalculate_idx(const vector<Item> &data, vector<vector<Item>> &cache, Accumulate accumulate, int idx)
{
  for (int i=0; i<cache.size(); i++)
  {
    const vector<Item> &cur = i == 0 ? data : cache[i - 1];
    vector<Item> &next = cache[i];
    idx /= 2;
    if (idx * 2 + 1 < cur.size())
      accumulate(cur[idx * 2], cur[idx * 2 + 1], next[idx]);
    else
      next[idx] = cur[idx * 2];
  }
}

/* -------------- ------ ---- ------------ */

void example_binary_tree() {
  int n; n = 100;
  vector<int> data(n,1);

  auto accumulate = [](const int &a, const int &b, int &out) {
    out = a + b;
  };
  auto makeChecker = [](int lookFor) {
    return [lookFor](int right) {
      return right >= lookFor;
    };
  };
  vector<vector<int>> cache;
  btree_init(data, cache, accumulate);

  // нашли индекс элемента idx такой, что `data[0] + data[1] + ... + data[idx] == 5`
  int idx = btree_find_idx(data, cache, 0, accumulate, makeChecker(5));
  cout << idx << endl; // idx == 4

  data[idx] = 0;
  btree_recalculate_idx(data, cache, accumulate, idx);

  idx = btree_find_idx(data, cache, 0, accumulate, makeChecker(5));
  cout << idx << endl; // idx == 5
}