# 🟧 Smallest Non-Zero Number

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/find-smallest-non-zero-number4510/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-33.84%25-success?style=for-the-badge" alt="Accuracy: 33.84%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <a href="./LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
  </a>
</div>

---

### ⚠️ Educational Use Only:
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]`, find the smallest number `x` such that when `x` is processed sequentially with each element of the array (from index `0` to `n-1`), it **never becomes negative**, under the following conditions:
- If `x` is greater than the current array element, `x` is increased by the difference between `x` and the array element.
- If `x` is less than or equal to the current array element, `x` is decreased by the difference between the array element and `x`.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [3, 4, 3, 2, 4]
Output: 4
Explanation: Start with x = 4:
- For arr[0] = 3, x becomes 5.
- For arr[1] = 4, x becomes 6.
- For arr[2] = 3, x becomes 9.
- For arr[3] = 2, x becomes 16.
- For arr[4] = 4, x becomes 28.
x remains positive throughout the process.
If x < 4, it would become negative at some point.
```

### Example 2
```text
Input: arr[] = [4, 4]
Output: 3
Explanation: Start with x = 3:
- For arr[0] = 4, x becomes 2.
- For arr[1] = 4, x becomes 0.
x remains non-negative. If x < 3, it would become negative.
```

<details>
<summary><b>📖 Example Breakdown (Walkthrough)</b></summary>
<br>

Let's carefully analyze the operation being performed at each step:
- If $x > arr[i]$, new $x = x + (x - arr[i]) = 2x - arr[i]$.
- If $x \le arr[i]$, new $x = x - (arr[i] - x) = 2x - arr[i]$.

Notice that in **both** cases, the mathematical formula evaluates to the exact same equation: $x_{next} = 2x_{current} - arr[i]$.

To ensure $x$ never goes negative, we can assume the worst-case scenario at the very end of the array: $x_{final} = 0$. By working backwards from the last element to the first, we can find the minimum required $x$ at each step using the inverted formula: $x_{current} = \lceil \frac{x_{next} + arr[i]}{2} \rceil$.

</details>

---

## 🚧 Constraints

> - `1 ≤ arr.size() ≤ 10^6`
> - `1 ≤ arr[i] ≤ 10^4`

---

## 🛠️ Solution Approaches

### 1. Optimal Approach (Backward Traversal)

**Intuition:** Since the forward operation always translates to `x = 2 * x - arr[i]`, we can reverse engineer the required starting value. By starting from the end of the array with a minimum required energy of `0`, we can propagate backwards and calculate the minimum `x` needed at each preceding step.

```cpp
// Intuition: The problem describes a state transition where the next value of x is always (2 * x - arr[i]), regardless of whether x is greater or smaller than arr[i]. To find the minimum initial x such that x never drops below 0, we can work backward from the end of the array, assuming a minimum final requirement of 0.
// Approach: Start with required x = 0 at the end of the array. Iterate backwards from the last element to the first. For each element, the required x before processing it must be ceil((x + arr[i]) / 2). Update x iteratively and return the final computed x for index 0.
// Time Complexity: O(N) where N is the size of the array, as we are traversing the array exactly once.
// Space Complexity: O(1) as we are only using a single variable x to keep track of the required minimum number.
class Solution {
  public:
    int find(vector<int>& arr) {
        // Initialize required x at the end of the process to 0
        int x = 0;
        
        // Traverse the array backwards
        for (int i = arr.size() - 1; i >= 0; i--) {
            // Calculate the minimum required x before this step
            // (x + arr[i] + 1) / 2 gracefully simulates ceil((x + arr[i]) / 2)
            x = (x + arr[i] + 1) / 2;
        }
        
        // Return the initial required value
        return x;
    }
};

/*
Dry Run
Input: arr[] = [3, 4, 3, 2, 4]
Initialize x = 0
Iterating backward:
i = 4, arr[4] = 4 => x = (0 + 4 + 1) / 2 = 5 / 2 = 2
i = 3, arr[3] = 2 => x = (2 + 2 + 1) / 2 = 5 / 2 = 2
i = 2, arr[2] = 3 => x = (2 + 3 + 1) / 2 = 6 / 2 = 3
i = 1, arr[1] = 4 => x = (3 + 4 + 1) / 2 = 8 / 2 = 4
i = 0, arr[0] = 3 => x = (4 + 3 + 1) / 2 = 8 / 2 = 4
Final Output: 4
*/
```

---

## 🧠 Key Insights
- **Unified Formula:** The complicated piecewise function simplified exactly down to one core mathematical transition: `x = 2x - arr[i]`.
- **Reverse Engineering:** For problems where forward simulation involves checking lower bounds, reverse traversal often flips an $O(N \log M)$ binary search problem into a beautiful $O(N)$ linear pass.
- **Ceiling Division Trick:** Using `(a + b + 1) / 2` in C++ guarantees proper rounding up without invoking external floating-point mathematical libraries like `ceil()`.

---

## 🔭 Further Exploration
- Compare this problem with **Jump Game** or **Minimum Energy to Reach End** scenarios where backward traversal is also highly optimal.
- Practice solving it using Binary Search on the Answer. Though it operates in $O(N \log(\text{max\_val}))$, it's a solid conceptual stepping stone!

---

## 🔗 References
- **Original Problem:** [Smallest Non-Zero Number](https://www.geeksforgeeks.org/problems/find-smallest-non-zero-number4510/1)

---

## 👨‍💻 Author
**Nilesh**
- GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#Arrays` `#Mathematics` `#BackwardTraversal` `#GeeksforGeeks` `#OptimalSolution` `#DataStructures`