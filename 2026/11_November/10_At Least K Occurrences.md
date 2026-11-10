# 🟩 At Least K Occurrences

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Practice-green?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/first-element-to-occur-k-times5150/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)]()
[![Accuracy: 37.11%](https://img.shields.io/badge/Accuracy-37.11%25-blue?style=for-the-badge)]()
[![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](LICENSE)

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` of integers and an integer `k`, find the **first element** that occurs **at least `k` times** in the array.

- If multiple elements satisfy the condition, return the element whose `k`-th occurrence appears **earliest** in the array.
- If no element occurs at least `k` times, return `-1`.

---

## 📖 Examples

### Example 1
```text
Input: arr[] = [1, 7, 4, 3, 4, 8, 7], k = 2
Output: 4
Explanation: Both 7 and 4 occur twice. However, 4 reaches its second occurrence before 7, so the answer is 4.
```

### Example 2
```text
Input: arr[] = [3, 1, 3, 4, 5, 1, 3, 3, 5, 4], k = 3
Output: 3
Explanation: The element 3 is the only element that occurs at least 3 times in the array.
```

### Example 3
```text
Input: arr[] = [10, 8, 2], k = 10
Output: -1
Explanation: No element occurs at least 10 times in the array.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough of Example 1)</b></summary>

<br/>

For `arr = [1, 7, 4, 3, 4, 8, 7]` and `k = 2`:

| Step | Current Num | Map Frequency State | Condition `freq[num] == 2` | Action / Result |
| :---: | :---: | :--- | :---: | :--- |
| 1 | `1` | `{1: 1}` | ❌ `1 != 2` | Continue |
| 2 | `7` | `{1: 1, 7: 1}` | ❌ `1 != 2` | Continue |
| 3 | `4` | `{1: 1, 7: 1, 4: 1}` | ❌ `1 != 2` | Continue |
| 4 | `3` | `{1: 1, 7: 1, 4: 1, 3: 1}` | ❌ `1 != 2` | Continue |
| 5 | `4` | `{1: 1, 7: 1, 4: 2, 3: 1}` | **✅ `2 == 2`** | **Return `4` immediately** |

Since `4` is the first element to hit a frequency of `2`, it is returned immediately.
</details>

---

## ⚙️ Constraints

> - $1 \le \text{arr.size()} \le 10^6$
> - $0 \le \text{arr}[i] \le 10^6$
> - $1 \le k \le 10^3$

---

## 🚀 Solution Approach

### Hash Map Frequency Counting (Single Pass)

#### Intuition
To find the element whose $k$-th occurrence appears earliest, we can iterate through the array sequentially from left to right while tracking the frequency of each element using a hash map (`unordered_map`). The moment any element's frequency count reaches $k$, we return that element immediately.

#### C++ Code Implementation

```cpp
// Intuition: Use a hash map to track element frequencies while iterating from left to right. Returning immediately when frequency reaches k guarantees finding the element whose k-th occurrence appears earliest.
// Approach: Traverse arr[], increment frequency count in unordered_map. If frequency equals k, return the element. If traversal completes without reaching k, return -1.
// Time Complexity: O(n) average time complexity as we traverse the array once and hash map lookups/updates take O(1) average time.
// Space Complexity: O(n) auxiliary space to store frequency counts of unique elements in the hash map.

class Solution {
  public:
    int firstElementKTime(vector<int>& arr, int k) {
        unordered_map<int, int> freq;

        for (int num : arr) {
            freq[num]++;

            // As soon as an element hits k occurrences, return it immediately
            if (freq[num] == k) {
                return num;
            }
        }

        return -1; // If no element reaches k occurrences
    }
};

/*
*
* Dry Run
*
* Input: arr = [1, 7, 4, 3, 4, 8, 7], k = 2
*
* Initial: freq = {}
*
* num = 1 -> freq[1] = 1 (1 != 2)
* num = 7 -> freq[7] = 1 (1 != 2)
* num = 4 -> freq[4] = 1 (1 != 2)
* num = 3 -> freq[3] = 1 (1 != 2)
* num = 4 -> freq[4] = 2 (2 == 2) -> Return 4
*
* Output: 4
*
*/
```

---

## 🔑 Key Insights

1. **Early Return Strategy:** Returning as soon as `freq[num] == k` avoids completing unnecessary array iterations and naturally selects the element whose $k$-th occurrence occurs first.
2. **Order Preservation:** Left-to-right sequential processing naturally preserves array indices, making hash map iteration optimal.
3. **Average $O(N)$ Performance:** `unordered_map` provides $O(1)$ average insertion and lookup performance.

---

## 🧪 Further Exploration

- **Follow-up Question:** What if constraints require $O(1)$ auxiliary space? (Consider modifying the array if elements fall in a specific range or index-mapping tricks).
- **Related Problems:**
  - [First Repeating Element](https://www.geeksforgeeks.org/problems/first-repeating-element4000/1)
  - [Majority Element](https://www.geeksforgeeks.org/problems/majority-element-1587115620/1)
  - [Non-Repeating Element](https://www.geeksforgeeks.org/problems/non-repeating-element3902/1)

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks - At Least K Occurrences](https://www.geeksforgeeks.org/problems/first-element-to-occur-k-times5150/1)
- **Standard Library:** [C++ `unordered_map` Documentation](https://en.cppreference.com/w/cpp/container/unordered_map)

---

## 👨‍💻 Author

Created with ❤️ by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

`arrays` `hash-map` `cpp` `geeksforgeeks` `easy` `dsa`