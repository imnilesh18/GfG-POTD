# 🟢 Union of Arrays with Duplicates

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-4caf50?style=for-the-badge" alt="Difficulty Easy" />
  <img src="https://img.shields.io/badge/Accuracy-42.22%25-blue?style=for-the-badge" alt="Accuracy 42.22%" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points 2" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

You are given two arrays `a[]` and `b[]`, return the **Union** of both the arrays in any order.

The **Union** of two arrays is a collection of all **distinct elements** present in either of the arrays. If an element appears more than once in one or both arrays, it should be included **only once** in the result.

**Note:** Elements of `a[]` and `b[]` are not necessarily distinct. You can return the Union in any order but the driver code will print the result in **sorted order** only.

---

## 💡 Examples

### Example 1
```text
Input: a[] = [1, 2, 3, 2, 1], b[] = [3, 2, 2, 3, 3, 2]
Output: [1, 2, 3]
Explanation: Union set of both the arrays will be 1, 2 and 3.
```

### Example 2
```text
Input: a[] = [1, 2, 3], b[] = [4, 5, 6] 
Output: [1, 2, 3, 4, 5, 6]
Explanation: Union set of both the arrays will be 1, 2, 3, 4, 5 and 6.
```

<details>
<summary><b>📖 Example 3 Breakdown</b></summary>

```text
Input: a[] = [1, 2, 1, 1, 2], b[] = [2, 2, 1, 2, 1] 
Output: [1, 2]

1. Array a[] contains elements 1 and 2.
2. Array b[] contains elements 1 and 2.
3. Combining them gives us 1 and 2 (ignoring all repeating instances).
4. Output is [1, 2].
```
</details>

---

## ⚙️ Constraints

- `1 ≤ a.size(), b.size() ≤ 10^6`
- `0 ≤ a[i], b[i] ≤ 10^5`

---

## 🧠 Solution Approach

### Hashing / Set Approach

**Intuition:** The core of the problem requires us to find unique elements that appear across two arrays. A Hash Set (`unordered_set` in C++) inherently stores only unique items. By throwing all elements from both arrays into a set, duplicates are automatically filtered out. 

```cpp
// Intuition: We need to find all unique elements present in either of the arrays. Using a hash set is ideal because it automatically handles duplicates and stores only unique elements.
// Approach: Create an unordered_set. Iterate through both arrays one by one and insert their elements into the set. Finally, copy the distinct elements from the set to a result vector and return it.
// Time Complexity: O(n + m) on average, where n and m are the sizes of the two arrays. Insertion in an unordered_set takes O(1) time on average.
// Space Complexity: O(n + m) to store the distinct elements in the hash set and the result vector in the worst case.

class Solution {
  public:
    vector<int> findUnion(vector<int>& a, vector<int>& b) {
        unordered_set<int> st;  // Set to store distinct elements
        
        // Put all elements of a[] in st
        for (int i = 0; i < a.size(); i++) 
            st.insert(a[i]);
        
        // Put all elements of b[] in st
        for (int i = 0; i < b.size(); i++) 
            st.insert(b[i]);
        
        vector<int> res;        // Result vector to return the union                                    
        
        // iterate through the set to 
        // fill the result array 
        for(auto it: st) 
            res.push_back(it);
        
        return res;
    }
};

/*
*
* Dry Run
*
* Input: a = [1, 2], b = [2, 3]
*
* Step 1: Initialize empty unordered_set 'st' and vector 'res'
*
* Step 2: Iterate array 'a'
* Insert 1: st = {1}
* Insert 2: st = {1, 2}
*
* Step 3: Iterate array 'b'
* Insert 2: st = {1, 2} (Already present, ignored)
* Insert 3: st = {1, 2, 3}
*
* Step 4: Iterate set 'st'
* Push elements to 'res'
* res = [1, 2, 3] (Internal ordering in unordered_set may vary)
*
* Output: [1, 2, 3]
*
*/
```

---

## 🔑 Key Insights

- **Automatic Deduplication:** Hash sets are highly efficient tools when dealing with problems asking for unique counts or distinct combinations. They completely eliminate the need for manual sorting or adjacent checking.
- **Order Independence:** The problem specifies that returning elements in any order is acceptable since the driver code sorts it automatically. This allows us to use `unordered_set` (O(1) average time) over an ordered `set` (O(log n) time), strictly optimizing our runtime complexity.

---

## 🚀 Further Exploration
- **Intersection of Two Arrays:** Instead of the union, find common elements between two arrays.
- **Two Pointer Approach:** What if the arrays were given to us already sorted? Can we achieve this in `O(1)` auxiliary space using two pointers? (Hint: Yes, by comparing `a[i]` and `b[j]`).

---

## 🔗 References
- **Original Problem:** [Union of Arrays with Duplicates](https://www.geeksforgeeks.org/problems/union-of-two-arrays3538/1)
- **C++ Unordered Set:** [C++ Reference](https://cplusplus.com/reference/unordered_set/unordered_set/)

---

## 👤 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#Hash` `#DataStructures` `#Algorithms` `#Arrays` `#GeeksforGeeks`
