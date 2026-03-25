# 🌱 Minimum height roots

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-77.79%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📜 Problem Statement

You are given an undirected graph, which has tree characteristics with `V` vertices numbered from `0` to `V-1` and `E` edges, represented as a 2D array `edges[][]`, where each element `edges[i] = [u, v]` represents an edge from vertex `u` to `v`.

You can choose any vertex as the root of the tree. Your task is to find all the vertices that, when chosen as the root, result in the **minimum possible height** of the tree.

**Note:** The height of a rooted tree is defined as the maximum number of edges on the path from the root to any leaf node.

---

## 🚨 Constraints

- `1 ≤ V ≤ 10^5`
- `0 ≤ E ≤ V-1`
- `0 ≤ edges[i][0], edges[i][1] < V`

---

## 💡 Examples

### Example 1

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/914206/Web/Other/blobid1_1761821734.jpg" alt="Example 1 Initial Graph" />
</div>

**Input:** `V = 5`, `E = 4`, `edges[][] = [[0, 2], [1, 2], [2, 3], [3, 4]]`

**Output:** `[2, 3]`

**Explanation:** If we choose vertices 2 or 3 as the root, the resulting tree has the minimum possible height, which is 2.

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/914206/Web/Other/blobid2_1761821775.jpg" alt="Example 1 Rooted Trees" />
</div>

### Example 2

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/914206/Web/Other/blobid0_1761826368.png" alt="Example 2 Initial Graph" />
</div>

**Input:** `V = 4`, `E = 3`, `edges[][] = [[0, 1], [0, 2], [0, 3]]`

**Output:** `[0]`

**Explanation:** Only vertex 0 as root gives the minimum possible height, which is 1.

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/914206/Web/Other/blobid2_1761826469.jpg" alt="Example 2 Rooted Tree" />
</div>

<details>
<summary>📖 <b>Example Breakdown</b></summary>

**Let's analyze Example 2:**
- We have 4 nodes connected in a star shape where `0` is the center, and `1, 2, 3` are leaves.
- If we pick `1` as the root, the longest path is `1 -> 0 -> 2` (or `0 -> 3`), making the height `2`.
- If we pick the central node `0` as the root, the longest paths are `0 -> 1`, `0 -> 2`, and `0 -> 3`, all having a height of `1`.
- Thus, node `0` provides the minimum possible height.
</details>

---

## 🛠️ Solution Approach

### Kahn's Algorithm / BFS (Trimming Leaves)

**Intuition:**
Choosing a leaf node as the root will naturally result in a tall tree because the distance to the opposite leaves is maximized. Therefore, the best roots must lie at the absolute center of the graph. By repeatedly trimming off the outermost leaf nodes (nodes with only 1 connection/indegree) level by level, we will eventually be left with the most central nodes. A mathematical property of trees is that there can be at most 2 central nodes.

```cpp
// Intuition: The minimum height tree roots will always be the most central nodes of the graph.
// We can find them by iteratively removing leaf nodes (indegree == 1) level by level until 2 or fewer nodes remain.
// Approach: 
// 1. Build an adjacency list and calculate the indegree for each vertex.
// 2. Add all leaf nodes (indegree == 1) to a queue.
// 3. Process the queue level by level, removing leaves and decreasing the indegree of their neighbors.
// 4. If a neighbor's indegree becomes 1, it is a new leaf; push it to the queue.
// 5. Stop when the total number of remaining vertices V is <= 2. The queue holds the answer.
// Time Complexity: O(V) - Building the graph and processing each vertex/edge in BFS takes linear time. (Since E = V-1, O(V+E) simplifies to O(V)).
// Space Complexity: O(V) - Using adjacency list, indegree array, and queue all require linear space.

class Solution {
  public:
    vector<int> minHeightRoot(int V, vector<vector<int>>& edges) {
        unordered_map<int, vector<int>> adj;
        vector<int> indegree(V);
        
        // Build the graph and populate indegrees
        for(auto &edge : edges){
            int u = edge[0];
            int v = edge[1];
            
            indegree[u]++;
            indegree[v]++;
            
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        vector<int> result;
        queue<int> que;
        
        // Push initial leaf nodes (nodes with only 1 connection) into the queue
        for(int i = 0; i < V; i++) {
            if(indegree[i] == 1) {
                que.push(i);
            }
        }
        
        // Trim leaves layer by layer until 2 or fewer central nodes remain
        while(V > 2) {
            int size = que.size();
            V -= size; // Reduce total node count by the number of leaves we are stripping
            
            // Process the current layer of leaves
            while(size--) {
                int u = que.front();
                que.pop();
                
                // Traverse neighbors and strip the leaf connection
                for(int &v : adj[u]) {
                    indegree[v]--;
                    // If a neighbor becomes a leaf, queue it up for the next layer
                    if(indegree[v] == 1) {
                        que.push(v);
                    }
                }
            }
        }
        
        // The remaining nodes are the roots for the minimum height trees
        while(!que.empty()) {
            result.push_back(que.front());
            que.pop();
        }
        
        return result;
    }
};

/*
* Dry Run
* Input: V = 4, edges = [[0, 1], [0, 2], [0, 3]]
* * Graph Generation:
* adj: {0: [1, 2, 3], 1: [0], 2: [0], 3: [0]}
* indegree: [3, 1, 1, 1]
* * Initial Leaves:
* Nodes 1, 2, 3 have indegree == 1.
* Queue: [1, 2, 3]
* * BFS Trimming:
* Loop condition V > 2: (4 > 2 is True)
* size = 3. V becomes 4 - 3 = 1.
* * Processing leaves:
* Pop 1: neighbor 0's indegree becomes 2.
* Pop 2: neighbor 0's indegree becomes 1. Indegree is 1, push 0 to Queue.
* Pop 3: neighbor 0's indegree becomes 0.
* * Next iteration:
* Loop condition V > 2: (1 > 2 is False). Loop terminates.
* * Result Collection:
* Queue contains [0]. Result gets [0].
* * Output: [0]
*/
```

---

## 🧠 Key Insights

1. **Leaf Nodes are Never the Answer:** If you select a leaf node as the root, the path traversing through the center of the graph to the farthest leaf on the other side will yield the maximum possible height. 
2. **Finding the Center:** By progressively snipping away the leaf nodes layer by layer (much like peeling an onion), we naturally converge to the center-most nodes.
3. **Graph Theory Property:** Any tree can have at most **two** centers. This is why our termination condition explicitly checks for `V > 2`. When the remaining node count is 1 or 2, we have found our optimal roots.

---

## 🔗 Further Exploration

- **[Topological Sort (Kahn's Algorithm)](https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)** - Understanding in-degree based graph reductions.
- **[Longest Path in a Directed Acyclic Graph](https://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/)**

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - Minimum height roots](https://www.geeksforgeeks.org/problems/minimum-height-roots/1)

---

## ✍️ Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Graph` `Topological-Sort` `BFS` `GeeksforGeeks` `C++`