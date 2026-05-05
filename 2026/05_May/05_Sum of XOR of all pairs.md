# 🧮 Sum of XOR of all pairs

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/sum-of-xor-of-all-pairs0723/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-45.14%25-green?style=for-the-badge" alt="Accuracy: 45.14%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer array `arr[]` of size `n`, compute the sum of the **bitwise XOR** for all distinct pairs of elements. That is, consider every pair of indices `(i, j)` such that `0 ≤ i < j < n`, and calculate the total sum of `(arr[i] XOR arr[j])` over all such pairs.

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [7, 3, 5]
Output: 12
Explanation: 
All pairs (i, j) such that i < j and their XOR values are:
7 ^ 3 = 4
7 ^ 5 = 2
3 ^ 5 = 6
Sum of all XOR values = 4 + 2 + 6 = 12.
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>
<br>
We extract all possible distinct pairs from the array <code>[7, 3, 5]</code>:
<br><br>
1. <b>Pair (7, 3)</b>: 7 is <code>111</code> in binary, 3 is <code>011</code>. XOR is <code>100</code> (4 in decimal).<br>
2. <b>Pair (7, 5)</b>: 7 is <code>111</code> in binary, 5 is <code>101</code>. XOR is <code>010</code> (2 in decimal).<br>
3. <b>Pair (3, 5)</b>: 3 is <code>011</code> in binary, 5 is <code>101</code>. XOR is <code>110</code> (6 in decimal).<br><br>
Total Sum = 4 + 2 + 6 = 12.
</details>

### Example 2

```text
Input: arr[] = [5, 9, 7, 6] 
Output: 47
Explanation:
All pairs (i, j) such that i < j and their XOR values are:
5 ^ 9 = 12
5 ^ 7 = 2
5 ^ 6 = 3
9 ^ 7 = 14
9 ^ 6 = 15
7 ^ 6 = 1
Sum of all XOR values = 12 + 2 + 3 + 14 + 15 + 1 = 47.
```

### Example 3

```text
Input: arr[] = [10] 
Output: 0
Explanation: Since there are no pairs, sum is 0.
```

---

## ⚠️ Constraints

> - `1 ≤ n ≤ 10^5`
> - `1 ≤ arr[i] ≤ 10^5`

---

## 🛠️ Solution Approaches

### 1️⃣ Naive Approach (Iterative Method)

**Intuition & Approach**: 
The most straightforward way to solve this is to generate all possible distinct pairs from the array and sum up their individual XOR values. We can use two nested loops to iterate through the array and process every unique pair `(arr[i], arr[j])` where `i < j`.

```cpp
// Intuition: Generate all possible unique pairs and add their XOR results to a running total.
// Approach: Use a nested loop where the outer loop fixes the first element and the inner loop iterates through the subsequent elements to form pairs. Calculate the XOR and add it to the sum.
// Time Complexity: O(n^2) - Two nested loops iterate over the array of size n, leading to quadratic time complexity.
// Space Complexity: O(1) - Only a single variable is used to keep track of the sum, requiring constant extra space.

class Solution {
  public:
    long sumXOR(vector<int> arr) {
        long sum = 0;
    
        // Consider all pairs (arr[i], arr[j]) such that
        // i < j
        for (int i = 0; i < arr.size() - 1; i++) {
            // Inner loop starts from i+1 to avoid duplicate pairs and self-pairing
            for (int j = i + 1; j < arr.size(); j++) {
                // Add the XOR of the current pair to the total sum
                sum += arr[i] ^ arr[j];
            }
        }
    
        return sum;
    }
};

/*
* Dry Run
*
* arr = [7, 3, 5]
* Initial sum = 0
* 
* Outer loop i = 0 (value 7):
* Inner loop j = 1 (value 3): 7 ^ 3 = 4. sum = 0 + 4 = 4.
* Inner loop j = 2 (value 5): 7 ^ 5 = 2. sum = 4 + 2 = 6.
* 
* Outer loop i = 1 (value 3):
* Inner loop j = 2 (value 5): 3 ^ 5 = 6. sum = 6 + 6 = 12.
* 
* Outer loop terminates. 
* Final sum returned is 12.
*/
```

---

### 2️⃣ Expected Approach (Bit Manipulation)

**Intuition & Approach**: 
To optimize the solution to O(n), we can evaluate the contribution of each bit position (from 0 to 31) independently across all numbers. 

For the XOR of two bits to be `1`, the bits must be different (one must be `0` and the other must be `1`). For any given bit position `i`, if we count how many numbers in the array have a `0` at that position (`zc`) and how many have a `1` (`oc`), the total number of pairs that will produce a `1` at the `i-th` position in their XOR result is simply `zc * oc`. 

The positional value of this bit is `2^i` (or `1 << i`). Therefore, the total contribution of the `i-th` bit to our final sum will be `(zc * oc) * 2^i`. By summing these contributions across all 32 bit positions, we calculate the grand total in linear time.

```cpp
// Intuition: Evaluate the XOR sum bit by bit rather than pair by pair, leveraging the fact that XOR yields 1 only for differing bits.
// Approach: Loop through all 32 bit positions. For each bit, count the number of elements with that bit set to 1 and unset (0). Multiply these counts together to find the number of pairs generating a 1 at this bit, scale it by its positional value (2^i), and add it to the total sum.
// Time Complexity: O(n) - We loop exactly 32 times over the array of size n, which simplifies to O(n) linear time.
// Space Complexity: O(1) - Only a few variables for counting and summing are required, taking constant space.

class Solution {
  public:
    long sumXOR(vector<int>& arr) {
        long sum = 0;
        
        // Iterate over all 32 bit positions
        for (int i = 0; i < 32; i++) {
            // Count of zeros (zc) and ones (oc) for the current bit position
            int zc = 0, oc = 0; 
            
            // Check the i-th bit for every number in the array
            for (int j = 0; j < arr.size(); j++) {
                // If the i-th bit is set, increment one-count
                if ((arr[j] >> i) & 1)
                        oc++;
                    else
                        // Otherwise, increment zero-count
                        zc++;
            }
            
            // Adding the total contribution of the current bit position to the sum
            // Contribution = (pairs creating a 1) * (value of the bit)
            sum += (long) oc * zc * (1 << i); 
        }
        
        return sum;
    }
};

/*
* Dry Run
*
* arr = [7, 3, 5] (Binary: 7=111, 3=011, 5=101)
* Initial sum = 0
* 
* Bit position i = 0 (rightmost bit):
* Counts: zc = 0 (no zeros at bit 0), oc = 3 (all end in 1)
* Contribution: 0 * 3 * (2^0) = 0
* sum = 0 + 0 = 0
* 
* Bit position i = 1:
* Counts: zc = 1 (number 5 has 0 at bit 1), oc = 2 (numbers 7, 3 have 1)
* Contribution: 1 * 2 * (2^1) = 2 * 2 = 4
* sum = 0 + 4 = 4
* 
* Bit position i = 2:
* Counts: zc = 1 (number 3 has 0 at bit 2), oc = 2 (numbers 7, 5 have 1)
* Contribution: 1 * 2 * (2^2) = 2 * 4 = 8
* sum = 4 + 8 = 12
* 
* For i = 3 to 31, oc will be 0, so contribution remains 0.
* Final sum returned is 12.
*/
```

---

## 🧠 Key Insights

* **Bitwise Independence**: The result of a bitwise operation at any specific bit position `i` depends *only* on the `i-th` bits of the operands. This allows us to break down O(n^2) pair problems into O(n) frequency counting problems.
* **Combinatorics in Bit Magic**: To form a pair `(x, y)` whose XOR has a `1` at the `i-th` bit, exactly one number must have a `0` and the other must have a `1`. The total valid pair combinations for this bit is simply `count(0) * count(1)`.

---

## 🔍 Further Exploration

*   [Count pairs with given XOR](https://www.geeksforgeeks.org/count-pairs-with-given-xor/)
*   [Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)
*   [Sum of bit differences among all pairs](https://www.geeksforgeeks.org/sum-of-bit-differences-among-all-pairs/)

---

## 🔗 References

*   **GeeksforGeeks Problem**: [Sum of XOR of all pairs](https://www.geeksforgeeks.org/problems/sum-of-xor-of-all-pairs0723/1)

---

## 👨‍💻 Author

*   **GitHub**: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Arrays` `#BitMagic` `#DataStructures` `#DynamicProgramming` `#GeeksforGeeks`