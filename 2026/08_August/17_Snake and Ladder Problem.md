# 🐍🪜 Snake and Ladder Problem

<div align="center">
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/snake-and-ladder-problem4816/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-34.65%25-brightgreen?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](#)

</div>

<div align="center">
  
**⚠️ Educational Use Only**
  
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given an integer `n` such that there is an `n × n` Snakes and Ladders board with cells numbered from `1` to `n*n`, find the **minimum number of dice throws** required to reach cell `n*n` starting from cell `1`. 

You are given two arrays of even lengths:
*   `lad[]`: where each pair `(lad[2*i], lad[2*i + 1])` represents the start and end of a **ladder**.
*   `sn[]`: where each pair `(sn[2*i], sn[2*i + 1])` represents the start and end of a **snake**.

If you land on the start cell of a snake or ladder, you must immediately move to its corresponding end cell. You have complete control over the outcome of each dice throw (i.e., in a single move, you can move forward by any number of cells from 1 to 6). 

If it is impossible to reach cell `n*n`, return `-1`.

---

## 💡 Examples

### Example 1
```text
Input: n = 6, lad[] = [3, 22, 5, 8, 11, 35, 20, 32], sn[] = [17, 4, 19, 7, 34, 1, 21, 9]
Output: 3
Explanation: For the 6 × 6 board, the minimum number of dice throws needed to reach cell 36 from cell 1 is 3.
One optimal path is:
1. Throw 4 to move from 1 to 5, then take the ladder to 8.
2. Throw 3 to move from 8 to 11, then take the ladder to 35.
3. Throw 1 to move from 35 to 36.
So the destination is reached in 3 dice throws.
```

### Example 2
```text
Input: n = 3, lad[] = [2, 8], sn[] = [7, 3]
Output: 2
Explanation: For the 3 × 3 board, the minimum number of dice throws needed to reach cell 9 from cell 1 is 2.
One optimal path is:
1. Throw 1 to move from 1 to 2, then take the ladder to 8.
2. Throw 1 to move from 8 to 9.
So the destination is reached in 2 dice throws.
```

<details>
<summary><b>📖 Example Breakdown (Example 2)</b></summary>
<br>

* **Target:** Reach cell 9 starting from cell 1.
* **Ladders:** `2 -> 8`
* **Snakes:** `7 -> 3`
* **Move 1:** Start at `1`, roll a `1`. Land on `2`. Ladder pushes you to `8`.
* **Move 2:** Start at `8`, roll a `1`. Land on `9`.
* **Result:** Reached the end in exactly 2 optimized rolls!

</details>

---

## ⚠️ Constraints

> * `1 ≤ n ≤ 10^3`
> * `1 ≤ lad.size(), sn.size(), lad[i], sn[i] ≤ n^2`

---

## 🚀 Solution Approaches

### Optimized Approach: Breadth-First Search (BFS)

```cpp
// Intuition: The problem can be represented as an unweighted directed graph where cells are nodes and dice rolls are edges. Shortest path in an unweighted graph is optimally found using Breadth-First Search (BFS).
// Approach: 
// 1. Create a `moves` array to map start points of snakes and ladders to their end points.
// 2. Initialize a BFS queue storing pairs of {position, dice_throws} and start from cell 1.
// 3. Mark cells as visited to avoid cycles.
// 4. For each cell, simulate all 6 possible dice throws.
// 5. If a next cell has a snake or ladder, take it. Push the final destination to the queue.
// 6. Return the distance when the destination cell (n * n) is reached.
// Time Complexity: O(n^2) where n^2 is the total number of cells. Each cell is visited at most once during BFS.
// Space Complexity: O(n^2) to store the board transformations (moves array), visited array, and the BFS queue.

class Solution {
  public:
    int minThrows(int n, vector<int>& lad, vector<int>& sn) {
        
         // Array to store board transformations (snakes and ladders)
         vector<int> moves(n * n + 1, -1);
         // Array to keep track of visited cells
         vector<bool> vis(n * n + 1, false);

         // Store all ladders: start to end
         for (int i = 0; i < (int)lad.size(); i += 2) {
             moves[lad[i]] = lad[i + 1];
         }
         // Store all snakes: start to end
         for (int i = 0; i < (int)sn.size(); i += 2) { 
             moves[sn[i]] = sn[i + 1];
         }

         // BFS queue storing {current_cell, dice_throws}
         queue<pair<int, int>> q;
         q.push({1, 0});
         vis[1] = true;

         pair<int, int> cur;

         while (!q.empty()) {
             cur = q.front();
             q.pop();

             int pos = cur.first;
             int dist = cur.second;

             // If we reached the final cell, return the minimum throws
             if (pos == n * n)
             {
                 return dist;
             }

             // Try all possible dice outcomes from 1 to 6
             for (int nxt = pos + 1; nxt <= pos + 6 && nxt <= n * n; nxt++) {
                 // If the cell hasn't been visited yet
                 if (!vis[nxt]) {
                     vis[nxt] = true;

                     // Determine actual destination (check for snake/ladder)
                     int dest = (moves[nxt] == -1) ? nxt : moves[nxt];
                     q.push({dest, dist + 1});
                 }
             }
         }

         // If destination is unreachable
         return -1;
     }
};

/*
*
* Dry Run
*
* Input: n = 3, lad = [2, 8], sn = [7, 3]
* Board Size: 9 cells. 
* Initialization: moves[2] = 8, moves[7] = 3.
* 
* Step 1: Queue = [{1, 0}], vis[1] = true
* Step 2: Pop {1, 0}. Generate next moves (dice 1 to 6):
*         - Roll 1 (nxt = 2): moves[2] is 8 (Ladder!). Push {8, 1}, vis[2] = true
*         - Roll 2 (nxt = 3): moves[3] is -1. Push {3, 1}, vis[3] = true
*         - Roll 3 (nxt = 4): moves[4] is -1. Push {4, 1}, vis[4] = true
*         - Roll 4 (nxt = 5): moves[5] is -1. Push {5, 1}, vis[5] = true
*         - Roll 5 (nxt = 6): moves[6] is -1. Push {6, 1}, vis[6] = true
*         - Roll 6 (nxt = 7): moves[7] is 3 (Snake!). Push {3, 1}, vis[7] = true
* Step 3: Pop {8, 1}. Generate next moves:
*         - Roll 1 (nxt = 9): moves[9] is -1. Push {9, 2}, vis[9] = true
* Step 4: Next pops are {3, 1}, {4, 1}, etc. 
* Step 5: Eventually Pop {9, 2}. pos == 9 (n*n). Target reached!
* Output: 2
*/
```

---

## 🧠 Key Insights

* **Graph Conversion:** Treat the board as a graph where each cell is a node. The edges are the 6 possible dice rolls. Unweighted graph shortest-path problems are best solved using **BFS**.
* **Visited Array:** Marking cells as visited prevents infinite loops (like going up a ladder, falling down a snake, and repeating).
* **Pre-computation:** The `moves` array maps out all transformations in `O(1)` time during the traversal, keeping the BFS logic clean.

---

## 🔭 Further Exploration

* **Related Problems:**
  * Minimum Steps to Reach Target by a Knight (GFG)
  * Word Ladder (GFG / LeetCode)
  * Shortest Path in an Unweighted Graph (GFG)

---

## 🔗 References

* **Problem Link:** [Snake and Ladder Problem on GeeksforGeeks](https://www.geeksforgeeks.org/problems/snake-and-ladder-problem4816/1)
* **Algorithm:** [Breadth-First Search (BFS)](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Dynamic Programming` `#DFS` `#Graph` `#BFS` `#GeeksForGeeks` `#Zoho` `#Flipkart` `#Amazon` `#Microsoft`
