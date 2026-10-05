<div align="center">

# 🌐 Your Social Network

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-68.37%25-10B981?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-0ea5e9?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Geek is creating a social networking site called Geeksbook with `n` users numbered from `1` to `n`. Each user `i` (where $2 \le i \le n$) has exactly one friend, and that friend must have a strictly smaller user number than `i`. User `1` has no friend. 

The friends of users `2` to `n` are given in an array `arr[]` of size `n - 1`, where:
* `arr[0]` is the friend of user 2.
* `arr[1]` is the friend of user 3.
* ...
* `arr[i - 2]` is the friend of user `i`.

The relationship is one-way. A user can reach another user by repeatedly following their friend's link. For every user `i` from `2` to `n`, find all users `j` ($1 \le j < i$) that can be reached from `i`. For every reachable pair `(i, j)`, create an array `[i, j, k]` where:
* `i` is the starting user.
* `j` is the reachable user.
* `k` is the number of links that must be followed to reach `j` from `i`.

The result should contain these arrays in the following order:
1. Process users `i` from `2` to `n`.
2. For each user `i`, consider users `j` from `1` to `i - 1` in **increasing order**.
3. Include `[i, j, k]` only if `j` is reachable from `i`.

Return a 2D array containing information about all reachable pairs.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [1, 2]
Output: [[2, 1, 1], [3, 1, 2], [3, 2, 1]]
Explanation: 
The links are 2 → 1 and 3 → 2. 
- User 2 can reach user 1 in 1 link. 
- User 3 can reach user 1 in 2 links. 
- User 3 can reach user 2 in 1 link.
```

### Example 2
```text
Input: arr[] = [1, 1]
Output: [[2, 1, 1], [3, 1, 1]]
Explanation: 
The links are 2 → 1 and 3 → 1. 
- User 2 can reach user 1 in 1 link. 
- User 3 can reach user 1 in 1 link.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1 Walkthrough)</b></summary>

Given `arr[] = [1, 2]`, it means:
*   Total users `n` = 3 (since `arr.size()` is 2).
*   User 2's friend is `arr[0]` = 1.
*   User 3's friend is `arr[1]` = 2.

**Tracing Reachability:**
*   **Start with User 2:**
    *   Path: 2 → 1 (1 link)
    *   Generated output for User 2: `[2, 1, 1]`
*   **Start with User 3:**
    *   Path: 3 → 2 (1 link) → 1 (2 links)
    *   Generated output (visited order): `[3, 2, 1]`, then `[3, 1, 2]`.
    *   Reversed to maintain strictly increasing order for `j`: `[3, 1, 2]`, `[3, 2, 1]`

**Combined Output:** `[[2, 1, 1], [3, 1, 2], [3, 2, 1]]`
</details>

---

## ⚠️ Constraints

> - $2 \le \text{arr.size()} \le 500$
> - $1 \le \text{arr}[i] \le 500$
> - **Time Complexity:** $O(n^2)$
> - **Auxiliary Space:** $O(n^2)$

---

## 💻 Solution Approach

### Iterative Graph Traversal
This approach simulates the traversal of a directed graph where each node has an out-degree of exactly $1$. Because each node points to a node with a strictly smaller identifier, no cycles can exist. It essentially forms a collection of paths terminating at node $1$.

```cpp
// Intuition: Since each user i only connects to one friend with a smaller ID, this forms a tree directed towards user 1. We can find all reachable nodes from i by simply tracing the one-way friend links until we reach a user with no further links.
// Approach: Loop from user 2 to n. For each user i, trace their connections using `curr = arr[curr - 2]`. Record the distance at each step. Since tracing naturally visits smaller IDs in decreasing order, reverse the collected connections for user i to satisfy the "increasing order of j" requirement before appending to the final result.
// Time Complexity: O(n^2) - In the worst case (e.g., each user points to the immediate previous user), tracing takes O(n) steps for each of the n users.
// Space Complexity: O(n^2) - To store the result 2D array which can contain up to n*(n-1)/2 connections.

class Solution {
  public:
    vector<vector<int>> socialNetwork(vector<int>& arr) {
        vector<vector<int>> result; // Container for final reachable pairs
        int n = arr.size() + 1;     // Total number of users

        // Process users i from 2 to n
        for (int i = 2; i <= n; ++i) {
            vector<vector<int>> current_user_reach; // Stores reachability for current user
            int curr = i; // Trace starts from user i
            int dist = 0; // Initialize link distance

            // Traverse the one-way friend links
            // Because each friend is strictly smaller, 'curr' decreases every step
            while (curr > 1) {
                curr = arr[curr - 2]; // Jump to the friend's ID
                dist++; // Increment the number of links followed
                current_user_reach.push_back({i, curr, dist}); // Record trace state
            }

            // Since reachable users (j) were visited in strictly decreasing order,
            // reversing the array sorts them in strictly increasing order
            reverse(current_user_reach.begin(), current_user_reach.end());

            // Append the processed pairs for user i into the main result
            result.insert(result.end(), current_user_reach.begin(), current_user_reach.end());
        }

        return result; // Return completed network trace
    }
};

/*
*
* Dry Run
* Input: arr[] = [1, 2]
* n = 3 (Users: 1, 2, 3)
*
* i = 2:
*   curr = 2, dist = 0
*   curr > 1 is true -> curr = arr[0] = 1, dist = 1
*   current_user_reach = [[2, 1, 1]]
*   curr > 1 is false. Loop ends.
*   Reverse current_user_reach -> [[2, 1, 1]]
*   result = [[2, 1, 1]]
*
* i = 3:
*   curr = 3, dist = 0
*   curr > 1 is true -> curr = arr[1] = 2, dist = 1
*   current_user_reach = [[3, 2, 1]]
*   curr > 1 is true -> curr = arr[0] = 1, dist = 2
*   current_user_reach = [[3, 2, 1], [3, 1, 2]]
*   curr > 1 is false. Loop ends.
*   Reverse current_user_reach -> [[3, 1, 2], [3, 2, 1]]
*   result = [[2, 1, 1], [3, 1, 2], [3, 2, 1]]
*
* Final Output: [[2, 1, 1], [3, 1, 2], [3, 2, 1]]
*
*/
```

---

## 🧠 Key Insights

* **Directional Certainty:** The problem ensures that every friend relationship points to a *smaller* user number. This guarantees a lack of cycles, meaning infinite loops during traversal are impossible. 
* **O(1) Sorting:** Since following the links naturally generates the reachable IDs in descending order, we can simply apply the built-in `reverse()` function to sort the subarray in $O(k)$ time (where $k$ is the path length) rather than utilizing an $O(k \log k)$ sort routine. 

---

## 🚀 Further Exploration

If you enjoyed this problem, you might want to explore these related concepts and problems:
* **Lowest Common Ancestor (LCA):** Try solving problems that ask you to find the first common friend between two different users in a directed tree.
* **Cycle Detection:** How would you modify your approach if user IDs weren't strictly decreasing, opening up the possibility of closed friend circles (cycles)?
* [GFG: Cycle in a Directed Graph](https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1)

---

## 🔗 References

* **GeeksforGeeks Problem Link:** [Your Social Network](https://www.geeksforgeeks.org/problems/your-social-network0328/1)

---

## 🧑‍💻 Author

**Nilesh Kumar**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️️ Tags

`Graph` `Data Structures` `Array` `Tree Traversal` `GeeksforGeeks`
