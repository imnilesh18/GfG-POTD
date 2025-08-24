# 💐 Minimum days to make M bouquets

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-46.85%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/minimum-days-to-make-m-bouquets/1).

</div>

---

## 📄 Problem Statement

You have a row of flowers, where each flower blooms after a specific day. The array `arr[]` represents the blooming schedule: `arr[i]` is the day the flower at position `i` will bloom. To create a bouquet, you need to collect `k` **adjacent** bloomed flowers. Each flower can only be used in one bouquet.

Your goal is to find the **minimum** number of days required to make exactly `m` bouquets. If it is not possible to make `m` bouquets with the given arrangement, return `-1`.

---

## 📖 Examples

### Example 1

```
Input: m = 3, k = 2, arr[] = [3, 4, 2, 7, 13, 8, 5]
Output: 8
Explanation:
We need 3 bouquets, and each bouquet should have 2 flowers.
- After day 2: [_, _, x, _, _, _, _]
- After day 5: [x, x, x, _, _, _, x]
- After day 8: [x, x, x, x, _, x, x] (bloomed flowers are at indices where arr[i] <= 8)
On day 8, we can form bouquets from:
- Flowers at indices {0, 1} (bloom days 3, 4)
- Flowers at indices {2, 3} (bloom days 2, 7)
- Flowers at indices {5, 6} (bloom days 8, 5)
Thus, we can make 3 bouquets. This is the minimum day to achieve this.
```

<details>
<summary>📖 Example 1 Breakdown</summary>

- **Goal**: Make `m = 3` bouquets, each with `k = 2` adjacent flowers.
- **Bloom Days**: `[3, 4, 2, 7, 13, 8, 5]`
- **Observation**: The problem asks for the _minimum_ number of days. This hints at a search problem. If we can make the bouquets in `D` days, we can surely make them in `D+1` days. This monotonic property is a perfect fit for **Binary Search on the Answer**.

- **Search Space**: The minimum possible day is `min(arr) = 2` and the maximum is `max(arr) = 13`. So, we can search for the answer in the range `[2, 13]`.

- **Binary Search Simulation**:

  - `low = 2`, `high = 13`. `mid = (2+13)/2 = 7`.
  - **Check for Day 7**: Can we make 3 bouquets?

    - Bloomed flowers are those with bloom day <= 7: `[3, 4, 2, 7, _, _, 5]`.
    - Flower states: `[Bloomed, Bloomed, Bloomed, Bloomed, Not, Not, Bloomed]`
    - We find a block of 4 adjacent bloomed flowers at the start. We can make `4 / k = 4 / 2 = 2` bouquets.
    - Total bouquets = 2, which is less than `m = 3`. So, day 7 is not enough. We need more days.
    - `low = mid + 1 = 8`.

  - `low = 8`, `high = 13`. `mid = (8+13)/2 = 10`.
  - **Check for Day 10**:

    - Bloomed flowers (day <= 10): `[3, 4, 2, 7, _, 8, 5]`.
    - Flower states: `[B, B, B, B, N, B, B]`
    - Block 1 (indices 0-3): 4 flowers -> `4/2 = 2` bouquets.
    - Block 2 (indices 5-6): 2 flowers -> `2/2 = 1` bouquet.
    - Total bouquets = 2 + 1 = 3. This is possible! Since we want the _minimum_ day, we store `10` as a potential answer and try for fewer days.
    - `ans = 10`, `high = mid - 1 = 9`.

  - `low = 8`, `high = 9`. `mid = (8+9)/2 = 8`.
  - **Check for Day 8**:

    - Bloomed flowers (day <= 8): `[3, 4, 2, 7, _, 8, 5]`.
    - Flower states: `[B, B, B, B, N, B, B]`
    - This is the same state as day 10. We can make 3 bouquets.
    - `ans = 8`, `high = mid - 1 = 7`.

  - `low = 8`, `high = 7`. The loop terminates because `low > high`.

- **Result**: The minimum day found is **8**.
</details>

### Example 2

```
Input: m = 2, k = 3, arr[] = [5, 5, 5, 5, 10, 5, 5]
Output: 10
Explanation:
We need 2 bouquets, each with 3 flowers.
- After day 5: [x, x, x, x, _, x, x]. We can make one bouquet from the first three flowers, but not another.
- After day 10: [x, x, x, x, x, x, x]. Now we can make two bouquets.
```

### Example 3

```
Input: m = 3, k = 2, arr[] = [1, 10, 3, 10, 2]
Output: -1
Explanation:
We need 3 bouquets of 2 flowers each, which means we need a total of `3 * 2 = 6` flowers. However, the array only has 5 flowers, so it's impossible.
```

---

## ⛓️ Constraints

```
1 ≤ k ≤ arr.size() ≤ 10^5
1 ≤ m ≤ 10^5
1 ≤ arr[i] ≤ 10^9
```

---

## 💡 Solution Approaches

### 1. Brute-Force Approach

The most straightforward way is to check every possible day, starting from day 1 up to the maximum bloom day in the array. For each day, we can iterate through the `arr` and count how many bouquets can be formed. The first day that allows us to form `m` bouquets is our answer.

- **Intuition**: Linearly check each day.
- **Time Complexity**: `O(max(arr) * N)`, where N is the number of flowers. This is too slow given the constraint `arr[i] ≤ 10^9` and will result in a Time Limit Exceeded (TLE) error.
- **Space Complexity**: `O(1)`.

### 2. Optimized Approach (Binary Search)

The problem asks for the **minimum** number of days. If we can make `m` bouquets in `D` days, we can also make them in `D+1` days. This monotonic relationship allows us to use **Binary Search on the Answer** (the number of days).

The search space for the days will range from `1` to the maximum bloom day in the array. For each `mid` day in our binary search, we check if it's possible to make `m` bouquets. If it is, we try to find a smaller number of days; otherwise, we need more days.

#### C++ Solution

```cpp
// Intuition: The problem has a monotonic property. If we can make 'm' bouquets in 'd' days, we can also do it in 'd+1' days. This allows us to binary search for the minimum number of days.
// Approach:
// 1. Define a search space for days from low = 0 to high = max element in arr.
// 2. Use a helper function `check(days)` to determine if it's possible to make 'm' bouquets within a given number of days.
// 3. In `check(days)`, iterate through the flowers. If a flower at arr[i] blooms on or before 'days', increment a counter for adjacent bloomed flowers.
// 4. When a flower is not bloomed (arr[i] > days), calculate how many bouquets can be formed from the current adjacent count (`cnt / k`) and reset the counter.
// 5. If `check(mid)` is true, it means 'mid' is a possible answer, so we try for a smaller day (`hi = mid - 1`) and store `mid`.
// 6. If false, we need more days, so we search in the upper half (`lo = mid + 1`).
// 7. The minimal day found is the result. If the total required flowers (m * k) is more than available, return -1 upfront.
// Time Complexity: O(N * log(max(arr))), where N is the size of the array. The binary search takes log(max(arr)) steps, and each step involves a linear scan of the array (O(N)).
// Space Complexity: O(1), as no extra space proportional to the input is used.

class Solution {
  public:
    // function to check if the given number of days is valid for creating bouquets
    bool check(vector<int>& arr, int k, int m, int days) {
        int bouquets = 0; // Number of bouquets formed
        int cnt = 0;      // Consecutive bloomed flowers counter

        // Iterate through the bloom days of the flowers
        for (int i = 0; i < arr.size(); i++) {
            // If the flower has bloomed by the given 'days'
            if (arr[i] <= days) {
                cnt += 1; // Increment adjacent flower count
            } else {
                // This flower hasn't bloomed, breaking the adjacent streak
                bouquets += cnt / k; // Calculate bouquets from the previous streak
                cnt = 0;             // Reset the counter
            }
        }

        // Add any bouquets from the last streak of adjacent flowers
        bouquets += cnt / k;

        // Return true if we could form at least 'm' bouquets
        return bouquets >= m;
    }

    // function to find the minimum number of days needed to create m bouquets
    int minDaysBloom(vector<int>& arr, int k, int m) {
        // Edge case: if total flowers needed is more than available
        if ((long long)m * k > arr.size()) {
            return -1;
        }

        int lo = 0; // Minimum possible day
        int hi = *max_element(arr.begin(), arr.end()); // Maximum possible day
        int res = -1; // Stores the minimum valid day found

        // Binary search on the number of days
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2; // Avoid potential overflow

            // Check if it's possible to make 'm' bouquets in 'mid' days
            if (check(arr, k, m, mid)) {
                res = mid;      // 'mid' is a valid day, store it
                hi = mid - 1;   // Try to find a smaller valid day
            } else {
                lo = mid + 1;   // Need more days, search in the right half
            }
        }
        return res;
    }
};

/*
*
* Dry Run
* Input: m = 3, k = 2, arr[] = [3, 4, 2, 7, 13, 8, 5]
*
* Initial call: minDaysBloom(arr, 2, 3)
* lo = 0, hi = 13, res = -1
*
* Iteration 1:
* mid = (0 + 13) / 2 = 6
* check(arr, 2, 3, 6):
* - flowers bloomed by day 6: [3, 4, 2, _, _, _, 5]
* - i=0, arr[0]<=6 -> cnt=1
* - i=1, arr[1]<=6 -> cnt=2
* - i=2, arr[2]<=6 -> cnt=3
* - i=3, arr[3]>6 -> bouquets+=3/2=1, cnt=0
* - i=4, arr[4]>6 -> bouquets+=0/2=0, cnt=0
* - i=5, arr[5]>6 -> bouquets+=0/2=0, cnt=0
* - i=6, arr[6]<=6 -> cnt=1
* - end loop, bouquets+=1/2=0. Total bouquets = 1.
* check(6) returns false.
* lo = mid + 1 = 7.
*
* Iteration 2:
* mid = (7 + 13) / 2 = 10
* check(10) is true (we can make 3 bouquets)
* res = 10, hi = 9.
*
* Iteration 3:
* mid = (7 + 9) / 2 = 8
* check(8) is true (we can make 3 bouquets)
* res = 8, hi = 7.
*
* Iteration 4:
* mid = (7 + 7) / 2 = 7
* check(7) is false (we can make only 2 bouquets)
* lo = mid + 1 = 8.
*
* Iteration 5:
* lo = 8, hi = 7. Loop terminates.
*
* Return res = 8.
*
*/
```

#### Java Solution

```java
// Intuition: The problem can be solved by searching for the answer. Since the possibility of making 'm' bouquets increases with the number of days, the problem has a monotonic nature. This makes binary search an ideal approach for finding the minimum required days.
// Approach:
// 1. Set up a binary search range for the number of days. The lower bound `lo` is 0, and the upper bound `hi` is the maximum bloom day in the array.
// 2. In each step of the binary search, calculate `mid` and use a helper function `check(mid)` to verify if `m` bouquets can be formed within `mid` days.
// 3. The `check(days)` function iterates through the garden, counting consecutive flowers that have bloomed by the given day. When a sequence of `k` bloomed flowers is found, a bouquet is counted.
// 4. If `check(mid)` returns true, `mid` is a potential answer. We then try to find an even smaller number of days by setting `hi = mid - 1`.
// 5. If `check(mid)` returns false, we need more time for flowers to bloom, so we set `lo = mid + 1`.
// 6. An initial check ensures that there are enough flowers in total (`m * k <= arr.length`); if not, it's impossible, and we return -1.
// Time Complexity: O(N * log(max(arr))), where N is the length of the array. The binary search performs log(max(arr)) iterations, and each involves a linear scan of the array by the `check` function.
// Space Complexity: O(1), as the algorithm uses a constant amount of extra space.

class Solution {
    static boolean check(int[] arr, int k, int m, int days) {
        int bouquets = 0; // Tracks the number of bouquets made
        int cnt = 0;      // Counts consecutive bloomed flowers

        // Iterate through the bloom days of the flowers
        for (int i = 0; i < arr.length; i++) {
            // Check if the current flower has bloomed by the given day
            if (arr[i] <= days) {
                cnt += 1; // Increment the counter for adjacent bloomed flowers
            } else {
                // The streak of adjacent bloomed flowers is broken
                bouquets += cnt / k; // Add bouquets from the completed streak
                cnt = 0;             // Reset the counter
            }
        }
        // After the loop, account for the last streak of flowers
        bouquets += cnt / k;

        // Return true if we have formed at least 'm' bouquets
        return bouquets >= m;
    }

    static int minDaysBloom(int[] arr, int k, int m) {
        // Early exit if the total number of flowers required is impossible to get
        if ((long) m * k > arr.length) {
            return -1;
        }

        int lo = 0; // Lower bound of our search space for days
        int hi = 0; // Upper bound
        for(int day : arr) {
            hi = Math.max(hi, day);
        }

        int res = -1; // Stores the minimum days found so far

        // Perform binary search on the answer (number of days)
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2; // Calculate the middle day

            // If it's possible to make 'm' bouquets in 'mid' days
            if (check(arr, k, m, mid)) {
                res = mid;      // 'mid' is a valid answer
                hi = mid - 1;   // Try for an even smaller number of days
            } else {
                // Not possible, need more days
                lo = mid + 1;
            }
        }
        return res;
    }
}
/*
*
* Dry Run
* Input: m = 2, k = 3, arr[] = [5, 5, 5, 5, 10, 5, 5]
*
* Initial call: minDaysBloom(arr, 3, 2)
* lo = 0, hi = 10, res = -1
*
* Iteration 1:
* mid = (0 + 10) / 2 = 5
* check(arr, 3, 2, 5):
* - flowers bloomed by day 5: [5, 5, 5, 5, _, 5, 5]
* - i=0, arr[0]<=5 -> cnt=1
* - i=1, arr[1]<=5 -> cnt=2
* - i=2, arr[2]<=5 -> cnt=3 -> bouquets+=3/3=1, cnt=0
* - i=3, arr[3]<=5 -> cnt=1
* - i=4, arr[4]>5 -> bouquets+=1/3=0, cnt=0
* - i=5, arr[5]<=5 -> cnt=1
* - i=6, arr[6]<=5 -> cnt=2
* - end loop, bouquets+=2/3=0. Total bouquets = 1.
* check(5) returns false.
* lo = mid + 1 = 6.
*
* Iteration 2:
* mid = (6 + 10) / 2 = 8
* check(8) is false (same as day 5, total bouquets = 1).
* lo = mid + 1 = 9.
*
* Iteration 3:
* mid = (9 + 10) / 2 = 9
* check(9) is false (same as day 5, total bouquets = 1).
* lo = mid + 1 = 10.
*
* Iteration 4:
* mid = (10 + 10) / 2 = 10
* check(10) is true (all flowers bloom, we can make 7/3 = 2 bouquets).
* res = 10, hi = 9.
*
* Iteration 5:
* lo = 10, hi = 9. Loop terminates.
*
* Return res = 10.
*
*/
```

---

## 🔑 Key Insights

- The core idea is that the feasibility of creating `m` bouquets is a **monotonic function** of the number of days. This means if it's possible on day `D`, it's also possible for all days `D' > D`.
- This monotonic property makes the problem searchable. Instead of checking every day one by one (which is inefficient), we can use **binary search** to find the minimum required day in logarithmic time complexity relative to the search space.
- The `check` function is the workhorse of the solution. It efficiently verifies, for a given day, whether the condition of making `m` bouquets can be met. This involves a single pass through the array.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might also like these related GFG problems that use the "Binary Search on Answer" technique:

- [**Allocate minimum number of pages**](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1)
- [**The Painter's Partition Problem**](https://www.geeksforgeeks.org/problems/the-painters-partition-problem1535/1)
- [**Aggressive Cows**](https://www.geeksforgeeks.org/problems/aggressive-cows/1)
- [**Koko Eating Bananas**](https://www.geeksforgeeks.org/problems/koko-eating-bananas/1)

---

## 🔗 References

- **Original Problem**: [GeeksforGeeks | Minimum days to make M bouquets](https://www.geeksforgeeks.org/problems/minimum-days-to-make-m-bouquets/1)

---

## 👨‍💻 Author

- **Connect with me**: [imnilesh18](https://github.com/imnilesh18)

---

## #️⃣ Tags

`binary-search` `arrays` `geeksforgeeks` `dsa`

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder**: The solutions and content in this repository are for educational purposes only. They are meant to help you learn and practice data structures and algorithms.
