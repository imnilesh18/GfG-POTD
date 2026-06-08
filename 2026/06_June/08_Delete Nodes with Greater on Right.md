# 🗑️ Delete Nodes with Greater on Right

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy: 35.51%](https://img.shields.io/badge/Accuracy-35.51%25-yellow?style=for-the-badge)
![Points: 2](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-blueviolet?style=for-the-badge)

---

### ⚠️ Educational Use Only
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/delete-nodes-having-greater-value-on-right/1).

---

## 📝 Problem Statement
Given a singly linked list, remove all nodes that have a node with a greater value anywhere to their right in the list. Return the head of the modified linked list.

### 📊 Constraints
* `1 ≤ size of linked list ≤ 10^6`
* `1 ≤ element of linked list ≤ 10^6`

---

## 📖 Examples

**Example 1:**
* **Input:** `LinkedList = 12->15->10->11->5->6->2->3`
* **Output:** `15->11->6->3`

**Example 2:**
* **Input:** `LinkedList = 10->20->30->40->50->60`
* **Output:** `60`

<details>
<summary>📖 Example Breakdown</summary>

For the input `12->15->10->11->5->6->2->3`:
1. We evaluate each node from right to left.
2. We keep track of the maximum value seen so far.
3. If a current node is smaller than the maximum seen, it is deleted.
4. If it is greater or equal, it is retained and becomes the new maximum.
5. In this case, 12, 10, 5, and 2 are removed because they have larger values to their right.
</details>

---

## 💡 Solution Approaches

### Approach: Right-to-Left Traversal (Optimal)

// Intuition: A node needs to be removed if there's any strictly greater node to its right. Processing from right to left makes this easy, as we only need to track the maximum value seen so far.
// Approach: Reverse the linked list to simulate right-to-left traversal. Traverse the reversed list, keeping track of the maximum value seen. If a node's value is smaller than the maximum, delete it. Otherwise, update the maximum. Finally, reverse the list back to its original order.
// Time Complexity: O(N) where N is the number of nodes. We traverse the list three times (reverse, filter, reverse back), taking linear time.
// Space Complexity: O(1) since we only use a few pointers to manipulate the linked list in-place without any extra memory.

```cpp
class Solution {
  public:
    Node *compute(Node *head) {
        // Handle edge case of empty list or single node
        if (!head || !head->next) return head;

        // Reverse the original list to process from right to left
        Node* prev = nullptr;
        Node* curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head = prev; 

        // Track max node while traversing the reversed list
        Node* current = head;
        Node* maxNode = head;

        while (current && current->next) {
            // Check if next node is smaller than current max
            if (current->next->data < maxNode->data) {
                // Remove the smaller node
                Node* temp = current->next;
                current->next = temp->next;
                delete temp; 
            } else {
                // Update pointers if next node is greater or equal
                current = current->next;
                maxNode = current;
            }
        }

        // Reverse the filtered list back to original order
        prev = nullptr;
        curr = head;
        while (curr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        head = prev;

        return head;
    }
};

```

/*

* Dry Run
* Input: 12 -> 15 -> 10 -> 11 -> 5 -> 6 -> 2 -> 3
* 1. First reverse: 3 -> 2 -> 6 -> 5 -> 11 -> 10 -> 15 -> 12


* 2. Traverse and filter (maxNode starts at 3):


* * Next is 2 (2 < 3): Delete 2.


* * Next is 6 (6 >= 3): Keep 6. maxNode = 6.


* * Next is 5 (5 < 6): Delete 5.


* * Next is 11 (11 >= 6): Keep 11. maxNode = 11.


* * Next is 10 (10 < 11): Delete 10.


* * Next is 15 (15 >= 11): Keep 15. maxNode = 15.


* * Next is 12 (12 < 15): Delete 12.


* 3. Resulting reversed list: 3 -> 6 -> 11 -> 15


* 4. Reverse back: 15 -> 11 -> 6 -> 3
*/



---

## 🔑 Key Insights

* **Reverse Traversal Trick:** Whenever a problem involves comparing a node with everything to its right, reversing the list allows us to transform a "look ahead" problem into a "look behind" (max so far) problem, significantly simplifying the logic.
* **In-place manipulation:** By careful pointer management, we achieved O(1) auxiliary space, which is critical for large inputs (`10^6`).

## 🚀 Further Exploration

* Try solving this using **Recursion**. Can you manage the state without reversing the list twice?
* Practice other Linked List problems:
* [Reverse a Linked List](https://www.geeksforgeeks.org/problems/reverse-a-linked-list/1)
* [Remove N-th node from end of list](https://www.google.com/search?q=https://www.geeksforgeeks.org/problems/remove-nth-node-from-end-of-list/1)



## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/delete-nodes-having-greater-value-on-right/1)

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)