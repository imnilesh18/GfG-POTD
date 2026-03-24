# 📚 Course Schedule I

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/course-schedule-i/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Accuracy-76.79%25-green?style=for-the-badge" alt="Accuracy: 76.79%">
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4">
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-success?style=for-the-badge" alt="License: MIT">
  </a>
</div>

<br>

<div align="center">

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

</div>

---

## 📝 Problem Statement

You are given `n` courses, labeled from `0` to `n - 1`, and a 2D array `prerequisites[][]` where `prerequisites[i] = [x, y]` indicates that we need to take course `y` first if we want to take course `x`.

Find if it is possible to complete all tasks. Return **`true`** if all tasks can be completed, or **`false`** if it is impossible.

---

## 💡 Examples

### Example 1
```text
Input: n = 4, prerequisites[] = [[2, 0], [2, 1], [3, 2]]
Output: true
Explanation: 
To take course 2, you must first finish courses 0 and 1.
To take course 3, you must first finish course 2.
All courses can be completed, for example in the order [0, 1, 2, 3] or [1, 0, 2, 3].
````

### Example 2

```text
Input: n = 3, prerequisites[] = [[0, 1], [1, 2], [2, 0]]
Output: false
Explanation: 
To take course 0, you must first finish course 1. 
To take course 1, you must first finish course 2. 
To take course 2, you must first finish course 0.
Since each course depends on the other, it is impossible to complete all courses.
```

\<details\>
\<summary\>📖 \<b\>Example Breakdown (Walkthrough)\</b\>\</summary\>

Let's break down **Example 2**:

  - `n = 3`, prerequisites: `[0, 1]` (means `1 -> 0`), `[1, 2]` (means `2 -> 1`), `[2, 0]` (means `0 -> 2`).
  - We can view this as a directed graph where each prerequisite rule is a directed edge.
  - Path: `0` depends on `1`, `1` depends on `2`, `2` depends on `0`.
  - This creates a cyclic dependency: `0 -> 2 -> 1 -> 0`.
  - Because you are stuck in a cycle, you can never fulfill the initial prerequisite requirement.
  - Therefore, we cannot complete the courses, and we return `false`.

\</details\>

-----

## ⚠️ Constraints

>   - `1 ≤ n ≤ 10^4`
>   - `0 ≤ prerequisites.size() ≤ 10^5`
>   - `0 ≤ prerequisites[i][0], prerequisites[i][1] < n`
>   - `All prerequisite pairs are unique`
>   - `prerequisites[i][0] ≠ prerequisites[i][1]`

-----

## 🛠️ Solution Approach

### Optimized Approach: Kahn's Algorithm (BFS Topological Sort)

This problem essentially asks us to find if there is a circular dependency among the courses. This translates exactly to **detecting a cycle in a Directed Graph**.
If there's no cycle, it's a Directed Acyclic Graph (DAG), and we can safely find a valid linear order (Topological Sort) to complete all courses. We can implement this using Kahn's Algorithm.

```cpp
// Intuition: The problem models a Directed Graph where courses are nodes and prerequisites are directed edges. If a cycle exists, we can't finish the courses. We use Kahn's Algorithm (Topological Sorting) to detect cycles.
// Approach: 
// 1. Build an adjacency list where `y -> x` means course `y` must be taken before `x`.
// 2. Track the `indegree` (incoming edges) for each course.
// 3. Push all courses with `indegree == 0` into a queue (these have no prerequisites).
// 4. Process the queue: decrement the indegree of neighbors. If a neighbor's indegree becomes 0, push it to the queue.
// 5. Keep a count of processed nodes. If count equals `n`, we successfully traversed all nodes without encountering a cycle.
// Time Complexity: O(n + m), where `n` is the number of courses (vertices) and `m` is the number of prerequisites (edges).
// Space Complexity: O(n + m) to store the adjacency list and the indegree array.

class Solution {
public:
    
    bool topologicalSortCheck(unordered_map<int, vector<int>> &adj, int n, vector<int> &indegree) {
        queue<int> que;
        
        int count = 0; // Tracks the number of successfully completed courses
        
        // Push all nodes with 0 indegree (independent courses) into the queue
        for(int i = 0; i < n; i++) {
            if(indegree[i] == 0) {
                count++;
                que.push(i);
            }
        }
        
        // Process courses level by level
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            
            // Decrease the indegree of dependent courses
            for(int &v : adj[u]) {
                indegree[v]--;
                
                // If a course has no more pending prerequisites, add to queue
                if(indegree[v] == 0) {
                    count++;
                    que.push(v);
                }
            }
        }
        
        if(count == n) // I was able to visit all the nodes (courses)
            return true; // i.e I was able to finish all courses
        
        return false; // means there was a cycle and I couldn't complete all the courses
    }
    
    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> adj;
        
        vector<int> indegree(n, 0); // kahn's algo array
        
        for(auto &vec : prerequisites) {
            int x = vec[0];
            int y = vec[1];
            
            // y ---> x (Course y must be completed before Course x)
            adj[y].push_back(x);
            
            // arrow going to x
            indegree[x]++;
            
        }
        
        return topologicalSortCheck(adj, n, indegree);
    }
};

/*
*
* Dry Run
*
* Input: n = 4, prerequisites = [[2, 0], [2, 1], [3, 2]]
*
* Graph (Adjacency List):
* 0 -> [2]
* 1 -> [2]
* 2 -> [3]
* 3 -> []
* * Indegrees: 
* 0: 0, 1: 0, 2: 2, 3: 1
* * Queue Initialization: 
* indegree[0] == 0 -> push(0), count = 1
* indegree[1] == 0 -> push(1), count = 2
* Queue: [0, 1]
* * Processing:
* - Pop 0. Neighbors of 0: [2]. Decrement indegree[2] to 1. Queue: [1]
* - Pop 1. Neighbors of 1: [2]. Decrement indegree[2] to 0. 
* -> indegree[2] == 0, push(2), count = 3. Queue: [2]
* - Pop 2. Neighbors of 2: [3]. Decrement indegree[3] to 0.
* -> indegree[3] == 0, push(3), count = 4. Queue: [3]
* - Pop 3. Neighbors of 3: []. Queue: []
* * Result:
* count (4) == n (4). Returns true.
*
*/
```

-----

## 🔍 Key Insights

  - **Directed Acyclic Graph (DAG) Property:** The prerequisite relationships form a directed graph. The problem guarantees success only if no circular dependency exists, making it a classic DAG cycle detection problem.
  - **Kahn's Algorithm:** It systematically removes nodes with `0` incoming edges (tasks requiring no dependencies) and updates the dependencies of remaining tasks. If any tasks remain unvisited after this process, a cycle exists.
  - **Why it works:** Courses involved in a cycle will never drop their `indegree` to zero. Consequently, they will never be pushed to the queue, and our `count` will fall short of `n`.

-----

## 🚀 Further Exploration

  - **Course Schedule II:** Instead of just checking if completing the courses is possible, return the exact order to take the courses.
  - **Alien Dictionary:** Another classic topological sort problem involving character precedence.
  - **Cycle Detection using DFS:** Try solving the same problem by tracking states (`unvisited`, `visiting`, `visited`) in a standard Depth First Search.

-----

## 🔗 References

  - **GeeksforGeeks Problem:** [Course Schedule I](https://www.geeksforgeeks.org/problems/course-schedule-i/1)
  - **Topological Sorting:** [Kahn's Algorithm](https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)

-----

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)