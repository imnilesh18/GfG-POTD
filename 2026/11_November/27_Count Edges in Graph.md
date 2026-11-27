# 🟩 Count Edges in Graph

<p align="left">
  <a href="https://www.geeksforgeeks.org/problems/count-number-of-edges-in-an-undirected-graph/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-79.48%25-blue?style=for-the-badge" alt="Accuracy: 79.48%" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
</p>

> ⚠️ **Educational Use Only:** This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given an undirected graph with `V` vertices numbered from `0` to `V - 1`, represented by an adjacency list `adj[][]`, where `adj[i]` contains the vertices adjacent to vertex `i`.

Return the total number of edges present in the graph.

---

## 🧪 Examples

### Example 1

```text
Input: adj[][] = [[1, 2], [0, 2], [0, 1, 3], [2]]
Output: 4
Explanation: The edges in the graph are: (0-1), (0-2), (2-3), (1-2). Hence, total number of edges = 4.
```

### Example 2

```text
Input: adj[][] = [[1], [0, 2], [1, 3], [2]]
Output: 3
Explanation: The edges in the graph are: (0-1), (1-2), (2-3). Hence, total number of edges = 3.
```

<details>
<summary><b>📖 Example Breakdown (Example 1 Walkthrough)</b></summary>

Consider `adj[][] = [[1, 2], [0, 2], [0, 1, 3], [2]]` with `V = 4` vertices:

| Vertex (`i`) | Adjacency List `adj[i]` | Degree `adj[i].size()` | Edges Incident to `i` |
| :---: | :---: | :---: | :--- |
| **0** | `[1, 2]` | `2` | `(0-1)`, `(0-2)` |
| **1** | `[0, 2]` | `2` | `(1-0)`, `(1-2)` |
| **2** | `[0, 1, 3]` | `3` | `(2-0)`, `(2-1)`, `(2-3)` |
| **3** | `[2]` | `1` | `(3-2)` |

- **Total Degree Sum:** `2 + 2 + 3 + 1 = 8`
- **Unique Undirected Edges:** Each edge appears in two adjacency lists (once at each endpoint), so total edges = `8 / 2 = 4`.

</details>

---

## 🔒 Constraints

> - $1 \le \text{adj.size()} \le 10^4$
> - $0 \le \text{adj}[i][j] < \text{adj.size()}$
>
> **Expected Complexities:**
> - **Time Complexity:** $\mathcal{O}(V + E)$
> - **Auxiliary Space:** $\mathcal{O}(1)$

---

## 💡 Solution Approaches

### Approach 1: Unique Edge Set (Explicit Deduplication)

In an undirected graph, every edge between `u` and `v` appears twice in `adj`—once as `v` inside `adj[u]` and once as `u` inside `adj[v]`. By normalizing each edge as an ordered pair `{min(u, v), max(u, v)}` and inserting it into a `set`, duplicates are automatically filtered out, and the final size of the set gives the exact edge count.

```cpp
// Intuition: Normalize every undirected edge (u, v) as {min(u, v), max(u, v)} in a set so duplicate representations are ignored.
// Approach: Traverse all vertices u and their neighbors v, insert ordered pairs {min(u, v), max(u, v)} into a set, and return the set size.
// Time Complexity: O((V + E) log E), where V is the number of vertices and E is the number of edges, due to logarithmic set insertions.
// Space Complexity: O(E) auxiliary space to store all unique edges inside the set.

class Solution {
  public:
    int countEdges(vector<vector<int>> &adj) {
        set<pair<int, int>> uniqueEdges; // Stores unique undirected edges

        // Traverse each vertex u in the graph
        for (int u = 0; u < adj.size(); u++) {
            // Traverse all adjacent vertices v of u
            for (int v : adj[u]) {
                // Store edge in canonical order to avoid counting (u, v) and (v, u) twice
                uniqueEdges.insert({min(u, v), max(u, v)});
            }
        }

        return uniqueEdges.size(); // Total count of distinct edges
    }
};

/*
 *
 * Dry Run
 *
 * Input: adj = [[1, 2], [0, 2], [0, 1, 3], [2]]
 *
 * u = 0: neighbors = [1, 2] -> insert {0, 1}, {0, 2}
 * u = 1: neighbors = [0, 2] -> {0, 1} exists, insert {1, 2}
 * u = 2: neighbors = [0, 1, 3] -> {0, 2}, {1, 2} exist, insert {2, 3}
 * u = 3: neighbors = [2] -> {2, 3} exists
 *
 * uniqueEdges = {{0, 1}, {0, 2}, {1, 2}, {2, 3}}
 * uniqueEdges.size() = 4
 *
 * Output: 4
 *
 */
```

---

### Approach 2: Handshaking Lemma — Degree Sum (Optimal)

By the **Handshaking Lemma** in graph theory, the sum of the degrees of all vertices in an undirected graph is equal to twice the number of edges:

$$\sum_{i=0}^{V-1} \deg(i) = 2E$$

Since `adj[i].size()` gives the degree of vertex `i` in $\mathcal{O}(1)$ time, we can sum the sizes of all adjacency lists in a single loop and divide by `2`.

```cpp
// Intuition: By the Handshaking Lemma, the sum of degrees of all vertices in an undirected graph equals twice the number of edges.
// Approach: Iterate over all vertices, accumulate the size of each adjacency list adj[i], and return totalDegree / 2.
// Time Complexity: O(V) (within expected O(V + E)), where V is the number of vertices, since vector::size() runs in O(1) time.
// Space Complexity: O(1) auxiliary space, using only a single integer accumulator.

class Solution {
  public:
    int countEdges(vector<vector<int>> &adj) {
        int degreeSum = 0; // Accumulates sum of degrees across all vertices

        // Add the degree of each vertex i to degreeSum
        for (int i = 0; i < adj.size(); i++) {
            degreeSum += adj[i].size();
        }

        return degreeSum / 2; // Each undirected edge is counted twice
    }
};

/*
 *
 * Dry Run
 *
 * Input: adj = [[1, 2], [0, 2], [0, 1, 3], [2]]
 *
 * Initial: degreeSum = 0
 * i = 0: adj[0].size() = 2 -> degreeSum = 2
 * i = 1: adj[1].size() = 2 -> degreeSum = 4
 * i = 2: adj[2].size() = 3 -> degreeSum = 7
 * i = 3: adj[3].size() = 1 -> degreeSum = 8
 *
 * Return degreeSum / 2 = 8 / 2 = 4
 *
 * Output: 4
 *
 */
```

---

### 📊 Complexity Comparison

| Approach | Time Complexity | Auxiliary Space | Verdict |
| :--- | :---: | :---: | :---: |
| **Unique Edge Set** | $\mathcal{O}((V + E) \log E)$ | $\mathcal{O}(E)$ | ⚠️ Extra memory & log factor |
| **Handshaking Lemma (Optimal)** | $\mathcal{O}(V)$ | $\mathcal{O}(1)$ | ✅ Optimal — Meets $\mathcal{O}(1)$ space target |

---

## 🔑 Key Insights

- **Handshaking Lemma:** In any undirected simple graph, each edge connects two endpoints, contributing `1` to the adjacency list of each endpoint. Summing `adj[i].size()` across all vertices always produces $2E$.
- **Constant-Time Size Lookup:** In C++, `std::vector::size()` is an $\mathcal{O}(1)$ operation, so we do not even need an inner loop to traverse individual neighbors.
- **Overflow Safety:** Given $V \le 10^4$, the maximum possible sum of degrees in a simple undirected graph is $V(V - 1) \approx 10^8$, which fits comfortably within a standard 32-bit signed `int`.

---

## 🚀 Further Exploration

- **Directed Graph Variant:** If the input graph were **directed**, each edge `(u -> v)` would appear only once (in `adj[u]`), so the total number of edges would simply be `degreeSum` without dividing by `2`.
- **Self-Loops Variant:** If self-loops `(u, u)` are represented once in `adj[u]`, counting neighbors `v` where `u <= v` handles both self-loops and standard undirected edges in $\mathcal{O}(V + E)$ time and $\mathcal{O}(1)$ space.
- **Related Problems:**
  - [Print Adjacency List](https://www.geeksforgeeks.org/problems/print-adjacency-list-1587115620/1)
  - [BFS of Graph](https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1)
  - [DFS of Graph](https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks — Count Edges in Graph](https://www.geeksforgeeks.org/problems/count-number-of-edges-in-an-undirected-graph/1)
- **Concept Guide:** [GeeksforGeeks — Graph and its Representations](https://www.geeksforgeeks.org/graph-and-its-representations/)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Graph](https://img.shields.io/badge/Topic-Graph-blueviolet?style=flat-square)
![Adjacency List](https://img.shields.io/badge/Topic-Adjacency%20List-informational?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=cplusplus)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks)