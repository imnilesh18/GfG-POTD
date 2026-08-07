# 👥 Friends Pairing Problem

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-358A1E?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-25.04%25-orange?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

---

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/friends-pairing-problem5425/1) problem.

---

## 📝 Problem Statement

Given `n` friends, each one can remain single or can be paired up with some other friend. Each friend can be paired only once. Find out the total number of ways in which friends can remain single or can be paired up.

---

## 📖 Examples

### Example 1
```text
Input: n = 3
Output: 4
Explanation:
{1}, {2}, {3} : All single.
{1}, {2,3}   : 2 and 3 paired, 1 is single.
{1,2}, {3}   : 1 and 2 paired, 3 is single.
{1,3}, {2}   : 1 and 3 paired, 2 is single.
Note that {1,2} and {2,1} are considered the same.
```

### Example 2
```text
Input: n = 2
Output: 2
Explanation:
{1}, {2}   : All single.
{1,2}      : 1 and 2 paired.
```

### Example 3
```text
Input: n = 1
Output: 1
Explanation:
{1} : Single.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough for n = 3)</b></summary>

<br>

Let the friends be labeled as **1, 2, and 3**:

1. **Option 1: Friend 3 remains single**  
   - The remaining `2` friends (`{1, 2}`) can form arrangements in `f(2) = 2` ways (`{1}, {2}` or `{1, 2}`).  
   - Arrangements formed:  
     - `{1}, {2}, {3}`  
     - `{1, 2}, {3}`

2. **Option 2: Friend 3 pairs with someone**  
   - Friend 3 can choose to pair with either **1** or **2** (`3 - 1 = 2` choices).  
   - If paired with **1**: Remaining friend is `{2}` (`f(1) = 1` way) $\rightarrow$ `{1, 3}, {2}`  
   - If paired with **2**: Remaining friend is `{1}` (`f(1) = 1` way) $\rightarrow$ `{2, 3}, {1}`

3. **Total Ways Calculation:**  
   $$\text{Total} = f(2) + (3 - 1) \times f(1) = 2 + 2 \times 1 = 4$$

</details>

---

## ⚙️ Constraints

> - $1 \le n \le 18$
> - **Expected Time Complexity:** $\mathcal{O}(n)$
> - **Expected Auxiliary Space:** $\mathcal{O}(1)$

---

## 💡 Solution Approach

### Space-Optimized Dynamic Programming

#### Intuition
For the $n$-th person, there are two mutually exclusive decisions available:
1. **Remain Single:** The person stays alone, reducing the problem to finding the total ways to arrange the remaining $(n - 1)$ friends ($f(n - 1)$).
2. **Pair Up:** The person pairs up with any of the remaining $(n - 1)$ friends. Once paired, both people are removed, leaving the subproblem of arranging the remaining $(n - 2)$ friends. Since there are $(n - 1)$ choices of partners, this yields $(n - 1) \times f(n - 2)$ ways.

This gives the linear recurrence relation:
$$f(n) = f(n - 1) + (n - 1) \times f(n - 2)$$

Since $f(n)$ depends only on the previous two values ($f(n - 1)$ and $f(n - 2)$), we can optimize space from $\mathcal{O}(n)$ to $\mathcal{O}(1)$ using two tracking variables.

---

### C++ Code Implementation

```cpp
// Intuition: The nth friend can stay single (f(n-1) ways) or pair with any of the (n-1) friends ((n-1) * f(n-2) ways).
// Approach: Iterate from 3 to n maintaining only the last two computed values to optimize space complexity.
// Time Complexity: O(n) - Single loop iterating from 3 to n.
// Space Complexity: O(1) - Constant space using state variables.

class Solution {
  public:
    int countFriendsPairings(int n) {
        // Base cases: 1 friend = 1 way, 2 friends = 2 ways
        if (n <= 2) return n;
        
        long long a = 1; // Stores f(i-2), initially f(1) = 1
        long long b = 2; // Stores f(i-1), initially f(2) = 2
        long long c = 0; // Stores current result f(i)
        
        // Iteratively compute total ways from 3 to n
        for (int i = 3; i <= n; i++) {
            c = b + (i - 1) * a; // Recurrence relation
            a = b;               // Shift window for next state
            b = c;
        }
        
        return b; // Returns total ways for n friends
    }
};

/*
*
* Dry Run
* 
* Input: n = 3
* 
* Initial State:
* n = 3 (> 2, proceed to loop)
* a = 1 (f(1))
* b = 2 (f(2))
* 
* Iteration i = 3:
* c = b + (3 - 1) * a 
*   = 2 + 2 * 1 
*   = 4
* a = b = 2
* b = c = 4
* 
* Loop finishes.
* Returns b = 4.
* Output: 4
* 
*/
```

---

## 🔑 Key Insights

- **Combinatorial Breakup:** The problem is a variant of the Fibonacci sequence where the subproblem $f(n-2)$ is scaled by the coefficient $(n - 1)$ due to partner selection choices.
- **Space Reduction:** Transitioning from dynamic programming table state array `dp[n]` to variables `a` and `b` reduces auxiliary space overhead from $\mathcal{O}(n)$ to $\mathcal{O}(1)$.

---

## 🚀 Further Exploration

- **[Climbing Stairs (GFG)](https://www.geeksforgeeks.org/problems/count-ways-to-reach-the-nth-stair-1587115620/1):** Standard Fibonacci dynamic programming transition problem.
- **[Gold Mine Problem (GFG)](https://www.geeksforgeeks.org/problems/gold-mine-problem2608/1):** Grid-based dynamic programming problem with choices.
- **[Count Derangements](https://www.geeksforgeeks.org/problems/count-derangements/0):** Similar combinatorial recurrence relation $f(n) = (n - 1) \times (f(n - 1) + f(n - 2))$.

---

## 🔗 References

- **GeeksforGeeks Problem Link:** [Friends Pairing Problem](https://www.geeksforgeeks.org/problems/friends-pairing-problem5425/1)

---

## 👤 Author

Crafted with 💻 by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`dynamic-programming` `recursion` `modular-arithmetic` `geeksforgeeks` `cpp`