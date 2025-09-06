# ♾️ Find length of Loop

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-2A2B2D?style=for-the-badge&logo=geeksforgeeks&logoColor=308D46)](https://www.geeksforgeeks.org/problems/find-length-of-loop/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow.svg)](https://www.geeksforgeeks.org/problems/find-length-of-loop/1)
[![Accuracy: 44.26%](https://img.shields.io/badge/Accuracy-44.26%25-red.svg)](https://www.geeksforgeeks.org/problems/find-length-of-loop/1)
[![Points: 4](https://img.shields.io/badge/Points-4-blue.svg)](https://www.geeksforgeeks.org/problems/find-length-of-loop/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

---

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/find-length-of-loop/1).

---

## 📜 Problem Statement

Given the `head` of a linked list, determine whether the list contains a **loop**. If a loop is present, **return the number of nodes** in the loop, otherwise return `0`.

**Note:** Internally, `pos` (1 based index) is used to denote the position of the node that the tail's next pointer is connected to. If `pos = 0`, it means the last node points to `null`, indicating there is no loop. Note that `pos` is not passed as a parameter.

---

## 📥 Examples

### Example 1:
`Input:`
`head: 25 → 14 → 19 → 33 → 10 → 21 → 39 → 90 → 58 → 45, c = 4`
`Output: 7`
`Explanation: The loop is from 33 to 45. So length of loop is 33 → 10 → 21 → 39 → 90 → 58 → 45 = 7.`

<details>
<summary>📖 Example Breakdown</summary>

Here's a step-by-step walkthrough for the first example:
The linked list has a loop starting at the 4th node (data `33`). The last node, `45`, points back to `33`.
The nodes within the loop are `33, 10, 21, 39, 90, 58, 45`.
Counting these nodes, we get a total of 7.
Our algorithm should detect this loop and return the count of 7.
</details>

### Example 2:
`Input: head: 0 → 1 → 2 → 3, c = 0`
`Output: 0`
`Explanation: There is no loop.`

---

## 🚧 Constraints

- `1 ≤ number of nodes ≤ 10^5`
- `1 ≤ node->data ≤ 10^4`
- `0 ≤ pos < number of nodes`

---

## 💡 Solution Approaches

### Optimized Approach (Floyd’s Cycle Detection Algorithm)
The problem can be efficiently solved using **Floyd’s Cycle Detection Algorithm**, also known as the **Tortoise and Hare** algorithm. The main idea is to use two pointers, a `slow` pointer that moves one step at a time, and a `fast` pointer that moves two steps at a time.
If there is a loop, the fast pointer will eventually catch up to the slow pointer inside the loop. Once they meet, we can start counting the length of the loop by holding one pointer in place and moving the other until they meet again.

```cpp
/*
 *
 * struct Node {
 * int data;
 * struct Node *next;
 * Node(int x) {
 * data = x;
 * next = NULL;
 * }
 * };
 *
 */

// Intuition: Use two pointers, one fast and one slow, to detect a cycle. If they meet, a cycle exists.
// Approach: The slow pointer moves one step, and the fast pointer moves two steps. If there's a loop, the fast pointer will eventually overlap with the slow pointer. Once they meet, we can traverse the loop from that meeting point to count the number of nodes.
// Time Complexity: O(n), where n is the number of nodes in the linked list. Both pointers traverse the list at most twice.
// Space Complexity: O(1), since we only use a few extra pointers and no additional data structures.
class Solution {
public:
    // Helper function to count nodes in the loop starting from a given node
    int countNodes(Node* node) {
        int   count = 1;  // Initialize count to 1 for the starting node
        Node* temp  = node;

        // Traverse the loop until we return to the starting node
        while (temp->next != node) {
            count++;           // Increment count for each node
            temp = temp->next; // Move to the next node
        }
        return count; // Return the total count
    }
    // Main function to detect loop and return count of nodes in it
    int lengthOfLoop(Node* head) {
        Node* slow = head, * fast = head; // Initialize slow and fast pointers

        // Move slow by 1 and fast by 2 steps and check for meeting point
        while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
            slow = slow->next;      // Move slow pointer one step
            fast = fast->next->next; // Move fast pointer two steps

            // Loop detected, since the pointers met
            if (slow == fast) {
                return countNodes(slow); // Call helper function to count loop length
            }
        }

        // No loop found if the loop terminates
        return 0; // Return 0 if no loop is present
    }
};

/*
*
* Dry Run
*
* Given Linked List: 25 -> 14 -> 19 -> 33 -> 10 -> 21 -> 39 -> 90 -> 58 -> 45 -> 33 (loop)
*
* Pointers:
* slow = head (25)
* fast = head (25)
*
* 1. slow moves to 14, fast moves to 19.
* 2. slow moves to 19, fast moves to 10.
* 3. slow moves to 33, fast moves to 39.
* 4. slow moves to 10, fast moves to 58.
* 5. slow moves to 21, fast moves to 33.
* 6. slow moves to 39, fast moves to 21.
* 7. slow moves to 90, fast moves to 90. Pointers meet. Loop detected.
*
* Now, count the loop length from the meeting point (90):
* Starting at 90, traverse until we reach 90 again.
* 90 -> 58 (count=1)
* 58 -> 45 (count=2)
* 45 -> 33 (count=3)
* 33 -> 10 (count=4)
* 10 -> 21 (count=5)
* 21 -> 39 (count=6)
* 39 -> 90 (count=7)
*
* The count is 7.
*
* Final Output: 7
*
*/
````

-----

## 🔑 Key Insights

The core insight of this problem is the use of two pointers moving at different speeds. The fast pointer's speed being twice that of the slow pointer guarantees that if a loop exists, they will eventually meet. This is because the fast pointer effectively "laps" the slow pointer within the cycle. The moment they meet, we know a cycle is present. To find the length of the cycle, we can simply traverse from the meeting point back to itself, counting each node along the way. This approach is highly efficient, solving the problem in linear time and constant space.

-----

## 🔎 Further Exploration

  - **Find the starting node of the loop:** After detecting a loop, how would you find the first node of the cycle? (Hint: Reset one pointer to the head and move both pointers at the same speed).
  - **Remove the loop:** How would you modify the linked list to remove the detected loop and make it a valid, non-cyclic list?
  - **Cycle detection in a graph:** Can this algorithm be extended to detect cycles in a general graph?

-----

## 🔗 References

  - [Original GFG Problem](https://www.google.com/search?q=https://www.geeksforghttps://www.geeksforgeeks.org/problems/find-length-of-loop/1)
  - [Floyd’s Cycle-Finding Algorithm (Wikipedia)](https://en.wikipedia.org/wiki/Floyd%27s_cycle-finding_algorithm)

-----

## ✍️ Author

[imnilesh18](https://github.com/imnilesh18)

-----

## 🏷️ Tags

  - `Linked List`
  - `Floyd's Cycle Detection`
  - `Two Pointers`
  - `GeeksforGeeks`

-----

## 📄 License

This project is licensed under the MIT License.

**MIT License**

A short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications, and larger works may be distributed under different terms and without source code.

**Educational Use Disclaimer:**
This project is explicitly intended for educational use. While the MIT License permits commercial use, this content is provided as a learning resource. Users are encouraged to respect the spirit of educational sharing and integrity.
