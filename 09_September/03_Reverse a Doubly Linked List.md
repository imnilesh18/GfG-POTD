# 🔗 Reverse a Doubly Linked List

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/reverse-a-doubly-linked-list/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-70.38%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/reverse-a-doubly-linked-list/1).

</div>

---

## Problem Statement

You are given the `head` of a **doubly linked list**. You have to **reverse** the doubly linked list and return its new `head`.

### Examples

**Example 1:**

```
Input:
LinkedList: 3 <--> 4 <--> 5
Output: 5 <--> 4 <--> 3
Explanation: After reversing the given doubly linked list, the new list will be 5 <--> 4 <--> 3.
```

**Example 2:**

```
Input:
LinkedList: 75 <--> 122 <--> 59 <--> 196
Output: 196 <--> 59 <--> 122 <--> 75
Explanation: After reversing the given doubly linked list, the new list will be 196 <--> 59 <--> 122 <--> 75.
```

<details>
<summary>📖 Example 1 Breakdown</summary>

Let's walk through the first example: `3 <-> 4 <-> 5`

1.  **Start at the head (node 3):**

    - `currNode` is `3`.
    - Its `next` is `4` and `prev` is `NULL`.
    - Swap them: `currNode->next` becomes `NULL`, `currNode->prev` becomes `4`.
    - The list is now partially `NULL <- 3 -> 4`.
    - Move to the next node in the original list (which was `4`).

2.  **Move to node 4:**

    - `currNode` is `4`.
    - Its `next` is `5` and `prev` is `3`.
    - Swap them: `currNode->next` becomes `3`, `currNode->prev` becomes `5`.
    - The list structure is now `NULL <- 3 <-> 4 -> 5`.
    - Move to the next node in the original list (which was `5`).

3.  **Move to node 5:**

    - `currNode` is `5`.
    - Its `next` is `NULL` and `prev` is `4`.
    - Swap them: `currNode->next` becomes `4`, `currNode->prev` becomes `NULL`.
    - The list is fully reversed: `5 <-> 4 <-> 3`.
    - The loop terminates as we move to what was originally the next node (`NULL`).

4.  **Identify New Head:** The last node we processed before `NULL` was `5`. This is our new head.

5.  **Return `5`**. The final reversed list is `5 <-> 4 <-> 3`.

</details>

---

## Constraints

> `1 ≤ number of nodes ≤ 10^6` > `0 ≤ node->data ≤ 10^4`

---

## Solution Approaches

The core idea is to traverse the list while swapping the `next` and `prev` pointers of each node.

### C++ Solution

```cpp
// Intuition: The fundamental idea is to iterate through the doubly linked list and, for each node, swap its `prev` and `next` pointers. This inverts the direction of all links. The new head of the list will be the tail of the original list.
// Approach: We use a `currNode` pointer to traverse the list. In each step, we temporarily store the `prev` pointer, then swap the `next` and `prev` pointers of the `currNode`. Finally, we move `currNode` to the next node in the original list (which, after the swap, is pointed to by `currNode->prev`). The `prevNode` pointer keeps track of the last processed node, which will eventually become the new head.
// Time Complexity: O(N), where N is the number of nodes in the list. We perform a single pass through the linked list.
// Space Complexity: O(1), as we only use a constant amount of extra space for pointers (`prevNode`, `currNode`) regardless of the list size.

class Solution {
  public:
    Node *reverse(Node *head) {
        // If the list is empty or has only one node, no reversal is needed.
        if (head == nullptr || head->next == nullptr)
            return head;

        Node *prevNode = NULL;
        Node *currNode = head;

        // Traverse the list and reverse the links for each node.
        while (currNode != nullptr) {

            // Store the original previous node.
            prevNode = currNode->prev;

            // Swap the next and prev pointers.
            currNode->prev = currNode->next;
            currNode->next = prevNode;

            // Move to the next node in the original list (which is now `currNode->prev`).
            currNode = currNode->prev;
        }

        // The new head is the `prev` of the last node (which was the original tail).
        return prevNode->prev;
    }
};

/*
*
* Dry Run
*
* Initial List: 3 <-> 4 <-> 5 -> NULL
*
* Iteration 1:
* - currNode = 3
* - prevNode = 3->prev (NULL)
* - 3->prev = 3->next (4)
* - 3->next = prevNode (NULL)
* - Resulting node links: NULL <- 3 -> 4
* - currNode moves to currNode->prev (4)
*
* Iteration 2:
* - currNode = 4
* - prevNode = 4->prev (3)
* - 4->prev = 4->next (5)
* - 4->next = prevNode (3)
* - Resulting node links: 3 <- 4 -> 5
* - currNode moves to currNode->prev (5)
*
* Iteration 3:
* - currNode = 5
* - prevNode = 5->prev (4)
* - 5->prev = 5->next (NULL)
* - 5->next = prevNode (4)
* - Resulting node links: 4 <- 5 -> NULL
* - currNode moves to currNode->prev (NULL)
*
* Loop ends. The last non-null node was 5. `prevNode` is pointing to the node before it (node 4).
* The new head is `prevNode->prev`, which is 5.
* Final List: 5 <-> 4 <-> 3
*
*/
```

### Java Solution

```java
// Intuition: To reverse a doubly linked list, we need to swap the `prev` and `next` pointers for every node. The last node of the original list becomes the first node of the reversed list.
// Approach: We iterate through the list with a `currNode`. A `prevNode` pointer is used to keep track of the previously visited node. For each `currNode`, we swap its `next` and `prev` references. After the swap, we advance `currNode` to the next node in the original list, which is now accessible via `currNode.prev`. The loop continues until the end of the list. The new head will be the `prev` of the final `currNode` (which is null).
// Time Complexity: O(N), as the algorithm requires a single traversal of the linked list.
// Space Complexity: O(1), because the reversal is done in-place using only a few extra pointers.
class Solution {
    public Node reverse(Node head) {
        // Base case: if the list is empty or has a single node, return it.
        if (head == null || head.next == null) {
            return head;
        }

        Node currNode = head;
        Node prevNode = null;

        // Traverse the list, swapping pointers at each node.
        while (currNode != null) {

            // Store the original previous node.
            prevNode = currNode.prev;

            // Swap the next and prev pointers.
            currNode.prev = currNode.next;
            currNode.next = prevNode;

            // Move to the next node in the original sequence (now the previous).
            currNode = currNode.prev;
        }

        // After the loop, `prevNode` points to the second-to-last node of the original list.
        // The new head is `prevNode.prev`.
        head = prevNode.prev;

        return head;
    }
}

/*
*
* Dry Run
*
* Initial List: 75 <-> 122 <-> 59 -> NULL
*
* Iteration 1 (currNode = 75):
* - prevNode = 75.prev (null)
* - 75.prev = 75.next (122)
* - 75.next = prevNode (null)
* - currNode becomes 75.prev (122)
*
* Iteration 2 (currNode = 122):
* - prevNode = 122.prev (75)
* - 122.prev = 122.next (59)
* - 122.next = prevNode (75)
* - currNode becomes 122.prev (59)
*
* Iteration 3 (currNode = 59):
* - prevNode = 59.prev (122)
* - 59.prev = 59.next (null)
* - 59.next = prevNode (122)
* - currNode becomes 59.prev (null)
*
* Loop terminates. `prevNode` is pointing to 122.
* The new head is `prevNode.prev`, which is 59.
* Final List: 59 <-> 122 <-> 75
*
*/
```

---

## 🔑 Key Insights

- The core of the solution is the **in-place swapping** of the `next` and `prev` pointers.
- A temporary variable (in our case, `prevNode`) is crucial to hold a reference to the original `prev` pointer before it's overwritten.
- After the loop finishes, the pointer that was tracking the "previous" node will be at the second-to-last node of the original list. The new head is the `prev` of that node.

---

## 🚀 Further Exploration

- **Reverse a Singly Linked List:** A simpler version of this problem.
- **Reverse a Linked List in groups of size k:** A more complex variation where you reverse chunks of the list.
- **Check if a Doubly Linked List is a Palindrome:** This problem can be solved by comparing nodes from both ends.

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/reverse-a-doubly-linked-list/1)
- [Article on Reversing a Doubly Linked List](https://www.geeksforgeeks.org/reverse-a-doubly-linked-list/)

---

## 🧑‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`doubly-linked-list` `linked-list` `reversal` `geeksforgeeks` `pointer-manipulation`

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A gentle reminder that this is for educational purposes. Always try to solve problems on your own first!**
