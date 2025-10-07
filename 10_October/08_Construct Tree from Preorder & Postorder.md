# 🌳 Construct Tree from Preorder & Postorder

![GFG](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-89.04%25-brightgreen?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

---

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/construct-tree-from-preorder-postorder/1).

---

## 📝 Problem Statement

Given two arrays `pre[]` and `post[]` that represent the **preorder** and **postorder** traversals of a **full binary tree**. Your task is to construct the binary tree and return its **root**.

**Note:** A **Full Binary Tree** is a binary tree where every node has either 0 or 2 children. The preorder and postorder traversals contain unique values, and every value present in the preorder traversal is also found in the postorder traversal.

---

## 🧪 Examples

<details>
<summary>📖 Example 1 Breakdown</summary>

* **Input:** `pre[] = [1, 2, 4, 8, 9, 5, 3, 6, 7]`, `post[] = [8, 9, 4, 5, 2, 6, 7, 3, 1]`
* **Output:** `[1, 2, 3, 4, 5, 6, 7, 8, 9]`
* **Tree Structure:**
    ```
          1
        /   \
       2     3
      / \   / \
     4   5 6   7
    / \
   8   9
    ```
* **Explanation:**
    1.  The first element of `pre` is always the root (1).
    2.  The element after the root in `pre` is the root of the left subtree (2).
    3.  Find 2 in `post`. All elements before it (`[8, 9, 4, 5]`) belong to the left subtree of 1.
    4.  The remaining elements in `post` (before the root 1), which are `[6, 7, 3]`, belong to the right subtree.
    5.  Recursively build the left and right subtrees using the identified segments of `pre` and `post`.

</details>

```
Input: pre[] = [1, 2, 4, 5, 3, 6, 7], post[] = [4, 5, 2, 6, 7, 3, 1]
Output: [1, 2, 3, 4, 5, 6, 7]
```

---

## ⛓️ Constraints

* `1 ≤ number of nodes ≤ 10^3`
* `1 ≤ pre[i], post[i] ≤ 10^4`

---

## 💡 Solution Approaches

### 🚀 Brute-Force (Recursive)

The core idea is to recursively build the tree. The first element of the preorder traversal is the root of the current subtree. The next element in the preorder traversal is the root of the left subtree. We can find this left subtree's root in the postorder traversal to determine which nodes belong to the left and right subtrees.

```cpp
// Intuition: The first element in preorder is the root. The next element is the root of the left subtree. We can use this information to find the boundary of the left and right subtrees in the postorder traversal.
// Approach:
// 1. Pick the first element from `preorder` as the root.
// 2. If there's more than one element, the second element `preorder[prestart + 1]` is the root of the left subtree.
// 3. Search for this `nextNode` in the `postorder` array. All elements from `poststart` up to where `nextNode` is found belong to the left subtree.
// 4. The number of elements in the left subtree helps determine the range of elements for the left and right subtrees in the `preorder` array.
// 5. Recursively call the function for the left and right subtrees with the calculated indices.
// Time Complexity: O(N^2), because of the linear search for `nextNode` in the `postorder` array for each node.
// Space Complexity: O(N) for the recursion stack space, which in the worst case (a skewed tree) can be N.
/*
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};
*/

class Solution {
  public:
   
    Node* solve(int prestart, int poststart, int preend, vector<int> &preorder, vector<int> &postorder) {
         
        if(prestart > preend) { // Base case: If the start index exceeds the end, there are no nodes to process.
            return NULL;
        }
         
        Node* root = new Node(preorder[prestart]); // The first element in the current preorder segment is the root.
        if(prestart == preend) { // If there's only one element, it's a leaf node.
            return root;
        }
        int nextNode = preorder[prestart + 1]; // The next node in preorder is the root of the left subtree.
         
        int j = poststart; // Start searching for the left subtree's root in the postorder array.
        while(postorder[j] != nextNode) {
            j++;
        }
         
        int num = j - poststart + 1; // Calculate the number of nodes in the left subtree.
         
        root->left = solve(prestart + 1, poststart, prestart + num, preorder, postorder); // Recursively build the left subtree.
        root->right = solve(prestart + num + 1, j + 1, preend, preorder, postorder); // Recursively build the right subtree.
         
        return root;
         
    }
   
    Node *constructTree(vector<int> &preorder, vector<int> &postorder) {
        int n = preorder.size();
        return solve(0, 0, n - 1, preorder, postorder); // Initial call to the recursive helper function.
    }
};

/*
*
* Dry Run
*
* pre[] = [1, 2, 4, 5, 3, 6, 7], post[] = [4, 5, 2, 6, 7, 3, 1]
* * Initial call: solve(0, 0, 6, pre, post)
* - root = Node(1)
* - nextNode = 2
* - Find 2 in post: j = 2
* - num = 2 - 0 + 1 = 3
* - root->left = solve(1, 0, 1 + 3, pre, post) -> solve(1, 0, 4, ...)
* - root->right = solve(1 + 3 + 1, 2 + 1, 6, pre, post) -> solve(5, 3, 6, ...)
*
* Left subtree call: solve(1, 0, 4, ...)
* - root = Node(2)
* - nextNode = 4
* - Find 4 in post: j = 0
* - num = 0 - 0 + 1 = 1
* - root->left = solve(2, 0, 2, ...) -> returns Node(4)
* - root->right = solve(3, 1, 3, ...) -> returns Node(5)
*
* Right subtree call: solve(5, 3, 6, ...)
* - root = Node(3)
* - nextNode = 6
* - Find 6 in post: j = 3
* - num = 3 - 3 + 1 = 1
* - root->left = solve(6, 3, 6, ...) -> returns Node(6)
* - root->right = solve(7, 4, 6, ...) -> returns Node(7)
*
*/
```

### ⚡ Optimized (Recursive with HashMap)

To optimize the search for the `nextNode` in the `postorder` array, we can pre-process the `postorder` array and store the indices of its elements in a hash map. This reduces the search time from O(N) to O(1).

```cpp
// Intuition: Same as the brute-force approach, but we optimize the search for the left subtree's root in the postorder array.
// Approach:
// 1. Create a hash map to store each element of the `postorder` array and its corresponding index.
// 2. The rest of the logic remains the same as the brute-force approach.
// 3. When we need to find the index of `nextNode`, we look it up in the hash map, which takes O(1) time.
// Time Complexity: O(N), as we iterate through each node once, and the search operation is now O(1).
// Space Complexity: O(N) for both the recursion stack and the hash map.
/*
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};
*/

class Solution {
  public:
   
    Node* solve(int prestart, int poststart, int preend, vector<int> &preorder, vector<int> &postorder, 
                unordered_map<int, int> &mp) {
         
        if(prestart > preend) { // Base case
            return NULL;
        }
         
        Node* root = new Node(preorder[prestart]); // Create the root node
        if(prestart == preend) { // Leaf node condition
            return root;
        }
        int nextNode = preorder[prestart + 1]; // Root of the left subtree
         
        int j = mp[nextNode]; // Find the index of the left subtree's root in O(1)
         
        int num = j - poststart + 1; // Number of nodes in the left subtree
         
        root->left = solve(prestart + 1, poststart, prestart + num, preorder, postorder, mp); // Build left subtree
        root->right = solve(prestart + num + 1, j + 1, preend, preorder, postorder, mp); // Build right subtree
         
        return root;
         
    }
   
    Node *constructTree(vector<int> &preorder, vector<int> &postorder) {
        int n = preorder.size();
         
        unordered_map<int, int> mp; // HashMap to store indices
        for(int i = 0; i < n; i++) {
            mp[postorder[i]] = i; // Pre-compute indices of postorder elements
        }
         
        return solve(0, 0, n - 1, preorder, postorder, mp);
    }
};

/*
*
* Dry Run
*
* pre[] = [1, 2, 4, 5, 3, 6, 7], post[] = [4, 5, 2, 6, 7, 3, 1]
* mp = {4:0, 5:1, 2:2, 6:3, 7:4, 3:5, 1:6}
* * Initial call: solve(0, 0, 6, pre, post, mp)
* - root = Node(1)
* - nextNode = 2
* - j = mp[2] -> 2
* - num = 2 - 0 + 1 = 3
* - root->left = solve(1, 0, 4, ...)
* - root->right = solve(5, 3, 6, ...)
* * ...The rest of the execution is similar to the brute-force dry run, but the lookup for 'j' is O(1).
*
*/
```

---

## 🎯 Key Insights

The main bottleneck in the brute-force approach is the repeated linear search for the root of the left subtree within the `postorder` array. By using a **hash map** to store the indices of elements in the `postorder` array, we can reduce the search time to constant time, O(1), thereby optimizing the overall time complexity from O(N²) to O(N).

---

## 🔎 Further Exploration

* [Construct Tree from Inorder & Preorder](https://www.geeksforgeeks.org/problems/construct-tree-from-inorder-and-preorder/1)
* [Construct Tree from Inorder & Postorder](https://www.geeksforgeeks.org/problems/tree-from-postorder-and-inorder/1)

---

## 📚 References

* [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/construct-tree-from-preorder-postorder/1)

---

## 👨‍💻 Author

* [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Binary Tree](https://img.shields.io/badge/Binary_Tree-blue?style=for-the-badge)
![Recursion](https://img.shields.io/badge/Recursion-orange?style=for-the-badge)
![Data Structures](https://img.shields.io/badge/Data_Structures-green?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-gray?style=for-the-badge)

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
**Reminder:** This content is for educational purposes only.