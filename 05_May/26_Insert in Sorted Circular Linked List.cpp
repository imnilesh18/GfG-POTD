/*
 * GfG Link: https://www.geeksforgeeks.org/problems/sorted-insert-for-circular-linked-list/1
 *
 * Insert in Sorted Circular Linked List
 *
 * Difficulty: Medium Accuracy: 25.56% Submissions: 123K+ Points: 4 Average Time: 20m
 *
 * Given a sorted circular linked list, the task is to insert a new node in this circular linked list so that it remains a sorted circular linked list.
 *
 * Examples:
 *
 * Input: head = 1->2->4, data = 2
 * Output: 1->2->2->4
 * Explanation: We can add 2 after the second node.
 *
 * Input: head = 1->4->7->9, data = 5
 * Output: 1->4->5->7->9
 * Explanation: We can add 5 after the second node.
 *
 * Constraints:
 * 2 <= number of nodes <= 10^6
 * 0 <= node->data <= 10^6
 * 0 <= data <= 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Traverse the circular linked list using two pointers (curr and nextToCurr) to find the correct position to insert the new node such that the list remains sorted. There are 3 cases to handle: inserting in the middle of two nodes, inserting as the new minimum (before current head), or inserting as the new maximum (at the wrap-around point).
// Time Complexity: O(n) In the worst case, we may traverse all 'n' nodes in the circular linked list once to find the correct insertion point.
// Space Complexity: O(1) Only a constant amount of extra space is used for pointers and the new node.

/* structure for a node
 * class Node {
 * public:
 * int data;
 * Node *next;
 *
 * Node(int x){
 *    data = x;
 *    next = NULL;
 * }
 * }; */

class Solution {
public:
    Node* sortedInsert(Node* head, int data) {
        // Step 1: Create the new node with given data
        Node* newNode = new Node(data);

        // Step 2: Initialize two pointers
        Node* curr       = head;
        Node* nextToCurr = head->next;

        // Step 3: Traverse the circular list to find correct insertion point
        while (true) {
            // Case 1: Normal case — insert between two nodes in sorted order
            if (curr->data <= data && data <= nextToCurr->data) {
                break;
            }

            // Case 2: Turning point (from max to min)
            // This means curr is at the largest element, and nextToCurr is at the smallest
            if (curr->data > nextToCurr->data) {
                // Insert at wrap-around if:

                // - data is smaller than current min or
                // - data is greater than current max
                if (data <= nextToCurr->data || data >= curr->data) {
                    break;
                }
            }

            // Move both pointers ahead in the circular list
            curr       = curr->next;
            nextToCurr = nextToCurr->next;
        }

        // Step 4: Insert the new node between curr and nextToCurr
        curr->next    = newNode;
        newNode->next = nextToCurr;

        // Step 5: If inserted before head (i.e., new minimum), return newNode as new head
        return (data < head->data) ? newNode : head;
    }
};

/*
 * Dry Run 1: Inserting in the Middle
 *
 * // Input: data = 5, linked list = 1 -> 3 -> 6 -> 9 (circular)
 * // Start: curr = 1, nextToCurr = 3
 *
 * 1st Iteration:
 * curr = 1, nextToCurr = 3
 * → 1 <= 5 <= 3? No
 * → curr->data (1) < nextToCurr->data (3), so move forward
 * → curr = 3, nextToCurr = 6
 *
 * 2nd Iteration:
 * curr = 3, nextToCurr = 6
 * → 3 <= 5 <= 6 → Yes! Insert here
 *
 * // Insert new node with data 5 between 3 and 6
 * // Result: 1 -> 3 -> 5 -> 6 -> 9 (circular)
 * // Since 5 is not less than head (1), return head.
 *
 *
 *
 * Dry Run 2: Inserting as New Minimum
 *
 * // Input: data = 1, linked list = 2 -> 4 -> 6 -> 9 (circular)
 * // Start: curr = 2, nextToCurr = 4
 *
 * 1st Iteration:
 * curr = 2, nextToCurr = 4
 * → 2 <= 1 <= 4? No
 * → Not wrap-around, move ahead → curr = 4, nextToCurr = 6
 *
 * 2nd Iteration:
 * curr = 4, nextToCurr = 6
 * → 4 <= 1 <= 6? No → move ahead → curr = 6, nextToCurr = 9
 *
 * 3rd Iteration:
 * curr = 6, nextToCurr = 9
 * → 6 <= 1 <= 9? No → move ahead → curr = 9, nextToCurr = 2
 *
 * 4th Iteration:
 * curr = 9, nextToCurr = 2
 * → Detected wrap-around (curr->data > nextToCurr->data)
 * → 1 <= 2 or 1 >= 9? Yes → insert here
 *
 * // Insert 1 between 9 and 2
 * // Result: 1 -> 2 -> 4 -> 6 -> 9 (circular)
 * // 1 < head (2), so return newNode (1) as new head
 *
 *
 *
 * Dry Run 3: Inserting as New Maximum
 *
 * // Input: data = 11, linked list = 2 -> 4 -> 6 -> 9 (circular)
 * // Start: curr = 2, nextToCurr = 4
 *
 * 1st Iteration:
 * curr = 2, nextToCurr = 4
 * → 2 <= 11 <= 4? No → not wrap-around → move ahead
 *
 * 2nd Iteration:
 * curr = 4, nextToCurr = 6
 * → 4 <= 11 <= 6? No → move ahead
 *
 * 3rd Iteration:
 * curr = 6, nextToCurr = 9
 * → 6 <= 11 <= 9? No → move ahead
 *
 * 4th Iteration:
 * curr = 9, nextToCurr = 2
 * → Detected wrap-around (9 > 2)
 * → 11 <= 2 or 11 >= 9? Yes → insert here
 *
 * // Insert 11 between 9 and 2
 * // Result: 2 -> 4 -> 6 -> 9 -> 11 (circular)
 * // 11 > head (2), so return head
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Traverse the circular linked list using two pointers (curr and nextToCurr) to find the correct position to insert the new node such that the list remains sorted. There are 3 cases to handle: inserting in the middle of two nodes, inserting as the new minimum (before current head), or inserting as the new maximum (at the wrap-around point).
// Time Complexity: O(n) In the worst case, we may traverse all 'n' nodes in the circular linked list once to find the correct insertion point.
// Space Complexity: O(1) Only a constant amount of extra space is used for pointers and the new node.

/*
 * class Node {
 *  int data;
 *  Node next;
 *
 *  Node(int x) {
 *      data = x;
 *      next = null;
 *  }
 * }
 */

class Solution {
    public Node sortedInsert(Node head, int data) {
        // Step 1: Create the new node with given data
        Node newNode = new Node(data);

        // Case: Empty list (should not occur as per constraints, but safe check)
        if (head == null) {
            newNode.next = newNode;
            return newNode;
        }

        // Step 2: Initialize two pointers
        Node curr       = head;
        Node nextToCurr = head.next;

        // Step 3: Traverse the circular list to find correct insertion point
        while (true) {
            // Case 1: Normal case — insert between two nodes in sorted order
            if (curr.data <= data && data <= nextToCurr.data) {
                break;
            }

            // Case 2: Turning point (from max to min)
            // This means curr is at the largest element, and nextToCurr is at the smallest
            if (curr.data > nextToCurr.data) {
                // Insert at wrap-around if:
                // - data is smaller than current min or
                // - data is greater than current max
                if (data <= nextToCurr.data || data >= curr.data) {
                    break;
                }
            }

            // Move both pointers ahead in the circular list
            curr       = curr.next;
            nextToCurr = nextToCurr.next;

            // If we came full circle, insert here
            if (curr == head) {
                break;
            }
        }

        // Step 4: Insert the new node between curr and nextToCurr
        curr.next    = newNode;
        newNode.next = nextToCurr;

        // Step 5: If inserted before head (i.e., new minimum), return newNode as new head
        return (data < head.data) ? newNode : head;
    }
}

/*
 * Dry Run 1: Inserting in the Middle
 *
 * // Input: data = 5, linked list = 1 -> 3 -> 6 -> 9 (circular)
 * // Start: curr = 1, nextToCurr = 3
 *
 * 1st Iteration:
 * curr = 1, nextToCurr = 3
 * → 1 <= 5 <= 3? No
 * → curr->data (1) < nextToCurr->data (3), so move forward
 * → curr = 3, nextToCurr = 6
 *
 * 2nd Iteration:
 * curr = 3, nextToCurr = 6
 * → 3 <= 5 <= 6 → Yes! Insert here
 *
 * // Insert new node with data 5 between 3 and 6
 * // Result: 1 -> 3 -> 5 -> 6 -> 9 (circular)
 * // Since 5 is not less than head (1), return head.
 *
 *
 *
 * Dry Run 2: Inserting as New Minimum
 *
 * // Input: data = 1, linked list = 2 -> 4 -> 6 -> 9 (circular)
 * // Start: curr = 2, nextToCurr = 4
 *
 * 1st Iteration:
 * curr = 2, nextToCurr = 4
 * → 2 <= 1 <= 4? No
 * → Not wrap-around, move ahead → curr = 4, nextToCurr = 6
 *
 * 2nd Iteration:
 * curr = 4, nextToCurr = 6
 * → 4 <= 1 <= 6? No → move ahead → curr = 6, nextToCurr = 9
 *
 * 3rd Iteration:
 * curr = 6, nextToCurr = 9
 * → 6 <= 1 <= 9? No → move ahead → curr = 9, nextToCurr = 2
 *
 * 4th Iteration:
 * curr = 9, nextToCurr = 2
 * → Detected wrap-around (curr->data > nextToCurr->data)
 * → 1 <= 2 or 1 >= 9? Yes → insert here
 *
 * // Insert 1 between 9 and 2
 * // Result: 1 -> 2 -> 4 -> 6 -> 9 (circular)
 * // 1 < head (2), so return newNode (1) as new head
 *
 *
 *
 * Dry Run 3: Inserting as New Maximum
 *
 * // Input: data = 11, linked list = 2 -> 4 -> 6 -> 9 (circular)
 * // Start: curr = 2, nextToCurr = 4
 *
 * 1st Iteration:
 * curr = 2, nextToCurr = 4
 * → 2 <= 11 <= 4? No → not wrap-around → move ahead
 *
 * 2nd Iteration:
 * curr = 4, nextToCurr = 6
 * → 4 <= 11 <= 6? No → move ahead
 *
 * 3rd Iteration:
 * curr = 6, nextToCurr = 9
 * → 6 <= 11 <= 9? No → move ahead
 *
 * 4th Iteration:
 * curr = 9, nextToCurr = 2
 * → Detected wrap-around (9 > 2)
 * → 11 <= 2 or 11 >= 9? Yes → insert here
 *
 * // Insert 11 between 9 and 2
 * // Result: 2 -> 4 -> 6 -> 9 -> 11 (circular)
 * // 11 > head (2), so return head
 *
 */
