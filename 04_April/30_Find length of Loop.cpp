/*
 * Find length of Loop
 *
 * Difficulty: Easy Accuracy: 44.26% Submissions: 248K+ Points: 2 Average Time: 30m
 *
 * Given the head of a linked list, determine whether the list contains a loop. If a loop is present, return the number of nodes in the loop, otherwise return 0.
 * Note: 'c' is the position of the node which is the next pointer of the last node of the linkedlist. If c is 0, then there is no loop.
 *
 * Examples:
 *
 * Input: head: 25 → 14 → 19 → 33 → 10 → 21 → 39 → 90 → 58 → 45, c = 4
 * Output: 7
 * Explanation: The loop is from 33 to 45. So length of loop is 33 → 10 → 21 → 39 → 90 → 58 → 45 = 7.
 * The number 33 is connected to the last node of the linkedlist to form the loop because according to the input the 4th node from the beginning(1 based indexing)
 * will be connected to the last node in the LinkedList.
 *
 * Input: head: 0 → 1 → 2 → 3, c = 0
 * Output: 0
 * Explanation: There is no loop.
 *
 * Constraints:
 * 1 ≤ no. of nodes ≤ 10^6
 * 0 ≤ node.data ≤ 10^6
 * 0 ≤ c ≤ n-1
 */

/************************************************************ C++ ************************************************/

/*
 *
 * struct Node {
 *  int data;
 *  struct Node *next;
 *  Node(int x) {
 *      data = x;
 *      next = NULL;
 *  }
 * };
 *
 */

// Approach: Use Floyd’s Cycle Detection Algorithm (Tortoise and Hare) to detect the loop. If found, count the number of nodes in the loop.
// Time Complexity: O(n), where n is the number of nodes in the linked list because each node is visited at most twice.
// Space Complexity: O(1), since no extra space is used apart from pointers.
class Solution {
public:
    // Helper function to count nodes in the loop starting from a given node
    int countNodes(Node* node) {
        int   count = 1;
        Node* temp  = node;

        // Traverse the loop until we return to the starting node
        while (temp->next != node) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    // Main function to detect loop and return count of nodes in it
    int countNodesinLoop(Node* head) {
        Node* slow = head, * fast = head;

        // Move slow by 1 and fast by 2 steps and check for meeting point
        while (slow != nullptr && fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            // Loop detected
            if (slow == fast) {
                return countNodes(slow);
            }
        }

        // No loop found
        return 0;
    }
};

/*
 *
 * 💡 Intuition + Visual Dry Run (Box Representation)
 *
 * Given Linked List (with a loop):
 *
 * 25 → 14 → 19 → 33 → 10 → 21 → 39 → 90 → 58 → 45
 *                ↑                              |
 *                |______________________________|
 *
 * Loop: 33 → 10 → 21 → 39 → 90 → 58 → 45 → (back to 33)
 *
 * 🐢 = slow pointer
 * 🐇 = fast pointer
 *
 * Step-by-step Pointer Movement:
 * ---------------------------------
 *
 * Initial:
 * 25 🐢🐇
 *
 * Step 1:
 * 14 🐢
 *      19 🐇
 *
 * Step 2:
 * 19 🐢
 *              10 🐇
 *
 * Step 3:
 * 33 🐢
 *                        39 🐇
 *
 * Step 4:
 * 10 🐢
 *                                58 🐇
 *
 * Step 5:
 * 21 🐢
 *      ⭣
 *                        33 🐇
 *
 * Step 6:
 * 39 🐢
 *                     21 🐇
 *
 * Step 7:
 * 90 🐢
 *                    ⭣
 *                    90 🐇 ✅ 🎯 Meeting Point → Loop Detected!
 *
 * ---------------------------------
 *
 * 🔁 Now count the loop length starting from 90:
 *
 * Traversal:
 * 90 → 58  → 45 → 33 → 10 → 21 → 39 → back to 90)
 *
 * 🧮 Count = 7
 *
 * ✅ Final Output = 7
 *
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node
 * {
 *  int data;
 *  Node next;
 *  Node(int d) {data = d; next = null; }
 * }
 */

// Approach: Use Floyd’s Cycle Detection Algorithm (Tortoise and Hare) to detect the loop. If found, count the number of nodes in the loop.
// Time Complexity: O(n), where n is the number of nodes in the linked list because each node is visited at most twice.
// Space Complexity: O(1), since no extra space is used apart from pointers.
class Solution {
    // Helper function to count nodes in the loop starting from the meeting point
    private int countNodes(Node node) {
        int  count = 1;
        Node temp  = node;

        // Traverse the loop until we return to the same node
        while (temp.next != node) {
            count++;
            temp = temp.next;
        }
        return count;
    }
    // Function to detect loop and return its length
    public int countNodesinLoop(Node head) {
        Node slow = head, fast = head;

        while (slow != null && fast != null && fast.next != null) {
            slow = slow.next;         // Move slow by 1
            fast = fast.next.next;    // Move fast by 2

            // Loop detected
            if (slow == fast) {
                return countNodes(slow);
            }
        }

        // No loop found
        return 0;
    }
}

/*
 *
 * 💡 Intuition + Visual Dry Run (Box Representation)
 *
 * Given Linked List (with a loop):
 *
 * 25 → 14 → 19 → 33 → 10 → 21 → 39 → 90 → 58 → 45
 *                ↑                             |
 *                |_____________________________|
 *
 * Loop: 33 → 10 → 21 → 39 → 90 → 58 → 45 → (back to 33)
 *
 * 🐢 = slow pointer
 * 🐇 = fast pointer
 *
 * Step-by-step Pointer Movement:
 * ---------------------------------
 *
 * Initial:
 * 25 🐢🐇
 *
 * Step 1:
 * 14 🐢
 *      19 🐇
 *
 * Step 2:
 * 19 🐢
 *              10 🐇
 *
 * Step 3:
 * 33 🐢
 *                        39 🐇
 *
 * Step 4:
 * 10 🐢
 *                                58 🐇
 *
 * Step 5:
 * 21 🐢
 *      ⭣
 *                        33 🐇
 *
 * Step 6:
 * 39 🐢
 *                     21 🐇
 *
 * Step 7:
 * 90 🐢
 *                    ⭣
 *                    90 🐇 ✅ 🎯 Meeting Point → Loop Detected!
 *
 * ---------------------------------
 *
 * 🔁 Now count the loop length starting from 90:
 *
 * Traversal:
 * 90 → 58 → 45 → 33 → 10 → 21 → 39 → (back to 90)
 *
 * 🧮 Count = 7
 *
 * ✅ Final Output = 7
 *
 */
