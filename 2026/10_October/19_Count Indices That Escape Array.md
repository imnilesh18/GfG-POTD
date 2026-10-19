# 🪨 Count Indices That Escape Array

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy: 53.74%](https://img.shields.io/badge/Accuracy-53.74%25-blue?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-success?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]`, where `arr[i]` represents the exact number of steps to move from index `i`. An index is considered **good** if repeatedly following the jumps eventually takes you outside the array. Otherwise, if the jumps result in an infinite loop, the index is considered **bad**.

*   A positive value indicates a move to the right.
*   A negative value indicates a move to the left.
*   A `0` value means no move and is considered bad.

**Task:** Return the number of good indices.

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [2, 3, -1, 2, -2, 4, 1]
Output: 3
Explanation: 
Indices 3, 5, and 6 are good because their jump sequences eventually leave the array. 
Indices 1, 2, and 4 form a cycle, while index 0 eventually enters this cycle through index 2. 
Hence, the total number of good indices is 3.
```

<details>
<summary>📖 Example Breakdown</summary>

*   **Index 0 (`2`)**: Jumps to index 2 (`-1`) -> jumps to index 1 (`3`) -> jumps to index 4 (`-2`) -> jumps to index 2 (`-1`). **Cycle detected!** (Bad)
*   **Index 3 (`2`)**: Jumps to index 5 (`4`) -> jumps to index 9. **Out of bounds!** (Good)
*   **Index 5 (`4`)**: Jumps to index 9. **Out of bounds!** (Good)
*   **Index 6 (`1`)**: Jumps to index 7. **Out of bounds!** (Good)

Total good indices = 3.
</details>

### Example 2

```text
Input: arr[] = [1, 0, -3, 0, -5, 0]
Output: 2
Explanation: 
Indices 2 and 4 are good because their jumps take them outside the array. 
Indices 1, 3, and 5 are bad because their jumps are zero. 
Index 0 is also bad because it jumps to index 1, which is a dead end. 
Hence, the total number of good indices is 2.
```

---

## ⚠️ Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `-10^5 ≤ arr[i] ≤ 10^5`

---

## 🚀 Solution Approaches

### Optimized Approach: Depth First Search (DFS) with Memoization / Cycle Detection

```cpp
// Intuition: The problem can be modeled as a directed graph where each index has an edge to `i + arr[i]`. We need to find nodes that lead out of bounds and avoid nodes that lead to a cycle or a 0-jump. DFS with state tracking allows us to detect cycles and memorize results to avoid redundant calculations.
// Approach:
// 1. Initialize a `state` array to track the status of each index (0: unvisited, 1: visiting, 2: good, 3: bad).
// 2. Iterate through each unvisited index and begin a traversal.
// 3. Track the current path. If we jump out of bounds, the path is good.
// 4. If we hit a node currently in our path (state 1), a cycle is detected, so the path is bad.
// 5. If we hit an already processed node (state 2 or 3), inherit its result to save time.
// 6. Backtrack and update the state of all nodes visited in the current path.
// 7. Finally, count and return the number of indices marked as good (state 2).
// Time Complexity: O(n) because each index is visited and processed at most once due to the state memoization.
// Space Complexity: O(n) for the state array and the path vector used during the graph traversal.

class Solution {
public:
    int goodIndices(vector<int> &arr) {
        int n = arr.size();

        // State array to keep track of each index's status:
        // 0 = unvisited
        // 1 = currently visiting (in the current path)
        // 2 = good (eventually escapes)
        // 3 = bad (ends in a cycle or 0)
        vector<int> state(n, 0); 

        int goodCount = 0;

        for (int i = 0; i < n; ++i) {
            // Only process unvisited nodes
            if (state[i] == 0) {
                int curr = i;
                vector<int> path; // To store the sequence of jumps
                bool isGood = false;

                while (true) {
                    // Condition 1: Escaped the array -> Good path!
                    if (curr < 0 || curr >= n) {
                        isGood = true;
                        break;
                    }

                    // Condition 2: Hit a node currently in our path -> Cycle detected -> Bad path!
                    if (state[curr] == 1) {
                        isGood = false;
                        break;
                    }

                    // Condition 3: Hit a previously processed node -> Inherit its result
                    if (state[curr] == 2) {
                        isGood = true;
                        break;
                    }
                    if (state[curr] == 3) {
                        isGood = false;
                        break;
                    }

                    // Mark as currently visiting and add to path
                    state[curr] = 1;
                    path.push_back(curr);

                    // Move to the next index
                    curr = curr + arr[curr];
                }

                // Backtrack and update the state of all nodes visited in the current path
                for (int node : path) {
                    state[node] = isGood ? 2 : 3;
                }
            }
        }

        // Count all good indices
        for (int i = 0; i < n; ++i) {
            if (state[i] == 2) {
                goodCount++;
            }
        }

        return goodCount;
    }
};

/*
*
* Dry Run
* Input: arr[] = [2, 3, -1, 2, -2, 4, 1]
* n = 7, state = [0, 0, 0, 0, 0, 0, 0]
*
* i = 0: path=[0], curr=2
*        path=[0, 2], curr=1
*        path=[0, 2, 1], curr=4
*        path=[0, 2, 1, 4], curr=2 -> state[2]==1 (Cycle) -> isGood=false
*        Update states: state[0, 2, 1, 4] = 3 (bad)
*
* i = 1, 2: state != 0, skip.
*
* i = 3: path=[3], curr=5
*        path=[3, 5], curr=9 -> out of bounds -> isGood=true
*        Update states: state[3, 5] = 2 (good)
*
* i = 4, 5: state != 0, skip.
*
* i = 6: path=[6], curr=7 -> out of bounds -> isGood=true
*        Update states: state[6] = 2 (good)
*
* Count state == 2: Indices 3, 5, 6 are good.
* Return 3.
*
*/
```

---

## 🧠 Key Insights
- **Graph Traversal Modeling:** The array jumps act exactly like directed edges in a graph.
- **Cycle Detection:** By marking nodes as "visiting" (state 1) during the current path, any encounter with a state 1 node immediately confirms an infinite loop.
- **Memoization:** Storing the final result (good or bad) of a node prevents recalculating paths that merge into already explored territory, optimizing the time complexity to `O(n)`.

---

## 🔍 Further Exploration
- Cycle Detection in Directed Graphs
- Jump Game (LeetCode / GFG)
- Linked List Cycle Detection (Floyd’s Cycle-Finding Algorithm)

---

## 🔗 References
- **Original Problem:** [GeeksforGeeks - Good Stones](https://www.geeksforgeeks.org/problems/good-stones--170647/1)

---

## 👤 Author
**Nilesh Kumar**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
- `Greedy`
- `Dynamic Programming`
- `Graph`
- `DFS`
- `GeeksforGeeks`