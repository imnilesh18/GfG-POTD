# 🎈 Party in Town

[![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/party-in-town3951/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](#)
[![Accuracy: 50.86%](https://img.shields.io/badge/Accuracy-50.86%25-1ea362?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-027FFF?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📜 Problem Statement

Geek Town has `n` houses numbered from `1` to `n`. Choose a house to host a party such that its distance from its farthest house is as small as possible. Return this minimum possible distance[cite: 1].

The houses are connected by `n - 1` bidirectional roads, forming a tree[cite: 1]. 
The connections are given as an adjacency list `adj`, where `adj[i]` contains all houses directly connected to house `i + 1`[cite: 1]. 

---

## 🛑 Constraints

> - `1 ≤ n ≤ 10^5`[cite: 1]
> - `1 ≤ adj[i][j]`[cite: 1]
> - `adj.size() = n`[cite: 1]

---

## 💡 Examples

### Example 1

```text
Input: adj[][] = [[2], [1, 4, 3], [2], [2]] 
Output: 1
```
> **Explanation:** Party should take place at house number 2. Maximum distance from house number 2 is 1[cite: 1].

<details>
<summary><b>📖 Example Breakdown</b></summary>

1. **Graph Construction**:
   - House 1 connects to House 2.
   - House 2 connects to Houses 1, 4, 3.
   - House 3 connects to House 2.
   - House 4 connects to House 2.
2. **Analysis**: This is a star graph where House 2 is at the center. 
3. **Distance Calculation**: If we host the party at House 2, the distance to any other house (1, 3, or 4) is exactly 1. No other house yields a smaller maximum distance.

</details>

### Example 2

```text
Input: adj[][] = [[2], [1, 3], [4, 2], [3]]
Output: 2
```
> **Explanation:** Party should take place at house number 2 or 3. The minimum distance is 2[cite: 1].

---

## 🛠️ Solution Approaches

### Optimal Approach: Two-BFS to Find Tree Diameter Center

**Intuition:** 
The problem asks us to find a node that minimizes the maximum distance to any other node. In graph theory, this optimal node is known as the **Center of the Tree**. The maximum distance from the center to any leaf node is mathematically equivalent to half of the tree's diameter. By calculating the tree's diameter using the standard Two-BFS method, we can simply return `ceil(diameter / 2)` to get the minimal maximum distance.

```cpp
// Intuition: The optimal house to host the party is the center of the tree. The maximum distance from the tree's center to any leaf is exactly half of the tree's diameter (rounded up). We can find the diameter using two BFS traversals.
// Approach: 1. Run BFS from node 0 to find one endpoint of the diameter. 2. Run a second BFS from this endpoint to find the actual length of the diameter. 3. Return the radius, which is ceil(diameter / 2) calculated as (diameter + 1) / 2.
// Time Complexity: O(n) - We visit every node and edge a constant number of times across two Breadth-First Searches.
// Space Complexity: O(n) - Used for the distance array and the BFS queue.

class Solution {
  public:
    pair<int, int> bfs(vector<vector<int>> &adj, int start) {
        int n = adj.size();

        // distance array initialized to -1 for unvisited nodes
        vector<int> dist(n, -1);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        int farthestNode = start;
        int farthestDist = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int next : adj[node])
            {
                // Convert 1-based house number to 0-based index.
                next--;

                // If node is unvisited, process it
                if (dist[next] == -1)
                {
                    dist[next] = dist[node] + 1;
                    q.push(next);

                    // Update the farthest house found so far.
                    if (dist[next] > farthestDist)
                    {
                        farthestDist = dist[next];
                        farthestNode = next;
                    }
                }
            }
        }

        return {farthestNode, farthestDist};
    }

    int partyHouse(vector<vector<int>> &adj) {
        int n = adj.size();

        // First BFS:
        // Find one endpoint of the tree's diameter.
        pair<int, int> first = bfs(adj, 0);
        int diameterEnd = first.first;

        // Second BFS:
        // Starting from the diameter endpoint,
        // find the actual diameter length.
        pair<int, int> second = bfs(adj, diameterEnd);
        int diameter = second.second;

        // The optimal party house is at the center
        // of the diameter.
        // ceil(diameter / 2) = (diameter + 1) / 2
        return (diameter + 1) / 2;
    }
};

/*
*
* Dry Run
* Input: adj = [[2], [1, 4, 3], [2], [2]]
*
* First BFS (Start at node 0 / house 1):
* queue: [0], dist[0] = 0
* pop 0 -> push 1 (house 2), dist[1] = 1, farthest = 1
* pop 1 -> push 3 (house 4), 2 (house 3), dist[3] = 2, dist[2] = 2, farthest = 2, farthestNode = 3
* return endpoint = 3
*
* Second BFS (Start at endpoint 3 / house 4):
* queue: [3], dist[3] = 0
* pop 3 -> push 1 (house 2), dist[1] = 1, farthest = 1
* pop 1 -> push 0 (house 1), 2 (house 3), dist[0] = 2, dist[2] = 2, farthest = 2
* return diameter = 2
*
* Calculation:
* diameter = 2
* Return (2 + 1) / 2 = 1.
*
*/
```

---

## 🧠 Key Insights

* **Tree Diameter Property:** In an unweighted tree, the longest path between any two nodes is the tree's diameter. A classic algorithm to find this is to pick any node `x`, find the farthest node `y` from `x`, and then find the farthest node `z` from `y`. The path `y -> z` is the diameter.
* **Tree Center Property:** The node that minimizes the maximum distance to all other nodes is located at the exact middle of the tree's diameter. The maximum distance from this center is simply the radius of the tree, which is $\lceil D/2 \rceil$.

---

## 🔎 Further Exploration

* **Dynamic Programming on Trees:** Alternatively, this problem can be solved using "In-Out DP" on trees to compute the maximum distance from each node to all others, though the Two-BFS method is much simpler to implement for unweighted trees.
* **Related Problems:**
  * Find the Center of a Star Graph (LeetCode)
  * Minimum Height Trees (LeetCode)

---

## 🔗 References

* **GeeksforGeeks Problem:** [Party in Town](https://www.geeksforgeeks.org/problems/party-in-town3951/1)
* **Concepts:** Tree Diameter, Breadth-First Search (BFS)

---

## 👨‍💻 Author

**Nilesh**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

[![DFS](https://img.shields.io/badge/Algorithm-DFS-blue)](#)
[![Tree](https://img.shields.io/badge/Data_Structure-Tree-green)](#)
[![BFS](https://img.shields.io/badge/Algorithm-BFS-orange)](#)
[![GeeksForGeeks](https://img.shields.io/badge/Platform-GeeksForGeeks-lightgrey)](#)