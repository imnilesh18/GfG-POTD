# Maximize Number of 1's

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-39.46%25-orange?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

<div>

⚠️ **Educational Use Only**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1).

</div>

---

## 📝 Problem Statement

Given a binary array `arr[]` containing only 0s and 1s and an integer `k`, you are allowed to flip at most `k` 0s to 1s. Find the **maximum** number of consecutive **1's** that can be obtained in the array after performing the operation at most `k` times.

---

## examples-emoji Examples

### Example 1:

```
Input: arr[] = [1, 0, 1], k = 1
Output: 3
Explanation: By flipping the zero at index 1, we get the longest subarray from index 0 to 2 containing all 1’s.
```

<details>
<summary>📖 Example Breakdown</summary>

- **Initial Array**: `[1, 0, 1]`
- **k (flips allowed)**: `1`
- We can flip the `0` at index `1` to a `1`.
- The array becomes `[1, 1, 1]`.
- The longest sequence of consecutive `1`s is now `3`.

</details>

### Example 2:

```
Input: arr[] = [1, 0, 0, 1, 0, 1, 0, 1], k = 2
Output: 5
Explanation: By flipping the zeroes at indices 4 and 6, we get the longest subarray from index 3 to 7 containing all 1’s.
```

### Example 3:

```
Input: arr[] = [1, 1], k = 2
Output: 2
Explanation: Since the array is already having the max consecutive 1's, hence we dont need to perform any operation. Hence the answer is 2.
```

---

## ⛓️ Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `0 ≤ k ≤ arr.size()`
- `0 ≤ arr[i] ≤ 1`

---

## 💡 Solution Approaches

### Optimized Approach (Sliding Window)

This approach uses a sliding window to find the longest subarray with at most `k` zeros.

#### C++ Solution

```cpp
// Intuition: We can find the longest subarray that contains at most k zeros. The length of this subarray is our answer.
// Approach: Use a sliding window (two pointers, i and j). Expand the window by moving j. If the number of zeros (cnt) exceeds k, shrink the window from the left by moving i.
// Time Complexity: O(N), as each element is visited at most twice (by i and j).
// Space Complexity: O(1), as we only use a few variables to store state.
class Solution {
  public:
    int maxOnes(vector<int>& arr, int k) {
        int n = arr.size(); // Get the size of the array
        int result = 0;

        // Start and end pointer of the window
        int i = 0, j = 0;

        // Counter to keep track of zeros in current window
        int cnt = 0;

        while (j < n) {
            if (arr[j] == 0)
                cnt++; // Increment zero count if current element is 0

            // Shrink the window from left if number of
            // zeroes are greater than k
            while (cnt > k) {
                if (arr[i] == 0)
                    cnt--; // Decrement zero count if the element at i is 0

                i++; // Move the left pointer to shrink the window
            }

            result = max(result, (j - i + 1)); // Update the maximum length found so far

            // Increment end pointer to expand the window
            j++;
        }

        return result;

    }
};

/*
*
* Dry Run
* Input: arr[] = [1, 0, 0, 1, 0, 1, 0, 1], k = 2
*
* j=0, arr[0]=1. cnt=0. result=1.
* j=1, arr[1]=0. cnt=1. result=2.
* j=2, arr[2]=0. cnt=2. result=3.
* j=3, arr[3]=1. cnt=2. result=4.
* j=4, arr[4]=0. cnt=3. cnt>k. arr[i=0]=1, i=1. arr[i=1]=0, cnt=2. i=2. Now window is from 2 to 4. result=max(4, 3)=4.
* j=5, arr[5]=1. cnt=2. result=max(4, 4)=4.
* j=6, arr[6]=0. cnt=3. cnt>k. arr[i=2]=0, cnt=2, i=3. Now window is from 3 to 6. result=max(4, 4)=4.
* j=7, arr[7]=1. cnt=2. result=max(4, 5)=5.
*
* Final Answer: 5
*/
```

#### Java Solution

```java
// Intuition: We can find the longest subarray that contains at most k zeros. The length of this subarray is our answer.
// Approach: Use a sliding window (two pointers, i and j). Expand the window by moving j. If the number of zeros (cnt) exceeds k, shrink the window from the left by moving i.
// Time Complexity: O(N), as each element is visited at most twice (by i and j).
// Space Complexity: O(1), as we only use a few variables to store state.
class Solution {
    public int maxOnes(int arr[], int k) {
        int n = arr.length; // Get the size of the array
        int result = 0;

        // Start and end pointer of the window
        int i = 0, j = 0;

        // Counter to keep track of zeros in current window
        int cnt = 0;

        while (j < n) {
            if (arr[j] == 0)
                cnt++; // Increment zero count if current element is 0

            // Shrink the window from left if number of
            // zeroes are greater than k
            while (cnt > k) {
                if (arr[i] == 0)
                    cnt--; // Decrement zero count if the element at i is 0

                i++; // Move the left pointer to shrink the window
            }

            result = Math.max(result, (j - i + 1)); // Update the maximum length found so far

            // Increment end pointer to expand the window
            j++;
        }

        return result;
    }
}

/*
*
* Dry Run
* Input: arr[] = [1, 0, 0, 1, 0, 1, 0, 1], k = 2
*
* j=0, arr[0]=1. cnt=0. result=1.
* j=1, arr[1]=0. cnt=1. result=2.
* j=2, arr[2]=0. cnt=2. result=3.
* j=3, arr[3]=1. cnt=2. result=4.
* j=4, arr[4]=0. cnt=3. cnt>k. arr[i=0]=1, i=1. arr[i=1]=0, cnt=2. i=2. Now window is from 2 to 4. result=max(4, 3)=4.
* j=5, arr[5]=1. cnt=2. result=max(4, 4)=4.
* j=6, arr[6]=0. cnt=3. cnt>k. arr[i=2]=0, cnt=2, i=3. Now window is from 3 to 6. result=max(4, 4)=4.
* j=7, arr[7]=1. cnt=2. result=max(4, 5)=5.
*
* Final Answer: 5
*/
```

---

## 🔑 Key Insights

The **sliding window** technique is perfect for this problem. We maintain a "window" (a subarray) and ensure it's always "valid" (contains at most `k` zeros). By expanding from the right and shrinking from the left when the window becomes invalid, we efficiently check all possible subarrays without nested loops, achieving a linear time complexity.

---

## 🚀 Further Exploration

- [Longest Sub-Array with Sum K](https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k0809/1)
- [Longest K unique characters substring](https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1)
- [Fruit Into Baskets](http://leetcode.com/problems/fruit-into-baskets/description/)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks | Maximize Number of 1's](https://www.geeksforgeeks.org/problems/maximize-number-of-1s0905/1)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Sliding Window` `Two Pointers` `Arrays` `GeeksforGeeks` `POTD`

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
**Reminder:** This is for educational purposes only.
