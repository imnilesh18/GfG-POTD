# Maximize median after doing k addition operation

<div align="center">

<a href="https://www.geeksforgeeks.org/problems/maximize-median-after-doing-k-addition-operation/1"><img src="https://img.shields.io/badge/GeeksforGeeks-2962FF?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG"></a>
<img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge" alt="Difficulty">
<img src="https://img.shields.io/badge/Accuracy-19.99%25-red.svg?style=for-the-badge" alt="Accuracy">
<img src="https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge" alt="Points">
<img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License">

</div>

---

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/maximize-median-after-doing-k-addition-operation/1).

## 📝 Problem Statement

Given an array `arr[]` consisting of positive integers and an integer `k`. You are allowed to perform **at most k operations**, where in each operation, you can **increment** any one element of the array by **1**.

Determine the **maximum possible median** of the array that can be achieved after performing at most `k` such operations.

---

## 📖 Examples

### Example 1

```
Input: arr[] = [1, 3, 4, 5], k = 3
Output: 5
Explanation: We can add +2 to the second element and +1 to the third element to get the array [1, 5, 5, 5]. After sorting, the array remains [1, 5, 5, 5]. Since the length is even, the median is (5 + 5) / 2 = 5.
```

### Example 2

```
Input: arr[] = [1, 3, 6, 4, 2], k = 10
Output: 7
Explanation: After applying operations optimally, we can transform the array to [1, 3, 7, 7, 7] (one possible way). The sorted array becomes [1, 3, 7, 7, 7]. Since the length is odd, the median is the middle element 7.
```

<details>
<summary>📖 Test Case Breakdown</summary>

Let's walk through the failing test case: `arr[] = [4, 6, 10, 10, 4, 10]`, `k = 2`.

1.  **Sort the Array**: The sorted array is `[4, 4, 6, 10, 10, 10]`.
2.  **Identify Median Elements**: The length `n = 6` (even). The median elements are `arr[n/2 - 1]` and `arr[n/2]`, which are `arr[2] = 6` and `arr[3] = 10`. The initial median is `(6 + 10) / 2 = 8`.
3.  **Goal**: Maximize the median using at most `k=2` operations.
4.  **Binary Search for the Answer**: Let's check if we can achieve a median of `9`.
5.  **Check `isPossible(9)`**:
    - `n=6`, `target=9`, `k=2`.
    - The code enters the `else` block for an even-sized array.
    - The two middle elements are `arr[2]=6` and `arr[3]=10`.
    - Since `arr[3]=10` is greater than `target=9`, the `else` condition `(arr[n / 2] <= target)` is false.
    - The code calculates the cost as `k -= (2 * target - (arr[n / 2] + arr[n / 2 - 1]))`.
    - `cost = 2 * 9 - (10 + 6) = 18 - 16 = 2`.
    - `k` becomes `k - 2`, which is `2 - 2 = 0`.
    - The loop for `i = n/2 + 1` to `n` checks `arr[4]` and `arr[5]`. Both are `10`, which are not less than `target=9`. The loop does nothing.
    - The function returns `k >= 0` (`0 >= 0`), which is `true`.
6.  **Conclusion**: It is possible to achieve a median of `9`. Let's check `10`.
7.  **Check `isPossible(10)`**:
    - `target=10`.
    - The `if (arr[n / 2] <= target)` condition is `true` since `10 <= 10`.
    - `k -= (10 - arr[3])` which is `k -= (10-10) = 0`. `k` is now `2`.
    - `k -= (10 - arr[2])` which is `k -= (10-6) = 4`. `k` becomes `2 - 4 = -2`.
    - The function returns `k >= 0` (`-2 >= 0`), which is `false`.
8.  **Final Answer**: The binary search will correctly conclude that the maximum possible median is `9`.

</details>

---

## ⛓️ Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `0 ≤ arr[i], k ≤ 10^9`

---

## 💡 Solution Approaches

### C++ Solution

```cpp
// Intuition: The problem has a monotonic property: if a median 'm' is achievable, any median less than 'm' is also achievable. This allows us to binary search for the maximum possible median on the answer space.
// Approach:
// 1. Sort the array to easily work with the median element(s).
// 2. Define a search space for the binary search. The lower bound is the initial median, and a safe upper bound is `initial_median + k`.
// 3. For each `mid` value (our target median) in the binary search, call a helper function `isPossible`.
// 4. `isPossible` calculates the minimum operations needed. To raise the median, we only need to increment elements from the median position to the right.
// 5. For an odd-sized array, it sums the costs to raise each element in the right half to the target.
// 6. For an even-sized array, it specifically calculates the cost for the two middle elements and then the rest of the right half.
// 7. If `isPossible` returns true, we try for a higher median (`low = mid + 1`); otherwise, we search for a smaller one (`high = mid - 1`).
// Time Complexity: O(N*log(K)), where N is the array size. Sorting takes O(N log N). The binary search performs log(K) iterations, and each `isPossible` check takes O(N).
// Space Complexity: O(1), as we use a constant amount of extra space (sorting can take O(log N) or O(N) depending on implementation).
class Solution {
  public:
    // check if we can make the median at least
    // 'target' using at most 'k' operation
    bool isPossible(vector<int>& arr, int target, int k){
        int n = arr.size(); // Get array size.

        if (n % 2 == 1) {
            // for odd-sized array, consider elements from
            // middle to end
            for (int i = n / 2; i < n; ++i) { // Iterate from the single median element.
                if (arr[i] < target)
                    k -= (target - arr[i]); // Subtract cost to raise element to target.
            }
        }
        else {
            // for even-sized array, handle two middle
            // elements separately
            if (arr[n / 2] <= target) { // If the higher middle element is not already above target.
                k -= (target - arr[n / 2]); // Cost for the higher middle element.
                k -= (target - arr[n / 2 - 1]); // Cost for the lower middle element.
            }
            else {
                // This case handles when the higher middle element is already >= target.
                // The cost is the total needed for both to average to target.
                k -= (2LL * target -
                           (arr[n / 2] + arr[n / 2 - 1]));
            }
            // process remaining elements to the right
            for (int i = n / 2 + 1; i < n; ++i) { // Iterate over the rest of the right half.
                if (arr[i] < target)
                    k -= (target - arr[i]); // Subtract cost to raise them to target.
            }
        }

        return k >= 0; // Return true if operations were sufficient.
    }

    // function to compute maximum achievable median
    // with given k operation
    int maximizeMedian(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end()); // Sort the array to find the median.

        // compute initial median floor if even length
        int iniMedian = arr[n / 2];
        if (n % 2 == 0) {
            iniMedian += arr[n / 2 - 1];
            iniMedian /= 2;
        }

        int low = iniMedian, high = iniMedian + k; // Define search space.
        int bestMedian = iniMedian; // Initialize best median found so far.

        // binary search to find maximum
        // achievable median
        while (low <= high) {
            long long mid = low + (high - low) / 2; // Use long long for mid to prevent overflow.

            if (isPossible(arr, mid, k)) {
                bestMedian = mid; // If 'mid' is possible, store it.
                low = mid + 1;    // Try for a higher median.
            }
            else {
                high = mid - 1;   // If 'mid' is not possible, try a lower one.
            }
        }

        return bestMedian;
    }
};

/*
*
* Dry Run
* arr = [4, 6, 10, 10, 4, 10], k = 2
*
* 1. sort(arr) -> arr is now [4, 4, 6, 10, 10, 10]
* 2. n = 6. iniMedian = (arr[2] + arr[3]) / 2 = (6 + 10) / 2 = 8.
* 3. Set binary search range: low = 8, high = 8 + 2 = 10. bestMedian = 8.
*
* --- Iteration 1 ---
* mid = 8 + (10 - 8) / 2 = 9.
* isPossible(arr, 9, 2):
* n=6 (even).
* arr[3] (10) > target (9). The 'if' is false, enter 'else'.
* k -= (2 * 9 - (10 + 6))  => k -= (18 - 16) => k -= 2. k is now 0.
* Loop for i > n/2 does nothing.
* Returns k >= 0 (true).
* Result: isPossible is true. bestMedian = 9, low = 9 + 1 = 10.
*
* --- Iteration 2 ---
* mid = 10 + (10 - 10) / 2 = 10.
* isPossible(arr, 10, 2):
* n=6 (even).
* arr[3] (10) <= target (10). The 'if' is true.
* k -= (10 - arr[3]) => k -= 0. k is 2.
* k -= (10 - arr[2]) => k -= (10 - 6) => k -= 4. k is now -2.
* Returns k >= 0 (false).
* Result: isPossible is false. high = 10 - 1 = 9.
*
* Loop terminates as low (10) > high (9).
* Return bestMedian = 9.
*/
```

### Java Solution

```java
// Intuition: The problem has a monotonic property: if a median 'm' is achievable, any median less than 'm' is also achievable. This allows us to binary search for the maximum possible median on the answer space.
// Approach:
// 1. Sort the array to easily work with the median element(s).
// 2. Define a search space for the binary search. The lower bound is the initial median, and a safe upper bound is `initial_median + k`.
// 3. For each `mid` value (our target median) in the binary search, call a helper function `isPossible`.
// 4. `isPossible` calculates the minimum operations needed. To raise the median, we only need to increment elements from the median position to the right.
// 5. For an odd-sized array, it sums the costs to raise each element in the right half to the target.
// 6. For an even-sized array, it specifically calculates the cost for the two middle elements and then the rest of the right half.
// 7. If `isPossible` returns true, we try for a higher median (`low = mid + 1`); otherwise, we search for a smaller one (`high = mid - 1`).
// Time Complexity: O(N*log(K)), where N is the array size. Sorting takes O(N log N). The binary search performs log(K) iterations, and each `isPossible` check takes O(N).
// Space Complexity: O(1), as we use a constant amount of extra space (sorting can take O(log N) depending on implementation).
class Solution {
    // check if we can make the median at least
    // 'target' using at most 'k' operation
    static boolean isPossible(int[] arr, int target, int k) {
        int n = arr.length; // Get array length.
        long temp_k = k; // Use long to prevent overflow and avoid modifying original k.

        if (n % 2 == 1) {
            // for odd-sized array, consider elements from
            // middle to end
            for (int i = n / 2; i < n; ++i) { // Iterate from the single median element.
                if (arr[i] < target)
                    temp_k -= (target - arr[i]); // Subtract cost from our budget.
            }
        } else {
            // for even-sized array, handle two middle
            // elements separately
            if (arr[n / 2] <= target) { // If the higher middle element is not already above target.
                temp_k -= (target - arr[n / 2]); // Cost for the higher middle element.
                temp_k -= (target - arr[n / 2 - 1]); // Cost for the lower middle element.
            } else {
                // This handles when arr[n/2] > target.
                temp_k -= (2L * target - (arr[n / 2] + arr[n / 2 - 1])); // Use 2L for long arithmetic.
            }
            // process remaining elements to the right
            for (int i = n / 2 + 1; i < n; ++i) { // Iterate over the rest of the right half.
                if (arr[i] < target)
                    temp_k -= (target - arr[i]); // Subtract cost to raise them to target.
            }
        }

        return temp_k >= 0; // Return true if we had enough operations.
    }

    // function to compute maximum achievable median
    // with given k operation
    static int maximizeMedian(int[] arr, int k) {
        int n = arr.length;
        Arrays.sort(arr); // Sort the array to find the median.

        // compute initial median floor if even length
        int iniMedian = arr[n / 2];
        if (n % 2 == 0) {
            iniMedian += arr[n / 2 - 1];
            iniMedian /= 2;
        }

        int low = iniMedian, high = iniMedian + k; // Set the binary search range.
        int bestMedian = iniMedian; // Initialize with current median.

        // binary search to find maximum
        // achievable median
        while (low <= high) {
            int mid = low + (high - low) / 2; // Calculate midpoint.

            if (isPossible(arr, mid, k)) {
                bestMedian = mid; // If possible, update best answer.
                low = mid + 1;    // Try for a larger median.
            } else {
                high = mid - 1;   // Otherwise, try for a smaller one.
            }
        }

        return bestMedian;
    }
}

/*
*
* Dry Run
* arr = [4, 6, 10, 10, 4, 10], k = 2
*
* 1. Arrays.sort(arr) -> arr becomes [4, 4, 6, 10, 10, 10]
* 2. n = 6. iniMedian = (arr[2] + arr[3]) / 2 = (6 + 10) / 2 = 8.
* 3. Set binary search range: low = 8, high = 8 + 2 = 10. bestMedian = 8.
*
* --- Iteration 1 ---
* mid = 8 + (10 - 8) / 2 = 9.
* isPossible(arr, 9, 2):
* n=6 (even). temp_k = 2.
* arr[3] (10) > target (9). The 'if' is false, enter 'else'.
* temp_k -= (2 * 9 - (10 + 6))  => temp_k -= (18 - 16) => temp_k -= 2. temp_k is now 0.
* Loop for i > n/2 does nothing.
* Returns temp_k >= 0 (true).
* Result: isPossible is true. bestMedian = 9, low = 9 + 1 = 10.
*
* --- Iteration 2 ---
* mid = 10.
* isPossible(arr, 10, 2):
* n=6 (even). temp_k = 2.
* arr[3] (10) <= target (10). The 'if' is true.
* temp_k -= (10 - arr[3]) => temp_k -= 0. temp_k is 2.
* temp_k -= (10 - arr[2]) => temp_k -= (10 - 6) => temp_k -= 4. temp_k is now -2.
* Returns temp_k >= 0 (false).
* Result: isPossible is false. high = 10 - 1 = 9.
*
* Loop terminates as low (10) > high (9).
* Return bestMedian = 9.
*/
```

---

## 🔑 Key Insights

The core insight is the **monotonicity** of the problem. If you can achieve a certain median `m`, you can spend fewer operations to achieve any median smaller than `m`. This "yes/no" characteristic for a given median value is a classic signal for a binary search problem. By searching over the possible _answer_ space (the value of the median), we can efficiently narrow down to the optimal solution.

The second key insight is that to raise the median, we only need to increase the values of the elements from the median position to the end of the sorted array. Any operations on elements before the median position would be wasteful.

---

## 🚀 Further Exploration

- [**Aggressive cows**](https://www.geeksforgeeks.org/problems/aggressive-cows/1): Another classic problem that can be solved using binary search on the answer.
- [**Allocate minimum number of pages**](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1): This problem also shares the pattern of binary searching for an optimal value.
- [**Smallest Divisor**](https://www.geeksforgeeks.org/problems/smallest-divisor/1): Find the smallest divisor such that the sum of the divisions is less than or equal to a threshold, a great binary search on answer problem.

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/maximize-median-after-doing-k-addition-operation/1)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div align="center">

`Binary Search` `Arrays` `Sorting` `Greedy` `GeeksforGeeks`

</div>

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder**: The solutions and content in this repository are for educational purposes only. They are meant to help you learn and practice data structures and algorithms.
