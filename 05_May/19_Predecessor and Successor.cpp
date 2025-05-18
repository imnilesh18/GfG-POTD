/*
 * GfG Link: https://www.geeksforgeeks.org/problems/predecessor-and-successor/1
 *
 * Predecessor and Successor
 *
 * Difficulty: Medium Accuracy: 47.36% Submissions: 137K+ Points: 4
 *
 * You are given root node of the BST and an integer key. You need to find the in-order successor and predecessor of the given key. If either predecessor or successor is not found, then set it to NULL.
 * Note:- In an inorder traversal the number just smaller than the target is the predecessor and the number just greater than the target is the successor.
 *
 * Examples :
 *
 * Input: root[] = [8, 1, 9, N, 4, N, 10, 3, N, N, N], key = 8
 * Output: 4 9
 * Explanation: In the given BST the inorder predecessor of 8 is 4 and inorder successor of 8 is 9.
 *
 * Input: root[] = [10, 2, 11, 1, 5, N, N, N, N, 3, 6, N, 4, N, N], key = 11
 * Output: 10 -1
 * Explanation: In given BST, the inorder predecessor of 11 is 10 whereas it does not have any inorder successor.
 *
 * Input: root[] = [2, 1, 3], key = 3
 * Output: 2 -1
 * Explanation: In given BST, the inorder predecessor of 3 is 2 whereas it does not have any inorder successor.
 *
 * Constraints:
 * 1 <= no. of nodes <= 10^5
 * 1 <= node->data <= 10^6
 * 1 <= key <= 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1: Perform an inorder traversal to store all nodes in a vector. Then linearly search for the key and its predecessor and successor.
// Time Complexity: O(N) — where N is the number of nodes in the BST, due to inorder traversal and single pass through the vector.
// Space Complexity: O(N) — storing all nodes in the inorder traversal result vector.

/* BST Node
 * class Node
 * {
 * public:
 *  int data;
 *  Node *left;
 *  Node *right;
 *
 *  Node(int x){
 *      data = x;
 *      left = NULL;
 *      right = NULL;
 *  }
 * }; */

class Solution {
public:

    // Helper function to perform inorder traversal and store nodes in a vector
    void inorder(Node* root, vector<Node*>& result) {
        if (!root) {
            return;
        }
        inorder(root->left, result);         // Traverse left subtree
        result.push_back(root);              // Visit current node
        inorder(root->right, result);        // Traverse right subtree
    }
    // Function to find predecessor and successor of given key
    vector<Node*> findPreSuc(Node* root, int key) {
        vector<Node*> result;                // Vector to store inorder traversal result

        inorder(root, result);               // Fill the vector with inorder traversal

        Node* pre = NULL;                    // Pointer to store predecessor
        Node* suc = NULL;                    // Pointer to store successor

        for (int i = 0; i < result.size(); i++) {
            if (result[i]->data < key) {
                pre = result[i];             // Keep updating predecessor until key is found
            } else if (result[i]->data > key) {
                suc = result[i];             // First greater element after key is the successor
                break;
            } else {
                if (i - 1 >= 0) {
                    pre = result[i - 1];     // Element before key is predecessor
                }
                if (i + 1 < result.size()) {
                    suc = result[i + 1];     // Element after key is successor
                }
                break;                       // Break after finding key
            }
        }
        return { pre, suc };                   // Return both predecessor and successor
    }
};

/*
 *
 * Dry Run
 *
 *               30
 *             /    \
 *           20     40
 *         /   \      \
 *       10     25     50
 *      /  \    /
 *     5   15  23
 *          \
 *          18
 *
 *
 * Inorder traversal of BST:
 * [5, 10, 15, 18, 20, 23, 25, 30, 40, 50]
 *
 * Now we search for the key = 20 in the result vector.
 *
 * Loop:
 * i = 0 → 5 < 20 → pre = 5
 * i = 1 → 10 < 20 → pre = 10
 * i = 2 → 15 < 20 → pre = 15
 * i = 3 → 18 < 20 → pre = 18
 * i = 4 → 20 == 20
 *     → i-1 = 3 → pre = result[3] = 18
 *     → i+1 = 5 → suc = result[5] = 23
 *
 * Result: Predecessor = 18, Successor = 23
 *
 */

// Approach 2: Use BST properties to find predecessor and successor in O(h) time by traversing down the tree.
// Time Complexity: O(h) — where h is the height of the BST, as we traverse top to bottom.
// Space Complexity: O(1) — no extra space used apart from variables.

// BST Node
/*
 * class Node
 * {
 * public:
 *  int data;
 *  Node *left;
 *  Node *right;
 *
 *  Node(int x){
 *      data = x;
 *      left = NULL;
 *      right = NULL;
 *  }
 * };
 */

class Solution {
public:

    // Helper function to find the rightmost node in the left subtree
    Node* rightMost(Node* node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }
    // Helper function to find the leftmost node in the right subtree
    Node* leftMost(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
    // Function to find predecessor and successor
    vector<Node*> findPreSuc(Node* root, int key) {
        Node* pre  = nullptr;     // To store predecessor
        Node* curr = root;        // Start from root
        Node* suc  = nullptr;     // To store successor

        while (curr) {
            if (curr->data < key) {
                pre  = curr;              // Current node could be predecessor
                curr = curr->right;       // Move to right to find closer value
            }else if (curr->data > key) {
                suc  = curr;              // Current node could be successor
                curr = curr->left;        // Move to left to find closer value
            }else {
                if (curr->left) {
                    pre = rightMost(curr->left); // Rightmost node in left subtree is predecessor
                }
                if (curr->right) {
                    suc = leftMost(curr->right); // Leftmost node in right subtree is successor
                }
                break;                           // Key found, no need to search further
            }
        }

        return { pre, suc };                // Return pair of predecessor and successor
    }
};

/*
 *
 * Dry Run
 *
 *               30
 *             /    \
 *           20     40
 *         /   \      \
 *       10     25     50
 *      /  \    /
 *     5   15  23
 *          \
 *          18
 *
 * Key = 20
 *
 * Start from root (30):
 * 30 > 20 → suc = 30, move left
 * 20 == 20 →
 *    → curr->left exists → pre = rightMost(10)
 *       → rightMost(10) = 15 → 15 has right → move to 18 → no right → pre = 18
 *    → curr->right exists → suc = leftMost(25)
 *       → leftMost(25) = 23 → no left → suc = 23
 *
 * Final Answer: Predecessor = 18, Successor = 23
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Perform an inorder traversal to store all nodes in a list. Then linearly search for the key and its predecessor and successor.
// Time Complexity: O(N) — where N is the number of nodes in the BST, due to inorder traversal and single pass through the list.
// Space Complexity: O(N) — storing all nodes in the inorder traversal result list.

/* BST Node
 * class Node {
 *  int data;
 *  Node left, right;
 *  Node(int x) {
 *      data = x;
 *      left = right = null;
 *  }
 * } */

class Solution {
    // Helper method to perform inorder traversal and store nodes
    private void inorder(Node root, ArrayList<Node> result) {
        if (root == null) {
            return;
        }
        inorder(root.left, result);           // Traverse left subtree
        result.add(root);                     // Visit current node
        inorder(root.right, result);          // Traverse right subtree
    }
    public ArrayList<Node> findPreSuc(Node root, int key) {
        ArrayList<Node> result = new ArrayList<>(); // Stores inorder traversal result

        inorder(root, result);                      // Fill the list with inorder traversal

        Node pre = null;                            // Pointer to store predecessor
        Node suc = null;                            // Pointer to store successor

        for (int i = 0; i < result.size(); i++) {
            if (result.get(i).data < key) {
                pre = result.get(i);                // Keep updating predecessor until key is found
            } else if (result.get(i).data > key) {
                suc = result.get(i);                // First greater element after key is the successor
                break;
            } else {
                if (i - 1 >= 0) {
                    pre = result.get(i - 1);        // Element before key is predecessor
                }
                if (i + 1 < result.size()) {
                    suc = result.get(i + 1);        // Element after key is successor
                }
                break;                              // Break after finding key
            }
        }

        ArrayList<Node> ans = new ArrayList<>();
        ans.add(pre);                               // Add predecessor
        ans.add(suc);                               // Add successor
        return ans;                                 // Return result
    }
}

/*
 *
 * Dry Run
 *
 *               30
 *             /    \
 *           20     40
 *         /   \      \
 *       10     25     50
 *      /  \    /
 *     5   15  23
 *          \
 *          18
 *
 *
 * Inorder traversal of BST:
 * [5, 10, 15, 18, 20, 23, 25, 30, 40, 50]
 *
 * Now we search for the key = 20 in the result list.
 *
 * Loop:
 * i = 0 → 5 < 20 → pre = 5
 * i = 1 → 10 < 20 → pre = 10
 * i = 2 → 15 < 20 → pre = 15
 * i = 3 → 18 < 20 → pre = 18
 * i = 4 → 20 == 20
 *     → i-1 = 3 → pre = result[3] = 18
 *     → i+1 = 5 → suc = result[5] = 23
 *
 * Result: Predecessor = 18, Successor = 23
 *
 */

// Approach 2: Use BST properties to traverse down the tree and find predecessor and successor without extra space.
// Time Complexity: O(h) — where h is the height of the BST, due to top-down traversal.
// Space Complexity: O(1) — only constant extra space used for pointers.

/* BST Node
 * class Node {
 *  int data;
 *  Node left, right;
 *
 *  Node(int x) {
 *      data = x;
 *      left = right = null;
 *  }
 * }
 */

class Solution {
    // Helper to find rightmost node (max value) in a subtree
    private Node rightMost(Node node) {
        while (node.right != null) {
            node = node.right;
        }
        return node;
    }
    // Helper to find leftmost node (min value) in a subtree
    private Node leftMost(Node node) {
        while (node.left != null) {
            node = node.left;
        }
        return node;
    }
    // Function to find predecessor and successor
    public ArrayList<Node> findPreSuc(Node root, int key) {
        Node pre  = null;         // To store predecessor
        Node suc  = null;         // To store successor
        Node curr = root;         // Start traversal from root

        while (curr != null) {
            if (curr.data < key) {
                pre  = curr;      // Current node is a potential predecessor
                curr = curr.right;
            } else if (curr.data > key) {
                suc  = curr;      // Current node is a potential successor
                curr = curr.left;
            } else {
                if (curr.left != null) {
                    pre = rightMost(curr.left);  // Predecessor is rightmost of left subtree
                }
                if (curr.right != null) {
                    suc = leftMost(curr.right); // Successor is leftmost of right subtree
                }
                break;                          // Key found, break the loop
            }
        }

        ArrayList<Node> res = new ArrayList<>();
        res.add(pre);             // Add predecessor to result
        res.add(suc);             // Add successor to result
        return res;
    }
}

/*
 *
 * Dry Run
 *
 *               30
 *             /    \
 *           20     40
 *         /   \      \
 *       10     25     50
 *      /  \    /
 *     5   15  23
 *          \
 *          18
 *
 * Key = 20
 *
 * Start from root (30):
 * 30 > 20 → suc = 30, move left
 * 20 == 20 →
 *    → curr.left exists → pre = rightMost(10)
 *       → rightMost(10) = 15 → 15 has right → move to 18 → no right → pre = 18
 *    → curr.right exists → suc = leftMost(25)
 *       → leftMost(25) = 23 → no left → suc = 23
 *
 * Final Answer: Predecessor = 18, Successor = 23
 *
 */
