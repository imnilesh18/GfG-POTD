<div align="center">
  
# 🟧 Number of Ways to Arrive at Destination

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/number-of-ways-to-arrive-at-destination/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](#)
[![Accuracy: 61.13%](https://img.shields.io/badge/Accuracy-61.13%25-green?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given an undirected weighted graph with `V` vertices numbered from `0` to `V-1` and `E` edges, represented as a 2D array `edges[][]`, where `edges[i] = [ui, vi, timei]` means that there is an undirected edge between nodes `ui` and `vi` that takes `timei` minutes to reach. 

Your task is to return in **how many ways** you can travel from node `0` to node `V - 1` in the **shortest amount of time**.

---

## 💡 Examples

### Example 1

```text
Input: V = 4, edges[][] = [[0, 1, 2], [1, 2, 3], [0, 3, 5], [1, 3, 3], [2, 3, 4]]
Output: 2
````

<details>
<summary>📖 Example Breakdown</summary>

**Explanation:** The shortest path from `0` to `3` takes `5` minutes. There are exactly two ways to reach node `3` in `5` minutes:

1.  `0 -> 3` (Time: 5)
2.  `0 -> 1 -> 3` (Time: 2 + 3 = 5)

</details>

### Example 2

```text
Input: V = 6, edges[][] = [[0, 2, 3], [0, 4, 2], [0, 5, 7], [2, 3, 1], [2, 5, 5], [5, 3, 3], [5, 1, 4], [1, 4, 1], [4, 5, 5]]
Output: 4
```

<details>
<summary>📖 Example Breakdow</summary>

**Explanation:** The shortest path from `0` to `5` is `7` minutes. Four ways to reach `5` in `7` minutes are:

1.  `0 -> 5` (Time: 7)
2.  `0 -> 4 -> 5` (Time: 2 + 5 = 7)
3.  `0 -> 4 -> 1 -> 5` (Time: 2 + 1 + 4 = 7)
4.  `0 -> 2 -> 3 -> 5` (Time: 3 + 1 + 3 = 7)

</details>

-----

## ⚙️ Constraints

>   - `1 ≤ V ≤ 200`
>   - `V - 1 ≤ edges.size() ≤ V * (V - 1) / 2`
>   - `0 ≤ ui, vi ≤ V - 1`
>   - `1 ≤ timei ≤ 10^5`
>   - `ui != vi`

-----

## 🚀 Solution Approaches

### Dijkstra's Algorithm (Shortest Path + Path Counting)

```cpp
// Intuition: To find the shortest path from a source to a destination, Dijkstra's algorithm is optimal. To also count the number of shortest paths, we can maintain an additional array `paths[]` that stores the number of distinct ways to reach a node in the minimum time found so far.
// Approach: 
// 1. Build an adjacency list representation of the undirected graph.
// 2. Initialize a `minTime` array with infinity and a `paths` array with 0. Set `minTime[0] = 0` and `paths[0] = 1` since we start at node 0.
// 3. Use a min-heap priority queue storing `{time, node}` to process nodes in increasing order of arrival time.
// 4. For each processed node, iterate through its neighbors.
// 5. If a strictly shorter path to a neighbor is found, update its `minTime`, set its `paths` equal to the current node's `paths`, and push it to the queue.
// 6. If a path with the exact same minimum time is found, simply add the current node's `paths` to the neighbor's `paths`.
// 7. Finally, return `paths[V-1]`.
// Time Complexity: O(E log V) where V is the number of vertices and E is the number of edges, typical for Dijkstra's Algorithm using a Priority Queue.
// Space Complexity: O(V + E) to store the adjacency list representing the graph, plus O(V) for the priority queue, distance array, and paths array.

class Solution {
 public:
    /**
     * @brief Counts the number of ways to reach node V-1 from node 0 in the minimum time.
     * @param V The number of nodes (0 to V-1).
     * @param edges A list of edges where edges[i] = {u, v, time}.
     * @return int The number of paths with minimum time to reach V-1.
     */
    int countPaths(int V, vector<vector<int>>& edges) {
        // 1. Build Adjacency List from the edge list
        // adj[u] = {v, time}
        vector<vector<pair<int, int>>> adj(V);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int time = edge[2];
            adj[u].push_back({v, time});
            adj[v].push_back({u, time}); // Assuming an undirected graph based on typical competitive programming problems for this question type
        }

        // min time to reach a node from src (0)
        vector<long long> minTime(V, LLONG_MAX); 
        // number of ways to reach a node from src (0) with minimum cost
        // We use a large prime for modulo operations in similar problems, 
        // but since the original code didn't, we'll stick to a simple int/long long 
        // or assume the constraints prevent overflow for the path count.
        vector<int> paths(V, 0); 
        
        minTime[0] = 0; // Time to reach start node is 0
        paths[0] = 1;   // Base case: 1 way to be at the start

        // Min-heap: {time, node}
        priority_queue<pair<long long, int>, 
                       vector<pair<long long, int>>, 
                       greater<pair<long long, int>>> pq;
        pq.push({0, 0});

        // Use long long for time variables to prevent overflow for large times
        // within the graph traversal.
        
        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();
            long long currentTime = top.first;
            int node = top.second;

            // Optimization: ignore outdated longer paths in the priority queue
            if (currentTime > minTime[node]) continue;

            for (const auto& next : adj[node]) {
                int nextNode = next.first;
                int nextTime = next.second; // Edge time is already an int

                long long newTime = currentTime + nextTime;
                
                // Case 1: Found a shorter path
                if (newTime < minTime[nextNode]) {
                    minTime[nextNode] = newTime;
                    paths[nextNode] = paths[node]; // Inherit ways from current node
                    pq.push({newTime, nextNode});
                } 
                // Case 2: Found a path with the same minimum time
                else if (newTime == minTime[nextNode]) {
                    // Update the count: paths[nextNode] = (paths[nextNode] + paths[node]) % MOD;
                    // For simplicity, we assume no modulo is needed as in the original code.
                    paths[nextNode] = paths[nextNode] + paths[node]; // Add alternative paths
                }
            }
        }

        // Return the number of paths to reach dest (V-1) from src (0) in min time
        return paths[V - 1];
    }
};

/*
*
* Dry Run
* Input: V = 4, edges = [[0, 1, 2], [1, 2, 3], [0, 3, 5], [1, 3, 3], [2, 3, 4]]
* * Initialization: 
* minTime = [0, INF, INF, INF]
* paths = [1, 0, 0, 0]
* PQ = [{0, 0}]
* * Step 1: Pop {0, 0}
* - Neighbor 1 (edge time 2): newTime = 2 < INF. minTime[1] = 2, paths[1] = 1. Push {2, 1}
* - Neighbor 3 (edge time 5): newTime = 5 < INF. minTime[3] = 5, paths[3] = 1. Push {5, 3}
* PQ is now: [{2, 1}, {5, 3}]
*
* Step 2: Pop {2, 1}
* - Neighbor 0 (edge time 2): newTime = 4 > minTime[0]. Ignore.
* - Neighbor 2 (edge time 3): newTime = 5 < INF. minTime[2] = 5, paths[2] = 1. Push {5, 2}
* - Neighbor 3 (edge time 3): newTime = 5 == minTime[3]. paths[3] += paths[1] -> paths[3] = 1 + 1 = 2.
* PQ is now: [{5, 2}, {5, 3}]
*
* Step 3: Pop {5, 2}
* - Neighbor 1 (edge time 3): newTime = 8 > minTime[1]. Ignore.
* - Neighbor 3 (edge time 4): newTime = 9 > minTime[3]. Ignore.
* PQ is now: [{5, 3}]
*
* Step 4: Pop {5, 3}
* - (Destination node, checking neighbors won't find shorter paths back)
* * Output: paths[3] which is 2.
*
*/
```

-----

## 🧠 Key Insights

  - **Dijkstra's Versatility:** Standard Dijkstra gives us the absolute shortest path length. By coupling it with a `paths` counting array, we easily map the shortest graph traversals recursively.
  - **Strict Relaxation:** Whenever we strictly reduce the distance (`newTime < minTime[nextNode]`), it acts as a "reset" for the `paths` array for that node. The number of ways to reach `nextNode` becomes exactly the number of ways to reach the `node` we just came from.
  - **Equivalence Check:** If `newTime == minTime[nextNode]`, we've discovered an *alternative route* of optimal length. Thus, we add `paths[node]` to `paths[nextNode]`.
  - **Optimization:** We ignore any stale distance states popped from the Priority Queue using `if (currentTime > minTime[node]) continue;` to drastically cut down on processing time.

-----

## 🔗 Further Exploration

  - [Dijkstra's Algorithm Implementation](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)
  - [Find the City With the Smallest Number of Neighbors at a Threshold Distance (Leetcode/GFG)](https://www.geeksforgeeks.org/problems/city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/1)
  - [Shortest Path in Directed Acyclic Graph](https://www.geeksforgeeks.org/shortest-path-for-directed-acyclic-graphs/)

-----

## 📚 References

  - **GeeksforGeeks Problem:** [Number of Ways to Arrive at Destination](https://www.geeksforgeeks.org/problems/number-of-ways-to-arrive-at-destination/1)

-----

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

-----

## 🏷️ Tags

  - `Graph`
  - `Shortest Path`
  - `Dijkstra Algorithm`
  - `Dynamic Programming`
  - `Priority Queue`
  - `GeeksforGeeks`