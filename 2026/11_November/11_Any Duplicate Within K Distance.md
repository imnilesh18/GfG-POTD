# 🟧 Any Duplicate Within K Distance

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-008159?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy: 48.69%](https://img.shields.io/badge/Accuracy-48.69%25-blue?style=for-the-badge)
![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statements and test cases are based on the GeeksforGeeks problem.

---

## 📌 Problem Statement

Given an array of integers, `arr[]` and an integer `k`, check whether there exist two distinct indices `i` and `j` such that `arr[i]` is equal to `arr[j]` and the absolute difference between `i` and `j` is at most `k`.

### Constraints
- $2 \le \text{arr.size()} \le 10^5$
- $1 \le \text{arr}[i] \le 10^5$
- $1 \le k < \text{arr.size()}$

---

## 💡 Examples

```text
Input: arr[] = [1, 5, 4, 5, 1], k = 3
Output: true
Explanation: The element 5 occurs at indices 1 and 3. Their distance is |3 - 1| = 2, which is less than or equal to k.

```

```text
Input: arr[] = [10, 2, 3, 4, 10, 5], k = 3
Output: false
Explanation: The element 10 occurs at indices 0 and 4. Their distance is |4 - 0| = 4, which is greater than k. Hence, no duplicate exists within the given distance.

```

Let's trace `arr[] = [1, 5, 4, 5, 1]`, `k = 3`:

* Index `0`: element `1`, window `[1]`
* Index `1`: element `5`, window `[1, 5]`
* Index `2`: element `4`, window `[1, 5, 4]`
* Index `3`: element `5`. Since `5` is already in our window (from index 1, distance `3 - 1 = 2 <= 3`), we immediately return `true`.

---

## 🛠️ Solution Approaches

### Approach 1: Hash Map (Tracking Most Recent Index)

#### Summary & Intuition

We can store each element's most recent index in a hash map. As we iterate through the array, if we encounter an element that already exists in the map, we check if the difference between the current index and the stored index is less than or equal to `k`.

#### C++ Code

```cpp
// Intuition: Store the last seen index of each element in a hash map to check proximity efficiently.
// Approach: Iterate through the array, check if the current element was seen within index distance k, and update its latest index.
// Time Complexity: O(n) because we traverse the array of size n and hash map operations take O(1) on average.
// Space Complexity: O(n) to store elements and their indices in the hash map in the worst case.
class Solution {
  public:
    bool checkWithinK(vector<int>& arr, int k) {
        unordered_map<int, int> map; // Stores element -> most recent index
        
        for (int i = 0; i < arr.size(); i++) {
            // If element exists and the distance is <= k
            if (map.find(arr[i]) != map.end() && i - map[arr[i]] <= k) {
                return true; // Duplicate found within distance k
            }
            // Update the map with the most recent index of the element
            map[arr[i]] = i;
        }
        
        return false; // No duplicates within distance k
    }
};

/*
*
* Dry Run
* Input: arr = [1, 5, 4, 5, 1], k = 3
* i = 0: arr[0] = 1, map = {1: 0}
* i = 1: arr[1] = 5, map = {1: 0, 5: 1}
* i = 2: arr[2] = 4, map = {1: 0, 5: 1, 4: 2}
* i = 3: arr[3] = 5, found in map at index 1. 3 - 1 = 2 <= 3. Returns true.
*
*/

```

---

### Approach 2: Sliding Window using Hash Set (Optimized Space)

#### Summary & Intuition

Since we only care about duplicates within a window of size `k`, we can maintain a sliding window using an `unordered_set` of size at most `k + 1`. When the window size exceeds `k`, we remove the element that falls out of the window bounds.

#### C++ Code

```cpp
// Intuition: Maintain a sliding window of size k using a hash set to track elements within the allowed distance.
// Approach: Iterate through the array, check for existence in the set, insert the element, and remove elements older than k distance.
// Time Complexity: O(n) as each element is inserted and erased from the set at most once.
// Space Complexity: O(min(n, k)) because the sliding window size never exceeds k + 1 elements.
class Solution {
  public:
    bool checkWithinK(vector<int>& arr, int k) {
        unordered_set<int> window;

        for (int i = 0; i < arr.size(); i++) {
            // If the element is already in the set, a duplicate exists within distance k
            if (window.find(arr[i]) != window.end()) {
                return true;
            }

            // Add the current element to the window
            window.insert(arr[i]);

            // Maintain the sliding window of size k
            // When index i >= k, the element at i - k falls out of the allowed distance
            if (i >= k) {
                window.erase(arr[i - k]);
            }
        }

        return false;
    }
};

/*
*
* Dry Run
* Input: arr = [1, 5, 4, 5, 1], k = 3
* i = 0: window = {1}
* i = 1: window = {1, 5}
* i = 2: window = {1, 5, 4}
* i = 3: arr[3] = 5 exists in window. Returns true.
*
*/

```

---

## 🔑 Key Insights

* **Sliding Window Optimization**: Using a hash set constrained to size `k` reduces space complexity from `O(n)` to `O(\min(n, k))`.
* **Early Exit**: As soon as a matching element is located within the distance threshold, the algorithm terminates immediately.

---

## 🚀 Further Exploration

* [Contains Duplicate II (LeetCode 219)](https://leetcode.com/problems/contains-duplicate-ii/)
* [Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/)

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/kth-distance3757/1)



---

## 👤 Author

* GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Hash` `Sliding Window` `GeeksforGeeks`