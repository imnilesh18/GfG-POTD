# 🟧 Max Value After m Range Increments

<div align="center">
  <img src="https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksForGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty Medium" />
  <img src="https://img.shields.io/badge/Accuracy-49.92%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="MIT License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.[cite: 1]

---

## 📝 Problem Statement

Given three arrays `a[]`, `b[]`, and `k[]`, representing `m` range increment operations on an array `arr[]` of size `n`, where all elements of `arr[]` are initially 0.[cite: 1]

`Increment(a[i], b[i], k[i])` adds `k[i]` to each element `arr[j]` such that `a[i] <= j <= b[i]` (mainly indexes in range from `a[i]` to `b[i]`).[cite: 1]

After performing all the given operations, find the **maximum value** present in the array.[cite: 1]

---

## 🎯 Examples

### Example 1
```text
Input: n = 5, a[] = [0, 1, 2], b[] = [1, 4, 3], k[] = [100, 100, 100]
Output: 200
Explanation: 
Initially, arr = [0, 0, 0, 0, 0]
After the first operation: arr = [100, 100, 0, 0, 0]
After the second operation: arr = [100, 200, 100, 100, 100]
After the third operation: arr = [100, 200, 200, 200, 100]
The maximum element after all operations is 200.

```

### Example 2

```text
Input: n = 4, a[] = [1, 0, 3], b[] = [2, 0, 3], k[] = [603, 286, 882]
Output: 882
Explanation: 
Initially, arr = [0, 0, 0, 0]
After the first operation: arr = [0, 603, 603, 0]
After the second operation: arr = [286, 603, 603, 0]
After the third operation: arr = [286, 603, 603, 882]
The maximum element after all operations is 882.

```

For **Example 1**: `n = 5`, `m = 3`
Operations:

1. `(0, 1, 100)` -> Increment index 0 to 1 by 100.
2. `(1, 4, 100)` -> Increment index 1 to 4 by 100.
3. `(2, 3, 100)` -> Increment index 2 to 3 by 100.

Instead of a brute-force approach (looping through ranges), we apply the **Difference Array** technique:

* `arr = [0, 0, 0, 0, 0, 0]` (Size `n+1`)
* Op 1: `arr[0] += 100`, `arr[2] -= 100`
* `arr` becomes `[100, 0, -100, 0, 0, 0]`


* Op 2: `arr[1] += 100`, `arr[5] -= 100`
* `arr` becomes `[100, 100, -100, 0, 0, -100]`


* Op 3: `arr[2] += 100`, `arr[4] -= 100`
* `arr` becomes `[100, 100, 0, 0, -100, -100]`



Now, compute the **Prefix Sum** to get final array values:

* `sum = 100` -> `max = 100`
* `sum = 100 + 100 = 200` -> `max = 200`
* `sum = 200 + 0 = 200` -> `max = 200`
* `sum = 200 + 0 = 200` -> `max = 200`
* `sum = 200 - 100 = 100` -> `max = 200`

Result is **200**.

---

## 🛑 Constraints

* `1 ≤ n ≤ 10^6`

* `1 ≤ a.size() = b.size() = k.size() = m ≤ 10^6`

* `0 ≤ a[i] ≤ b[i] ≤ n - 1`

* `0 ≤ k[i] ≤ 10^6`


---

## 💡 Solution Approaches

### Optimized Approach (Difference Array / Prefix Sum)

```cpp
// Intuition: Updating elements one-by-one in a range takes O(N) per query, leading to O(N * M) overall, which will give TLE. Instead, we can use a Difference Array to record the boundary changes of each operation in O(1) time.
// Approach: 
// 1. Create a difference array of size n+1 initialized to 0.
// 2. For each query, add k[i] to the start index (a[i]) and subtract k[i] from the index just after the end (b[i] + 1).
// 3. Compute the running prefix sum of the difference array. The prefix sum at any index gives the exact value after all operations.
// 4. Track and return the maximum value found during the prefix sum calculation.
// Time Complexity: O(N + M) - O(M) to process the m operations, and O(N) to compute the prefix sum.
// Space Complexity: O(N) - We use an auxiliary array of size n+1 to store the differences.

class Solution {
  public:
    int findMax(int n, vector<int>& a, vector<int>& b, vector<int>& k) {
        // Step 1: Create difference array with size n+1 to handle out-of-bound safely
        vector<long long> diff(n + 1, 0);
        
        int m = a.size();
        
        // Step 2: Apply the range operations using boundary markers
        for (int i = 0; i < m; i++) {
            diff[a[i]] += k[i];
            
            // Neutralize the addition after the right boundary
            if (b[i] + 1 < n) {
                diff[b[i] + 1] -= k[i];
            }
        }
        
        long long max_val = 0;
        long long current_sum = 0;
        
        // Step 3 & 4: Compute prefix sum on the fly and track the maximum
        for (int i = 0; i < n; i++) {
            current_sum += diff[i];
            if (current_sum > max_val) {
                max_val = current_sum;
            }
        }
        
        // Safe to cast back to int or return as per problem signature
        return max_val;
    }
};

/*
*
* Dry Run
*
* Input: n = 4, a = [1, 0, 3], b = [2, 0, 3], k = [603, 286, 882]
* Initial diff array of size 5: [0, 0, 0, 0, 0]
*
* i = 0: a[0]=1, b[0]=2, k[0]=603
*   diff[1] += 603 -> [0, 603, 0, 0, 0]
*   diff[3] -= 603 -> [0, 603, 0, -603, 0]
*
* i = 1: a[1]=0, b[1]=0, k[1]=286
*   diff[0] += 286 -> [286, 603, 0, -603, 0]
*   diff[1] -= 286 -> [286, 317, 0, -603, 0]
*
* i = 2: a[2]=3, b[2]=3, k[2]=882
*   diff[3] += 882 -> [286, 317, 0, 279, 0]
*   diff[4] -= 882 -> [286, 317, 0, 279, -882]
*
* Prefix sum generation:
* j=0: sum = 286, max_val = 286
* j=1: sum = 286 + 317 = 603, max_val = 603
* j=2: sum = 603 + 0 = 603, max_val = 603
* j=3: sum = 603 + 279 = 882, max_val = 882
* 
* Final Max Value returned: 882
*/

```

---

## 🧠 Key Insights

* **The Difference Array Technique:** By only manipulating the endpoints of a subarray (`+k` at the start, `-k` right after the end), we reduce an $O(N)$ traversal to an $O(1)$ operation.
* Prefix summation accurately propagates these boundary conditions across the whole array because adding `x` to `index 0` affects all subsequent running totals until a `-x` is encountered.

---

## 🔗 References

* **Original GFG Problem:** [Max Value After m Range Increments](https://www.geeksforgeeks.org/problems/max-value-after-m-range-operation4300/1)


---

## 👨‍💻 Author

Created and maintained by **[imnilesh18](https://github.com/imnilesh18)**.

---

## 🏷️ Tags

`#prefix-sum` `#Arrays` `#Mathematical` `#FactSet` `#geeksforgeeks`
