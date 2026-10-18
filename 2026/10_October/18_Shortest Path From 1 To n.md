# 🛣️ Shortest Path From 1 To n

![GeeksForGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-37.62%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Consider a directed graph whose vertices are numbered from 1 to `n`. There is an edge from a vertex `i` to a vertex `j` if and only if either `j = i + 1` or `j = 3 * i`. The task is to find the minimum number of edges in a path from vertex 1 to vertex `n`.

## 💡 Examples

<details>
<summary>📖 Example Breakdown</summary>

**Input:** `n = 9`
**Output:** `2`
**Explanation:** 
Many paths are possible from 1 to 9. The shortest one possible is:
`1 -> 3 -> 9`, which has a length of 2 edges.

**Step-by-step reverse logic:**
1. Start at `9`. Since `9` is divisible by 3, the optimal previous step was `3 * 3`. (Move to `3`, steps = 1)
2. Start at `3`. Since `3` is divisible by 3, the optimal previous step was `1 * 3`. (Move to `1`, steps = 2)
</details>

**Example 2:**
```text
Input: n = 4
Output: 2
Explanation: Possible paths from 1 to 4 are, 1 -> 2 -> 3 -> 4 and 1 -> 3 -> 4. Second path of length 2 is the shortest.

```

**Example 3:**

```text
Input: n = 15
Output: 4
Explanation: Many paths are possible from 1 to 15. Shortest one possible is, 1 -> 3 -> 4 -> 5 -> 15, of length 4.

```

## ⚠️ Constraints

> * `1 ≤ n ≤ 10^8`
> 
> 

---

## 💻 Solution Approaches

### Greedy Approach (Bottom-Up / Reverse)

Working forward from `1` to `n` can branch out exponentially. Working backwards from `n` to `1` allows us to use a greedy strategy: division reduces the number much faster than subtraction, guaranteeing the shortest path.

```cpp
// Intuition: To find the minimum edges, it is strictly optimal to work backwards from n to 1. Division by 3 shrinks the number significantly faster than subtraction, acting as a greedy choice.
// Approach: Iterate backwards while n > 1. If n is cleanly divisible by 3, divide it by 3 (representing the j = 3*i edge). Otherwise, decrement n by 1 (representing the j = i+1 edge). Count each operation.
// Time Complexity: O(log n) because in the optimal scenario, we are repeatedly dividing n by 3.
// Space Complexity: O(1) as we only use a single integer variable to keep track of steps.
class Solution {
  public:
    int minimumStep(int n) {
        int steps = 0; // Initialize step counter
        
        // Work backwards from n to 1
        while (n > 1) {
            if (n % 3 == 0) {
                // If n is a multiple of 3, the shortest previous step was a multiplication by 3
                n /= 3;
            } else {
                // Otherwise, the previous step had to be an addition of 1
                n--;
            }
            steps++; // Increment edge count for this step
        }
        
        return steps;
    }
};

/*
*
* Dry Run
* Input: n = 15
* Initialization: steps = 0
* Iteration 1: n = 15. 15 % 3 == 0 -> n = 15 / 3 = 5. steps = 1.
* Iteration 2: n = 5. 5 % 3 != 0 -> n = 5 - 1 = 4. steps = 2.
* Iteration 3: n = 4. 4 % 3 != 0 -> n = 4 - 1 = 3. steps = 3.
* Iteration 4: n = 3. 3 % 3 == 0 -> n = 3 / 3 = 1. steps = 4.
* Loop terminates (n is not > 1).
* Output: 4
*
*/

```

---

## 🔍 Key Insights

* **Greedy Optimization:** Moving from `1` to `n` makes it difficult to know when to multiply vs add to hit the exact target `n`. Moving from `n` to `1` makes the choice deterministic: always divide if possible, otherwise subtract.
* **Mathematical Bound:** The maximum number of operations is constrained logarithmically, easily passing the `10^8` constraint in sub-millisecond execution time.

## 🔗 References

* **GeeksforGeeks Problem:** [Shortest Path From 1 To n](https://www.geeksforgeeks.org/problems/shortest-path-from-1-to-n0156/1)

## 👤 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

## 🏷️ Tags

* `Mathematics` `Graph` `Shortest Path` `Greedy` `GeeksforGeeks`