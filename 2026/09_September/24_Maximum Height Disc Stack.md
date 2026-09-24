# 🔴 Maximum Height Disc Stack

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-358a1c?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Hard](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy: 55.31%](https://img.shields.io/badge/Accuracy-55.31%25-blue?style=for-the-badge)
![Points: 8](https://img.shields.io/badge/Points-8-orange?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two arrays `r[]` and `h[]` of size `n`, where `r[i]` and `h[i]` represent the radius and height of the $i$-th circular disc, respectively.

A disc can be placed above another disc **only if both its radius and height are strictly smaller** than those of the disc below it.

Find the **maximum possible height** of a stack that can be formed using the given discs. Each disc can be used **at most once**.

---

## 📊 Examples

### Example 1
```text
Input:  r[] = [5, 7, 3], h[] = [6, 5, 4]
Output: 10
Explanation: Disc (3, 4) can be placed above Disc (5, 6) because 3 < 5 and 4 < 6.
             The stack height is 4 + 6 = 10.
```

### Example 2
```text
Input:  r[] = [3, 7], h[] = [7, 4]
Output: 7
Explanation: Neither disc can be placed above the other because both required 
             dimensions (radius and height) are not strictly smaller.
             Therefore, the maximum possible stack height is 7.
```

<details>
<summary>📖 <b>Example Breakdown (Walkthrough for Example 1)</b></summary>

<br>

Given discs:
1. Disc 0: Radius = 5, Height = 6
2. Disc 1: Radius = 7, Height = 5
3. Disc 2: Radius = 3, Height = 4

**Valid Stack Configurations:**
- `[ (3, 4), (5, 6) ]`: Valid since $3 < 5$ and $4 < 6$. Total height = $4 + 6 = 10$.
- `[ (5, 6) ]`: Valid. Height = 6.
- `[ (7, 5) ]`: Valid. Height = 5.
- `[ (3, 4) ]`: Valid. Height = 4.

The optimal configuration gives maximum height **10**.
</details>

---

## ⚙️ Constraints

> - $1 \le \text{r.size()}, \text{h.size()} \le 10^5$
> - $1 \le r[i], h[i] \le 1000$
> - Expected Time Complexity: $O(N \log N)$
> - Expected Auxiliary Space: $O(N)$

---

## 💡 Solution Approach

### Optimized Approach: Fenwick Tree (BIT) + Coordinate Compression

The problem is a variant of the **2D Longest Increasing Subsequence (LIS)** with weighted values (heights).

1. **Custom Sorting**:
   - Sort the discs primarily by radius in **ascending order**.
   - If two discs have equal radius, sort them by height in **descending order**.
   - *Why descending order for equal radius?* This prevents a disc with equal radius from improperly using another disc with the same radius in the same stack, since strict inequality is required for both dimensions.

2. **Coordinate Compression**:
   - Collect all unique height values and map them to $1$-based rank indices so they can be queried/updated in a **Fenwick Tree (Binary Indexed Tree)**.

3. **Fenwick Tree Query & Update**:
   - Process discs sequentially.
   - Query the Fenwick Tree for the maximum stack height achieved by any disc with a **strictly smaller height** (`query(index - 1)`).
   - Update the Fenwick Tree at `index` with `best + current_disc_height`.
   - Maintain a global maximum stack height `ans`.

---

### 💻 C++ Implementation

```cpp
// Intuition: To place disc A above disc B, both radius and height of A must be strictly smaller than B. By sorting discs by radius ascending (and height descending for ties), we ensure that a disc processed later cannot be placed above an earlier disc with the same radius. The problem then reduces to finding the maximum height sum of a chain with strictly increasing heights, which can be efficiently computed using a Fenwick Tree (Binary Indexed Tree) with coordinate compression.
// Approach: 
// 1. Combine radius and height arrays into pairs of discs (r[i], h[i]).
// 2. Sort discs primarily by radius in ascending order. For equal radii, sort by height in descending order so that discs with equal radius cannot extend each other's stack.
// 3. Collect and coordinate-compress all unique disc heights to map them into 1-based indices for the Fenwick Tree.
// 4. Iterate through the sorted discs. For each disc, query the Fenwick Tree for the maximum stack height among strictly smaller height values (query(index - 1)).
// 5. Update the Fenwick Tree at current disc's height index with (best + current_disc_height).
// 6. Track and return the global maximum height achievable.
// Time Complexity: O(N log N) due to sorting and Fenwick Tree queries/updates for N discs.
// Space Complexity: O(N) auxiliary space to store disc pairs, unique heights, and Fenwick tree entries.

class Solution {
  public:
    // Fenwick Tree for storing maximum stack height.
    class FenwickTree {
        vector<int> tree;

    public:
        FenwickTree(int n) {
            tree.resize(n + 1, 0);
        }

        // Updates the maximum stack height at index and its ancestors
        void update(int index, int value) {
            while (index < tree.size()) {
                tree[index] = max(tree[index], value);
                index += index & -index;
            }
        }

        // Queries the maximum stack height for height indices <= index
        int query(int index) {
            int result = 0;

            while (index > 0) {
                result = max(result, tree[index]);
                index -= index & -index;
            }

            return result;
        }
    };

    int maxStackHeight(vector<int>& r, vector<int>& h) {
        int n = r.size();

        vector<pair<int, int>> discs;

        // Pair radius and height for each disc
        for (int i = 0; i < n; i++)
            discs.push_back({r[i], h[i]});

        // Equal radii are sorted by height in descending order.
        sort(discs.begin(), discs.end(), [](auto& a, auto& b) {
            if (a.first != b.first)
                return a.first < b.first;
            return a.second > b.second;
        });

        vector<int> heights;

        // Extract heights for coordinate compression
        for (auto& disc : discs)
            heights.push_back(disc.second);

        // Remove duplicate heights to get unique sorted rank list
        sort(heights.begin(), heights.end());
        heights.erase(unique(heights.begin(), heights.end()), heights.end());

        // Initialize Fenwick Tree with number of unique heights
        FenwickTree bit(heights.size());

        int ans = 0;

        // Process each disc in sorted radius order
        for (auto& disc : discs) {
            int height = disc.second;

            // Get 1-based coordinate rank of current height
            int index = lower_bound(
                heights.begin(), heights.end(), height
            ) - heights.begin() + 1;

            // Query only strictly smaller heights.
            int best = bit.query(index - 1);

            int currentHeight = best + height;

            // Update Fenwick Tree at index with new total height
            bit.update(index, currentHeight);

            // Update global maximum stack height
            ans = max(ans, currentHeight);
        }

        return ans;
    }
};

/*
*
* Dry Run
*
* Input: r = [5, 7, 3], h = [6, 5, 4]
* 
* Step 1: Pair Discs -> [(5, 6), (7, 5), (3, 4)]
* Step 2: Sort Discs -> [(3, 4), (5, 6), (7, 5)]
* Step 3: Unique Sorted Heights -> [4, 5, 6]
*         Height Mappings (1-based index):
*         4 -> index 1
*         5 -> index 2
*         6 -> index 3
* 
* Step 4: Iteration through Discs:
* 
* Disc 1: (3, 4)
*   - height = 4, index = 1
*   - query(0) = 0
*   - currentHeight = 0 + 4 = 4
*   - update(1, 4)
*   - ans = max(0, 4) = 4
* 
* Disc 2: (5, 6)
*   - height = 6, index = 3
*   - query(2) = 4 (from height index 1)
*   - currentHeight = 4 + 6 = 10
*   - update(3, 10)
*   - ans = max(4, 10) = 10
* 
* Disc 3: (7, 5)
*   - height = 5, index = 2
*   - query(1) = 4
*   - currentHeight = 4 + 5 = 9
*   - update(2, 9)
*   - ans = max(10, 9) = 10
* 
* Final Output: 10
*
*/
```

---

## 🔑 Key Insights

- **Sorting Trick for Ties**: Sorting equal radii by height in **descending** order guarantees that if two discs have the same radius, the taller one is processed first. When processing the shorter one later, its query range excludes the taller equal-radius disc, preventing invalid stack chains with equal radii.
- **Fenwick Tree Acceleration**: Standard 2D DP takes $O(N^2)$ time. Using a Fenwick Tree (or Segment Tree) along with coordinate compression reduces the dynamic programming transition lookup time from $O(N)$ to $O(\log N)$, reducing total complexity to $O(N \log N)$.

---

## 🛠️ Further Exploration

- [Box Stacking Problem (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/box-stacking/1)
- [Longest Increasing Subsequence (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1)
- [Russian Doll Envelopes (LeetCode 354)](https://leetcode.com/problems/russian-doll-envelopes/)

---

## 🔗 References

- **GeeksforGeeks Problem**: [Maximum Height Disc Stack](https://www.geeksforgeeks.org/problems/stacking-up-discs1315/1)
- **Data Structure**: [Fenwick Tree / Binary Indexed Tree](https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/)

---

## 👤 Author

Crafted with ❤️ by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Dynamic Programming](https://img.shields.io/badge/-Dynamic_Programming-blue?style=flat-square)
![Fenwick Tree](https://img.shields.io/badge/-Fenwick_Tree-purple?style=flat-square)
![Sorting](https://img.shields.io/badge/-Sorting-orange?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/-GeeksforGeeks-green?style=flat-square)