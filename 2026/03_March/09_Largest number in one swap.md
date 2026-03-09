# 🔄 Largest number in one swap

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/largest-number-in-one-swap1520/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
    <img src="https://img.shields.io/badge/Accuracy-48.67%25-blue?style=for-the-badge" alt="Accuracy: 48.67%" />
    <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
    <a href="https://choosealicense.com/licenses/mit/">
        <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="License: MIT" />
    </a>
</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s`, return the **lexicographically largest** string that can be obtained by swapping at most **one pair** of characters in `s`.

---

## 💡 Examples

### Example 1:
```text
Input: s = "768"
Output: "867"
Explanation: Swapping the 1st and 3rd characters (7 and 8 respectively), gives the lexicographically largest string.
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>

1. We have the string `s = "768"`.
2. To make it the largest possible string, we want to place the largest digit as far to the left as possible.
3. The largest digit is `'8'` at index `2`.
4. We swap the first character `'7'` (at index `0`) with `'8'` (at index `2`).
5. The string becomes `"867"`, which is the maximum possible value.

</details>

### Example 2:
```text
Input: s = "333"
Output: "333"
Explanation: Performing any swaps gives the same result i.e "333".
```

---

## ⚙️ Constraints

- `1 ≤ |s| ≤ 10^5`
- `'0' ≤ s[i] ≤ '9'`

---

## 🚀 Solution Approach

### Optimized Greedy Approach (Single Pass)

Below is the highly optimized C++ approach that solves the problem in a single pass. 

```cpp
// Intuition: To maximize the number, we should swap a smaller left digit with the largest possible right digit. Traversing right-to-left lets us efficiently track the maximum digit seen so far.
// Approach: Iterate from right to left tracking the maximum digit and its index. Whenever we see a digit smaller than the max digit, we record this pair (current index and max index) as the best candidate for swapping, because it affects the most significant (leftmost) possible position.
// Time Complexity: O(n) where n is the length of the string, as we only iterate through the string once.
// Space Complexity: O(1) since we only use a few variables for indices and characters.
class Solution {
  public:
    string largestSwap(string &s) {
        char maxDigit = '0';
        int maxIndx = -1;
        int l = -1, r = -1;
    
        // Traverse from right to left
        for (int i = s.size() - 1; i >= 0; i--)
        {
            // Update maxDigit if current digit is larger
            if (s[i] > maxDigit)
            {
                maxDigit = s[i];
                maxIndx = i;
            }
            
            // Found a smaller digit before a larger one
            else if (s[i] < maxDigit)
            {
                l = i;
                r = maxIndx;
            }
        }
    
        // If no swap needed, return original
        if (l == -1) return s;
    
        // Perform swap
        swap(s[l], s[r]);
        
        return s;
    }
};

/*
*
* Dry Run
* Input: s = "768"
* * Initialization:
* maxDigit = '0', maxIndx = -1, l = -1, r = -1
* * Loop (right to left):
* i = 2, s[2] = '8'. '8' > '0' -> maxDigit = '8', maxIndx = 2
* i = 1, s[1] = '6'. '6' < '8' -> l = 1, r = 2
* i = 0, s[0] = '7'. '7' < '8' -> l = 0, r = 2
* * After loop:
* l = 0, r = 2
* swap(s[0], s[2]) -> '7' and '8' swap. s becomes "867".
* * Output: "867"
*
*/
```

---

## 🔍 Key Insights

- **Direction of Traversal:** Traversing the array from **right to left** guarantees that as we move backwards, any number that is smaller than the tracked maximum digit *must* be on the left side of it. 
- **Most Significant Swap:** Since we want the largest possible number, we continually overwrite the `l` and `r` variables when we find a smaller digit further to the left. The final `l` index will be the most significant position that can be improved.
- **Constant Extra Space:** Tracking just indices and max character variables allows us to solve the problem dynamically without requiring auxiliary arrays, achieving pure $O(1)$ space.

---

## 🔭 Further Exploration

If you enjoyed this problem, you might also like to try these related concepts:
- **Maximum Swap (LeetCode 670):** A highly similar problem that extends the logic slightly.
- **Next Greater Element:** Problems involving monotonic stacks.
- **Lexicographical Array Sorting:** Practice arranging numerical strings for the highest concatenated value.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Largest number in one swap](https://www.geeksforgeeks.org/problems/largest-number-in-one-swap1520/1)

---

## 👨‍💻 Author
[@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Strings` `Data Structures` `Greedy` `GeeksforGeeks` `C++`