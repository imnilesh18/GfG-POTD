# 🔗 Intersection Point in Y Shaped Linked Lists

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-44.67%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1)
[![Points](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

Given the heads of two non-empty singly linked lists, `head1` and `head2`, that intersect at a certain point. Return that **Node** where these two linked lists intersect.

**Note:**
* It is guaranteed that the intersected node always exists.
* In the custom input, you have to give input for `CommonList` which is pointed at the end of both `head1` and `head2` to form a Y-shaped linked list.

### 🔢 Constraints

* $2 \le \text{total number of nodes} \le 2 \times 10^5$
* $-10^4 \le \text{node->data} \le 10^4$

---

## 🔍 Examples

### Example 1
**Input:**
```text
head1: 10 -> 15 -> 30
head2:  3 ->  6 ->  9 -> 15 -> 30

```

**Output:**

```text
15

```

**Explanation:**
The common part is `15 -> 30`. The starting point of intersection is node with data **15**.

### Example 2

**Input:**

```text
head1: 4 -> 1 -> 8 -> 5
head2: 5 -> 6 -> 1 -> 8 -> 5

```

**Output:**

```text
1

```

**Explanation:**
The common part is `1 -> 8 -> 5`. The intersection starts at node with data **1**.

<details>
<summary><b>📖 Example Breakdown</b></summary>

Consider **Example 2**:

* **List A:** 4 -> 1 -> 8 -> 5
* **List B:** 5 -> 6 -> 1 -> 8 -> 5
* Visually, they merge at node `1`.
```
4 --- 1
      \
       8 --- 5
      /
5 --- 6 --- 1

```


*(Note: The diagram structure depends on specific memory addresses, but logically they share the node `1`)*.

</details>

---

## 💡 Solution Approaches

We will explore four approaches, ranging from brute force to the most optimal two-pointer technique.

### Approach 1: Brute Force (Nested Loops)

Iterate through every node of the second list, and for each node, check if it matches any node in the first list.

```cpp
// Intuition: Check every pair of nodes from both lists to see if they point to the same memory address.
// Approach: Nested traversal - for each node in list2, iterate entirely through list1.
// Time Complexity: O(N * M) where N and M are lengths of the lists.
// Space Complexity: O(1) as we only use temporary pointers.

/*
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    Node *intersectPoint(Node *head1, Node *head2) {
        // Iterate over second list and for each node
        // Search it in first list
        while (head2 != nullptr) {
            Node *temp = head1;
            while (temp) {
               
                // If both Nodes are same (memory address check)
                if (temp == head2)
                    return head2;
                temp = temp->next;
            }
            head2 = head2->next;
        }
        
        // intersection is not present between the lists
        return nullptr;
    }
};

/*
*
* Dry Run
* Input: List1: 1->2->3, List2: 4->3 (Intersect at 3)
* 1. head2 points to 4.
* - Inner loop checks 1, 2, 3 against 4. No match.
* 2. head2 moves to 3.
* - Inner loop checks 1 against 3. No.
* - Inner loop checks 2 against 3. No.
* - Inner loop checks 3 against 3. MATCH!
* Return Node(3).
*
*/

```

---

### Approach 2: Hashing

Use a Hash Set to store all nodes of the first list. Then traverse the second list and check if the current node exists in the set.

```cpp
// Intuition: Trade space for time. By memorizing visited nodes of one list, we can check intersection in O(1).
// Approach: Store all nodes of head1 in a set. Traverse head2; the first node found in the set is the intersection.
// Time Complexity: O(N + M) for traversing both lists.
// Space Complexity: O(N) to store nodes of the first list in the set.

/*
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    Node *intersectPoint(Node *head1, Node *head2) {
    
        unordered_set<Node *> visNodes;
    
        // traverse the first list and store all
        // nodes in a set
        Node *curr1 = head1;
        while (curr1 != nullptr) {
            visNodes.insert(curr1);
            curr1 = curr1->next;
        }
    
        // traverse the second list and check if any
        // node is in the set
        Node *curr2 = head2;
        while (curr2 != nullptr) {
            if (visNodes.find(curr2) != visNodes.end()) {
                
                // Intersection point found
                return curr2;
            }
            curr2 = curr2->next;
        }
    
        return nullptr;
    }
};

/*
*
* Dry Run
* Input: List1: 10->20, List2: 5->10->20 (Intersect at 10)
* 1. Set stores {Node(10), Node(20)}.
* 2. Iterate List2:
* - Check Node(5): Not in set.
* - Check Node(10): Found in set!
* Return Node(10).
*
*/

```

---

### Approach 3: Two Pointers (Optimal)

This is the most elegant solution. By switching pointers to the head of the *other* list when they reach the end, we compensate for the difference in lengths. They will effectively travel `Len1 + Len2` steps and meet exactly at the intersection.

```cpp
// Intuition: Align the start of iteration by canceling out the length difference using pointer switching.
// Approach: Two pointers traverse their lists. When one hits NULL, it jumps to the OTHER list's head. They meet at the intersection.
// Time Complexity: O(N + M) - each pointer traverses at most length of both lists.
// Space Complexity: O(1) - no extra space used.

/*
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    Node *intersectPoint(Node *head1, Node *head2) {
        
        Node *ptr1 = head1;
        Node *ptr2 = head2;
    
        if (ptr1 == nullptr || ptr2 == nullptr)
            return nullptr;
    
        // traverse through the lists until both pointers meet
        while (ptr1 != ptr2) {
           
            // move to the next node in each list and if the one 
            // pointer reaches NULL, start from the other linked list
            ptr1 = ptr1 ? ptr1->next : head2;
            ptr2 = ptr2 ? ptr2->next : head1;
        }
    
        return ptr1;
    }
};

/*
*
* Dry Run
* List A: 1->9 (Length 2), List B: 2->3->9 (Length 3). Intersect at 9.
* 1. p1 at 1, p2 at 2.
* 2. p1 -> 9, p2 -> 3.
* 3. p1 -> NULL (end of A), p2 -> 9.
* 4. p1 -> headB (2), p2 -> NULL (end of B).
* 5. p1 -> 3, p2 -> headA (1).
* 6. p1 -> 9, p2 -> 9. Match!
* Return Node(9).
*
*/

```

---

### Approach 4: Cycle Detection Transformation

This creative approach modifies the structure temporarily. By connecting the end of one list to the head of the (reversed) second list, finding the intersection becomes equivalent to finding the starting node of a cycle.

**Note:** This modifies the input lists (reverses `head2`), which implies the lists are consumed.

```cpp
// Intuition: Convert the Y-shape into a loop (lasso shape) and use Floyd's Cycle Detection to find the entry point.
// Approach: Reverse List2, connect end of List1 to new Head2, find cycle entry, return node.
// Time Complexity: O(N + M). Reverse is O(M), traversal is linear.
// Space Complexity: O(1).

/*
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
   // reverses a linked list
    Node* reverse(Node* node) {
        Node *prev = nullptr, *curr = node;
        while (curr) {
            Node *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        return prev;
    }
    
    // finds the intersection point of two
    // linked lists
    Node* intersectPoint(Node* head1, Node* head2) {
        if (!head1 || !head2) return nullptr;
    
        // reverse the second list
        Node* revHead2 = reverse(head2);
    
        // attach reversed second list to the
        // end of the first
        Node* temp = head1;
        while (temp->next)
            temp = temp->next;
        temp->next = revHead2;
    
        // detect cycle using Floyd’s algorithm
        Node* slow = head1;
        Node* fast = head1;
    
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
    
            if (slow == fast) { 
                slow = head1;
                while (slow != fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
    
        return nullptr;
    }
};

/*
*
* Dry Run
* Logic is complex to trace briefly, but essentially:
* 1. Reversing List2 makes the intersection path 'backward'.
* 2. Linking End(List1) to Rev(List2) creates a path that loops back to the intersection point.
* 3. Floyd's algorithm identifies this entry point.
*
*/

```

---

## 🔑 Key Insights

* **Difference in Length:** The main difficulty is that the lists have different lengths before the intersection. The pointers won't arrive at the intersection at the same time if they start simultaneously.
* **Pointer Switching (Approach 3):** This is the standard "interview perfect" solution. It implicitly calculates the length difference. If List A is length  and List B is , traversing  then  takes  steps. Traversing  then  takes  steps. They align perfectly for the second pass.
* **Space vs Time:** Hashing is easiest to implement if memory is not a constraint.

---

## 🚀 Further Exploration

* **Detect Cycle:** Try solving "Detect Cycle in a Linked List".
* **Union of Lists:** Try finding the union of two linked lists.
* **Restoration:** In Approach 4, can you restore the list structure before returning?

---

## 📚 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1)
* [Floyd's Cycle Finding Algorithm](https://www.google.com/search?q=https://en.wikipedia.org/wiki/Cycle_detection%23Floyd%27s_tortoise_and_hare)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

<div align="center">

### 📜 License

This project is licensed under the **MIT License**.

**⚠️ Educational Disclaimer:**

> The code provided in this repository is intended for educational purposes only. It serves as a resource for learning concepts related to data structures and algorithms.

</div>
