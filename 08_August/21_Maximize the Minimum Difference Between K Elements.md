# 📏 Maximize the Minimum Difference Between K Elements

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/maximize-the-minimum-difference-between-k-elements/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=for-the-badge&logo=geeksforgeeks" alt="GFG Problem">
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty: Medium">
    <img src="https://img.shields.io/badge/Accuracy-65.42%25-brightgreen?style=for-the-badge" alt="Accuracy: 65.42%">
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4">
    <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License: MIT">
</div>

> [!CAUTION] > **Educational Use Only**: This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximize-the-minimum-difference-between-k-elements/1).

---

## 📝 Problem Statement

Given an array `arr[]` of integers and an integer `k`, select `k` elements from the array such that the **minimum** absolute difference between any two of the selected elements is **maximized**. Return this **maximum** possible **minimum** difference.

---

## Examples

### Example 1:

```
Input: arr[] = [2, 6, 2, 5], k = 3
Output: 1
Explanation:
3 elements out of 4 elements are to be selected with a minimum difference as large as possible.
- Selecting {2, 2, 5} will result in a minimum difference of 0.
- Selecting {2, 5, 6} will result in a minimum difference of 1 (6 - 5 = 1).
The maximum possible minimum difference is 1.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>
<div>

Let's break down the first example: `arr[] = [2, 6, 2, 5], k = 3`.

1.  **Goal**: We need to pick 3 elements from the array to maximize the smallest gap between any two chosen elements.
2.  **Sort the Array**: To easily calculate differences, let's sort the array first.
    `arr` becomes `[2, 2, 5, 6]`.
3.  **Possible Selections of 3 elements**:
    - `{2, 2, 5}` -> Differences are `(2-2)=0`, `(5-2)=3`. The minimum difference is **0**.
    - `{2, 2, 6}` -> Differences are `(2-2)=0`, `(6-2)=4`. The minimum difference is **0**.
    - `{2, 5, 6}` -> Differences are `(5-2)=3`, `(6-5)=1`. The minimum difference is **1**.
    - `{2, 5, 6}` -> (Using the other '2') Same as above. The minimum difference is **1**.
4.  **Compare Minimums**: The minimum differences we found are `0` and `1`.
5.  **Maximize the Minimum**: The largest of these minimums is **1**.

Therefore, the output is `1`. The core idea is to find the best possible arrangement (`{2, 5, 6}`) that keeps the elements as far apart as possible, maximizing the smallest gap.

</div>
</details>

### Example 2:

```
Input: arr[] = [1, 4, 9, 0, 2, 13, 3], k = 4
Output: 4
Explanation:
Selecting {0, 4, 9, 13} will result in a minimum difference of 4 (4-0=4, 9-4=5, 13-9=4), which is the largest minimum difference possible.
```

---

## ⛓️ Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `0 ≤ arr[i] ≤ 10^6`
- `2 ≤ k ≤ arr.size()`

---

## 💡 Solution Approaches

### Optimized Approach: Binary Search on the Answer

The problem asks us to "maximize the minimum," which is a strong indicator that we can use **Binary Search on the Answer**.

The core idea is to guess a potential minimum difference (`mid`) and then check if it's possible to select `k` elements from the array, all having at least this `mid` difference.

- If it's **possible** to achieve a minimum difference of `mid`, it means we might be able to do even better. So, we try for a larger difference (`low = mid + 1`).
- If it's **not possible**, our guess `mid` was too ambitious. We need to try a smaller difference (`high = mid - 1`).

This check is possible because of the monotonic nature of the problem: if we can place `k` elements with a minimum distance `d`, we can definitely place them with any distance smaller than `d`. This allows binary search to work efficiently.

#### C++ Solution

```cpp
// Intuition: The problem asks to "maximize the minimum difference," which is a classic pattern for Binary Search on the Answer. We can guess a potential minimum difference and then check if it's feasible to select 'k' elements with that difference.
// Approach:
// 1. Sort the input array. This helps in greedily picking elements.
// 2. Define a search space for the answer. The minimum possible difference is 0, and the maximum is `arr.back() - arr.front()`.
// 3. Apply binary search on this range. For each `mid` value (our guessed minimum difference):
//    a. Use a helper function `isPossible` to check if we can select 'k' elements such that the difference between any two consecutive elements is at least `mid`.
//    b. The check is done greedily: pick the first element, then iterate through the array and pick the next element that is at least `mid` distance away from the previously picked one.
// 4. If `isPossible(mid)` is true, it means `mid` is a valid minimum difference. We store it and try for a larger difference (i.e., `low = mid + 1`).
// 5. If it's false, `mid` is too large, so we reduce our search space (`high = mid - 1`).
// 6. The final stored answer will be the maximum possible minimum difference.
// Time Complexity: O(N log(max_diff)), where N is the number of elements and max_diff is the difference between the maximum and minimum elements in the array. Sorting takes O(N log N), and the binary search performs log(max_diff) iterations, with each `isPossible` check taking O(N).
// Space Complexity: O(1), as we are not using any extra space proportional to the input size (sorting might take O(log N) for recursion stack, but is often considered in-place).

class Solution {
  public:
    // Helper function to check if it's possible to place 'k' elements
    // with a minimum difference of at least 'mid'.
    bool isPossible(vector<int>& arr, int k, int mid){
        int count = 1;      // We always place the first element.
        int last = arr[0];  // Position of the last placed element.

        // Greedily check for the next valid position.
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] - last >= mid) { // If the gap is sufficient
                count++;            // Place another element.
                last = arr[i];      // Update the last placed position.
            }
            if (count == k) {       // If we have placed 'k' elements
                return true;        // It's possible.
            }
        }

        return false; // Not possible to place 'k' elements.
    }

    int maxMinDiff(vector<int>& arr, int k){
        // Sort the array to easily find differences.
        sort(arr.begin(), arr.end());

        // Define the binary search range for the answer.
        int low = 0; // Minimum possible difference
        int high = arr.back() - arr.front(); // Maximum possible difference
        int answer = 0;

        // Binary search to find the maximum valid minimum difference.
        while (low <= high) {
            int mid = low + (high - low) / 2; // Avoid potential overflow

            // Check if a difference of 'mid' is achievable.
            if (isPossible(arr, k, mid)) {
                answer = mid;       // 'mid' is a possible answer, store it.
                low = mid + 1;      // Try for a larger minimum difference.
            } else {
                high = mid - 1;     // 'mid' is too large, try a smaller one.
            }
        }

        // Return the maximum feasible minimum difference found.
        return answer;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [2, 6, 2, 5], k = 3
*
* 1. sort(arr) -> arr = [2, 2, 5, 6]
*
* 2. Binary Search Setup:
* low = 0
* high = 6 - 2 = 4
* answer = 0
*
* 3. Iteration 1:
* mid = (0 + 4) / 2 = 2
* isPossible(arr, 3, 2):
* - Place at arr[0] = 2. count = 1, last = 2.
* - arr[1]=2, 2-2 < 2.
* - arr[2]=5, 5-2 >= 2. Place at 5. count = 2, last = 5.
* - arr[3]=6, 6-5 < 2.
* - End of loop. count = 2. Returns false.
* isPossible is false, so high = mid - 1 = 1.
*
* 4. Iteration 2:
* low = 0, high = 1
* mid = (0 + 1) / 2 = 0
* isPossible(arr, 3, 0):
* - Place at arr[0] = 2. count = 1, last = 2.
* - arr[1]=2, 2-2 >= 0. Place at 2. count = 2, last = 2.
* - arr[2]=5, 5-2 >= 0. Place at 5. count = 3. Returns true.
* isPossible is true, so answer = 0, low = mid + 1 = 1.
*
* 5. Iteration 3:
* low = 1, high = 1
* mid = (1 + 1) / 2 = 1
* isPossible(arr, 3, 1):
* - Place at arr[0] = 2. count = 1, last = 2.
* - arr[1]=2, 2-2 < 1.
* - arr[2]=5, 5-2 >= 1. Place at 5. count = 2, last = 5.
* - arr[3]=6, 6-5 >= 1. Place at 6. count = 3. Returns true.
* isPossible is true, so answer = 1, low = mid + 1 = 2.
*
* 6. Loop ends because low (2) > high (1).
*
* 7. Final Answer: 1
*
*/
```

#### Java Solution

```java
// Intuition: This problem fits the "maximize the minimum" pattern, making it a perfect candidate for Binary Search on the Answer. The idea is to binary search for the maximum possible minimum difference.
// Approach:
// 1. Sort the array. This allows us to greedily pick elements that are spaced out.
// 2. Set up a search range for the answer. The lowest possible difference is 0, and the highest is `arr[n-1] - arr[0]`.
// 3. In each step of the binary search, we take a `mid` value and check if it's possible to select 'k' elements with at least `mid` difference between them using a helper `isPossible` function.
// 4. The `isPossible` function works greedily. It always selects the first element. Then, it iterates through the sorted array, selecting the next element only if its distance from the previously selected element is `mid` or greater.
// 5. If `isPossible(mid)` returns true, it means `mid` is a potential answer, so we store it and search for a larger difference in the upper half (`low = mid + 1`).
// 6. If it returns false, `mid` is too large, and we need to search for a smaller difference in the lower half (`high = mid - 1`).
// 7. The loop continues until `low` crosses `high`, and the last successfully stored `mid` is our answer.
// Time Complexity: O(N log(max_diff)), dominated by sorting O(N log N) and binary search O(N * log(max_diff)).
// Space Complexity: O(1) (or O(log N) for recursion stack in sorting).

class Solution {
    // Checks if it's possible to pick k elements with at least 'mid' difference.
    static boolean isPossible(int[] arr, int k, int mid) {
        int count = 1;      // Start by placing the first element.
        int last = arr[0];  // Keep track of the last element's value.

        // Iterate through the array to find the next valid element to place.
        for (int i = 1; i < arr.length; i++) {
            // If the current element is far enough from the last one.
            if (arr[i] - last >= mid) {
                count++;        // Increment the count of placed elements.
                last = arr[i];  // Update the last placed element.
            }
            // If we have successfully placed k elements.
            if (count == k) {
                return true;
            }
        }

        // If the loop finishes and we haven't placed k elements, it's not possible.
        return false;
    }

    static int maxMinDiff(int[] arr, int k) {
        // Sort the array to apply the greedy strategy.
        Arrays.sort(arr);

        // Define the binary search range for the answer.
        int low = 0;
        int high = arr[arr.length - 1] - arr[0];
        int answer = 0;

        // Binary search to find the maximum valid minimum difference.
        while (low <= high) {
            int mid = low + (high - low) / 2;

            // If a 'mid' difference is possible, it's a potential answer.
            if (isPossible(arr, k, mid)) {
                answer = mid;       // Store this valid answer.
                low = mid + 1;      // Try for an even larger difference.
            } else {
                high = mid - 1;     // The guessed difference is too large.
            }
        }

        // Return the maximum feasible minimum difference.
        return answer;
    }
}

/*
*
* Dry Run
*
* Input: arr[] = [1, 4, 9, 0, 2, 13, 3], k = 4
*
* 1. Arrays.sort(arr) -> arr = [0, 1, 2, 3, 4, 9, 13]
*
* 2. Binary Search Setup:
* low = 0
* high = 13 - 0 = 13
* answer = 0
*
* 3. Iteration 1:
* mid = (0 + 13) / 2 = 6
* isPossible(arr, 4, 6):
* - Place at 0. count = 1, last = 0.
* - Place at 9 (9-0 >= 6). count = 2, last = 9.
* - Cannot place more. Returns false.
* isPossible is false, so high = mid - 1 = 5.
*
* 4. Iteration 2:
* low = 0, high = 5
* mid = (0 + 5) / 2 = 2
* isPossible(arr, 4, 2):
* - Place at 0. count=1, last=0.
* - Place at 2 (2-0 >= 2). count=2, last=2.
* - Place at 4 (4-2 >= 2). count=3, last=4.
* - Place at 9 (9-4 >= 2). count=4. Returns true.
* isPossible is true, so answer = 2, low = mid + 1 = 3.
*
* 5. Iteration 3:
* low = 3, high = 5
* mid = (3 + 5) / 2 = 4
* isPossible(arr, 4, 4):
* - Place at 0. count=1, last=0.
* - Place at 4 (4-0 >= 4). count=2, last=4.
* - Place at 9 (9-4 >= 4). count=3, last=9.
* - Place at 13 (13-9 >= 4). count=4. Returns true.
* isPossible is true, so answer = 4, low = mid + 1 = 5.
*
* 6. Iteration 4:
* low = 5, high = 5
* mid = (5 + 5) / 2 = 5
* isPossible(arr, 4, 5):
* - Place at 0. count=1, last=0.
* - Place at 9 (9-0 >= 5). count=2, last=9.
* - Cannot place more. Returns false.
* isPossible is false, so high = mid - 1 = 4.
*
* 7. Loop ends because low (5) > high (4).
*
* 8. Final Answer: 4
*
*/
```

---

## 🚀 Key Insights

- **Monotonic Search Space**: The core of this problem is recognizing the monotonic property of the `isPossible(d)` function. If you can select `k` elements with a minimum difference of `d`, you can also do it for any difference less than `d`. This allows the "Binary Search on Answer" technique to be applied.
- **Greedy Choice**: After sorting the array, the check (`isPossible`) can be performed greedily. By always picking the first available element that satisfies the minimum difference constraint, you maximize your chances of fitting the remaining `k-1` elements.

---

## 🕵️‍♂️ Further Exploration

This problem is a variation of a classic competitive programming problem often called "Aggressive Cows." Understanding this pattern opens the door to solving many similar problems.

- [**Aggressive Cows (SPOJ)**](https://www.spoj.com/problems/AGGRCOW/): The canonical version of this problem.
- [**Allocate Minimum Number of Pages (GFG)**](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1): Another "minimize the maximum" problem solved with binary search on the answer.
- [**Split Array Largest Sum (LeetCode)**](https://leetcode.com/problems/split-array-largest-sum/): Similar logic where you binary search for the minimum possible value of the largest sum.
- [**Koko Eating Bananas (LeetCode)**](https://leetcode.com/problems/koko-eating-bananas/): Binary search for the minimum eating speed (k).

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/maximize-the-minimum-difference-between-k-elements/1)
- [Article on Binary Search on Answer](https://www.geeksforgeeks.org/binary-search-on-answer-the-cow-problem/)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/your-username)

---

## 🏷️ Tags

<div align="center">
    <img src="https://img.shields.io/badge/binary search-20232A?style=for-the-badge" alt="Binary Search">
    <img src="https://img.shields.io/badge/array-20232A?style=for-the-badge" alt="Array">
    <img src="https://img.shields.io/badge/sorting-20232A?style=for-the-badge" alt="Sorting">
    <img src="https://img.shields.io/badge/geeksforgeeks-20232A?style=for-the-badge" alt="GeeksforGeeks">
    <img src="https://img.shields.io/badge/gfg potd-20232A?style=for-the-badge" alt="GFG POTD">
</div>

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

> **Note**: The solutions are provided for educational purposes and are not intended for any commercial use. They are meant to help users learn and practice data structures and algorithms.
