# 🧮 Subsets with MEX in Range

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-80.3%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License" />
</div>

<br>

<div align="center">
  <b>⚠️ Educational Use Only:</b><br>
  This repository and its content are intended solely for educational purposes.<br>
  Solutions are provided for learning, practice, and reference only.<br>
  Problem statement and test cases are based on the GeeksforGeeks problem.
</div>

---

## 📝 Problem Statement

Given an array `arr[]` of integers and a range `[l, r]`, count the number of subsets whose Minimum Excluded (MEX) value lies within the given range, inclusive[cite: 1]. 

The Minimum Excluded (or MEX) of a subset is the smallest non-negative integer that is not present in the subset[cite: 1]. An empty subset has a Minimum Excluded value of zero[cite: 1]. Since the answer can be very large, return the answer modulo 10^9 + 7[cite: 1].

---

## 📖 Example Breakdown

<details>
<summary><b>Example 1: Walkthrough</b></summary>

**Input:** `arr[] = [2, 0, 1, 0]`, `l = 1`, `r = 2`[cite: 1]  
**Output:** `9`[cite: 1]  
**Explanation:**  
The subsets whose MEX lies in the range `[1, 2]` are counted as follows[cite: 1]:
* **MEX = 1:** The subsets must contain at least one `0` and must not contain `1`. These subsets are `[0]` (2 ways), `[2, 0]` (2 ways), `[0, 0]` (1 way), and `[2, 0, 0]` (1 way). Total = 6[cite: 1].
* **MEX = 2:** The subsets must contain both `0` and `1` but must not contain `2`. These subsets are `[0, 1]` (2 ways) and `[0, 1, 0]` (1 way). Total = 3[cite: 1].

The subsets `[2, 0, 1]` and `[2, 0, 1, 0]` have MEX = 3, which is outside the given range. Therefore, the total number of valid subsets is 6 + 3 = 9[cite: 1].
</details>

<details>
<summary><b>Example 2</b></summary>

**Input:** `arr[] = [2, 0, 1]`, `l = 1`, `r = 2`[cite: 1]  
**Output:** `3`[cite: 1]  
**Explanation:** The subsets whose MEX lies in the range `[1, 2]` are `[0]` (MEX = 1), `[2, 0]` (MEX = 1), and `[0, 1]` (MEX = 2). Hence, the answer is 3[cite: 1].
</details>

---

## 🚧 Constraints

* `2 ≤ arr.size() ≤ 10^5`[cite: 1]
* `0 ≤ arr[i], r ≤ arr.size()`[cite: 1]
* `0 ≤ l ≤ r`[cite: 1]

---

## 💡 Solution Approach

### Mathematical & Combinatorics Approach
To achieve a specific Minimum Excluded (MEX) value of `M`, a subset must strictly follow two rules:
1. It must contain **at least one** instance of every integer from `0` to `M-1`.
2. It must contain **zero** instances of `M`.

Any number strictly greater than `M` can either be included or excluded from the subset without affecting the MEX. 

Using this intuition, we can calculate the number of valid subsets by:
1. Counting the frequency of every element in the array.
2. Iterating from `0` to `l-1` to calculate the base combinations required to even reach the lower bound `l`. If any number in this range is missing, it's impossible to get a MEX $\ge l$, so we return 0.
3. Iterating through our target range `[l, r]`. For each target MEX `i`, we calculate combinations by excluding `i` entirely, mandating numbers `< i`, and freely multiplying by $2^k$ (where `k` is the count of all remaining unprocessed elements). We add this to our total result.

---

## 💻 Code

```cpp
// Intuition: To get a MEX of 'M', the subset must contain at least one of every integer from 0 to M-1, and absolutely no instances of 'M'. Numbers greater than 'M' can be freely included or excluded.
// Approach:
// 1. Count frequencies of all elements in the array.
// 2. Precompute powers of 2 modulo 10^9+7 for subset combinations.
// 3. Ensure all numbers from 0 to l-1 are present (multiply ways by 2^freq - 1). If any is missing, MEX can't reach l.
// 4. For each potential MEX from l to r, calculate valid subsets by excluding the current number and freely picking from remaining larger numbers.
// 5. Update the running combinations to mandate the presence of the current number to check higher MEX values.
// Time Complexity: O(n + r) where n is array size (for frequency map and powers) and r is the upper bound of MEX to check.
// Space Complexity: O(n) for storing the frequency map and precomputed powers of 2.

class Solution {
  public:
    int cntSubsets(vector<int> &arr, int l, int r) {
        const long long M = 1000000007; // Modulo constant
        int n = arr.size();

        unordered_map<int, int> mp;
        
        // Count frequencies of each number
        for (int num : arr) {
            mp[num]++;
        }

        // Precompute powers of 2 modulo M
        vector<long long> power(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            power[i] = (power[i - 1] * 2) % M;
        }

        long long res = 0;
        long long cur = 1; // Tracks combinations of required elements
        int seen = 0;      // Tracks count of elements processed so far

        // Ensure every value smaller than l is present
        for (int i = 0; i < l; i++) {
            int freq = mp[i];

            // If a number < l is missing, MEX can never reach l
            if (freq == 0) {
                return 0;
            }

            seen += freq;
            // We must pick at least one instance of the current number
            cur = (cur * (power[freq] - 1 + M)) % M;
        }

        // Count subsets for each possible MEX in range [l, r]
        for (int i = l; i <= r; i++) {
            int freq = mp[i];

            // Subsets with MEX == i: exclude 'i', freely pick from unprocessed numbers
            long long here = (cur * power[n - seen - freq]) % M;
            res = (res + here) % M;

            // No larger MEX is possible if i is completely absent
            if (freq == 0) {
                return res;
            }

            seen += freq;
            // Mandate at least one 'i' for calculating higher MEX values
            cur = (cur * (power[freq] - 1 + M)) % M;
        }

        return (int)res;
    }
};

/*
* Dry Run
* Input: arr = [2, 0, 1, 0], l = 1, r = 2
* M = 1000000007, n = 4
* mp = {0: 2, 1: 1, 2: 1}
* power = [1, 2, 4, 8, 16]
*
* Checking required elements < l (i = 0):
* freq of 0 is 2.
* seen = 2
* cur = 1 * (power[2] - 1) = 1 * (4 - 1) = 3 (Ways to pick at least one '0')
*
* Target MEX i = 1 (in range [1, 2]):
* freq of 1 is 1.
* here = cur * power[4 - 2 - 1] = 3 * power[1] = 3 * 2 = 6
* res = 6
* seen = 2 + 1 = 3
* cur = 3 * (power[1] - 1) = 3 * (2 - 1) = 3 (Ways to pick at least one '0' and '1')
*
* Target MEX i = 2 (in range [1, 2]):
* freq of 2 is 1.
* here = cur * power[4 - 3 - 1] = 3 * power[0] = 3 * 1 = 3
* res = 6 + 3 = 9
* seen = 3 + 1 = 4
* cur = 3 * (power[1] - 1) = 3 * (2 - 1) = 3
*
* Loop ends. Returns res = 9.
*/

```

---

## 🔍 Key Insights

* **Subset Combinatorics:** Selecting *at least one* element from a group of `f` identical elements can be done in $2^f - 1$ ways.
* **Greedy Modulo Arithmetic:** Computing powers of 2 beforehand ensures we meet the $O(n + r)$ time complexity expectation while avoiding repeated heavy multiplication operations.

---

## 🌍 Further Exploration

* **Related GeeksforGeeks Problems:**
* "Missing Number in Array"
* "Smallest Positive Missing Number"


* Explore Modular Arithmetic properties for combinations and permutations.

---

## 🔗 References

* **Original Problem:** [Subsets with MEX in Range - GeeksforGeeks](https://www.geeksforgeeks.org/problems/crazy-subsets--131708/1)


* Reference File: `GfG.txt`



---

## ✍️ Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`- Mathematics` `- Subset` `- Modular Arithmetic` `- Hash` `- GeeksforGeeks`