# 🔗 Linked List Group Reverse

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-296236?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-57.08%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/reverse-a-linked-list-in-groups-of-given-size/1).

</div>

---

## Problem Statement

You are given the **head** of a Singly linked list. You have to **reverse** every **k** node in the linked list and return the head of the modified list.

**Note**: If the number of nodes is not a multiple of `k` then the left-out nodes at the end, should be considered as a group and must be **reversed**.

---

## Examples

<details>
<summary><strong>📖 Example 1 Breakdown</strong></summary>

**Input:**

```
k = 2
Linked List: 1 -> 2 -> 3 -> 4 -> 5 -> 6
```

**Output:**

```
2 -> 1 -> 4 -> 3 -> 6 -> 5
```

**Walkthrough:**

1.  The first group of size `k=2` is `1 -> 2`. After reversing, it becomes `2 -> 1`. The new head of the entire list is now node `2`.
2.  The next group is `3 -> 4`. Reversing it gives `4 -> 3`. We connect the tail of the first group (node `1`) to the head of this new group (node `4`). The list is now `2 -> 1 -> 4 -> 3`.
3.  The final group is `5 -> 6`. Reversing it gives `6 -> 5`. We connect the tail of the previous group (node `3`) to the head of this group (node `6`).
4.  The final modified list is `2 -> 1 -> 4 -> 3 -> 6 -> 5`.

</details>

<details>
<summary><strong>Example 2</strong></summary>

**Input:**

```
k = 4
Linked List: 1 -> 2 -> 3 -> 4 -> 5 -> 6
```

**Output:**

```
4 -> 3 -> 2 -> 1 -> 6 -> 5
```

**Explanation:**
The first group `1 -> 2 -> 3 -> 4` is reversed to `4 -> 3 -> 2 -> 1`. The second group `5 -> 6` is smaller than `k`, but it's the last group, so it's also reversed to `6 -> 5`. The two groups are then connected.

</details>

---

## Constraints

<div align="center">

| Constraint            | Value Range           |
| --------------------- | --------------------- |
| `size of linked list` | `1` ≤ `size` ≤ `10^5` |
| `node->data`          | `0` ≤ `data` ≤ `10^6` |
| `k`                   | `1` ≤ `k` ≤ `size`    |

</div>

---

## Solution Approaches

### Iterative Approach

The core idea is to traverse the linked list, processing `k` nodes at a time. For each group of `k` nodes, we perform a standard iterative reversal. The key challenge is to correctly link the reversed groups together. We use a `tail` pointer to keep track of the end of the _previously_ reversed group, allowing us to connect it to the head of the _newly_ reversed group.

---

### C++ Solution

```cpp
// Intuition: The problem requires reversing a linked list in groups of 'k'. The core idea is to iterate through the linked list,
// take 'k' nodes at a time, reverse that group, and then connect it to the previously reversed group.
// Approach:
// 1. Initialize pointers: `curr` to traverse the list, `newHead` to store the final head, and `tail` to connect the reversed groups.
// 2. Use a `while` loop to process the list as long as `curr` is not null.
// 3. Inside the loop, for each group:
//    a. Store the head of the current group (`groupHead`).
//    b. Reverse `k` nodes using the standard iterative reversal method (with `prev`, `curr`, `nextNode`).
//    c. After reversing, `prev` will be the new head of the reversed group.
//    d. If this is the first group (`newHead` is null), set `newHead` to `prev`.
//    e. If it's not the first group, connect the tail of the *previous* group (`tail`) to the head of the *current* reversed group (`prev`).
//    f. Update `tail` to be the end of the current reversed group, which was its original head (`groupHead`).
// 4. Return `newHead`.
// Time Complexity: O(N), where N is the number of nodes in the linked list. Each node is visited exactly once.
// Space Complexity: O(1), as we only use a constant number of extra pointers.

class Solution {
  public:
    Node *reverseKGroup(Node *head, int k) {
        if (head == nullptr) {
            return head; // Return if the list is empty.
        }

        Node *curr = head;
        Node *newHead = nullptr; // This will become the new head of the modified list.
        Node *tail = nullptr;    // This will point to the tail of the last reversed group.

        while (curr != nullptr) {
            Node *groupHead = curr; // The starting node of the current group.
            Node *prev = nullptr;
            Node *nextNode = nullptr;
            int count = 0;

            // Reverse the nodes in the current group of size up to k.
            while (curr != nullptr && count < k) {
                nextNode = curr->next;
                curr->next = prev;
                prev = curr;
                curr = nextNode;
                count++;
            }

            // If newHead is null, it means this is the first group.
            // Its reversed head (prev) becomes the new head of the entire list.
            if (newHead == nullptr) {
                newHead = prev;
            }

            // Connect the previous group to the current reversed group.
            if (tail != nullptr) {
                tail->next = prev;
            }

            // The tail of the current reversed group is its original head (`groupHead`).
            // Update the main `tail` pointer to this node for the next iteration.
            tail = groupHead;
        }

        return newHead;
    }
};

/*
*
* Dry Run
*
* Input: head = 1 -> 2 -> 3 -> 4 -> 5 -> 6, k = 2
*
* --- First Iteration (curr = 1) ---
* groupHead = 1
* Reverse first 2 nodes: 1 -> 2 becomes 2 -> 1
* - prev = 2 (head of the reversed group)
* - curr = 3 (start of the next group)
* - groupHead = 1 (tail of the reversed group)
* newHead is null, so newHead = prev = 2.
* tail is null, no connection needed yet.
* Update tail = groupHead = 1.
* List state: newHead -> 2 -> 1, tail -> 1, curr -> 3
*
* --- Second Iteration (curr = 3) ---
* groupHead = 3
* Reverse next 2 nodes: 3 -> 4 becomes 4 -> 3
* - prev = 4 (head of this reversed group)
* - curr = 5
* - groupHead = 3 (tail of this reversed group)
* newHead is not null.
* Connect previous group: tail->next = prev => 1->next = 4.
* List becomes: 2 -> 1 -> 4 -> 3
* Update tail = groupHead = 3.
* List state: newHead -> 2 -> 1 -> 4 -> 3, tail -> 3, curr -> 5
*
* --- Third Iteration (curr = 5) ---
* groupHead = 5
* Reverse next 2 nodes: 5 -> 6 becomes 6 -> 5
* - prev = 6
* - curr = nullptr
* - groupHead = 5
* newHead is not null.
* Connect previous group: tail->next = prev => 3->next = 6.
* List becomes: 2 -> 1 -> 4 -> 3 -> 6 -> 5
* Update tail = groupHead = 5.
* List state: newHead -> 2 -> 1 -> 4 -> 3 -> 6 -> 5, tail -> 5, curr -> nullptr
*
* --- Loop Ends (curr is nullptr) ---
*
* Return newHead, which points to 2.
* Final List: 2 -> 1 -> 4 -> 3 -> 6 -> 5
*
*/
```

---

### Java Solution

```java
// Intuition: The problem requires reversing a linked list in groups of 'k'. The core idea is to iterate through the linked list,
// take 'k' nodes at a time, reverse that group, and then connect it to the previously reversed group.
// Approach:
// 1. Initialize pointers: `curr` to traverse the list, `newHead` to store the final head, and `tail` to connect the reversed groups.
// 2. Use a `while` loop to process the list as long as `curr` is not null.
// 3. Inside the loop, for each group:
//    a. Store the head of the current group (`groupHead`).
//    b. Reverse `k` nodes using the standard iterative reversal method (with `prev`, `curr`, `nextNode`).
//    c. After reversing, `prev` will be the new head of the reversed group.
//    d. If this is the first group (`newHead` is null), set `newHead` to `prev`.
//    e. If it's not the first group, connect the tail of the *previous* group (`tail`) to the head of the *current* reversed group (`prev`).
//    f. Update `tail` to be the end of the current reversed group, which was its original head (`groupHead`).
// 4. Return `newHead`.
// Time Complexity: O(N), where N is the number of nodes in the linked list. Each node is visited exactly once.
// Space Complexity: O(1), as we only use a constant number of extra pointers.

class Solution {
    public Node reverseKGroup(Node head, int k) {
        if (head == null) {
            return head; // Return if the list is empty.
        }

        Node curr = head;
        Node newHead = null; // This will become the new head of the modified list.
        Node tail = null;    // This will point to the tail of the last reversed group.

        while (curr != null) {
            Node groupHead = curr; // The starting node of the current group.
            Node prev = null;
            Node nextNode = null;
            int count = 0;

            // Reverse the nodes in the current group of size up to k.
            while (curr != null && count < k) {
                nextNode = curr.next;
                curr.next = prev;
                prev = curr;
                curr = nextNode;
                count++;
            }

            // If newHead is null, it means this is the first group.
            // Its reversed head (prev) becomes the new head of the entire list.
            if (newHead == null) {
                newHead = prev;
            }

            // Connect the previous group to the current reversed group.
            if (tail != null) {
                tail.next = prev;
            }

            // The tail of the current reversed group is its original head (`groupHead`).
            // Update the main `tail` pointer to this node for the next iteration.
            tail = groupHead;
        }

        return newHead;
    }
}
/*
*
* Dry Run
*
* Input: head = 1 -> 2 -> 3 -> 4 -> 5 -> 6, k = 2
*
* --- First Iteration (curr = 1) ---
* groupHead = 1
* Reverse first 2 nodes: 1 -> 2 becomes 2 -> 1
* - prev = 2 (head of the reversed group)
* - curr = 3 (start of the next group)
* - groupHead = 1 (tail of the reversed group)
* newHead is null, so newHead = prev = 2.
* tail is null, no connection needed yet.
* Update tail = groupHead = 1.
* List state: newHead -> 2 -> 1, tail -> 1, curr -> 3
*
* --- Second Iteration (curr = 3) ---
* groupHead = 3
* Reverse next 2 nodes: 3 -> 4 becomes 4 -> 3
* - prev = 4 (head of this reversed group)
* - curr = 5
* - groupHead = 3 (tail of this reversed group)
* newHead is not null.
* Connect previous group: tail.next = prev => 1.next = 4.
* List becomes: 2 -> 1 -> 4 -> 3
* Update tail = groupHead = 3.
* List state: newHead -> 2 -> 1 -> 4 -> 3, tail -> 3, curr -> 5
*
* --- Third Iteration (curr = 5) ---
* groupHead = 5
* Reverse next 2 nodes: 5 -> 6 becomes 6 -> 5
* - prev = 6
* - curr = null
* - groupHead = 5
* newHead is not null.
* Connect previous group: tail.next = prev => 3.next = 6.
* List becomes: 2 -> 1 -> 4 -> 3 -> 6 -> 5
* Update tail = groupHead = 5.
* List state: newHead -> 2 -> 1 -> 4 -> 3 -> 6 -> 5, tail -> 5, curr -> null
*
* --- Loop Ends (curr is null) ---
*
* Return newHead, which points to 2.
* Final List: 2 -> 1 -> 4 -> 3 -> 6 -> 5
*
*/
```

---

## Key Insights

- **Group-by-Group Reversal:** The problem is solved by breaking it down into smaller, manageable subproblems: reversing each group of `k` nodes.
- **Connecting the Dots:** The most crucial part of the iterative solution is managing the connections between the reversed groups. The `tail` pointer, which always points to the last node of the most recently processed group, is essential for this.
- **Handling the First Group:** A special check (`if (newHead == nullptr)`) is needed to correctly assign the head of the _first_ reversed group as the new head for the entire list.
- **Final Un-even Group**: The inner `while` loop `(curr != nullptr && count < k)` naturally handles the last group, even if it has fewer than `k` nodes. It simply reverses whatever nodes are left.

---

## Further Exploration

- [Reverse a Doubly Linked List in groups of given size](https://www.geeksforgeeks.org/reverse-doubly-linked-list-groups-given-size/)
- [Reverse alternate K nodes in a Singly Linked List](https://www.geeksforgeeks.org/reverse-alternate-k-nodes-in-a-singly-linked-list/)
- [Sort a linked list of 0s, 1s and 2s](https://www.geeksforgeeks.org/problems/sort-a-linked-list-of-0s-1s-and-2s/1)

---

## References

- **Original Problem:** [GeeksforGeeks | Reverse a Linked List in Groups of Given Size](https://www.geeksforgeeks.org/problems/reverse-a-linked-list-in-groups-of-given-size/1)

---

## Author

- **Connect with me:** [imnilesh18](https://github.com/imnilesh18)

---

## Tags

<div align="center">

![Linked List](https://img.shields.io/badge/Linked_List-blue?style=for-the-badge)
![Reversal](https://img.shields.io/badge/Reversal-orange?style=for-the-badge)
![Iterative](https://img.shields.io/badge/Iterative-purple?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge)

</div>

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder:** The solutions and content in this repository are for educational purposes only. They are meant to help you learn, practice, and understand different problem-solving techniques. Please use them responsibly.
