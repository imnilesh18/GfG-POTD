# 🔡 Lexicographically Smallest After Removing K

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/lexicographically-smallest-after-removing-k/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge)](#)
[![Accuracy: 49.97%](https://img.shields.io/badge/Accuracy-49.97%25-10B981?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-2563EB?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](#)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a string `s` consisting of $n$ lowercase characters. Return the lexicographically smallest string after removing exactly $k$ characters from the string. 

Before removing the characters, you have to **correct the value of $k$**: 
* If the length of the string is a power of 2, reduce $k$ by half ($k = k / 2$).
* Else, multiply $k$ by 2 ($k = k \times 2$). 

You can remove any $k$ characters.

> **Note:** If it is not possible to remove $k$ (the value of $k$ after correction) characters or if the resulting string is empty, return `"-1"`.

---

## 💡 Examples

### Example 1
```text
Input: s = "fooland", k = 2
Output: "and" 

```

* The size of the string $n = 7$, which is **not** a power of 2.
* Hence, the corrected $k = 2 \times 2 = 4$.
* After removing 4 characters from the given string, the lexicographically smallest possible string left is `"and"`.

### Example 2

```text
Input: s = "code", k = 4
Output: "cd"

```

* The length of the string $n = 4$, which is a power of 2 ($2^2$).
* Hence, the corrected $k = 4 / 2 = 2$.
* The lexicographically smallest string after the removal of 2 characters is `"cd"`.

---

## 🚧 Constraints

> * $1 \le n \le 10^5$
> * $1 \le k \le 10^5$
> 
> 

---

## 🛠️ Solution Approaches

### Optimized Approach: Greedy + Monotonic Stack

**Brief Summary / Intuition:**
To obtain the lexicographically smallest string, we need to ensure that smaller characters appear as early as possible. This means if we encounter a character that is smaller than the previous character we kept, and we still have "removals" left (i.e., $k > 0$), we should discard the previous larger character. A string acting as a stack is perfect for this: we push characters onto it and pop from the back whenever the current character is smaller and removals are available.

```cpp
// Intuition: To get the lexicographically smallest string, we must remove larger characters that appear before smaller characters. A stack (or string acting as one) allows us to efficiently track and drop these characters while scanning.
// Approach: First, find length 'n' and update 'k'. If n is a power of 2, halve k; else double k. If 'k' >= 'n', return "-1". Iterate through 's', using a string as a stack. Pop the stack if the current character is smaller than the stack's top and we still need to remove characters. Finally, if k > 0, remove remaining characters from the end.
// Time Complexity: O(n) as each character in the string is pushed and popped at most once.
// Space Complexity: O(n) to store the characters in the resulting string which acts as our stack.

class Solution {
  public:
    string lexicographicallySmallest(string &s, int k) {
        int n = s.length();
        
        // Adjust k based on whether n is a power of 2 using bitwise AND
        if ((n & (n - 1)) == 0) {
            k = k / 2;
        } else {
            k = k * 2;
        }
        
        // If we need to remove all characters or more, return "-1"
        if (k >= n) {
            return "-1";
        }
        
        string st = "";
        
        for (char c : s) {
            // Remove larger characters from the back if k > 0
            while (!st.empty() && k > 0 && st.back() > c) {
                st.pop_back();
                k--;
            }
            // Push the current character into the string (stack)
            st.push_back(c);
        }
        
        // If k is still greater than 0 (e.g., characters were already in ascending order)
        // remove the remaining required characters from the end
        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }
        
        return st;
    }
};

/*
*
* Dry Run
*
* Input: s = "fooland", k = 2
* 
* Initialization:
* n = 7. 7 is not a power of 2, so k = k * 2 = 4.
* k (4) is less than n (7), so we proceed.
* st = ""
* 
* Iteration:
* c = 'f', st = "f"
* c = 'o', o is not smaller than f, st = "fo"
* c = 'o', o is not smaller than o, st = "foo"
* c = 'l', l is smaller than o. pop o (k=3), pop o (k=2). st = "fl"
* c = 'a', a is smaller than l. pop l (k=1). a is smaller than f. pop f (k=0). st = "a"
* c = 'n', k is 0, st = "an"
* c = 'd', k is 0, st = "and"
* 
* Result:
* k is 0, loop finishes.
* return "and"
*
*/

```

---

## 🧠 Key Insights

* **Power of 2 Check:** The condition `(n & (n - 1)) == 0` is an elegant bitwise trick to check if a number is a power of 2 in $O(1)$ time.
* **Monotonic Stack Pattern:** Building the result string by treating it as a stack allows us to maintain a monotonically increasing sequence of characters as much as the removal budget ($k$) allows.
* **Edge Case Handling:** If the string is fully traversed and we still have $k > 0$ (which happens if the characters were already sorted like `"abc"`), we simply drop the remaining characters from the end.

---

## 🔗 Further Exploration

* **Related Patterns:** Greedy Algorithms, Monotonic Stacks
* **Similar Problems:**
* Remove K Digits (LeetCode / GFG)
* Lexicographically Smallest Subsequence



---

## 📚 References

* [GeeksforGeeks Problem: Lexicographically smallest after removing k](https://www.geeksforgeeks.org/problems/lexicographically-smallest-after-removing-k/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`Strings` `Stack` `Data Structures` `Greedy` `GeeksforGeeks`
