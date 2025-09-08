# 🔗 Merge Sort for Linked List

<span>
    <img src="https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks" alt="GeeksforGeeks Logo" />
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge" alt="Difficulty: Medium" />
    <img src="https://img.shields.io/badge/Accuracy-74.76%25-brightgreen.svg?style=for-the-badge" alt="Accuracy: 74.76%" />
    <img src="https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge" alt="Points: 4" />
    <img src="https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge" alt="License: MIT" />
</span>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/sort-a-linked-list/1).

---

## Problem Statement

You are given the `head` of a linked list. You have to sort the given linked list using **Merge Sort**.

## Examples

**Example 1:**

```
Input:
head = 60 -> 40 -> 20 -> 50 -> 30 -> 10
Output:
10 -> 20 -> 30 -> 40 -> 50 -> 60
Explanation:
After sorting the given linked list, the resultant list is as shown.
```

<details>
<summary><strong>📖 Example Breakdown</strong></summary>

Let's trace the Merge Sort logic with the input `60 -> 40 -> 20 -> 50 -> 30 -> 10`:

1.  **Main Call:** `mergeSort(60 -> 40 -> 20 -> 50 -> 30 -> 10)`
2.  **Find Mid & Split:**
    - The middle is found before `50`. The list is split into two halves.
    - `head`: `60 -> 40 -> 20`
    - `second`: `50 -> 30 -> 10`
3.  **Recursive Call (Left):** `mergeSort(60 -> 40 -> 20)`
    - **Split:** `head1 = 60 -> 40`, `second1 = 20`
    - **Recursive Call:** `mergeSort(60 -> 40)`
      - **Split:** `h = 60`, `s = 40`
      - `mergeSort(60)` returns `60` (base case).
      - `mergeSort(40)` returns `40` (base case).
      - **Merge:** `merge(60, 40)` compares 60 and 40, returns `40 -> 60`.
    - **Recursive Call:** `mergeSort(20)` returns `20` (base case).
    - **Merge:** `merge(40 -> 60, 20)` compares 40 and 20, returns `20 -> 40 -> 60`.
4.  **Recursive Call (Right):** `mergeSort(50 -> 30 -> 10)`
    - **Split:** `head2 = 50 -> 30`, `second2 = 10`
    - **Recursive Call:** `mergeSort(50 -> 30)`
      - **Split:** `h' = 50`, `s' = 30`
      - `mergeSort(50)` returns `50`.
      - `mergeSort(30)` returns `30`.
      - **Merge:** `merge(50, 30)` returns `30 -> 50`.
    - **Recursive Call:** `mergeSort(10)` returns `10`.
    - **Merge:** `merge(30 -> 50, 10)` compares 30 and 10, returns `10 -> 30 -> 50`.
5.  **Final Merge:** Now we merge the results from steps 3 and 4: `merge(20 -> 40 -> 60, 10 -> 30 -> 50)`
    - 10 < 20. Result: `10 -> merge(20 -> ..., 30 -> ...)`
    - 20 < 30. Result: `10 -> 20 -> merge(40 -> ..., 30 -> ...)`
    - 30 < 40. Result: `10 -> 20 -> 30 -> merge(40 -> ..., 50 -> ...)`
    - 40 < 50. Result: `10 -> 20 -> 30 -> 40 -> merge(60 -> ..., 50 -> ...)`
    - 50 < 60. Result: `10 -> 20 -> 30 -> 40 -> 50 -> merge(60 -> ..., NULL)`
    - Base case hits. Result: `10 -> 20 -> 30 -> 40 -> 50 -> 60`
6.  **Final Sorted List:** `10 -> 20 -> 30 -> 40 -> 50 -> 60`

</details>

**Example 2:**

```
Input:
head = 9 -> 8 -> 5 -> 2
Output:
2 -> 5 -> 8 -> 9
Explanation:
After sorting the given linked list, the resultant list is as shown.
```

---

## Constraints

<div style="background-color: #333; border-radius: 5px; padding: 10px; color: #eee;">
<ul>
    <li><code>1 ≤ number of nodes ≤ 10<sup>5</sup></code></li>
    <li><code>0 ≤ node->data ≤ 10<sup>6</sup></code></li>
</ul>
</div>

---

## Solution Approaches

### Optimized Approach: Merge Sort

This problem requires us to adapt the classic Merge Sort algorithm, a divide-and-conquer strategy, for a singly linked list. Since we cannot perform random access like in an array, we find the middle of the list using the **slow and fast pointer** technique.

We recursively sort the left and right halves and then merge them using a standard merge procedure for two sorted linked lists.

#### C++ Solution

```cpp
// Intuition: Apply the divide-and-conquer strategy of Merge Sort. Recursively split the linked list
// into two halves, sort them independently, and then merge the two sorted halves.
//
// Approach:
// 1. Base Case: If the list is empty or has only one node (head == NULL || head->next == NULL),
//    it's already sorted, so return head.
// 2. Split: Use a `split` function (with slow/fast pointers) to find the middle node (slow).
//    Split the list into two halves: `head` (from start to slow) and `second` (from slow->next to end).
//    Set `slow->next = NULL` to terminate the first half.
// 3. Recurse: Recursively call `mergeSort(head)` for the first half and `mergeSort(second)` for the second half.
// 4. Merge: Use a `merge` function to merge the two sorted lists returned from the recursive calls.
//
// Time Complexity: O(N log N). Splitting the list takes O(N) using slow/fast pointers. Merging two sorted lists
// takes O(N). The recurrence relation is T(N) = 2T(N/2) + O(N), which resolves to O(N log N).
// Space Complexity: O(log N). This space is used by the recursion call stack. The depth of the
// recursion tree is log N.

/*
class Node {
public:
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
    // Function to split the singly linked list into two halves
    Node *split(Node *head) {
        Node *fast = head;
        Node *slow = head;

        // Move fast pointer two steps and slow pointer
        // one step until fast reaches the end or the node before the end.
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            if (fast != nullptr) {
                slow = slow->next; // slow will stop at the middle (or just before)
            }
        }

        // Split the list into two halves
        Node *temp = slow->next; // `temp` becomes the head of the second half
        slow->next = nullptr;    // Terminate the first half of the list
        return temp;             // Return the head of the second half
    }

    // Function to merge two sorted singly linked lists
    Node *merge(Node *first, Node *second) {

        // Base cases: If either list is empty, return the other list
        if (first == nullptr) return second;
        if (second == nullptr) return first;

        // Pick the node with the smaller value between the heads of the two lists
        if (first->data < second->data) {

            // The smaller node (first) becomes the head of the merged list.
            // Recursively merge the rest of the first list (first->next) with the entire second list.
            first->next = merge(first->next, second);
            return first;
        }
        else {
            // The smaller (or equal) node (second) becomes the head.
            // Recursively merge the entire first list with the rest of the second list (second->next).
            second->next = merge(first, second->next);
            return second;
        }
    }

    // Function to perform merge sort on a singly linked list
    Node *mergeSort(Node *head) {

        // Base case: if the list is empty or has only one node,
        // it's already sorted.
        if (head == nullptr || head->next == nullptr)
            return head;

        // Split the list into two halves
        Node *second = split(head); // `head` remains start of 1st half, `second` is start of 2nd half

        // Recursively sort each half
        head = mergeSort(head);
        second = mergeSort(second);

        // Merge the two now-sorted halves
        return merge(head, second);
    }
};

/*
*
* Dry Run
*
* Input: 9 -> 8 -> 5 -> 2
*
* 1. mergeSort(9 -> 8 -> 5 -> 2)
* - List is not base case.
* - split(9 -> 8 -> 5 -> 2):
* - slow=9, fast=9
* - slow=8, fast=5
* - slow=8, fast=NULL (fast->next->next is NULL)
* - Split point is after 8.
* - temp = 8->next (which is 5).
* - 8->next = NULL.
* - Returns temp (5 -> 2).
* - First half (head): 9 -> 8
* - Second half (second): 5 -> 2
*
* 2. Recurse(Left): mergeSort(9 -> 8)
* - split(9 -> 8): slow=9, fast=9 -> fast=NULL.
* - Split point after 9.
* - temp = 9->next (which is 8).
* - 9->next = NULL.
* - First half (head'): 9
* - Second half (second'): 8
* - Recurse: mergeSort(9) -> returns 9 (base case)
* - Recurse: mergeSort(8) -> returns 8 (base case)
* - merge(9, 8): 8 < 9. Returns 8 -> merge(9, NULL) -> returns 8 -> 9.
* - Call (2) returns 8 -> 9.
*
* 3. Recurse(Right): mergeSort(5 -> 2)
* - split(5 -> 2): slow=5, fast=5 -> fast=NULL.
* - Split point after 5.
* - temp = 5->next (which is 2).
* - 5->next = NULL.
* - First half (head''): 5
* - Second half (second''): 2
* - Recurse: mergeSort(5) -> returns 5 (base case)
* - Recurse: mergeSort(2) -> returns 2 (base case)
* - merge(5, 2): 2 < 5. Returns 2 -> merge(5, NULL) -> returns 2 -> 5.
* - Call (3) returns 2 -> 5.
*
* 4. Final Merge (from step 1): merge(8 -> 9, 2 -> 5) [Results from steps 2 and 3]
* - merge(8->..., 2->...): 2 < 8. Returns 2 -> merge(8->..., 5->...)
* - merge(8->..., 5->...): 5 < 8. Returns 2 -> 5 -> merge(8->..., NULL)
* - Base case: Returns 2 -> 5 -> 8 -> 9.
*
* Final Output: 2 -> 5 -> 8 -> 9
*/
```

---

## Key Insights 💡

- **Why Merge Sort for Linked Lists?** Unlike arrays, linked lists do not allow random access (O(1) indexing). Sorting algorithms like Quicksort perform poorly on linked lists (worst-case O(N^2) if partitions are bad, and pointer manipulation is complex). Merge Sort, however, works exceptionally well.
- **Finding the Middle:** The slow and fast pointer technique is the standard O(N) way to find the middle node of a linked list in a single pass.
- **Splitting and Merging:** The "split" operation is simply setting the `next` pointer of the node before the middle to `NULL`. The "merge" operation is a pointer-intensive but straightforward process of combining two sorted lists, which is the core of this algorithm. This entire process avoids the O(N) auxiliary space required by array-based merge sort, only using O(log N) stack space for recursion.

---

## Further Exploration

- [Sort a linked list of 0s, 1s and 2s](https://www.geeksforgeeks.org/problems/sort-a-linked-list-of-0s-1s-and-2s/1) (Can be done in O(N) time without full sorting)
- [Merge K Sorted Lists](https://www.geeksforgeeks.org/problems/merge-k-sorted-linked-lists/1)
- [Intersection Point in Y Shaped Linked Lists](https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1)

---

## References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/sort-a-linked-list/1)
- [Merge Sort for Linked Lists (Article)](https://www.geeksforgeeks.org/merge-sort-for-linked-list/)

---

## Author

- [imnilesh18](https://github.com/imnilesh18)

---

## Tags

![Linked List](https://img.shields.io/badge/Linked_List-blue?style=flat-square)
![Merge Sort](https://img.shields.io/badge/Merge_Sort-gray?style=flat-square)
![Sorting](https://img.shields.io/badge/Sorting-orange?style=flat-square)
![Divide and Conquer](https://img.shields.io/badge/Divide_and_Conquer-purple?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=flat-square)

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.

This repository is for educational purposes only. All problem statements and examples are derived from GeeksforGeeks.
