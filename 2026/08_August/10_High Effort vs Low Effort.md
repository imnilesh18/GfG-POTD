# 🟩 High Effort vs Low Effort

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-orange?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/high-effort-vs-low-effort0213/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/high-effort-vs-low-effort0213/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-51.95%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/high-effort-vs-low-effort0213/1)
[![Points](https://img.shields.io/badge/Points-2-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/problems/high-effort-vs-low-effort0213/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given two integer arrays `h[]` and `l[]` of equal size, where:
* `h[i]` denotes the number of tasks completed on the $i$-th day by performing a **high-effort task**.
* `l[i]` denotes the number of tasks completed on the $i$-th day by performing a **low-effort task**.

For each day, you may choose **exactly one** of the following options:
1. Perform **no task** ($0$ tasks).
2. Perform a **low-effort task** (`l[i]` tasks).
3. Perform a **high-effort task** (`h[i]` tasks), which can **only** be performed on the first day ($i = 0$) or if **no task was performed on the previous day** ($i - 1$).

Return the **maximum total number of tasks** that can be completed over all days.

---

## 💡 Examples

### Example 1
```text
Input:  h[] = [2, 8, 1], l[] = [1, 2, 1]
Output: 9
Explanation: Pick high-effort task on day 1 (index 1) and low-effort task on day 2 (index 2). Total = 8 + 1 = 9.
```

### Example 2
```text
Input:  h[] = [3, 6, 8, 7, 6], l[] = [1, 5, 4, 5, 3]
Output: 20
Explanation: Pick high-effort task on day 0, and low-effort tasks on all remaining days. Total = 3 + 5 + 4 + 5 + 3 = 20.
```

<details>
<summary>📖 Example Breakdown (Walkthrough for Example 1)</summary>

<br>

* **Day 0 (`i = 0`):**
  * Option A (Low effort): $1$ task. Max so far = $1$.
  * Option B (High effort): $2$ tasks. Max so far = $2$.
  * Best choice for Day 0 = $2$.

* **Day 1 (`i = 1`):**
  * Option A (Low effort): Perform low effort on Day 1 + Max tasks till Day 0 $\implies 2 + 2 = 4$.
  * Option B (High effort): Must skip Day 0 + Perform high effort on Day 1 $\implies 0 + 8 = 8$.
  * Best choice up to Day 1 = $\max(4, 8) = 8$.

* **Day 2 (`i = 2`):**
  * Option A (Low effort): Perform low effort on Day 2 + Max tasks till Day 1 $\implies 1 + 8 = 9$.
  * Option B (High effort): Skip Day 1 + Perform high effort on Day 2 $\implies 1 \text{ (from Day 2)} + 2 \text{ (Max till Day 0)} = 3$.
  * Best choice up to Day 2 = $\max(9, 3) = 9$.

**Final Output:** `9`
</details>

---

## ⚙️ Constraints

* $1 \le h.\text{length} \le 10^5$
* $0 \le h[i] \le 10^3$
* $1 \le l.\text{length} \le 10^5$
* $0 \le l[i] \le 10^3$
* $l.\text{length} == h.\text{length}$

---

## 🚀 Solution Approach

### Dynamic Programming (Space-Optimized $O(1)$ Space)

#### Summary / Intuition
At any given day $i$, we face a decision tree for maximizing total tasks:
1. **Choose Low Effort on day $i$**: We add $l[i]$ to the optimal task sum up to day $i-1$.
2. **Choose High Effort on day $i$**: Since high effort requires skipping day $i-1$, we add $h[i]$ to the optimal task sum up to day $i-2$.

Since the optimal state at day $i$ depends only on the results of day $i-1$ and day $i-2$, we can reduce the $O(N)$ dynamic programming table into two dynamic variables (`prev1` and `prev2`), achieving optimal $O(1)$ space complexity.

```cpp
// Intuition: To maximize tasks at day i, we either take low effort on day i (adding to max tasks up to day i-1) or take high effort on day i (adding to max tasks up to day i-2 since day i-1 must be skipped).
// Approach: Use dynamic programming space-optimization. Track max tasks up to day i-1 (prev1) and day i-2 (prev2) and update iteratively.
// Time Complexity: O(N) because we perform a single linear scan over the input arrays of size N.
// Space Complexity: O(1) auxiliary space as we only store integer state variables.

class Solution {
  public:
    int maxTask(vector<int>& h, vector<int>& l) {
        int n = h.size();
        if (n == 0) return 0;
        
        // Base state variables for space optimization
        int prev2 = 0;                  // Max tasks up to day i-2
        int prev1 = max(h[0], l[0]);    // Max tasks up to day 0
        
        for (int i = 1; i < n; i++) {
            // Option 1: Perform low-effort task today
            int take_low = prev1 + l[i];
            
            // Option 2: Perform high-effort task today (requires skipping day i-1)
            int take_high = prev2 + h[i];
            
            // Optimal tasks up to day i
            int curr = max(take_low, take_high);
            
            // Advance states for next day
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1; // Final answer for day n-1
    }
};

/*
*
* Dry Run
*
* Input: h = [2, 8, 1], l = [1, 2, 1]
* Initial State:
*   prev2 = 0
*   prev1 = max(h[0], l[0]) = max(2, 1) = 2
*
* Day 1 (i = 1): h[1] = 8, l[1] = 2
*   take_low  = prev1 + l[1] = 2 + 2 = 4
*   take_high = prev2 + h[1] = 0 + 8 = 8
*   curr      = max(4, 8) = 8
*   Update: prev2 = 2, prev1 = 8
*
* Day 2 (i = 2): h[2] = 1, l[2] = 1
*   take_low  = prev1 + l[2] = 8 + 1 = 9
*   take_high = prev2 + h[2] = 2 + 1 = 3
*   curr      = max(9, 3) = 9
*   Update: prev2 = 8, prev1 = 9
*
* Return prev1 = 9
*
*/
```

---

## 🔑 Key Insights

1. **State Reduction**: The problem exhibits identical recurrence patterns to the classic **House Robber / Stickler Thief** problem.
2. **Greedy Trap**: A purely greedy choice per day can be sub-optimal because picking a high-effort task today forces a $0$-task penalty yesterday.
3. **Space Optimization**: Storing an full DP array $dp[N]$ is unnecessary; only $dp[i-1]$ and $dp[i-2]$ are ever referenced.

---

## 🔮 Further Exploration

Looking to practice similar Dynamic Programming pattern problems?
* [Stickler Thief (House Robber)](https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1)
* [Maximum Sum without Adjacents](https://www.geeksforgeeks.org/problems/max-sum-without-adjacents2430/1)
* [Geek Jump (Climbing Stairs variation)](https://www.geeksforgeeks.org/problems/geek-jump/1)

---

## 🔗 References

* Original Problem: [GeeksforGeeks - High Effort vs Low Effort](https://www.geeksforgeeks.org/problems/high-effort-vs-low-effort0213/1)
* Dynamic Programming Concepts: [GeeksforGeeks DP Series](https://www.geeksforgeeks.org/dynamic-programming/)

---

## 👤 Author

Crafted with 💚 by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/Dynamic--Programming-4682B4?style=flat-square&logo=cplusplus)
![Array](https://img.shields.io/badge/Array-E06C75?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-POTD-orange?style=flat-square&logo=geeksforgeeks)
![CPP](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=c%2B%2B)