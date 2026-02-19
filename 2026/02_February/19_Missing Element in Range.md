# 🔍 Missing Element in Range

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-65.5%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> **Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/missing-element-in-range/1) problem.** ---

## 📝 Problem Statement

Given an array `arr[]` of **distinct** integers and a range `[low, high]`, find all the numbers within the range that are **not present** in the array. Return the missing numbers in **sorted order**.

### 🔍 Constraints

- `1 ≤ arr.size(), low, high ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^5`

---

## 📊 Examples

### Example 1

```bash
Input: arr[] = [10, 12, 11, 15], low = 10, high = 15
Output: [13, 14]
Explanation: Numbers 13 and 14 lie in the range [10, 15] but are not present in the array.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

1. **Array:** `[10, 12, 11, 15]`
2. **Range:** `10` to `15` -> `{10, 11, 12, 13, 14, 15}`
3. **Check 10:** Present in array? **Yes**.
4. **Check 11:** Present in array? **Yes**.
5. **Check 12:** Present in array? **Yes**.
6. **Check 13:** Present in array? **No**. -> Add to result.
7. **Check 14:** Present in array? **No**. -> Add to result.
8. **Check 15:** Present in array? **Yes**.
9. **Result:** `[13, 14]`

</details>

### Example 2

```bash
Input: arr[] = [1, 4, 11, 51, 15], low = 50, high = 55
Output: [50, 52, 53, 54, 55]
Explanation: Numbers 50, 52, 53, 54 and 55 lie in the range [50, 55] but are not present in the array.

```

---

## 💡 Solution Approach

### 🚀 Optimized Approach: Hash Set Lookup

#### Intuition

The core problem is to check for the existence of numbers within a specific range inside a given array. Since the output must be sorted and we need to check every number in the range `[low, high]`, a brute-force linear search for each number would be inefficient (`O(N * R)`). Using a **Hash Set** reduces the lookup time to `O(1)` on average, making the checking process significantly faster.

#### Algorithm

1. Insert all elements of the input array `arr` into an `unordered_set` for fast lookups.
2. Iterate through every integer `i` from `low` to `high`.
3. For each `i`, check if it exists in the set.
4. If `i` is not found in the set, add it to the `result` vector.
5. Since the loop runs from `low` to `high` incrementally, the `result` vector will automatically be sorted.
6. Return the `result`.

### 💻 Code (C++)

```cpp
// Intuition: We need to find numbers in a specific range [low, high] that are missing from the input array. Using a Hash Set allows us to check for the existence of any number in O(1) time average.
// Approach: First, insert all elements of the array into an unordered_set for fast lookup. Then, iterate through every number from 'low' to 'high'. If a number is not found in the set, add it to our result list. Since we iterate linearly from low to high, the result is automatically sorted.
// Time Complexity: O(N + R), where N is the size of the array (for insertion) and R is the range size (high - low + 1) for iteration.
// Space Complexity: O(N) to store the elements of the array in the unordered_set.

class Solution {
  public:
    vector<int> missinRange(vector<int>& arr, int low, int high) {
        // Use unordered_set for O(1) average time complexity lookups
        unordered_set<int> elements(arr.begin(), arr.end());
        
        vector<int> result;
        
        // Iterate through the target range [low, high]
        for (int i = low; i <= high; i++) {
            
            // If current number 'i' is not in the set, it is missing
            if (elements.find(i) == elements.end()) {
                result.push_back(i);
            }
        }
        
        return result;
    }
};

/*
* Dry Run
* * Input: arr = [10, 12, 11, 15], low = 10, high = 15
* * 1. Initialize unordered_set 'elements' with arr values: {10, 12, 11, 15}
* 2. Initialize empty vector 'result'.
* * 3. Loop i from 10 to 15:
* i = 10: Found in set? Yes. Do nothing.
* i = 11: Found in set? Yes. Do nothing.
* i = 12: Found in set? Yes. Do nothing.
* i = 13: Found in set? No. Add 13 to result. Result: [13]
* i = 14: Found in set? No. Add 14 to result. Result: [13, 14]
* i = 15: Found in set? Yes. Do nothing.
* * 4. Return result: [13, 14]
*/

```

---

## 🔑 Key Insights

* **Space-Time Tradeoff:** By using extra space `O(N)` for the set, we drastically reduce the time needed to check if a number exists in the array from `O(N)` to `O(1)`.
* **Automatic Sorting:** Iterating the loop from `low` to `high` naturally ensures the output elements are added in increasing order, avoiding the need for an explicit sorting step (`O(R log R)`).
* **Complexity:** The efficiency depends heavily on the size of the range `R` and the size of the array `N`. The solution is linear with respect to the sum of these sizes.

---

## 🔗 References

* **[Original Problem on GeeksforGeeks](https://www.geeksforgeeks.org/problems/missing-element-in-range/1)**
* **[C++ Unordered Set Documentation](https://en.cppreference.com/w/cpp/container/unordered_set)**

---

## 🛠️ Further Exploration

* **Missing Number:** Find the one missing number in an array containing 0 to n.
* **Find All Numbers Disappeared in an Array:** A similar problem often solvable without extra space by marking indices.
* **Kth Missing Positive Number:** Finding the *k*-th missing number instead of all missing numbers.

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**