# 🔠 Roll Characters of String

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-35.76%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given a string `s` consisting of lowercase English letters and an integer array `roll[]`, perform a sequence of roll operations on the string.

For each value `roll[i]`, increment each of the first `roll[i]` characters of the string by 1 in the English alphabet. After `'z'`, the character wraps around to `'a'`.

Return the final string after applying all roll operations.

**Note:** A roll operation affects the current state of the string, including all previous modifications.

---

## 💡 Examples

### Example 1

```text
Input: s = "bca", roll[] = [1, 2, 3]
Output: "eeb"
```

<details>
<summary>📖 Example 1 Breakdown</summary>

Initially, `s` = "bca"
*   `roll[0] = 1`: Roll the first 1 character. "bca" -> "cca"
*   `roll[1] = 2`: Roll the first 2 characters. "cca" -> "dda"
*   `roll[2] = 3`: Roll the first 3 characters. "dda" -> "eeb"

After applying all the roll operations, the final string is "eeb".
</details>

### Example 2

```text
Input: s = "zcza", roll[] = [1, 1, 3, 4]
Output: "debb"
```

<details>
<summary>📖 Example 2 Breakdown</summary>

Initially, `s` = "zcza"
*   Roll first 1 character: "zcza" -> "acza"
*   Roll first 1 character again: "acza" -> "bcza"
*   Roll first 3 characters: "bcza" -> "cdaa"
*   Roll first 4 characters: "cdaa" -> "debb"

Therefore, the final string is "debb".
</details>

---

## 🛑 Constraints

*   $1 \leq s.size(), roll.size() \leq 10^5$
*   $1 \leq roll[i] \leq s.size()$
*   `s` consists only of lowercase English alphabets.

---

## 🛠️ Solution Approaches

### Optimal Approach: Difference Array (Prefix Sum)

**Intuition:** 
Updating the string character by character for every roll operation would result in an inefficient $O(N \times Q)$ time complexity. Instead, we can use a difference array to record the boundaries of each roll operation. Computing the prefix sum of this difference array gives us the exact number of times each character needs to be shifted in just $O(N + Q)$ time.

```cpp
// Intuition: Instead of updating the string for every roll operation, use a difference array to efficiently count the total shifts for each character in O(1) per operation.
// Approach: 
// 1. Create a difference array `diff` of size N + 1.
// 2. For each value `r` in `roll`, mark the range increment: `diff[0]++` and `diff[r]--`.
// 3. Compute the prefix sum of `diff` on the fly to get the exact number of rolls for each character.
// 4. Shift each character using modulo 26 arithmetic to handle the 'z' to 'a' wrap-around.
// Time Complexity: O(N + M) where N is the length of the string and M is the size of the roll array. Both arrays are traversed independently.
// Space Complexity: O(N) to store the difference array of size N + 1.

class Solution {
  public:
    string findRollOut(string& s, vector<int>& roll) {
        int n = s.length();
        // Difference array to keep track of increments
        vector<int> diff(n + 1, 0);
        
        // For each roll value 'r', increment characters from index 0 to r-1
        for (int r : roll) {
            diff[0]++;
            diff[r]--;
        }
        
        // Accumulate the prefix sums to get the actual number of rolls
        int current_rolls = 0;
        for (int i = 0; i < n; ++i) {
            current_rolls += diff[i];
            
            // Calculate the new character with wrap-around using modulo 26
            int shift = current_rolls % 26;
            s[i] = 'a' + (s[i] - 'a' + shift) % 26;
        }
        
        return s;
    }
};

/*
* Dry Run
* Input: s = "bca", roll = [1, 2, 3]
*
* Initialization:
* n = 3, diff = [0, 0, 0, 0]
*
* Step 1: Processing roll array into difference array
* r = 1 -> diff[0]++, diff[1]-- -> diff = [1, -1, 0, 0]
* r = 2 -> diff[0]++, diff[2]-- -> diff = [2, -1, -1, 0]
* r = 3 -> diff[0]++, diff[3]-- -> diff = [3, -1, -1, -1]
*
* Step 2: Accumulating prefix sums and updating string
* i = 0: current_rolls = 0 + 3 = 3. shift = 3. s[0] = 'b' + 3 = 'e'
* i = 1: current_rolls = 3 + (-1) = 2. shift = 2. s[1] = 'c' + 2 = 'e'
* i = 2: current_rolls = 2 + (-1) = 1. shift = 1. s[2] = 'a' + 1 = 'b'
*
* Final String: "eeb"
*/
```

---

## 🧠 Key Insights

*   **Difference Array Technique:** Whenever you need to perform multiple range increments `[L, R]`, a difference array allows you to record the operation in $O(1)$ by doing `arr[L] += X` and `arr[R+1] -= X`.
*   **Modulo Arithmetic:** To wrap letters around the alphabet (e.g., shifting 'z' by 1 becomes 'a'), use `(char - 'a' + shift) % 26` to keep the offset strictly within the 0-25 range.

---

## 🔍 Further Exploration
*   GeeksforGeeks: Difference Array | Range update query in O(1)
*   LeetCode 2381. Shifting Letters II (Similar concept with both forward and backward shifts)

---

## 🔗 References

*   **Original Problem:** [Roll Characters of String on GeeksforGeeks](https://www.geeksforgeeks.org/problems/roll-the-characters-of-a-string2127/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Arrays` `#Strings` `#Difference-Array` `#Prefix-Sum` `#GeeksforGeeks`