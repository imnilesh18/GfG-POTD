# 🔗 Merge K sorted linked lists

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-57.01%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/merge-k-sorted-linked-lists/1).

---

## Problem Statement

Given an array `arr[]` of `n` sorted linked lists of different sizes. Your task is to **merge** all these lists into a single **sorted** linked list and return the **head** of the merged list.

---

## Examples

**Example 1:**

```
Input:
arr[] = [
  1 -> 3 -> 7,
  2 -> 4 -> 8,
  9
]
Output: 1 -> 2 -> 3 -> 4 -> 7 -> 8 -> 9
Explanation: The arr[] has 3 sorted linked lists.
1st list: 1 -> 3 -> 7
2nd list: 2 -> 4 -> 8
3rd list: 9
The merged list will be: 1 -> 2 -> 3 -> 4 -> 7 -> 8 -> 9.
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>
<br>
This problem requires us to combine all K lists while maintaining sorted order.

1.  We can start with the first list: `1 -> 3 -> 7`
2.  Merge this with the second list: `2 -> 4 -> 8`.
    - Compare `1` and `2`. Pick `1`. List: `1`
    - Compare `3` and `2`. Pick `2`. List: `1 -> 2`
    - Compare `3` and `4`. Pick `3`. List: `1 -> 2 -> 3`
    - Compare `7` and `4`. Pick `4`. List: `1 -> 2 -> 3 -> 4`
    - Compare `7` and `8`. Pick `7`. List: `1 -> 2 -> 3 -> 4 -> 7`
    - First list is done. Append remainder of second: `8`.
    - Merged list is now: `1 -> 2 -> 3 -> 4 -> 7 -> 8`
3.  Now, merge this result with the third list: `9`.
    - Since `9` is larger than all elements in our result list, it simply gets appended to the end.
4.  **Final List:** `1 -> 2 -> 3 -> 4 -> 7 -> 8 -> 9`.
</details>

**Example 2:**

```
Input:
arr[] = [
  1 -> 3,
  8,
  4 -> 5 -> 6
]
Output: 1 -> 3 -> 4 -> 5 -> 6 -> 8
Explanation: The arr[] has 3 sorted linked lists.
1st list: 1 -> 3
2nd list: 8
3rd list: 4 -> 5 -> 6
The merged list will be: 1 -> 3 -> 4 -> 5 -> 6 -> 8.
```

---

## 📏 Constraints

<div style="background-color: #282c34; padding: 10px; border-radius: 5px; color: #abb2bf;">
<ul>
  <li><code>1 ≤ total no. of nodes ≤ 10^5</code></li>
  <li><code>1 ≤ node->data ≤ 10^3</code></li>
</ul>
</div>

---

## 💡 Solution Approaches

### Approach 1: Iterative Merging (Brute-Force)

The simplest approach is to sequentially merge the lists one by one. We start with an empty result list, merge it with the first list, then merge the result with the second list, and continue this process until all K lists are merged.

#### C++ Solution

```cpp
// Intuition: The problem asks to merge K sorted lists. A simple way to do this is to take one list, merge it with the second,
// then take the result and merge it with the third, and so on, until all K lists are merged into one.
// Approach:
// 1. We use a helper function `merge(a, b)` that merges two sorted linked lists (standard merge-sort merge step).
// 2. Initialize a result list `res` to `nullptr` (empty list).
// 3. Iterate through the array (vector) of K lists from i = 0 to K-1.
// 4. In each iteration, merge the current result list `res` with the next list in the array `arr[i]`.
// 5. Update `res` to be the head of this new merged list.
// 6. After the loop finishes, `res` will be the head of the final, single sorted list containing all elements.
// Time Complexity: O(N*K), where N is the total number of nodes and K is the number of lists.
//    - Let each list have an average of n = N/K nodes.
//    - 1st merge: 0 + n = n operations.
//    - 2nd merge: n + n = 2n operations.
//    - 3rd merge: 2n + n = 3n operations.
//    - ...
//    - (K)th merge: (K-1)n + n = Kn operations.
//    - Total operations sum is roughly n * (1+2+...+K) which is O(n*K^2).
//    - Since n = N/K, this is O((N/K) * K^2) = O(N*K).
// Space Complexity: O(N) or O(1) depending on implementation.
//    - The recursive call stack for the `merge` function can go as deep as the total number of nodes (N) in the worst case.
//    - An iterative merge helper would be O(1) space.

/*Linked list Node structure

struct Node
{
    int data;
    Node* next;

    Node(int x){
        data = x;
        next = NULL;
    }

};
*/


class Solution {
  public:
      // Function to merge two sorted linked lists into one sorted list
    Node* merge(Node* a, Node* b) {
        // Base case: If list 'a' is empty, the merged list is just list 'b'
        if (!a) return b;

        // Base case: If list 'b' is empty, the merged list is just list 'a'
        if (!b) return a;

        // Compare the data of the heads of lists 'a' and 'b'
        if (a->data < b->data) {
            // 'a' has the smaller element. Its next should be the result of merging the rest of 'a' with all of 'b'.
            a->next = merge(a->next, b);
            // Return 'a' as the head of this newly merged list
            return a;
        } else {
            // 'b' has the smaller or equal element. Its next should be the result of merging all of 'a' with the rest of 'b'.
            b->next = merge(a, b->next);
            // Return 'b' as the head of this newly merged list
            return b;
        }
    }

    // Function to merge k sorted linked lists into one sorted list
    Node* mergeKLists(vector<Node*>& arr) {
        // Initialize the result list as empty (nullptr)
        Node* res = nullptr;

        // Iterate over each linked list in the input vector 'arr'
        for (int i = 0; i < arr.size(); i++) {
            // Sequentially merge the current result (res) with the current list from 'arr' (arr[i])
            res = merge(res, arr[i]);
        }

        // After merging all lists one by one, return the final merged list head
        return res;
    }
};

/*
*
* Dry Run
* Example 1: arr[] = [ (1 -> 3 -> 7), (2 -> 4 -> 8), (9) ]
*
* 1. Iteration i = 0:
* - res = nullptr
* - Call merge(nullptr, arr[0]) which is merge(nullptr, 1->3->7)
* - This returns (1 -> 3 -> 7).
* - res is now (1 -> 3 -> 7).
*
* 2. Iteration i = 1:
* - res = (1 -> 3 -> 7)
* - Call merge(res, arr[1]) which is merge(1->3->7, 2->4->8)
* - The merge helper recursively builds the list: 1 -> 2 -> 3 -> 4 -> 7 -> 8.
* - res is now (1 -> 2 -> 3 -> 4 -> 7 -> 8).
*
* 3. Iteration i = 2:
* - res = (1 -> 2 -> 3 -> 4 -> 7 -> 8)
* - Call merge(res, arr[2]) which is merge(1->2->3->4->7->8, 9)
* - This will append 9 at the end of the first list.
* - The result is (1 -> 2 -> 3 -> 4 -> 7 -> 8 -> 9).
* - res is now (1 -> 2 -> 3 -> 4 -> 7 -> 8 -> 9).
*
* 4. Loop finishes.
* 5. Return res: (1 -> 2 -> 3 -> 4 -> 7 -> 8 -> 9).
*
*/
```

---

## 🚀 Key Insights

- **Brute-Force (O(N\*K)):** This approach is simple but inefficient. Merging list 1 (size `n`) and list 2 (size `n`) takes `2n` time. Merging that result (size `2n`) with list 3 (size `n`) takes `3n` time. This summation leads to an O(N\*K) time complexity, which can be slow if K (the number of lists) is large.
- **Min-Heap (O(N log K)):** This approach is significantly faster because it avoids re-scanning merged nodes. At any point, it only operates on at most K nodes (the current "front" of each list). Finding the smallest of these K nodes takes `O(log K)` time (a heap pop). Since we must do this for all N nodes, the total time is a much-improved O(N log K).
- This problem is a classic application of a min-heap (priority queue) to efficiently merge K sorted streams of data.

---

## 📚 Further Exploration

- [Merge two sorted linked lists](https://www.geeksforgeeks.org/problems/merge-two-sorted-linked-lists/1) (This is the building block of the brute-force method).
- [Kth smallest element in a sorted matrix](https://www.geeksforgeeks.org/problems/kth-element-in-matrix/1) (A similar problem that can be solved using a min-heap).
- [Merge k Sorted Arrays](https://www.geeksforgeeks.org/problems/merge-k-sorted-arrays/1) (The same problem concept, but with arrays instead of linked lists).

---

## 🔗 References

- [Original GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/merge-k-sorted-linked-lists/1)
- [Min-Heap (Priority Queue) Data Structure](https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/)

---

## 🧑‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![linked-list](https://img.shields.io/badge/linked--list-blue?style=for-the-badge)
![heap](https://img.shields.io/badge/heap-orange?style=for-the-badge)
![priority-queue](https://img.shields.io/badge/priority--queue-red?style=for-the-badge)
![divide-and-conquer](https://img.shields.io/badge/divide--and--conquer-green?style=for-the-badge)
![geeksforgeeks](https://img.shields.io/badge/geeksforgeeks-black?style=for-the-badge)

---

## 📜 License

This project is licensed under the **MIT License**.

See the [LICENSE](LICENSE) file for details.

**Note:** This repository is for educational purposes only. The problem statement and examples are from GeeksforGeeks.
