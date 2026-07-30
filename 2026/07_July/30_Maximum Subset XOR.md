# 🟧 Maximum Subset XOR

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/maximum-subset-xor/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge" alt="Difficulty: Medium" />
  <img src="https://img.shields.io/badge/Accuracy-28.93%25-green?style=for-the-badge" alt="Accuracy: 28.93%" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]`, choose any subset of elements (possibly all elements) such that the XOR of the chosen elements is maximized.

---

## 💡 Examples

```text
Input: arr[] = [2, 4, 5]
Output: 7
Explanation: The subset {2, 5} has the maximum XOR value.
```

```text
Input: arr[] = [9, 8, 5]
Output: 13
Explanation: The subset {8, 5} has the maximum XOR value.
```

<details>
<summary>📖 <strong>Example Breakdown</strong></summary>

For `arr[] = [2, 4, 5]`:
- The subsets and their XOR sums are:
  - `{2}` $\rightarrow$ 2
  - `{4}` $\rightarrow$ 4
  - `{5}` $\rightarrow$ 5
  - `{2, 4}` $\rightarrow$ $2 \oplus 4 = 6$
  - `{2, 5}` $\rightarrow$ $2 \oplus 5 = 7$
  - `{4, 5}` $\rightarrow$ $4 \oplus 5 = 1$
  - `{2, 4, 5}` $\rightarrow$ $2 \oplus 4 \oplus 5 = 3$
- The maximum XOR value produced is **7**, derived from the subset `{2, 5}`.

</details>

---

## ⚠️ Constraints

- $1 \le \text{arr.size()} \le 10^5$
- $1 \le \text{arr}[i] \le 10^6$

---

## 🧠 Solution Approaches

### Modified Gaussian Elimination

**Intuition:** 
The problem asks for the maximum XOR of a subset. This can be efficiently solved by representing the numbers in binary and using a modified Gaussian elimination to find the basis of the vector space spanned by these numbers. By reducing the elements into an independent set (row echelon form), the XOR sum of the modified array will yield the maximum possible value.

```cpp
// Intuition: The problem asks for the maximum XOR of a subset, which can be solved by representing the numbers in binary and applying modified Gaussian elimination.
// Approach: Iterate from the MSB (31) down to 0. Find an element with the current bit set, swap it to the active position, and XOR it with all other elements that also have this bit set to eliminate it elsewhere. Finally, XOR all elements in the modified array.
// Time Complexity: $O(N \cdot \log(\max(arr[i])))$ where $N$ is the size of the array. We process 32 bits and iterate through the array for each bit.
// Space Complexity: $O(1)$ because all modifications to the array are performed in place without any auxiliary data structures.
class Solution {
  public:
    int maxSubsetXOR(vector<int> &arr) {
        int n = arr.size();
        int index = 0;
        
        // Loop from the most significant bit down to the 0th bit
        for (int i = 31; i >= 0; i--) {
            int maxInd = index;
            int maxEle = INT_MIN;
            
            // Find the maximum element with the i-th bit set
            for (int j = index; j < n; j++) {
                if ((arr[j] & (1 << i)) != 0 && arr[j] > maxEle) {
                    maxEle = arr[j];
                    maxInd = j;
                }
            }
            
            // If no element has the i-th bit set, continue to the next bit
            if (maxEle == INT_MIN) continue;
            
            // Swap the found element with the element at the current index
            swap(arr[index], arr[maxInd]);
            maxInd = index;
            
            // XOR this element with all other elements having the i-th bit set
            for (int j = 0; j < n; j++) {
                if (j != maxInd && (arr[j] & (1 << i)) != 0) {
                    arr[j] ^= arr[maxInd];
                }
            }
            
            index++; // Move to the next position
        }
        
        // Calculate the final maximum XOR sum of the reduced array
        int res = 0;
        for (int i = 0; i < n; i++) {
            res ^= arr[i];
        }
        
        return res;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 4, 5]
* Binary representation: 2 = 010, 4 = 100, 5 = 101
* 
* Bit 2 (MSB): 
* Elements with bit 2 set: 4 and 5. Max is 5 (index 2).
* Swap arr[0] and arr[2] -> arr = [5, 4, 2].
* XOR arr[0] (5) with others having bit 2 set (arr[1] which is 4).
* arr[1] = 4 ^ 5 = 1 (001).
* arr = [5, 1, 2]. index = 1.
* 
* Bit 1:
* Elements from index 1 with bit 1 set: arr[2] (2). Max is 2.
* Swap arr[1] and arr[2] -> arr = [5, 2, 1].
* XOR arr[1] (2) with others having bit 1 set (none, since 5 is 101 and 1 is 001).
* arr = [5, 2, 1]. index = 2.
* 
* Bit 0:
* Elements from index 2 with bit 0 set: arr[2] (1). Max is 1.
* Swap arr[2] and arr[2] -> arr = [5, 2, 1].
* XOR arr[2] (1) with others having bit 0 set (arr[0] which is 5).
* arr[0] = 5 ^ 1 = 4 (100).
* arr = [4, 2, 1]. index = 3.
* 
* Final Result:
* res = 4 ^ 2 ^ 1 = 100 ^ 010 ^ 001 = 111 = 7.
* Output: 7.
*/
```

---

## 🔑 Key Insights

- **Vector Space Basis:** Bitwise XOR operations follow the properties of vectors over the Galois Field of 2, GF(2). Finding the maximum subset XOR is akin to finding the basis of this vector space to construct the largest possible value.
- **Greedy Bit Elimination:** By forcing the highest bits to be isolated into distinct numbers (Gaussian elimination), we ensure that they do not conflict with each other. A simple XOR sweep at the end yields the global maximum.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might want to try these related concepts:
- **Maximum XOR of Two Numbers in an Array** (Trie based approach)
- **Maximum AND Value** 
- **Find the exact Subset that gives Max XOR**

---

## 🔗 References

- **Original Problem:** [Maximum Subset XOR on GeeksforGeeks](https://www.geeksforgeeks.org/problems/maximum-subset-xor/1)

---

## ✍️ Author

**imnilesh18**
- GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Array` `Bit Magic` `Math` `Dynamic Programming` `GeeksforGeeks`