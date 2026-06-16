# 🧮 Construct List using XOR Queries

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/construct-list-using-given-q-xor-queries/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-50.86%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-orange?style=for-the-badge" alt="Points" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License" />
  </a>
</p>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

There is an array that initially contains only a single value, `0`. 
Given a list of queries `queries[][]` of size `q`, where each query is of one of the following types:
* **`0 x`**: Insert `x` into the array.
* **`1 x`**: Replace every element `a` in the array with `a ^ x`, where `^` denotes the bitwise XOR operator.

Return the array in **sorted order** after performing all the queries.

---

## 🎯 Constraints

> * `1 <= q <= 10^5`
> * `0 <= x <= 10^9`

---

## 💡 Examples

**Example 1:**
```text
Input: q = 5, queries[] = [[0, 6], [0, 3], [0, 2], [1, 4], [1, 5]]
Output: [1, 2, 3, 7]
```

**Example 2:**
```text
Input: q = 3, queries[] = [[0, 2], [1, 3], [0, 5]]
Output: [1, 3, 5]
```

<details>
<summary>📖 <b>Example 1 Breakdown</b></summary>

**Initial Array:** `[0]`
1. `[0, 6]`: Insert `6` -> Array becomes `[0, 6]`
2. `[0, 3]`: Insert `3` -> Array becomes `[0, 6, 3]`
3. `[0, 2]`: Insert `2` -> Array becomes `[0, 6, 3, 2]`
4. `[1, 4]`: XOR all with `4` -> Array becomes `[4, 2, 7, 6]`
5. `[1, 5]`: XOR all with `5` -> Array becomes `[1, 7, 2, 3]`

**Final Sorted Array:** `[1, 2, 3, 7]`
</details>

---

## 🛠️ Solution Approaches

### 1️⃣ Naive Approach: Direct Simulation
The most straightforward approach is to process each query exactly as it is described. We keep track of the list and for every XOR query, we iterate through the entire list to update the elements.

```cpp
// Intuition: Simulates the queries step-by-step. Whenever an XOR query appears, we apply it to all existing elements.
// Approach: 
// 1. Initialize a vector with a starting element 0.
// 2. Iterate through each query. If it's type 0, simply append the value.
// 3. If it's type 1, iterate through the entire current vector and XOR each element with the given value.
// 4. Finally, sort the vector to meet the output requirements.
// Time Complexity: O(n^2) - In the worst case, every query is an XOR operation on a growing list, causing a nested loop iteration.
// Space Complexity: O(n) - Auxiliary space needed to store the elements.

class Solution {
  public:
    // Function to return required list
    // after performing all the queries
    vector<int> constructList(vector<vector<int>> &queries) {
        // Initially list contains only 0
        vector<int> s = {0};
    
        // Process each query one by one
        for (int i = 0; i < queries.size(); i++) {
            int type = queries[i][0];
            int x = queries[i][1];
    
            // Query type 0: Insert x
            if (type == 0) {
                s.push_back(x);
            }
            
            // Query type 1: Apply XOR to all elements
            else {
                // Apply XOR iteratively
                for (int j = 0; j < s.size(); j++) {
                    s[j] = s[j] ^ x;
                }
            }
        }
    
        // Sort the final list
        sort(s.begin(), s.end());
    
        return s;
    }
};

/*
* Dry Run:
* q = 3, queries = [[0, 2], [1, 3], [0, 5]]
* s = [0]
* i=0: type 0, x=2 -> s = [0, 2]
* i=1: type 1, x=3 -> s[0]=0^3=3, s[1]=2^3=1 -> s = [3, 1]
* i=2: type 0, x=5 -> s = [3, 1, 5]
* sort(s) -> [1, 3, 5]
* Return [1, 3, 5]
*/
```

### 2️⃣ Optimal Approach: Reverse Processing + XOR
Instead of updating every element whenever an XOR query appears, we can traverse the queries backward. An element inserted at step `i` is only affected by the XOR operations that happen *after* step `i`. We can maintain a cumulative XOR of all operations seen so far from the end.

```cpp
// Intuition: Future XOR queries apply to previously inserted elements. By iterating backwards, we can track a running cumulative XOR and apply it instantly upon inserting an element.
// Approach: 
// 1. Maintain a running XOR variable, initially 0.
// 2. Traverse the queries from right to left (end to start).
// 3. If it's type 1 (XOR), update the running XOR by XORing it with the query value.
// 4. If it's type 0 (Insert), apply the running XOR to the value and push it to the answer.
// 5. Append the initial 0 value XORed with the final running XOR.
// 6. Sort the final vector and return.
// Time Complexity: O(n log n) - We traverse the queries in a single pass taking O(n) time, and then sort the array which takes O(n log n) time.
// Space Complexity: O(n) - Auxiliary space used to store the output array.

class Solution {
  public:
    // Function to return required list
    // after performing all the queries
    vector<int> constructList(vector<vector<int>> &queries) {
        // Store cumulative Bitwise XOR
        int xr = 0;
    
        // Initialize final list to return
        vector<int> ans;
    
        int n = queries.size();
    
        // Perform each query from right to left
        for (int i = n - 1; i >= 0; i--) {
            // Query type 0: Insert x XORed with running xr
            if (queries[i][0] == 0)
                ans.push_back(queries[i][1] ^ xr);
            // Query type 1: Update running xr
            else
                xr ^= queries[i][1];
        }
    
        // The initial value of 0 must also be XORed with all type 1 queries
        ans.push_back(xr);
    
        // Sort the list
        sort(ans.begin(), ans.end());
    
        // Return final list
        return ans;
    }
};

/*
* Dry Run:
* q = 3, queries = [[0, 2], [1, 3], [0, 5]]
* xr = 0, ans = []
* i=2: [0, 5] -> ans.push(5 ^ 0) -> ans = [5]
* i=1: [1, 3] -> xr ^= 3 -> xr = 3
* i=0: [0, 2] -> ans.push(2 ^ 3) -> ans = [5, 1]
* Loop ends.
* ans.push(0 ^ 3) -> ans.push(3) -> ans = [5, 1, 3]
* sort(ans) -> [1, 3, 5]
* Return [1, 3, 5]
*/
```

---

## 🧠 Key Insights

* **Time Travel Trick:** When operations affect all existing elements, reversing the processing order often collapses an $O(N^2)$ problem down to $O(N)$. 
* **Properties of XOR:** XOR is associative and commutative. A sequence of XOR operations on a number `a ^ x1 ^ x2 ^ x3` is equivalent to `a ^ (x1 ^ x2 ^ x3)`. Accumulating the XOR state saves us from redundant linear passes.

---

## 🔗 References & Further Exploration

* **GeeksforGeeks Problem:** [Construct List using given q XOR queries](https://www.geeksforgeeks.org/problems/construct-list-using-given-q-xor-queries/1)
* **Related Topics:** Arrays, Bit Manipulation, Reverse Traversal.

---

## 👨‍💻 Author

**Nilesh**
* GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#arrays` `#bit-manipulation` `#data-structures` `#geeksforgeeks` `#c++`