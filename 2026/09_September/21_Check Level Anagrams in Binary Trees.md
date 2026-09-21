# 🌳 Check if all levels of two trees are anagrams or not

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/check-if-all-levels-of-two-trees-are-anagrams-or-not/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" /></a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-FFB81C?style=for-the-badge" alt="Difficulty Medium" />
    <img src="https://img.shields.io/badge/Accuracy-56.88%25-brightgreen?style=for-the-badge" alt="Accuracy 56.88%" />
    <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points 4" />
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem[cite: 1].

---

## 📝 Problem Statement

Given the roots of two binary trees `root1` and `root2`, check whether the nodes at every corresponding level of the two trees are anagrams of each other[cite: 1].

Two levels are considered anagrams if they contain the same node values with the same frequencies, regardless of their order[cite: 1].

---

## 💡 Examples

### Example 1

```text
Input: root1 = [1, 3, 2, N, N, 5, 4], root2 = [1, 2, 3, 4, 5, N, N]
Output: true

```

> **Explanation:**
> Level 0: [1] and [1]
> Level 1: [3, 2] and [2, 3]
> Level 2: [5, 4] and [4, 5]
> The node values at every corresponding level are anagrams of each other. Hence, the answer is true.
> 
> 

### Example 2

```text
Input: root1 = [1, 2, 3, 5, 4], root2 = [1, 2, 4, 5, 3]
Output: false

```

> **Explanation:**
> Level 0: [1] and [1]
> Level 1: [2, 3] and [2, 4]
> Since the node values at level 1 are not anagrams, the answer is false.
> 
> 

Let's visualize the first example step-by-step:

**Tree 1:**

```text
       1
     /   \
    3     2
         / \
        5   4

```

**Tree 2:**

```text
       1
     /   \
    2     3
   / \
  4   5

```

1. **Level 0:**
* Tree 1 nodes: `[1]`
* Tree 2 nodes: `[1]`
* Frequencies match perfectly.


2. **Level 1:**
* Tree 1 nodes: `[3, 2]`
* Tree 2 nodes: `[2, 3]`
* Both levels have one `2` and one `3`. They are anagrams.


3. **Level 2:**
* Tree 1 nodes: `[5, 4]`
* Tree 2 nodes: `[4, 5]`
* Both levels have one `4` and one `5`. They are anagrams.



Since all levels are anagrams, the final output is `true`.

---

## ⚠️ Constraints

* `1 ≤ size of binary tree ≤ 10^5`

* `1 ≤ node.data ≤ 10^6`

* The character `N` represents a null child.



---

## 🚀 Solution Approaches

### 1️⃣ Optimized Approach: Simultaneous BFS with Frequency Map

The most efficient way to solve this is to perform a Level Order Traversal (BFS) on both trees at the same time. At each level, we ensure the number of nodes in both trees is identical. To verify if they are anagrams, we use a Hash Map to count node occurrences for `root1` (incrementing) and `root2` (decrementing). If the map balances out to zero for all keys at the end of the level, the levels are anagrams.

```cpp
// Intuition: Check level by level whether node values in both trees form valid anagrams.[cite: 1]
// Approach: Perform simultaneous BFS traversal on both trees using queues. For each level, compare node counts and use a frequency map to verify if node values in root1 match those in root2.[cite: 1]
// Time Complexity: O(N) where N is the total number of nodes, as each node is visited once during traversal.[cite: 1]
// Space Complexity: O(N) auxiliary space used by queues and frequency map to store level nodes.[cite: 1]

/* Structure of binary tree Node[cite: 1]
class Node {
    public:
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};
*/

class Solution {
  public:
    bool areAnagrams(Node* root1, Node* root2) {
        // Handle empty tree base cases
        if (!root1 && !root2) return true;
        if (!root1 || !root2) return false;

        // Initialize queues for BFS
        queue<Node*> q1, q2;
        q1.push(root1);
        q2.push(root2);

        // Process trees level by level
        while (!q1.empty() && !q2.empty()) {
            int n1 = q1.size();
            int n2 = q2.size();

            // Mismatch in level size implies not anagrams
            if (n1 != n2) return false;

            // Map to track value frequencies for current level
            unordered_map<int, int> freq;

            // Process all nodes at the current level
            for (int i = 0; i < n1; i++) {
                Node* node1 = q1.front();
                q1.pop();
                Node* node2 = q2.front();
                q2.pop();

                // Increment for root1 nodes and decrement for root2 nodes
                freq[node1->data]++;
                freq[node2->data]--;

                // Add children to queues for the next level processing
                if (node1->left) q1.push(node1->left);
                if (node1->right) q1.push(node1->right);
                if (node2->left) q2.push(node2->left);
                if (node2->right) q2.push(node2->right);
            }

            // Check if all frequency balances are zero
            for (auto it : freq) {
                if (it.second != 0) return false;
            }
        }

        // Return true if both queues are completely exhausted simultaneously
        return q1.empty() && q2.empty();
    }
};

/*
* Dry Run
*
* Input: root1 = [1, 3, 2], root2 = [1, 2, 3][cite: 1]
* 
* Level 0 Processing
* Queue 1: [1], Queue 2: [1][cite: 1]
* Level sizes: n1 = 1, n2 = 1[cite: 1]
* Pop node 1 from q1, node 1 from q2[cite: 1]
* Update frequencies: freq[1] = 1 - 1 = 0[cite: 1]
* Push children: q1 gets [3, 2], q2 gets [2, 3][cite: 1]
* Frequency check passes[cite: 1]
* 
* Level 1 Processing
* Queue 1: [3, 2], Queue 2: [2, 3][cite: 1]
* Level sizes: n1 = 2, n2 = 2[cite: 1]
* Iteration 1: Pop 3 from q1, 2 from q2 -> freq[3] = 1, freq[2] = -1[cite: 1]
* Iteration 2: Pop 2 from q1, 3 from q2 -> freq[2] = 0, freq[3] = 0[cite: 1]
* Push children: None (leaf nodes)[cite: 1]
* Frequency check passes[cite: 1]
* 
* Traversal completes successfully with both queues empty[cite: 1]
* Output: true[cite: 1]
*/

```

---

## 🧠 Key Insights

* **Simultaneous Traversal:** Processing both trees in lockstep ensures we never waste time evaluating deeper levels if a structural or value mismatch occurs early.
* **Efficient Matching:** Instead of sorting the values at each level (which would take $O(K \log K)$ time per level), we use an `unordered_map`. Adding frequencies from `root1` and subtracting from `root2` allows us to validate an anagram match in linear $O(K)$ time for each level.

---

## 🔍 Further Exploration

If you enjoyed this tree-level manipulation, consider trying out these related problems:

1. **Check if Two Trees are Identical** - A simpler variant without the anagram requirement.
2. **Binary Tree Level Order Traversal** - Fundamental BFS technique.
3. **Determine if Two Trees are Isomorphic** - Structural tree comparison.

---

## 🔗 References

* **GeeksforGeeks Problem:** [Check if all levels of two trees are anagrams or not](https://www.geeksforgeeks.org/problems/check-if-all-levels-of-two-trees-are-anagrams-or-not/1?utm_source=gemini)


---

## 🧑‍💻 Author

**Nilesh Kumar**

* GitHub: [imnilesh18](https://github.com/imnilesh18?utm_source=gemini)

---

## 🏷️ Tags

`#Tree` `#Breadth-First-Search` `#Data-Structures` `#GeeksforGeeks` `#C++`