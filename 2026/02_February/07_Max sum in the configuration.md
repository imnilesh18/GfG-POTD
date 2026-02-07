# 🔄 Max sum in the configuration

<div align="center">

[![Status](https://img.shields.io/badge/Status-Active-success.svg)]()
[![Platform](https://img.shields.io/badge/Platform-GeeksforGeeks-green.svg)](https://www.geeksforgeeks.org/problems/max-sum-in-the-configuration/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange.svg)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-36.56%25-blue.svg)]()
[![Points](https://img.shields.io/badge/Points-4-yellow.svg)]()
[![License](https://img.shields.io/badge/License-MIT-purple.svg)]()

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> **Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/max-sum-in-the-configuration/1).**

---

## 📝 Problem Statement

Given an integer array `arr[]`. Find the **maximum** value of the sum of `i*arr[i]` for all `0 ≤ i ≤ arr.size()-1`.  
The only operation allowed is to **rotate** (clockwise or counterclockwise) the array any number of times.

**Constraints:**
- `1 ≤ arr.size() ≤ 10^4`
- `1 ≤ arr[i] ≤ 20`

---

## 🔍 Examples

### Example 1
```text
Input: arr[] = [3, 1, 2, 8]
Output: 29
Explanation: Out of all the possible configurations by rotating the elements: 
arr[] = [3, 1, 2, 8] here (3*0) + (1*1) + (2*2) + (8*3) = 29 is maximum.

```

<details>
<summary>📖 <strong>Example Breakdown</strong></summary>

Let's calculate the value for each rotation of `[3, 1, 2, 8]`:

1. **Original**: `[3, 1, 2, 8]`
* Sum: `(0*3) + (1*1) + (2*2) + (3*8) = 0 + 1 + 4 + 24 = 29`


2. **Rotate 1**: `[8, 3, 1, 2]`
* Sum: `(0*8) + (1*3) + (2*1) + (3*2) = 0 + 3 + 2 + 6 = 11`


3. **Rotate 2**: `[2, 8, 3, 1]`
* Sum: `(0*2) + (1*8) + (2*3) + (3*1) = 0 + 8 + 6 + 3 = 17`


4. **Rotate 3**: `[1, 2, 8, 3]`
* Sum: `(0*1) + (1*2) + (2*8) + (3*3) = 0 + 2 + 16 + 9 = 27`



**Maximum Value is 29.**

</details>

### Example 2

```text
Input: arr[] = [1, 2, 3]
Output: 8
Explanation: Out of all the possible configurations by rotating the elements: 
arr[] = [1, 2, 3] here (1*0) + (2*1) + (3*2) = 8 is maximum.

```

### Example 3

```text
Input: arr[] = [4, 13]
Output: 13

```

---

## 💡 Solution Approach

### **Optimized Approach (Mathematical Derivation)**

Instead of calculating the sum for every rotation from scratch (which would be ), we can derive the sum of the *next* rotation from the *current* rotation in  time.

Let `S_total` be the sum of all elements in the array.
Let `Curr_Val` be the configuration sum of the current state.
When we rotate the array to the right (shifting elements), the element at the last index (`n-1`) moves to index `0`, and all other elements shift to index `i+1`.

**Formula:**
`Next_Val = Curr_Val + S_total - (n * arr[n-1])`

By iterating through the array and updating the value using this formula, we can find the maximum configuration sum in linear time.

#### **Algorithm:**

1. Calculate the total sum of the array (`sum`).
2. Calculate the initial configuration value (`curr_val`) for the original array.
3. Iterate `n-1` times to simulate all rotations:
* Identify the pivot element moving from end to start.
* Apply the formula to get the `next_val`.
* Update the `max_val` if `next_val` is larger.
* Update `curr_val` for the next iteration.



```cpp
// Intuition: Instead of recalculating the weighted sum for every rotation O(N^2), we use the relation between the current sum and the next rotated sum to update in O(1).
// Approach: Compute initial weighted sum. Iterate to find sums for all rotations using the formula: next_val = curr_val + sum - (n * pivot_element).
// Time Complexity: O(N) because we iterate through the array twice (once for initial sum, once for rotations).
// Space Complexity: O(1) as we only use a few variables for tracking sums.

class Solution {
  public:
    int maxSum(vector<int> &arr) {
        long long n = arr.size();
        if (n == 0) return 0;

        long long sum = 0;
        long long curr_val = 0;

        // Step 1: Calculate total sum and initial configuration value
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            curr_val += (long long)i * arr[i];
        }

        long long max_val = curr_val;

        // Step 2: Iterate to simulate rotations
        // In each step, we calculate the value of the array rotated to the right
        for (int i = 0; i < n - 1; i++) {
            // The element that moves from the end to the beginning in this rotation
            // 1st rotation: arr[n-1] moves
            // 2nd rotation: arr[n-2] moves
            long long pivot_element = arr[n - 1 - i];

            // Apply the formula
            // New_Val = Old_Val + Total_Sum - (N * Element_Moving_To_Front)
            long long next_val = curr_val + sum - (n * pivot_element);

            // Update max
            if (next_val > max_val) {
                max_val = next_val;
            }

            // Move to next state
            curr_val = next_val;
        }

        return (int)max_val;
    }
};

/*
*
* Dry Run
* Input: arr[] = [3, 1, 2, 8], n = 4
*
* Step 1: Initialization
* sum = 3 + 1 + 2 + 8 = 14
* curr_val = (0*3) + (1*1) + (2*2) + (3*8) = 0 + 1 + 4 + 24 = 29
* max_val = 29
*
* Step 2: Rotations Loop (runs n-1 = 3 times)
*
* Iteration 1 (i=0):
* pivot_element = arr[4-1-0] = arr[3] = 8 (Element '8' moves to front)
* next_val = 29 + 14 - (4 * 8) = 43 - 32 = 11
* max_val = max(29, 11) = 29
* curr_val = 11
* (Config corresponds to: [8, 3, 1, 2])
*
* Iteration 2 (i=1):
* pivot_element = arr[4-1-1] = arr[2] = 2 (Element '2' moves to front)
* next_val = 11 + 14 - (4 * 2) = 25 - 8 = 17
* max_val = max(29, 17) = 29
* curr_val = 17
* (Config corresponds to: [2, 8, 3, 1])
*
* Iteration 3 (i=2):
* pivot_element = arr[4-1-2] = arr[1] = 1 (Element '1' moves to front)
* next_val = 17 + 14 - (4 * 1) = 31 - 4 = 27
* max_val = max(29, 27) = 29
* curr_val = 27
* (Config corresponds to: [1, 2, 8, 3])
*
* Result: 29
*/

```

---

## 🧠 Key Insights

* **Mathematical Pattern**: The difference between the weighted sum of a rotation and the previous one follows a specific pattern based on the total sum of the array.
* **O(1) Update**: Understanding that `Sum(i * arr[i])` changes by adding the total sum of elements and subtracting `N` times the element that wraps around allows for an efficient solution.
* **Overflow Handling**: Intermediate sums can exceed standard integer limits, so using `long long` is crucial.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/max-sum-in-the-configuration/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

</div>

> **Note**: This repository is for educational purposes. Please use the solutions to understand the core concepts.
