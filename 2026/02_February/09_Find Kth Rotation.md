# 🔄 Find Kth Rotation

![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?logo=geeksforgeeks&style=for-the-badge)
![Accuracy: 23.16%](https://img.shields.io/badge/Accuracy-23.16%25-blue?style=for-the-badge)
![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

> [!WARNING]
> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📜 Problem Statement

Given an increasing sorted rotated array `arr[]` of distinct integers. The array is right-rotated `k` times. Find the value of `k`.

Let's suppose we have an array `arr[] = [2, 4, 6, 9]`, if we rotate it by 2 times it will look like this:
* **After 1st Rotation:** `[9, 2, 4, 6]`
* **After 2nd Rotation:** `[6, 9, 2, 4]`

Basically, we need to find the index of the minimum element, which corresponds to the number of rotations.

### 🔹 Constraints
* $1 \le arr.size() \le 10^5$
* $1 \le arr[i] \le 10^7$

---

## 🧪 Examples

### Example 1
```python
Input: arr[] = [5, 1, 2, 3, 4]
Output: 1
Explanation: The given array is [5, 1, 2, 3, 4]. The original sorted array is [1, 2, 3, 4, 5]. We can see that the array was rotated 1 time to the right.

```

### Example 2

```python
Input: arr = [1, 2, 3, 4, 5]
Output: 0
Explanation: The given array is not rotated.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's consider `arr = [5, 1, 2, 3, 4]`.

1. **Original:** `[1, 2, 3, 4, 5]`
2. **Right Rotate 1:** `[5, 1, 2, 3, 4]` -> Minimum element `1` is at index `1`.
3. **Result:** The rotation count `k` is simply the index of the minimum element in the array.

</details>

---

## 💡 Solution Approaches

### 1️⃣ Binary Search Approach (Optimized)

#### Intuition

In a sorted array rotated `k` times, the number of rotations `k` is exactly equal to the **index of the minimum element**. A brute force search takes . However, since the array is partially sorted, we can use **Binary Search** to find the minimum element in  time. The minimum element is the only element in the array that is smaller than its previous element (cyclically). We use the property that if `arr[mid] > arr[high]`, the minimum is in the right half; otherwise, it's in the left half (or is `mid`).

#### Code

```cpp
// Intuition: The number of rotations is equal to the index of the minimum element. We can find this efficiently using Binary Search.
// Approach: Use Binary Search to narrow down the unsorted part of the array where the minimum element resides.
// Time Complexity: O(log N) - Standard binary search complexity.
// Space Complexity: O(1) - Constant extra space used.

class Solution {
  public:
    int findKRotation(vector<int> &arr) {
        int low = 0, high = arr.size() - 1;
        
        while (low <= high)
        {
            // If subarray is already sorted, 
            // the smallest element is at 'low' (number of rotations)
            if (arr[low] <= arr[high])        
                return low;
                        
            int mid = (low + high) / 2;
        
            // If mid element is greater than high, the pivot (min element)
            // must be in the right unsorted half
            if (arr[mid] > arr[high])
                low = mid + 1;
            // Otherwise, the minimum is in the left half (could be mid itself)
            // so we pull high to mid
            else
                high = mid;
        }
        
        return low;
    }
};

/*
*
* Dry Run
* Input: arr[] = [5, 1, 2, 3, 4]
* Size n = 5
*
* Iteration 1:
* low = 0, high = 4
* arr[0] (5) <= arr[4] (4) ? False (Array not sorted)
* mid = (0 + 4) / 2 = 2 (Value: 2)
* arr[2] (2) > arr[4] (4) ? False
* high = mid = 2
*
* Iteration 2:
* low = 0, high = 2
* arr[0] (5) <= arr[2] (2) ? False (Not sorted)
* mid = (0 + 2) / 2 = 1 (Value: 1)
* arr[1] (1) > arr[2] (2) ? False
* high = mid = 1
*
* Iteration 3:
* low = 0, high = 1
* arr[0] (5) <= arr[1] (1) ? False (Not sorted)
* mid = (0 + 1) / 2 = 0 (Value: 5)
* arr[0] (5) > arr[1] (1) ? True
* low = mid + 1 = 1
*
* Iteration 4:
* low = 1, high = 1
* arr[1] (1) <= arr[1] (1) ? True
* return low (1)
*
* Output: 1 (Correct)
*/

```

---

## 🔑 Key Insights

* **Rotation = Min Index**: The key observation is that finding the rotation count `k` is equivalent to finding the index of the smallest element in the array.
* **Sorted Property**: If `arr[low] <= arr[high]`, the segment is already fully sorted, so the minimum is at `low`.
* **Discarding Halves**:
* If `arr[mid] > arr[high]`, the "cliff" (drop from max to min) is to the right.
* Otherwise, we might be on the slope to the right of the cliff, so we search left (including `mid`).



---

## 🚀 Further Exploration

* **Find Minimum in Rotated Sorted Array II**: What if the array contains duplicates?
* **Search in Rotated Sorted Array**: Finding a specific target value instead of the rotation count.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/rotation4723/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## ⚖️ License

<div align="center">

**MIT License**

Copyright (c) 2026 imnilesh18

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files...

</div>

> [!TIP]
> **Remember:** Coding is about patterns. Recognizing that "Rotation Count" == "Index of Minimum Element" transforms this problem into a standard Binary Search template.
