# 🟧 Gray Code

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty Medium" />
  <img src="https://img.shields.io/badge/Accuracy-61.3%25-green?style=for-the-badge" alt="Accuracy 61.3%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

<br/>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a number `n`, generate bit patterns from `0` to `2^n - 1` such that successive patterns differ by exactly **one bit**.
A Gray code sequence must always begin with `0`.

---

## 📌 Constraints

> - `1 ≤ n ≤ 16`
> - **Expected Time Complexity:** `O(2^n)`
> - **Expected Auxiliary Space:** `O(2^n)`

---

## 💡 Examples

### Example 1

**Input:** `n = 2`
**Output:** `["00", "01", "11", "10"]`
**Explanation:** - `00` and `01` differ by one bit.
- `01` and `11` differ by one bit.
- `11` and `10` also differ by one bit.

### Example 2

**Input:** `n = 3`
**Output:** `["000", "001", "011", "010", "110", "111", "101", "100"]`
**Explanation:**
- `000` and `001` differ by one bit.
- `001` and `011` differ by one bit.
- `011` and `010` differ by one bit.
Similarly, every successive pattern differs by one bit.

<details>
<summary>📖 <b>Example Breakdown (n = 2)</b></summary>

Let's understand how the formula `i ^ (i >> 1)` generates the sequence:
- **i = 0 (00 in binary):** `00 ^ (00 >> 1) = 00 ^ 00 = 00`
- **i = 1 (01 in binary):** `01 ^ (01 >> 1) = 01 ^ 00 = 01`
- **i = 2 (10 in binary):** `10 ^ (10 >> 1) = 10 ^ 01 = 11`
- **i = 3 (11 in binary):** `11 ^ (11 >> 1) = 11 ^ 01 = 10`

Resulting Sequence: `00`, `01`, `11`, `10`. Each step changes exactly 1 bit!

</details>

---

## 🚀 Solution Approaches

### Optimized Bit Manipulation Approach

**Intuition:** The $i^{th}$ number in the Gray Code sequence can be directly derived from the integer $i$ using the bitwise XOR operation: `G(i) = i ^ (i >> 1)`. This simple formula perfectly guarantees that consecutive terms will only vary by exactly one bit.

```cpp
// Intuition: The i-th Gray code can be mathematically generated using the formula `i ^ (i >> 1)`. This avoids recursion and generates the sequence iteratively.
// Approach: Loop from `0` to `(2^n) - 1`. For each number, calculate its Gray code equivalent. Then, extract each bit from `n-1` down to `0` to build the `n`-bit binary string.
// Time Complexity: O(n * 2^n) - We iterate `2^n` times, and for each number, we run a nested loop of `n` steps to construct the binary string.
// Space Complexity: O(n * 2^n) - The result vector stores `2^n` strings, each of length `n`.

class Solution {
  public:
    vector<string> graycode(int n) {
        vector<string> res;
    
        // Loop from 0 to (2^n) - 1
        for (int i = 0; i < (1 << n); i++) {
            
            // Generate the i-th Gray code integer
            int g = i ^ (i >> 1);
    
            // Convert the code to an n-bit binary string
            string s = "";
            for (int j = n - 1; j >= 0; j--) {
                // Check if the j-th bit is set
                if (g & (1 << j))
                    s += '1';
                else
                    s += '0';
            }
    
            // Store the generated string in the result list
            res.push_back(s);
        }
    
        return res;
    }
};

/*
*
* Dry Run
*
* Input: n = 2
* Total iterations: (1 << 2) = 4
*
* Iteration i = 0:
* g = 0 ^ (0 >> 1) => 0 ^ 0 = 0
* j = 1: (0 & 2) == 0 => s = "0"
* j = 0: (0 & 1) == 0 => s = "00"
* res = ["00"]
*
* Iteration i = 1:
* g = 1 ^ (1 >> 1) => 1 ^ 0 = 1
* j = 1: (1 & 2) == 0 => s = "0"
* j = 0: (1 & 1) == 1 => s = "01"
* res = ["00", "01"]
*
* Iteration i = 2:
* g = 2 ^ (2 >> 1) => 2 ^ 1 = 3
* j = 1: (3 & 2) == 2 => s = "1"
* j = 0: (3 & 1) == 1 => s = "11"
* res = ["00", "01", "11"]
*
* Iteration i = 3:
* g = 3 ^ (3 >> 1) => 3 ^ 1 = 2
* j = 1: (2 & 2) == 2 => s = "1"
* j = 0: (2 & 1) == 0 => s = "10"
* res = ["00", "01", "11", "10"]
*
* Final Output: ["00", "01", "11", "10"]
*
*/
```

---

## 🧠 Key Insights

- **Mathematical Magic:** The bitwise trick `i ^ (i >> 1)` is the universally standard way to generate the $i^{th}$ element in a Gray Code sequence directly in $O(1)$ arithmetic steps. 
- **String Construction:** Using `(1 << j)` helps dynamically mask and extract the $j^{th}$ bit from the number, which allows us to format the integer seamlessly as an $n$-bit binary string.

---

## 🔍 Further Exploration

- **LeetCode Variant:** Try solving [LeetCode 89. Gray Code](https://leetcode.com/problems/gray-code/) which returns an array of integers instead of strings.
- **Circular Permutation in Binary Representation:** Another related problem that utilizes Gray Code concepts.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Gray Code](https://www.geeksforgeeks.org/problems/gray-code-1611215248/1)
- **Wikipedia:** [Gray code](https://en.wikipedia.org/wiki/Gray_code)

---

## 👨‍💻 Author

**Nilesh** 🔗 [GitHub: imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#BitManipulation` `#Recursion` `#DataStructures` `#Algorithms` `#GeeksforGeeks` `#CPP`