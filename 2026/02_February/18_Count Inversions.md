# 🟧 Count Inversions

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D35?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-FFC107?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-16.93%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 🧐 Problem Statement

Given an array of integers `arr[]`. You have to find the **Inversion Count** of the array.

> **Note:** Inversion count is the number of pairs of elements `(i, j)` such that `i < j` and `arr[i] > arr[j]`.

### 🔹 Constraints
- $1 \le arr.size() \le 10^5$
- $1 \le arr[i] \le 10^4$

---

## 📂 Examples

### Example 1
```bash
Input: arr[] = [2, 4, 1, 3, 5]
Output: 3
Explanation: The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).

```

### Example 2

```bash
Input: arr[] = [2, 3, 4, 5, 6]
Output: 0
Explanation: As the sequence is already sorted so there is no inversion count.

```

### Example 3

```bash
Input: arr[] = [10, 10, 10]
Output: 0
Explanation: As all the elements of array are same, so there is no inversion count.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's look at `arr[] = [2, 4, 1, 3, 5]`.
We need pairs `(i, j)` where `i < j` but `arr[i] > arr[j]`.

1. Index 0 (Value 2):
* Is `2 > 4`? No.
* Is `2 > 1`? **Yes**. (Inversion 1)
* Is `2 > 3`? No.
* Is `2 > 5`? No.


2. Index 1 (Value 4):
* Is `4 > 1`? **Yes**. (Inversion 2)
* Is `4 > 3`? **Yes**. (Inversion 3)
* Is `4 > 5`? No.


3. Index 2 (Value 1): No elements to right are smaller.
4. Index 3 (Value 3): No elements to right are smaller.

**Total Inversions:** 3.

</details>

---

## 💡 Solution Approaches

### 🚀 Optimized Approach: Merge Sort (Divide & Conquer)

#### Intuition

A brute force approach would compare every pair, resulting in  time complexity. This is inefficient for .
The Merge Sort algorithm naturally divides the array into sorted halves. During the **merge** step, if an element from the left sorted subarray is greater than an element from the right sorted subarray, it implies that **all subsequent elements** in the left subarray are also greater (since it's sorted). This allows us to count multiple inversions at once.

#### Approach

1. **Divide**: Recursively split the array into two halves until the size is 1.
2. **Conquer**: Recursively count inversions in the left half and right half.
3. **Merge & Count**: Merge the two sorted halves.
* While comparing `arr[i]` (left half) and `arr[j]` (right half):
* If `arr[i] <= arr[j]`: No inversion, push `arr[i]` to temp.
* If `arr[i] > arr[j]`: **Inversion found!** Since the left half is sorted, `arr[i]` and all elements after it in the left half form inversions with `arr[j]`. Add `(mid + 1 - i)` to count. Push `arr[j]` to temp.



```cpp
// Intuition: Using Merge Sort allows us to count inversions efficiently. When merging two sorted subarrays, if arr[i] > arr[j], it means arr[i] and all subsequent elements in the left subarray are greater than arr[j], constituting inversions.
// Approach: Recursively divide the array into halves. Count inversions in the left and right halves. During the merge step, count split inversions: if arr[i] > arr[j], add (mid - i + 1) to the count because the left part is sorted.
// Time Complexity: O(N log N) - Standard Merge Sort complexity.
// Space Complexity: O(N) - Temporary vector used during the merge process.

class Solution {
  public:
    
    int merge(vector<int> &arr, int left, int mid, int right) {
        int count = 0;
        vector<int> temp; // Temporary array for merging
        int i = left, j = mid + 1;
        
        while(i <= mid && j <= right) {
            if(arr[i] <= arr[j]) {
                temp.push_back(arr[i++]); // No inversion, standard merge
            } else {
                // Inversion found: arr[i] > arr[j]
                // Since left part is sorted, all elements from i to mid are > arr[j]
                count += (mid + 1 - i);
                temp.push_back(arr[j++]);
            }
        }
        
        // Copy remaining elements from left subarray
        while(i <= mid) {
            temp.push_back(arr[i++]);
        }
          
        // Copy remaining elements from right subarray
        while(j <= right) {
            temp.push_back(arr[j++]);
        }
        
        // Restore sorted elements back to original array
        for(int k = left; k <= right; k++) {
            arr[k] = temp[k - left];
        }
        
        return count;
    }
    
    int mergeSort(vector<int> &arr, int left, int right) {
        if(left >= right) {
            return 0; // Base case: single element has 0 inversions
        }
        
        int mid = left + (right - left) / 2;
        int count = 0;
        
        count += mergeSort(arr, left, mid);      // Count in left half
        count += mergeSort(arr, mid + 1, right); // Count in right half
        count += merge(arr, left, mid, right);   // Count split inversions
        
        return count;
    }
    
    int inversionCount(vector<int> &arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};

/*
*
* Dry Run
* Input: arr[] = [2, 4, 1, 3, 5]
* * 1. mergeSort(0, 4) -> mid=2 (split [2,4,1] and [3,5])
* 2. mergeSort(0, 2) -> mid=1 (split [2,4] and [1])
* 3. mergeSort(0, 1) -> mid=0 (split [2] and [4]) -> merge([2], [4]) -> sorted: [2,4], count=0
* 4. mergeSort(2, 2) -> returns 0
* 5. merge([2,4], [1]):
* - i=0(val=2), j=2(val=1): 2 > 1 -> inversion. count += (1-0+1) = 2. temp=[1], j++
* - j > right. Copy rest [2,4]. temp=[1,2,4]. arr becomes [1,2,4]. return 2.
* 6. mergeSort(3, 4) -> mid=3 (split [3] and [5]) -> merge([3], [5]) -> sorted: [3,5], count=0
* 7. merge([1,2,4], [3,5]):
* - i=0(1), j=3(3): 1<=3 -> temp=[1], i++
* - i=1(2), j=3(3): 2<=3 -> temp=[1,2], i++
* - i=2(4), j=3(3): 4>3  -> inversion. count += (2-2+1) = 1. temp=[1,2,3], j++
* - i=2(4), j=4(5): 4<=5 -> temp=[1,2,3,4], i++
* - i > mid. Copy rest [5]. temp=[1,2,3,4,5].
* - Total count this step = 1.
* * Total Inversions = 2 (from step 5) + 0 (step 6) + 1 (step 7) = 3.
*/

```

---

## 🗝️ Key Insights

* **Divide and Conquer**: The problem can be broken down into counting inversions in the left half, the right half, and split inversions across the middle.
* **Sorted Property**: The crucial insight is that within the `merge` function, the left and right subarrays are already sorted. If `arr[i] > arr[j]`, then *every* element from `arr[i]` to `arr[mid]` is strictly greater than `arr[j]`.
* **Counting Formula**: The number of such elements is `mid - i + 1`. This allows us to increment the count in constant time for that specific `arr[j]` rather than iterating.

---

## 🚀 Further Exploration

* **Reverse Pairs** (LeetCode 493): A variation where `i < j` and `nums[i] > 2*nums[j]`.
* **Count Smaller Numbers After Self**: Using Fenwick Tree or Merge Sort.
* **Global Swaps**: Determine minimum swaps to sort using inversion logic.

---

## 🔗 References

* [GeeksforGeeks Problem Link]()
* [Merge Sort Algorithm]()

---

## 👨‍💻 Author

**[imnilesh18]()**