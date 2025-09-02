# 🔗 Swap Kth nodes from ends

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-35.5%25-red.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/swap-kth-node-from-beginning-and-kth-node-from-end-in-a-singly-linked-list/1).

---

## 📝 Problem Statement

Given the **head** of a singly linked list and an integer **k**. **Swap** the kth node (1-based index) from the **beginning** and the kth node from the **end** of the linked list. Return the head of the final formed list and if it's **not possible** to swap the nodes return the **original** list.

---

## 🖼️ Examples

### Example 1:

**Input:**
```
k = 1
Linked List: 1 -> 2 -> 3 -> 4 -> 5
```
<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/701070/Web/Other/blobid0_1755953423.webp" alt="Example 1 Input" width="400">
</div>

**Output:**
```
5 -> 2 -> 3 -> 4 -> 1
```
<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/701070/Web/Other/blobid1_1755953433.webp" alt="Example 1 Output" width="400">
</div>

**Explanation:**
Here k = 1, hence after swapping the 1st node from the beginning and end the new list will be 5 -> 2 -> 3 -> 4 -> 1.

<details>
<summary>📖 Example Breakdown</summary>

1.  **Identify nodes:**
    * **1st node from beginning:** `1`
    * **1st node from end:** `5`
2.  **Swap:**
    * The node `5` now points to `2`.
    * The node `4` now points to `1`.
    * The node `1` points to `null` (end of the list).
3.  **Result:** The new head is `5`, resulting in the list `5 -> 2 -> 3 -> 4 -> 1`.
</details>

### Example 2:

**Input:**
```
k = 2
Linked List: 5 -> 10 -> 8 -> 5 -> 9 -> 3
```
<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/701070/Web/Other/blobid2_1755953453.webp" alt="Example 2 Input" width="400">
</div>

**Output:**
```
5 -> 9 -> 8 -> 5 -> 10 -> 3
```
<div align="center">
  <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/701070/Web/Other/blobid3_1755953462.webp" alt="Example 2 Output" width="400">
</div>

**Explanation:**
Here k = 2, hence after swapping the 2nd node from the beginning and end the new list will be 5 -> 9 -> 8 -> 5 -> 10 -> 3.

---

## ⛓️ Constraints

> `1 ≤ list size ≤ 10^4`
> `1 ≤ node->data ≤ 10^6`
> `1 ≤ k ≤ 10^4`

---

## 💡 Solution Approaches

### Optimized Approach

The core idea is to first find the length of the linked list. With the length, we can easily locate the kth node from the beginning and the kth node from the end (which is the `(length - k + 1)`th node from the beginning). We also need to keep track of the nodes *previous* to the ones we want to swap. After identifying these four nodes (the two to be swapped and their predecessors), we can carefully rewire their `next` pointers to perform the swap. Special handling is required if `k=1` or `k=length` as the head of the list will change.

#### C++ Solution
```cpp
// Intuition: To swap the kth nodes from both ends, we first need to find them. By calculating the list's length, 'n', we can pinpoint the kth node from the start and the (n - k + 1)th node from the start (which is the kth from the end). The swap involves carefully re-linking the previous nodes to the swapped nodes and updating the swapped nodes' next pointers.
// Approach:
// 1. Calculate the total number of nodes 'n' in the list.
// 2. Handle edge cases: If k > n or if the two nodes to be swapped are the same (k == n - k + 1), return the original head.
// 3. Find the kth node from the beginning (let's call it 'x') and its previous node ('prevX').
// 4. Find the kth node from the end (i.e., (n - k + 1)th from the beginning, let's call it 'y') and its previous node ('prevY').
// 5. Adjust the 'next' pointers:
//    - If prevX exists, its 'next' should point to 'y'.
//    - If prevY exists, its 'next' should point to 'x'.
// 6. Swap the 'next' pointers of 'x' and 'y'.
// 7. Update the head of the list if k was 1 or n.
// 8. Return the new head.
// Time Complexity: O(N), where N is the number of nodes. We traverse the list once to find the length and then again to find the nodes.
// Space Complexity: O(1), as we only use a few extra pointers.

/*
class Node {
  public:
    int data;
    Node *next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    Node* swapKth(Node* head, int k) {
        if (!head) return head; // Handle empty list

        // Count the total number of nodes in the list
        int n = 0;
        Node* temp = head;
        while (temp) {
            n++;
            temp = temp->next;
        }
    
        // If k is out of bounds, no swap is possible
        if (k > n) return head;
    
        // If kth node from start and end are the same, no need to swap
        if (2 * k - 1 == n) return head;
    
        // Find the kth node from the start and its previous node
        Node* prevX = nullptr;
        Node* x = head;
        for (int i = 1; i < k; i++) {
            prevX = x;
            x = x->next;
        }
    
        // Find the kth node from the end (n - k + 1 from start) and its previous node
        Node* prevY = nullptr;
        Node* y = head;
        for (int i = 1; i < n - k + 1; i++) {
            prevY = y;
            y = y->next;
        }
    
        // Adjust the 'next' pointers of the previous nodes
        if (prevX) prevX->next = y;
        if (prevY) prevY->next = x;
    
        // Swap the 'next' pointers of the target nodes
        Node* tempNext = x->next;
        x->next = y->next;
        y->next = tempNext;
    
        // Update the head if the first or last node was swapped
        if (k == 1) head = y;
        if (k == n) head = x;
    
        return head;
    }
};

/*
*
* Dry Run
*
* Input: head = [1, 2, 3, 4, 5], k = 2
*
* 1. n = 5 (length of the list).
* 2. k (2) is valid and 2*2-1 != 5.
*
* 3. Find 2nd node from start (x):
* - i=1: prevX = 1, x = 2. Loop ends.
* - So, x is node 2, prevX is node 1.
*
* 4. Find 2nd from end (5 - 2 + 1 = 4th node) (y):
* - i=1: prevY = 1, y = 2
* - i=2: prevY = 2, y = 3
* - i=3: prevY = 3, y = 4. Loop ends.
* - So, y is node 4, prevY is node 3.
*
* 5. Adjust previous pointers:
* - prevX (node 1) -> next = y (node 4). List becomes: 1 -> 4 ...
* - prevY (node 3) -> next = x (node 2). List becomes: 3 -> 2 ...
*
* 6. Swap next pointers:
* - tempNext = x->next (node 3)
* - x->next (node 2 -> next) = y->next (node 5). List part: 2 -> 5
* - y->next (node 4 -> next) = tempNext (node 3). List part: 4 -> 3
*
* 7. Combine the links:
* - 1 -> 4
* - 4 -> 3
* - 3 -> 2
* - 2 -> 5
* - Final list: 1 -> 4 -> 3 -> 2 -> 5
*
* 8. Head doesn't change since k is not 1 or 5.
*
* Output: 1 -> 4 -> 3 -> 2 -> 5
*/
```

#### Java Solution
```java
// Intuition: To swap the kth nodes from both ends, we first need to find them. By calculating the list's length, 'n', we can pinpoint the kth node from the start and the (n - k + 1)th node from the start (which is the kth from the end). The swap involves carefully re-linking the previous nodes to the swapped nodes and updating the swapped nodes' next pointers.
// Approach:
// 1. Calculate the total number of nodes 'n' in the list.
// 2. Handle edge cases: If k > n or if the two nodes to be swapped are the same (k == n - k + 1), return the original head.
// 3. Find the kth node from the beginning (let's call it 'x') and its previous node ('prevX').
// 4. Find the kth node from the end (i.e., (n - k + 1)th from the beginning, let's call it 'y') and its previous node ('prevY').
// 5. Adjust the 'next' pointers:
//    - If prevX exists, its 'next' should point to 'y'.
//    - If prevY exists, its 'next' should point to 'x'.
// 6. Swap the 'next' pointers of 'x' and 'y'.
// 7. Update the head of the list if k was 1 or n.
// 8. Return the new head.
// Time Complexity: O(N), where N is the number of nodes. We traverse the list once to find the length and then again to find the nodes.
// Space Complexity: O(1), as we only use a few extra pointers.

/*
class Node {
    int data;
    Node next;

    Node(int x) {
        data = x;
        next = null;
    }
}
*/
class Solution {
    public Node swapKth(Node head, int k) {
        if (head == null) return head; // Handle empty list

        // Count the total number of nodes in the list
        int n = 0;
        Node temp = head;
        while (temp != null) {
            n++;
            temp = temp.next;
        }
    
        // If k is out of bounds, no swap is possible
        if (k > n) return head;
    
        // If kth node from start and end are the same, no need to swap
        if (2 * k - 1 == n) return head;
    
        // Find the kth node from the start and its previous node
        Node prevX = null;
        Node x = head;
        for (int i = 1; i < k; i++) {
            prevX = x;
            x = x.next;
        }
    
        // Find the kth node from the end (n - k + 1 from start) and its previous node
        Node prevY = null;
        Node y = head;
        for (int i = 1; i < n - k + 1; i++) {
            prevY = y;
            y = y.next;
        }
    
        // Adjust the 'next' pointers of the previous nodes
        if (prevX != null) prevX.next = y;
        if (prevY != null) prevY.next = x;
    
        // Swap the 'next' pointers of the target nodes
        Node tempNext = x.next;
        x.next = y.next;
        y.next = tempNext;
    
        // Update the head if the first or last node was swapped
        if (k == 1) head = y;
        if (k == n) head = x;
    
        return head;
    }
}

/*
*
* Dry Run
*
* Input: head = [1, 2, 3, 4, 5], k = 2
*
* 1. n = 5 (length of the list).
* 2. k (2) is valid and 2*2-1 != 5.
*
* 3. Find 2nd node from start (x):
* - i=1: prevX = 1, x = 2. Loop ends.
* - So, x is node 2, prevX is node 1.
*
* 4. Find 2nd from end (5 - 2 + 1 = 4th node) (y):
* - i=1: prevY = 1, y = 2
* - i=2: prevY = 2, y = 3
* - i=3: prevY = 3, y = 4. Loop ends.
* - So, y is node 4, prevY is node 3.
*
* 5. Adjust previous pointers:
* - prevX (node 1) -> next = y (node 4). List becomes: 1 -> 4 ...
* - prevY (node 3) -> next = x (node 2). List becomes: 3 -> 2 ...
*
* 6. Swap next pointers:
* - tempNext = x.next (node 3)
* - x.next (node 2 -> next) = y.next (node 5). List part: 2 -> 5
* - y.next (node 4 -> next) = tempNext (node 3). List part: 4 -> 3
*
* 7. Combine the links:
* - 1 -> 4
* - 4 -> 3
* - 3 -> 2
* - 2 -> 5
* - Final list: 1 -> 4 -> 3 -> 2 -> 5
*
* 8. Head doesn't change since k is not 1 or 5.
*
* Output: 1 -> 4 -> 3 -> 2 -> 5
*/
```

---

## 🔑 Key Insights

- The problem simplifies once you realize the kth node from the end is the same as the **(n - k + 1)th** node from the beginning, where 'n' is the list size.
- The most crucial part is managing the pointers correctly. You're not just swapping the nodes themselves, but also updating the `next` pointers of their **predecessors**.
- Edge cases like swapping the head node (`k=1` or `k=n`) must be handled explicitly to update the list's head pointer correctly.

---

## 🚀 Further Exploration

- What if the list was a **doubly linked list**? How would that change the swapping logic?
- Can you solve this problem in a **single pass**? (Hint: Use two pointers, one fast and one slow).
- [Reverse a Linked List in groups of given size](https://www.geeksforgeeks.org/problems/reverse-a-linked-list-in-groups-of-given-size/1)
- [Add two numbers represented by linked lists](https://www.geeksforgeeks.org/problems/add-two-numbers-represented-by-linked-lists/1)

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/swap-kth-node-from-beginning-and-kth-node-from-end-in-a-singly-linked-list/1)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div align="left">

![Linked List](https://img.shields.io/badge/Linked_List-0077B5?style=for-the-badge)
![Data Structures](https://img.shields.io/badge/Data_Structures-239120?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge)
![Morgan Stanley](https://img.shields.io/badge/Morgan_Stanley-003A6F?style=for-the-badge)
![Amazon](https://img.shields.io/badge/Amazon-FF9900?style=for-the-badge&logo=amazon&logoColor=white)

</div>

---

## ⚖️ License

[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. This is intended for educational purposes only.