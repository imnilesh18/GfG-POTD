# 🟧 Negative Weight Cycle

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Practice-green?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/negative-weight-cycle3504/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-41.9%25-orange?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

⚠️ Educational Use Only:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📌 Problem Statement

Given a weighted directed graph containing $V$ vertices numbered from $0$ to $V - 1$ and a list of $E$ directed edges `edges[][]`, determine whether the graph contains a **negative weight cycle** or not.

Each edge is represented as `[u, v, w]`, indicating a directed edge from vertex `u` to vertex `v` with a weight `w`.

> **Note:** A negative-weight cycle is a cycle in a graph whose edges sum up to a negative value.

---

## 💡 Examples

### Example 1
```text
Input: V = 4, E = 4, edges[][] = [[0, 3, 6], [1, 0, 4], [1, 2, 6], [3, 1, 2]]
Output: false
Explanation: Cycle 1 -> 0 -> 3 -> 1 has total weight 4 + 6 + 2 = 12, which is positive. 
No negative weight cycle exists.
```

### Example 2
```text
Input: V = 4, E = 4, edges[][] = [[1, 0, 4], [3, 1, -2], [1, 2, -6], [2, 3, 5]]
Output: true
Explanation: There is a cycle 1 -> 2 -> 3 -> 1 with total weight (-6) + 5 + (-2) = -3, 
which is negative, so a negative weight cycle exists.
```

<details>
<summary>📖 <b>Example Breakdown (Example 2 Walkthrough)</b></summary>

<br/>

1. **Cycle Identification:**
   * Path: $1 \rightarrow 2 \rightarrow 3 \rightarrow 1$
   * Edge $1 \rightarrow 2$ weight = $-6$
   * Edge $2 \rightarrow 3$ weight = $5$
   * Edge $3 \rightarrow 1$ weight = $-2$
2. **Total Weight Calculation:**
   $$\text{Total Weight} = (-6) + 5 + (-2) = -3$$
3. **Conclusion:**
   Since $-3 < 0$, traversing this cycle infinitely reduces path costs continuously. Thus, a negative weight cycle exists.
</details>

---

## ⚡ Constraints

> - $1 \le V \le 10^3$
> - $0 \le E \le 10^5$
> - $0 \le u, v < V$
> - $-10^6 \le w \le 10^6$

---

## 🛠️ Solution Approach

This problem can be efficiently solved using the **Bellman-Ford Algorithm**.

```cpp
// Intuition: A simple path without cycles in a graph with V vertices contains at most V - 1 edges. If relaxing all edges V - 1 times still permits distance reductions on the V-th iteration, a negative weight cycle must exist.
// Approach: Initialize a dist array of size V with 0s. Relax all edges V - 1 times. Run a V-th check; if any edge can still be relaxed, return true (cycle detected). Otherwise, return false.
// Time Complexity: O(V * E) - We iterate V - 1 times over all E edges, plus one extra pass over E edges for cycle detection.
// Space Complexity: O(V) - Uses an auxiliary distance array dist of size V.

class Solution {
  public:
    bool isNegativeWeightCycle(int V, vector<vector<int>>& edges) {
        // Distance array initialized to 0 to handle disconnected components simultaneously
        vector<int> dist(V, 0);

        // Relax all edges V - 1 times.
        for (int i = 0; i < V - 1; i++) {
            bool updated = false;

            for (const auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                // If a shorter path to v is found through u, update dist[v]
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }

            // No update means distances have stabilized.
            if (!updated) {
                return false;
            }
        }

        // Check whether any edge can still be relaxed.
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            // Further relaxation indicates a negative weight cycle
            if (dist[u] + w < dist[v]) {
                return true;
            }
        }

        return false;
    }
};

/*
* Dry Run
*
* Input: V = 4, E = 4, edges = [[1, 0, 4], [3, 1, -2], [1, 2, -6], [2, 3, 5]]
* Initial dist = [0, 0, 0, 0]
*
* Iteration 1 (i = 0):
*   Edge [1, 0, 4]:  dist[1] + 4  = 0 + 4 = 4   >= dist[0] (0)  -> No update
*   Edge [3, 1, -2]: dist[3] - 2  = 0 - 2 = -2  < dist[1] (0)   -> dist[1] = -2, updated = true
*   Edge [1, 2, -6]: dist[1] - 6  = -2 - 6 = -8 < dist[2] (0)   -> dist[2] = -8, updated = true
*   Edge [2, 3, 5]:  dist[2] + 5  = -8 + 5 = -3 < dist[3] (0)   -> dist[3] = -3, updated = true
* State after Iteration 1: dist = [0, -2, -8, -3]
*
* Iteration 2 (i = 1):
*   Edge [1, 0, 4]:  dist[1] + 4 = -2 + 4 = 2   >= dist[0] (0)  -> No update
*   Edge [3, 1, -2]: dist[3] - 2 = -3 - 2 = -5  < dist[1] (-2)  -> dist[1] = -5, updated = true
*   Edge [1, 2, -6]: dist[1] - 6 = -5 - 6 = -11 < dist[2] (-8)  -> dist[2] = -11, updated = true
*   Edge [2, 3, 5]:  dist[2] + 5 = -11 + 5 = -6 < dist[3] (-3)  -> dist[3] = -6, updated = true
* State after Iteration 2: dist = [0, -5, -11, -6]
*
* V-th Iteration Check:
*   Edge [3, 1, -2]: dist[3] + (-2) = -6 - 2 = -8 < dist[1] (-5) -> Can be relaxed!
* Output: true (Negative weight cycle exists)
*/
```

---

## 🔑 Key Insights

* **Why $V - 1$ Relaxations?** A shortest path between any two vertices in a graph without negative cycles contains at most $V - 1$ edges. Relaxing edges $V - 1$ times guarantees that short distances propagate across all vertices.
* **Detecting Cycles ($V$-th Relaxation):** If distance reductions still occur on the $V$-th iteration, it implies path lengths are reducing infinitely—proving the presence of a negative cycle.
* **Handling Disconnected Graphs:** Initializing `dist` array with `0` instead of `INT_MAX` ensures that all components are checked simultaneously, avoiding the need to run the algorithm separately from every potential source node.

---

## 🔗 Further Exploration

* [Distance from the Source (Bellman-Ford Algorithm)](https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1)
* [Floyd Warshall Algorithm (All-Pairs Shortest Path)](https://www.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1)
* [Dijkstra's Shortest Path Algorithm](https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1)

---

## 📚 References

* [GeeksforGeeks Problem Page](https://www.geeksforgeeks.org/problems/negative-weight-cycle3504/1)

---

## 👨‍💻 Author

Created with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

![Graph](https://img.shields.io/badge/Topic-Graph-blue?style=flat-square)
![Bellman-Ford](https://img.shields.io/badge/Algorithm-Bellman--Ford-orange?style=flat-square)
![Dynamic Programming](https://img.shields.io/badge/Topic-Dynamic%20Programming-purple?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square)