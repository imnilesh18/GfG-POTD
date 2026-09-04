<div align="center">
  
# 🐦 Bird and Maximum Fruit Gathering

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/bird-and-maximum-fruit-gathering--170645/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy: 63.66%](https://img.shields.io/badge/Accuracy-63.66%25-blue?style=for-the-badge)](#)
[![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given an array `arr[]` representing the fruit values of trees arranged in a circle and an integer `m`, find the **maximum total fruits** the bird can collect by visiting at most `m` trees.

* The bird can start from any tree and move to a neighboring tree.
* The first and last trees are also considered neighbors (circular arrangement).
* The bird collects the fruit value of every tree it visits.

---

## 💡 Examples

```text
Input: arr[] = [2, 1, 3, 5, 0, 1, 4], m = 3
Output: 9
Explanation: The bird starts from the second tree and visits the 2nd, 3rd, and 4th trees. Total = 1 + 3 + 5 = 9.

```

```text
Input: arr[] = [1, 6, 2, 5, 3, 4], m = 2
Output: 8
Explanation: Starting from the 2nd tree, visiting 2nd and 3rd yields 6 + 2 = 8. Starting from the 4th tree yields 5 + 3 = 8. Maximum is 8.

```

**Input:** `arr[] = [7, 2, 1, 3, 4], m = 2`

Since the array is circular, the neighbors of the 5th tree (value `4`) are the 4th tree (value `3`) and the 1st tree (value `7`).
If the bird starts at the 5th tree and moves to the 1st tree, it collects exactly `m = 2` trees:

* Tree 5: `4`
* Tree 1: `7`
* Total Collected: `4 + 7 = 11`

**Output:** `11`

---

## ⚠️ Constraints

> * `1 ≤ arr.size() ≤ 10^6`
> * `0 ≤ arr[i] ≤ 10^6`
> * `1 ≤ m ≤ arr.size()`
> 
> 

---

## 🛠️ Solution Approach

**Optimal Approach: Sliding Window on a Circular Array**
To solve this efficiently, we can use the **Sliding Window** technique. Since the trees are in a circular arrangement, a sequence of visited trees can wrap around from the end of the array back to the beginning.
Instead of physically duplicating the array to handle the circular nature, we can simulate a concatenated array by iterating up to `n + m - 1` and using the modulo operator `(% n)` to map indices back into the bounds of the original array. We maintain a running sum of our current window of size `m` and track the maximum sum encountered.

### 💻 C++ Code

```cpp
// Intuition: Since the trees are circular, the problem reduces to finding the maximum contiguous subarray sum of exactly size 'm' in a circular array.
// Approach: We use a sliding window of size 'm'. To simulate the circular array without extra space, we iterate up to 'n + m - 1' using the modulo operator '% n'.
// Time Complexity: O(N) where N is the number of elements in the array. The pointers 'i' and 'j' traverse at most N+M elements.
// Space Complexity: O(1) as we only use a few integer variables for tracking sums and indices, requiring no auxiliary space.

class Solution {
  public:
    int maxFruits(vector<int>& arr, int m) {
        int n = arr.size();
    
        // Base case: If bird can visit all trees or more, take everything
        if (m >= n) {
            long long total = 0;
            for (int val : arr) total += val;
            return total;
        }
    
        long long current_sum = 0;
        long long max_sum = 0;
        int i = 0, j = 0;
        
        // Total logical length to account for the circular wrap-around
        int total_len = n + m - 1; 
    
        while (j < total_len) {
            // 1. Expand window by adding the current circular element
             current_sum += arr[j % n];
    
            // 2. Shrink window from the left if its size exceeds m
            if (j - i + 1 > m) {
                 current_sum -= arr[i % n];
                 i++;
            }
    
            // 3. Calculate and update the maximum result when window size is exactly m
            if (j - i + 1 == m) {
                max_sum = std::max(max_sum, current_sum);
            }
    
            // 4. Advance right pointer to continue expanding
            j++;
        }
    
        return max_sum;
    }
};

/*
* Dry Run
* Input: arr = [7, 2, 1, 3, 4], m = 2
* n = 5, m = 2, total_len = 5 + 2 - 1 = 6
*
* j=0: arr[0]=7 -> current_sum = 7. Size=1. j++
* j=1: arr[1]=2 -> current_sum = 9. Size=2 (==m) -> max_sum = max(0, 9) = 9. j++
* j=2: arr[2]=1 -> current_sum = 10. Size=3 (>m) -> shrink i=0, current_sum -= arr[0] (7) = 3. i=1. max_sum = max(9, 3) = 9. j++
* j=3: arr[3]=3 -> current_sum = 6. Size=3 (>m) -> shrink i=1, current_sum -= arr[1] (2) = 4. i=2. max_sum = max(9, 4) = 9. j++
* j=4: arr[4]=4 -> current_sum = 8. Size=3 (>m) -> shrink i=2, current_sum -= arr[2] (1) = 7. i=3. max_sum = max(9, 7) = 9. j++
* j=5: arr[5%5]=arr[0]=7 -> current_sum = 14. Size=3 (>m) -> shrink i=3, current_sum -= arr[3] (3) = 11. i=4. max_sum = max(9, 11) = 11. j++
* Loop ends (j = 6 >= total_len)
*
* Output: 11
*/

```

---

## 🔑 Key Insights

1. **Virtual Unrolling:** We treat the array as if it is twice its size (or specifically `n + m - 1`) to naturally handle the circular wrapping property. This avoids complicated index looping logic.
2. **Modulo Arithmetic:** Instead of creating a new larger array, `arr[j % n]` acts as an elegant pointer that wraps seamlessly back to the start.
3. **Fixed Window Optimization:** Because `m` is constant (or bounded to `n`), a sliding window guarantees an O(N) linear scan, maintaining peak efficiency even for arrays up to $10^6$ in size.

---

## 🔭 Further Exploration

* [Max Sum Subarray of size K](https://www.geeksforgeeks.org/find-maximum-minimum-sum-subarray-size-k/)
* [Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
* [Maximum Circular Subarray Sum](https://www.google.com/search?q=https://leetcode.com/problems/maximum-circular-subarray-sum/)

---

## 🔗 References

* **GeeksforGeeks Problem:** [Bird and Maximum Fruit Gathering](https://www.geeksforgeeks.org/problems/bird-and-maximum-fruit-gathering--170645/1)

---

## 👤 Author

**imnilesh18**

* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Arrays` `#Sliding-Window` `#Two-Pointers` `#Data-Structures` `#GeeksforGeeks`