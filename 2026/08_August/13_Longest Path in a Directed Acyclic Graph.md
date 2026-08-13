# 🟥 Longest Path in a Directed Acyclic Graph

<div align="center">
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/longest-path-in-a-directed-acyclic-graph/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-46.7%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](#)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a weighted **Directed Acyclic Graph (DAG)** with `V` vertices numbered from `0` to `V - 1`, represented by `edges[][]`, where `edges[i] = [u, v, w]` denotes a directed edge from `u` to `v` with weight `w`, and a source vertex `src`.

Return the distance array, where the value at index `i` represents the **longest distance** from `src` to vertex `i`. 
If a vertex is unreachable from `src`, store `INT_MIN` for that vertex. The driver code will automatically display `INT_MIN` as `INF`.

---

## 💡 Examples

### Example 1
```text
Input: V = 4, src = 0, edges[][] = [[0, 1, 1], [0, 2, 1], [1, 2, 5], [3, 1, 2], [3, 2, -1]]
Output: [0, 1, 6, INF]
Explanation: The longest distance of vertex 1 from 0 is 1, vertex 2 is 6 and vertex 3 is unreachable so INF.
```

### Example 2
```text
Input: V = 5, src = 1, edges[][] = [[0, 1, 1], [0, 2, 2], [1, 4, 4], [3, 2, -1], [4, 2, 3], [4, 3, 6]]
Output: [INF, 0, 9, 10, 4]
Explanation: The vertex 0 is not reachable from vertex 1 so its distance is INF, for 2 it is 9, for 3 it is 10, and for 4 it is 4.
```

<details>
<summary>📖 Example Breakdown (Example 1)</summary>

* **Graph Edges**: 
  * 0 -> 1 (weight 1)
  * 0 -> 2 (weight 1)
  * 1 -> 2 (weight 5)
  * 3 -> 1 (weight 2)
  * 3 -> 2 (weight -1)
* **Source (`src`)**: 0
* **Process**:
  1. Topo sort places `0` before `1` before `2`. (`3` is unreachable from `0` but gets processed in topo sort).
  2. Start distance array: `[0, -∞, -∞, -∞]`
  3. Relax node `0`: dist to `1` becomes max(-∞, 0+1) = 1. dist to `2` becomes max(-∞, 0+1) = 1.
  4. Array: `[0, 1, 1, -∞]`
  5. Relax node `1`: dist to `2` becomes max(1, 1+5) = 6. 
  6. Final Array: `[0, 1, 6, -∞]` (which maps to INF).
</details>

---

## ⚙️ Constraints

> * `1 ≤ V ≤ 10^3`
> * `1 ≤ edges.size() ≤ V * (V - 1) / 2`
> * `0 ≤ edges[i][0], edges[i][1] < V`
> * `-100 ≤ edges[i][2] ≤ 100`

---

## 🚀 Solution Approach

### Optimized Approach: Topological Sort & Edge Relaxation

```cpp
// Intuition: Since the graph is a Directed Acyclic Graph (DAG), there are no cycles. This means we can process the vertices in Topological Order, ensuring that before we compute the longest path for a vertex, all paths leading to its ancestors have already been finalized.
// Approach: 
// 1. Convert the edge list into an adjacency list and calculate the indegree of each vertex.
// 2. Use Kahn's Algorithm (BFS) to generate the Topological Sort order of the vertices.
// 3. Initialize a distance array with INT_MIN (infinity for longest paths), setting dist[src] = 0.
// 4. Iterate over the nodes in topological order. If a node is reachable, traverse its adjacent nodes and relax the edges (maximize the distance).
// Time Complexity: O(V + E) - We traverse all vertices and edges once to build the graph, once for Kahn's algorithm, and once to relax distances.
// Space Complexity: O(V + E) - For storing the adjacency list, indegree array, queue, and topological order array.

class Solution {
  public:
    vector<int> maxDistance(int V, int src, vector<vector<int>> &edges) {
        // Build adjacency list and indegree array
        vector<vector<pair<int, int>>> g(V);
        vector<int> indegree(V, 0);
    
        // Populate the graph structure
        for (auto &ed : edges) {
            int u = ed[0];
            int v = ed[1];
            int wt = ed[2];
    
            g[u].push_back({v, wt});
            indegree[v]++;
        }
    
        // Initialize queue for Kahn's Algorithm
        queue<int> q;
    
        // Push all nodes with zero incoming edges
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }
    
        vector<int> topoOrder;
    
        // Process queue to find topological order
        while (!q.empty()) {
            int node = q.front();
            q.pop();
    
            topoOrder.push_back(node);
    
            // Reduce indegree of neighbors
            for (auto &it : g[node]) {
                int v = it.first;
    
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }
    
        // Distance array initialized to negative infinity
        vector<int> dist(V, INT_MIN);
        dist[src] = 0;
    
        // Process vertices strictly in topological order
        for (int node : topoOrder) {
            // Skip if the current vertex is completely unreachable
            if (dist[node] == INT_MIN)
                continue;
    
            // Relax all outgoing edges
            for (auto &it : g[node]) {
                int v = it.first;
                int wt = it.second;
    
                // Update with maximum possible distance
                dist[v] = max(dist[v], dist[node] + wt);
            }
        }
    
        return dist;
    }
};

/*
Dry Run
Input: V = 4, src = 0, edges = [[0,1,1], [0,2,1], [1,2,5], [3,1,2], [3,2,-1]]
Indegrees: [0:0, 1:2, 2:2, 3:0]
Initial Queue: [0, 3]

Kahn's BFS:
Pop 0 -> topoOrder=[0], Neighbors 1, 2. Indegrees now [1:1, 2:1]
Pop 3 -> topoOrder=[0, 3], Neighbors 1, 2. Indegrees now [1:0, 2:0]. Queue=[1, 2]
Pop 1 -> topoOrder=[0, 3, 1], Neighbors 2. Indegrees now [2:-1]
Pop 2 -> topoOrder=[0, 3, 1, 2]

Distances init: [0, INT_MIN, INT_MIN, INT_MIN]
Relaxation along topoOrder [0, 3, 1, 2]:
Node 0: dist[1] = max(INT_MIN, 0+1) = 1. dist[2] = max(INT_MIN, 0+1) = 1. (Dist: [0, 1, 1, INT_MIN])
Node 3: Skip, dist[3] is INT_MIN.
Node 1: dist[2] = max(1, 1+5) = 6. (Dist: [0, 1, 6, INT_MIN])
Node 2: No outgoing edges.

Final Distances: [0, 1, 6, INT_MIN]
*/
```

---

## 🧠 Key Insights

* **Why Topological Sort?** In a DAG, topological sort guarantees that all paths directed towards vertex `v` are fully explored before we process `v` itself. This linear dependency mapping allows us to solve the problem in `O(V+E)` instead of using complex standard graph traversals.
* **Negative Weights:** Standard algorithms like Dijkstra's fail or struggle with negative weights for longest paths, but topological sort evaluates nodes strictly downstream, making edge weights irrelevant to traversal rules.

---

## 🔗 Further Exploration

If you enjoyed this, check out these related concepts and problems:
* [Shortest Path in Directed Acyclic Graph](https://www.geeksforgeeks.org/problems/shortest-path-in-a-directed-acyclic-graph/1)
* [Topological sort](https://www.geeksforgeeks.org/problems/topological-sort/1)
* [Dijkstra Algorithm](https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1)

---

## 📚 References

* **GeeksforGeeks Problem:** [Longest Path in a Directed Acyclic Graph](https://www.geeksforgeeks.org/problems/longest-path-in-a-directed-acyclic-graph/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`Graph` `Directed Acyclic Graph` `Topological Sort` `Dynamic Programming` `GeeksforGeeks`
