# 🟥 Rearrange the Array

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-58.69%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
  <a href="https://github.com/imnilesh18">
    <img src="https://img.shields.io/badge/License-MIT-orange?style=for-the-badge" alt="License" />
  </a>
</div>

---

**⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Consider an array `a[] = [1, 2, 3, ..., n]` and a permutation `b[]` of size `n` containing all integers from `1` to `n` exactly once. The array `b[]` defines a rearrangement operation. 

During a single operation, every element at position `i` in `a[]` moves to position `b[i]` (1-based indexing). We must do at least one operation on `a[]`.

Find the minimum number of operations required for all elements to return to their original positions simultaneously, i.e., for `a[]` to become: `[1, 2, 3, ..., n]` again.

*Note: The answer can be large, so return the answer modulo `10^9+7`.*

---

## ⚠️ Constraints

- `1 ≤ n ≤ 10^4`
- `a.size() = b.size() = n`
- `b[]` is a permutation of integers from `1` to `n`.

---

## 💡 Examples

**Example 1:**
```text
Input: b[] = [1, 2, 3]
Output: 1
Explanation: 
Initially, a[] = [1, 2, 3] and b[] = [1, 2, 3]
After one operation:
a[1] = 1 goes to position 1 as b[1] = 1.
a[2] = 2 goes to position 2.
a[3] = 3 goes to position 3.
So, now a[] becomes [1, 2, 3]. All elements remain at their original positions. Hence, the answer is 1.
```

**Example 2:**
```text
Input: b[] = [2, 3, 1, 5, 4]
Output: 6
Explanation: The sequence of arrays obtained after each operation is:
Initially : [1, 2, 3, 4, 5]
1 : [3, 1, 2, 5, 4]
2 : [2, 3, 1, 4, 5]
3 : [1, 2, 3, 5, 4]
4 : [3, 1, 2, 4, 5]
5 : [2, 3, 1, 5, 4]
6 : [1, 2, 3, 4, 5]
After 6 operations, all elements return to their original positions simultaneously. Therefore, the answer is 6.
```

<details>
<summary>📖 Example Breakdown (Walkthrough)</summary>

Let's analyze how elements move in **Example 2**:
* Element `1` at pos 1 moves to pos `2`, then to pos `3`, and back to pos `1`. (Cycle length = 3)
* Element `2` at pos 2 moves to pos `3`, then to pos `1`, and back to pos `2`. (Cycle length = 3)
* Element `3` at pos 3 moves to pos `1`, then to pos `2`, and back to pos `3`. (Cycle length = 3)
* Element `4` at pos 4 moves to pos `5`, and back to pos `4`. (Cycle length = 2)
* Element `5` at pos 5 moves to pos `4`, and back to pos `5`. (Cycle length = 2)

The total number of operations required for all cycles to align at their starting position is simply the **Least Common Multiple (LCM)** of all the cycle lengths.
`LCM(3, 2) = 6`.

</details>

---

## 🚀 Solution Approaches

### 1. Brute-Force Approach (Simulation)
The brute-force way is to actually simulate the movement of each element in the array step by step until the entire array returns to its original sorted configuration `[1, 2, 3, ..., n]`. 
* **Why it fails:** Some permutations can result in massive numbers of required operations before realigning. Simulating step by step will quickly lead to a Time Limit Exceeded (TLE) error since the LCM can grow exponentially.

### 2. Optimized Approach (Cycles & Prime Factorization)
The problem can be modeled as a directed graph where each element connects to its new position. Since every element has an in-degree and out-degree of exactly 1, the graph will be composed of disjoint cycles. 
Each element will return to its original position after `K` steps, where `K` is the length of the cycle it belongs to. For all elements to return simultaneously, we need to find the **Least Common Multiple (LCM)** of all the cycle lengths.

Because the LCM can be exceedingly large, doing basic LCM calculations with `(a * b) / GCD(a, b)` under modulo arithmetic will yield incorrect results (as division does not distribute simply over modulo). Instead, we:
1. Find all cycle lengths.
2. Calculate the prime factorization for each length.
3. Keep track of the highest power of each prime factor across all cycle lengths.
4. Multiply these highest prime powers and take the modulo `10^9+7`.

```cpp
// Intuition: 
// The problem asks for the minimum number of operations for all elements to return to their original positions.
// This is equivalent to finding the cycle lengths of the permutation and computing their Least Common Multiple (LCM).
// Since the LCM can be very large, we compute it modulo 10^9+7 using prime factorization by tracking the highest power of each prime across all cycle lengths.

// Approach:
// 1. Traverse the permutation to find the lengths of all disjoint cycles using a boolean visited array.
// 2. For each cycle length found, compute its prime factorization.
// 3. Keep a track of the maximum exponent for every prime factor encountered.
// 4. Finally, compute the LCM by multiplying all these prime factors raised to their respective maximum exponents, applying modulo 10^9 + 7 at each multiplication step.

// Time Complexity: O(N * sqrt(N)) in the worst case for prime factorization, but practically closer to O(N log N) since the sum of cycle lengths is exactly N.
// Space Complexity: O(N) to store the visited array and the maximum prime powers up to N.

class Solution {
  public:
    int minOperations(vector<int> &b) {
        int n = b.size();
        vector<bool> visited(n + 1, false);
        vector<int> max_pow(n + 1, 0); // Stores the maximum power of each prime
        
        // Find cycles in the permutation
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                int len = 0;
                int curr = i;
                
                // Traverse the current cycle
                while (!visited[curr]) {
                    visited[curr] = true;
                    // Move to the next position (1-based to 0-based index adjustment)
                    curr = b[curr - 1]; 
                    len++;
                }
                
                // Find prime factorization of the current cycle's length
                int temp = len;
                for (int p = 2; p * p <= temp; p++) {
                    int count = 0;
                    while (temp % p == 0) {
                        count++;
                        temp /= p;
                    }
                    // Keep track of the maximum power of prime p across all cycles
                    if (count > 0) {
                        max_pow[p] = max(max_pow[p], count); 
                    }
                }
                // If the remaining number itself is a prime greater than sqrt(len)
                if (temp > 1) {
                    max_pow[temp] = max(max_pow[temp], 1); 
                }
            }
        }
        
        long long ans = 1;
        int MOD = 1e9 + 7;
        
        // Compute the final LCM modulo 10^9+7
        for (int i = 2; i <= n; i++) {
            if (max_pow[i] > 0) {
                long long power = 1;
                // Calculate i ^ max_pow[i]
                for (int j = 0; j < max_pow[i]; j++) {
                    power = (power * i) % MOD;
                }
                // Multiply into the running answer under modulo
                ans = (ans * power) % MOD;
            }
        }
        
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: b = [2, 3, 1, 5, 4]
*
* Cycle Detection:
* i=1: 1 -> b[0]=2 -> b[1]=3 -> b[2]=1. Cycle length = 3
* i=4: 4 -> b[3]=5 -> b[4]=4. Cycle length = 2
*
* Disjoint Cycle lengths: [3, 2]
*
* Prime Factorization & Storing max powers:
* Length 3: Prime 3, power 1 -> max_pow[3] = 1
* Length 2: Prime 2, power 1 -> max_pow[2] = 1
*
* LCM calculation:
* Loop over primes up to N:
* i=2: max_pow[2] = 1 -> ans = (1 * 2^1) % mod = 2
* i=3: max_pow[3] = 1 -> ans = (2 * 3^1) % mod = 6
*
* Output: 6
*
*/
```

---

## 🔑 Key Insights
- **Permutation Cycles:** Any permutation of size `N` forms one or more disjoint cycles. Finding the cycle lengths is the most crucial step.
- **LCM with Modulo:** You cannot apply modulo distributively over the `LCM(a, b)` function itself. By maintaining the maximum prime factorization exponents independently, you can safely apply the modulo operation globally at the end when multiplying out the factors.

## 🔗 Further Exploration
- Try extending this logic for scenarios where you only need a specific subset of elements to align.
- GeeksforGeeks: Explore other graph cycle detection problems like **Find the number of islands**.

## 📑 References
- **Original Problem:** [Rearrange the Array on GeeksforGeeks](https://www.geeksforgeeks.org/problems/rearrange-the-array-1639032648/1)
- **Concepts:** LCM using Prime Factorization, Disjoint Cycles in Permutations.

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

### 🏷️ Tags
`#DFS` `#Prime Number` `#LCS` `#Algorithms` `#Arrays` `#GeeksforGeeks` `#C++`