# 📈 Count increasing Subarrays

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://practice.geeksforgeeks.org/problems/count-strictly-increasing-subarrays/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](https://practice.geeksforgeeks.org/)
[![Accuracy](https://img.shields.io/badge/Accuracy-53.02%25-blue?style=for-the-badge)](https://practice.geeksforgeeks.org/)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](https://practice.geeksforgeeks.org/)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of integers, count the number of subarrays in `arr[]` which are strictly increasing with size greater or equal to `2`. 

A subarray is a contiguous part of the array. A subarray is strictly increasing if each element is greater than its previous element (if it exists).

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [1, 4, 5, 3, 7, 9]
Output: 6
Explanation: The strictly increasing subarrays are: [1, 4], [1, 4, 5], [4, 5], [3, 7], [3, 7, 9], [7, 9]
```

**Example 2:**
```text
Input: arr[] = [1, 3, 3, 2, 3, 5]
Output: 4
Explanation: Increasing Subarrays of size greater or equal to 2 are : {1, 3}, {2, 3}, {2, 3, 5}, {3, 5}. So answer for this test case is 4.
```

**Example 3:**
```text
Input: arr[] = [2, 2, 2, 2]
Output: 0
Explanation: No strictly increasing subarray exists.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough)</b></summary>

Let's trace **Example 1**: `arr[] = [1, 4, 5, 3, 7, 9]`

1. **First increasing sequence:** `[1, 4, 5]`
   - Length (`len`) = `3`
   - Subarrays of length $\ge 2$: `[1,4]`, `[4,5]`, `[1,4,5]`
   - Number of subarrays = `(3 * 2) / 2 = 3`
2. Sequence breaks at `3` because `3 < 5`. Reset length.
3. **Second increasing sequence:** `[3, 7, 9]`
   - Length (`len`) = `3`
   - Subarrays of length $\ge 2$: `[3,7]`, `[7,9]`, `[3,7,9]`
   - Number of subarrays = `(3 * 2) / 2 = 3`
4. **Total Subarrays** = `3 + 3 = 6`.

</details>

---

## ⚠️ Constraints

- $1 \le arr.size() \le 10^5$
- $1 \le arr[i] \le 10^7$

---

## 🚀 Solution Approaches

### Optimal Approach (Combinatorics / Single Pass)
By tracking the length of continuously increasing contiguous elements, we can easily find the valid subarrays. Any strictly increasing subarray of length `L` can form exactly `L * (L - 1) / 2` valid strictly increasing subarrays of length $\ge 2$. 

```cpp
// Intuition: A strictly increasing sequence of length L has (L * (L - 1)) / 2 strictly increasing subarrays of length >= 2. We can find all such maximal increasing sequences and sum their respective valid subarrays.
// Approach: Traverse the array while keeping track of the current increasing sequence length (`len`). When the sequence breaks, compute the number of subarrays it forms using the formula `(len * (len - 1)) / 2`, add it to the total `count`, and reset `len`. Remember to add the count for the last sequence outside the loop.
// Time Complexity: O(n) where n is the size of the array. We make a single pass through the array.
// Space Complexity: O(1) as we only use a few variables (`count`, `len`) which take constant extra space.

class Solution {
  public:
    int countIncreasing(vector<int>& arr) {
        
        int n = arr.size();
        int count = 0;
        int len = 1;
    
        // Iterate through the array starting from the second element
        for (int i = 1; i < n; i++) {
            
            // If current element is greater than previous, increase len
            if (arr[i] > arr[i - 1]) {
                len++;
            } 
            
            else {
                // Sequence broke: add subarrays count and reset len
                count += (len * (len - 1)) / 2;
                len = 1;
            }
        }
    
        // Add remaining subarrays count for the last valid sequence
        count += (len * (len - 1)) / 2;
    
        return count;
    }
};

/*
*
* Dry Run
* arr[] = [1, 4, 5, 3, 7, 9]
* Initial: n = 6, count = 0, len = 1
* i = 1: arr[1](4) > arr[0](1). len becomes 2
* i = 2: arr[2](5) > arr[1](4). len becomes 3
* i = 3: arr[3](3) < arr[2](5). Sequence breaks.
* count += (3 * 2) / 2 = 3. count = 3
* len resets to 1
* i = 4: arr[4](7) > arr[3](3). len becomes 2
* i = 5: arr[5](9) > arr[4](7). len becomes 3
* Loop ends.
* Add remaining: count += (3 * 2) / 2 = 3. count = 3 + 3 = 6
* Return count: 6
*
*/
```

---

## 🔍 Key Insights

- **Mathematical Optimization:** Instead of using nested loops to find every possible subarray which would cost $O(n^2)$ time, we use the combination formula $^nC_2$ which is $N \times (N-1) / 2$. This formula accurately calculates the number of pairings possible in a contiguous sequence of length `N`.
- **Edge Case Handling:** We must ensure we add the `count` calculation *after* the loop terminates, to account for an increasing sequence that goes all the way to the end of the array.

---

## 📚 Further Exploration

If you liked this problem, you might also enjoy:
- **Longest Increasing Subsequence** (Finding the maximum length of an increasing sequence, contiguous or not).
- **Maximum Subarray Sum (Kadane’s Algorithm)**
- **Count Subarrays with Given Sum**

---

## 🔗 References

- **GeeksforGeeks Problem:** [Count increasing Subarrays](https://practice.geeksforgeeks.org/problems/count-strictly-increasing-subarrays/1)
- **Concept Reference:** [Combinations and Permutations](https://en.wikipedia.org/wiki/Combination)

---

## 👨‍💻 Author

Created and maintained by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

`#arrays` `#data-structures` `#sliding-window` `#two-pointers` `#combinatorics` `#geeksforgeeks`