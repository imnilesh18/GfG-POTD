# 🟩 Path Exists Between Two Vertices

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/path-exists/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-64.27%25-blue?style=for-the-badge" alt="Accuracy: 64.27%" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
</p>

> ⚠️ **Educational Use Only:** This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

<div align="center">

```text
Component 1:          Component 2:
    1
    |
    2 --- 0 --- 3         4 --- 5
```

*Visualizing the undirected graph from the sample test cases: vertices `{0, 1, 2, 3}` form one connected component, while `{4, 5}` form a separate component.*

</div>

---

## 📋 Problem Statement

Given an **undirected graph** with $V$ vertices numbered from $0$ to $V - 1$, represented by an adjacency list `adj[][]`, where `adj[i]` contains all vertices adjacent to vertex `i`. Also given two vertices `u` and `v`, check whether a path exists between them.

Return `true` if a path exists, otherwise return `false`.

---

## 💡 Examples

### Example 1
```text
Input: adj[][] = [[2, 3], [2], [0, 1], [0], [5], [4]], u = 1, v = 5
Output: false
Explanation: There is no path from vertex 1 to vertex 5.
```

### Example 2
```text
Input: adj[][] = [[2, 3], [2], [0, 1], [0], [5], [4]], u = 2, v = 3
Output: true
Explanation: We can reach vertex 3 from vertex 2 via vertex 0.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's inspect the adjacency list `adj = [[2, 3], [2], [0, 1], [0], [5], [4]]`:
- **Vertex 0** connects to `2, 3`
- **Vertex 1** connects to `2`
- **Vertex 2** connects to `0, 1`
- **Vertex 3** connects to `0`
- **Vertex 4** connects to `5`
- **Vertex 5** connects to `4`

1. **For `u = 1, v = 5` (Example 1):**
   - Starting from `1`, we can visit `2`, then `0`, and then `3`.
   - No edges bridge `{0, 1, 2, 3}` to `{4, 5}`.
   - Once all reachable vertices from `1` are exhausted, `5` remains unvisited, so the result is **`false`**.

2. **For `u = 2, v = 3` (Example 2):**
   - Starting from `2`, its neighbors are `0` and `1`.
   - Moving to `0`, we find `3` in `adj[0]`.
   - Since `2 -> 0 -> 3` forms a valid path, the result is **`true`**.

</details>

---

## 🔒 Constraints & Expected Complexities

> - $2 \le \text{adj.size()} \le 10^5$
> - $0 \le \text{adj}[i][j], u, v < \text{adj.size()}$
> - $u \ne v$
> - **Expected Time Complexity:** $\mathcal{O}(V + E)$
> - **Expected Auxiliary Space:** $\mathcal{O}(V + E)$

---

## 🚀 Solution Approaches

### Approach 1: Breadth-First Search (BFS) — Recommended

Exploring the graph level-by-level from `u` using a queue avoids deep recursion stacks (important when $V \le 10^5$) and terminates immediately as soon as `v` is encountered.

```cpp
// Intuition: Two vertices in an undirected graph belong to the same connected component if and only if a path exists between them, which we can verify by exploring neighbors from u until we reach v.
// Approach:
// 1. Initialize a visited array of size V (adj.size()) to avoid revisiting nodes and prevent infinite loops in cycles.
// 2. Push the starting vertex u into a queue and mark visited[u] = true.
// 3. While the queue is not empty, pop the front vertex curr; if curr == v, return true immediately.
// 4. Iterate through all neighbors of curr; for each unvisited neighbor, mark it visited and push it into the queue.
// 5. If the queue becomes empty without reaching v, return false.
// Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges, as each vertex and edge is explored at most once.
// Space Complexity: O(V), for the visited vector and the BFS queue storing up to V vertices in the worst case.
class Solution {
  public:
    bool checkPath(vector<vector<int>> &adj, int u, int v) {
        int V = adj.size(); // Total number of vertices
        vector<bool> visited(V, false); // Track visited vertices
        queue<int> q; // Queue for level-order BFS traversal
        
        q.push(u); // Start traversal from source vertex u
        visited[u] = true; // Mark source as visited
        
        while (!q.empty()) {
            int curr = q.front(); // Get next vertex to process
            q.pop();
            
            if (curr == v) return true; // Target vertex v reached
            
            for (int neighbor : adj[curr]) { // Explore all adjacent vertices
                if (!visited[neighbor]) {
                    visited[neighbor] = true; // Mark neighbor visited before pushing
                    q.push(neighbor); // Enqueue unvisited neighbor
                }
            }
        }
        
        return false; // Destination v is unreachable from u
    }
};

/*
 *
 * Dry Run
 *
 * Input: adj = [[2, 3], [2], [0, 1], [0], [5], [4]], u = 2, v = 3
 * V = 6, visited = [false, false, false, false, false, false]
 * Start: push 2 into queue, visited[2] = true -> q = [2]
 * Iteration 1: pop curr = 2 (2 != 3)
 *   Neighbors of 2 are 0 and 1
 *   neighbor = 0: not visited -> visited[0] = true, push 0
 *   neighbor = 1: not visited -> visited[1] = true, push 1
 *   q = [0, 1]
 * Iteration 2: pop curr = 0 (0 != 3)
 *   Neighbors of 0 are 2 and 3
 *   neighbor = 2: already visited -> skip
 *   neighbor = 3: not visited -> visited[3] = true, push 3
 *   q = [1, 3]
 * Iteration 3: pop curr = 1 (1 != 3)
 *   Neighbor of 1 is 2 (already visited -> skip)
 *   q = [3]
 * Iteration 4: pop curr = 3 (3 == v) -> returns true
 * Output: true
 *
 */
```

---

### Approach 2: Depth-First Search (DFS)

Recursively traversing along each branch from `u` provides a compact implementation that propagates `true` up the call stack as soon as `v` is found.

```cpp
// Intuition: Recursively exploring as deep as possible along each branch from u allows us to verify whether v lies in the same connected component.
// Approach:
// 1. Create a boolean visited vector of size V initialized to false.
// 2. Call a recursive DFS helper function starting at vertex u.
// 3. Inside DFS, if the current vertex equals v, return true immediately.
// 4. Mark the current vertex as visited and recursively visit all unvisited neighbors; if any recursive call returns true, propagate true upward.
// 5. Return false if all reachable vertices from u are exhausted without finding v.
// Time Complexity: O(V + E), as every vertex is visited at most once and every edge is traversed at most twice in an undirected graph.
// Space Complexity: O(V), for the visited array and the recursion call stack in the worst case of a skewed/linear graph.
class Solution {
  private:
    bool dfs(int curr, int target, vector<vector<int>> &adj, vector<bool> &visited) {
        if (curr == target) return true; // Target vertex found
        visited[curr] = true; // Mark current vertex as visited
        
        for (int neighbor : adj[curr]) { // Traverse all adjacent vertices
            if (!visited[neighbor]) {
                if (dfs(neighbor, target, adj, visited)) {
                    return true; // Path found via this neighbor
                }
            }
        }
        
        return false; // No path found from current branch
    }

  public:
    bool checkPath(vector<vector<int>> &adj, int u, int v) {
        int V = adj.size(); // Total number of vertices
        vector<bool> visited(V, false); // Track visited vertices
        return dfs(u, v, adj, visited); // Start DFS traversal from u
    }
};

/*
 *
 * Dry Run
 *
 * Input: adj = [[2, 3], [2], [0, 1], [0], [5], [4]], u = 1, v = 5
 * V = 6, visited = [false, false, false, false, false, false]
 * Call dfs(1, 5): 1 != 5, visited[1] = true
 *   Neighbor of 1 is 2 (unvisited) -> call dfs(2, 5)
 *   Call dfs(2, 5): 2 != 5, visited[2] = true
 *     First neighbor of 2 is 0 (unvisited) -> call dfs(0, 5)
 *     Call dfs(0, 5): 0 != 5, visited[0] = true
 *       First neighbor of 0 is 2 (visited -> skip)
 *       Second neighbor of 0 is 3 (unvisited) -> call dfs(3, 5)
 *       Call dfs(3, 5): 3 != 5, visited[3] = true
 *         Neighbor of 3 is 0 (visited -> skip)
 *         Returns false to dfs(0, 5)
 *       Returns false to dfs(2, 5)
 *     Second neighbor of 2 is 1 (visited -> skip)
 *     Returns false to dfs(1, 5)
 *   Returns false to checkPath
 * Output: false
 *
 */
```

---

## 🔑 Key Insights

- **Cycle Prevention:** Because the graph is undirected, every edge `(a, b)` appears in both `adj[a]` and `adj[b]`. Marking vertices in a `visited` array immediately upon discovery prevents infinite loops and redundant queue/stack entries.
- **Early Exit Optimization:** Checking `curr == v` immediately lets both BFS and DFS stop as soon as the target is reached, avoiding unnecessary traversal of the rest of the graph.
- **Stack Safety with BFS:** With $V$ up to $10^5$, a long linear chain graph can cause a recursion stack overflow in recursive DFS on strict stack limits; iterative BFS avoids this risk while maintaining $\mathcal{O}(V + E)$ time.

---

## 🔍 Further Exploration

- **Multiple Queries Optimization:** If you need to answer $Q$ path-existence queries on a static graph, preprocess connected components using **Disjoint Set Union (DSU / Union-Find)** so each query runs in nearly $\mathcal{O}(1)$ amortized time ($\mathcal{O}(\alpha(V))$).
- **Related GeeksforGeeks Problems:**
  - [Find whether path exist (Grid)](https://www.geeksforgeeks.org/problems/find-whether-path-exist5238/1)
  - [BFS of graph](https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1)
  - [DFS of Graph](https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1)
  - [Number of Provinces](https://www.geeksforgeeks.org/problems/number-of-provinces/1)

---

## 📚 References

- **GeeksforGeeks Problem:** [Path Exists Between Two Vertices](https://www.geeksforgeeks.org/problems/path-exists/1)
- **Graph Traversal Concepts:** [Breadth-First Search (BFS)](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/) & [Depth-First Search (DFS)](https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Graph](https://img.shields.io/badge/Topic-Graph-blueviolet?style=flat-square)
![BFS](https://img.shields.io/badge/Topic-BFS-blue?style=flat-square)
![DFS](https://img.shields.io/badge/Topic-DFS-teal?style=flat-square)
![NPCI](https://img.shields.io/badge/Company-NPCI-orange?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square)