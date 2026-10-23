# 🌳 Count Pairs Violating BST Property

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty Medium" />
  <img src="https://img.shields.io/badge/Accuracy-56.99%25-green?style=for-the-badge" alt="Accuracy 56.99%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given the root of a binary tree in which all node values are distinct, count the pairs of nodes that violate any of the following **Binary Search Tree (BST)** properties:
1. All values in the left subtree are strictly smaller.
2. All values in the right subtree are strictly greater.

### 🛑 Constraints

- `1 ≤ size of binary tree ≤ 5 * 10^4`
- `1 ≤ node.data ≤ 10^9`
- All node values are distinct.

---

## 💡 Examples

### Example 1

```text
Input: root[] = [10, 50, 40, N, N, 20, 30]
Output: 5
Explanation: Pairs violating BST property are:
(10, 50) - 10 should be greater than its left child value.
(40, 30) - 40 should be less than its right child value.
(50, 20), (50, 30) and (50, 40) - maximum of left subtree of 10 is 50, which is greater than 20, 30 and 40 of its right subtree.

```

### Example 2

```text
Input: root[] = [80, 40, 30, 70, N, 60, 50]
Output: 10
Explanation: There are total 10 pairs (80, 30), (80, 60), (80, 50), (30, 60), (40, 70), (40, 30), (40, 50), (70, 30), (70, 60), (70, 50) which violate the BST properties.

```

Let's break down **Example 1**:

1. We perform an **in-order traversal** of the given tree: `[50, 10, 20, 40, 30]`.
2. In a perfect BST, the in-order traversal should yield a strictly sorted ascending array: `[10, 20, 30, 40, 50]`.
3. Every instance where a larger number appears before a smaller number (an **inversion**) represents a pair violating the BST property.
4. Counting inversions in `[50, 10, 20, 40, 30]`:
* `50` comes before `10, 20, 40, 30` (4 violations)
* `40` comes before `30` (1 violation)


5. Total violations = `4 + 1 = 5`.

---

## 🧠 Solution Approach

### In-order Traversal + Inversion Counting (Merge Sort)

**Intuition:**
A valid Binary Search Tree (BST) produces a strictly increasing array during an in-order traversal. Therefore, any pairs of nodes that violate the BST property correspond exactly to **inversions** in its in-order traversal array. An inversion is a pair `(arr[i], arr[j])` such that `i < j` but `arr[i] > arr[j]`. We can efficiently count these inversions using an optimized Merge Sort algorithm.

```cpp
// Intuition: A valid BST produces a strictly increasing array during in-order traversal. Any violations of the BST property correspond exactly to inversions in this in-order array.
// Approach: 
// 1. Perform an in-order traversal of the tree and store node values in an array.
// 2. Count the number of inversions in the array using a modified Merge Sort.
// 3. An inversion occurs when arr[left] > arr[right] with left < right, which directly represents a BST violation.
// Time Complexity: O(N log N) where N is the number of nodes, due to the merge sort algorithm. In-order traversal takes O(N).
// Space Complexity: O(N) auxiliary space used to store the in-order traversal and for the temporary array during merge sort.

/* BST Node Structure
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/
class Solution {
  public:
    // Extract node values via in-order traversal
    void inorder(Node* root, vector<int>& arr) {
        if (!root) return;
        inorder(root->left, arr);
        arr.push_back(root->data);
        inorder(root->right, arr);
    }

    // Merge two sorted halves and count cross inversions
    int mergeAndCount(vector<int>& arr, int l, int m, int r) {
        int left = l, right = m + 1;
        vector<int> temp;
        int count = 0;

        while (left <= m && right <= r) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left++]);
            } else {
                temp.push_back(arr[right++]);
                // Left elements are greater than arr[right], creating inversions
                count += (m - left + 1);
            }
        }

        // Copy remaining elements from left half
        while (left <= m) {
            temp.push_back(arr[left++]);
        }
        
        // Copy remaining elements from right half
        while (right <= r) {
            temp.push_back(arr[right++]);
        }

        // Copy merged elements back to original array
        for (int i = l; i <= r; i++) {
            arr[i] = temp[i - l];
        }

        return count;
    }

    // Recursively sort the array and count inversions
    int mergeSortAndCount(vector<int>& arr, int l, int r) {
        int count = 0;
        if (l < r) {
            int m = l + (r - l) / 2;

            // Aggregate inversions from left, right, and merge steps
            count += mergeSortAndCount(arr, l, m);
            count += mergeSortAndCount(arr, m + 1, r);
            count += mergeAndCount(arr, l, m, r);
        }
        return count;
    }
  
    int pairsViolatingBST(Node *root) {
        vector<int> arr;

        // Step 1: Flatten tree to array via in-order traversal
        inorder(root, arr);

        // Step 2: Use merge sort to count inversions efficiently
        if (arr.empty()) return 0;
        return mergeSortAndCount(arr, 0, arr.size() - 1);
    }
};

/*
* Dry Run
* Input: root = [10, 50, 40, N, N, 20, 30]
* 
* 1. In-order traversal extracts: arr = [50, 10, 20, 40, 30]
* 2. mergeSortAndCount(arr, 0, 4):
*    - Splits into [50, 10, 20] and [40, 30]
*    - Processing [50, 10, 20]:
*        - Inversions found: (50, 10), (50, 20) -> Count = 2
*        - Sorted half: [10, 20, 50]
*    - Processing [40, 30]:
*        - Inversions found: (40, 30) -> Count = 1
*        - Sorted half: [30, 40]
*    - Merging [10, 20, 50] and [30, 40]:
*        - Inversions found: 50 is greater than 30 and 40 -> Count = 2
*        - Final sorted array: [10, 20, 30, 40, 50]
* 3. Total Inversions = 2 + 1 + 2 = 5
* Output: 5
*/

```

---

## 🔑 Key Insights

* **BST In-Order Property:** The foundation of this approach relies on the mathematical guarantee that an in-order traversal of a valid BST yields a strictly increasing sequence.
* **Inversion Counting:** Counting violations natively in a tree is complex. By mapping the tree structure to a 1D array, the problem seamlessly transforms into the classic "Count Inversions in an Array" problem.
* **Algorithm Optimization:** A brute-force nested loop to count inversions would take $O(N^2)$ time, which results in a Time Limit Exceeded (TLE) error for large trees. Piggybacking the count logic onto a **Merge Sort** algorithm drops the time complexity to an optimal $O(N \log N)$.

---

## 🔭 Further Exploration

* **Count Inversions:** Explore the standard array inversion counting problem to solidify your understanding of modified Merge Sorts.
* **Check for BST:** A related problem where you simply return `true` or `false` if the tree maintains the BST properties.
* **Fixing a BST:** Try problems like "Recover Binary Search Tree" where exactly two nodes of a BST are swapped, and you must restore it without changing the structure.

---

## 🔗 References

* **Original Problem:** [GeeksforGeeks - Count Pairs Violating BST Property](https://www.geeksforgeeks.org/problems/pairs-violating-bst-property--212515/1)
* **Concept:** [Inversion Count in Array using Merge Sort](https://www.geeksforgeeks.org/inversion-count-in-array-using-merge-sort/)

---

## 👨‍💻 Author

Prepared and documented by [imnilesh18](https://github.com/imnilesh18).

## 🏷️ Tags

`#binary-search-tree` `#merge-sort` `#tree-traversal` `#inversion-count` `#geeksforgeeks` `#c++`