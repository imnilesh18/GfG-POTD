# 🟧 Maximum Number of People Defeated

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/killing-spree3020/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-48.32%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
  </a>
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

There are infinitely many people standing in a row, indexed from `1`. The strength of the person at index `i` is `i²`.
Given a total strength `p`, determine the **maximum number of people that can be defeated**. A person with strength `x` can be defeated only if `p ≥ x`, after which the available strength `p` decreases by `x`.

---

## 💡 Examples

```text
Input: p = 14
Output: 3
```

<details>
<summary>📖 Example Breakdown</summary>

**Explanation:**
- The strengths of the first few people are `1², 2², 3², 4², ...` which are `1, 4, 9, 16, ...`
- Defeating the 1st person takes `1` strength. Remaining: `14 - 1 = 13`.
- Defeating the 2nd person takes `4` strength. Remaining: `13 - 4 = 9`.
- Defeating the 3rd person takes `9` strength. Remaining: `9 - 9 = 0`.
- We have `0` strength left, so we cannot defeat the 4th person (requires `16`). 
- Total people defeated = `3`.
</details>

```text
Input: p = 10
Output: 2
```
*Explanation:* After defeating people with strengths `1` and `4`, the remaining strength is `5`, which is less than the next required strength `9`. So we can only defeat `2` people.

---

## ⚠️ Constraints

> - `1 ≤ p ≤ 3 * 10^8`

---

## 🛠️ Solution Approach

### Binary Search on Answer
**Intuition:** The total strength required to defeat `n` people is the sum of squares of the first `n` natural numbers. Since this sum strictly increases as `n` increases, the search space is monotonic. This makes it a perfect candidate for **Binary Search**.

We will binary search the possible number of people `n` we can defeat. For a given `mid`, we calculate the total strength needed using the formula:  
**Sum = `[mid * (mid + 1) * (2 * mid + 1)] / 6`**

If this `Sum` is less than or equal to `p`, we can defeat at least `mid` people, so we look for a larger valid `mid` in the right half. Otherwise, we shrink our search space to the left half.

---

### 💻 Optimized Code (C++)

```cpp
// Intuition: The required strength to defeat 'n' people is the sum of squares of the first 'n' natural numbers. Since this sum monotonically increases as 'n' increases, we can use Binary Search to find the maximum possible 'n' for the given strength 'p'.
// Approach: 
// 1. Initialize the search space for 'n' with low = 1 and high = 100000 (a safe upper limit since 1000^3 > 3*10^8).
// 2. Calculate mid. For each mid, find the sum of squares of first 'mid' numbers using the formula: (mid * (mid + 1) * (2 * mid + 1)) / 6.
// 3. If this sum is less than or equal to 'p', it means we can defeat at least 'mid' people. Record 'mid' as a potential answer and search in the right half (low = mid + 1).
// 4. If the sum exceeds 'p', we cannot defeat 'mid' people, so search in the left half (high = mid - 1).
// Time Complexity: O(log(min(p, 100000))) -> effectively O(1), since the search space is small and bounded.
// Space Complexity: O(1) -> constant extra space used.

class Solution {
  public:
    int maxPeopleDefeated(int p) {
        long long low = 1, high = 100000;
        int ans = 0;
        
        // Binary search on the answer
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            
            // Sum of squares of first 'mid' natural numbers
            long long requiredStrength = (mid * (mid + 1LL) * (2LL * mid + 1LL)) / 6;
            
            if (requiredStrength <= p) {
                ans = mid;         // Update answer
                low = mid + 1;     // Try to defeat more people
            } else {
                high = mid - 1;    // Requires too much strength, reduce 'mid'
            }
        }
        
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: p = 14
*
* Initialization:
* low = 1, high = 100000, ans = 0
*
* Iteration 1:
* mid = 1 + (100000 - 1) / 2 = 50000
* requiredStrength = 50000 * 50001 * 100001 / 6 = 41667916675000
* 41667916675000 > 14 -> high = 49999
*
* ... (Binary search drastically narrows down the range quickly) ...
*
* Iteration K (when search space is reduced around 3):
* low = 3, high = 4
* mid = 3 + (4 - 3) / 2 = 3
* requiredStrength = (3 * 4 * 7) / 6 = 14
* 14 <= 14 -> ans = 3, low = 4
*
* Iteration K+1:
* low = 4, high = 4
* mid = 4
* requiredStrength = (4 * 5 * 9) / 6 = 30
* 30 > 14 -> high = 3
*
* Loop terminates because low (4) > high (3).
* Output: 3
*
*/
```

---

## 🔍 Key Insights
- **Why Binary Search?** The total required strength forms a strictly increasing monotonic sequence relative to the number of people defeated. Binary Search is the most efficient way to query monotonic ranges.
- **Data Types:** Even though `p` fits into a standard `int`, the intermediate calculation `mid * (mid+1) * (2*mid+1)` can easily overflow. Applying `long long` (or `1LL`) ensures safe mathematical execution without integer overflow errors.
- **Upper Bound:** A safe upper limit for `high` can be derived mathematically. For $p = 3 \times 10^8$, $n^3 / 3 \approx 3 \times 10^8 \implies n^3 \approx 10^9 \implies n \approx 1000$. Setting `high = 100000` is incredibly safe and barely impacts performance since $\log_2(100000) \approx 17$ iterations maximum.

---

## 🚀 Further Exploration
- [Allocate Minimum Number of Pages](https://www.geeksforgeeks.org/allocate-minimum-number-pages/) (A classic Binary Search on Answer problem)
- [Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)

---

## 🔗 References
- **Original Problem:** [GeeksforGeeks - Killing Spree](https://www.geeksforgeeks.org/problems/killing-spree3020/1)
- **Concept:** [Binary Search on Answer](https://www.geeksforgeeks.org/binary-search/)

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#BinarySearch` `#Mathematics` `#Algorithms` `#GeeksforGeeks` `#DivideAndConquer`