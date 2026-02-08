# 🟧 Maximum Product Subarray

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-18.09%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

</div>

<p align="center">
  <b>⚠️ Educational Use Only:</b> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the <a href="https://www.geeksforgeeks.org/problems/maximum-product-subarray3604/1">GeeksforGeeks problem</a>.
</p>

---

## 🧐 Problem Statement

Given an array `arr[]` that contains positive and negative integers (may contain 0 as well). Find the **maximum** product that we can get in a subarray of `arr[]`.

**Note:** It is guaranteed that the answer fits in a 32-bit integer.

### 📊 Constraints

- $1 \le arr.size() \le 10^6$
- $-10 \le arr[i] \le 10$

---

## 📂 Examples

### Example 1
```text
Input: arr[] = [-2, 6, -3, -10, 0, 2]
Output: 180
Explanation: The subarray with maximum product is [6, -3, -10] with product = 6 * (-3) * (-10) = 180.

```

### Example 2

```text
Input: arr[] = [-1, -3, -10, 0, 6]
Output: 30
Explanation: The subarray with maximum product is [-3, -10] with product = (-3) * (-10) = 30.

```

### Example 3

```text
Input: arr[] = [2, 3, 4] 
Output: 24 
Explanation: For an array with all positive elements, the result is product of all elements. 

```

<details>
<summary><b>📖 Example Breakdown: <code>[-2, 6, -3, -10, 0, 2]</code></b></summary>

1. **Start:** `max_prod = -2`
2. **i=1 (Val 6):**
* Current subarray product can be `6` or `-2 * 6`. Max is `6`.
* `max_prod` updates to `6`.


3. **i=2 (Val -3):**
* Multiplying `6` by `-3` gives `-18`. We need to track the minimum too (`-18`), because a future negative number could turn this into a huge positive.


4. **i=3 (Val -10):**
* Current val is negative. We swap our max/min trackers.
* Previous min was `-18`. New potential max is `-18 * -10 = 180`.
* `max_prod` updates to `180`.


5. **i=4 (Val 0):**
* Product becomes 0. Reset trackers.


6. **i=5 (Val 2):**
* Max ending here is 2. Global max remains `180`.



</details>

---

## 💡 Solution Approach

### Optimized Approach: Modified Kadane's Algorithm

The problem is a variation of the Maximum Sum Subarray problem (Kadane's Algorithm). However, because the product of two negative numbers is positive, simply tracking the maximum product isn't enough. We must also track the **minimum product** ending at the current position. When we encounter a negative number, the maximum product becomes the minimum, and the minimum becomes the maximum.

```cpp
// Intuition: Since product of two negative numbers is positive, we must track both max and min product ending at current position. A negative number flips max to min and vice versa.
// Approach: Iterate array. If current num is negative, swap maxEnding and minEnding. Update maxEnding as max(curr, maxEnding*curr) and minEnding as min(curr, minEnding*curr). Update global max.
// Time Complexity: O(N) where N is the size of the array, as we traverse it once.
// Space Complexity: O(1) as we only use a few variables for tracking state.

class Solution {
public:
    // Function to find maximum product subarray
    int maxProduct(vector<int>& arr) {
        // Initialize variables
        int n = arr.size();
        int maxProduct = arr[0];
        int maxEndingHere = arr[0];
        int minEndingHere = arr[0];
        
        // Iterate through the array
        for (int i = 1; i < n; ++i) {
            if (arr[i] < 0) {
                // Swap max and min when current element is negative
                swap(maxEndingHere, minEndingHere);
            }
            
            // Update maxEndingHere and minEndingHere
            maxEndingHere = max(arr[i], maxEndingHere * arr[i]);
            minEndingHere = min(arr[i], minEndingHere * arr[i]);
            
            // Update global maximum product
            maxProduct = max(maxProduct, maxEndingHere);
        }
        
        return maxProduct;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 3, -2, 4]
*
* Initialization: maxP = 2, maxEnd = 2, minEnd = 2
*
* i = 1, val = 3 (Positive):
* maxEnd = max(3, 2 * 3) = 6
* minEnd = min(3, 2 * 3) = 3
* maxP = max(2, 6) = 6
*
* i = 2, val = -2 (Negative):
* swap(maxEnd, minEnd) -> maxEnd = 3, minEnd = 6
* maxEnd = max(-2, 3 * -2) = max(-2, -6) = -2
* minEnd = min(-2, 6 * -2) = min(-2, -12) = -12
* maxP = max(6, -2) = 6
*
* i = 3, val = 4 (Positive):
* maxEnd = max(4, -2 * 4) = max(4, -8) = 4
* minEnd = min(4, -12 * 4) = min(4, -48) = -48
* maxP = max(6, 4) = 6
*
* Return 6
*
*/

```

---

## 🧠 Key Insights

1. **Negative Numbers Flip:** The core complexity comes from negative numbers. A "minimum" product (large negative number) can instantly become the "maximum" product if multiplied by another negative number. This is why `swap(maxEndingHere, minEndingHere)` is crucial when `arr[i] < 0`.
2. **Zeros Reset Chains:** If `arr[i]` is 0, the product becomes 0. The `max()` logic `max(arr[i], maxEndingHere * arr[i])` implicitly handles this by starting a new subarray at the next element if the previous product was reset or effectively useless.
3. **Local vs Global:** We maintain local extrema (`maxEndingHere`, `minEndingHere`) for continuity and update the global extrema (`maxProduct`) at every step.

---

## 🚀 Further Exploration

* **Maximum Sum Subarray:** Solve using standard Kadane's Algorithm.
* **Maximum Product Subarray (k-size):** Find max product of a fixed size window.
* **Subarray with 0 Sum:** Using Hashing.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/maximum-product-subarray3604/1)
* [Kadane's Algorithm Explanation](https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

</div>

**⚠️ Note:** This repository is for educational purposes. Please use these solutions to understand the concepts and improve your coding skills. Avoid direct copying for academic assignments or competitive platforms.
