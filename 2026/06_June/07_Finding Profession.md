# 👨‍💻 Finding Profession

[![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/finding-profession3834/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-30.3%25-1EA362?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-4-007BFF?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/finding-profession3834/1).

---

## 📜 Problem Statement

Consider a special family of Engineers and Doctors with the following rules:
1. Everybody has two children.
2. The **first child** of an Engineer is an Engineer, and the **second child** is a Doctor.
3. The **first child** of a Doctor is a Doctor, and the **second child** is an Engineer.
4. All generations of Doctors and Engineers start with an **Engineer**.

The first few levels of the family tree are shown below:

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/929039/Web/Other/blobid0_1780132182.png" alt="Family Tree" />
</div>

Given the `level` and position (`pos`) of a person in the above ancestor tree, find the profession of the person.

---

## 💡 Examples

### Example 1

```text
Input: level = 4, pos = 2
Output: Doctor
Explanation: As shown in the tree given in the problem statement, the 2nd position at level 4 is a Doctor.
```

### Example 2

```text
Input: level = 3, pos = 4
Output: Engineer
Explanation: As shown in the tree, the 4th position at level 3 is an Engineer.
```

<details>
<summary><b>📖 Example Breakdown (level = 3, pos = 4)</b></summary>

1. **Level 1**: Engineer (1st child)
2. **Level 2**: Engineer (1st child), Doctor (2nd child)
3. **Level 3**: Engineer, Doctor, Doctor, **Engineer**
4. Looking at the tree, the 4th element at level 3 is an **Engineer**.
5. Using our bitwise logic: `pos - 1` = `3`. The binary representation of `3` is `11`.
6. There are **two** set bits (an even number). 
7. An even number of flips implies the profession remains the default ("Engineer").
</details>

---

## 🚧 Constraints

- **1 <= level <= 10^9**
- **1 <= pos <= 10^9**

*Expected Complexities:*
- **Time Complexity:** $O(\log(\text{pos}))$
- **Auxiliary Space:** $O(1)$

---

## 🚀 Solution Approach

### Bit Manipulation (Optimized)

```cpp
// Intuition: The tree generates a Thue-Morse sequence. By converting to 0-based indexing, the binary representation of the position dictates the path from the root. Every '1' bit acts as a right child leading to a profession flip, while '0' bits maintain the current profession.
// Approach: Shift 'pos' to a 0-based index. Count the set bits (1s) in this value using Brian Kernighan's algorithm. An even count of set bits means the net flips cancel out resulting in "Engineer", whereas an odd count results in "Doctor".
// Time Complexity: O(log(pos)) because counting the set bits takes iterations proportional to the number of 1s in the binary representation, bounded by 30 for max pos 10^9.
// Space Complexity: O(1) as we avoid recursion entirely and only track two integer variables.

class Solution {
public:
    string profession(int level, int pos) {
        // Convert to 0-based index to align with binary pathing
        int zero_based_pos = pos - 1;
        int flip_count = 0;
        
        // Count set bits (1s) to determine total profession flips
        // Using Brian Kernighan's algorithm for efficiency
        while (zero_based_pos > 0) {
            zero_based_pos &= (zero_based_pos - 1); // Clears the lowest set bit
            flip_count++;
        }
        
        // Even flips mean original profession, odd means flipped profession
        if (flip_count % 2 == 0) {
            return "Engineer";
        }
        
        return "Doctor";
    }
};

/*
*
* Dry Run
*
* Input: level = 3, pos = 4
*
* Initialization:
* zero_based_pos = 3 (from 4 - 1)
* flip_count = 0
* 
* While loop execution starts:
* 
* First pass:
* zero_based_pos = 3 & 2 = 2
* flip_count = 1
* 
* Second pass:
* zero_based_pos = 2 & 1 = 0
* flip_count = 2
* 
* Loop terminates because zero_based_pos reached 0.
* 
* Parity check:
* flip_count is 2, which is an even number.
* Result evaluates to "Engineer".
*/
```

---

## 🧠 Key Insights

* **Thue-Morse Sequence**: The problem generates a classic Thue-Morse sequence where each subsequent level is formed by appending the bitwise negation of the current level.
* **0-Based Indexing**: By treating the position as 0-indexed (`pos - 1`), the binary representation maps the path down the tree perfectly: a `0` implies a left child (no flip), and a `1` implies a right child (flip profession).
* **Parity & Flipping**: Because we always start as an `Engineer`, an even number of right-turns (flips) returns us to `Engineer`. An odd number of right-turns toggles the profession to `Doctor`.
* **Brian Kernighan’s Algorithm**: We use `n & (n - 1)` to effectively count the set bits in $O(k)$ time, where $k$ is the number of `1`s in the binary representation of the position. 

---

## 🔗 Further Exploration

If you enjoyed this problem, you might also want to try:
* **[K-th Symbol in Grammar](https://leetcode.com/problems/k-th-symbol-in-grammar/)** (LeetCode equivalent of this problem)
* Related GFG problems on **Bit Magic** and **Recursion**.

---

## 📚 References

* **GeeksforGeeks Problem:** [Finding Profession](https://www.geeksforgeeks.org/problems/finding-profession3834/1)
* **Brian Kernighan’s Algorithm:** [Count set bits in an integer](https://www.geeksforgeeks.org/count-set-bits-in-an-integer/)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`recursion` `bit-manipulation` `algorithms` `geeksforgeeks` `thue-morse`