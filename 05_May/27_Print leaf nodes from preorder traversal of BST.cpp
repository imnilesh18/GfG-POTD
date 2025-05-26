/*
 * GfG Link: https://www.geeksforgeeks.org/problems/print-leaf-nodes-from-preorder-traversal-of-bst2657/1
 *
 * Print leaf nodes from preorder traversal of BST
 *
 * Difficulty: Medium Accuracy: 47.26% Submissions: 23K+ Points: 4
 *
 * Given a preorder traversal of a BST, find the leaf nodes of the tree without building the tree.
 *
 * Examples:
 *
 * Input: preorder[] = [5, 2, 10]
 * Output: [2, 10]
 * Explaination:
 * 2 and 10 are the leaf nodes as shown in the figure.
 *
 * Input: preorder[] = [4, 2, 1, 3, 6, 5]
 * Output: [1, 3, 5]
 * Explaination:
 * 1, 3 and 5 are the leaf nodes as shown in the figure.
 * Input: preorder[] = [8, 2, 5, 10, 12]
 * Output: [5, 12]
 * Explaination:
 * 5 and 12 are the leaf nodes as shown in the figure.
 *
 * Constraints:
 * 1 ≤ preorder.size() ≤ 10^3
 * 1 ≤ preorder[i] ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach: Use a stack to simulate BST insertion from preorder and detect leaf nodes based on how many ancestors are popped. If two or more nodes are popped, the previous node is a leaf.
// Time Complexity: O(n) – each element is pushed and popped at most once.
// Space Complexity: O(n) – stack can grow up to n in worst case.
class Solution {
public:
    vector<int> leafNodes(vector<int>& preorder) {
        stack<int>  st;     // Stack to simulate the path of nodes in BST
        vector<int> result; // To store the final leaf nodes

        for (int i = 0; i < preorder.size(); i++) {
            int count = 0;
            int curr  = preorder[i]; // Current node in preorder

            // Pop until we find a node greater than current, simulating right child path
            while (!st.empty() && curr > st.top()) {
                st.pop();
                count++;
            }

            // If two or more nodes are popped, then the previous node is a leaf
            if (count >= 2) {
                result.push_back(preorder[i - 1]);
            }

            // Push current node to stack
            st.push(curr);
        }

        // Last node is always a leaf in preorder traversal
        result.push_back(preorder.back());

        return result;
    }
};

/*
 *
 * Dry Run
 * Input: preorder = [4, 2, 1, 3, 6, 5]
 *
 * i = 0, curr = 4
 *   stack = [] -> push 4
 *
 * i = 1, curr = 2
 *   stack = [4] -> push 2
 *
 * i = 2, curr = 1
 *   stack = [4, 2] -> push 1
 *
 * i = 3, curr = 3
 *   stack = [4, 2, 1]
 *   pop 1 -> count = 1
 *   pop 2 -> count = 2
 *   (count >= 2) -> push preorder[2] = 1 to result
 *   push 3
 *
 * i = 4, curr = 6
 *   stack = [4, 3]
 *   pop 3 -> count = 1
 *   pop 4 -> count = 2
 *   (count >= 2) -> push preorder[3] = 3 to result
 *   push 6
 *
 * i = 5, curr = 5
 *   stack = [6] -> push 5
 *
 * End of loop, add preorder.back() = 5 to result
 *
 * Final result = [1, 3, 5]
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a stack to simulate BST insertion from preorder and detect leaf nodes based on how many ancestors are popped. If two or more nodes are popped, the previous node is a leaf.
// Time Complexity: O(n) – each element is pushed and popped at most once.
// Space Complexity: O(n) – stack can grow up to n in worst case.
class Solution {
    public ArrayList<Integer> leafNodes(int[] preorder) {
        Stack<Integer>     st     = new Stack<>();     // Stack to simulate the path of nodes in BST
        ArrayList<Integer> result = new ArrayList<>(); // To store the final leaf nodes

        for (int i = 0; i < preorder.length; i++) {
            int count = 0;
            int curr  = preorder[i]; // Current node in preorder

            // Pop until we find a node greater than current, simulating right child path
            while (!st.isEmpty() && curr > st.peek()) {
                st.pop();
                count++;
            }

            // If two or more nodes are popped, then the previous node is a leaf
            if (count >= 2) {
                result.add(preorder[i - 1]);
            }

            // Push current node to stack
            st.push(curr);
        }

        // Last node is always a leaf in preorder traversal
        result.add(preorder[preorder.length - 1]);

        return result;
    }
}

/*
 *
 * Dry Run
 * Input: preorder = [4, 2, 1, 3, 6, 5]
 *
 * i = 0, curr = 4
 *   stack = [] -> push 4
 *
 * i = 1, curr = 2
 *   stack = [4] -> push 2
 *
 * i = 2, curr = 1
 *   stack = [4, 2] -> push 1
 *
 * i = 3, curr = 3
 *   stack = [4, 2, 1]
 *   pop 1 -> count = 1
 *   pop 2 -> count = 2
 *   (count >= 2) -> add preorder[2] = 1 to result
 *   push 3
 *
 * i = 4, curr = 6
 *   stack = [4, 3]
 *   pop 3 -> count = 1
 *   pop 4 -> count = 2
 *   (count >= 2) -> add preorder[3] = 3 to result
 *   push 6
 *
 * i = 5, curr = 5
 *   stack = [6] -> push 5
 *
 * End of loop, add preorder[5] = 5 to result
 *
 * Final result = [1, 3, 5]
 */
