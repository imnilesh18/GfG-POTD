# 🧩 Split Array Subsequences

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Split%20Array%20Subsequences-green?style=flat&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=flat)
![Accuracy](https://img.shields.io/badge/Accuracy-44.16%25-blue?style=flat)
![Points](https://img.shields.io/badge/Points-4-orange?style=flat)
![License](https://img.shields.io/badge/License-MIT-brightgreen?style=flat)

---

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/split-array-subsequences/1).

---

## 📝 Problem Statement

Given a **sorted** integer array `arr[]` and an integer `k`, determine if it is possible to split the array into one or more **consecutive subsequences** such that:

1.  Each subsequence consists of **consecutive integers** (each number is exactly one greater than the previous).
2.  Every subsequence has a **length of at least `k`**.

Return `true` if such a split is possible, otherwise return `false`.

---

## 🧪 Examples

**Example 1:**

```plaintext
Input: arr[] = [2, 2, 3, 3, 4, 5], k = 2
Output: true
`````

<details>
<summary>📖 Example Breakdown</summary>

The array `arr = [2, 2, 3, 3, 4, 5]` needs to be split into consecutive subsequences, each of length at least `k = 2`.

1.  We encounter the first `2`. Start a subsequence: `[2]`
2.  We encounter the second `2`. Start another subsequence: `[2]`
3.  We encounter the first `3`. It can extend the first subsequence `[2]` -\> `[2, 3]`
4.  We encounter the second `3`. It can extend the second subsequence `[2]` -\> `[2, 3]`
5.  We encounter `4`. Start a new subsequence (since both `3`s are used): `[4]`
6.  We encounter `5`. It can extend the subsequence `[4]` -\> `[4, 5]`

The resulting subsequences are `[2, 3]`, `[2, 3]`, and `[4, 5]`.
All subsequences are consecutive, and their lengths (`2`, `2`, `2`) are all greater than or equal to `k = 2`.
Therefore, the output is `true`.

</details>

**Example 2:**

```plaintext
Input: arr[] = [1, 1, 1, 1, 1], k = 4
Output: false
Explanation: It is impossible to split arr into consecutive increasing subsequences of length 4 or more.
```

-----

## ⛓️ Constraints

>   - `1 ≤ arr.size() ≤ 10^5`
>   - `1 ≤ arr[i] ≤ 10^5`
>   - `1 ≤ k ≤ arr.size()`
>   - The input array `arr[]` is sorted in non-decreasing order.

-----

## 💡 Solution Approach

### Optimized Approach (Using Min-Heap)

The core idea is to greedily extend existing subsequences whenever possible. We use a min-heap to keep track of the subsequences currently being formed. The heap stores pairs `(last_element, length)`, prioritizing subsequences that end with a smaller number and, among those, subsequences with shorter lengths. This prioritization helps ensure we extend shorter subsequences first, making it easier to meet the length `k` requirement.

```cpp
// Intuition: We want to greedily assign each number to an existing consecutive subsequence.
//            If a number `x` arrives, we prefer attaching it to a subsequence ending in `x-1`.
//            Among subsequences ending in `x-1`, we prioritize the shortest one to help it reach length `k`.
//            A min-heap is suitable for managing the "ending number" and "length" of active subsequences.
// Approach:
// 1. Initialize a min-heap `pq` storing pairs `{end_number, length}`.
// 2. Define a custom comparator for the heap:
//    - Prioritize smaller `end_number`.
//    - If `end_number` is the same, prioritize smaller `length` (min-heap stores pairs such that `a.second > b.second` means `a` has higher priority).
// 3. Iterate through the input array `arr`:
//    a. If the heap is empty, start a new subsequence: push `{arr[i], 1}`.
//    b. Get the top element `top = {end_num, len}` from the heap.
//    c. If `arr[i] == end_num`: Start a new subsequence with `arr[i]`: push `{arr[i], 1}`.
//    d. If `arr[i] == end_num + 1`: Extend the subsequence at the top: pop `top`, push `{arr[i], len + 1}`.
//    e. If `arr[i] > end_num + 1`: The subsequence `top` cannot be extended further. Check if its length `len < k`. If so, return `false`. Otherwise, pop `top` and *re-process* `arr[i]` (stay at the same index `i` by not incrementing).
// 4. After iterating through `arr`, check any remaining subsequences in the heap. If any subsequence has `length < k`, return `false`.
// 5. If all checks pass, return `true`.
// Time Complexity: O(N log N), where N is the size of `arr`. Each element is pushed and popped from the heap at most once. Heap operations take O(log N) time (heap size can be up to N).
// Space Complexity: O(N), in the worst case, the heap might store N elements if all numbers are distinct and start new subsequences.

class Solution {
public:
    bool isPossible(vector<int>& arr, int k) {
        // Custom comparator for the min-heap
        auto comp = [](pair<int, int> a, pair<int, int> b) {
            // If numbers are different, prioritize the smaller number
            if (a.first != b.first) {
                return a.first > b.first; // Min-heap based on the ending number
            }
            // If numbers are the same, prioritize the shorter subsequence length
            return a.second > b.second; // Min-heap based on length (shorter first)
        };

        // Min-heap stores pairs: {end_number, length of subsequence ending with end_number}
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);

        int i = 0;
        while (i < arr.size()) {
            // Remove completed subsequences that cannot be extended by arr[i]
            while (!pq.empty() && arr[i] > pq.top().first + 1) {
                // If a subsequence ends too early and its length is less than k, return false
                if (pq.top().second < k) {
                    return false;
                }
                pq.pop(); // Remove the valid, completed subsequence
            }

            if (pq.empty()) {
                // If heap is empty or no suitable subsequence exists, start a new one
                pq.push({arr[i], 1});
                i++;
            } else {
                // If current number matches the end of the highest priority subsequence
                if (arr[i] == pq.top().first) {
                     // Start a new subsequence (as the existing one with the same end number might be shorter)
                    pq.push({arr[i], 1});
                    i++;
                }
                // If current number can extend the highest priority subsequence
                else if (arr[i] == pq.top().first + 1) {
                    auto top = pq.top(); // Get the top element
                    pq.pop();           // Remove it
                    // Push the extended subsequence back
                    pq.push({arr[i], top.second + 1});
                    i++;
                } else {
                     // This case (arr[i] < pq.top().first) shouldn't happen due to the sorted array and the cleanup loop above.
                     // If arr[i] > pq.top().first + 1, it's handled by the cleanup loop.
                     // Defensive programming: If somehow we reach here, start a new subsequence.
                     pq.push({arr[i], 1});
                     i++;
                }
            }
        }

        // After processing all numbers, check if all remaining subsequences in the heap have length >= k
        while (!pq.empty()) {
            if (pq.top().second < k) {
                return false; // Found an incomplete subsequence
            }
            pq.pop(); // Remove valid subsequence
        }

        // If all subsequences are valid
        return true;
    }
};

/*
*
* Dry Run
* Input: arr[] = [2, 2, 3, 3, 4, 5], k = 2
*
* i = 0, arr[0] = 2. pq is empty. Push {2, 1}. pq = [{2, 1}]
* i = 1, arr[1] = 2. pq top = {2, 1}. arr[1] == top.first. Push {2, 1}. pq = [{2, 1}, {2, 1}] (Heap orders them internally)
* i = 2, arr[2] = 3. pq top = {2, 1}. arr[2] == top.first + 1. Pop {2, 1}. Push {3, 2}. pq = [{2, 1}, {3, 2}]
* i = 3, arr[3] = 3. pq top = {2, 1}. arr[3] == top.first + 1. Pop {2, 1}. Push {3, 2}. pq = [{3, 2}, {3, 2}]
* i = 4, arr[4] = 4. pq top = {3, 2}. arr[4] == top.first + 1. Pop {3, 2}. Push {4, 3}. pq = [{3, 2}, {4, 3}]
* i = 5, arr[5] = 5. pq top = {3, 2}. Cleanup loop: arr[5] > top.first + 1 (5 > 3 + 1). Check top.second (2) >= k (2). Yes. Pop {3, 2}. pq = [{4, 3}].
* Now process arr[5]=5. pq top = {4, 3}. arr[5] == top.first + 1. Pop {4, 3}. Push {5, 4}. pq = [{5, 4}]
* End of array.
* Check remaining heap: pq = [{5, 4}]. top.second (4) >= k (2). Yes. Pop {5, 4}. pq is empty.
* Return true.
*
* Input: arr[] = [1, 1, 1, 1, 1], k = 4
*
* i = 0, arr[0] = 1. pq is empty. Push {1, 1}. pq = [{1, 1}]
* i = 1, arr[1] = 1. pq top = {1, 1}. arr[1] == top.first. Push {1, 1}. pq = [{1, 1}, {1, 1}]
* i = 2, arr[2] = 1. pq top = {1, 1}. arr[2] == top.first. Push {1, 1}. pq = [{1, 1}, {1, 1}, {1, 1}]
* i = 3, arr[3] = 1. pq top = {1, 1}. arr[3] == top.first. Push {1, 1}. pq = [{1, 1}, {1, 1}, {1, 1}, {1, 1}]
* i = 4, arr[4] = 1. pq top = {1, 1}. arr[4] == top.first. Push {1, 1}. pq = [{1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}]
* End of array.
* Check remaining heap:
* pq top = {1, 1}. top.second (1) < k (4). Return false.
*
*/
```

-----

## 🔑 Key Insights

  - **Greedy Approach:** The core idea is to always try and extend the "most needy" existing subsequence first. The "most needy" is defined as the one ending with the smallest number (`x-1`) and having the shortest current length.
  - **Min-Heap Utility:** A min-heap perfectly models this greedy strategy. It allows efficient retrieval (`O(log N)`) of the subsequence that should be prioritized for extension. The custom comparator ensures we prioritize correctly based on the ending number and then the length.
  - **Handling Gaps:** When the current number `arr[i]` is greater than `pq.top().first + 1`, it signifies that the subsequence represented by `pq.top()` cannot be extended further. At this point, we *must* check if it meets the length requirement `k`. If it does, we discard it (pop); otherwise, we know it's impossible to form valid subsequences, and we return `false`.

-----

## 🚀 Further Exploration

  - **Variations:** What if the input array wasn't sorted? (You'd likely need a frequency map and potentially a more complex heap or map-based approach).
  - **Related Problems:**
      - [GeeksforGeeks: Split array into K disjoint subarrays](https://www.google.com/search?q=https://www.geeksforgeeks.org/split-the-array-into-k-sub-arrays-such-that-maximum-sum-among-all-sub-arrays-is-minimum/) (Different type of split, often involves binary search on the answer).
      - [LeetCode 659: Split Array into Consecutive Subsequences](https://leetcode.com/problems/split-array-into-consecutive-subsequences/) (Similar problem, but the minimum length requirement is fixed at 3).

-----

## 📚 References

  - [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/split-array-subsequences/1)
  - [Similar LeetCode Problem Discussion](https://leetcode.com/problems/split-array-into-consecutive-subsequences/discuss/) (May offer alternative perspectives/optimizations).

-----

## 👨‍💻 Author

  - [imnilesh18](https://github.com/imnilesh18)

-----

## 🏷️ Tags

-----

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file (if available in the repository) for details.

**Disclaimer:** The code and explanation provided are for educational purposes only. They are based on the problem statement from GeeksforGeeks and aim to help users understand the concepts involved. Always refer to the original problem source for official requirements and constraints.
