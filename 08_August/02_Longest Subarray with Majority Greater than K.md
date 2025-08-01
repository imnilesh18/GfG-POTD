# 📈 Longest Subarray with Majority Greater than K

<div align="center">

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/longest-subarray-with-majority-greater-than-k/1).

</div>

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-52.63%25-green.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=for-the-badge)

</div>

---

## 📝 Problem Statement

Given an array `arr[]` and an integer `k`, the task is to find the length of the **longest** subarray in which the **count** of elements **greater than k** is **more** than the **count** of elements **less than or equal to k**.

---

## 🧪 Examples

### Example 1:

```
Input: arr[] = [1, 2, 3, 4, 1], k = 2
Output: 3
Explanation: The subarray [3, 4, 1] satisfies the condition.
- Elements > k (2): {3, 4} (Count = 2)
- Elements <= k (2): {1} (Count = 1)
Since 2 > 1, the condition holds. The length is 3.
The subarray [2, 3, 4] also works, with length 3.
No subarray of length 4 or 5 satisfies the condition.
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>
<br>

Let's walk through the first example: `arr[] = [1, 2, 3, 4, 1]`, `k = 2`.

The core idea is to transform the array into a new array of `+1`s and `-1`s.

- If `arr[i] > k`, we treat it as `+1`.
- If `arr[i] <= k`, we treat it as `-1`.

The problem now becomes finding the **longest subarray with a sum > 0**.

1.  **Transformed Array**:
    `arr[] = [1, 2, 3, 4, 1]`
    `k = 2`
    Transformed: `[-1, -1, 1, 1, -1]` (since `1<=2`, `2<=2`, `3>2`, `4>2`, `1<=2`)

2.  **Prefix Sum Calculation & Hashing**: We compute the prefix sum and store the _first occurrence_ of each sum in a hash map. We are looking for a subarray `[j+1, i]` such that `prefix_sum[i] - prefix_sum[j] > 0`.

| Index (i) | Element | Transformed | `sum` (Prefix Sum) | `map` {sum: index}      | `max_len` Calculation                                                        | `max_len` |
| :-------- | :------ | :---------- | :----------------- | :---------------------- | :--------------------------------------------------------------------------- | :-------- |
| -1        | -       | -           | 0                  | `{0: -1}`               | Initial state                                                                | 0         |
| 0         | 1       | -1          | -1                 | `{0: -1, -1: 0}`        | `sum-1` (-2) not in map.                                                     | 0         |
| 1         | 2       | -1          | -2                 | `{0: -1, -1: 0, -2: 1}` | `sum-1` (-3) not in map.                                                     | 0         |
| 2         | 3       | +1          | -1                 | `{0: -1, -1: 0, -2: 1}` | `sum-1` (-2) is in map. `len = 2 - map[-2] = 2 - 1 = 1`.                     | 1         |
| 3         | 4       | +1          | 0                  | `{0: -1, -1: 0, -2: 1}` | `sum > 0` is false. `sum-1` (-1) is in map. `len = 3 - map[-1] = 3 - 0 = 3`. | 3         |
| 4         | 1       | -1          | -1                 | `{0: -1, -1: 0, -2: 1}` | `sum-1` (-2) is in map. `len = 4 - map[-2] = 4 - 1 = 3`.                     | 3         |

The final `max_len` is **3**.

</details>

### Example 2:

```
Input: arr[] = [6, 5, 3, 4], k = 2
Output: 4
Explanation: In the subarray [6, 5, 3, 4], there are 4 elements > 2 and 0 elements <= 2. The count of greater elements (4) is more than the count of other elements (0). This is the longest possible subarray.
```

---

## ⛓️ Constraints

> `1 ≤ arr.size() ≤ 10^6` 
>`1 ≤ arr[i] ≤ 10^6` 
>`0 ≤ k ≤ 10^6`

---

## 💡 Solution Approaches

### Optimized Approach (Prefix Sum & Hashing)

The problem asks for the longest subarray where the count of elements `> k` exceeds the count of elements `<= k`.

We can rephrase this by converting the array into a simpler form. Let's represent elements `> k` as `+1` and elements `<= k` as `-1`. The problem now transforms into finding the **longest subarray with a sum greater than 0**.

A subarray sum being greater than 0 means it has more `+1`s than `-1`s.

To find this efficiently, we use the concept of **prefix sums**. Let `prefix_sum[i]` be the sum of the transformed array from index `0` to `i`. A subarray from `j+1` to `i` has a sum `prefix_sum[i] - prefix_sum[j]`. We need `prefix_sum[i] - prefix_sum[j] > 0`, which is `prefix_sum[i] > prefix_sum[j]`.

To maximize the length `i - j`, for each `i`, we need to find the smallest `j` that satisfies this condition. A hash map is perfect for this. We store the _first index_ where a particular prefix sum appears.

#### C++ Code

```cpp
// Intuition: The problem can be simplified by converting the array into a binary representation.
// Elements > k become +1, and elements <= k become -1. The goal is then to find the
// longest subarray with a sum greater than 0.
//
// Approach:
// 1. Initialize a `sum = 0`, `max_len = 0`, and a hash map `mp` to store the first occurrence of each prefix sum.
// 2. Pre-populate the map with `mp[0] = -1` to handle cases where the valid subarray starts from index 0.
// 3. Iterate through the array from `i = 0` to `n-1`.
// 4. In each iteration, update the `sum` by adding `+1` if `arr[i] > k` and `-1` otherwise.
// 5. Check for two conditions to update `max_len`:
//    a. If `sum > 0`, it means the subarray from index `0` to `i` is a valid candidate. Update `max_len = i + 1`.
//    b. We need a subarray with a sum of at least 1. To find the longest such subarray ending at `i`,
//       we look for a previous prefix sum `sum - 1`. If `mp.count(sum - 1)` exists, it means we found
//       a subarray between `mp[sum - 1]` and `i` with a sum of exactly 1. Update `max_len` with `i - mp[sum - 1]`.
//       (We check for `sum-1` and not just any smaller sum because `sum-1` will give the longest possible length for the current `i`).
// 6. If the current `sum` is not already in the map, add it with its index `i`. This ensures we always store the
//    leftmost index for any sum, which is crucial for maximizing the subarray length.
//
// Time Complexity: O(N), where N is the size of the array. We iterate through the array once.
// Space Complexity: O(N), as the hash map can store up to N distinct prefix sums in the worst case.
class Solution {
public:
    int longestSubarray(vector<int> &arr, int k) {
        unordered_map<int, int> mp;
        int sum = 0;
        int max_len = 0;

        // A sum of 0 is found at index -1 (before the array starts)
        mp[0] = -1;

        for (int i = 0; i < arr.size(); ++i) {
            // Transform the element to +1 or -1 and update sum
            sum += (arr[i] > k) ? 1 : -1;

            // If the current prefix sum is positive, the subarray from index 0 is a candidate.
            // This handles cases where the longest subarray starts from the beginning.
            if (sum > 0) {
                max_len = max(max_len, i + 1);
            }

            // Find a subarray with a sum of at least 1 ending at i.
            // This is equivalent to finding a previous prefix sum of `sum - 1`.
            // mp[sum-1] gives the end of a prefix that we can remove to get a subarray sum of 1.
            if (mp.count(sum - 1)) {
                max_len = max(max_len, i - mp[sum - 1]);
            }

            // If the current sum hasn't been seen before, record its first occurrence.
            // This is key to finding the longest subarray. We only care about the leftmost
            // position of a prefix sum.
            if (mp.find(sum) == mp.end()) {
                mp[sum] = i;
            }
        }
        return max_len;
    }
};
/*
*
* Dry Run with arr[] = [1, 2, 3, 4, 1], k = 2
* Transformed array: [-1, -1, 1, 1, -1]
*
* i = 0: arr[0]=1 -> sum = -1. mp[-1] = 0.
* i = 1: arr[1]=2 -> sum = -2. mp[-2] = 1.
* i = 2: arr[2]=3 -> sum = -1. mp.count(-1-1 = -2) is true. max_len = max(0, 2 - mp[-2]) = max(0, 2 - 1) = 1.
* i = 3: arr[3]=4 -> sum = 0. sum > 0 is false. mp.count(0-1 = -1) is true. max_len = max(1, 3 - mp[-1]) = max(1, 3 - 0) = 3.
* i = 4: arr[4]=1 -> sum = -1. mp.count(-1-1 = -2) is true. max_len = max(3, 4 - mp[-2]) = max(3, 4 - 1) = 3.
*
* Final Result: 3
*
*/
```

#### Java Code

```java
// Intuition: The problem can be simplified by converting the array into a binary representation.
// Elements > k become +1, and elements <= k become -1. The goal is then to find the
// longest subarray with a sum greater than 0.
//
// Approach:
// 1. Initialize a `sum = 0`, `maxLength = 0`, and a HashMap `map` to store the first occurrence of each prefix sum.
// 2. Pre-populate the map with `map.put(0, -1)` to handle cases where the valid subarray starts from index 0.
// 3. Iterate through the array from `i = 0` to `n-1`.
// 4. In each iteration, update the `sum` by adding `+1` if `arr[i] > k` and `-1` otherwise.
// 5. Check for two conditions to update `maxLength`:
//    a. If `sum > 0`, it means the subarray from index `0` to `i` is a valid candidate. Update `maxLength = i + 1`.
//    b. We need a subarray with a sum of at least 1. To find the longest such subarray ending at `i`,
//       we look for a previous prefix sum `sum - 1`. If `map.containsKey(sum - 1)` exists, it means we found
//       a subarray between `map.get(sum - 1)` and `i` with a sum of exactly 1. Update `maxLength` with `i - map.get(sum - 1)`.
// 6. If the current `sum` is not already in the map, add it with its index `i`. This ensures we always store the
//    leftmost index for any sum, which is crucial for maximizing the subarray length.
//
// Time Complexity: O(N), where N is the size of the array. We iterate through the array once.
// Space Complexity: O(N), as the HashMap can store up to N distinct prefix sums in the worst case.
class Solution {
    public int longestSubarray(int[] arr, int k) {
        // The Java equivalent of an unordered_map is a HashMap.
        Map<Integer, Integer> map = new HashMap<>();
        int sum = 0;
        int maxLength = 0;

        // A sum of 0 is found at index -1 (before the array starts)
        map.put(0, -1);

        for (int i = 0; i < arr.length; ++i) {
            // Transform the element to +1 or -1 and update sum
            sum += (arr[i] > k) ? 1 : -1;

            // If the current prefix sum is positive, the subarray from index 0 is a candidate.
            if (sum > 0) {
                maxLength = Math.max(maxLength, i + 1);
            }

            // Find a subarray with a sum of at least 1 ending at i.
            // This is equivalent to finding a previous prefix sum of `sum - 1`.
            if (map.containsKey(sum - 1)) {
                maxLength = Math.max(maxLength, i - map.get(sum - 1));
            }

            // If the current sum hasn't been seen before, record its first occurrence.
            // `putIfAbsent` or checking `!containsKey` achieves this.
            if (!map.containsKey(sum)) {
                map.put(sum, i);
            }
        }
        return maxLength;
    }
}
/*
*
* Dry Run with arr[] = [1, 2, 3, 4, 1], k = 2
* Transformed array: [-1, -1, 1, 1, -1]
*
* i = 0: arr[0]=1 -> sum = -1. map.put(-1, 0).
* i = 1: arr[1]=2 -> sum = -2. map.put(-2, 1).
* i = 2: arr[2]=3 -> sum = -1. map.containsKey(-1-1 = -2) is true. maxLength = max(0, 2 - map.get(-2)) = max(0, 2 - 1) = 1.
* i = 3: arr[3]=4 -> sum = 0. sum > 0 is false. map.containsKey(0-1 = -1) is true. maxLength = max(1, 3 - map.get(-1)) = max(1, 3 - 0) = 3.
* i = 4: arr[4]=1 -> sum = -1. map.containsKey(-1-1 = -2) is true. maxLength = max(3, 4 - map.get(-2)) = max(3, 4 - 1) = 3.
*
* Final Result: 3
*
*/
```

---

## 🎯 Key Insights

- **Problem Transformation**: The core idea is to abstract the problem. Instead of dealing with the actual values, we classify them into two categories: `> k` (`+1`) and `<= k` (`-1`). This simplifies the condition to a simple sum.
- **Prefix Sum Power**: This transformation makes the problem a classic prefix sum application. We are looking for a subarray `(j, i]` where `prefix[i] - prefix[j] > 0`.
- **Why Hashing Works**: To maximize the length `i - j`, we need the smallest `j` for each `i`. By storing the _first time_ we see a prefix sum in a hash map, we guarantee that when we calculate `i - map.get(sum-1)`, we are using the leftmost possible start for a valid subarray, thus maximizing its length.
- **Edge Case `sum > 0`**: The check `if (sum > 0)` is a special case of the general logic. Here, `prefix[j]` would be `0` at index `j=-1`, so the length is `i - (-1) = i + 1`. Our initialization `map.put(0, -1)` handles this, but an explicit check can be clearer.

---

## 🔎 Further Exploration

Here are some related problems that use similar concepts of prefix sums, hashing, and array transformations:

- [**Subarray Sum Equals K**](https://www.geeksforgeeks.org/problems/subarrays-with-sum-k/1): Find the total number of continuous subarrays whose sum equals a given integer k.
- [**Longest Sub-array with Sum K**](https://www.geeksforgeeks.org/problems/longest-sub-array-with-sum-k/1): Find the length of the longest subarray with a sum equal to k.
- [**Count Subarrays with Equal 0s and 1s**](https://www.geeksforgeeks.org/problems/count-subarrays-with-equal-number-of-1s-and-0s-1587115620/1): A direct application where 0s are treated as -1s.
- [**Longest Subarray with sum divisible by K**](https://www.geeksforgeeks.org/problems/longest-subarray-with-sum-divisible-by-k/1): Uses prefix sums and the modulo operator.

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/longest-subarray-with-majority-greater-than-k/1)
- [Article on Prefix Sums](https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/)

---

## 🧑‍💻 Author

<div align="center">
    <a href="https://github.com/imnilesh18">imnilesh18</a>
</div>

---

## 🏷️ Tags

![Array](https://img.shields.io/badge/Array-20232A?style=for-the-badge&logo=react)
![Prefix Sum](https://img.shields.io/badge/Prefix_Sum-007ACC?style=for-the-badge&logo=cplusplus)
![Hashing](https://img.shields.io/badge/Hashing-3178C6?style=for-the-badge&logo=java)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks)

---

## 📜 License

This project is licensed under the MIT License.

**A gentle reminder:** The solutions and explanations provided here are for educational purposes. They are meant to help you understand the problem-solving process. It is highly encouraged to try solving the problem on your own before referring to these solutions.

Happy Coding! 🎉
