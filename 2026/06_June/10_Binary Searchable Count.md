# 🟧 Binary Searchable Count

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/binary-searchable-elements/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-48.28%25-brightgreen?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` consisting of `n` distinct integers, find the maximum count of integers that are **binary searchable** in the given array. 

Binary searchable elements are determined using the standard Binary Search implementation described below:
1. Initially `l` is `0` and `r` is `size of array - 1`.
2. While `(l <= r)`, compute `mid` as the floor of `(l + r)/2` and compare with `arr[mid]`.
3. If the target element is the same as `arr[mid]`, return `true`. 
4. Else if `arr[mid]` is smaller, change `l = mid + 1`.
5. Else change `r = mid - 1`.

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [1, 3, 2]
Output: 2
Explanation: arr[0], arr[1] can be found using standard binary search.

```

**Example 2:**

```text
Input: arr[] = [2, 1, 3, 5, 4, 6]
Output: 4
Explanation: arr[0], arr[2], arr[4], arr[5] can be found using standard binary search.

```

Let's test if **5** is binary searchable in `arr[] = [2, 1, 3, 5, 4, 6]`:

* `l = 0, r = 5` ➔ `mid = 2`. `arr[2] = 3`. Since `3 < 5`, move right `l = 3`.
* `l = 3, r = 5` ➔ `mid = 4`. `arr[4] = 4`. Since `4 < 5`, move right `l = 5`.
* `l = 5, r = 5` ➔ `mid = 5`. `arr[5] = 6`. Since `6 > 5`, move left `r = 4`.
* `l = 5 > r = 4`. Loop ends, **5 is NOT found**. Wait, the example says elements `arr[0]=2`, `arr[2]=3`, `arr[4]=4`, and `arr[5]=6` are found. **5** is skipped because standard binary search takes a wrong turn due to the unsorted nature of the array.

---

## ⚠️ Constraints

> * `1 ≤ n ≤ 10^5`
> * `1 ≤ arr[i] ≤ 10^5`
> * `Expected Time Complexity: O(n)`
> * `Expected Auxiliary Space: O(log n)`
> 
> 

---

## 🚀 Solution Approaches

### 1️⃣ Brute-Force Approach (Simulation)

We simply iterate through every element in the array and simulate the standard binary search process. If the element is found by the algorithm, we increment our counter.

```cpp
// Intuition: The problem asks us to find how many elements can be successfully found using standard binary search. The simplest way is to simulate the binary search process for each element individually.
// Approach: 
// 1. Iterate through each element in the array as the 'target'.
// 2. For each target, initialize the binary search range with 'l = 0' and 'r = n - 1'.
// 3. Perform standard binary search: find 'mid', check if it equals 'target'.
// 4. Update 'l' or 'r' based on whether 'target' is greater or smaller than 'arr[mid]'.
// 5. If found, increment the count. Return the total count after checking all elements.
// Time Complexity: O(N log N) - We run a binary search taking O(log N) time for each of the N elements.
// Space Complexity: O(1) - No extra space is used, only a few variables for pointers.
class Solution {
  public:
    int binarySearchable(vector<int> arr) {
        int count = 0;
        int n = arr.size();
    
        // For each element check if it can be found by doing a binary search
        for (int i = 0; i < n; i++) {
    
            // Binary search range
            int l = 0, r = n - 1;
    
            // Do a binary Search
            while (l <= r) {
                int mid = (l + r) / 2;
    
                // Array element found
                if (arr[mid] == arr[i]) {
                    count++;
                    break;
                }
                
                // If target is larger, search right half
                if (arr[mid] < arr[i]) {
                    l = mid + 1;
                }
                // If target is smaller, search left half
                else {
                    r = mid - 1;
                }
            }
        }
    
        return count;
    }
};

/*
*
* Dry Run
* Input: arr = [1, 3, 2]
*
* i=0, target=1: l=0, r=2 -> mid=1. arr[1]=3. 1<3, so r=0. 
*                l=0, r=0 -> mid=0. arr[0]=1. Found! count=1
* i=1, target=3: l=0, r=2 -> mid=1. arr[1]=3. Found! count=2
* i=2, target=2: l=0, r=2 -> mid=1. arr[1]=3. 2<3, so r=0.
*                l=0, r=0 -> mid=0. arr[0]=1. 2>1, so l=1.
*                l=1 > r=0. Not Found.
* Output: 2
*
*/

```

---

### 2️⃣ Optimized Approach (Implicit BST Traversal)

Instead of running a binary search for every element independently, we can view the binary search index partitions as an implicit **Binary Search Tree (BST)**. For an element to be found correctly, it must abide by the BST rules: it must be larger than all the ancestors where we took a right turn, and smaller than all ancestors where we took a left turn.

```cpp
// Intuition: Since binary search divides the array at indices exactly like a Binary Search Tree (BST), an element is binary searchable if and only if it satisfies the BST property. It must be greater than all ancestors where we took a right turn, and smaller than all ancestors where we took a left turn.
// Approach: 
// 1. Simulate the implicit binary search tree traversing the array indices from 0 to n-1.
// 2. Keep track of the valid range (min_val, max_val) for each subtree.
// 3. At any 'mid', check if 'arr[mid]' is strictly within (min_val, max_val). If yes, increment the count.
// 4. Recursively traverse the left half by restricting the upper bound to min(max_val, arr[mid]).
// 5. Recursively traverse the right half by restricting the lower bound to max(min_val, arr[mid]).
// Time Complexity: O(N) - We visit each index in the array exactly once, imitating a tree traversal.
// Space Complexity: O(log N) - The recursive call stack goes as deep as the height of the implicit binary tree.
class Solution {
public:
    void checkSearchable(const vector<int>& arr, int l, int r, int min_val, int max_val, int& count) {
        // Base case: Invalid range
        if (l > r) return;
        
        // Find the middle index representing current root
        int mid = (l + r) / 2;
        
        // Validate if current element respects the BST bounds
        if (arr[mid] > min_val && arr[mid] < max_val) {
            count++;
        }
        
        // Recursively check the left partition restricting the upper bound
        checkSearchable(arr, l, mid - 1, min_val, min(max_val, arr[mid]), count);
        
        // Recursively check the right partition restricting the lower bound
        checkSearchable(arr, mid + 1, r, max(min_val, arr[mid]), max_val, count);
    }
    
    int binarySearchable(vector<int>& arr) {
        int count = 0;
        
        // Start DFS traversal with infinite bounds
        checkSearchable(arr, 0, arr.size() - 1, INT_MIN, INT_MAX, count);
        
        return count;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 1, 3]
*
* Call 1: l=0, r=2, min=-INF, max=INF. mid=1, arr[1]=1. 
*         1 is within bounds. count=1.
*   Call 2 (left): l=0, r=0, min=-INF, max=1. mid=0, arr[0]=2. 
*                  2 is NOT < 1. count remains 1.
*   Call 3 (right): l=2, r=2, min=1, max=INF. mid=2, arr[2]=3. 
*                   3 is within bounds. count=2.
* Output: 2
*
*/

```

---

## 🧠 Key Insights

* Standard Binary Search doesn't care if the array is sorted; it simply navigates the array conceptually identical to how one traverses a Binary Search Tree (BST).
* Using **DFS traversal over the array indices**, we check the constraints inherited from parent nodes (elements acting as bounds). This transforms $O(N \log N)$ redundant checks into a highly efficient single-pass $O(N)$ tree search.

---

## 🔗 Further Exploration

1. [GeeksforGeeks - Binary Search](https://www.geeksforgeeks.org/binary-search/)
2. [Check if a given array can represent Preorder Traversal of Binary Search Tree](https://www.geeksforgeeks.org/check-if-a-given-array-can-represent-preorder-traversal-of-binary-search-tree/)

---

## 🧑‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

* `greedy`
* `algorithms`
* `binary-search`
* `trees`
* `geeksforgeeks`