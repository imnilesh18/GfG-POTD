<div align="center">
  <h1>🛑 Length of Longest Cycle in a Graph</h1>
  
  [![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://practice.geeksforgeeks.org/problems/length-of-longest-cycle-in-a-graph/1)
  [![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)](#)
  [![Accuracy](https://img.shields.io/badge/Accuracy-70.83%25-green?style=for-the-badge)](#)
  [![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)](#)
  [![License](https://img.shields.io/badge/License-MIT-orange?style=for-the-badge)](#)
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a directed graph with `V` vertices numbered from `0` to `V-1` and `E` edges, represented as a 2D array `edges[][]`, where each entry `edges[i] = [u, v]` denotes an edge between vertices `u` and `v`. **Each node has at most one outgoing edge.**

Your task is to find the length of the **longest cycle** present in the graph. If no cycle exists, return `-1`.

> **Note:** A cycle is a path that starts and ends at the same vertex.

### 🎯 Constraints

> - `1 ≤ V, E ≤ 10^4`
> - `0 ≤ edges[i][0], edges[i][1] < V`
> - Each node has **at most one** outgoing edge.

---

## 💡 Examples

### Example 1
```text
Input: V = 7, edges[][] = [[0, 5], [1, 0], [2, 4], [3, 1], [4, 6], [5, 6], [6, 3]]
Output: 5
Explanation: The longest Cycle is 0 -> 5 -> 6 -> 3 -> 1 -> 0
```

### Example 2
```text
Input: V = 8, edges[][] = [[0, 1], [1, 2], [2, 3], [3, 0], [4, 1], [5, 4], [6, 2], [7, 6]]
Output: 4
Explanation: The longest Cycle is 0 -> 1 -> 2 -> 3 -> 0
```

<details>
  <summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>
  
  **Given `edges[][] = [[0, 1], [1, 2], [2, 3], [3, 0], [4, 1], [5, 4], [6, 2], [7, 6]]`**
  
  1. We build an adjacency relationship since out-degree is $\le 1$:
     - `0 -> 1`, `1 -> 2`, `2 -> 3`, `3 -> 0`
     - `4 -> 1`, `5 -> 4`
     - `6 -> 2`, `7 -> 6`
  2. Starting traversal from `0`: 
     `0` -> `1` -> `2` -> `3` -> `0` (Hits `0` again!)
     Length of this cycle = $4$.
  3. Starting traversal from `4`:
     `4` -> `1` (But `1` was already fully visited in the previous cycle, so we stop to avoid redundant work).
  4. Same goes for `5`, `6`, and `7`. They eventually lead to nodes already marked visited.
  5. The maximum cycle length recorded is **4**.

</details>

---

## 🚀 Solution Approaches

### Optimal Approach: Iterative Traversal using Distance Tracking

**Intuition:** Because each node has at most one outgoing edge, the graph is essentially a "functional graph". Nodes will form either trees or cycles. If we traverse the graph starting from unvisited nodes, we can easily find cycle lengths by recording the exact traversal distance at each step.

**Time Complexity:** $O(V + E)$ - We visit each vertex and process each edge at most twice (once for initial visitation and once for path clean-up).

**Space Complexity:** $O(V + E)$ - We use a simple 1D array to store the adjacency list, along with global `vis`, `pathVis`, and `dist` arrays to track state throughout the traversals.

```cpp
// Intuition: Since each node has at most one outgoing edge, the graph is a collection of trees and cycles (functional graph). We can traverse from unvisited nodes, keeping track of the traversal distance to easily calculate cycle lengths when a back-edge is found.
// Approach: Build an adjacency array since out-degree is <= 1. Use an iterative traversal tracking global 'vis' and 'pathVis' (nodes in the current traversal path). Track distance from the start of the current path. If we hit a node already in 'pathVis', a cycle is found. Its length is the current distance minus the distance recorded at the hit node.
// Time Complexity: O(V + E) where V is vertices and E is edges. We visit each node and edge at most twice.
// Space Complexity: O(V) for the visited, path visited, distance arrays, and adjacency list.

class Solution {
  public:
    int longestCycle(int V, vector<vector<int>>& edges) {
        // Create adjacency list mapping (at most 1 outgoing edge)
        vector<int> adj(V, -1);
        for (auto& edge : edges) {
            adj[edge[0]] = edge[1];
        }
        
        vector<bool> vis(V, false);
        vector<bool> pathVis(V, false);
        vector<int> dist(V, 0);
        int maxCycle = -1;
        
        // Traverse each node to find cycles
        for (int i = 0; i < V; ++i) {
            if (!vis[i]) {
                int curr = i;
                int currentDist = 0;
                vector<int> currentPath; 
                
                // Traverse along outgoing edges
                while (curr != -1) {
                    if (!vis[curr]) {
                        // Mark node as visited globally and in current path
                        vis[curr] = true;
                        pathVis[curr] = true;
                        dist[curr] = currentDist++;
                        currentPath.push_back(curr);
                        curr = adj[curr];
                    } else if (pathVis[curr]) {
                        // Cycle detected in current path traversal
                        maxCycle = max(maxCycle, currentDist - dist[curr]);
                        break;
                    } else {
                        // Hit a previously fully processed node, no new cycle
                        break;
                    }
                }
                
                // Clean up path vis array for the next starting nodes
                for (int node : currentPath) {
                    pathVis[node] = false;
                }
            }
        }
        
        return maxCycle;
    }
};

/*
Dry Run:
Input: V = 8, edges = [[0,1], [1,2], [2,3], [3,0], [4,1], [5,4], [6,2], [7,6]]
Initialization: adj = [1, 2, 3, 0, 1, 4, 2, 6], maxCycle = -1

i = 0: 
curr = 0, currentDist = 0
vis[0]=T, pathVis[0]=T, dist[0]=0, curr=1
vis[1]=T, pathVis[1]=T, dist[1]=1, curr=2
vis[2]=T, pathVis[2]=T, dist[2]=2, curr=3
vis[3]=T, pathVis[3]=T, dist[3]=3, curr=0
curr=0 is already in pathVis! Cycle length = 4 - dist[0] = 4 - 0 = 4
maxCycle = max(-1, 4) = 4
Reset pathVis for nodes 0,1,2,3

i = 4:
curr = 4, vis[4]=T, pathVis[4]=T, dist[4]=0, curr=1
curr=1 is already vis=T but pathVis=F. Break.
Reset pathVis for node 4

i = 5, 6, 7 follow similar paths ending at previously visited nodes without forming new cycles.

Result: 4
*/
```

---

## 🧠 Key Insights

- **Functional Graph Structure:** The crucial constraint `Each node has at most one outgoing edge` transforms a standard graph problem into traversing a Functional Graph. This means no branching occurs, heavily simplifying standard DFS constraints.
- **`pathVis` Array:** Keeping a separate memory of nodes visited *during the current walk* allows us to accurately deduce whether a back-edge connects to the *current* cycle or simply merges into a component we have already evaluated and closed.

---

## 🔍 Further Exploration

- [Detect Cycle in a Directed Graph](https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1)
- [Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)
- Cycle Counting in Permutation Graphs

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - Length of Longest Cycle in a Graph](https://practice.geeksforgeeks.org/problems/length-of-longest-cycle-in-a-graph/1)
- **Concept Reference:** Topographical sorting and Functional Directed Graphs.

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`Graph` `DFS` `BFS` `Cycle Detection` `GeeksforGeeks` `C++`
