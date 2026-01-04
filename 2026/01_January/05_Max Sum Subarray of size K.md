# 🟧 Max Sum Subarray of size K

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-2980b9?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-49.6%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1)
[![Points](https://img.shields.io/badge/Points-2-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 🧐 Problem Statement

Given an array of integers `arr[]` and a number `k`. Return the **maximum sum** of a subarray of size `k`.

**Note:** A subarray is a contiguous part of any given array.

---

## 📊 Constraints

- $1 \le arr.size() \le 10^6$
- $1 \le arr[i] \le 10^6$
- $1 \le k \le arr.size()$

---

## 📂 Examples

### Example 1
```bash
Input: arr[] = [100, 200, 300, 400], k = 2
Output: 700
Explanation: arr[2] + arr[3] = 300 + 400 = 700, which is maximum.

```

### Example 2

```bash
Input: arr[] = [1, 4, 2, 10, 23, 3, 1, 0, 20], k = 4
Output: 39
Explanation: arr[1] + arr[2] + arr[3] + arr[4] = 4 + 2 + 10 + 23 = 39, which is maximum.

```

### Example 3

```bash
Input: arr[] = [100, 200, 300, 400], k = 1
Output: 400
Explanation: arr[3] = 400, which is maximum.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's take `arr[] = [1, 4, 2, 10, 23, 3]`, `k = 3`.

1. **First Window (Indices 0-2):** `[1, 4, 2]` -> Sum = 7. `Max = 7`.
2. **Slide Window (Indices 1-3):** Remove 1, Add 10. `[4, 2, 10]` -> Sum = 16. `Max = 16`.
3. **Slide Window (Indices 2-4):** Remove 4, Add 23. `[2, 10, 23]` -> Sum = 35. `Max = 35`.
4. **Slide Window (Indices 3-5):** Remove 2, Add 3. `[10, 23, 3]` -> Sum = 36. `Max = 36`.

**Result:** 36.

</details>

---

## 💡 Solution Approach

### **Sliding Window Technique**

The problem asks for the maximum sum of a contiguous subarray of a fixed size `k`. This is a classic application of the **Sliding Window** technique. Instead of recalculating the sum for every subarray from scratch (which would be ), we maintain a running sum of the current window. As we move the window one step to the right, we subtract the element leaving the window (from the left) and add the element entering the window (from the right). This reduces the complexity to .

#### Code Implementation

```cpp
// Intuition: Use a sliding window of size k. Maintain the sum of the current window by adding the new element and removing the old element as we slide.
// Approach: Iterate through the array with a pointer j. Add elements to sum. Once the window size hits k, record the max sum, subtract the element at start i, and slide both pointers.
// Time Complexity: O(N) where N is the size of the array, as we traverse it once.
// Space Complexity: O(1) as we use only constant extra space for variables.

class Solution {
  public:
    long long maxSubarraySum(vector<int>& arr, int k) {
        int n = arr.size();
        int i = 0;
        int j = 0;
        
        long long currentSum = 0;
        long long maxSum = 0; // Initialize with 0 or minimal value
        
        while(j < n) {
            // 1. Calculation: Add the current element to the sum
            currentSum = currentSum + arr[j];
            
            // 2. If window size is less than k, just expand the window
            if(j - i + 1 < k) {
                j++;
            }
            
            // 3. If window size is equal to k, calculate answer and slide
            else if(j - i + 1 == k) {
                // Calculate answer
                maxSum = max(maxSum, currentSum);
                
                // Remove calculation for i (slide the window)
                currentSum = currentSum - arr[i];
                
                // Move both pointers
                i++;
                j++;
            }
        }
        
        return maxSum;
    }
};

/*
*
* Dry Run
* Input: arr = [100, 200, 300, 400], k = 2
* n = 4, i = 0, j = 0, currentSum = 0, maxSum = 0
*
* Iteration 1:
* j = 0, arr[j] = 100
* currentSum = 0 + 100 = 100
* Window size (0-0+1) = 1 < 2
* j becomes 1
*
* Iteration 2:
* j = 1, arr[j] = 200
* currentSum = 100 + 200 = 300
* Window size (1-0+1) = 2 == 2
* maxSum = max(0, 300) = 300
* currentSum = 300 - arr[0] (100) = 200
* i becomes 1, j becomes 2
*
* Iteration 3:
* j = 2, arr[j] = 300
* currentSum = 200 + 300 = 500
* Window size (2-1+1) = 2 == 2
* maxSum = max(300, 500) = 500
* currentSum = 500 - arr[1] (200) = 300
* i becomes 2, j becomes 3
*
* Iteration 4:
* j = 3, arr[j] = 400
* currentSum = 300 + 400 = 700
* Window size (3-2+1) = 2 == 2
* maxSum = max(500, 700) = 700
* currentSum = 700 - arr[2] (300) = 400
* i becomes 3, j becomes 4
*
* j (4) is not < n (4). Loop ends.
* Return maxSum: 700
*
*/

```

---

## 🗝️ Key Insights

1. **Optimization:** The brute force method calculates the sum of every subarray of size `k` independently, resulting in redundant calculations. The sliding window reuses the sum of the previous window.
2. **Window Management:** The condition `j - i + 1` precisely calculates the current window size. We only slide (increment `i`) when this size hits `k`.
3. **Data Types:** Since elements can be up to  and we sum `k` of them, the total sum can exceed the range of a standard `int`. Using `long long` for `currentSum` and `maxSum` prevents integer overflow.

---

## 🚀 Further Exploration

* **Variable Size Window:** Try problems where the window size isn't fixed but determined by a sum constraint (e.g., "Smallest subarray with sum greater than x").
* **Negative Numbers:** How would the logic change if the array contained negative numbers? (The sliding window still works for fixed `k`).
* **Max Sum Subarray (Any Size):** Check out **Kadane's Algorithm** for finding the maximum sum subarray where the size isn't fixed.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1)
* [Sliding Window Technique Explained](https://www.geeksforgeeks.org/window-sliding-technique/)

---

## 👤 Author

**Nilesh** [GitHub Profile](https://github.com/imnilesh18)

---

## 📜 License

> **Note:** This repository is for educational purposes. Please do not submit this code directly to competitive programming platforms without understanding the logic.