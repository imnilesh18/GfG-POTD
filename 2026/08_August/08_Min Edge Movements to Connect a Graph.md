# 🟧 Min Edge Movements to Connect a Graph

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Practice-brightgreen?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/connecting-the-graph/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-52.79%25-blue?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-yellow?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](#)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/connecting-the-graph/1) problem.

---

## 📝 Problem Statement

Given an undirected graph with **$n$** vertices (numbered from $0$ to $n-1$) and **$m$** edges. You can remove one edge from anywhere in the graph and add that edge between any two vertices in a single operation.

Find the **minimum number of operations** required to connect all vertices of the graph. If it is impossible to connect the entire graph, return `-1`.

---

## 💡 Examples

### Example 1
```text
Input: 
n = 4, edges[][] = [[0, 1], [0, 2], [1, 2]]

Output: 
1

Explanation: 
Remove the redundant edge between vertices 1 and 2, then add a new edge between vertices 1 and 3.
```

<details>
<summary>📖 Example Breakdown</summary>

* **Vertices**: $\{0, 1, 2, 3\}$
* **Connected Component 1**: $\{0, 1, 2\}$ formed by edges `(0, 1)`, `(0, 2)`, and redundant edge `(1, 2)`.
* **Connected Component 2**: $\{3\}$ (Isolated vertex).
* **Total Components ($C$)**: $2$
* **Required Edges to Connect Components**: $C - 1 = 2 - 1 = 1$
* **Redundant Edges Available**: $1$ (edge between `1` and `2`)
* Since available redundant edges ($\ge 1$), the minimum operations needed = **1**.
</details>

### Example 2
```text
Input: 
n = 6, edges[][] = [[0, 1], [0, 2], [0, 3], [1, 2], [1, 3]]

Output: 
2

Explanation: 
Remove edges between (1, 2) and (0, 3), then add edges between (1, 4) and (3, 5).
```

---

## ⚙️ Constraints

> - $1 \le n \le 10^5$
> - $1 \le m \le 10^5$
> - $0 \le edges[i][j] < n$
> - $2 \le \text{edges.cols} \le 2$
> - There are **no multi-edges** in the graph.

---

## 🛠️ Solution Approach

### Disjoint Set Union (DSU)

An undirected graph with $n$ vertices needs at least $n - 1$ edges to be fully connected. If total edges $m < n - 1$, it is impossible to connect the graph, so we return `-1`.

Using **Disjoint Set Union (DSU)**, we iterate through all edges:
1. If two vertices of an edge already belong to the same component, this edge is **redundant** (forms a cycle).
2. Otherwise, we unite the components using **Union by Rank/Size**.
3. After processing all edges, we count the total number of connected components ($C$).
4. To connect $C$ components, we need $C - 1$ edges.
5. If redundant edges $\ge C - 1$, return $C - 1$; otherwise, return `-1`.

```cpp
// Intuition: To connect C disjoint components, we need at least C - 1 edges. Redundant edges (edges forming cycles) can be repurposed to connect disconnected components.
// Approach: Use Disjoint Set Union (DSU) to count redundant edges and identify connected components. If total edges < n - 1, return -1. Otherwise, return (components - 1).
// Time Complexity: O(E * alpha(V) + V) which is virtually O(V + E) using path compression and union by rank.
// Space Complexity: O(V) auxiliary space for parent and rank arrays in DSU.

class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find representative with path compression
    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }
    
    // Union two components by rank
    bool unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        if (ulp_u == ulp_v) return false; // Edge is redundant
        
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
        return true;
    }
};

class Solution {
public:
    int minEdgesReq(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        
        // Minimum edges needed to connect n nodes is n - 1
        if (m < n - 1) return -1;
        
        DisjointSet ds(n);
        int extraEdges = 0;
        
        // Process each edge
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            
            // If u and v share the same parent, edge is redundant
            if (!ds.unionByRank(u, v)) {
                extraEdges++;
            }
        }
        
        // Count number of connected components
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i) {
                components++;
            }
        }
        
        int reqEdges = components - 1;
        
        // Check if we have enough extra edges to connect all components
        if (extraEdges >= reqEdges) {
            return reqEdges;
        }
        
        return -1;
    }
};

/*
*
* Dry Run
*
* Input: n = 4, edges = [[0, 1], [0, 2], [1, 2]]
* Total nodes (n) = 4, Total edges (m) = 3
* Check constraint: m >= n - 1 -> 3 >= 3 (Valid)
*
* Initial DSU state:
* parent = [0, 1, 2, 3]
* rank   = [0, 0, 0, 0]
* extraEdges = 0
*
* Processing Edge [0, 1]:
* findUPar(0) = 0, findUPar(1) = 1 (Different parents)
* unionByRank(0, 1) -> parent[1] = 0, rank[0] = 1
*
* Processing Edge [0, 2]:
* findUPar(0) = 0, findUPar(2) = 2 (Different parents)
* unionByRank(0, 2) -> parent[2] = 0, rank[0] = 1
*
* Processing Edge [1, 2]:
* findUPar(1) = 0, findUPar(2) = 0 (Same parent)
* Redundant edge found! extraEdges = 1
*
* Component Counting:
* Nodes with parent[i] == i:
* i = 0: parent[0] == 0 -> Component 1
* i = 1: parent[1] == 0
* i = 2: parent[2] == 0
* i = 3: parent[3] == 3 -> Component 2
* Total components = 2
*
* Required Edges = components - 1 = 2 - 1 = 1
* Check extraEdges >= reqEdges -> 1 >= 1 (True)
* Output: 1
*
*/
```

---

## 🔑 Key Insights

1. **Edge Count Minimum Requirement**: Any graph with $N$ nodes needs a minimum of $N - 1$ edges to form a single connected component. If $M < N - 1$, graph connection is impossible.
2. **Cycle Detection via DSU**: Whenever an edge connects two nodes that already belong to the same component (`findUPar(u) == findUPar(v)`), that edge is redundant and can be safely moved elsewhere.
3. **Component Bridging**: To bridge $C$ distinct connected components into a single connected graph, exactly $C - 1$ operations/edges are needed.

---

## 🚀 Further Exploration

- [Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)
- [Redundant Connection](https://leetcode.com/problems/redundant-connection/)
- [Disjoint Set Union (DSU) Practice Problems](https://www.geeksforgeeks.org/disjoint-set-data-structures/)

---

## 📌 References

- **GeeksforGeeks Problem Page**: [Min Edge Movements to Connect a Graph](https://www.geeksforgeeks.org/problems/connecting-the-graph/1)
- **Data Structure**: Disjoint Set Union (Union-Find) with Path Compression and Rank Optimization.

---

## 👤 Author

Developed and documented by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags

`graph` `disjoint-set` `dsu` `depth-first-search` `breadth-first-search` `geeksforgeeks` `cpp`