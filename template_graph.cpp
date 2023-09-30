#include <bits/stdc++.h>
using namespace std;

/* -------------- GRAPH -------------- */

struct Graph {
  struct Node {
    vector<int> edges;
  };

  vector<Node> nodes;

  inline void init(int reserveSize)
  {
    nodes.reserve(reserveSize);
    nodes.resize(0);
  }

  inline int add_node(const Node& n = {})
  {
    const int nodeIdx = nodes.size();
    nodes.push_back(n);
    return nodeIdx;
  }

  inline void set_nodes(int count, const Node& n = {})
  {
    nodes.resize(count);
    fill(nodes.begin(), nodes.end(), n);
  }

  inline void add_edge(int nodeIdx1, int nodeIdx2)
  {
    nodes[nodeIdx1].edges.push_back(nodeIdx2);
    nodes[nodeIdx2].edges.push_back(nodeIdx1);
  }
};

/* -------------- ----- -------------- */

/* -------------- GRAPH ERASABLE -------------- */

struct GraphErasable {
  struct Node
  {
    set<int> edges;
  };

  map<int, Node> nodes;

  inline void init()
  {
    nodes.clear();
  }

  inline int add_node(const Node& n)
  {
    const int nodeIdx = nodes.size();
    nodes[nodeIdx] = {};
    return nodeIdx;
  }

  inline void add_edge(int nodeIdx1, int nodeIdx2)
  {
    nodes[nodeIdx1].edges.insert(nodeIdx2);
    nodes[nodeIdx2].edges.insert(nodeIdx1);
  }

  inline void erase_node(int nodeIdx)
  {
    for (int otherNodeIdx : nodes[nodeIdx].edges)
      nodes[otherNodeIdx].edges.erase(nodeIdx);
    nodes.erase(nodeIdx);
  }

  inline void erase_edge(int nodeIdx1, int nodeIdx2)
  {
    nodes[nodeIdx1].edges.erase(nodeIdx2);
    nodes[nodeIdx2].edges.erase(nodeIdx1);
  }
};

/* -------------- ----- -------- -------------- */

/* -------------- GRAPH DFS -------------- */

template<typename EdgesIterator>
struct GraphDfsCache {
  vector<bool> visited;
  vector<int> stack;
  vector<EdgesIterator> edgesIterators;
};

template<typename Graph, typename Visitor, typename DfsCache>
inline void graph_dfs(const Graph& graph, DfsCache& cache, int startNodeIdx, Visitor visitor)
{
  cache.visited.resize(graph.nodes.size());
  fill(cache.visited.begin(), cache.visited.end(), false);
  cache.stack.clear();
  cache.edgesIterators.resize(graph.nodes.size());
  for (int i = 0; i < graph.nodes.size(); i++)
    cache.edgesIterators[i] = graph.nodes[i].edges.cbegin();

  cache.stack.push_back(startNodeIdx);
  cache.visited[startNodeIdx] = true;
  if (visitor(-1, startNodeIdx))
    return;
  while (cache.stack.size())
  {
    int curNodeIdx = cache.stack.back();
    while (cache.edgesIterators[curNodeIdx] != graph.nodes[curNodeIdx].edges.cend()) {
      int nextNodeIdx = *(cache.edgesIterators[curNodeIdx]++);
      if (cache.visited[nextNodeIdx]) continue;
      cache.stack.push_back(nextNodeIdx);
      cache.visited[nextNodeIdx] = true;
      if (visitor(curNodeIdx, nextNodeIdx)) return;
      break;
    }
    if (cache.stack.back() == curNodeIdx)
      cache.stack.pop_back();
  }
}

GraphDfsCache<vector<int>::const_iterator> _graphDfsCache = {};
GraphDfsCache<set<int>::const_iterator> _graphErasableDfsCache = {};

template<typename Visitor>
inline void graph_dfs(const Graph& graph, int startNodeIdx, Visitor visitor)
{
  graph_dfs(graph, _graphDfsCache, startNodeIdx, visitor);
}

template<typename Visitor>
inline void graph_dfs(const GraphErasable& graph, int startNodeIdx, Visitor visitor)
{
  graph_dfs(graph, _graphErasableDfsCache, startNodeIdx, visitor);
}

/* -------------- ----- --- -------------- */