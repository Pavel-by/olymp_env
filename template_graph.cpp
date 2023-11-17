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

/* -------------- GRAPH ACCUMULATOR --------------*/

template<typename NodeAccumulator, typename EdgeAccumulator, typename Node, typename AddToNode, typename SubFromNode, typename AccumulateToEdge>
void graph_accumulate(const vector<Node>& nodes, vector<NodeAccumulator>& nodesAccumulators, AddToNode addToNode, SubFromNode subFromNode, AccumulateToEdge accumulateToEdge) {
  if (nodesAccumulators.size() != nodes.size()) {
    cout << "INVALID nodesAccumulators SIZE" << endl;
    return;
  }
  vector<map<int, EdgeAccumulator>> edgesAccumulators(nodes.size());

  vector<bool> isInitialized(nodes.size(), false);
  vector<bool> isPreFinished(nodes.size(), false);
  vector<bool> isFinished(nodes.size(), false);

  vector<int> stack;
  vector<bool> isInStack(nodes.size(), false);

#define stack_push(id) { if (!isInStack[id]) { stack.push_back(id); isInStack[id] = true; } }
#define stack_pop() { isInStack[stack.back()] = false; stack.pop_back(); }

  stack_push(0);
  while (stack.size()) {
    int curNodeId = stack.back(); stack_pop();
    const Node& node = nodes[curNodeId];
    if (!isInitialized[curNodeId]) {
      isInitialized[curNodeId] = true;
      for (int edge : nodes[curNodeId].edges)
        if (!isInitialized[edge])
          stack_push(edge);
    }
    if (!isPreFinished[curNodeId] && node.edges.size()-1 == edgesAccumulators[curNodeId].size()) {
      isPreFinished[curNodeId] = true;
      for (int edge : nodes[curNodeId].edges) {
        if (!edgesAccumulators[curNodeId].count(edge)) {
          if (edgesAccumulators[edge].count(curNodeId)) break;
          EdgeAccumulator edgeAccumulator;
          accumulateToEdge(edgeAccumulator, nodes[curNodeId], nodesAccumulators[curNodeId]);
          addToNode(nodesAccumulators[edge], edgeAccumulator);
          edgesAccumulators[edge][curNodeId] = edgeAccumulator;
          stack_push(edge);
          break;
        }
      }
    }
    if (!isFinished[curNodeId] && node.edges.size() == edgesAccumulators[curNodeId].size()) {
      isFinished[curNodeId] = true;
      for (int edge : nodes[curNodeId].edges) {
        if (edgesAccumulators[edge].count(curNodeId)) continue;
        NodeAccumulator nodeAccumulator = nodesAccumulators[curNodeId];
        subFromNode(nodeAccumulator, edgesAccumulators[curNodeId][edge]);
        EdgeAccumulator edgeAccumulator;
        accumulateToEdge(edgeAccumulator, nodes[curNodeId], nodeAccumulator);
        addToNode(nodesAccumulators[edge], edgeAccumulator);
        edgesAccumulators[edge][curNodeId] = edgeAccumulator;
        stack_push(edge);
      }
    }
  }

#undef stack_push
#undef stack_pop
}

/* -------------- ----- ----------- --------------*/

/* ------------- DFS -------------- */

struct DfsSettings
{
  int startNodeIdx;
  bool canVisitParent;
};

vector<int> __dfs_stack;
vector<int> __dfs_visited;

template<typename T, typename NodeVisitor, typename EdgeVisitor>
void dfs(const vector<T> &nodes, NodeVisitor nodeVisitor, EdgeVisitor edgeVisitor, DfsSettings settings)
{
  __dfs_stack.clear();
  __dfs_visited.resize(nodes.size());
  fill(__dfs_visited.begin(), __dfs_visited.end(), 0);
  __dfs_stack.push_back(settings.startNodeIdx);
  while (!__dfs_stack.empty())
  {
    int cur = __dfs_stack.back();
    if (!__dfs_visited[cur])
      nodeVisitor(cur);
    if (__dfs_visited[cur] >= nodes[cur].edges.size())
    {
      __dfs_visited[cur]++;
      __dfs_stack.pop_back();
      continue;
    }
    int prev = __dfs_stack.size() > 1 ? __dfs_stack[__dfs_stack.size() - 2] : -1;
    int edge = nodes[cur].edges[__dfs_visited[cur]++];
    if (settings.canVisitParent || prev != edge)
    {
      edgeVisitor(cur, edge);
      __dfs_stack.push_back(edge);
    }
  }
}

/* ------------- --- -------------- */
