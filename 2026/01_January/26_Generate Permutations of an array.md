# 🔁 Generate Permutations of an array

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-85.48%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License" />
</div>

> [!WARNING]
> **Educational Use Only** > This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/problems/generate-permutations-of-an-array/1) problem.

<div align="center">
  <img src="https://media.geeksforgeeks.org/wp-content/uploads/20250924153020241638/aaa.webp" alt="Permutation Recursion Tree" width="60%" />
</div>

---

## 📝 Problem Statement

Given an array `arr[]` of unique elements. Generate all possible **permutations** of the elements in the array.

**Note:** You can return the permutations in any order, the driver code will print them in sorted order.

---

## 🎯 Examples

### Example 1
```text
Input: arr[] = [1, 2, 3]
Output: [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
Explanation: There are 6 possible permutations (3! = 6) of the array.
```

### Example 2
```text
Input: arr[] = [1, 3]
Output: [[1, 3], [3, 1]]
Explanation: There are 2 possible permutations (2! = 2) of the array.
```

<details>
<summary><strong>📖 Example Breakdown (Input: [1, 2])</strong></summary>

1.  **Start:** Array `[1, 2]`, Index `0`.
2.  **Branch 1 (Swap index 0 with 0):** Array stays `[1, 2]`. Move to Index `1`.
    * **Sub-branch (Swap index 1 with 1):** Array `[1, 2]`. Reached end -> **Store [1, 2]**.
    * Backtrack.
3.  **Branch 2 (Swap index 0 with 1):** Array becomes `[2, 1]`. Move to Index `1`.
    * **Sub-branch (Swap index 1 with 1):** Array `[2, 1]`. Reached end -> **Store [2, 1]**.
    * Backtrack.
4.  **Result:** `[[1, 2], [2, 1]]`.
</details>

---

## ⛓️ Constraints

* `1 ≤ arr.size() ≤ 9`
* Elements are unique.

---

## 💡 Solution Approaches

### Approach: Recursion and Backtracking

We fix elements one by one at the current index and recursively permute the remaining elements. By swapping the current index with every subsequent index, we explore all possible arrangements. Backtracking ensures the array is restored to its previous state for the next iteration.

```cpp
// Intuition: Fix one element at the current index and recursively permute the rest. Backtrack to explore other choices.
// Approach: 
// 1. Base Case: If index reaches array size, a valid permutation is formed. Add to result.
// 2. Recursive Step: Iterate from current index to end. Swap current element with iterator element.
// 3. Recurse for the next index (idx + 1).
// 4. Backtrack: Swap elements back to restore original array state for next iteration.
// Time Complexity: O(N! * N) - There are N! permutations and we might take O(N) to store each.
// Space Complexity: O(N) - For recursion stack depth.

class Solution {
  public:
    // Recursive function to find all possible permutations. 
    void permutations(vector<vector<int>>& res, vector<int> arr, int idx) {
        // Base case: if all positions are filled
        if (idx == arr.size()) {
            res.push_back(arr);
            return;
        }
    
        // Permutations made by swapping each element
        // starting from index `idx`
        for (int i = idx; i < arr.size(); i++) {
          
            // Swapping current index with i to fix the position
            swap(arr[idx], arr[i]);
    
            // Recursive call to create permutations 
            // for the next element
            permutations(res, arr, idx + 1);
    
            // Backtracking: Restore the array to original state
            swap(arr[idx], arr[i]);
        }
    }
    
    // Function to get the permutations
    vector<vector<int>> permuteDist(vector<int>& arr) {
        vector<vector<int>> res;
        permutations(res, arr, 0);
        return res;
    }
};

/*
*
* Dry Run
* Input: arr = [1, 2]
* Call: permuteDist([1, 2]) -> permutations(res, [1, 2], 0)
*
* Level 0 (idx = 0):
* i = 0: 
* swap(arr[0], arr[0]) -> arr is [1, 2]
* Recurse: permutations(res, [1, 2], 1)
* Level 1 (idx = 1):
* i = 1:
* swap(arr[1], arr[1]) -> arr is [1, 2]
* Recurse: permutations(res, [1, 2], 2)
* Level 2 (idx = 2 == size):
* res.push_back([1, 2]) -> res = [[1, 2]]
* Return
* Backtrack: swap(arr[1], arr[1]) -> arr is [1, 2]
* Loop ends. Return.
* Backtrack: swap(arr[0], arr[0]) -> arr is [1, 2]
*
* i = 1:
* swap(arr[0], arr[1]) -> arr is [2, 1]
* Recurse: permutations(res, [2, 1], 1)
* Level 1 (idx = 1):
* i = 1:
* swap(arr[1], arr[1]) -> arr is [2, 1]
* Recurse: permutations(res, [2, 1], 2)
* Level 2 (idx = 2 == size):
* res.push_back([2, 1]) -> res = [[1, 2], [2, 1]]
* Return
* Backtrack: swap(arr[1], arr[1]) -> arr is [2, 1]
* Loop ends. Return.
* Backtrack: swap(arr[0], arr[1]) -> arr is [1, 2] (Restored)
*
* Loop ends. Return res.
*/
```

---

## 🔑 Key Insights

* **Backtracking Principle:** The core concept is "Choice, Explore, Un-choose". We make a choice (swap), explore recursive paths, and then undo the choice (swap back) to explore other possibilities.
* **Factorial Growth:** The number of permutations grows factorially ($N!$). For $N=10$, this is huge ($3.6$ million), so this approach is generally limited to small array sizes (usually $N \le 10$).
* **In-Place Modification:** By passing the array by value (or carefully managing references) and swapping, we generate permutations without needing complex auxiliary data structures like `visited` arrays, though standard backtracking often uses swaps on a single array reference.

---

## 🚀 Further Exploration

* **Next Permutation:** Find the next lexicographically greater permutation.
* **Permutations II:** Generate permutations when the array contains duplicates.
* **String Permutations:** Similar logic applied to characters in a string.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/generate-permutations-of-an-array/1)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Backtracking](https://img.shields.io/badge/Topic-Backtracking-FF5722?style=flat-square)
![Arrays](https://img.shields.io/badge/Topic-Arrays-007ACC?style=flat-square)
![Recursion](https://img.shields.io/badge/Topic-Recursion-4CAF50?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Platform-GeeksforGeeks-298D46?style=flat-square)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

> [!NOTE]
> **Educational Purpose:** This code is provided for learning and reference. Please attempt to solve the problem yourself before reviewing the solution.