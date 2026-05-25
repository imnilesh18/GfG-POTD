# 🟢 Elements in the Range

<p align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Basic-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-37.28%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-1-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge" alt="License" />
</p>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/elements-in-the-range2834/1).

---

## 📝 Problem Statement

Given an array `arr[]` containing distinct positive integers, and two integers `start` and `end` defining a range. Determine if the array contains all elements within the inclusive range `[start, end]`.

**Note:** If the array contains all elements in the given range return `true` otherwise return `false`.

---

## 💡 Examples

### Example 1
```text
Input: start = 2, end = 5, arr[] =  [1, 4, 5, 2, 7, 8, 3]
Output: true
Explanation: All integers within the range [2, 5] are 2, 3, 4, and 5, and all of them are present in the array. Therefore, the answer is true for this test case.

```

### Example 2

```text
Input: start = 2, end = 6, arr[] = [1, 4, 5, 2, 7, 8, 3]
Output: false
Explanation: The array does not contain 6; hence, it does not contain all the elements in the range [2, 6]. Therefore, the output is false.

```

1. **Target Range:** We need to find `2, 3, 4, 5, 6`.
2. **Array Elements:** `[1, 4, 5, 2, 7, 8, 3]`.
3. Let's check each number:
* `2`: Present ✔️
* `3`: Present ✔️
* `4`: Present ✔️
* `5`: Present ✔️
* `6`: Missing ❌


4. Since `6` is missing, the condition fails. We immediately return `false`.

---

## 🛑 Constraints

> * `1 ≤ arr.size() ≤ 10^5`
> * `0 ≤ arr[i] ≤ 10^5`
> * `0 ≤ start ≤ end ≤ 10^5`
> 
> 

---

## 💻 Solution Approach

### Optimized Approach (Hash Set)

```cpp
// Intuition: Hash sets provide O(1) average time complexity for lookups. By storing all array elements in a hash set, we can quickly verify if every element in the target range exists.
// Approach: 
// 1. Insert all elements of the given array into an unordered_set.
// 2. Iterate through the target range from 'start' to 'end' (inclusive).
// 3. For each number in the range, check if it exists in the set.
// 4. If any number is missing, return false immediately. If the loop completes, return true.
// Time Complexity: O(N + K), where N is the size of the array and K is the number of elements in the range [start, end]. Inserting into the set takes O(N) average time, and checking the range takes O(K) average time.
// Space Complexity: O(N) to store the distinct elements of the array in the unordered_set.

class Solution {
public:
    bool checkElements(int start, int end, std::vector<int> &arr) {
        // Step 1: Insert all elements of the array into a hash set for O(1) lookups
        unordered_set<int> elements(arr.begin(), arr.end());
        
        // Step 2: Check if every number from 'start' to 'end' exists in the set
        for(int i = start; i <= end; i++) {
            if(elements.find(i) == elements.end()) {
                // If any number in the range is missing, return false immediately
                return false;
            }
        }
        
        // If the loop finishes, it means all numbers in the range were found
        return true;
    }
};

/*
* Dry Run
* Input: start = 2, end = 5, arr = [1, 4, 5, 2, 7, 8, 3]
* * Step 1: Initialize hash set 'elements' with arr.
* elements = {1, 4, 5, 2, 7, 8, 3}
* * Step 2: Loop i from start (2) to end (5).
* i = 2: elements.find(2) != end -> Found
* i = 3: elements.find(3) != end -> Found
* i = 4: elements.find(4) != end -> Found
* i = 5: elements.find(5) != end -> Found
* * Step 3: Loop finishes without missing any element.
* Output: true
*/

```

---

## 🔑 Key Insights

* **O(1) Lookups:** Using an `unordered_set` (hash set) reduces the lookup time for each target element from `O(N)` (using linear search) to `O(1)`.
* **Early Exit:** As soon as we find a missing number, the function instantly returns `false`, preventing unnecessary checks.

---

## 🚀 Further Exploration

* How would you solve this if you couldn't use extra space (`O(1)` space complexity) but modifying the array was allowed? (Hint: Think about sorting or cyclic sort algorithms if the range starts from 1).
* What if the array was extremely large and couldn't fit into memory?

---

## 🔗 References

* **GeeksforGeeks Problem:** [Elements in the Range](https://www.geeksforgeeks.org/problems/elements-in-the-range2834/1)
* **Concept:** Checking subset presence using Hash Tables.

---

## 👨‍💻 Author

Created by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Arrays` `#Searching` `#Data Structures` `#Algorithms` `#Hash Set` `#GeeksforGeeks`