# 🔴🔵 Longest Colored Path

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/longest-colored-path--151454/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-36.5%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an undirected acyclic graph (tree) with `n` nodes numbered from `1` to `n`. Each node is colored either **Red (R)** or **Blue (B)**.

The colors of the nodes are given by a string `s` of length `n`, where:
* `s[i] = 'R'` means node `i + 1` is Red.
* `s[i] = 'B'` means node `i + 1` is Blue.

You are also given a list of `n - 1` edges `edges[][]`, where each `edges[i] = [u, v]` represents an undirected edge between nodes `u` and `v`.

You can start from any node and traverse along the edges to form a path. A path is called **valid** if, once you visit a Blue node, you **cannot** visit any Red node after it on the same path. 

In other words, a valid path must have the following form:
* Only Red nodes, or
* Only Blue nodes, or
* Some Red nodes followed by some Blue nodes.

*(A path containing a pattern like Blue -> Red is invalid).*

**Task:** Find the maximum number of nodes in a valid path.

---

## 💡 Examples

```text
Input: s = "RBB", edges = [[1, 2], [1, 3]] 
Output: 2
Explanation: The longest path is either 1 -> 2 or 1 -> 3. In both cases, the length of the path is 2.
```

```text
Input: s = "BB", edges = [[1, 2]]
Output: 2
Explanation: The longest path is 1 -> 2. The length of the path is 2.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's break down the first example:
* **Nodes & Colors:** 
  * Node 1: Red ('R')
  * Node 2: Blue ('B')
  * Node 3: Blue ('B')
* **Edges:** (1-2) and (1-3). This means Node 1 is the center connected to Node 2 and Node 3.
* **Possible Paths:**
  * Path `2 -> 1 -> 3`: Blue -> Red -> Blue. **Invalid** (Blue cannot be followed by Red).
  * Path `1 -> 2`: Red -> Blue. **Valid** (Length 2).
  * Path `1 -> 3`: Red -> Blue. **Valid** (Length 2).
* **Maximum valid path length:** 2.
</details>

---

## 🛑 Constraints

> * `s.size() ≤ 10^5`
> * `1 ≤ edges[i][j] ≤ s.size()`
> * `s` consists only of the characters `R` and `B`
> * `edges.size() == s.size() - 1`

---

## 🧠 Solution Approaches

### Tree DP with Rerooting (In-Out DP)

Since this problem is defined on a tree and we need to find the maximum path across *any* possible starting node, calculating paths independently for every node would result in an $O(N^2)$ Time Limit Exceeded (TLE) error. Instead, we can optimize this to $O(N)$ using the **Tree Re-rooting** technique.

1. **Bottom-Up DFS (In-DP):** First, we root the tree arbitrarily at node `0` and compute the maximum valid paths extending downwards into the subtrees. For every node, we calculate the max path if it were a Red node, and the max path if it were a Blue node.
2. **Top-Down DFS (Out-DP / Rerooting):** Next, we push the computed maximums from the parent downwards to its children. To do this efficiently, we keep track of the *top two* longest paths from the children of any node. If a child itself is on the longest path, we pass the second-longest path down to it; otherwise, we pass the longest path.
3. Combine the In-DP and Out-DP values for every node to find the global maximum path.

### 💻 C++ Code

```cpp
// Intuition: The problem asks for the longest valid path where a Blue node cannot be followed by a Red node. This translates to finding paths that are entirely Red, entirely Blue, or Red nodes transitioning to Blue nodes. Using Tree DP with Rerooting allows us to compute the best paths traversing through ancestors and subtrees efficiently.
// Approach:
// 1. Build an adjacency list to represent the tree.
// 2. Perform a bottom-up DFS (`root`) to calculate the maximum valid path length going down into the subtree for each node.
// 3. Perform a top-down DFS (`reroot`) to propagate the maximum path lengths from the parent and siblings downwards. We maintain the top two longest child paths to easily pass the best alternate path.
// 4. The overall answer is the maximum valid path length found across all nodes.
// Time Complexity: O(N) where N is the number of nodes, as we perform exactly two full DFS traversals over the tree.
// Space Complexity: O(N) for the adjacency list, DP tables, and recursion stack.

class Solution {
  public:
    // Perform a bottom-up DFS to calculate the best path
    // contribution coming from each node's subtree.
    void root(vector<vector<int>> &adj, string &s, 
            vector<vector<int>> &sa, int node = 0, int par = -1) {
        int ra = 0, ba = 0;

        // Process all children of the current node
        for (auto &it : adj[node]) {
            if (it == par) continue;

            // Calculate DP values for the child subtree
            root(adj, s, sa, it, node);

            // Store max possible contribution for a path ending at a Red node
            ra = max(ra, sa[it][0]);
            ra = max(ra, sa[it][1]);

            // Store max possible contribution for a path ending at a Blue node
            ba = max(ba, sa[it][1]);
        }

        // Calculate DP values based on the current node's color
        if (s[node] == 'R') {
            sa[node][0] = ra + 1;
            sa[node][1] = 0;
        } else {
            sa[node][0] = ba + 1;
            sa[node][1] = ba + 1;
        }
    }

    // Reroot the tree to include contributions from parent and sibling subtrees.
    void reroot(vector<vector<int>> &adj, string &s, vector<vector<int>> &ans, 
                vector<vector<int>> &sa, int node = 0, int par = -1, 
                int red_par = 0, int blue_par = 0) {
        
        // Calculate best answer considering both subtree and parent contributions
        if (s[node] == 'R') {
            ans[node][0] = max(sa[node][0], 1 + red_par);
            ans[node][1] = 0;
        } else {
            ans[node][0] = max(sa[node][0], 1 + blue_par);
            ans[node][1] = max(sa[node][1], 1 + blue_par);
        }

        // Find the largest and second-largest contributions from child subtrees
        int fr = red_par, sr = red_par;
        int fb = blue_par, sb = blue_par;

        for (auto &it : adj[node]) {
            if (it == par) continue;

            // Maintain the two largest Red contributions
            if (sa[it][0] > fr) {
                sr = fr;
                fr = sa[it][0];
            } else if (sa[it][0] > sr) {
                sr = sa[it][0];
            }

            // Maintain the two largest Blue contributions
            if (sa[it][1] > fb) {
                sb = fb;
                fb = sa[it][1];
            } else if (sa[it][1] > sb) {
                sb = sa[it][1];
            }
        }

        // Pass the best contribution excluding the current child downwards
        for (auto &it : adj[node]) {
            if (it == par) continue;

            int new_red = 0, new_blue = 0;

            if (s[node] == 'R') {
                new_red = 1;
                // Use the best Red contribution not coming from this specific child
                if (sa[it][0] == fr) new_red += sr;
                else new_red += fr;
                new_blue = 0;
            } else {
                new_red = 1;
                // Use the best Blue contribution not coming from this specific child
                if (sa[it][1] == fb) new_red += sb;
                else new_red += fb;
                new_blue = new_red;
            }

            // Reroot the tree at the current child
            reroot(adj, s, ans, sa, it, node, new_red, new_blue);
        }
    }

    int longestPath(string &s, vector<vector<int>> &edges) {
        int n = s.size();
        vector<vector<int>> adj(n);

        // Build the adjacency list of the tree
        for (auto &e : edges) {
            adj[e[0] - 1].push_back(e[1] - 1);
            adj[e[1] - 1].push_back(e[0] - 1);
        }

        // DP array: Index 0 represents Red, index 1 represents Blue
        vector<vector<int>> subTreeAns(n, vector<int>(2));

        // Step 1: Calculate DP values using bottom-up traversal
        root(adj, s, subTreeAns);

        vector<vector<int>> ans(n, vector<int>(2));

        // Step 2: Reroot the tree to consider paths in all directions
        reroot(adj, s, ans, subTreeAns);

        int res = 0;
        // Find the global maximum valid path length
        for (int i = 0; i < n; i++) {
            res = max({res, ans[i][0], ans[i][1]});
        }

        return res;
    }
};

/*
*
* Dry Run
* Input: s = "RBB", edges = [[1, 2], [1, 3]]
*
* 1. Initialization & Adjacency List:
*    adj[0] = {1, 2}
*    adj[1] = {0}
*    adj[2] = {0}
*    Colors: Node 0 = 'R', Node 1 = 'B', Node 2 = 'B'
*
* 2. Bottom-Up DFS (root):
*    - Process Node 1 ('B'): No children. sa[1][0] = 1, sa[1][1] = 1.
*    - Process Node 2 ('B'): No children. sa[2][0] = 1, sa[2][1] = 1.
*    - Process Node 0 ('R'): Gets max Red and Blue paths from children (1 and 2).
*      sa[0][0] = max child value + 1 = 2. sa[0][1] = 0.
*
* 3. Top-Down DFS (reroot):
*    - Node 0: red_par = 0, blue_par = 0. ans[0][0] = 2. Passes down alternative paths.
*    - Node 1 ('B'): Receives alternative path from Node 0. ans[1][0] = max(1, 1+1) = 2.
*    - Node 2 ('B'): Receives alternative path from Node 0. ans[2][0] = max(1, 1+1) = 2.
*
* 4. Result:
*    Max value in ans array is 2.
* Output: 2
*
*/
```

---

## 🔑 Key Insights

* **Constraint Breakdown:** A rule specifying "No Red after Blue" restricts paths to follow a strict state machine `(Start) -> [Red Nodes] -> [Blue Nodes] -> (End)`.
* **Tree DP (In-Out DP):** Whenever a problem asks to find the optimal path or value passing through *any* node in a tree, computing it naively for each node results in $O(N^2)$ time. Using the In-Out DP (or Rerooting) technique optimizes this to $O(N)$ by reusing the calculated subtrees and passing sibling/parent contexts downwards.
* **Tracking Top Two Paths:** To efficiently process the rerooting, we maintain the highest and second-highest path contributions at each parent node. This prevents the parent from falsely propagating a path down to a child when that path actually originated from that exact child.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might also want to explore:
* [Longest Path in a Tree](https://www.geeksforgeeks.org/longest-path-undirected-tree/) (Finding the diameter of a tree)
* [Tree DP Concept and Examples](https://www.geeksforgeeks.org/dynamic-programming-trees-set-1/)
* [Maximum Path Sum between 2 Leaf Nodes](https://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/)

---

## 🔗 References

* **GeeksforGeeks Problem:** [Longest Colored Path](https://www.geeksforgeeks.org/problems/longest-colored-path--151454/1)

---

## 👨‍💻 Author

Built and maintained by [imnilesh18](https://github.com/imnilesh18). 

## 🏷️ Tags

`#Tree` `#DynamicProgramming` `#DFS` `#TreeDP` `#GeeksforGeeks` `#Hard` `#C++`