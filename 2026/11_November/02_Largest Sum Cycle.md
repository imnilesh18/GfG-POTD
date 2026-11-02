# ♻️ Largest Sum Cycle

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

## 📝 Problem Statement

Return the maximum cycle sum in a given directed graph. If there is no cycle, return `-1`. The graph is represented by an array `edge[]` where `edge[i]` indicates a directed edge from node `i` to node `edge[i]`. If `edge[i] == -1`, there is no outgoing edge from node `i`.

## 📖 Examples

### Example Breakdown
<details>
<summary>View Walkthrough</summary>

**Input:** `edge[] = [1, 2, 0, -1]`
**Output:** `3`

**Explanation:** 
- Node 0 points to 1.
- Node 1 points to 2.
- Node 2 points to 0.
- Node 3 points nowhere (-1).
There is only one cycle in the graph: `0 -> 1 -> 2 -> 0`. 
The sum of the cell indices in that cycle = `0 + 1 + 2 = 3`.
</details>

**Input:** `edge[] = [2, 0, -1, 2]`
**Output:** `-1`
**Explanation:** There is no cycle in the graph. The edges are `1 -> 0 -> 2 <- 3`. Node 2 has no outgoing edge, so no cycle exists.

## ⚠️ Constraints

> - `2 ≤ edge.size() ≤ 10^5`
> - `-1 ≤ edge[i] < edge.size()`
> - `edge[i] != i`

## 💻 Solution Approach

**Brief Intuition:**
We can use Kahn's Algorithm (Topological Sorting) to strip away all nodes that are not part of any cycle. Nodes with an indegree of 0 can never be in a cycle. Once we remove them and their outgoing edges, the only nodes left in the graph with an indegree > 0 will be the ones forming cycles. We then traverse these remaining nodes to calculate the sum of each cycle and find the maximum.

```cpp
// Intuition: Strip away non-cycle nodes using Kahn's algorithm, then evaluate remaining cycles.
// Approach: 
// 1. Calculate indegree for all nodes.
// 2. Use a queue to process and remove all nodes with indegree 0 (and their cascading effects).
// 3. Traverse the remaining unvisited nodes (which form cycles) to calculate their sum.
// 4. Return the maximum cycle sum found.
// Time Complexity: O(n) where n is the number of nodes. Each node is processed at most a few times.
// Space Complexity: O(n) for the indegree array, queue, and visited array.

class Solution {
  public:
    int largestSumCycle(vector<int> &edge) {
        int n = edge.size();
        vector<int> indegree(n, 0);

        // Step 1: Calculate the indegree of every cell
        for (int i = 0; i < n; i++) {
            if (edge[i] != -1) {
                indegree[edge[i]]++;
            }
        }

        queue<int> q;

        // Step 2: Add all cells with indegree 0 to the queue
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) { 
                q.push(i);
            }
        }

        // Step 3: Remove all cells that cannot be part of a cycle (Kahn's BFS)
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            int next = edge[node];

            if (next != -1) {
                indegree[next]--;
                // If indegree becomes 0, it cannot be part of a cycle
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        long long ans = -1;
        vector<int> visited(n, 0);

        // Step 4: Traverse the remaining cells to find all cycles and their sums
        for (int i = 0; i < n; i++) {
            // If indegree > 0, it's part of a cycle
            if (indegree[i] > 0 && visited[i] == 0) {
                long long sum = 0;
                int node = i;

                // Traverse the cycle and calculate the sum
                while (visited[node] == 0) {
                    visited[node] = 1;
                    sum += node;
                    node = edge[node];
                }
                
                // Update max cycle sum
                ans = max(ans, sum);
            }
        }

        return (int)ans;
    }
};

/*
* Dry Run
* Input: edge[] = [1, 2, 0, -1]
* n = 4
* indegree calculation:
* i=0: edge[0]=1 -> indegree[1]=1
* i=1: edge[1]=2 -> indegree[2]=1
* i=2: edge[2]=0 -> indegree[0]=1
* i=3: edge[3]=-1 -> skipped
* indegree[] = [1, 1, 1, 0]
* 
* Queue processing:
* q pushes 3 (indegree[3] == 0).
* pop 3. next = edge[3] = -1. queue becomes empty.
* 
* Cycle summation:
* i=0: indegree[0]=1, visited[0]=0.
* node = 0, sum = 0.
* visited[0] = 1, sum = 0, node = edge[0] = 1.
* visited[1] = 1, sum = 1, node = edge[1] = 2.
* visited[2] = 1, sum = 1+2 = 3, node = edge[2] = 0.
* visited[0] is 1, loop ends.
* ans = max(-1, 3) = 3.
* Nodes 1 and 2 are already visited, so loop skips them. Node 3 has indegree 0.
* Return ans = 3.
*/

```

## 🧠 Key Insights

* **Topological Sort (Kahn's Algorithm):** By iteratively removing nodes with an indegree of 0, we effectively "trim the branches" of the graph. Any nodes remaining after this process are guaranteed to be part of a cycle.
* **Efficient Cycle Detection:** Since each node has at most one outgoing edge, the cycles are disjoint or simple loops. Once the non-cycle nodes are removed, a simple DFS/while-loop efficiently sums up the cycle components without the risk of overlapping complex sub-graphs.

## 🔗 References

* **Problem Link:** [Largest Sum Cycle on GeeksforGeeks](https://www.geeksforgeeks.org/problems/largest-sum-cycle--170645/1)

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

## 🏷️ Tags

* `Graph`
* `Topological Sort`
* `Cycle Detection`
* `GeeksforGeeks`