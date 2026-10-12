# 🔲 Minimum Squares with Full Cuts

<div align="center">

![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-50.16%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a rectangular paper with dimensions **n × m**, find the **minimum number of squares** that can be formed by cutting the paper.[cite: 1] Each cut must be made completely across the remaining paper, either horizontally or vertically.[cite: 1]

---

## 💡 Examples

### Example 1
```text
Input: n = 4, m = 5
Output: 5
Explanation: One square of size 4 x 4 and four squares of size 1 x 1 are required.[cite: 1]
```

### Example 2
```text
Input: n = 2, m = 4
Output: 2
Explanation: Two squares of size 2 x 2 are enough to fill the rectangle.[cite: 1]
```

### Example 3
```text
Input: n = 11, m = 13
Output: 8
Explanation: One square of size 11 x 11, five squares of size 2 x 2, and two squares of size 1 x 1 are formed by following the rule.[cite: 1]
```

<details>
<summary><b>📖 Example Breakdown (n = 11, m = 13)</b></summary>

1. We start with an `11 x 13` rectangle.
2. We cut the largest possible square, which is `11 x 11`. We can fit `13 / 11 = 1` such square. The remaining piece is `11 x 2`.
3. With the `11 x 2` piece, we cut the largest possible square, which is `2 x 2`. We can fit `11 / 2 = 5` such squares. The remaining piece is `1 x 2`.
4. With the `1 x 2` piece, we cut `1 x 1` squares. We can fit `2 / 1 = 2` such squares.
5. Total squares = `1 + 5 + 2 = 8`.

</details>

---

## 🛑 Constraints

- $1 \le n, m \le 10^9$[cite: 1]

---

## 🛠️ Solution Approaches

### 1. Optimized Approach (Euclidean Algorithm Concept)

**Brief Summary / Intuition:**
Instead of iteratively subtracting the smaller side from the larger side (which would result in a Time Limit Exceeded error for large inputs), we can use division and modulo operators.[cite: 1] This approach mimics the Euclidean algorithm used for finding the Greatest Common Divisor (GCD). By calculating `max_side / min_side`, we instantly find out how many full squares of size `min_side` can be cut out. The remaining rectangle dimensions simply become the `min_side` and the remainder `max_side % min_side`.

```cpp
// Intuition: We can greedily cut the largest possible squares from the given rectangle. Instead of subtracting repeatedly (which is slow for large inputs), we can use division and modulo operations, similar to the Euclidean algorithm for GCD.
// Approach: 
// 1. Run a loop as long as both n and m are greater than 0.
// 2. If n > m, we can cut (n / m) squares of size m x m. The new length becomes the remainder (n % m).
// 3. If m > n, we can cut (m / n) squares of size n x n. The new width becomes the remainder (m % n).
// 4. Accumulate the number of cut squares into the count variable at each step.
// Time Complexity: O(log(min(n, m))) - The dimensions reduce exponentially at each step, identical to the time complexity of the Euclidean GCD algorithm.[cite: 1]
// Space Complexity: O(1) - We only use a single integer variable to keep track of the count.[cite: 1]

class Solution {
  public:
    int minSquares(int n, int m) {
        int count = 0; // Tracks the total number of squares formed

        while (n > 0 && m > 0) { // Continue cutting as long as we have valid paper dimensions
            // If length is greater than width, cut m x m squares
            if (n > m) {
                count += n / m; // Add all possible squares of size m
                n %= m;         // Update the remaining length
            } 
            // If width is greater than length, cut n x n squares
            else {
                count += m / n; // Add all possible squares of size n
                m %= n;         // Update the remaining width
            }
        }

        return count; // Return total squares accumulated
    }
};

/*
*
* Dry Run
* Input: n = 4, m = 5
*
* Initialization: count = 0
*
* Iteration 1:
* n = 4, m = 5 (m > n)
* count += 5 / 4 -> count = 1
* m = 5 % 4 -> m = 1
* Remaining dimensions: n = 4, m = 1
*
* Iteration 2:
* n = 4, m = 1 (n > m)
* count += 4 / 1 -> count = 1 + 4 = 5
* n = 4 % 1 -> n = 0
* Remaining dimensions: n = 0, m = 1
*
* Loop terminates because n is not > 0.
* Output: 5
*
*/
```

---

## 🧠 Key Insights

- **Mathematical Optimization:** The brute-force approach simulates cutting one square at a time, resulting in $O(\max(n, m))$ time complexity. Recognizing that multiple identical squares can be cut simultaneously allows us to use division `/` for counting and modulo `%` for the remaining dimensions, dropping the time complexity to $O(\log(\min(n, m)))$.[cite: 1]
- **Greedy Strategy:** Cutting the largest possible square at every step always yields the minimum number of total squares for this specific constraint rule (full cuts only).

---

## 🔍 Further Exploration

- **Min Cut Square:** What if we are allowed to make partial horizontal or vertical cuts?[cite: 1] (This transforms the problem into a dynamic programming problem).
- **Greatest Common Divisor (GCD):** Explore how this solution directly maps to the traditional Euclidean GCD algorithm.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Minimum Squares with Full Cuts](https://www.geeksforgeeks.org/problems/squares-in-reactangle3340/1)[cite: 1]

---

## 👤 Author

**Nilesh Kumar**
- GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Mathematics` `#Greedy` `#Algorithm` `#GeeksForGeeks` `#CPP`