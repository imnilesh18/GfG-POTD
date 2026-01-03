# 🔗 Flattening a Linked List

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-51.53%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

<br>

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p>This repository and its content are intended solely for educational purposes.<br>
  Solutions are provided for learning, practice, and reference only.<br>
  Problem statement and test cases are based on the GeeksforGeeks problem.</p>
</div>

---

## 📜 Problem Statement

Given a Linked List of size **N**, where every node represents a sub-linked-list and contains two pointers:

1.  **Next Pointer (`next`)**: Points to the next node in the main list (horizontal).
2.  **Bottom Pointer (`bottom`)**: Points to a sub-linked-list where the current node is the head (vertical).

Each of the sub-linked-lists nodes and the head nodes are **sorted in ascending order** based on their data. Your task is to **flatten** the linked list such that all the nodes appear in a single level while maintaining the sorted order.

> **Note:**
>
> 1. `↓` represents the bottom pointer and `→` represents the next pointer.
> 2. The flattened list will be printed using the **bottom** pointer instead of the next pointer.

---

## 📊 Examples

### Example 1

<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/700192/Web/Other/blobid0_1756383797.webp" alt="Example 1 Illustration" width="500"/>
</div>

```text
Output: 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 40 -> 45.

Explanation:
Bottom pointer of 5 is pointing to 7.
Bottom pointer of 7 is pointing to 8.
Bottom pointer of 10 is pointing to 20 and so on.
So, after flattening the linked list the sorted list will be
5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 40 -> 45.

```

### Example 2

<div align="center">
<img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/700192/Web/Other/blobid1_1756383851.webp" alt="Example 2 Illustration" width="400"/>
</div>

```text
Output: 5 -> 7 -> 8 -> 10 -> 19 -> 22 -> 28 -> 30 -> 50

Explanation:
Bottom pointer of 5 is pointing to 7.
Bottom pointer of 7 is pointing to 8.
Bottom pointer of 8 is pointing to 30 and so on.
So, after flattening the linked list the sorted list will be
5 -> 7 -> 8 -> 10 -> 19 -> 22 -> 28 -> 30 -> 50.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's visualize the merging process for a simpler case:

1. **Structure**:

- List 1 (Head 5): `5 -> 7 -> 8 -> 30` (Vertical)
- List 2 (Head 10): `10 -> 20` (Vertical)
- List 3 (Head 19): `19 -> 22 -> 50` (Vertical)

2. **Recursion**:

- We go deep to the end. First, we merge List 2 (`10`) and List 3 (`19`).
- The result of merging `10` and `19` becomes a single sorted vertical list: `10->19->20->22->50`.

3. **Final Merge**:

- Now we merge List 1 (`5`) with the result from the previous step (`10`).
- Compare `5` vs `10` -> `5` comes first.
- Compare `7` vs `10` -> `7`.
- Compare `8` vs `10` -> `8`.
- Compare `30` vs `10` -> `10`.
- ... and so on.

4. **Result**: The flattened list is linked via bottom pointers.

</details>

---

## 🛑 Constraints

$$0 \le n \le 100$$ $$1 \le \text{number of nodes in sub-linked list}(m_i) \le 50$$ $$1 \le \text{node->data} \le 10^4$$

---

## 💡 Solution Approach

### Recursive Merge Strategy

#### Intuition

The problem asks us to flatten a 2D linked list structure into a 1D list sorted by value. Since every vertical sub-list is already sorted, this problem reduces to **merging sorted linked lists**.
Instead of merging all at once, we can use recursion to merge the lists two at a time, starting from the end. We assume `flatten(head->next)` will return a fully sorted flattened list of the "right side", and we simply merge the current list (`head`) with that result.

#### Approach

1. **Base Case**: If `head` is `NULL` or `head->next` is `NULL`, return `head`. There is nothing to flatten.
2. **Recursive Step**: Recursively call `flatten` on `head->next` to solve the sub-problem for the rest of the list. Store this result in a pointer `head2`.
3. **Merge**: Use a standard `mergeTwoLists` function to merge the current vertical list (`head`) and the flattened right side (`head2`).

- _Important_: The output must be linked using `bottom` pointers, so the merge logic connects nodes via `.bottom` instead of `.next`.

4. **Return**: The result of the merge becomes the new head for this level of recursion.

#### Complexity Analysis

- **Time Complexity**: - Where is the number of horizontal nodes and is the average number of nodes in vertical lists. In the worst case, we might visit every node multiple times during merge operations, but conceptually we process all nodes.
- **Space Complexity**: - Recursion stack space. In the worst case (skewed tree/list merge), the depth of recursion for merging could be proportional to the total number of nodes if not carefully implemented, but strictly for the `flatten` calls, the depth is . The merge function also uses stack space.

```cpp
// Intuition: Use recursion to process the list from right to left. We flatten the 'rest' of the list first, then merge the current vertical list with the flattened result using the bottom pointer.
// Approach: Recursively go to the last node, then merge two sorted lists (current and the result of the recursion) using the bottom pointers.
// Time Complexity: O(N * M) where N is the number of head nodes and M is the average length of the vertical lists.
// Space Complexity: O(N * M) due to the recursion stack used in merging and flattening (worst case total number of nodes).

/*
class Node {
public:
    int data;
    Node* next;
    Node* bottom;

    Node(int x) {
        data = x;
        next = NULL;
        bottom = NULL;
    }
};
*/

class Solution {
  public:

    // Helper function to merge two sorted linked lists using the bottom pointer
    Node* mergeTwoLists(Node* l1, Node* l2) {
        // If first list is empty, return the second list
        if(!l1) {
            return l2;
        }
        // If second list is empty, return the first list
        if(!l2){
            return l1;
        }

        Node* result;
        // Compare data to pick the smaller node
        if(l1->data < l2->data) {
            result = l1;
            // Recursively merge the remaining part of l1 with l2
            result->bottom = mergeTwoLists(result->bottom, l2);
        } else {
            result = l2;
            // Recursively merge l1 with the remaining part of l2
            result->bottom = mergeTwoLists(l1, result->bottom);
        }
        // Return the head of the merged list
        return result;
    }

    // Main function to flatten the linked list
    Node *flatten(Node *head) {
        // Base case: if list is empty or last node reached
        if(head == NULL || head->next == NULL) {
            return head;
        }

        // Recursively flatten the rest of the list (next pointer)
        Node* head2 = flatten(head->next);

        // Merge the current list (head) with the flattened rest (head2)
        // This effectively flattens the list by merging from right to left
        return mergeTwoLists(head, head2);
    }
};

/*
*
* Dry Run
* Input:
* 5 -> 10 (Horizontal)
* |    |
* 7    20 (Vertical)
* |
* 8
*
* 1. flatten(5) called.
* 2. Calls flatten(10).
* 3. flatten(10) checks next. next is NULL. Returns 10.
* (Currently head2 = 10 -> 20)
* 4. Back in flatten(5): calls mergeTwoLists(5, 10).
* - Compare 5 vs 10. Pick 5. result = 5.
* - Recurse: merge(7, 10).
* - Compare 7 vs 10. Pick 7. result->bottom = 7.
* - Recurse: merge(8, 10).
* - Compare 8 vs 10. Pick 8. result->bottom = 8.
* - Recurse: merge(NULL, 10).
* - l1 is NULL, return 10.
* - Connection: 8->bottom = 10.
* 5. Final structure from merge: 5 -> 7 -> 8 -> 10 -> 20.
* 6. Returns 5.
*/

```

---

## 🧠 Key Insights

- **Recursion Magic**: The problem simplifies drastically if you believe in the "Recursion Leap of Faith". Assume `flatten(head->next)` gives you a perfect list. Your only job is to merge that with your current vertical list.
- **Merge Sort Variant**: This is essentially the merge step of Merge Sort applied iteratively or recursively across the columns of the linked list.
- **Pointer Management**: The tricky part is realizing we ignore `next` pointers in the final result and chain everything using `bottom` pointers.

---

## 🔗 Further Exploration

- [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)
- [Sort List](https://leetcode.com/problems/sort-list/)
- [Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)

---

## 📝 References

- [GFG Problem Link](https://www.geeksforgeeks.org/problems/flattening-a-linked-list/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

<div>
<p>This project is licensed under the <a href="https://opensource.org/licenses/MIT">MIT License</a>.</p>
<p><b>⚠️ Educational Use Only:</b> This repository is intended for learning and reference purposes.</p>
</div>
