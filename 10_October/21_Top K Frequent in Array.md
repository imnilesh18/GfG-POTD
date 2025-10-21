#  Top K Frequent in Array

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/top-k-frequent-elements-in-array/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG Problem">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Accuracy-40.23%25-orange.svg?style=for-the-badge" alt="Accuracy: 40.23%">
  <img src="https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge" alt="Points: 4">
  <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License: MIT">
</p>

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. The solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/top-k-frequent-elements-in-array/1).

---

## 📝 Problem Statement

Given a non-empty integer array `arr[]`, your task is to find and return the top `k` elements that have the **highest frequency** in the array.

**Note:** If two numbers have the same frequency, the **larger number** should be given higher priority.

---

## 🧪 Examples

### Example 1
```
Input:
arr[] = [3, 1, 4, 4, 5, 2, 6, 1]
k = 2

Output:
[4, 1]

Explanation:
Frequency of 4 is 2.
Frequency of 1 is 2.
These two have the maximum frequency. Since 4 is larger than 1, it gets higher priority.
```

<details>
<summary>📖 Example 1 Breakdown</summary>

1.  **Count Frequencies:**
    * `3`: 1
    * `1`: 2
    * `4`: 2
    * `5`: 1
    * `2`: 1
    * `6`: 1
2.  **Identify Highest Frequencies:** The highest frequency is 2, which belongs to elements `1` and `4`.
3.  **Apply Tie-Breaker:** We need the top `k=2` elements. Both `1` and `4` have the same frequency (2). The problem states that the larger number gets higher priority.
4.  **Final Result:** Since `4 > 1`, the order is `[4, 1]`.

</details>

### Example 2
```
Input:
arr[] = [7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9]
k = 4

Output:
[5, 11, 7, 10]

Explanation:
Frequency of 5 is 3.
Frequency of 11 is 2.
Frequency of 7 is 2.
Frequency of 10 is 1.
The top 4 frequent elements are 5, 11, 7, and 10.
```

---

## ⛓️ Constraints

> `1 ≤ arr.size() ≤ 10^5`
> `1 ≤ arr[i] ≤ 10^5`
> `1 ≤ k ≤ number of distinct elements`

---

## 💡 Solution Approaches

### Optimized Approach: Using a Hash Map and Min-Heap

The most efficient way to solve this is to first count the frequency of each element using a hash map. Then, we can use a min-heap (priority queue) of size `k` to keep track of the top `k` most frequent elements encountered so far.

The min-heap stores pairs of `{frequency, element}`. By keeping the heap size at most `k`, we ensure that the element with the smallest frequency is always at the top, ready to be removed if a more frequent element comes along.

#### C++ Solution
```cpp
// Intuition: We can find the top k frequent elements by first counting the frequency of each element and then using a data structure to find the k elements with the highest frequencies. A min-heap is ideal for this, as it allows us to maintain a collection of the top k elements efficiently.

// Approach:
// 1. Create an unordered_map to store the frequency of each element in the input array.
// 2. Iterate through the array and populate the map.
// 3. Create a min-heap (priority_queue in C++) to store pairs of {frequency, element}.
// 4. Iterate through the frequency map. For each pair:
//    a. Push the {frequency, element} pair into the min-heap.
//    b. If the heap's size exceeds k, pop the top element (which has the smallest frequency).
// 5. After iterating through the map, the heap will contain the top k frequent elements.
// 6. Extract the elements from the heap and store them in a result vector. Since it's a min-heap, we populate the result from the end to get the correct descending order of frequency.

// Time Complexity: O(N log K), where N is the number of elements in the array. It takes O(N) to build the frequency map and O(N log K) to iterate through the map and perform heap operations.
// Space Complexity: O(N) for the unordered_map in the worst case (if all elements are unique) plus O(K) for the priority queue. So, the total space complexity is O(N).

class Solution {
  public:
    vector<int> topKFreq(vector<int> &arr, int k) {
        // Use a hash map to count the frequency of each element
        unordered_map<int, int> mp;
        for (int val: arr)
            mp[val]++;
    
        // Min-heap to keep track of top k frequent elements
        // The pair stores {frequency, element}
        priority_queue<pair<int, int>, 
        vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Iterate through the frequency map
        for (pair<int, int> entry : mp) {
            
            // Push the current element and its frequency into the heap
            pq.push({entry.second, entry.first});
            
            // If heap size exceeds k, remove the element with the smallest frequency
            if (pq.size() > k)
                pq.pop();
        }
    
        // Create a result vector of size k
        vector<int> res(k);
    
        // Extract elements from the heap in descending frequency order
        // We fill the result array from the end because the min-heap returns the smallest first
        for (int i = k-1; i >= 0; i--) {
            res[i] = pq.top().second;
            pq.pop();
        }
        
        return res;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [3, 1, 4, 4, 5, 2, 6, 1], k = 2
*
* 1. Frequency Map (mp):
* - After iterating through arr:
* mp = {{3, 1}, {1, 2}, {4, 2}, {5, 1}, {2, 1}, {6, 1}}
*
* 2. Min-Heap (pq) of size k=2:
* - Process {3, 1}: pq.push({1, 3}). pq = {{1, 3}}
* - Process {1, 2}: pq.push({2, 1}). pq = {{1, 3}, {2, 1}}
* - Process {4, 2}: pq.push({2, 4}). pq = {{1, 3}, {2, 1}, {2, 4}}. Size > 2, so pq.pop(). pq = {{2, 1}, {2, 4}}
* - Process {5, 1}: pq.push({1, 5}). pq = {{1, 5}, {2, 1}, {2, 4}}. Size > 2, so pq.pop(). pq = {{2, 1}, {2, 4}}
* - Process {2, 1}: pq.push({1, 2}). pq = {{1, 2}, {2, 1}, {2, 4}}. Size > 2, so pq.pop(). pq = {{2, 1}, {2, 4}}
* - Process {6, 1}: pq.push({1, 6}). pq = {{1, 6}, {2, 1}, {2, 4}}. Size > 2, so pq.pop(). pq = {{2, 1}, {2, 4}}
*
* 3. Final Heap Content:
* - pq = {{2, 1}, {2, 4}} (Note: order might vary internally, but these are the elements)
*
* 4. Extract Result:
* - Initialize res of size 2.
* - i = 1: res[1] = pq.top().second (which is 1). pq.pop(). pq = {{2, 4}}
* - i = 0: res[0] = pq.top().second (which is 4). pq.pop(). pq is empty.
*
* 5. Final Result:
* - res = [4, 1]
*
*/
```

---

## 🎯 Key Insights

-   The **hash map** is crucial for achieving an efficient frequency count in O(N) time.
-   A **min-heap** is preferred over a max-heap. While a max-heap could find the top `k` elements after populating it with all N unique elements, this would take O(N log N) time. A min-heap of size `k` allows us to process all unique elements in O(N log K) time, which is more efficient when `k` is much smaller than `N`.
-   The tie-breaking rule (larger number has higher priority) is naturally handled by the final extraction step. Since we extract from a min-heap (which places smaller numbers first in case of a frequency tie) and fill our result array backward, the larger numbers for a given frequency end up being placed first in the final output.

---

## 🚀 Further Exploration

-   [Kth Largest Element in an Array](https://www.geeksforgeeks.org/problems/kth-smallest-element/0)
-   [Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/)
-   [Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/)

---

## 📚 References

-   [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/top-k-frequent-elements-in-array/1)
-   [C++ Priority Queue (Min-Heap)](https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/)

---

## 👨‍💻 Author

-   Connect with me on GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p>
  <img src="https://img.shields.io/badge/Tag-Array-blue?style=for-the-badge" alt="Array">
  <img src="https://img.shields.io/badge/Tag-Hash Map-green?style=for-the-badge" alt="Hash Map">
  <img src="https://img.shields.io/badge/Tag-Heap-orange?style=for-the-badge" alt="Heap">
  <img src="https://img.shields.io/badge/Tag-Priority Queue-red?style=for-the-badge" alt="Priority Queue">
  <img src="https://img.shields.io/badge/Tag-GeeksforGeeks-298D46?style=for-the-badge" alt="GeeksforGeeks">
</p>

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder that this is for educational purposes. Always try to solve problems on your own first!**