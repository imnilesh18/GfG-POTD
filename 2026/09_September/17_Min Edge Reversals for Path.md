# 🟧 Min Edge Reversals for Path

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-2980B9?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy: 54.95%](https://img.shields.io/badge/Accuracy-54.95%25-blue?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a directed graph with $n$ vertices numbered from `1` to `n`. The graph is represented using a 2D array `edges[][]` of size $m$, where each entry `edges[i] = [u, v]` denotes a directed edge from vertex $u$ to vertex $v$. You are also given a source vertex `src` and a destination vertex `dst`.

Find the **minimum number of edges that need to be reversed** so that there exists at least one path from `src` to `dst`.

If it is not possible to create a path from `src` to `dst`, return `-1`.

---

## 📸 Examples

### Example 1
```text
Input: n = 3, edges[][] = [[1, 2], [3, 2]], src = 1, dst = 3
Output: 1
Explanation: Reverse the edge 3 -> 2 to make it 2 -> 3. The path 1 -> 2 -> 3 then exists.
```

### Example 2
```text
Input: n = 4, edges[][] = [[1, 2], [2, 3], [3, 4]], src = 1, dst = 4
Output: 0
Explanation: One direct path already exists between 1 to 4 i.e. 1 -> 2 -> 3 -> 4.
```

<details>
<summary>📖 Example Breakdown (Example 1)</summary>

1. **Initial Graph:**
   - $1 \rightarrow 2$
   - $3 \rightarrow 2$
2. **Goal:** Reach node `3` starting from node `1`.
3. **Traversal:**
   - From node `1`, we can naturally reach node `2` with `0` reversals.
   - From node `2`, there is no outgoing edge to node `3`.
   - Reversing the directed edge $3 \rightarrow 2$ creates an edge $2 \rightarrow 3$ at the cost of **1 reversal**.
4. **Result:** Total edge reversals = `1`.
</details>

---

## ⚙️ Constraints

- $1 \le n, m \le 10^5$
- $1 \le \text{edges}[i][0], \text{edges}[i][1] \le n$
- $1 \le \text{src}, \text{dst} \le n$

---

## 💡 Solution Approach (0-1 BFS)

### Intuition
To find the minimum number of edge reversals, we transform this into a shortest path problem on a graph with weighted edges:
- An existing directed edge $u \rightarrow v$ requires **0 reversals** (Cost = 0).
- A virtual reversed edge $v \rightarrow u$ requires **1 reversal** (Cost = 1).

Since edge weights are strictly `0` or `1`, standard Dijkstra's algorithm is unnecessary. We can find the optimal shortest path in $O(V + E)$ time using **0-1 BFS** with a Double-Ended Queue (`std::deque`).

### C++ Code Implementation

```cpp
// Intuition: Model original edges with weight 0 and reversed edges with weight 1. The minimum reversal path is equivalent to finding the shortest path on a 0-1 weighted graph using 0-1 BFS via a Deque.
// Approach: Build an adjacency list storing {neighbor, weight}. Use a double-ended queue (deque) to perform BFS. Push weight-0 moves to the front and weight-1 moves to the back.
// Time Complexity: O(V + E) where V is total vertices (n) and E is total edges (m), as every node and edge is processed at most twice.
// Space Complexity: O(V + E) to store the adjacency list, distance array, and double-ended queue.

class Solution {
  public:
    // Function to find the minimum number of edge reversals.
    int minimumEdgeReversal(vector<vector<int>>& edges, int n, int src, int dst) {

        vector<vector<pair<int, int>>> adj(n + 1);

        // Create adjacency list with both directions.
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            // Original direction requires no reversal.
            adj[u].push_back({v, 0});

            // Reverse direction requires one reversal.
            adj[v].push_back({u, 1});
        }

        // Store the minimum reversals required to reach each node.
        vector<int> dist(n + 1, INT_MAX);

        deque<int> dq;

        // Distance of source is 0.
        dist[src] = 0;
        dq.push_front(src);

        // Apply 0-1 BFS.
        while (!dq.empty()) {
            int node = dq.front();
            dq.pop_front();

            // Explore all adjacent nodes.
            for (auto& edge : adj[node]) {
                int next = edge.first;
                int cost = edge.second;

                // Update the distance if a better path is found.
                if (dist[node] + cost < dist[next]) {
                    dist[next] = dist[node] + cost;

                    // Process zero-cost edges first.
                    if (cost == 0)
                        dq.push_front(next);
                    else
                        dq.push_back(next);
                }
            }
        }

        // No path exists from src to dst.
        if (dist[dst] == INT_MAX)
            return -1;

        return dist[dst];
    }
};

/*
* Dry Run
* Input: n = 3, edges = [[1, 2], [3, 2]], src = 1, dst = 3
*
* Graph Construction:
* adj[1] = {(2, 0)}
* adj[2] = {(1, 1), (3, 1)}
* adj[3] = {(2, 0)}
*
* Initial State:
* dist = [INF, 0, INF, INF]
* dq = [1]
*
* Step 1: Pop node 1 (dist[1] = 0)
*   Neighbor (2, 0): dist[2] > 0 + 0 -> dist[2] = 0, push_front(2)
*   dq = [2]
*
* Step 2: Pop node 2 (dist[2] = 0)
*   Neighbor (1, 1): dist[1] <= 0 + 1 (no update)
*   Neighbor (3, 1): dist[3] > 0 + 1 -> dist[3] = 1, push_back(3)
*   dq = [3]
*
* Step 3: Pop node 3 (dist[3] = 1)
*   Neighbor (2, 0): dist[2] <= 1 + 0 (no update)
*   dq = []
*
* Final Output: dist[dst] = dist[3] = 1
*/
```

---

## Key Insights

- **0-1 Weight Transformation:** By modeling "no reversal" as cost `0` and "reversal" as cost `1`, the problem simplifies into finding the shortest path in a graph.
- **Efficiency of Deque:** Using `push_front()` for cost `0` and `push_back()` for cost `1` preserves topological ordering by distance, ensuring $O(V + E)$ complexity without the logarithmic overhead of a priority queue.

---

## 🔗 Related Topics & Problems

- **0-1 BFS / Shortest Path**
- **Graph Traversal (BFS & Deque)**
- [GFG: Minimum Cost Path in a Directed Graph](https://www.geeksforgeeks.org/problems/minimum-cost-path3833/1)
- [GFG: Distance of nearest cell having 1](https://www.geeksforgeeks.org/problems/distance-of-nearest-cell-having-1-1587115620/1)

---

## 📌 References

- [GeeksforGeeks Problem Page](https://www.geeksforgeeks.org/problems/minimum-edges/1)

---

## 👤 Author

Made with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`graph` `0-1-bfs` `deque` `shortest-path` `geeksforgeeks` `cpp`

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

> **Disclaimer:** This software is provided for educational and learning purposes only.