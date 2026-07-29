# 🧩 Split Array into Minimum Subsets

<div align="center">
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/split-array-into-minimum-subsets/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](#)
[![Accuracy: 84.98%](https://img.shields.io/badge/Accuracy-84.98%25-blue?style=for-the-badge)](#)
[![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

<br>

<div align="center">
⚠️ <b>Educational Use Only</b><br>
This repository and its content are intended solely for educational purposes.<br>
Solutions are provided for learning, practice, and reference only.<br>
Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given an array `arr[]` of distinct positive numbers. Split the array into the minimum number of subsets (or subsequences) such that each subset contains consecutive numbers.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [100, 56, 5, 6, 102, 58, 101, 57, 7, 103, 59]
Output: 3
Explanation: [5, 6, 7], [56, 57, 58, 59], [100, 101, 102, 103] are 3 subsequences in which numbers are consecutive.

```

**Example 2:**

```text
Input: arr[] = [10, 100, 105]
Output: 3
Explanation: [10], [100] and [105] are 3 subsets in which numbers are consecutive.

```

Let's trace **Example 1**: `arr[] = [100, 56, 5, 6, 102, 58, 101, 57, 7, 103, 59]`

1. Identify all consecutive sequences in the array.
2. Sequence 1: `5, 6, 7` (Subset 1)
3. Sequence 2: `56, 57, 58, 59` (Subset 2)
4. Sequence 3: `100, 101, 102, 103` (Subset 3)
5. Total minimum subsets required = `3`. Every number finds exactly one consecutive sequence to join.

---

## 🔒 Constraints

> * `1 ≤ arr.size() ≤ 10^5`
> * `0 ≤ arr[i] ≤ 10^9`
> 
> 

---

## 🚀 Solution Approaches

### 1️⃣ Naive Approach (Sorting)

```cpp
// Intuition: By sorting the array, consecutive numbers will be adjacent. Any break in continuity means a new consecutive subset begins.
// Approach:
// 1. Sort the given array in ascending order.
// 2. Initialize a counter to 1, as there will be at least one subset if the array is not empty.
// 3. Iterate through the array and check the difference between adjacent elements.
// 4. If the difference is greater than 1 (i.e., arr[i] + 1 != arr[i + 1]), increment the subset count.
// Time Complexity: O(n log n) - Sorting the array dominates the time complexity.
// Space Complexity: O(1) - Sorting is done in-place, taking O(1) auxiliary space.

class Solution {
  public:
    int minSubsets(vector<int>& arr) {
  
        // Sort the array so that consecutive elements
        // become consecutive in the array.
        sort(arr.begin(), arr.end());
    
        int count = 1; 
        for (int i = 0; i < arr.size() - 1; i++) {
          
            // Check if there's a break between consecutive numbers
            if (arr[i] + 1 != arr[i + 1])
                count++;
        }
    
        return count;
    }
};

/*
Dry Run
Input: arr[] = [10, 100, 105]
1. Initial array: [10, 100, 105]
2. Sorted array: [10, 100, 105]
3. Initialize count = 1
4. Loop i = 0: arr[0] is 10, arr[1] is 100. 10 + 1 != 100 -> count = 2
5. Loop i = 1: arr[1] is 100, arr[2] is 105. 100 + 1 != 105 -> count = 3
6. Return count = 3
*/

```

### 2️⃣ Expected Approach (Hashing)

```cpp
// Intuition: A number marks the start of a consecutive subset if its preceding number (num - 1) doesn't exist in the array.
// Approach:
// 1. Insert all array elements into a hash set for O(1) lookups.
// 2. Initialize a counter to 0.
// 3. Iterate through each element in the array.
// 4. Check if (element - 1) is present in the hash set.
// 5. If it is not present, the current element is the starting point of a new subset, so increment the count.
// Time Complexity: O(n) - Inserting elements and checking the hash set takes O(n) overall time.
// Space Complexity: O(n) - The hash set requires O(n) extra space to store the elements.

class Solution {
  public:
    int minSubsets(vector<int>& arr) {
      
        // Store all elements in a hash set to allow quick O(1) lookup
        unordered_set<int> s(arr.begin(), arr.end());    
        
        int count = 0;
        for(int x : arr) {
          
            // Check for the start of a new subset 
            if(s.find(x - 1) == s.end()) {
                count++;
            }
        }
        return count;
    }
};

/*
Dry Run
Input: arr[] = [10, 100, 105]
1. Set creation: s = {10, 100, 105}
2. Initialize count = 0
3. Loop x = 10: s.find(9) is s.end() (True) -> count = 1
4. Loop x = 100: s.find(99) is s.end() (True) -> count = 2
5. Loop x = 105: s.find(104) is s.end() (True) -> count = 3
6. Return count = 3
*/

```

---

## 🧠 Key Insights

* **Sorting Method:** Forces sequence discovery to become a simple neighbor-comparison problem. It is space-efficient `O(1)` but hits the computational bottleneck of `O(n log n)`.
* **Hashing Method:** Trades space for time. By utilizing an unordered_set, we can detect the absolute "starts" of sub-sequences in `O(1)` time per element, bringing the total time complexity down to a highly optimized `O(n)`. This is a classic trick for finding consecutive subsets/sequences without mutating the original array order.

---

## 🔎 Further Exploration

* **Related Problem:** *Longest Consecutive Subsequence* – You can use the exact same hash-based intuition to find the length of the longest subsequence.
* **Challenge:** Can you solve this without extra space if the array elements are constrained in a very narrow range (e.g., using a boolean array)?

---

## 🔗 References

* **GeeksforGeeks Problem:** [Split Array into Minimum Subsets](https://www.geeksforgeeks.org/problems/split-array-into-minimum-subsets/1)

---

## 👨‍💻 Author

👤 **Nilesh**

* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Sorting` `Arrays` `Hash` `GeeksforGeeks` `C++`
