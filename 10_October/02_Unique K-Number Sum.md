# 🔢 Unique K-Number Sum

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/combination-sum-iii--111703/1).

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-78.51%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-purple?style=for-the-badge)

</div>

---

## 📝 Problem Statement

Given two integers **n** and **k**, the task is to find all valid combinations of **k** numbers that add up to **n** based on the following conditions:

- Only numbers from the range `[1, 9]` are used.
- Each number can only be used at most once.

**Note:** You can return the combinations in any order; the driver code will print them in sorted order.

---

## 📖 Examples

### Example 1:

```

Input: n = 9, k = 3
Output: [[1, 2, 6], [1, 3, 5], [2, 3, 4]]
Explanation:
There are three valid combinations of 3 numbers that sum to 9:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9

```

### Example 2:

```

Input: n = 3, k = 3
Output: []
Explanation:
It is not possible to pick 3 distinct numbers from 1 to 9 that sum to 3, so no valid combinations exist.

```

<details>
<summary><strong>📖 Example 1 Breakdown</strong></summary>

Let's trace the path to find the combination `[1, 2, 6]` for `n = 9, k = 3`.

1.  **Start:** Begin with an empty combination `[]`, a target sum of `9`, and a needed count of `3`. Start picking numbers from `1`.
2.  **Pick 1:**
    - Add `1` to the combination: `[1]`.
    - New target sum: `9 - 1 = 8`.
    - Needed count: `3 - 1 = 2`.
    - Next number to pick must be greater than `1` (to avoid duplicates), so start from `2`.
3.  **Pick 2:**
    - Add `2` to the combination: `[1, 2]`.
    - New target sum: `8 - 2 = 6`.
    - Needed count: `2 - 1 = 1`.
    - Next number to pick must be greater than `2`, so start from `3`.
4.  **Try 3, 4, 5...:** The algorithm will try `3`, `4`, and `5`, but they won't lead to a solution from this path. For instance, picking `3` would leave a target sum of `3`, but we can't pick `3` again.
5.  **Pick 6:**
    - When the loop reaches `6`, add `6` to the combination: `[1, 2, 6]`.
    - New target sum: `6 - 6 = 0`.
    - Needed count: `1 - 1 = 0`.
6.  **Solution Found:** The target sum is `0` and we have picked `3` numbers (`k`). This is a valid combination. Add `[1, 2, 6]` to the result list.
7.  **Backtrack:** The algorithm will now backtrack by removing `6`, then removing `2`, and trying other numbers (like `3` after `1`) to find other combinations like `[1, 3, 5]`.

</details>

---

## 📊 Constraints

- `1 ≤ n ≤ 50`
- `1 ≤ k ≤ 9`

---

## 💡 Solution Approaches

### Optimized Approach (Backtracking)

The problem asks for all unique combinations, which is a classic signal for a **backtracking** approach. We can think of this as building a combination one number at a time.

- **Intuition:** We can recursively explore all possible combinations of `k` numbers. To ensure the combinations are unique and the numbers within them are unique (e.g., `[1, 2, 6]` is valid, `[2, 1, 6]` is a duplicate, and `[1, 1, 7]` is invalid), we pick numbers in increasing order.

- **Process:**
  1.  Define a recursive helper function that takes the current target sum `n`, the required size `k`, the starting number for the next choice, and the current combination being built.
  2.  **Base Case:** If the current combination has `k` numbers and the sum is `n`, we have found a valid combination.
  3.  **Recursive Step:** Iterate from the current starting number up to `9`. For each number `i`:
      - Add `i` to the current combination.
      - Make a recursive call with the updated sum (`n - i`), the same `k`, and an updated start number (`i + 1`).
      - **Backtrack:** After the recursive call returns, remove `i` from the combination to explore other possibilities.

This process prunes branches where the sum becomes negative or the combination size exceeds `k`, effectively exploring only valid paths.

### C++ Code

```cpp
// Intuition: The problem requires finding all unique combinations of k numbers that sum to n. This suggests a recursive approach to explore all possibilities. Using backtracking allows us to build a combination step-by-step and discard paths that are not fruitful.
// Approach: A recursive helper function 'solve' is used. It maintains the remaining sum, the required count of numbers (k), the current count of numbers in the combination, and the starting number for the next iteration to avoid duplicates.
// The base case for the recursion is when the sum becomes 0 and the count of numbers equals k.
// We iterate from 'start' to 9, adding the current number to a temporary list and making a recursive call. After the call, we backtrack by removing the number.
// Time Complexity: O(2^9 * k). In the worst-case, we explore all possible subsets of numbers from 1 to 9. The number of subsets is 2^9. For each valid subset of size k, we spend O(k) time to copy it to the result vector.
// Space Complexity: O(k). This is due to the recursion stack depth, which goes up to k, and the 'temp' vector that stores the current combination.

class Solution {
  public:
    void solve(int sum, int k, int count, int start, vector<int> &temp, vector<vector<int>> &result) {

        // Base case: if the desired sum is achieved and we have used exactly k numbers
        if(sum == 0 && count == k) {
            result.push_back(temp); // Add the valid combination to the result
            return;
        }

        // Pruning: if sum is negative or we have already picked k or more numbers, this path is invalid
        if(sum < 0 || count >= k) {
            return;
        }

        // Iterate through numbers from 'start' to 9
        for(int i = start; i <= 9; i++) {
            temp.push_back(i); // Include the current number in the combination
            // Recursive call for the next element
            solve(sum - i, k, count + 1, i + 1, temp, result);
            temp.pop_back(); // Backtrack: remove the current number to explore other possibilities
        }
    }

    vector<vector<int>> combinationSum(int n, int k) {
        vector<int> temp; // To store the current combination
        vector<vector<int>> result; // To store all valid combinations
        int count = 0; // Initial count of numbers in the combination
        solve(n, k, count, 1, temp, result); // Start the recursion
        return result;
    }
};

/*
*
* Dry Run (n = 9, k = 3)
*
* 1. combinationSum(9, 3) calls solve(9, 3, 0, 1, [], result)
*
* 2. solve(9, 3, 0, 1, [], result):
* - Loop starts, i = 1
* - temp = [1]
* - Calls solve(8, 3, 1, 2, [1], result)
*
* 3. solve(8, 3, 1, 2, [1], result):
* - Loop starts, i = 2
* - temp = [1, 2]
* - Calls solve(6, 3, 2, 3, [1, 2], result)
*
* 4. solve(6, 3, 2, 3, [1, 2], result):
* - Loop starts, tries i = 3, 4, 5...
* - When i = 6:
* - temp = [1, 2, 6]
* - Calls solve(0, 3, 3, 7, [1, 2, 6], result)
*
* 5. solve(0, 3, 3, 7, [1, 2, 6], result):
* - Base case met: sum is 0, count is 3 (equals k).
* - result.push_back([1, 2, 6]). result is now [[1, 2, 6]]
* - Returns.
*
* 6. Backtrack:
* - In solve(6, 3, 2, 3, ...), temp.pop_back() -> temp is [1, 2]. Loop continues with i = 7.
* - No further solutions found down this path. The function returns.
* - In solve(8, 3, 1, 2, ...), temp.pop_back() -> temp is [1]. Loop continues with i = 3.
* - Calls solve(5, 3, 2, 4, [1, 3], result)
*
* This process continues, finding all combinations like [1, 3, 5] and [2, 3, 4].
*
*/
```

---

## 🚀 Key Insights

- The core idea is **"pick, explore, and backtrack"**.
- The `start` parameter in the recursion is crucial. It ensures that we only pick numbers greater than the previous one, which elegantly handles two constraints:
  1.  **Each number is used at most once** (e.g., after picking 2, we start the next search from 3).
  2.  **Combinations are unique** (we will generate `[1, 2, 6]` but not `[2, 1, 6]`, `[6, 2, 1]`, etc.).
- Pruning the search (returning when `sum < 0` or `count >= k`) is essential for efficiency, as it stops the exploration of invalid paths early.

---

## 🌐 Further Exploration

- [Combination Sum](https://www.geeksforgeeks.org/problems/combination-sum/0)
- [Combination Sum II](https://www.geeksforgeeks.org/problems/combination-sum-ii/0)
- [Subsets II](https://www.google.com/search?q=https://www.geeksforgeeks.org/problems/subsets-ii/1)
- [Permutations](https://www.geeksforgeeks.org/problems/permutations-of-a-given-string/0)

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/combination-sum-iii--111703/1)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## \#️⃣ Tags

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

**A gentle reminder:** The solutions and explanations in this repository are for educational purposes. It's important to try solving problems on your own first to maximize your learning.
