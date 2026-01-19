# 📉 Remove K Digits

<div align="center">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D35?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
    <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks" alt="Difficulty" />
    <img src="https://img.shields.io/badge/Accuracy-26.8%25-blue?style=for-the-badge" alt="Accuracy" />
    <img src="https://img.shields.io/badge/Points-4-green?style=for-the-badge" alt="Points" />
    <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License" />
</div>

> [!IMPORTANT]
> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/remove-k-digits/1) problem.

---

## 📝 Problem Statement

Given a non-negative integer `s` represented as a string and an integer `k`, remove exactly `k` digits from the string so that the resulting number is the **smallest** possible, while maintaining the relative order of the remaining digits.

**Note:**
* The resulting number must not contain any leading zeros.
* If the resulting number is an empty string after the removal, return `"0"`.

---

## 🔍 Examples

### Example 1
```text
Input: s = "4325043", k = 3
Output: "2043"
Explanation: Remove the three digits 4, 3, and 5 to form the new number "2043" which is smallest among all possible removal.
```

### Example 2
```text
Input: s = "765028321", k = 5
Output: "221"
Explanation: Remove the five digits 7, 6, 5, 8 and 3 to form the new number "0221". Since we are not supposed to keep leading 0s, we get "221".
```

<details>
<summary><b>📖 Example Breakdown: s = "1432219", k = 3</b></summary>

1.  **Initial:** `s = "1432219"`, `k = 3`, `Stack = []`
2.  **'1'**: Stack is empty. Push '1'. `Stack = [1]`
3.  **'4'**: '4' > '1'. Push '4'. `Stack = [1, 4]`
4.  **'3'**: '3' < '4'. Pop '4'. `k = 2`. Push '3'. `Stack = [1, 3]`
5.  **'2'**: '2' < '3'. Pop '3'. `k = 1`. Push '2'. `Stack = [1, 2]`
6.  **'2'**: '2' not < '2'. Push '2'. `Stack = [1, 2, 2]`
7.  **'1'**: '1' < '2'. Pop '2'. `k = 0`. Push '1'. `Stack = [1, 2, 1]`
8.  **'9'**: '9' > '1'. Push '9'. `Stack = [1, 2, 1, 9]`
9.  **Construct Result**: The stack contains digits for `1219`. Return `"1219"`.

</details>

---

## 🚧 Constraints

* $1 \le k \le |s| \le 10^6$

---

## 💡 Solution Approaches

### Method: Greedy Strategy with Stack

#### Intuition
The relative order of digits matters most for the magnitude of the number. A smaller digit placed at a more significant position (left) reduces the overall value more than a smaller digit at a less significant position. Therefore, whenever we encounter a digit that is **smaller** than the digit immediately preceding it, we should remove the preceding digit (if we still have removals `k` available). This "peak" removal strategy ensures the sequence remains increasing as much as possible. A Stack is the perfect data structure to maintain this sequence and perform removals efficiently from the end.

#### Code (C++)

```cpp
// Intuition: We want the smallest digits as early as possible. If the current digit is smaller than the previous one (stack top), removing the previous one makes the number smaller. We repeat this greedily.
// Approach: Use a stack to build the answer. Iterate through s; if current char < stack.top, pop stack and decrement k. Push current char (handle leading zeros). Finally, truncate remaining k from end and reconstruct string.
// Time Complexity: O(N) - Each character is pushed and popped at most once.
// Space Complexity: O(N) - Stack stores the characters of the resulting string.

class Solution {
  public:
    string removeKdig(string &s, int k) {
        int n = s.size();
        stack<char> st;
    
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
    
            // Remove larger digits when possible
            while (!st.empty() && k > 0 && st.top() > c) {
                st.pop();
                k -= 1;
            }
    
            // Push current digit, avoiding leading zeros for empty stack
            if (!st.empty() || c != '0')
                st.push(c);
        }
    
        // Remove remaining digits if any (e.g., for increasing sequence "12345")
        while (!st.empty() && k--)
            st.pop();
    
        if (st.empty())
            return "0";
    
        // Build result from stack by placing chars from end of string backwards
        while (!st.empty()) {
            s[n - 1] = st.top();
            st.pop();
            n -= 1;
        }
    
        // Return the substring starting from the first valid character
        return s.substr(n);
    }
};

/*
*
* Dry Run
* Input: s = "10200", k = 1
*
* i=0, c='1': Stack=[1]
* i=1, c='0': '0' < '1', pop '1', k=0. Stack empty.
* c is '0' and stack empty -> don't push (leading zero logic). Stack=[]
* i=2, c='2': Stack=[2]
* i=3, c='0': '0' < '2', but k=0. Loop condition fails.
* Push '0'. Stack=[2, 0]
* i=4, c='0': Push '0'. Stack=[2, 0, 0]
*
* Loop end. k=0.
* Reconstruct: s[4]='0', s[3]='0', s[2]='2'.
* Return substring from index 2 -> "200"
*
*/
```

---

## 🗝️ Key Insights

1.  **Monotonic Stack:** The core logic is maintaining a monotonically non-decreasing sequence of digits.
2.  **Greedy Choice:** A dip in value (current < previous) is always an opportunity to reduce the total value by removing the previous digit.
3.  **Leading Zeros:** Special care must be taken not to push `0` onto an empty stack, as leading zeros don't contribute to the value.
4.  **String Reuse:** The provided solution cleverly reuses the input string `s` to construct the output from the stack to save some allocation overhead, though a separate result string is also common.

---

## 🔗 References

* [**GeeksforGeeks Problem Link**](https://www.geeksforgeeks.org/problems/remove-k-digits/1)
* [**LeetCode Equivalent (402)**](https://leetcode.com/problems/remove-k-digits/)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Stack](https://img.shields.io/badge/Topic-Stack-blue?style=for-the-badge)
![Greedy](https://img.shields.io/badge/Topic-Greedy-green?style=for-the-badge)
![Data Structures](https://img.shields.io/badge/Topic-Data_Structures-orange?style=for-the-badge)
![Company](https://img.shields.io/badge/Company-Microsoft-purple?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

> [!WARNING]
> This repository is for educational purposes only. Please do not use this code for plagiarism or academic dishonesty.