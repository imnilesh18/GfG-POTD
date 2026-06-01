# 🧮 Max Product Subset

[![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/maximum-product-subset-of-an-array/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy: 17.21%](https://img.shields.io/badge/Accuracy-17.21%25-green?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)
---
<div align="center">

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximum-product-subset-of-an-array/1).
</div>

---

## 📝 Problem Statement

Given an array `arr[]`, find and return the maximum product possible with the subset of elements present in the array.

> **Note:**
> * The maximum product can be of a single element also.
> * Since the product can be large, return it modulo `10^9 + 7`.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [-1, 0, -2, 4, 3]
Output: 24
Explanation: Maximum product will be ( -1 * -2 * 4 * 3 ) = 24

```

**Example 2:**

```text
Input: arr[] = [-1, 0]
Output: 0
Explanation: Maximum product will be ( -1 * 0) = 0

```

**Example 3:**

```text
Input: arr[] = [5]
Output: 5
Explanation: Maximum product will be 5.

```

**Input:** `arr[] = [-1, 0, -2, 4, 3]`

1. **Count Categories:** - Negatives: `-1, -2` (Total = 2)
* Zeros: `0` (Total = 1)
* Positives: `4, 3` (Total = 2)


2. Since the count of negative numbers is **even** (2), their product will automatically be positive (`-1 * -2 = 2`).
3. We multiply all non-zero numbers together: `(-1) * (-2) * 4 * 3 = 24`.
4. The maximum possible product is `24`.

---

## 🚫 Constraints

* `1 ≤ arr.size() ≤ 2 * 10^4`
* `-10 ≤ arr[i] ≤ 10`

---

## 🚀 Solution Approach

### **Greedy Approach**

To maximize the product of a subset, the key lies in handling the negative numbers and zeros properly:

1. **Zeros** always reset the product to zero, so they should be completely ignored unless the array forces us to return zero.
2. **Negative numbers**, when multiplied in pairs, yield a positive product. If the count of negative numbers is odd, leaving out the largest negative number (the one closest to 0) maximizes the product.
3. We can achieve this efficiently in an $O(N)$ time, two-pass (or one-pass if optimized further) solution counting zeros, negatives, and tracking the maximum negative element.

### **C++ Implementation**

```cpp
// Intuition: By counting positive, negative, and zero elements, we can easily determine the optimal subset. Even negative counts multiply to a positive product, while odd negative counts require dropping the smallest absolute negative to maximize the result.
// Approach: Traverse the array to count zeros and negatives while identifying the maximum negative number. Handle edge cases where the answer is strictly zero (all zeros, or a single negative with zeros). Traverse a second time to multiply the elements modulo 10^9+7, skipping zeros and exactly one instance of the maximum negative if the total negative count is odd.
// Time Complexity: O(n) because we iterate through the array twice, performing constant time operations at each step.
// Space Complexity: O(1) as we only use a few integer variables to track counts, maximums, and the product.

class Solution {
  public:
    int findMaxProduct(vector<int>& arr) {
        int n = arr.size();
        
        // base case for single element
        if (n == 1) return arr[0];
        
        long long MOD = 1e9 + 7;
        int count_neg = 0, count_zero = 0;
        int max_neg = -1e9;
        
        // first pass to gather counts and find max negative
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                count_zero++;
            } else if (arr[i] < 0) {
                count_neg++;
                max_neg = max(max_neg, arr[i]);
            }
        }
        
        // exceptional case: all zeros
        if (count_zero == n) return 0;
        
        // exceptional case: one negative and all other elements are zero
        if (count_neg == 1 && count_zero == n - 1) return 0;
        
        long long prod = 1;
        bool skipped_max_neg = false;
        
        // second pass to calculate maximum product
        for (int i = 0; i < n; i++) {
            // ignore zeros
            if (arr[i] == 0) continue;
            
            // ignore the max negative once if total negatives are odd
            if (count_neg % 2 != 0 && arr[i] == max_neg && !skipped_max_neg) {
                skipped_max_neg = true;
                continue;
            }
            
            // multiply and take modulo
            prod = (prod * arr[i]) % MOD;
        }
        
        // adjust if product became negative due to intermediate C++ modulo behavior
        if (prod < 0) prod = (prod + MOD) % MOD;
        
        return prod;
    }
};

/*
*
* Dry Run
*
* Input: arr = [-1, 0, -2, 4, 3]
* * Initial setup
* n = 5
* MOD = 1000000007
* * First Pass (counting)
* arr[0] is -1: count_neg = 1, max_neg = -1
* arr[1] is 0: count_zero = 1
* arr[2] is -2: count_neg = 2, max_neg = -1
* arr[3] is 4: positive, no change to counts
* arr[4] is 3: positive, no change to counts
* * Edge case check
* count_zero (1) is not equal to n (5)
* count_neg (2) is not 1
* * Second Pass (calculating product)
* count_neg (2) is even, so no negative elements are skipped
* arr[0] is -1: prod = (1 * -1) % MOD = -1
* arr[1] is 0: skipped
* arr[2] is -2: prod = (-1 * -2) % MOD = 2
* arr[3] is 4: prod = (2 * 4) % MOD = 8
* arr[4] is 3: prod = (8 * 3) % MOD = 24
* * Final check
* prod is 24, which is positive
* Return 24
*
*/

```

---

## 🧠 Key Insights

* Always isolate edge cases early (e.g., when the array is entirely zeroes, or a combination of just zeroes and exactly one negative number).
* Dealing with modulo rules properly is crucial since intermediate results can overflow or wrap around unexpectedly. Applying modulo step-by-step limits overflow.
* If negative values amount to an odd number, eliminating the *smallest* negative absolute value (which mathematically acts as the *maximum* negative number) preserves the largest possible magnitude for the overall positive product.

---

## 🔗 Further Exploration

* [Maximum Subarray Sum (Kadane's Algorithm)](https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)
* [Maximum Product Subarray](https://www.geeksforgeeks.org/maximum-product-subarray/)

---

## 📚 References

* **GeeksforGeeks:** [Max Product Subset](https://www.geeksforgeeks.org/problems/maximum-product-subset-of-an-array/1)

---

## 👨‍💻 Author

**Nilesh**

* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Arrays` `#DataStructures` `#GreedyAlgorithm` `#GeeksforGeeks` `#ProblemSolving` `#CPP`