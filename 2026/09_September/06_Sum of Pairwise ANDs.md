# 🔢 Sum of Pairwise ANDs

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/sum-of-products5049/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty">
  <img src="https://img.shields.io/badge/Accuracy-50.93%25-green?style=for-the-badge" alt="Accuracy">
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points">
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License">
</p>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of integers, calculate the sum of bitwise AND for all pairs of elements such that the first index is less than the second index ($i < j$).

---

## 💡 Examples

### Example 1
```text
Input: arr = [5, 10, 15]
Output: 15
Explanation: 
Consider all pairs of elements where the first index is less than the second index (i < j).
For the array [5, 10, 15], the valid pairs are:
(5, 10)  -> 5 & 10  = 0
(5, 15)  -> 5 & 15  = 5
(10, 15) -> 10 & 15 = 10
Now, add all these results: 0 + 5 + 10 = 15
```

### Example 2
```text
Input: arr = [10, 20, 30, 40]
Output: 46
Explanation: 
For the array [10, 20, 30, 40], the valid pairs are:
(10, 20) -> 0, (10, 30) -> 10, (10, 40) -> 8
(20, 30) -> 20, (20, 40) -> 0, (30, 40) -> 8
Result: 0 + 10 + 8 + 20 + 0 + 8 = 46
```

<details>
<summary><b>📖 Example Breakdown (Array: [5, 10, 15])</b></summary>
<br>

Instead of looking at pairs directly, look at the binary representations bit by bit:
* `5`  = `0101`
* `10` = `1010`
* `15` = `1111`

Let's calculate the contribution of each bit position:
1. **Bit 0 (Value 1):** Set in 5 and 15. Total set = 2. Pairs = 2 * 1 / 2 = 1 pair. Contribution = 1 * (2^0) = **1**.
2. **Bit 1 (Value 2):** Set in 10 and 15. Total set = 2. Pairs = 1 pair. Contribution = 1 * (2^1) = **2**.
3. **Bit 2 (Value 4):** Set in 5 and 15. Total set = 2. Pairs = 1 pair. Contribution = 1 * (2^2) = **4**.
4. **Bit 3 (Value 8):** Set in 10 and 15. Total set = 2. Pairs = 1 pair. Contribution = 1 * (2^3) = **8**.

**Total Sum** = 1 + 2 + 4 + 8 = **15**.
</details>

---

## ⚠️ Constraints

```text
1 ≤ arr.size() ≤ 10^5
1 ≤ arr[i] ≤ 10^8
```

---

## 🛠️ Solution Approaches

### 1. Brute-Force Approach
* **Intuition:** The most straightforward way is to generate all possible pairs $(i, j)$ using nested loops, perform the bitwise AND operation, and keep a running sum.
* **Complexity:** Time Complexity is O(n²). Since `n` can be up to 10⁵, `n²` will be 10¹⁰ operations, resulting in a Time Limit Exceeded (TLE) error. Space Complexity is O(1).

### 2. Optimized Approach (Bit Manipulation & Combinatorics)
* **Intuition:** The bitwise AND of two numbers is 1 at a specific bit position *only if* both numbers have that bit set to 1. By counting how many numbers have a particular bit set, we can easily calculate how many pairs will have that bit set in their AND result. 
* **Calculation:** If `k` numbers have the `i-th` bit set, the number of valid pairs we can form is `k * (k - 1) / 2`. The decimal value contributed by this bit across all those pairs is `(2^i) * (k * (k - 1) / 2)`.
* **Complexity:** We loop exactly 32 times (for each bit) regardless of how large the numbers are. Inside, we loop `n` times. The time complexity becomes O(32 * n), which simplifies to O(n).

### C++ Source Code

```cpp
// Intuition: Instead of calculating AND for O(n^2) pairs, we evaluate the contribution of each bit across the entire array.
// Approach: For every bit position (0 to 31), count how many numbers in the array have this bit set. If 'k' numbers have the bit set, they form k*(k-1)/2 pairs. Multiply this pair count by the bit's decimal value (2^i) and add it to the total sum.
// Time Complexity: O(n) — We traverse the array of size 'n' exactly 32 times, resulting in O(32 * n) which simplifies to O(n).
// Space Complexity: O(1) — We only use a few variables (ans, i, j, k) requiring constant extra space.

class Solution {
  public:
    long long pairAndSum(vector<int> &arr) {
        long long ans = 0; 

        int n = arr.size();

        // Traverse over all bits (0 to 31 for standard integers)
        for (int i = 0; i < 32; i++) {
            
            // Count number of elements with the i'th bit set
            long long k = 0; 
            for (int j = 0; j < n; j++) {
                if ((arr[j] & (1LL << i))) {
                    k++;
                }
            }

            // There are k set bits, meaning k*(k-1)/2 valid pairs.
            // Every pair adds 2^i to the final answer. Therefore,
            // we add "2^i * [k*(k-1)/2]" to the total sum.
            ans += (1LL << i) * (k * (k - 1) / 2);
        }

        return ans;
    }
};

/*
*
* Dry Run
* Input: arr = [5, 10, 15]
*
* Binary Breakdown:
* 5  -> 0101
* 10 -> 1010
* 15 -> 1111
*
* i = 0 (Value = 1):
* Set in 5 and 15 (k=2). Pairs = 2 * 1 / 2 = 1.
* Add to ans = 1 * (2^0) = 1.
*
* i = 1 (Value = 2):
* Set in 10 and 15 (k=2). Pairs = 2 * 1 / 2 = 1.
* Add to ans = 1 * (2^1) = 2.
*
* i = 2 (Value = 4):
* Set in 5 and 15 (k=2). Pairs = 2 * 1 / 2 = 1.
* Add to ans = 1 * (2^2) = 4.
*
* i = 3 (Value = 8):
* Set in 10 and 15 (k=2). Pairs = 2 * 1 / 2 = 1.
* Add to ans = 1 * (2^3) = 8.
*
* Final Answer = 1 + 2 + 4 + 8 = 15.
*
*/
```

---

## 🧠 Key Insights
1. **Vertical over Horizontal Analysis:** Rather than pairing array elements (horizontal evaluation), assessing the array column-by-column at the bit level (vertical evaluation) dramatically reduces redundant operations.
2. **Combinatorics (`nC2`):** When calculating possible pairs from a subset of elements, the combination formula `k * (k - 1) / 2` calculates all unique groupings in O(1) time without looping.
3. **Preventing Overflow:** Use `1LL << i` to perform bit shifting to safely prevent 32-bit signed integer overflow when shifting bits past `30`.

---

## 🔍 Further Exploration
* **Sum of XOR of all pairs:** A very similar problem where bitwise logic solves the O(n²) bottleneck. In XOR, you multiply the count of set bits by the count of unset bits.
* **Maximum AND Value:** Finding the maximum pairwise bitwise AND in an array.
* **Bit Magic Techniques:** Review bit manipulation tricks to check, set, and clear specific bits efficiently.

---

## 🔗 References
* **GeeksforGeeks Problem:** [Sum of Pairwise ANDs](https://www.geeksforgeeks.org/problems/sum-of-products5049/1)
* **Bit Manipulation Guide:** [GeeksforGeeks Bit Magic](https://www.geeksforgeeks.org/bitwise-algorithms/)

---

## 👤 Author
* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#Mathematics` `#Bit-Magic` `#Combinatorics` `#GeeksforGeeks` `#C++` `#Optimized-Approach`