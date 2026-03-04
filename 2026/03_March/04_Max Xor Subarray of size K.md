# 🟧 Max Xor Subarray of size K

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/max-xor-subarray-of-size-k/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy: 55.63%](https://img.shields.io/badge/Accuracy-55.63%25-blue?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

Given an array of integers `arr[]` and a number `k`. Return the **maximum xor** of a subarray of size `k`.

*Note:* A subarray is a contiguous part of any given array.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [2, 5, 8, 1, 1, 3], k = 3
Output: 15
Explanation: arr[0] ^ arr[1] ^ arr[2] = 2 ^ 5 ^ 8 = 15, which is the maximum possible XOR for any subarray of size 3.
```

### Example 2
```text
Input: arr[] = [1, 2, 4, 5, 6], k = 2
Output: 6
Explanation: arr[1] ^ arr[2] = 2 ^ 4 = 6, which is the maximum possible XOR.
```

<details>
<summary>📖 <b>Example Breakdown (Example 1)</b></summary>

Given `arr[] = [2, 5, 8, 1, 1, 3]` and `k = 3`:

1. **First window [2, 5, 8]:** XOR = $2 \oplus 5 \oplus 8 = 15$. Current Max = 15.
2. **Second window [5, 8, 1]:** XOR = $5 \oplus 8 \oplus 1 = 12$. Max remains 15.
3. **Third window [8, 1, 1]:** XOR = $8 \oplus 1 \oplus 1 = 8$. Max remains 15.
4. **Fourth window [1, 1, 3]:** XOR = $1 \oplus 1 \oplus 3 = 3$. Max remains 15.

The maximum XOR obtained is **15**.
</details>

---

## ⚠️ Constraints

> - $1 \le arr.size() \le 10^6$
> - $0 \le arr[i] \le 10^6$
> - $1 \le k \le arr.size()$

* **Expected Time Complexity:** $O(N)$
* **Expected Auxiliary Space:** $O(1)$

---

## 🚀 Solution Approaches

### 1. Sliding Window & Bit Manipulation (Optimized)

**Intuition:** Instead of recalculating the XOR sum for every subarray of size $k$ from scratch (which would take $O(N \times K)$ time), we can use the **Sliding Window** technique. The crucial property of the XOR operation is that $A \oplus A = 0$. This means we can remove the contribution of an element that slides out of our window by simply XORing it again with our current window sum.

**Approach:**
1. Initialize two pointers `i` and `j` to represent the sliding window boundaries, starting at 0.
2. Maintain a `currentXor` variable to store the XOR sum of the current window.
3. Traverse the array with pointer `j`. At each step, XOR `arr[j]` with `currentXor`.
4. If the window size `(j - i + 1)` is less than `k`, just move `j` forward to expand the window.
5. Once the window size hits `k`:
   - Update `maxXor` with the maximum of itself and `currentXor`.
   - Shrink the window from the left by XORing `arr[i]` with `currentXor` to remove its effect.
   - Increment both `i` and `j` to slide the window.

### C++ Source Code

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

## 🔑 Key Insights

* **XOR Reversibility:** The absolute game-changer here is that XOR acts as its own inverse. $A \oplus B \oplus A = B$. Thus, subtracting from an active window doesn't require complex bit counting, just an application of the `^` operator against the outgoing element.
* **Fixed Size Window:** Whenever a problem asks for an operation on a contiguous subarray of an exact length $K$, the Fixed-Size Sliding Window technique is the optimal go-to pattern to achieve an $O(N)$ solution.

---

## 🌍 Further Exploration

If you enjoyed this problem, check out these related topics:
1. **Sliding Window Variants:** Try problems with dynamically sized windows (e.g., longest subarray with a given sum).
2. **Advanced Bit Manipulation:** Explore problems using Tries to find maximum XOR pairs dynamically across entire arrays (e.g., Maximum XOR of Two Numbers in an Array).

---

## 🔗 References

* **GeeksforGeeks Problem:** [Max Xor Subarray of size K](https://www.geeksforgeeks.org/problems/max-xor-subarray-of-size-k/1)
* **XOR Bitwise Operator:** [GFG Tutorial on Bit Magic](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Sliding Window](https://img.shields.io/badge/Sliding_Window-FF6F00?style=for-the-badge)
![Bit Manipulation](https://img.shields.io/badge/Bit_Manipulation-673AB7?style=for-the-badge)
![Arrays](https://img.shields.io/badge/Arrays-009688?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
