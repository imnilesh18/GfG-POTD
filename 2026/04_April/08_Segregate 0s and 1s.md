<div align="center">

# 🟢 Segregate 0s and 1s

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/segregate-0s-and-1s5106/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy: 54.25%](https://img.shields.io/badge/Accuracy-54.25%25-blue?style=for-the-badge)](#)
[![Points: 2](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---
</div>

## 📝 Problem Statement

Given an array `arr[]` consisting of only `0`'s and `1`'s. Modify the array **in-place** to segregate `0`s onto the left side and `1`s onto the right side of the array.

### 🎯 Expected Complexities
- **Time Complexity:** `O(n)`
- **Auxiliary Space:** `O(1)`

---

## 📌 Examples

### Example 1
```text
Input: arr[] = [0, 1, 0, 1, 0, 0, 1, 1, 1, 0]
Output: [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
Explanation: After segregation, all the 0's are on the left and 1's are on the right. Modified array will be [0, 0, 0, 0, 0, 1, 1, 1, 1, 1].
````

### Example 2

```text
Input: arr[] = [1, 1]
Output: [1, 1]
Explanation: There are no 0s in the given array, so the modified array is [1, 1].
```

\<details\>
\<summary\>📖 \<b\>Example Breakdown (Walkthrough)\</b\>\</summary\>

For `arr[] = [0, 1, 0, 1, 0]`:

1.  **Initial Array:** `[0, 1, 0, 1, 0]`
2.  Our goal is to push all `0`s to the left and `1`s to the right.
3.  We can track from both ends:
      - Left pointer `i` looks for `1`.
      - Right pointer `j` looks for `0`.
4.  At index `1`, we find a `1`. At index `4`, we find a `0`. We swap them.
5.  **Array after swap:** `[0, 0, 0, 1, 1]`
6.  The pointers cross each other, meaning the array is successfully segregated.

\</details\>

-----

## 🛑 Constraints

>   - `1 ≤ arr.size() ≤ 10^5`
>   - `0 ≤ arr[i] ≤ 1`

-----

## 💡 Solution Approaches

### Approach 1: Counting Zeros (Two Passes)

This is the brute-force/naive approach. We iterate through the array once to count the total number of `0`s. In the second pass, we overwrite the first `count` elements with `0`s and the remaining elements with `1`s.

```cpp
// Intuition: The simplest way to segregate is to count how many 0s are present in the array. Since the array only contains 0s and 1s, the remaining elements must be 1s.
// Approach: 
// 1. Traverse the array and keep a count of 0s.
// 2. Iterate from 0 to 'count-1' and set elements to 0.
// 3. Iterate from 'count' to the end of the array and set elements to 1.
// Time Complexity: O(N) where N is the size of the array. We traverse the array exactly twice.
// Space Complexity: O(1) as we modify the array in-place without using extra space.

class Solution {
  public:
    // Function to segregate 0s and 1s
    void segregate0and1(vector<int>& arr) {
        // Count 0s
        int count = 0; 
        for (int x : arr)
            if (x == 0)
                count++;
    
        // Fill the vector with 0s until count
        for (int i = 0; i < count; i++)
            arr[i] = 0;
    
        // Fill the remaining vector space with 1s
        for (int i = count; i < arr.size(); i++)
            arr[i] = 1;
    }
};

/*
*
* Dry Run
* Input: [0, 1, 0, 1]
* 1st pass: count = 0. arr[0]=0 -> count=1. arr[1]=1. arr[2]=0 -> count=2. arr[3]=1. Total 0s = 2.
* 2nd pass: Fill index 0, 1 with 0 -> [0, 0, 0, 1]
* 3rd pass: Fill index 2, 3 with 1 -> [0, 0, 1, 1]
* Output: [0, 0, 1, 1]
*
*/
```

-----

### Approach 2: Two Pointers (One Pass - Optimized)

To optimize the operations to a single pass, we can use the two-pointer technique. One pointer traverses from the beginning and another from the end. We swap elements whenever we find a `1` on the left and a `0` on the right.

```cpp
// Intuition: Instead of counting and doing two passes, we can segregate the elements in a single pass using two pointers from opposite ends.
// Approach: 
// 1. Initialize two pointers: 'i' at the start (0) and 'j' at the end (size - 1).
// 2. Move 'i' forward as long as arr[i] is already 0.
// 3. Move 'j' backward as long as arr[j] is already 1.
// 4. If i < j, it means arr[i] is 1 and arr[j] is 0. Swap them to place them correctly, then move both pointers.
// Time Complexity: O(N) where N is the size of the array. We process each element at most once.
// Space Complexity: O(1) as the sorting is done purely in-place.

class Solution {
  public:
    void segregate0and1(vector<int> &arr) {
        int i = 0;
        int j = arr.size() - 1;

        while (i < j) {
            // Move 'i' forward if it is already pointing to 0
            while (i < j && arr[i] == 0) {
                i++;
            }
            
            // Move 'j' backward if it is already pointing to 1
            while (i < j && arr[j] == 1) {
                j--;
            }
            
            // If i is still less than j, we found a 1 at arr[i] and a 0 at arr[j]. 
            // Swap them to put them in their correct halves.
            if (i < j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
    }
};

/*
*
* Dry Run
* Input: [0, 1, 0, 1, 0]
* Initial: i = 0, j = 4
* i moves until arr[i] == 1 -> i stops at index 1.
* j moves until arr[j] == 0 -> j stops at index 4.
* swap(arr[1], arr[4]) -> [0, 0, 0, 1, 1]. i=2, j=3.
* i moves until arr[i] == 1 -> i stops at index 3.
* Since i is not < j (3 < 3 is false), the main loop terminates.
* Output: [0, 0, 0, 1, 1]
*
*/
```

-----

## 🧠 Key Insights

  - **Why Two Pointers?** While counting is straightforward, it requires multiple writes for the entire array structure. The Two Pointer approach minimizes array modifications (writes) exclusively to out-of-place elements and completes the task in a single sweep.
  - This logic is a simplified version of the partitioning step used in the **QuickSort** algorithm or **Dutch National Flag algorithm**.

-----

## 🔍 Further Exploration

Want to challenge yourself further? Check out these related problems:

1.  **Sort an array of 0s, 1s, and 2s** (Dutch National Flag Algorithm)
2.  **Move all zeroes to end of array**
3.  **Partition Array According to Given Pivot**

-----

## 🔗 References

  - **GeeksforGeeks Problem:** [Segregate 0s and 1s](https://www.geeksforgeeks.org/problems/segregate-0s-and-1s5106/1)

-----

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

-----

## 🏷️ Tags

`#Arrays` `#Two-Pointers` `#Sorting` `#DataStructures` `#GeeksforGeeks` `#C++`