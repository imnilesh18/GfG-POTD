# 🟧 Range GCD Queries

![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white) ![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge) ![Accuracy: 61.28%](https://img.shields.io/badge/Accuracy-61.28%25-green?style=for-the-badge) ![Points: 4](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)

<div align="center">
  ⚠️ <b>Educational Use Only:</b>
  <br>
  This repository and its content are intended solely for educational purposes.
  <br>
  Solutions are provided for learning, practice, and reference only.
  <br>
  Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given an integer array `arr[]` and a 2D array `queries[][]` containing `q` queries, where each query is one of the following two types[cite: 1]:
*   **Type 1:** `[0, l, r]` -> Return the GCD of all elements in the range `[l, r]` (both inclusive)[cite: 1].
*   **Type 2:** `[1, index, value]` -> Update `arr[index]` to `value`[cite: 1].

Return an array containing the answers to all Type 1 queries in the order they appear in `queries[][]`[cite: 1].

**Note:** Use 0-based indexing[cite: 1].

---

## 💡 Examples

**Example 1:**
```text
Input: arr[] = [2, 3, 4, 6, 8, 16], q = 3, queries[][] = [[0, 0, 2], [1, 3, 8], [0, 2, 5]]
Output: [1, 4]

```

* Initially, `arr[] = [2, 3, 4, 6, 8, 16]`.


* **Query [0, 0, 2]:** Find the GCD of the subarray `arr[0...2] = [2, 3, 4]`. The GCD is `1`.


* **Query [1, 3, 8]:** Update `arr[3]` from `6` to `8`. The array becomes `[2, 3, 4, 8, 8, 16]`.


* **Query [0, 2, 5]:** Find the GCD of the subarray `arr[2...5] = [4, 8, 8, 16]`. The GCD is `4`.


* Therefore, the answers to all Type 0 queries are `[1, 4]`.



**Example 2:**

```text
Input: arr[] = [12, 18, 24, 30, 36], q = 4, queries[][] = [[0, 1, 3], [1, 2, 15], [0, 0, 2], [0, 2, 4]]
Output: [6, 3, 3]

```

---

## ⚠️ Constraints

* $1 \le arr.size() \le 10^5$

* $1 \le q \le 10^5$

* $0 \le l, r, index \le arr.size()-1$

* $1 \le arr[i], value \le 10^5$


---

## 🛠️ Solution Approaches

### 1️⃣ Approach 1: Brute Force (Sub-optimal)

The most intuitive approach is to iterate from $l$ to $r$ for every GCD query and calculate the GCD on the fly. For update queries, we simply replace the value at the given index. However, in the worst-case scenario, finding the GCD takes $O(N)$ time per query. With $Q$ queries, the time complexity becomes $O(N \cdot Q)$, which will result in a Time Limit Exceeded (TLE) error given the constraints.

### 2️⃣ Approach 2: Segment Tree (Optimized)

To handle both point updates and range queries efficiently, we can use a **Segment Tree**. A Segment Tree allows us to perform both operations in logarithmic time.

```cpp
// Intuition: Range queries and point updates can be efficiently handled using a Segment Tree, reducing time complexity from linear to logarithmic time per query.
// Approach: 1. Build a Segment Tree where each node stores the GCD of its corresponding range. 2. For type 1 queries, recursively find and combine the GCD of overlapping segments. 3. For type 2 queries, update the leaf node and recalculate the GCD of ancestors on the way back up.
// Time Complexity: O((N + Q) * log N * log(max_val)) where N is array size and Q is the number of queries. Building the tree is O(N), and each query/update is O(log N).
// Space Complexity: O(N) auxiliary space is required for the Segment Tree array, which takes up to 4*N space.
class Solution {
  public:
    // Function to compute GCD of two numbers
    int gcd(int a, int b) {
        if (b == 0)
            return a; // Base case: if b is 0, GCD is a
        return gcd(b, a % b); // Recursive Euclidean algorithm
    }

    // Get mid index
    int getMid(int s, int e) {
        return s + (e - s) / 2; // Avoids integer overflow
    }

    // Build segment tree
    int buildSegmentTree(vector<int> &arr, int ss, int se, vector<int> &st, int si) {
        if (ss == se) {
            st[si] = arr[ss]; // Leaf node stores the array element
            return arr[ss];
        }
        int mid = getMid(ss, se);
        // Recursively build left and right children, then store their GCD
        st[si] = gcd(buildSegmentTree(arr, ss, mid, st, si * 2 + 1),
                     buildSegmentTree(arr, mid + 1, se, st, si * 2 + 2));
        return st[si];
    }

    // Query GCD in range
    int findGcd(int ss, int se, int qs, int qe, int si, vector<int> &st) {
        if (ss > qe || se < qs)
            return 0; // Out of bounds: 0 acts as a neutral element for GCD
        if (qs <= ss && qe >= se)
            return st[si]; // Complete overlap: return node's GCD
        int mid = getMid(ss, se);
        // Partial overlap: query both children and return their GCD
        return gcd(findGcd(ss, mid, qs, qe, 2 * si + 1, st), findGcd(mid + 1, se, qs, qe, 2 * si + 2, st));
    }

    // Update a value in segment tree
    void updateValueUtil(int ss, int se, int index, int new_val, int si, vector<int> &st) {
        if (index < ss || index > se)
            return; // Index out of bounds for current segment
        if (ss == se) {
            st[si] = new_val; // Update the leaf node
            return;
        }
        int mid = getMid(ss, se);
        // Traverse to the correct child segment
        if (index <= mid)
            updateValueUtil(ss, mid, index, new_val, 2 * si + 1, st);
        else
            updateValueUtil(mid + 1, se, index, new_val, 2 * si + 2, st);
        // Backtrack and update current node's GCD based on children
        st[si] = gcd(st[2 * si + 1], st[2 * si + 2]);
    }

    // Wrapper to update value
    void updateValue(int index, int new_val, vector<int> &arr, vector<int> &st, int n) {
        arr[index] = new_val; // Update original array
        updateValueUtil(0, n - 1, index, new_val, 0, st); // Update segment tree
    }

    // Function to process queries
    vector<int> processQueries(vector<int> &arr, vector<vector<int>> &q) {
        int n = arr.size();
        int x = 2 * (int)pow(2, ceil(log2(n))) - 1; // Calculate max size of segment tree
        vector<int> st(x);
        buildSegmentTree(arr, 0, n - 1, st, 0); // Initialize segment tree

        vector<int> result;
        for (auto &query : q) {
            int type = query[0];
            if (type == 1) { // Type 1 corresponds to UPDATE
                int index = query[1];
                int new_val = query[2];
                updateValue(index, new_val, arr, st, n);
            } else { // Type 0 corresponds to GCD QUERY
                int l = query[1];
                int r = query[2];
                result.push_back(findGcd(0, n - 1, l, r, 0, st));
            }
        }
        return result;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 3, 4], queries = [[0, 0, 2], [1, 1, 6], [0, 0, 2]]
*
* 1. buildSegmentTree(arr):
*    Segment tree built for [2, 3, 4].
*    Root node represents the GCD of the entire array (2, 3, 4) -> 1.
*
* 2. Processing Query 1: [0, 0, 2]
*    findGcd() searches range 0 to 2. It completely overlaps with the root node.
*    Result = 1. Output Array = [1]
*
* 3. Processing Query 2: [1, 1, 6]
*    This is an update query: update index 1 from 3 to 6.
*    arr becomes [2, 6, 4].
*    updateValueUtil() traverses down to the leaf for index 1, updates it to 6, 
*    and recalculates the parent nodes on the way back up.
*    New root node GCD = GCD(2, 6, 4) -> 2.
*
* 4. Processing Query 3: [0, 0, 2]
*    findGcd() searches range 0 to 2 again. 
*    Returns the new root node value.
*    Result = 2. Output Array = [1, 2]
*
* Final Output: [1, 2]
*
*/

```

---

## 🧠 Key Insights

* **Why a Segment Tree?** Arrays are static and computationally expensive ($O(N)$) for calculating range metrics (like GCD, sum, or min/max) if they are frequently updated. A Segment Tree breaks the array into manageable, pre-computed segments, allowing us to fetch metrics and update values dynamically in $O(\log N)$ time.
* **The Neutral Element:** When querying a Segment Tree for GCD, returning `0` for out-of-bounds queries is necessary because `GCD(x, 0) = x`. This prevents out-of-bound segments from corrupting the final GCD result.

---

## 🔍 Further Exploration

* Learn about **Range Minimum Queries (RMQ)**, which follow the exact same Segment Tree blueprint but replace the `gcd()` function with a `min()` function.
* Look into **Fenwick Trees (Binary Indexed Trees)** for sum-based range queries, though they cannot easily be used for GCD computations.

---

## 📑 References

* **GeeksforGeeks Problem:** [Range GCD Queries](https://www.geeksforgeeks.org/problems/range-gcd-queries3654/1?utm_source=gemini)
* **Segment Tree Fundamentals:** [GeeksforGeeks - Segment Tree](https://www.geeksforgeeks.org/segment-tree-data-structure/?utm_source=gemini)

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18?utm_source=gemini)

---

## 🏷️ Tags

`dynamic-programming` `segment-tree` `number-theory` `mathematics` `array` `geeksforgeeks`
