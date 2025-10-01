# 🔄 All Unique Permutations of an array

> ⚠️ **Educational Use Only**: This repository and its content are intended solely for educational purposes. The solutions provided are for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/all-unique-permutations-of-an-array/1).

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-52.85%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

---

### Problem Statement

Given an array `arr[]` that may contain duplicates, your task is to find all possible **distinct permutations** of the array in **sorted order**.

**Note:** A sequence `A` is greater than sequence `B` if there is an index `i` for which `Aj = Bj` for all `j < i` and `Ai > Bi`.

---

### 📖 Examples

Here are a couple of examples to illustrate the problem:

**Example 1:**
```
Input: arr[] = [1, 3, 3]
Output: 
[[1, 3, 3], 
 [3, 1, 3], 
 [3, 3, 1]]
Explanation: These are the only possible distinct permutations for the given array.
```

<details>
<summary>📖 Example Breakdown (arr = [1, 3, 3])</summary>
<div>
Let's trace how we get the unique permutations for `[1, 3, 3]`.

1.  **Initial State:**
    * Sorted `arr`: `[1, 3, 3]`
    * Start the backtracking process.

2.  **Path 1: Start with `1`**
    * Choose `1`. Current permutation `curr` is `[1]`.
    * Remaining elements to choose from are `[3, 3]`.
    * Choose the first `3`. `curr` becomes `[1, 3]`.
    * Choose the second `3`. `curr` becomes `[1, 3, 3]`. This is a full permutation. Add it to the result.
    * Backtrack. `curr` is `[1, 3]`. We can't choose the second `3` again if the first `3` is not in use, which prevents duplicates.

3.  **Path 2: Start with `3`**
    * Skip `1` (we'll use it later). Choose the first `3`. `curr` is `[3]`.
    * Remaining elements are `[1, 3]`.
    * Choose `1`. `curr` becomes `[3, 1]`.
    * Choose the remaining `3`. `curr` becomes `[3, 1, 3]`. Add to result.
    * Backtrack. `curr` is `[3]`.
    * Now choose the second `3`. `curr` becomes `[3, 3]`.
    * Choose `1`. `curr` becomes `[3, 3, 1]`. Add to result.

4.  **Path 3: Start with the second `3`**
    * Our logic prevents this. Since the array is sorted `[1, 3, 3]`, when we are at the second `3`, we see that it's the same as the previous element (`3`) and that the previous element has not been visited in this path. So, we **skip** it to avoid generating the same set of permutations we already generated starting with the first `3`.

This is how the sorting and the duplicate-check logic work together to ensure every generated permutation is unique.
</div>
</details>

**Example 2:**
```
Input: arr[] = [2, 3]
Output: 
[[2, 3], 
 [3, 2]]
Explanation: These are the only possible distinct permutations for the given array.
```

---

### ⛓️ Constraints

The constraints for this problem are:
- `1 ≤ arr.size() ≤ 9`

---

### 💡 Solution Approaches

The problem asks for all unique permutations, which is a classic signal for a **backtracking** approach. The main challenge is handling duplicate elements to ensure the generated permutations are distinct.

#### Optimized Approach: Backtracking with Duplicate Handling

The intuition is to build permutations step-by-step. To avoid duplicates, we first sort the array. Then, during the backtracking process, we add a condition: if the current element is the same as the previous one, and the previous one has not been picked in the current path, we skip the current element. This ensures that for a group of identical numbers, we only pick them in one specific order, thus preventing duplicate permutations.

```cpp
// Intuition: The problem requires generating all unique permutations from an array that might have duplicates. This is a classic backtracking problem. The key challenge is to avoid generating the same permutation multiple times.
// Approach:
// 1. Sort the input array. This brings all duplicate elements together, which is crucial for the duplicate handling logic.
// 2. Use a recursive backtracking function. This function will build a permutation step by step.
// 3. We use a 'visited' boolean array to keep track of which elements have been included in the current permutation.
// 4. The base case for the recursion is when the current permutation's size equals the input array's size. At this point, we've found a complete permutation and add it to our result list.
// 5. In the recursive step, we iterate through the array. For each element, we check:
//    a. If it's already visited, we skip it.
//    b. **Duplicate Handling Logic**: If the current element is the same as the previous one (i > 0 && arr[i] == arr[i - 1]) AND the previous element has NOT been visited yet (!visited[i - 1]), we skip the current element. This is the core trick to prevent duplicates. It ensures that for any set of duplicate numbers, we only generate permutations by picking them in the order they appear in the sorted array.
// 6. If an element can be chosen, we mark it as visited, add it to our current path, and make a recursive call.
// 7. After the recursive call returns, we "backtrack" by removing the element from the current path and un-marking it as visited, allowing it to be used in other permutations.
// Time Complexity: O(N * N!), where N is the number of elements. There are N! permutations in the worst case (all unique elements). For each permutation, it takes O(N) time to create a copy to add to the result list.
// Space Complexity: O(N) for the recursion depth and the auxiliary space used by the 'visited' and 'curr' vectors. This does not include the space for the final result vector.

class Solution {
  public:
    void backtrack(vector<int>& arr, vector<bool>& visited,
                   vector<int>& curr,  vector<vector<int>>& result) {

        // Base case: If the current permutation is complete, add it to the result list.
        if (curr.size() == arr.size()) {
            result.push_back(curr);
            return;
        }
    
        // Iterate through all numbers in the array to build the permutation.
        for (int i = 0; i < arr.size(); i++) {
    
            // Condition 1: Skip elements that are already included in the current permutation.
            if (visited[i]) continue;
    
            // Condition 2: The core logic to prevent duplicate permutations.
            // If the current element is the same as the previous one, and the previous one
            // hasn't been picked in this path, then skip the current element.
            // This ensures that we only pick the first of any duplicate elements available.
            if (i > 0 && arr[i] == arr[i - 1] && !visited[i - 1]) continue;
    
            // --- Choose ---
            visited[i] = true;      // Mark the element as visited.
            curr.push_back(arr[i]); // Add the element to the current permutation.
    
            // --- Recurse ---
            // Explore further to build the rest of the permutation.
            backtrack(arr, visited, curr, result);
    
            // --- Un-choose (Backtrack) ---
            curr.pop_back();        // Remove the element from the current permutation.
            visited[i] = false;     // Unmark as visited to allow it to be used in other paths.
        }
    }
    
    // Main function to generate all unique permutations.
    vector<vector<int>> uniquePerms(vector<int>& arr) {
    
        // Sort the array to handle duplicates effectively.
        sort(arr.begin(), arr.end());
    
        vector<vector<int>> result; // To store all unique permutations.
        vector<int> curr;           // To store the current permutation being built.
        vector<bool> visited(arr.size(), false); // To track visited elements.
    
        // Start the backtracking process.
        backtrack(arr, visited, curr, result);
        
        return result;
    }
};

/*
*
* Dry Run with arr = [1, 3, 3]
*
* 1. uniquePerms([1, 3, 3]) -> sort(arr) -> arr is already [1, 3, 3]
* 2. backtrack([1, 3, 3], [F, F, F], [], result)
*
* i = 0 (arr[0] = 1):
* - visited[0] = T, curr = [1]
* - backtrack([1, 3, 3], [T, F, F], [1], result)
* i = 0 -> skip (visited)
* i = 1 (arr[1] = 3):
* - visited[1] = T, curr = [1, 3]
* - backtrack([1, 3, 3], [T, T, F], [1, 3], result)
* ...
* i = 2 (arr[2] = 3):
* - visited[2] = T, curr = [1, 3, 3]
* - curr.size() == arr.size() -> result.push_back([1, 3, 3])
* - backtrack returns
* - curr.pop_back(), visited[2] = F -> curr = [1, 3]
* - curr.pop_back(), visited[1] = F -> curr = [1]
* i = 2 (arr[2] = 3):
* - DUPLICATE CHECK: i > 0, arr[2] == arr[1] (3 == 3), !visited[1] is TRUE.
* - So, we 'continue' and skip this path. This prevents generating [1, 3, 3] again.
*
* i = 1 (arr[1] = 3):
* - visited[1] = T, curr = [3]
* - backtrack([1, 3, 3], [F, T, F], [3], result)
* i = 0 (arr[0] = 1):
* - visited[0] = T, curr = [3, 1]
* - backtrack(...) -> finds [3, 1, 3] and adds to result
* ...
* i = 2 (arr[2] = 3):
* - DUPLICATE CHECK: i > 0, arr[2] == arr[1] (3==3), !visited[1] is FALSE because visited[1] is T. Condition fails.
* - visited[2] = T, curr = [3, 3]
* - backtrack(...) -> finds [3, 3, 1] and adds to result
*
* i = 2 (arr[2] = 3):
* - DUPLICATE CHECK: i > 0, arr[2] == arr[1] (3 == 3), !visited[1] is TRUE. Skip.
*
* Final Result: [[1, 3, 3], [3, 1, 3], [3, 3, 1]]
*
*/
```

---

### 🚀 Key Insights

-   **Sorting is Crucial**: The duplicate-handling logic `(i > 0 && arr[i] == arr[i-1] && !visited[i-1])` fundamentally relies on the input array being sorted. Sorting groups identical elements together, allowing the check to work correctly.
-   **Backtracking Pattern**: The "choose, explore, un-choose" pattern is a standard template for backtracking problems. `curr.push_back()` is the "choose" step, the recursive `backtrack()` call is the "explore" step, and `curr.pop_back()` is the "un-choose" step.

---

### 🗺️ Further Exploration

If you enjoyed this problem, you might also like these related challenges on GeeksforGeeks and LeetCode:

-   [Permutations of a given string](https://www.geeksforgeeks.org/problems/permutations-of-a-given-string2041/1) (handling string permutations)
-   [Combination Sum](https://www.geeksforgeeks.org/problems/combination-sum-1587115620/1) (finding combinations that sum to a target)
-   [LeetCode 46. Permutations](https://leetcode.com/problems/permutations/) (the version without duplicate numbers)

---

### 🔗 References

-   **Original Problem:** [https://www.geeksforgeeks.org/problems/all-unique-permutations-of-an-array/1](https://www.geeksforgeeks.org/problems/all-unique-permutations-of-an-array/1)
-   **Backtracking Guide:** A helpful resource for understanding backtracking is the [GeeksforGeeks Backtracking Introduction](https://www.geeksforgeeks.org/introduction-to-backtracking-data-structure-and-algorithm-tutorials/).

---

### 🧑‍💻 Author

-   **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

### 🏷️ Tags

`backtracking` `recursion` `c++` `geeksforgeeks` `arrays` `permutations`

---

### 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder:** The solutions in this repository are for educational and learning purposes. They are meant to help you understand different problem-solving techniques. Always try to solve problems on your own first!