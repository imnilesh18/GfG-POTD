# 🎯 Triplets with Sum in Range

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Triplets%20with%20Sum%20in%20Range-008a00?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Medium](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-30.77%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-purple?style=for-the-badge)

> ⚠️ **Educational Use Only:**  
> This repository and its content are intended solely for educational purposes.  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📌 Problem Statement

Given an array `arr[]` of positive integers and a range defined by `[l, r]`, your task is to count the total number of distinct triplets $(arr[i], arr[j], arr[k])$ such that $i < j < k$ and their sum lies within the range $[l, r]$.

---

## 💻 Examples

```text
Example 1:
Input: arr[] = [8, 3, 5, 2], l = 7, r = 11
Output: 1
Explanation: There is only one triplet [2, 3, 5] having sum 10, which lies in the range [7, 11].

Example 2:
Input: arr[] = [5, 1, 4, 3, 2], l = 2, r = 7
Output: 2
Explanation: There are two triplets having a sum within range: [1, 4, 2] (sum 7) and [1, 3, 2] (sum 6).
```

<details>
<summary>📖 Example Breakdown (Walkthrough)</summary>

<br/>

**For Input:** `arr = [8, 3, 5, 2]`, `l = 7`, `r = 11`

1. **Sort the array:** `[2, 3, 5, 8]`
2. **Find Triplets with sum $\le 11$:**
   - Fix $i = 0$ ($arr[i] = 2$):
     - Pair $(3, 8)$: $2 + 3 + 8 = 13 > 11 \rightarrow$ reduce right pointer.
     - Pair $(3, 5)$: $2 + 3 + 5 = 10 \le 11 \rightarrow$ Valid triplet `[2, 3, 5]` found. Count = 1.
3. **Find Triplets with sum $\le 6$ ($l - 1$):**
   - Fix $i = 0$ ($arr[i] = 2$):
     - Pair $(3, 5)$: $2 + 3 + 5 = 10 > 6 \rightarrow$ No valid triplets. Count = 0.
4. **Final Answer:** `Count(<= 11) - Count(<= 6)` = $1 - 0 = 1$.
</details>

---

## ⚡ Constraints

> - $1 \le \text{arr.size()} \le 10^3$
> - $1 \le \text{arr}[i] \le 10^3$
> - $1 \le l \le r \le 10^9$

---

## 🛠️ Solution Approach

### **Optimized Two-Pointer Range Reduction Strategy**

**Intuition:**  
Directly counting triplets in a range $[l, r]$ can be complex. Instead, we break the range query into two simpler prefix-based queries:  
$$\text{Triplets in } [l, r] = \text{Triplets with sum } \le r - \text{Triplets with sum } \le (l - 1)$$

**Step-by-Step Approach:**
1. Sort the array in non-decreasing order.
2. Define a helper function `countTripletsLessThan(arr, val)` to count triplets with sum $\le val$.
3. Fix the first element $arr[i]$ in a loop from $i = 0$ to $n-3$.
4. Use two pointers ($j = i + 1$ and $k = n - 1$) for the remaining elements:
   - Calculate $\text{sum} = arr[i] + arr[j] + arr[k]$.
   - If $\text{sum} > val$, decrement $k$ to reduce the total sum.
   - If $\text{sum} \le val$, then all elements from index $j+1$ to $k$ paired with $arr[i]$ and $arr[j]$ will yield a sum $\le val$. Add $(k - j)$ to our result and increment $j$.
5. Subtract `countTripletsLessThan(arr, l - 1)` from `countTripletsLessThan(arr, r)` to get the final count.

```cpp
// Intuition: Count triplets with sum in range [l, r] using prefix-range logic: count(l, r) = count(<= r) - count(<= l - 1).
// Approach: Sort the array, then fix element i and use two pointers (j, k) to count valid triplets efficiently in O(N^2) time.
// Time Complexity: O(N^2) - O(N log N) for sorting plus O(N^2) for two-pointer traversal.
// Space Complexity: O(1) - Auxiliary space used is constant O(1).

class Solution {
  public:
  int countTripletsLessThan(vector<int> &arr, int val) {

      int n = arr.size();

      // Sort the input array to enable two-pointer technique
      sort(arr.begin(), arr.end());

      // Initialize result counter
      int ans = 0;

      int j, k;

      // Variable to store current triplet sum
      int sum;

      // Fix the first element of the triplet
      for (int i = 0; i < n - 2; i++) {

          // Initialize remaining two pointers at ends of subarray arr[j+1..k]
          j = i + 1;
          k = n - 1;

          // Two-pointer search loop
          while (j < k) {
              sum = arr[i] + arr[j] + arr[k];

              // Decrement k if current sum exceeds target value
              if (sum > val)
                  k--;

              // If sum is <= val, all triplets from j+1 to k are valid
              else {
                  ans += (k - j);
                  j++; // Move left pointer rightward
              }
          }
      }

      return ans;
  }

  // Function to return count of triplets having sum in range [l, r]
  int countTriplets(vector<int> &arr, int l, int r) {

      // Variable to store count of triplets
      int res;

      // Calculate count of triplets with sum <= r minus sum <= (l - 1)
      res = countTripletsLessThan(arr, r) -
          countTripletsLessThan(arr, l - 1);

      return res;
  }
};

/*
*
* Dry Run
*
* Input: arr = [8, 3, 5, 2], l = 7, r = 11
* Sorted Array: arr = [2, 3, 5, 8], size n = 4
*
* Step 1: Execute countTripletsLessThan(arr, 11)
* Loop i = 0 (arr[0] = 2):
*   j = 1 (arr[1] = 3), k = 3 (arr[3] = 8)
*   sum = 2 + 3 + 8 = 13 (> 11) -> decrement k (k = 2)
*   sum = 2 + 3 + 5 = 10 (<= 11) -> ans += (2 - 1) = 1, increment j (j = 2)
*   j < k fails (2 < 2 is false)
* Loop i = 1 (arr[1] = 3):
*   j = 2 (arr[2] = 5), k = 3 (arr[3] = 8)
*   sum = 3 + 5 + 8 = 16 (> 11) -> decrement k (k = 2)
*   j < k fails (2 < 2 is false)
* Output of countTripletsLessThan(arr, 11) = 1
*
* Step 2: Execute countTripletsLessThan(arr, 6)
* Loop i = 0 (arr[0] = 2):
*   j = 1 (arr[1] = 3), k = 3 (arr[3] = 8)
*   sum = 2 + 3 + 8 = 13 (> 6) -> decrement k (k = 2)
*   sum = 2 + 3 + 5 = 10 (> 6) -> decrement k (k = 1)
*   j < k fails (1 < 1 is false)
* Output of countTripletsLessThan(arr, 6) = 0
*
* Step 3: Final Calculation
* res = countTripletsLessThan(arr, 11) - countTripletsLessThan(arr, 6)
* res = 1 - 0 = 1
*
*/
```

---

## 🔑 Key Insights

- **Range Transformation Trick:** Converting range queries $[l, r]$ into prefix operations $f(r) - f(l-1)$ dramatically simplifies multi-variable conditions.
- **Efficient Counting:** When $arr[i] + arr[j] + arr[k] \le val$ on a sorted array, any choice of the third element from index $j+1$ to $k$ yields a valid sum. This avoids manually iterating through all pairs and adds $(k - j)$ in $O(1)$ time.

---

## 🚀 Further Exploration

- [Count Triplets with Sum Smaller than X](https://www.geeksforgeeks.org/problems/count-triplets-with-sum-smaller-than-x5549/1)
- [3Sum Closest](https://www.geeksforgeeks.org/problems/3-sum-closest/1)
- [3Sum Zero](https://www.geeksforgeeks.org/problems/find-triplets-with-zero-sum/1)

---

## 📖 References

- **Problem Link:** [GeeksforGeeks - Triplets with Sum in Range](http://geeksforgeeks.org/problems/triplets-with-sum-with-given-range/1)
- **Company Tag:** Microsoft

---

## 👤 Author

Developed with ❤️ by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Sorting](https://img.shields.io/badge/Tag-Sorting-blue?style=flat-square)
![Two Pointer](https://img.shields.io/badge/Tag-Two--Pointer-brightgreen?style=flat-square)
![Arrays](https://img.shields.io/badge/Tag-Arrays-orange?style=flat-square)
![GeeksforGeeks](https://img.shields.io/badge/Tag-GeeksforGeeks-red?style=flat-square)