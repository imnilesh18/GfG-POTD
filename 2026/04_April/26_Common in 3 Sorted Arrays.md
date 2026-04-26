# 🟢 Common in 3 Sorted Arrays

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/common-elements1132/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-22.16%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-orange?style=for-the-badge" alt="License" />
</div>

<br>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given three sorted arrays in **non-decreasing** order, return all common elements in **non-decreasing** order across these arrays. If there are no such elements return an empty array.

---

## 🚀 Examples

**Example 1**
```text
Input: a[] = [1, 5, 10, 20, 40, 80], b[] = [6, 7, 20, 80, 100], c[] = [3, 4, 15, 20, 30, 70, 80, 120]
Output: [20, 80]
Explanation: The elements 20 and 80 appear in all three arrays a, b, and c, making them the only common elements, so the output is [20, 80].
```

**Example 2**
```text
Input: a[] = [1, 2, 3, 4, 5], b[] = [6, 7], c[] = [8, 9, 10]
Output: []
Explanation: Since none of the elements in arrays a, b, and c appear in all three arrays, there are no common elements, so the output is [].
```

<details>
<summary><b>📖 Example Breakdown (Example 3)</b></summary>

**Input:** `a[] = [1, 1, 1, 2, 2, 2]`
`b[] = [1, 1, 2, 2, 2]`
`c[] = [1, 1, 1, 1, 2, 2, 2, 2]`

**Process:**
1. Ignoring duplicates, `1` and `2` are present in all three arrays.
2. The logic safely steps over the consecutive identical elements, only pushing `1` and `2` into our resultant array once.
3. Once any array is fully traversed, we stop and return the common elements found so far.

**Output:** `[1, 2]`
</details>

---

## 🛑 Constraints

> - `1 ≤ a.size(), b.size(), c.size() ≤ 10^5`
> - `-10^5 ≤ a[i], b[i], c[i] ≤ 10^5`

---

## 💡 Solution Approach

### 1. Three Pointers (Optimized Approach)
**Intuition:** Since the arrays are sorted in non-decreasing order, we can use three pointers simultaneously. The smallest element among the three pointers will always dictate which pointer needs to move forward to potentially find a match. We can keep shifting the pointer for the strictly smallest element until they align on the same value.

**Approach:**
1. Initialize three pointers `i`, `j`, and `k` to 0.
2. Compare the elements `a[i]`, `b[j]`, and `c[k]`.
3. If they are equal, we found a common element! Store it and increment all three pointers. To avoid storing duplicate values, we use inner `while` loops to skip past any identical contiguous elements in all arrays.
4. If they are not equal, find the smallest of the three values and strictly increment its pointer. (e.g., if `a[i] < b[j]`, do `i++`).
5. Repeat this process until at least one array is completely traversed.

```cpp
// Intuition: Since the arrays are sorted, we can use three pointers to simultaneously traverse them. The smallest element among the pointers acts as the bottleneck, so we increment its pointer to catch up. If all three point to the same value, it's a common element.
// Approach: Initialize three pointers (i, j, k) to 0. Traverse while all pointers are within bounds. If a[i] == b[j] == c[k], add to result and increment all pointers, carefully skipping any duplicates to avoid repeating elements in the output. If not equal, increment the pointer pointing to the strictly smallest value among the three arrays to move forward in the sorted order.
// Time Complexity: O(n1 + n2 + n3), where n1, n2, and n3 are the sizes of the arrays. In the worst case, we traverse each array completely exactly once.
// Space Complexity: O(1) auxiliary space, as we only use three integer pointers regardless of the input sizes (excluding the space needed for the output vector).

class Solution {
  public:
    vector<int> commonElements(vector<int> &a, vector<int> &b, vector<int> &c) {
        int i = 0, j = 0, k = 0; // Pointers for arrays a, b, and c
        int n1 = a.size(), n2 = b.size(), n3 = c.size();
        vector<int> common; // Stores the common elements
    
        // Traverse all three arrays using three pointers
        while (i < n1 && j < n2 && k < n3) {
            
            // If all elements are equal, it's a common element
            if (a[i] == b[j] && b[j] == c[k]) {
                common.push_back(a[i]);
                i++;
                j++;
                k++;
    
                // Skip duplicates in all arrays
                while (i < n1 && a[i] == a[i - 1])
                    i++;
                while (j < n2 && b[j] == b[j - 1])
                    j++;
                while (k < n3 && c[k] == c[k - 1])
                    k++;
            }
            
            // Move the pointer with the smallest value
            else if (a[i] < b[j])
                i++;
            else if (b[j] < c[k])
                j++;
            else
                k++;
        }
    
        return common;
    }
};

/*
* Dry Run
* * Input: a = [1, 5, 10], b = [6, 7, 10], c = [3, 4, 10]
* * Step 1: i=0 (1), j=0 (6), k=0 (3)
* -> a[0] < b[0] (1 < 6), so i++ => i=1
* * Step 2: i=1 (5), j=0 (6), k=0 (3)
* -> a[1] < b[0] (5 < 6), so i++ => i=2
* * Step 3: i=2 (10), j=0 (6), k=0 (3)
* -> a[2] < b[0] is false, b[0] < c[0] (6 < 3) is false. So we drop to the 'else' block, k++ => k=1
* * Step 4: i=2 (10), j=0 (6), k=1 (4)
* -> a[2] < b[0] false, b[0] < c[1] (6 < 4) is false. So k++ => k=2
* * Step 5: i=2 (10), j=0 (6), k=2 (10)
* -> a[2] < b[0] false, b[0] < c[2] (6 < 10) is true. So j++ => j=1
* * Step 6: i=2 (10), j=1 (7), k=2 (10)
* -> a[2] < b[1] false, b[1] < c[2] (7 < 10) is true. So j++ => j=2
* * Step 7: i=2 (10), j=2 (10), k=2 (10)
* -> a[2] == b[2] == c[2] (10 == 10 == 10).
* -> Match found! push_back(10).
* -> i++, j++, k++ (i=3, j=3, k=3).
* * Step 8: Loop terminates as pointers exceed bounds. 
* Output: [10]
*/
```

---

## 🧠 Key Insights

- **Sorted Nature is Powerful:** Leveraging the non-decreasing order allows us to safely bypass potentially vast swathes of smaller numbers without resorting to nested loops or heavy lookup tables.
- **Handling Duplicates Inline:** While an `std::set` might seem tempting to handle duplications, pushing the logic down to tight inline `while` loops keeps space complexity strictly `O(1)` and reduces insertion overhead.

---

## 🔍 Further Exploration
- Try **Intersection of Two Arrays**
- Explore finding the **Union of Arrays** using similar two/three-pointer methodology.

---

## 📚 References
- **Original Problem:** [GeeksforGeeks - Common in 3 Sorted Arrays](https://www.geeksforgeeks.org/problems/common-elements1132/1)
- **Concept:** Three Pointer Approach, Array Intersection.

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
![Searching](https://img.shields.io/badge/-Searching-blue?style=flat-square)
![Arrays](https://img.shields.io/badge/-Arrays-brightgreen?style=flat-square)
![Three Pointers](https://img.shields.io/badge/-Three_Pointers-orange?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/-GeeksforGeeks-success?style=flat-square)