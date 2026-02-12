# 🌻 Max min Height

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-Hard-red?style=for-the-badge&logo=geeksforgeeks" alt="GFG Hard" />
  <img src="https://img.shields.io/badge/Accuracy-62.86%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-yellow?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/Language-C++%20|%20Java-blue?style=for-the-badge" alt="Languages" />
  <img src="https://img.shields.io/badge/License-MIT-orange?style=for-the-badge" alt="License" />
</div>


---

## 📝 Problem Statement

Given a garden with `n` flowers planted in a row, represented by an array `arr[]`, where `arr[i]` denotes the height of the `i-th` flower.

You will water them for `k` days. In one day, you can water `w` **continuous** flowers. Whenever you water a flower, its height increases by `1` unit.

Your task is to **maximize the minimum height** of all flowers after `k` days of watering.

---

## 📖 Examples

### Sample Test Cases

```bash
Input: arr[] = [2, 3, 4, 5, 1], k = 2, w = 2
Output: 2
Explanation: 
The minimum height after watering is 2.
Day 1: Water the last two flowers -> arr becomes [2, 3, 4, 6, 2]
Day 2: Water the last two flowers -> arr becomes [2, 3, 4, 7, 3]
The minimum height is now 2 (at index 0).

```

```bash
Input: arr[] = [5, 8], k = 5, w = 1
Output: 9
Explanation: 
Day 1 - Day 4: Water the first flower -> arr becomes [9, 8]
Day 5: Water the second flower -> arr becomes [9, 9]
The minimum height is 9.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's understand **Example 1** thoroughly:

* **Initial State:** `[2, 3, 4, 5, 1]`, `k=2` days, `w=2` window size.
* **Goal:** Make the smallest element as large as possible. The smallest is `1` (index 4).
* **Day 1:** We need to increase the `1`. Since `w=2`, we can water indices `3` and `4`.
* Array becomes: `[2, 3, 4, 6, 2]`


* **Day 2:** The smallest elements are now `2` (at index 0 and 4). We can choose to water indices `3` and `4` again (or `0` and `1`).
* If we water `3` and `4`: Array becomes `[2, 3, 4, 7, 3]`.
* Minimum height is `2`.


* We cannot achieve a minimum height of `3` because we only have 2 days (2 units of water total). To make `arr[0]=2` into `3`, we need 1 day. To make `arr[4]=1` into `3`, we need 2 days. Total days needed = 3, but we only have `k=2`.
* Thus, the answer is **2**.

</details>

---

## ⚠️ Constraints

* $1 \leq arr.size() \leq 10^5$
* $1 \leq w \leq arr.size()$
* $1 \leq k \leq 10^5$
* $1 \leq arr[i] \leq 10^9$

---

## 💡 Solution Approaches

### 🔹 Intuition

The problem asks us to **"Maximize the Minimum"** value. This is a classic indicator that we can use **Binary Search on the Answer**.

1. **Range:** The minimum height can be at least `min(arr)` and at most `min(arr) + k` (if we pour all water on the smallest flower).
2. **Monotonicity:** If it is possible to achieve a minimum height of `H`, it is definitely possible to achieve any height less than `H`. If `H` is not possible, any height greater than `H` is also not possible.
3. **Check Function:** We need a function `isPossible(targetHeight)` that checks if we can make all flowers reach at least `targetHeight` using at most `k` days.

To implement `isPossible` efficiently (better than ), we use the **Difference Array (Sweep Line)** technique to perform range updates in .

### 🔹 Optimized Approach (Binary Search + Difference Array)

* **Binary Search:** We search for the optimal height `mid`.
* **Greedy Strategy:** Iterate through the array. If a flower at index `i` is shorter than `targetHeight`, we **must** water it. To maximize the benefit, we start a watering window of size `w` starting at `i` (covering `i` to `i+w-1`).
* **Difference Array:** Instead of updating the array elements one by one (which is slow), we maintain a `water` array. Adding `x` to range `[l, r]` is done by `water[l] += x` and `water[r+1] -= x`. We track the cumulative effect as we iterate.

#### 💻 C++ Solution

```cpp
// Intuition: Binary Search on Answer to find max min height. 
//            Use Difference Array technique for O(1) range updates during the check.
// Approach:
// 1. Define search range: low = min(arr), high = min(arr) + k.
// 2. Binary search for 'mid'. Check if 'mid' height is achievable with <= k days.
// 3. Inside isPossible:
//    - Iterate through flowers. Maintain 'currWater' via difference array.
//    - If (arr[i] + currWater) < target, calculate needed water.
//    - Apply water greedily starting at i: update diff array at i and i+w.
//    - Track total days used. If > k, return false.
// Time Complexity: O(N * log(K)) where N is array size and K is the search space size.
// Space Complexity: O(N) for the difference array.

class Solution {
public:
    // Helper function to check if targetHeight can be achieved with <= k waterings
    bool isPossible(vector<int>& arr, int k, int w, int targetHeight) {
        int n = arr.size();
        vector<int> water(n + 1, 0);  // Difference array
        int daysUsed = 0;
        int currWater = 0;

        for (int i = 0; i < n; i++) {
            currWater += water[i];  // Apply range updates starting/ending here
            int currHeight = arr[i] + currWater;

            if (currHeight < targetHeight) {
                int need = targetHeight - currHeight; // Amount to increase
                daysUsed += need;
                
                if (daysUsed > k) return false; // Exceeded budget

                // Add water effect for current window [i, i + w - 1]
                currWater += need;
                water[i] += need; 
                if (i + w <= n) {
                    water[i + w] -= need; // Remove effect after window ends
                }
            }
        }
        return true;
    }

    int maxMinHeight(vector<int>& arr, int k, int w) {
        int low = *min_element(arr.begin(), arr.end());
        int high = low + k;
        int result = low;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (isPossible(arr, k, w, mid)) {
                result = mid;      // Possible, try higher
                low = mid + 1;
            } else {
                high = mid - 1;    // Not possible, try lower
            }
        }
        return result;
    }
};

/*
* Dry Run:
* arr = [2, 3, 4, 5, 1], k=2, w=2
* Binary Search Range: [1, 3]
* Check mid = 2:
* i=0, ht=2 >= 2. OK.
* ...
* i=4, ht=1 < 2. Need 1. daysUsed=1. Water [4, 5].
* Valid. Result = 2.
* Check mid = 3:
* i=0, ht=2 < 3. Need 1. daysUsed=1. Water [0, 1].
* i=1, ht=3+(1)=4 >= 3. OK.
* ...
* i=4, ht=1 < 3. Need 2. daysUsed=1+2=3. 3 > k(2). False.
* Final Answer: 2
*/

```

#### ☕ Java Solution

```java
// Approach: Use binary search to maximize the minimum possible height. For each candidate height, check if it can be achieved by at most k waterings using a difference array for efficient range update simulation.
// Time Complexity: O(n * log k), where n is the size of arr and log k is from binary search steps.
// Space Complexity: O(n), for the water difference array.
class Solution {
    // Helper function to check if targetHeight can be achieved with <= k waterings
    private boolean isPossible(int[] arr, int k, int w, int targetHeight) {
        int n = arr.length;
        int[] water = new int[n + 1]; // Difference array for efficient range addition
        int daysUsed  = 0;
        int currWater = 0;

        for (int i = 0; i < n; i++) {
            currWater += water[i]; // Add the effect of previous waterings
            int currHeight = arr[i] + currWater;
            if (currHeight < targetHeight) {
                int need = targetHeight - currHeight; // Water needed at this point
                daysUsed += need;
                if (daysUsed > k) {                   // If exceeded allowed waterings, not possible
                    return false;
                }
                currWater += need;        // Add immediate effect
                water[i]  += need;        // Start effect at i
                if (i + w <= n) {
                    water[i + w] -= need; // End effect after window
                }
            }
        }
        return true;
    }
    
    // Main function to maximize the minimum height
    public int maxMinHeight(int[] arr, int k, int w) {
        int low = Integer.MAX_VALUE;

        for (int v : arr) {
            low = Math.min(low, v);
        }
        int high = low + k;

        int result = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (isPossible(arr, k, w, mid)) {
                result = mid;      // Try to go higher
                low    = mid + 1;
            } else {
                high = mid - 1;    // Try lower
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 2, 2, 2, 1, 1], k = 2, w = 3
 *
 * 1. Binary search: low = 1, high = 3 (since min(arr)=1, max we can reach = 1 + k = 3)
 * 2. Try mid = 2:
 *     - isPossible(arr, 2, 3, 2):
 *         i=0: currHeight = 2, no water needed.
 *         i=1: currHeight = 2, no water needed.
 *         i=2: currHeight = 2, no water needed.
 *         i=3: currHeight = 2, no water needed.
 *         i=4: currHeight = 1, need 1 water. daysUsed = 1, water[4] += 1.
 *         i=5: currWater includes water[4]=1, so currHeight = 1+1=2, no more water needed.
 *         All daysUsed = 1 <= 2. So mid=2 is possible.
 *     - Update result=2, low=3
 * 3. Try mid = 3:
 *     - isPossible(arr, 2, 3, 3):
 *         i=0: currHeight = 2, need 1 water. daysUsed = 1, water[0] += 1, water[3] -= 1.
 *         i=1: currWater=1, currHeight=3, no water needed.
 *         i=2: currWater=1, currHeight=3, no water needed.
 *         i=3: currWater+=water[3]=-1 (currWater=0), currHeight=2, need 1 water. daysUsed = 2, water[3] += 1, water[6] -= 1.
 *         i=4: currWater=1, currHeight=2, need 1 water. daysUsed = 3 (> k), return false.
 *     - mid=3 is not possible, high=2
 * 4. Loop ends. Return result=2.
 *
 */

```

---

## 🗝️ Key Insights

1. **Binary Search on Answer:** Whenever you see "Maximize the Minimum" or "Minimize the Maximum", immediately think of Binary Search. It allows us to convert an optimization problem into a decision problem (Yes/No).
2. **Greedy Window:** When checking if a height is possible, if `arr[i]` is deficient, we always water the range `[i, i + w - 1]`. Starting the window earlier (e.g., at `i-1`) provides no extra benefit for `arr[i]` but might miss coverage for `i + w - 1`. Starting later doesn't cover `arr[i]`. Thus, the greedy choice is optimal.
3. **Difference Array Optimization:** A naive simulation of watering takes  per update, leading to  check time. By using a difference array (lazy propagation idea), we update ranges in , reducing the check time to .

---

## 🔗 References

* [Problem Link (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/max-min-height--170647/1)
* [Binary Search on Answer - Tutorial](https://www.google.com/search?q=https://www.geeksforgeeks.org/binary-search-on-answer/)
* [Difference Array Technique](https://www.geeksforgeeks.org/difference-array-range-update-query-o1/)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🔖 Tags

`binary-search` `greedy` `array` `difference-array` `sliding-window` `hard`

---

## 📜 License

**⚠️ Educational Use Only:** This content is for learning purposes. Please solve problems on your own before referring to solutions.