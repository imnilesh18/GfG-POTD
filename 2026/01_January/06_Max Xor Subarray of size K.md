# 🟧 Max Xor Subarray of size K

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/max-xor-subarray-of-size-k/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/max-xor-subarray-of-size-k/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-62.79%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/max-xor-subarray-of-size-k/1)
[![Points](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/max-xor-subarray-of-size-k/1)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://github.com/imnilesh18/gfg-potd/blob/master/LICENSE)

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> **Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.**

---

## 🧐 Problem Statement

Given an array of integers `arr[]` and a number `k`. Return the **maximum xor** of a subarray of size `k`.

> **Note:** A subarray is a contiguous part of any given array.

---

## 📊 Examples

**Example 1:**

```bash
Input: arr[] = [2, 5, 8, 1, 1, 3], k = 3
Output: 15
Explanation: arr[0] ^ arr[1] ^ arr[2] = 2 ^ 5 ^ 8 = 15, which is maximum.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let `arr = [2, 5, 8, 1, 1, 3]` and `k = 3`.
We need to check all contiguous subarrays of length 3:

1. **Subarray [2, 5, 8]**: `2 ^ 5 ^ 8 = 15`
2. **Subarray [5, 8, 1]**: `5 ^ 8 ^ 1 = 12`
3. **Subarray [8, 1, 1]**: `8 ^ 1 ^ 1 = 8`
4. **Subarray [1, 1, 3]**: `1 ^ 1 ^ 3 = 3`

The maximum XOR sum found is **15**.

</details>

**Example 2:**

```bash
Input: arr[] = [1, 2, 4, 5, 6], k = 2
Output: 6
Explanation: arr[1] ^ arr[2] = 2 ^ 4 = 6, which is maximum.

```

---

## 🛑 Constraints

* `1 ≤ arr.size() ≤ 10^6`
* `0 ≤ arr[i] ≤ 10^6`
* `1 ≤ k ≤ arr.size()`

---

## 💡 Solution Approach

### 1️⃣ Sliding Window (Optimal)

#### Intuition

The problem asks for a computation on a fixed-size contiguous subarray. This is a classic candidate for the **Sliding Window** technique. The XOR operation has a unique property: `A ^ A = 0`. This allows us to "remove" an element from a running XOR sum simply by XORing it again.

#### Approach

1. Initialize a `currentXor` to 0.
2. Traverse the array using a pointer `j` (end of window).
3. Add the new element `arr[j]` to `currentXor`.
4. If the window size (`j - i + 1`) is less than `k`, keep expanding (`j++`).
5. If the window size hits `k`:
* Update the `maxXor` with the current window's XOR sum.
* **Slide the window**: Remove the element at the start (`arr[i]`) from `currentXor` by XORing it.
* Increment both `i` (start) and `j` (end) to move to the next window.



#### Implementation

```cpp
// Intuition: Use Sliding Window. XOR property (A^A=0) allows removing the first element by XORing it again.
// Approach: Maintain a window of size k. Add new element, remove old element, update max.
// Time Complexity: O(N) - where N is the size of the array, as we traverse it once.
// Space Complexity: O(1) - only constant extra space used for variables.

class Solution {
  public:
    int maxSubarrayXOR(vector<int>& arr, int k) {
        int i = 0; // Start of window
        int j = 0; // End of window
        int currentXor = 0;
        int maxXor = 0;
        int n = arr.size();

        while (j < n) {
            // 1. Expand the window: Add the current element to the XOR sum
            currentXor = currentXor ^ arr[j];

            // 2. Check if window size is less than k
            if (j - i + 1 < k) {
                j++; 
            }
            // 3. If window size is exactly k (Standard Sliding Window Maintenance)
            else if (j - i + 1 == k) {
                // Result update
                maxXor = max(maxXor, currentXor);

                // Shrink/Slide the window:
                // Remove the contribution of arr[i] by XORing it again
                currentXor = currentXor ^ arr[i];
                
                // Move the start pointer forward
                i++;
                // Move the end pointer forward
                j++;
            }
        }
        
        return maxXor;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 5, 8, 1], k = 3
* n = 4, i = 0, j = 0, currentXor = 0, maxXor = 0
*
* Iteration 1:
* j = 0, arr[0] = 2
* currentXor = 0 ^ 2 = 2
* Window size (0-0+1) = 1 < 3 -> j becomes 1
*
* Iteration 2:
* j = 1, arr[1] = 5
* currentXor = 2 ^ 5 = 7
* Window size (1-0+1) = 2 < 3 -> j becomes 2
*
* Iteration 3:
* j = 2, arr[2] = 8
* currentXor = 7 ^ 8 = 15
* Window size (2-0+1) = 3 == 3
* maxXor = max(0, 15) = 15
* Remove arr[i] (arr[0]=2): currentXor = 15 ^ 2 = 13 (which is 5^8)
* i becomes 1
* j becomes 3
*
* Iteration 4:
* j = 3, arr[3] = 1
* currentXor = 13 ^ 1 = 12
* Window size (3-1+1) = 3 == 3
* maxXor = max(15, 12) = 15
* Remove arr[i] (arr[1]=5): currentXor = 12 ^ 5 = 9
* i becomes 2
* j becomes 4
*
* Loop ends (j=4 !< 4). Return 15.
*/

```

---

## 🗝️ Key Insights

* **Bitwise Property**: The property `X ^ A ^ A = X` is crucial. It allows us to "undo" the inclusion of an element in O(1) time, avoiding the need to recompute the XOR for the entire window from scratch.
* **Fixed Size Sliding Window**: Since the window size `k` is constant, we just need to ensure we process exactly `k` elements before sliding.
* **Efficiency**: This reduces the complexity from a brute-force O(N*K) to a linear O(N).

---

## 🚀 Further Exploration

* **Variable Size Window**: Try problems like "Longest Subarray with Sum K".
* **Maximum XOR of any Subarray**: A harder variation typically solved using a Trie data structure.
* **Prefix XOR**: Explore how prefix arrays work for range XOR queries.

---

## 🔗 References

* [GFG Problem Link](https://www.geeksforgeeks.org/problems/max-xor-subarray-of-size-k/1)
* [GeeksforGeeks Sliding Window Technique](https://www.geeksforgeeks.org/window-sliding-technique/)

---

## 📝 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## ⚖️ License

This project is licensed under the MIT License.

> **Note**: This repository is for educational purposes only. Please respect the Code of Conduct and the Terms of Service of the respective platforms.
