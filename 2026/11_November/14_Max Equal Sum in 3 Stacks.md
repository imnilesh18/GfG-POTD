# 🟧 Max Equal Sum in 3 Stacks

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-maximum-equal-sum-of-three-stacks/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/find-maximum-equal-sum-of-three-stacks/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-48.71%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/find-maximum-equal-sum-of-three-stacks/1)
[![Points](https://img.shields.io/badge/Points-4-success?style=for-the-badge)](https://www.geeksforgeeks.org/problems/find-maximum-equal-sum-of-three-stacks/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given three stacks `s1`, `s2`, and `s3`, represented by arrays where the **first element of each array represents the top** of the corresponding stack[cite: 1].

Your task is to find the **maximum possible equal sum** (sum of all remaining elements) of all three stacks by removing zero or more elements from the top of each stack[cite: 1].

If it is not possible to make the sum of all three stacks equal, return `0`[cite: 1].

---

## 💡 Examples

### Example 1
```text
Input: s1 = [3, 2, 1, 1, 1], s2 = [4, 3, 2], s3 = [2, 5, 4, 1]
Output: 5
Explanation: Remove 3 from s1, 4 from s2, and 2, 5 from s3. The remaining sums of all three stacks are equal to 5.
```[cite: 1]

### Example 2
```text
Input: s1 = [4, 7], s2 = [10], s3 = [1, 2, 3]
Output: 0
Explanation: It is not possible to make the sums of all three stacks equal by removing elements from their tops.
```[cite: 1]

<details>
<summary><b>📖 Example Breakdown (Walkthrough of Example 1)</b></summary>

<br>

Let's trace the stacks from top (index `0`) to bottom:

| Step | Stack `s1` (Top → Bottom) | `sum1` | Stack `s2` (Top → Bottom) | `sum2` | Stack `s3` (Top → Bottom) | `sum3` | Action Taken |
| :--- | :--- | :---: | :--- | :---: | :--- | :---: | :--- |
| **Start** | `[3, 2, 1, 1, 1]` | `8` | `[4, 3, 2]` | `9` | `[2, 5, 4, 1]` | `12` | `sum3` is max (`12`) → Pop `2` from `s3` |
| **Step 1** | `[3, 2, 1, 1, 1]` | `8` | `[4, 3, 2]` | `9` | `[5, 4, 1]` | `10` | `sum3` is max (`10`) → Pop `5` from `s3` |
| **Step 2** | `[3, 2, 1, 1, 1]` | `8` | `[4, 3, 2]` | `9` | `[4, 1]` | `5` | `sum2` is max (`9`) → Pop `4` from `s2` |
| **Step 3** | `[3, 2, 1, 1, 1]` | `8` | `[3, 2]` | `5` | `[4, 1]` | `5` | `sum1` is max (`8`) → Pop `3` from `s1` |
| **Step 4** | `[2, 1, 1, 1]` | `5` | `[3, 2]` | `5` | `[4, 1]` | `5` | **All sums equal `5`! Return `5`.** |

</details>

---

## 🔒 Constraints

> - $1 \le \text{s1.size()}, \text{s2.size()}, \text{s3.size()} \le 5 \times 10^5$[cite: 1]
> - $1 \le \text{s1}[i], \text{s2}[i], \text{s3}[i] \le 10^3$[cite: 1]

**Expected Complexities:**
- **Time Complexity:** $\mathcal{O}(n_1 + n_2 + n_3)$[cite: 1]
- **Auxiliary Space:** $\mathcal{O}(1)$[cite: 1]

---

## 🚀 Solution Approach

### Greedy Three-Pointer Approach

#### Intuition
Since all elements in the stacks are strictly positive integers ($1 \le s[i] \le 10^3$), popping an element from any stack strictly reduces its total sum[cite: 1]. Because we can only remove elements from the top (reducing sums, never increasing them), the target equal sum can never exceed the current minimum sum among the three stacks. Therefore, whichever stack currently holds the **maximum sum** cannot possibly reach equilibrium without popping its top element.

#### Step-by-Step Approach
1. Compute the initial total sums `sum1`, `sum2`, and `sum3` of all three stacks.
2. Initialize three pointers `i = 0`, `j = 0`, and `k = 0` representing the current top index of `s1`, `s2`, and `s3`, respectively.
3. While all three stacks still have elements (`i < n1 && j < n2 && k < n3`):
   - If `sum1 == sum2 && sum2 == sum3`, we have found the maximum possible equal sum—return `sum1`.
   - Otherwise, identify the stack with the largest current sum, subtract its current top element from its sum, and advance its top pointer.
4. If any stack becomes empty before all three sums match, it is impossible to achieve a non-zero equal sum—return `0`.

#### C++ Implementation

```cpp
// Intuition: Since all elements are positive, popping only decreases sums; thus, the stack with the maximum sum must pop its top element to ever match the smaller sums.
// Approach: Compute total sums of all three stacks, use three top pointers, and repeatedly remove the top element from whichever stack currently has the greatest sum until all sums match or a stack empties.
// Time Complexity: O(n1 + n2 + n3) because computing initial sums takes linear time and each element across all three stacks is visited at most once.
// Space Complexity: O(1) as only a fixed number of integer variables and pointers are used without extra data structures.

class Solution {
  public:
    int maxEqualSum(vector<int> &s1, vector<int> &s2, vector<int> &s3) {
        // Calculate total sum of each stack
        int sum1 = accumulate(s1.begin(), s1.end(), 0);
        int sum2 = accumulate(s2.begin(), s2.end(), 0);
        int sum3 = accumulate(s3.begin(), s3.end(), 0);

        // Pointers tracking the current top of each stack
        int i = 0, j = 0, k = 0;
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();

        // Continue while all three stacks remain non-empty
        while (i < n1 && j < n2 && k < n3) {
            // Return immediately once all three stack sums are equal
            if (sum1 == sum2 && sum2 == sum3) {
                return sum1;
            }

            // Greedily pop the top element from the stack with the largest sum
            if (sum1 >= sum2 && sum1 >= sum3) {
                sum1 -= s1[i++];
            } else if (sum2 >= sum1 && sum2 >= sum3) {
                sum2 -= s2[j++];
            } else {
                sum3 -= s3[k++];
            }
        }

        // Equal sum is not possible
        return 0;
    }
};

/*
Dry Run

Input: s1 = [3, 2, 1, 1, 1], s2 = [4, 3, 2], s3 = [2, 5, 4, 1]

Initial State:
sum1 = 8, sum2 = 9, sum3 = 12
i = 0, j = 0, k = 0

Iteration 1:
sum3 (12) is the largest, so remove top of s3 (s3[0] = 2)
sum3 = 12 - 2 = 10, k = 1

Iteration 2:
sum3 (10) is the largest, so remove top of s3 (s3[1] = 5)
sum3 = 10 - 5 = 5, k = 2

Iteration 3:
sum2 (9) is the largest, so remove top of s2 (s2[0] = 4)
sum2 = 9 - 4 = 5, j = 1

Iteration 4:
sum1 (8) is the largest, so remove top of s1 (s1[0] = 3)
sum1 = 8 - 3 = 5, i = 1

Iteration 5:
sum1 == sum2 == sum3 == 5
Return 5
*/
```

---

## 🔑 Key Insights

- **Monotonic Sum Reduction:** Because every element is positive ($s[i] \ge 1$), every pop operation strictly decreases the stack's sum[cite: 1]. This guarantees termination and eliminates any need for backtracking or dynamic programming.
- **First Match is Optimal:** Because we only reduce the current maximum sum at every step, the **very first** state where `sum1 == sum2 == sum3` is guaranteed to be the highest possible equal sum.
- **In-Place Pointer Simulation:** Instead of physically modifying the vectors with `erase()` (which would cost $\mathcal{O}(n)$ per pop), maintaining top indices `i`, `j`, and `k` simulates stack pops in $\mathcal{O}(1)$ time and $\mathcal{O}(1)$ auxiliary space[cite: 1].

---

## 🔍 Further Exploration

- [Equal Stacks (HackerRank)](https://www.hackerrank.com/challenges/equal-stacks/problem) — Direct counterpart using cylinder heights instead of stack elements.
- [Minimum Operations to Reduce X to Zero](https://www.geeksforgeeks.org/problems/minimum-operations-to-reduce-x-to-zero/1) — Practice removing elements from ends of arrays to achieve a target sum.
- [Two Stacks in an Array](https://www.geeksforgeeks.org/problems/implement-two-stacks-in-an-array/1) — Strengthen foundational array-backed stack manipulation skills.

---

## 📚 References

- **Original Problem:** [Max Equal Sum in 3 Stacks — GeeksforGeeks](https://www.geeksforgeeks.org/problems/find-maximum-equal-sum-of-three-stacks/1)[cite: 1]
- **C++ STL Reference:** [`std::accumulate`](https://en.cppreference.com/w/cpp/algorithm/accumulate)
- **Algorithmic Paradigm:** [Greedy Algorithms — GeeksforGeeks](https://www.geeksforgeeks.org/greedy-algorithms/)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Greedy](https://img.shields.io/badge/Greedy-informational?style=flat-square)
![Stack](https://img.shields.io/badge/Stack-informational?style=flat-square)
![Arrays](https://img.shields.io/badge/Arrays-informational?style=flat-square)
![Two Pointers](https://img.shields.io/badge/Two_Pointers-informational?style=flat-square)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks&logoColor=white)