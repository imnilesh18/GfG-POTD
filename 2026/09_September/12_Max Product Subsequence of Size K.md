# 🚀 Max Product Subsequence of Size K

<p align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-49.3%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="License" />
</p>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of integers and an integer `k`, find a subsequence of size `k` whose product is maximum among all possible subsequences of size `k`. Return the maximum product that can be obtained.

---

## 🎯 Examples

**Example 1:**
```text
Input: arr[] = [1, 2, 0, 3], k = 2
Output: 6
Explanation: Subsequence containing elements {2, 3} gives maximum product: 2*3 = 6
```

**Example 2:**
```text
Input: arr[] = [1, 2, -1, -3, -6, 4], k = 4
Output: 144
```

<details>
<summary><b>📖 Example Breakdown (Example 2)</b></summary>

1. **Given array:** `[1, 2, -1, -3, -6, 4]`, `k = 4`
2. **Sorted array:** `[-6, -3, -1, 1, 2, 4]`
3. **Choosing elements:** We can choose pairs from the ends to maximize the product.
   - The product of the two smallest (most negative) elements: `-6 * -3 = 18`
   - The product of the two largest elements: `4 * 2 = 8`
4. Since `18 > 8`, we take `-6` and `-3`. (2 elements taken, `k=2` remaining)
5. Next, we compare the remaining ends. The right side gives `4 * 2 = 8`, which is positive and maximizes our current product. (2 elements taken, `k=0` remaining).
6. **Total product:** `18 * 8 = 144`.
</details>

---

## 🔐 Constraints

> - `1 ≤ arr.size() ≤ 30`
> - `-10 ≤ arr[i] ≤ 10`
> - `1 ≤ k ≤ arr.size()`

---

## 💡 Solution Approach

### 🔹 Two-Pointer & Greedy Approach (Optimized)

The problem asks for the maximum product of a subsequence of size $K$. Because the product of two negative numbers is positive, the maximum product can be formed by multiplying large positive numbers or pairs of large negative numbers. 
By sorting the array, we can use a two-pointer approach to greedily pick the best pair of elements (either the two largest negatives from the left or the two largest positives from the right) when $K$ is even. If $K$ is odd, we handle the first element based on the array's signs to leave an even $K$ for pair-wise processing.

```cpp
// Intuition: To maximize the product of K elements, we need to consider both large positive numbers and large negative numbers (since two negatives multiply to a positive). Sorting allows us to easily access the largest positives at the right and the largest absolute negatives at the left.
// Approach:
// 1. Sort the given array in ascending order.
// 2. If K is odd, process one element to make K even: if all elements are negative, pick the K largest elements (closest to 0) to maximize the negative product. Otherwise, pick the largest positive element.
// 3. With an even K, use two pointers to greedily pick elements in pairs. Compare the product of the two smallest elements (largest absolute negatives) with the two largest positives.
// 4. Multiply the larger pair product to the total and adjust pointers until K becomes 0.
// Time Complexity: O(N log N) dominated by the sorting step. The two-pointer traversal takes O(K) time.
// Space Complexity: O(1) auxiliary space, ignoring the recursion stack used by the sorting algorithm.

class Solution {
public:
    int maxProduct(vector<int> &arr, int k) {
        // Sort array to easily access smallest (negatives) and largest (positives)
        sort(arr.begin(), arr.end());

        int n = arr.size();
        long long prod = 1; 
        int i = 0, j = n - 1;

        // If K is odd, we need to handle the first element carefully
        if (k % 2 != 0) {
            // If all elements are negative, pick smallest absolute values to maximize
            if (arr[j] < 0) {
                for (int x = 0; x < k; x++) {
                    prod *= arr[j - x];
                }
                return prod;
            } 
            // Otherwise, take the largest positive number, leaving an even K
            else {
                prod *= arr[j];
                j--;
                k--;
            }
        }

        // Process the remaining elements in pairs (since K is now even)
        while (k > 0) {
            // Product of the two largest absolute negative numbers
            long long left_prod = (long long)arr[i] * arr[i + 1];
            // Product of the two largest positive numbers
            long long right_prod = (long long)arr[j] * arr[j - 1];

            // Greedily pick the pair that gives the bigger product
            if (left_prod > right_prod) {
                prod *= left_prod;
                i += 2; // Move left pointer
            } else {
                prod *= right_prod;
                j -= 2; // Move right pointer
            }
            k -= 2; // We picked 2 elements
        }

        return prod;
    }
};

/*
* Dry Run
* Input: arr = [1, 2, -1, -3, -6, 4], k = 4
* Sorted arr: [-6, -3, -1, 1, 2, 4]
* k = 4 (even), prod = 1, i = 0, j = 5
* 
* Iteration 1:
* left_prod = (-6) * (-3) = 18
* right_prod = 4 * 2 = 8
* left_prod > right_prod -> prod = 1 * 18 = 18, i = 2, k = 2
*
* Iteration 2:
* left_prod = (-1) * 1 = -1
* right_prod = 4 * 2 = 8
* right_prod > left_prod -> prod = 18 * 8 = 144, j = 3, k = 0
* 
* Output: 144
*/
```

---

## 🚀 Key Insights

1. **Sorting is the anchor:** Sorting immediately partitions our candidate numbers, placing the most potent negative multipliers at index `0, 1...` and the largest positive multipliers at index `n-1, n-2...`.
2. **Parity of K:** A negative number needs a "partner" to become a positive product. Processing elements in pairs guarantees we safely harness negative pairs. Handling odd $K$ upfront smoothly reduces the core logic to just evaluating pairs.
3. **Edge Case Awareness:** The logic cleanly catches the edge case where every number is negative, and $K$ is odd, forcing a negative result. By picking the elements closest to 0 (right side of the sorted array), we ensure the final negative product is as large (close to zero) as possible.

---

## 🧭 Further Exploration

- **Max Subarray Product:** A variation where elements must be contiguous (Kadane's Algorithm variation).
- **Maximum Product of Three Numbers:** A specialized version of this logic where $K=3$.
- **GeeksforGeeks Arrays:** Practice more two-pointer problems on GFG to solidify the concept of evaluating opposing array ends.

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks: Max Product Subsequence of Size K](https://www.geeksforgeeks.org/problems/maximum-product4633/1)

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
- `Array`
- `Sorting`
- `Two Pointers`
- `Greedy`
- `GeeksforGeeks`