<div align="center">
  
# 🧮 Count Pairs Divisible By K

[![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-pairs-in-array-divisible-by-k/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-40.47%25-green?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform. 

---

## 📝 Problem Statement

Given an array `arr[]` and a positive integer `k`, count the total number of pairs in the array whose sum is divisible by `k`.

### 🚨 Constraints:
- `1 ≤ |arr| ≤ 5 * 10^4`
- `1 ≤ arr[i] ≤ 10^6`
- `1 ≤ k ≤ 5 * 10^4`

---

## 💡 Examples

**Example 1:**
```text
Input : arr[] = [2, 2, 1, 7, 5, 3], k = 4
Output : 5
Explanation : There are five pairs possible whose sum is divisible by '4' i.e., (2, 2), (1, 7), (7, 5), (1, 3) and (5, 3).
```

**Example 2:**
```text
Input : arr[] = [5, 9, 36, 74, 52, 31, 42], k = 3
Output : 7 
Explanation : There are seven pairs whose sum is divisible by 3, i.e, (9, 36), (9,42), (74, 52), (36, 42), (74, 31), (31, 5) and (5, 52).
```

<details>
<summary>📖 Example Breakdown (Walkthrough)</summary>

Let's take **Example 1**: `arr[] = [2, 2, 1, 7, 5, 3]`, `k = 4`

Instead of checking every pair (which takes $O(N^2)$ time), let's look at their remainders when divided by `k`:
- `2 % 4 = 2`
- `2 % 4 = 2`
- `1 % 4 = 1`
- `7 % 4 = 3`
- `5 % 4 = 1`
- `3 % 4 = 3`

If two numbers `a` and `b` add up to a multiple of `k`, then `(a % k + b % k) % k == 0`. 
Therefore, if `a % k == rem`, we need a number `b` such that `b % k == (k - rem) % k`.
- For `2` (rem `2`), we need another number with remainder `4 - 2 = 2`.
- For `1` (rem `1`), we need a number with remainder `4 - 1 = 3`.
- For `7` (rem `3`), we need a number with remainder `4 - 3 = 1`.

By keeping track of remainder frequencies, we can count the pairs on the fly!
</details>

---

## 🚀 Solution Approach

We use a Frequency Array (Hashing) approach to solve this optimally. 

```cpp
// Intuition: Two numbers sum up to a multiple of k if their remainders modulo k add up to k (or 0). By tracking the frequencies of remainders, we can count valid pairs efficiently without nested loops.
// Approach: Iterate through the array and calculate the remainder of each element modulo k. For a remainder 'rem', look up the count of previously seen elements with remainder '(k - rem) % k' and add it to our total pairs. Then, update the frequency of 'rem'.
// Time Complexity: O(n), where n is the size of the array, as we traverse the array exactly once.
// Space Complexity: O(k), to store the frequencies of the remainders from 0 to k-1.

class Solution {
  public:
    int countKdivPairs(vector<int>& arr, int k) {
        // stores frequency of remainders
        vector<int> freq(k, 0);
        int count = 0;

        for (int x : arr) {
            // calculate the remainder of the current element
            int rem = x % k;

            // if remainder is 0, we need another element with remainder 0
            if (rem == 0) {
                count += freq[0];
            } else {
                // otherwise, we need an element with remainder (k - rem)
                count += freq[k - rem];
            }

            // add current remainder to our frequency map
            freq[rem]++;
        }

        return count;
    }
};

/*
*
* Dry Run
* Input: arr = [2, 2, 1, 7, 5, 3], k = 4
* freq array of size 4 initialized to [0, 0, 0, 0]
*
* Step 1: x = 2
* rem = 2 % 4 = 2
* count += freq[4 - 2] -> freq[2] -> 0
* freq[2] becomes 1 -> [0, 0, 1, 0]
*
* Step 2: x = 2
* rem = 2 % 4 = 2
* count += freq[4 - 2] -> freq[2] -> 0 + 1 = 1
* freq[2] becomes 2 -> [0, 0, 2, 0]
*
* Step 3: x = 1
* rem = 1 % 4 = 1
* count += freq[4 - 1] -> freq[3] -> 1 + 0 = 1
* freq[1] becomes 1 -> [0, 1, 2, 0]
*
* Step 4: x = 7
* rem = 7 % 4 = 3
* count += freq[4 - 3] -> freq[1] -> 1 + 1 = 2
* freq[3] becomes 1 -> [0, 1, 2, 1]
*
* Step 5: x = 5
* rem = 5 % 4 = 1
* count += freq[4 - 1] -> freq[3] -> 2 + 1 = 3
* freq[1] becomes 2 -> [0, 2, 2, 1]
*
* Step 6: x = 3
* rem = 3 % 4 = 3
* count += freq[4 - 3] -> freq[1] -> 3 + 2 = 5
* freq[3] becomes 2 -> [0, 2, 2, 2]
*
* Final Output: count = 5
*
*/
```

---

## 🧠 Key Insights
- Modulo Arithmetic Properties: `(a + b) % k = (a % k + b % k) % k`. Thus, if `a % k = x`, then `b` must satisfy `b % k = k - x` (or `0` if `x` is `0`).
- By keeping track of remainders as we iterate (one pass), we automatically prevent double-counting and using the same element twice for a pair.

---

## 🔗 Further Exploration
- GeeksforGeeks: [Pairs with given sum](https://www.geeksforgeeks.org/count-pairs-with-given-sum/)
- Similar Concept: Try modifying the approach for "Count triplets divisible by K".

---

## 📚 References
- **Original Problem**: [GeeksforGeeks - Count Pairs Divisible By K](https://www.geeksforgeeks.org/problems/count-pairs-in-array-divisible-by-k/1)
- **Company Tags**: PayPal

---

## 👨‍💻 Author
Built and maintained by [imnilesh18](https://github.com/imnilesh18).

---

## 🏷️ Tags
`Arrays` `Hash` `Data Structures` `Modulo Arithmetic` `GeeksforGeeks` `C++`