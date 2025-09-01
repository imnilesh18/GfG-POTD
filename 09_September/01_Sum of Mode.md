# 📊 Sum of Mode

<div align="center">

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/sum-of-mode/1).

</div>

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/sum-of-mode/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-54.28%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

## 📝 Problem Statement

Given an array `arr[]` of positive integers and an integer `k`, your task is to find the sum of the **modes** of all the subarrays of size `k`.

**Note**: The mode of a subarray is the element that occurs with the highest frequency. If multiple elements have the same highest frequency, the **smallest** such element is considered the mode.

---

### 📖 Examples

#### Example 1:

Input:
arr[] = [1, 2, 3, 2, 5, 2, 4, 4]
k = 3
Output: 13

<details>
<summary>📖 Example Breakdown</summary>
Let's walk through the subarrays of size 3:
<ul>
<li>Subarray <code>[1, 2, 3]</code> -> Frequencies: {1:1, 2:1, 3:1}. All have frequency 1. Smallest element is 1. **Mode = 1**.</li>
<li>Subarray <code>[2, 3, 2]</code> -> Frequencies: {2:2, 3:1}. Highest frequency is 2. **Mode = 2**.</li>
<li>Subarray <code>[3, 2, 5]</code> -> Frequencies: {2:1, 3:1, 5:1}. All have frequency 1. Smallest element is 2. **Mode = 2**.</li>
<li>Subarray <code>[2, 5, 2]</code> -> Frequencies: {2:2, 5:1}. Highest frequency is 2. **Mode = 2**.</li>
<li>Subarray <code>[5, 2, 4]</code> -> Frequencies: {2:1, 4:1, 5:1}. All have frequency 1. Smallest element is 2. **Mode = 2**.</li>
<li>Subarray <code>[2, 4, 4]</code> -> Frequencies: {2:1, 4:2}. Highest frequency is 2. **Mode = 4**.</li>
</ul>
The modes of all subarrays are: `[1, 2, 2, 2, 2, 4]`.
The sum of modes is: `1 + 2 + 2 + 2 + 2 + 4 = 13`.
</details>

#### Example 2:

Input:
arr[] = [1, 2, 1, 3, 5]
k = 2
Output: 6

**Explanation**: The modes of each k-size subarray are `[1, 1, 1, 3]`, and the sum of all modes is 6.

---

### ⛓️ Constraints

> - `1 ≤ k ≤ arr.size() ≤ 10^5`
> - `1 ≤ arr[i] ≤ 10^5`

---

## 💡 Solution Approaches

### Optimized Approach (Sliding Window with Ordered Set)

The core idea is to use a **sliding window** of size `k`. To efficiently find the mode at each step, we need a data structure that can keep track of element frequencies and quickly retrieve the element with the highest frequency (and smallest value in case of a tie).

- A `HashMap` or `unordered_map` is used to store the frequency of elements in the current window.
- An `Ordered Set` (`set` in C++, `TreeSet` in Java) is used to store pairs of `{frequency, value}`. This set automatically keeps the elements sorted. By sorting based on frequency first and then by value, the mode can always be found at the end of the set.

As the window slides, we remove the outgoing element's old frequency pair from the set, update its count, and re-insert it if it's still in the window. We do a similar update for the incoming element. This allows for an efficient O(log k) update at each step.

<h3>C++ Code</h3>

```cpp
// Intuition: To find the sum of modes of all subarrays of size k, a sliding window approach is efficient.
// We need a way to maintain the frequencies of elements in the current window and quickly find the mode.
// The mode is the element with the highest frequency; if frequencies are tied, it's the smallest element.

// Approach:
// 1. Use a sliding window of size k.
// 2. Use an unordered_map `mp` to store the frequency of elements within the window.
// 3. Use an ordered set `st` of pairs `{frequency, -value}`. The set keeps pairs sorted by frequency.
//    Storing `-value` ensures that for the same frequency, the element with a larger -value (smaller actual value) is considered greater,
//    placing it correctly for mode calculation (st.rbegin()).
// 4. Initialize the first window: calculate frequencies and populate the map and set.
// 5. Calculate the mode of the first window and add it to the sum. The mode is `-st.rbegin()->second`.
// 6. Slide the window from index k to n-1:
//    a. For the outgoing element: remove its old entry from the set, decrement its frequency in the map, and re-insert the updated entry if its count is > 0.
//    b. For the incoming element: if it's already in the map, remove its old entry from the set. Increment its frequency and insert the new entry.
//    c. Find the new mode from the set and add it to the total sum.
// 7. Return the total sum.

// Time Complexity: O(N log K), where N is the size of the array and K is the window size.
// We iterate through the array once (O(N)). In each iteration, set operations (insert, erase) take O(log K) time.

// Space Complexity: O(K), as the map and set will store at most K distinct elements from the window.

class Solution {
  public:
    int sumOfModes(vector<int> &arr, int k) {
      int n = arr.size();
      int sum = 0;

      // Stores frequency of elements in the current window
      unordered_map<int, int> mp;

      // Stores {frequency, -value} to find the mode efficiently.
      // The set automatically sorts by frequency. Negative value handles the tie-breaking rule.
      set<pair<int, int>> st;

      // Process the first window of size k
      for (int i = 0; i < k; i++) {
          mp[arr[i]]++; // Increment frequency
      }

      // Populate the set with initial frequency-value pairs
      for (auto x : mp) {
          st.insert({x.second, -x.first});
      }

      // The mode is the element with the highest frequency (last element in the set)
      int mode = -st.rbegin()->second;
      sum += mode; // Add the mode of the first window to the sum

      // Slide the window from the k-th element to the end of the array
      for (int i = k; i < n; i++) {
          int out = arr[i - k]; // Element leaving the window
          int in = arr[i];      // Element entering the window

          // --- Update for the outgoing element ---
          // Erase the old frequency pair for the outgoing element
          st.erase({mp[out], -out});
          mp[out]--; // Decrement its frequency

          if (mp[out] > 0) {
              // If the element is still in the window, insert its updated pair
              st.insert({mp[out], -out});
          } else {
              // Otherwise, remove it completely from the map
              mp.erase(out);
          }

          // --- Update for the incoming element ---
          if(mp.count(in)){
              // If the incoming element is already present, remove its old pair
              st.erase({mp[in], -in});
          }
          mp[in]++; // Increment its frequency
          st.insert({mp[in], -in}); // Insert the new/updated pair

          // Get the current mode and add it to the sum
          mode = -st.rbegin()->second;
          sum += mode;
      }

      return sum;
    }
};

/*
*
* Dry Run
* arr[] = [1, 2, 3, 2, 5, 2, 4, 4], k = 3
*
* Initial Window (i=0 to k-1): [1, 2, 3]
* mp = {{1, 1}, {2, 1}, {3, 1}}
* st = {{1, -3}, {1, -2}, {1, -1}}
* Mode = -st.rbegin()->second = -(-1) = 1.
* sum = 1.
*
* Slide 1 (i=k=3): out=1, in=2
* Window: [2, 3, 2]
* - Remove 1: erase({1, -1}) from st. mp[1] becomes 0. erase(1) from mp.
* - Add 2: mp[2] was 1, now 2. erase({1, -2}) from st. insert({2, -2}) into st.
* mp = {{2, 2}, {3, 1}}
* st = {{1, -3}, {2, -2}}
* Mode = -st.rbegin()->second = -(-2) = 2.
* sum = 1 + 2 = 3.
*
* Slide 2 (i=4): out=3, in=5
* Window: [3, 2, 5] -> Becomes [2, 5, 2] in next window but order doesn't matter for frequency
* - Remove 2 (first one): mp[2] becomes 1. erase({2, -2}). insert({1, -2}).
* - Remove 3: mp[3] becomes 0. erase({1, -3}). erase(3).
* - Add 5: mp[5] becomes 1. insert({1, -5}).
* mp = {{2, 1}, {5, 1}}
* st has {1, -5}, {1, -2}. Mode is 2.
* sum = 3 + 2 = 5.
*
* ...and so on. The final sum will be 13.
*
*/
```

---

## 🔑 Key Insights

- The combination of a **HashMap** and an **Ordered Set** (like `std::set` or `TreeSet`) is powerful for solving sliding window problems that require tracking order statistics like min/max/mode.
- The map provides O(1) average time complexity for frequency lookups and updates.
- The ordered set provides O(log k) time for insertions, deletions, and finding the element with the highest frequency.
- The tie-breaking rule (smallest element is the mode) is cleverly handled in C++ by inserting the _negative_ of the value into the set's pair. This makes the set's default sorting behavior work in our favor. In Java, a custom comparator is needed to achieve the same result.

---

## 🚀 Further Exploration

- [Sliding Window Maximum (Maximum of all subarrays of size k)](https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1)
- [Count distinct elements in every window of size k](https://www.geeksforgeeks.org/problems/count-distinct-elements-in-every-window/1)
- [First negative integer in every window of size k](https://www.geeksforgeeks.org/problems/first-negative-integer-in-every-window-of-size-k3345/1)

---

## 🔗 References

- **Original Problem:** [Sum of Mode on GeeksforGeeks](https://www.geeksforgeeks.org/problems/sum-of-mode/1)
- **Data Structures:** [Sliding Window Technique](https://www.geeksforgeeks.org/window-sliding-technique/), [C++ Set](https://www.geeksforgeeks.org/set-in-cpp-stl/), [Java TreeSet](https://www.geeksforgeeks.org/treeset-in-java-with-examples/)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

**A gentle reminder**: The solutions are for educational purposes. It's recommended to try solving the problem on your own first to maximize learning.
