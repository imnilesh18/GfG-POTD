/*
 * Sort a linked list of 0s, 1s and 2s
 *
 * Difficulty: Medium Accuracy: 60.75% Submissions: 237K+ Points: 4 Average Time: 30m
 *
 * Given the head of a linked list where nodes can contain values 0s, 1s, and 2s only. Your task is to rearrange the list so that all 0s appear at the beginning, followed by all 1s, and all 2s are placed at the end.
 *
 * Examples:
 * Input: head = 1 → 2 → 2 → 1 → 2 → 0 → 2 → 2
 * Output: 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
 * Explanation: All the 0s are segregated to the left end of the linked list, 2s to the right end of the list, and 1s in between.
 *
 * Input: head = 2 → 2 → 0 → 1
 * Output: 0 → 1 → 2 → 2
 * Explanation: After arranging all the 0s, 1s and 2s in the given format, the output will be 0 → 1 → 2 → 2.
 *
 * Constraints:
 * 1 ≤ no. of nodes ≤ 10^6
 * 0 ≤ node->data ≤ 2
 */

/************************************************************ C++ ************************************************/

/*
 *
 * Node is defined as
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

// Approach 1: Count the number of 0s, 1s, and 2s, then overwrite the linked list with that many 0s, 1s, and 2s in order.
// Time Complexity: O(N) - Traverse the list twice: once for counting and once for updating.
// Space Complexity: O(1) - No extra space used except variables for counting.
class Solution {
public:
    // Function to sort a linked list of 0s, 1s and 2s.
    Node* segregate(Node* head) {
        if (!head || !(head->next)) {
            return head;   // If the list is empty or has only one node, it's already sorted.
        }
        // Initialize counts for 0s, 1s, and 2s
        int cntZero = 0, cntOne = 0, cntTwo = 0;

        // Traverse the list to count the occurrences of 0, 1, and 2
        Node* temp = head;
        while (temp) {
            if (temp->data == 0) {
                cntZero++;
            } else if (temp->data == 1) {
                cntOne++;
            } else {
                cntTwo++;
            }
            temp = temp->next;
        }

        // Rebuild the list with sorted values
        temp = head;

        // First add all the 0s
        while (cntZero) {
            temp->data = 0;
            temp       = temp->next;
            cntZero--;
        }

        // Then add all the 1s
        while (cntOne) {
            temp->data = 1;
            temp       = temp->next;
            cntOne--;
        }

        // Finally add all the 2s
        while (cntTwo) {
            temp->data = 2;
            temp       = temp->next;
            cntTwo--;
        }

        return head;   // Return the modified list
    }
};

/*
 *
 * Dry Run
 *
 * Input Linked List: 1 → 2 → 2 → 1 → 2 → 0 → 2 → 2
 *
 * Step 1: Count the number of 0s, 1s, and 2s
 * - cntZero = 1 (only one 0)
 * - cntOne = 2 (two 1s)
 * - cntTwo = 5 (five 2s)
 *
 * Step 2: Overwrite the linked list:
 * - First fill 0s → 0 (one time)
 *     Linked List after filling 0s: 0 → 2 → 2 → 1 → 2 → 0 → 2 → 2
 * - Then fill 1s → 1 → 1 (two times)
 *     Linked List after filling 1s: 0 → 1 → 1 → 1 → 2 → 0 → 2 → 2
 * - Finally fill 2s → 2 → 2 → 2 → 2 → 2 (five times)
 *     Linked List after filling 2s: 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
 *
 * Final Output: 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
 *
 */

// Approach 2: Use Dutch National Flag algorithm by creating three separate lists for 0s, 1s, and 2s, then connect them.
// Time Complexity: O(N) - Single traversal of the linked list.
// Space Complexity: O(1) - Only extra pointers are used, no space proportional to input size.
class Solution {
public:
    // Sort a linked list of 0s, 1s and 2s using Dutch National Flag logic (1-pass)
    Node* segregate(Node* head) {
        if (!head || !(head->next)) {
            return head;   // If list is empty or has one node, it's already sorted
        }

        // Dummy nodes for three separate lists
        Node* zeroHead = new Node(-1);   // Dummy head for 0s list
        Node* oneHead  = new Node(-1);   // Dummy head for 1s list
        Node* twoHead  = new Node(-1);   // Dummy head for 2s list

        // Tails for the three lists
        Node* zero = zeroHead;
        Node* one  = oneHead;
        Node* two  = twoHead;

        // Traverse the original list and partition into three lists
        Node* temp = head;
        while (temp) {
            if (temp->data == 0) {
                zero->next = temp;
                zero       = zero->next;
            } else if (temp->data == 1) {
                one->next = temp;
                one       = one->next;
            } else {
                two->next = temp;
                two       = two->next;
            }
            temp = temp->next;
        }

        // Connect the three lists together
        zero->next = (oneHead->next) ? (oneHead->next) : (twoHead->next); // 0s -> 1s if available, else 0s -> 2s
        one->next  = twoHead->next;                                       // 1s -> 2s
        two->next  = nullptr;                                             // End the list properly

        // New head of the modified list
        head = zeroHead->next;

        // Delete dummy nodes to free memory
        delete zeroHead;
        delete oneHead;
        delete twoHead;

        return head;   // Return the modified list
    }
};

/*
 *
 * Dry Run
 *
 * Input Linked List: 1 → 2 → 2 → 1 → 2 → 0 → 2 → 2
 *
 * Step 1: Create three dummy lists:
 * - zeroHead (for 0s): initially empty
 * - oneHead (for 1s): initially empty
 * - twoHead (for 2s): initially empty
 *
 * Step 2: Traverse the original list and distribute:
 * - 1 → added to 1s list
 * - 2 → added to 2s list
 * - 2 → added to 2s list
 * - 1 → added to 1s list
 * - 2 → added to 2s list
 * - 0 → added to 0s list
 * - 2 → added to 2s list
 * - 2 → added to 2s list
 *
 * After partition:
 * - 0s list: 0
 * - 1s list: 1 → 1
 * - 2s list: 2 → 2 → 2 → 2 → 2
 *
 * Step 3: Connect the lists:
 * - 0s list connects to 1s list
 * - 1s list connects to 2s list
 * - 2s list ends with null
 *
 * Final Linked List visually:
 *
 * 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
 *
 * Step 4: Return the new head: 0
 *
 */

/************************************************************ JAVA ************************************************/

/*
 * class Node
 * {
 *  int data;
 *  Node next;
 *  Node(int data)
 *  {
 *      this.data = data;
 *      next = null;
 *  }
 * }
 */

// Approach 1: Count the number of 0s, 1s, and 2s, then overwrite the linked list with that many 0s, 1s, and 2s in order.
// Time Complexity: O(N) - Traverse the list twice: once for counting and once for updating.
// Space Complexity: O(1) - No extra space used except variables for counting.
class Solution {
    // Function to sort a linked list of 0s, 1s and 2s.
    static Node segregate(Node head) {
        if (head == null || head.next == null) {
            return head; // If list is empty or has one node, it's already sorted.
        }
        // Initialize counts for 0s, 1s, and 2s
        int cntZero = 0, cntOne = 0, cntTwo = 0;

        // Traverse the list to count the occurrences of 0, 1, and 2
        Node temp = head;
        while (temp != null) {
            if (temp.data == 0) {
                cntZero++;
            } else if (temp.data == 1) {
                cntOne++;
            } else {
                cntTwo++;
            }
            temp = temp.next;
        }

        // Rebuild the list with sorted values
        temp = head;

        // First add all the 0s
        while (cntZero > 0) {
            temp.data = 0;
            temp      = temp.next;
            cntZero--;
        }

        // Then add all the 1s
        while (cntOne > 0) {
            temp.data = 1;
            temp      = temp.next;
            cntOne--;
        }

        // Finally add all the 2s
        while (cntTwo > 0) {
            temp.data = 2;
            temp      = temp.next;
            cntTwo--;
        }

        return head; // Return the modified list
    }
}

/*
 *
 * Dry Run
 *
 * Input Linked List: 1 → 2 → 2 → 1 → 2 → 0 → 2 → 2
 *
 * Step 1: Count the number of 0s, 1s, and 2s
 * - cntZero = 1 (only one 0)
 * - cntOne = 2 (two 1s)
 * - cntTwo = 5 (five 2s)
 *
 * Step 2: Overwrite the linked list:
 * - First fill 0s → 0 (one time)
 *     Linked List after filling 0s: 0 → 2 → 2 → 1 → 2 → 0 → 2 → 2
 * - Then fill 1s → 1 → 1 (two times)
 *     Linked List after filling 1s: 0 → 1 → 1 → 1 → 2 → 0 → 2 → 2
 * - Finally fill 2s → 2 → 2 → 2 → 2 → 2 (five times)
 *     Linked List after filling 2s: 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
 *
 * Final Output: 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
 *
 */

// Approach 2: Use Dutch National Flag algorithm by creating three separate lists for 0s, 1s, and 2s, then connect them.
// Time Complexity: O(N) - Single traversal of the linked list.
// Space Complexity: O(1) - Only extra pointers are used, no space proportional to input size.
class Solution {
    // Function to sort a linked list of 0s, 1s, and 2s
    static Node segregate(Node head) {
        if (head == null || head.next == null) {
            return head; // If list is empty or has one node, it's already sorted
        }

        // Dummy nodes for three separate lists
        Node zeroHead = new Node(-1); // Dummy head for 0s list
        Node oneHead  = new Node(-1); // Dummy head for 1s list
        Node twoHead  = new Node(-1); // Dummy head for 2s list

        // Tails for the three lists
        Node zero = zeroHead;
        Node one  = oneHead;
        Node two  = twoHead;

        // Traverse the original list and partition into three lists
        Node temp = head;
        while (temp != null) {
            if (temp.data == 0) {
                zero.next = temp;
                zero      = zero.next;
            } else if (temp.data == 1) {
                one.next = temp;
                one      = one.next;
            } else {
                two.next = temp;
                two      = two.next;
            }
            temp = temp.next;
        }

        // Connect the three lists together
        zero.next = (oneHead.next != null) ? oneHead.next : twoHead.next; // 0s -> 1s if available, else 0s -> 2s
        one.next  = twoHead.next;                                         // 1s -> 2s
        two.next  = null;                                                 // End the list properly

        // New head of the modified list
        head = zeroHead.next;

        return head; // Return the modified list
    }
}

/*
 *
 * Dry Run
 *
 * Input Linked List: 1 → 2 → 2 → 1 → 2 → 0 → 2 → 2
 *
 * Step 1: Create three dummy lists:
 * - zeroHead (for 0s): initially empty
 * - oneHead (for 1s): initially empty
 * - twoHead (for 2s): initially empty
 *
 * Step 2: Traverse the original list and distribute:
 * - 1 → added to 1s list
 * - 2 → added to 2s list
 * - 2 → added to 2s list
 * - 1 → added to 1s list
 * - 2 → added to 2s list
 * - 0 → added to 0s list
 * - 2 → added to 2s list
 * - 2 → added to 2s list
 *
 * After partition:
 * - 0s list: 0
 * - 1s list: 1 → 1
 * - 2s list: 2 → 2 → 2 → 2 → 2
 *
 * Step 3: Connect the lists:
 * - 0s list connects to 1s list
 * - 1s list connects to 2s list
 * - 2s list ends with null
 *
 * Final Linked List visually:
 *
 * 0 → 1 → 1 → 2 → 2 → 2 → 2 → 2
 *
 * Step 4: Return the new head: 0
 *
 */
