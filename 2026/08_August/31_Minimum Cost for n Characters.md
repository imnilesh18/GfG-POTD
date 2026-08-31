# 🔠 Minimum Cost for n Characters

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/minimum-time1238/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" /></a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty Medium" />
    <img src="https://img.shields.io/badge/Accuracy-38.21%25-green?style=for-the-badge" alt="Accuracy 38.21%" />
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points 4" />
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

> **⚠️ Educational Use Only**
> 
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.[cite: 1]

---

## 📝 Problem Statement

Given four integers `n`, `i`, `d`, and `c`, where:
*   `i` is the cost of inserting a single character,
*   `d` is the cost of deleting the last character,
*   `c` is the cost of copying the entire current string and pasting it immediately (thereby doubling its length).[cite: 1]

Find the minimum cost required to obtain exactly `n` characters on the screen. Initially, the screen is empty.[cite: 1]

---

## ⚙️ Constraints

> - `1 ≤ n ≤ 10^6`[cite: 1]
> - `1 ≤ i, d, c ≤ 100`[cite: 1]

---

## 💡 Examples

### Example 1

```text
Input: n = 9, i = 1, d = 2, c = 1
Output: 5

```

Perform the following operations:

1. Insert (1 character) - Cost: 1
2. Insert (2 characters) - Cost: 1
3. Copy-paste (4 characters) - Cost: 1
4. Copy-paste (8 characters) - Cost: 1
5. Insert (9 characters) - Cost: 1
**Total cost = 1 + 1 + 1 + 1 + 1 = 5.**


### Example 2

```text
Input: n = 9, i = 10, d = 1, c = 1
Output: 17

```

Perform the following operations:

1. Insert (1 character) - Cost: 10
2. Copy-paste (2 characters) - Cost: 1
3. Copy-paste (4 characters) - Cost: 1
4. Delete (3 characters) - Cost: 1
5. Copy-paste (6 characters) - Cost: 1
6. Delete (5 characters) - Cost: 1
7. Copy-paste (10 characters) - Cost: 1
8. Delete (9 characters) - Cost: 1
**Total cost = 10 + 1 + 1 + 1 + 1 + 1 + 1 + 1 = 17.**


Since insertion is expensive, it is cheaper to use copy-paste operations and adjust the length using deletions.

---

## 🧠 Solution Approach

### Dynamic Programming

**Intuition:**
Building the string character-by-character using only insertions is straightforward but can be expensive. Since copying and pasting doubles our current character count, it allows us to reach larger lengths exponentially faster.

For any length `x`:

* If `x` is **even**, we can reach it efficiently by getting to `x/2` and copying-pasting.
* If `x` is **odd**, we can reach it by getting to `x-1` and inserting, or by overshooting to `x+1` (which is even) via a copy-paste operation and then deleting one character.
We store the minimum cost for each length in a DP array to build our solution optimally from bottom to top.

### C++ Code

```cpp
// Intuition: Calculate minimum cost dynamically based on whether the target length is even (favoring copy-paste) or odd (favoring insert or copy-paste + delete).
// Approach: 
// 1. Initialize a dp array where dp[x] holds the min cost to reach x characters. Base cases: dp[0] = 0, dp[1] = i.
// 2. Iterate from 2 to n.
// 3. For even x: dp[x] = min(dp[x-1] + i, dp[x/2] + c).
// 4. For odd x: dp[x] = min(dp[x-1] + i, dp[(x+1)/2] + c + d).
// 5. Return dp[n].
// Time Complexity: O(n) because we compute the cost for each length from 2 to n exactly once.
// Space Complexity: O(n) auxiliary space required for the dp array of size n + 1.

class Solution {
  public:
    int minCost(int n, int i, int d, int c) {

        // Base case: No characters are required.
        if (n == 0)
            return 0;

        // Base case: One insert is needed to obtain a single character.
        if (n == 1)
            return i;

        // dp[x] stores the minimum cost to obtain exactly x characters.
        vector<int> dp(n + 1, 0);

        dp[1] = i;

        // Compute the minimum cost for every length from 2 to n.
        for (int x = 2; x <= n; x++) {
            if (x % 2 == 0) {

                // Even length:
                // 1) Insert one character after reaching x - 1.
                // 2) Copy-paste from x / 2 characters.
                dp[x] = min(dp[x - 1] + i, dp[x / 2] + c);
            } else {

                // Odd length:
                // 1) Insert one character after reaching x - 1.
                // 2) Copy-paste from (x + 1) / 2 characters,
                //    then delete the extra character.
                dp[x] = min(dp[x - 1] + i, dp[(x + 1) / 2] + c + d);
            }
        }

        return dp[n];
    }
};

/*
* Dry Run
* Input: n = 9, i = 1, d = 2, c = 1
* Initialization: dp[0] = 0, dp[1] = 1
* x = 2 (Even): min(dp[1]+1, dp[1]+1) = min(2, 2) = 2
* x = 3 (Odd):  min(dp[2]+1, dp[2]+1+2) = min(3, 5) = 3
* x = 4 (Even): min(dp[3]+1, dp[2]+1) = min(4, 3) = 3
* x = 5 (Odd):  min(dp[4]+1, dp[3]+1+2) = min(4, 6) = 4
* x = 6 (Even): min(dp[5]+1, dp[3]+1) = min(5, 4) = 4
* x = 7 (Odd):  min(dp[6]+1, dp[4]+1+2) = min(5, 6) = 5
* x = 8 (Even): min(dp[7]+1, dp[4]+1) = min(6, 4) = 4
* x = 9 (Odd):  min(dp[8]+1, dp[5]+1+2) = min(5, 7) = 5
* Output: 5
*/

```

---

## 🔑 Key Insights

* **The Power of Doubling:** The copy-paste operation (`c`) essentially acts as a multiplier. When target character length `n` is large, halving the problem space (or checking `x/2`) drastically reduces the accumulated costs compared to linear inserts.
* **Handling Odd Lengths:** A naive approach might only use inserts for odd lengths. However, depending on the cost variables, jumping to the next even number `(x+1)` via copy-paste and dialing back by deleting `d` can yield a much lower total cost.

---

## 🔎 Further Exploration

* [Minimum Number of Deletions and Insertions](https://www.geeksforgeeks.org/minimum-number-deletions-insertions-transform-one-string-another/)
* [Edit Distance](https://www.geeksforgeeks.org/edit-distance-dp-5/)

---

## 🔗 References

* **Problem Link:** [GeeksforGeeks - Minimum Cost for n Characters](https://www.geeksforgeeks.org/problems/minimum-time1238/1)


---

## 👨‍💻 Author

**Nilesh Kumar**

* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`dynamic-programming` `optimization` `algorithms` `geeksforgeeks` `cpp`