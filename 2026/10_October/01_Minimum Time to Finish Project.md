# ⏱️ Minimum Time to Finish Project

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) ![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge) ![Accuracy](https://img.shields.io/badge/Accuracy-64.98%25-green?style=for-the-badge) ![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge) ![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

An IT company is working on a large project consisting of `n` modules[cite: 1]. The given array time required (in months) to complete the `ith` module is stored in the array `duration[]`[cite: 1]. The array `dependencies[][]`, where `dependencies[i] = [u, v]`, indicates that module `v` can be started only after module `u` is completed[cite: 1]. 

Multiple modules can be worked on simultaneously as long as all their dependencies have been completed[cite: 1]. Find the minimum time required to complete the entire project[cite: 1]. If the project cannot be completed due to a cyclic dependency, return `-1`[cite: 1]. A module is never dependent on itself[cite: 1].

## 💡 Examples

### Example 1
```text
Input: duration[] = [10, 20, 30, 10, 30, 20], dependencies[][] = [[5, 2], [5, 0], [4, 0], [4, 1], [2, 3], [3, 1]]
Output: 80
```
<details>
<summary>📖 Example Breakdown</summary>

The Graph of dependency forms this and the project will be completed when Module 1 is completed[cite: 1]. The minimum taken time is `80` months, the maximum taken time is through the path `5 -> 2 -> 3 -> 1` which takes `20 + 30 + 10 + 20`[cite: 1].
</details>

### Example 2
```text
Input: duration[] = [5, 5, 5], dependencies[][] = [[0, 1], [1, 2], [2, 0]]
Output: -1
```
<details>
<summary>📖 Example Breakdown</summary>

There is a cycle in the dependency graph hence the project cannot be completed[cite: 1].
</details>

---

## ⚠️ Constraints

> - `1 ≤ duration.size() ≤ 10^5`[cite: 1]
> - `0 ≤ duration[i] ≤ 10^5`[cite: 1]
> - `0 ≤ m ≤ 2*10^5`[cite: 1]
> - `0 ≤ dependencies[i][j] < 10^5`[cite: 1]

---

## 💻 Solution Approaches

### Depth-First Search (DFS) with Memoization & Cycle Detection

**Intuition & Approach Summary:**  
This problem can be modeled as finding the maximum path sum in a Directed Acyclic Graph (DAG), where nodes are project modules and directed edges are prerequisites. By utilizing Depth-First Search (DFS) alongside memoization, we can efficiently calculate the maximum time required to complete any module's dependency chain. A 3-color state array helps us simultaneously detect cycles (impossible projects).

```cpp
// Intuition: The problem models a Directed Acyclic Graph (DAG) where we need the longest path representing the maximum time to finish all dependent modules. If a cycle exists, completion is impossible.
// Approach: 
// 1. Build an adjacency list `adj` from the given dependencies.
// 2. Iterate through all modules and perform a DFS to find the max completion time.
// 3. Use a `state` array (0 = unvisited, 1 = visiting, 2 = completed) to detect cycles.
// 4. Use a `dp` array to memoize the max time for each node to prevent redundant calculations.
// 5. If a cycle is detected during DFS, flag it and return -1. Otherwise, return the maximum time found.
// Time Complexity: O(n + m) where n is the number of modules and m is the number of dependencies, because we visit each node and edge exactly once during DFS.
// Space Complexity: O(n + m) for the adjacency list representation, plus O(n) for the dp array, state array, and recursive call stack.

class Solution {
  public:
    int dfs(int node, vector<vector<int>> &adj, vector<int> &duration, vector<int> &state, vector<int> &dp, bool &cycle) {

        // Cycle detected: node is currently in the recursion stack
        if (state[node] == 1) {
            cycle = true;
            return 0;
        }

        // Already calculated: return memoized result
        if (state[node] == 2)
            return dp[node];

        // Mark node as currently visiting
        state[node] = 1;

        int maxTime = 0;

        // Traverse all dependent modules to find the longest prerequisite chain
        for (int next : adj[node]) {
            maxTime = max(maxTime, dfs(next, adj, duration, state, dp, cycle));
        }

        // Mark node as completely processed
        state[node] = 2;

        // Total time = duration of current module + max time of its dependencies
        dp[node] = duration[node] + maxTime;

        return dp[node];
    }

    int minTime(vector<int> &duration, vector<vector<int>> &dependencies) {
        int n = duration.size();

        // Build the dependency graph
        vector<vector<int>> adj(n);
        for (auto &edge : dependencies)
            adj[edge[0]].push_back(edge[1]);

        // State array: 0 = unvisited, 1 = currently visiting, 2 = completed
        vector<int> state(n, 0);

        // DP array to memoize completion times
        vector<int> dp(n, 0);

        bool cycle = false;
        int res = 0;

        // Calculate completion time for every module
        for (int i = 0; i < n; i++) {
            res = max(res, dfs(i, adj, duration, state, dp, cycle));
        }

        // If a cycle exists, project cannot be completed
        if (cycle)
            return -1;

        return res;
    }
};

/*
*
* Dry Run
* Input: duration = [5, 5, 5], dependencies = [[0, 1], [1, 2], [2, 0]]
* 
* 1. Build adjacency list: 0 -> 1, 1 -> 2, 2 -> 0.
* 2. dfs(0) starts. state[0] = 1. Visits dependency 1.
* 3. dfs(1) starts. state[1] = 1. Visits dependency 2.
* 4. dfs(2) starts. state[2] = 1. Visits dependency 0.
* 5. dfs(0) is called, but state[0] is already 1 (visiting).
* 6. Cycle detected! cycle = true is set. Returns 0 recursively.
* 7. The main loop finishes. Since cycle == true, minTime returns -1.
*
*/
```

---

## 🔍 Key Insights

1. **DAG Longest Path:** The minimum time to finish all projects when tasks can run in parallel essentially translates to finding the "Longest Path" in a Directed Acyclic Graph. 
2. **Cycle Detection (3-Color Algorithm):** Using three states (unvisited, visiting, completed) is a standard and highly efficient way to detect cycles in a directed graph while simultaneously computing the DP state.
3. **Memoization Safety:** By returning `dp[node]` early if `state[node] == 2`, we guarantee an `O(V + E)` runtime and avoid Time Limit Exceeded (TLE) errors.

---

## 🚀 Further Exploration
- GeeksforGeeks / LeetCode: *Course Schedule* (Similar cycle detection logic)
- GeeksforGeeks / LeetCode: *Course Schedule II* (Topological sorting)
- GeeksforGeeks: *Longest Path in a Directed Acyclic Graph*

---

## 🔗 References
- **GeeksforGeeks Problem:** [Minimum Time to Finish Project](https://www.geeksforgeeks.org/problems/project-manager--141631/1)[cite: 1]

---

## ✍️ Author
👤 **Nilesh Kumar**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#graph` `#dfs` `#dynamic-programming` `#topological-sort` `#geeksforgeeks` `#cpp`