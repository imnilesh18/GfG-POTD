# 🟩 XOR of Number Range 

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-50.0%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given two integers `l` and `r`, find the **bitwise XOR** of all integers in the range `[l, r]` (both inclusive) .

---

## 🧪 Examples

### Example 1
```text
Input: l = 4, r = 8
Output: 8
Explanation: The XOR of all integers from 4 to 8 is (4 ^ 5 ^ 6 ^ 7 ^ 8) = 8. 
```

### Example 2
```text
Input: l = 2, r = 4
Output: 5
Explanation: The XOR of all integers from 2 to 4 is (2 ^ 3 ^ 4) = 5. 
```

### Example 3
```text
Input: l = 5, r = 9
Output: 5
Explanation: The XOR of all integers from 5 to 9 is (5 ^ 6 ^ 7 ^ 8 ^ 9) = 5. 
```

<details>
<summary><b>📖 Example Breakdown (Walkthrough for Example 1: l = 4, r = 8)</b></summary>

Let's trace the bitwise XOR of integers from `4` to `8` in binary:
* `4` = `0100`
* `5` = `0101`
* `6` = `0110`
* `7` = `0111`
* `8` = `1000`

Step-by-step XOR evaluation:
1. `4 ^ 5` = `0100 ^ 0101` = `0001` (`1`)
2. `1 ^ 6` = `0001 ^ 0110` = `0111` (`7`)
3. `7 ^ 7` = `0111 ^ 0111` = `0000` (`0`)
4. `0 ^ 8` = `0000 ^ 1000` = `1000` (`8`)

Using the prefix XOR property:
* $\text{XOR}(0 \dots 3) = 0 \oplus 1 \oplus 2 \oplus 3 = 0$
* $\text{XOR}(0 \dots 8) = 0 \oplus 1 \oplus 2 \oplus 3 \oplus 4 \oplus 5 \oplus 6 \oplus 7 \oplus 8 = 8$
* $\text{XOR}(4 \dots 8) = \text{XOR}(0 \dots 3) \oplus \text{XOR}(0 \dots 8) = 0 \oplus 8 = 8$

</details>

---

## 🔒 Constraints

> * $1 \le l \le r \le 10^9$ 
> * **Expected Time Complexity:** $\mathcal{O}(1)$ 
> * **Expected Auxiliary Space:** $\mathcal{O}(1)$ 

---

## 💡 Solution Approaches

### Why Brute-Force Fails
Iterating from `l` to `r` and accumulating `ans ^= i` takes $\mathcal{O}(r - l)$ time. Since $r$ can be up to $10^9$ , a linear loop will result in a **Time Limit Exceeded (TLE)** verdict.

---

### 🚀 Optimized Approach: Prefix XOR Pattern in $\mathcal{O}(1)$

#### Intuition
The cumulative XOR of consecutive non-negative integers starting from `0` repeats in a strict cycle of length `4` based on `n % 4` . Furthermore, because XOR is its own inverse ($x \oplus x = 0$), taking the XOR of prefix `[0, l - 1]` with prefix `[0, r]` cancels out all numbers from `0` to `l - 1`, leaving only the XOR of `[l, r]` .

#### Step-by-Step Approach
1. Create a helper function `xorUpto(n)` that returns $0 \oplus 1 \oplus \dots \oplus n$ in $\mathcal{O}(1)$ time by checking `n % 4` .
2. Compute `xorUpto(l - 1)` for the prefix just before `l` .
3. Compute `xorUpto(r)` for the prefix up to `r` .
4. Return `xorUpto(l - 1) ^ xorUpto(r)` .

#### C++ Implementation

```cpp
// Intuition: The prefix XOR from 0 to n repeats in a predictable cycle of length 4 based on n % 4. Using the self-canceling property of XOR (x ^ x = 0), XOR(l..r) equals XOR(0..l-1) ^ XOR(0..r).
// Approach:
// 1. Define a helper function xorUpto(n) that computes 0 ^ 1 ^ ... ^ n in O(1) time using n % 4.
// 2. Return xorUpto(l - 1) ^ xorUpto(r) so common prefix terms from 0 to l - 1 cancel out.
// Time Complexity: O(1), as both modulo and bitwise XOR operations execute in constant time.
// Space Complexity: O(1), since no auxiliary data structures are used.

class Solution {
  private:
    // Computes bitwise XOR of all integers from 0 to n in O(1) time
    int xorUpto(int n) {
        int rem = n % 4; // Prefix XOR follows a 4-element cycle
        if (rem == 0) return n;
        if (rem == 1) return 1;
        if (rem == 2) return n + 1;
        return 0; // Case when rem == 3
    }

  public:
    // Returns XOR of range [l, r] by canceling prefix [0, l - 1]
    int findXOR(int l, int r) {
        return xorUpto(l - 1) ^ xorUpto(r);
    }
};

/*
*
* Dry Run
*
* Input: l = 4, r = 8
* Step 1: Call xorUpto(l - 1) -> xorUpto(3)
*         rem = 3 % 4 = 3 -> returns 0 (since 0 ^ 1 ^ 2 ^ 3 = 0)
* Step 2: Call xorUpto(r) -> xorUpto(8)
*         rem = 8 % 4 = 0 -> returns 8 (since 0 ^ 1 ^ ... ^ 8 = 8)
* Step 3: Compute xorUpto(3) ^ xorUpto(8) = 0 ^ 8 = 8
* Output: 8
*
*/
```

---

## 🔑 Key Insights

* **4-Element Cycle of Prefix XOR:** Every block of 4 numbers starting at a multiple of 4 (`4k, 4k+1, 4k+2, 4k+3`) has a combined XOR of `0` because the lower two bits cycle through `00, 01, 10, 11` (which XOR to `00`) and higher bits appear an even number of times (4 times).

| `n % 4` | Prefix XOR `0 ^ 1 ^ ... ^ n` | Example (`n = 4..7`) |
| :---: | :---: | :---: |
| `0` | `n` | `0 ^ ... ^ 4 = 4` |
| `1` | `1` | `0 ^ ... ^ 5 = 1` |
| `2` | `n + 1` | `0 ^ ... ^ 6 = 7` |
| `3` | `0` | `0 ^ ... ^ 7 = 0` |

* **Range Query Trick:** Just like prefix sums use `sum(r) - sum(l - 1)`, prefix XOR uses `xorUpto(r) ^ xorUpto(l - 1)`  because XOR is both associative and self-inverse.

---

## 🔍 Further Exploration

* [Missing in Array (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/missing-number-in-array1416/1) — Classic application of XOR range cancellation.
* [Single Number / Unique Number I (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/element-appearing-once2552/1) — Finding the non-repeating element using $a \oplus a = 0$.
* [Two Odd Occurring (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/two-numbers-with-odd-occurrences5846/1) — Extending XOR properties with the rightmost set bit.

---

## 📚 References

* **Original Problem:** [XOR of Number Range — GeeksforGeeks](https://www.geeksforgeeks.org/problems/find-xor-of-numbers-from-l-to-r/1) 
* **Concept Guide:** [Calculate XOR from 1 to n — GeeksforGeeks](https://www.geeksforgeeks.org/calculate-xor-1-n/)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)
* **GeeksforGeeks:** [imnilesh18](https://www.geeksforgeeks.org/profile/imnilesh18)

---

## 🏷️ Tags

![Bit Magic](https://img.shields.io/badge/Topic-Bit%20Magic-blueviolet?style=flat-square) 
![Mathematics](https://img.shields.io/badge/Topic-Mathematics-teal?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square&logo=geeksforgeeks&logoColor=white)