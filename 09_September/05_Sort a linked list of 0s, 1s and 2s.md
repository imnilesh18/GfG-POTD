# 🔗 Sort a linked list of 0s, 1s and 2s

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/given-a-linked-list-of-0s-1s-and-2s-sort-it/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG">
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge" alt="Difficulty">
    <img src="https://img.shields.io/badge/Accuracy-60.75%25-green.svg?style=for-the-badge" alt="Accuracy">
    <img src="https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge" alt="Points">
    <img src="https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge" alt="License">
</div>

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/given-a-linked-list-of-0s-1s-and-2s-sort-it/1).

---

## 📝 Problem Statement

Given the `head` of a linked list where nodes can contain values **0s**, **1s**, and **2s** only. Your task is to **rearrange** the list so that all `0s` appear at the beginning, followed by all `1s`, and all `2s` are placed at the end.

---

## Examples

### Example 1:

```
Input: head = 1 → 2 → 2 → 1 → 2 → 0 → 2 → 2
Output: 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
```

**Explanation:** All the 0s are segregated to the left end of the linked list, 2s to the right end of the list, and 1s in between.

<details>
<summary>📖 Example Breakdown</summary>

1.  **Initial List**: `1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2`
2.  **Count Occurrences**:
    - Count of `0`s: 1
    - Count of `1`s: 2
    - Count of `2`s: 5
3.  **Rebuild the List**: Traverse the list from the head again and overwrite the node data based on the counts.
    - First, write `1` zero: `0 -> ...`
    - Next, write `2` ones: `0 -> 1 -> 1 -> ...`
    - Finally, write `5` twos: `0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2`
4.  **Final Sorted List**: `0 → 1 → 1 → 2 → 2 → 2 → 2 → 2`

</details>

### Example 2:

```
Input: head = 2 → 2 → 0 → 1
Output: 0 → 1 → 2 → 2
```

**Explanation:** After arranging all the 0s, 1s, and 2s in the given format, the output will be as shown.

---

## ⛓️ Constraints

> `1 ≤ no. of nodes ≤ 10^6`
>
> `0 ≤ node->data ≤ 2`

---

## 💡 Solution Approaches

### Optimized Approach (Counting Sort)

The most intuitive way to solve this problem is to count the occurrences of 0s, 1s, and 2s in the linked list. After counting, we can then iterate through the list again from the head and overwrite the node values with the counted numbers in the correct order. This approach avoids changing the pointers and only modifies the data within the nodes.

#### C++ Solution

```cpp
// Intuition: The problem requires sorting a linked list containing only 0s, 1s, and 2s. Instead of rearranging nodes (which is complex), we can simply overwrite the node data.
// Approach:
// 1. Traverse the linked list once to count the occurrences of 0s, 1s, and 2s.
// 2. Store these counts in three separate variables (e.g., cntZero, cntOne, cntTwo).
// 3. Traverse the linked list a second time from the head.
// 4. Overwrite the node data with 0s, then 1s, and finally 2s, based on the stored counts.
// 5. Return the modified head of the linked list.
// Time Complexity: O(N), where N is the number of nodes. We perform two traversals of the list.
// Space Complexity: O(1), as we only use a few variables to store the counts, regardless of the list size.

class Solution {
  public:
    // Function to sort a linked list of 0s, 1s and 2s.
    Node* segregate(Node* head) {
        // Handle edge cases: empty list or single-node list
        if (!head || !(head->next))
            return head;

        // Initialize counts for 0s, 1s, and 2s
        int cntZero = 0, cntOne = 0, cntTwo = 0;

        // Traverse the list to count the occurrences of 0, 1, and 2
        Node* curr = head;
        while (curr) {
            if (curr->data == 0) {
                cntZero++;
            } else if (curr->data == 1) {
                cntOne++;
            } else {
                cntTwo++;
            }
            curr = curr->next; // Move to the next node
        }

        // Reset the current pointer to the head to rebuild the list
        curr = head;

        // First, overwrite nodes with all the 0s
        while (cntZero--) {
            curr->data = 0;
            curr = curr->next;
        }

        // Then, overwrite nodes with all the 1s
        while (cntOne--) {
            curr->data = 1;
            curr = curr->next;
        }

        // Finally, overwrite nodes with all the 2s
        while (cntTwo--) {
            curr->data = 2;
            curr = curr->next;
        }

        return head; // Return the head of the sorted list
    }
};

/*
*
* Dry Run
*
* Input: head = 1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
*
* 1. First Pass (Counting):
* - curr starts at head (data=1).
* - Traverse list:
* - 1 -> cntOne = 1
* - 2 -> cntTwo = 1
* - 2 -> cntTwo = 2
* - 1 -> cntOne = 2
* - 2 -> cntTwo = 3
* - 0 -> cntZero = 1
* - 2 -> cntTwo = 4
* - 2 -> cntTwo = 5
* - Final Counts: cntZero = 1, cntOne = 2, cntTwo = 5.
*
* 2. Second Pass (Overwriting):
* - curr is reset to head.
* - Fill 0s (cntZero = 1):
* - curr->data becomes 0. List: 0 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
* - curr moves to the next node.
* - Fill 1s (cntOne = 2):
* - curr->data becomes 1. List: 0 -> 1 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
* - curr moves.
* - curr->data becomes 1. List: 0 -> 1 -> 1 -> 1 -> 2 -> 0 -> 2 -> 2
* - curr moves.
* - Fill 2s (cntTwo = 5):
* - curr->data becomes 2. List: 0 -> 1 -> 1 -> 2 -> 2 -> 0 -> 2 -> 2
* - ... and so on for the next 4 nodes.
*
* Final Output: 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2
*
*/
```

#### Java Solution

```java
// Intuition: The problem requires sorting a linked list containing only 0s, 1s, and 2s. Instead of rearranging nodes (which is complex), we can simply overwrite the node data.
// Approach:
// 1. Traverse the linked list once to count the occurrences of 0s, 1s, and 2s.
// 2. Store these counts in three separate variables (e.g., cntZero, cntOne, cntTwo).
// 3. Traverse the linked list a second time from the head.
// 4. Overwrite the node data with 0s, then 1s, and finally 2s, based on the stored counts.
// 5. Return the modified head of the linked list.
// Time Complexity: O(N), where N is the number of nodes. We perform two traversals of the list.
// Space Complexity: O(1), as we only use a few variables to store the counts, regardless of the list size.

class Solution {
    public Node segregate(Node head) {
       // Handle edge cases: empty list or single-node list
       if (head == null || head.next == null)
            return head;

        // Initialize counts for 0s, 1s, and 2s
        int cntZero = 0, cntOne = 0, cntTwo = 0;

        // Traverse the list to count the occurrences of 0, 1, and 2
        Node curr = head;
        while (curr != null) {
            if (curr.data == 0) {
                cntZero++;
            } else if (curr.data == 1) {
                cntOne++;
            } else {
                cntTwo++;
            }
            curr = curr.next; // Move to the next node
        }

        // Reset the current pointer to the head to rebuild the list
        curr = head;

        // First, overwrite nodes with all the 0s
        while (cntZero-- > 0) {
            curr.data = 0;
            curr = curr.next;
        }

        // Then, overwrite nodes with all the 1s
        while (cntOne-- > 0) {
            curr.data = 1;
            curr = curr.next;
        }

        // Finally, overwrite nodes with all the 2s
        while (cntTwo-- > 0) {
            curr.data = 2;
            curr = curr.next;
        }

        return head; // Return the head of the sorted list
    }
}

/*
*
* Dry Run
*
* Input: head = 1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
*
* 1. First Pass (Counting):
* - curr starts at head (data=1).
* - Traverse list:
* - 1 -> cntOne = 1
* - 2 -> cntTwo = 1
* - 2 -> cntTwo = 2
* - 1 -> cntOne = 2
* - 2 -> cntTwo = 3
* - 0 -> cntZero = 1
* - 2 -> cntTwo = 4
* - 2 -> cntTwo = 5
* - Final Counts: cntZero = 1, cntOne = 2, cntTwo = 5.
*
* 2. Second Pass (Overwriting):
* - curr is reset to head.
* - Fill 0s (cntZero = 1):
* - curr.data becomes 0. List: 0 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
* - curr moves to the next node.
* - Fill 1s (cntOne = 2):
* - curr.data becomes 1. List: 0 -> 1 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
* - curr moves.
* - curr.data becomes 1. List: 0 -> 1 -> 1 -> 1 -> 2 -> 0 -> 2 -> 2
* - curr moves.
* - Fill 2s (cntTwo = 5):
* - curr.data becomes 2. List: 0 -> 1 -> 1 -> 2 -> 2 -> 0 -> 2 -> 2
* - ... and so on for the next 4 nodes.
*
* Final Output: 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2
*
*/
```

---

## 🔑 Key Insights

- **Data Overwriting vs. Pointer Manipulation**: For this specific problem, since the values are limited to `0`, `1`, and `2`, modifying the data of the nodes is much simpler and more efficient than changing the `next` pointers to rearrange the nodes themselves.
- **Two-Pass Approach**: The problem can be solved cleanly in two linear passes. The first pass gathers all necessary information (the counts), and the second pass applies the changes. This leads to an optimal time complexity of O(N).
- **Constant Space**: No additional data structures that scale with the input size are needed. We only use a fixed number of integer variables for counting, making the space complexity O(1).

---

## 🚀 Further Exploration

- **Dutch National Flag Problem**: Try solving this problem for an array instead of a linked list. This is a classic algorithm problem.
- **Single Pass Solution**: Can you solve this problem in a single traversal? (Hint: You would need to manipulate the `next` pointers by creating three dummy lists for 0s, 1s, and 2s, and then merging them.)
- [Sort a linked list of 0s, 1s and 2s by changing links](https://www.geeksforgeeks.org/sort-a-linked-list-of-0s-1s-and-2s-by-changing-links/)

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/given-a-linked-list-of-0s-1s-and-2s-sort-it/1)

---

## 👨‍💻 Author

- **GitHub**: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div align="center">
    <img src="https://img.shields.io/badge/linked--list-9cf?style=for-the-badge" alt="linked-list">
    <img src="https://img.shields.io/badge/sorting-f39?style=for-the-badge" alt="sorting">
    <img src="https://img.shields.io/badge/data--structures-34a?style=for-the-badge" alt="data-structures">
    <img src="https://img.shields.io/badge/geeksforgeeks-298D46?style=for-the-badge" alt="geeksforgeeks">
    <img src="https://img.shields.io/badge/cpp-00599C?style=for-the-badge" alt="cpp">
    <img src="https://img.shields.io/badge/java-ED8B00?style=for-the-badge" alt="java">
</div>

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A gentle reminder**: The solutions in this repository are for educational purposes. They are meant to be used as a reference and a learning tool. Always try to solve the problem on your own first.
