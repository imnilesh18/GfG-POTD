# 🌳 Count Tree Paths With Limited Max Edge Weight

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/possible-paths--141628/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty: Hard" />
    <img src="https://img.shields.io/badge/Accuracy-71.75%25-green?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
    <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📜 Problem Statement

Given a weighted tree with `n` nodes, numbered from `1` to `n` and `n - 1` edges, where each edge is represented as `[u, v, w]` indicating an edge between nodes `u` and `v` with weight `w`.

You are also given an array `queries[]`, where each `queries[i]` represents a maximum allowed edge weight.

For each query `x`, find the number of distinct paths in the tree such that the maximum edge weight along the path is **less than or equal to** `x`.

Return an array containing the number of valid paths for each query.

**Note:**
* A path from node `u` to node `v` and the path from node `v` to node `u` are considered the same path.
* A path must contain at least one edge. A path from a node to itself is not considered.

---

## 💡 Examples

### Example 1
```text
Input: n = 3, edges[][] = [[1, 2, 1], [2, 3, 4]], queries[] = [3]
Output: [1]
Explanation:
For x = 3, only the edge [1, 2, 1] has weight less than or equal to 3.
Therefore, the only valid path is: 1 -> 2
The path 1 -> 3 contains an edge of weight 4, so it is not valid.
Hence, the answer is 1.
```

### Example 2
```text
Input: n = 7, edges[][] = [[1, 2, 3], [2, 3, 1], [2, 4, 9], [3, 6, 7], [3, 5, 8], [5, 7, 4]], queries[] = [1, 3, 5]
Output: [1, 3, 4]
Explanation: 
For x = 1, only the edge [2, 3, 1] satisfies the condition. Valid path: 2 -> 3. Answer: 1.
For x = 3, edges [2, 3, 1] and [1, 2, 3] can be used. Valid paths: 1 -> 2, 2 -> 3, 1 -> 3. Answer: 3.
For x = 5, edges with weights 1, 3, and 4 can be used. Valid paths: 1 -> 2, 2 -> 3, 1 -> 3, 5 -> 7. Answer: 4.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>
<br>

1. **Graph Setup:** Nodes 1, 2, and 3. Edges: (1-2, weight 1), (2-3, weight 4).
2. **Query `x = 3`**: We can only traverse edges with weight $\le 3$.
3. **Valid Edges**: Only (1-2, weight 1) is valid.
4. **Connected Components**: `[1, 2]` form a component of size 2. `[3]` is a component of size 1.
5. **Paths**: Within the component `[1, 2]`, we can form $(2 \times 1) / 2 = 1$ path.
6. **Result**: `[1]`

</details>

---

## ⚠️ Constraints

> - $2 \le n \le 10^4$
> - $1 \le queries.size() \le 10^4$
> - $0 \le queries[i] \le 10^5$
> - $edges.size() = n - 1$
> - $edges[i].size() = 3$
> - $1 \le edges[i][0], edges[i][1] \le n$
> - $edges[i][0] \neq edges[i][1]$
> - $0 \le edges[i][2] \le 10^5$

---

## 🛠️ Solution Approaches

### Optimized Approach (Disjoint Set Union / Offline Queries)
By sorting the edges by weight in ascending order, we can dynamically build the tree components using Disjoint Set Union (DSU). Whenever we join two previously disconnected components of size $S_a$ and $S_b$, we inherently create $S_a \times S_b$ new valid paths. We map each weight limit to the total number of paths generated up to that weight, allowing us to answer any query in $O(\log N)$ time using binary search.

```cpp
// Intuition: To find the number of paths where the max edge weight is <= x, process edges in ascending order of their weights. When an edge connects two disjoint components, every node in one component can now reach every node in the other component, creating (sizeA * sizeB) new valid paths.
// Approach: 
// 1. Sort all edges based on their weights in ascending order.
// 2. Use a Disjoint Set Union (DSU) structure to keep track of connected components and their sizes.
// 3. Iterate through the sorted edges. For edges with the same weight, union their respective components and add (size of component A * size of component B) to the total paths.
// 4. Store the total accumulated paths in a map/tree structure where the key is the edge weight.
// 5. For each query, use binary search (upper_bound) on the map to find the maximum valid paths for the given weight limit.
// Time Complexity: O(N log N + Q log N) where N is the number of nodes and Q is queries. Sorting edges takes O(N log N). DSU operations take near O(1). Answering each query takes O(log N) using the map.
// Space Complexity: O(N) to store the parent and size arrays for the DSU, and the map for storing cumulative paths per weight.

class Solution {
  public:
    int ans;

    // Find the representative of a set (with path compression).
    int root(int x, vector<int> &parent) {
        if (parent[x] == x)
            return x;

        return parent[x] = root(parent[x], parent);
    }

    // Union two components and accumulate the newly formed paths.
    void Union(int a, int b, vector<int> &parent, vector<int> &sz) {
        int ra = root(a, parent);
        int rb = root(b, parent);

        // Already in the same component.
        if (ra == rb)
            return;

        // Union by size to keep the tree flat.
        if (sz[ra] < sz[rb])
            swap(ra, rb);

        // Every node in one component can form a path
        // with every node in the other component.
        ans += sz[ra] * sz[rb];

        parent[rb] = ra;
        sz[ra] += sz[rb];
    }

    vector<int> maximumWeight(int n, vector<vector<int>> edges, vector<int> &queries) {
        ans = 0;

        vector<int> parent(n + 1);
        vector<int> sz(n + 1, 1); // Initially, every node is a component of size 1.

        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }

        // Store {weight, u, v}.
        vector<array<int, 3>> wt;

        for (auto &e : edges) {
            wt.push_back({e[2], e[0], e[1]});
        }

        // Sort edges by weight in ascending order.
        sort(wt.begin(), wt.end());

        // weight -> number of valid paths
        // whose maximum edge weight is <= weight.
        map<int, int> mp;

        int i = 0;

        while (i < (int)wt.size()) {

            int weight = wt[i][0];

            // Process all edges having the exact same weight together.
            while (i < (int)wt.size() && wt[i][0] == weight) {

                int u = wt[i][1];
                int v = wt[i][2];

                Union(u, v, parent, sz);

                i++;
            }

            // Store the cumulative answer after processing
            // all edges up to this current weight.
            mp[weight] = ans;
        }

        vector<int> res;
        res.reserve(queries.size());

        // Process every query using binary search.
        for (int x : queries) {

            // Find the first weight strictly greater than x.
            auto it = mp.upper_bound(x);

            if (it == mp.begin()) {
                // If the first element is already greater, no paths are valid.
                res.push_back(0);
            }
            else {
                // Step back to the largest weight <= x
                --it;
                res.push_back(it->second);
            }
        }

        return res;
    }
};

/*
*
* Dry Run
*
* Input: n = 3, edges = [[1, 2, 1], [2, 3, 4]], queries = [3]
* 
* 1. Initialize DSU: parent = [0, 1, 2, 3], sz = [1, 1, 1, 1], ans = 0
* 2. Sort edges by weight: [[1, 1, 2], [4, 2, 3]] 
* 3. Process edge {1, 1, 2}:
*    - Union(1, 2): sz[1]=1, sz[2]=1. New paths = 1 * 1 = 1. ans = 0 + 1 = 1.
*    - sz[1] becomes 2. parent[2] = 1.
*    - mp[1] = 1.
* 4. Process edge {4, 2, 3}:
*    - Union(2, 3): root(2)=1, root(3)=3. sz[1]=2, sz[3]=1. New paths = 2 * 1 = 2. ans = 1 + 2 = 3.
*    - sz[1] becomes 3. parent[3] = 1.
*    - mp[4] = 3.
* 5. Process queries:
*    - query x = 3. upper_bound(3) returns iterator to key 4.
*    - Decrement iterator -> points to key 1. mp[1] = 1.
*    - res pushes 1.
* 
* Output: [1]
*
*/
```

---

## 🧠 Key Insights
* **Combinatorics in Graphs:** When connecting two disconnected components of sizes $A$ and $B$, the number of distinct node pairs (paths) created is strictly $A \times B$. 
* **Offline Query Processing Concept:** Instead of running a traversal for every single query, computing the graph state progressively based on weight limits saves massive amounts of time.
* **Map upper_bound Magic:** By storing the discrete threshold points in a `std::map`, answering continuous range limits becomes a simple $O(\log N)$ binary search operation.

---

## 🚀 Further Exploration
* **Related GeeksforGeeks Problems:** 
  * "Number of connected components"
  * "Kruskal's Minimum Spanning Tree"
* **Follow-up Question:** How would you solve this if you were required to process the queries *online* dynamically (without sorting them beforehand)?

---

## 📚 References
* [GeeksforGeeks: Possible Paths](https://www.geeksforgeeks.org/problems/possible-paths--141628/1)
* [Disjoint Set Union (DSU)](https://www.geeksforgeeks.org/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/)

---

## 👨‍💻 Author

* **[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#dynamic-programming` `#union-find` `#graphs` `#tree` `#geeksforgeeks` `#hard`