# 🟨 Longest Span in two Binary Arrays

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](http://geeksforgeeks.org/problems/longest-span-with-same-sum-in-two-binary-arrays5142/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/)
[![Accuracy](https://img.shields.io/badge/Accuracy-48.22%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/)
[![Points](https://img.shields.io/badge/Points-4-orange?style=for-the-badge)](https://www.geeksforgeeks.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

Given two binary arrays, `a1[]` and `a2[]` of equal length. Find the length of the longest common span `(i, j)`, where `i <= j` such that the sum of elements in this span is equal for both arrays.

Mathematically:
`a1[i] + a1[i+1] + .... + a1[j] = a2[i] + a2[i+1] + ... + a2[j]`

---

## 💡 Examples

**Example 1:**
```text
Input: a1[] = [0, 1, 0, 0, 0, 0], a2[] = [1, 0, 1, 0, 0, 1]
Output: 4
Explanation: The longest span with same sum is from index 1 to 4 (0-based indexing).
Sum of a1 (Index 1 to 4): 1 + 0 + 0 + 0 = 1
Sum of a2 (Index 1 to 4): 0 + 1 + 0 + 0 = 1
```

**Example 2:**
```text
Input: a1[] = [0, 1, 0, 1, 1, 1, 1], a2[] = [1, 1, 1, 1, 1, 0, 1]
Output: 6
Explanation: The longest span with same sum is from index 1 to 6 (0-based indexing).
Sum of a1 (Index 1 to 6): 1 + 0 + 1 + 1 + 1 + 1 = 5
Sum of a2 (Index 1 to 6): 1 + 1 + 1 + 1 + 0 + 1 = 5
```

**Example 3:**
```text
Input: a1[] = [0, 0, 0], a2[] = [1, 1, 1]
Output: 0
Explanation: There is no span where the sum of the elements in a1[] and a2[] is equal.
```

<details>
<summary>📖 <b>Example Breakdown</b></summary>

Let's trace Example 1:
`a1 = [0, 1, 0, 0, 0, 0]`  
`a2 = [1, 0, 1, 0, 0, 1]`

If we pick the subarray from index 1 to index 4:
- `a1[1...4] -> [1, 0, 0, 0]` having a total sum = 1
- `a2[1...4] -> [0, 1, 0, 0]` having a total sum = 1

The length of this subarray is `4 - 1 + 1 = 4`. This is the longest possible subarray where both have an equal sum. Therefore, our output is 4.

</details>

---

## ⚠️ Constraints

> - `1 ≤ a1.size() = a2.size() ≤ 10^6`
> - `0 ≤ a1[i], a2[i] ≤ 1`

---

## 🚀 Solution Approaches

### 1️⃣ Brute-Force Approach
In this approach, we generate all possible subarrays and compare the sums of both arrays for each subarray. If the sum is equal, we update our result (the maximum length).

```cpp
// Intuition: Check all possible subarrays to find the longest one where the sum of elements is equal in both arrays.
// Approach: Use two nested loops. The outer loop (i) sets the starting index, and the inner loop (j) sets the ending index. Calculate the sum for each subarray and update the result if the sums match.
// Time Complexity: O(N^2) — as we are generating every possible subarray using nested loops. This might cause Time Limit Exceeded (TLE) for large inputs.
// Space Complexity: O(1) — utilizing only a few extra variables.

class Solution {
  public:
    int equalSumSpan(vector<int> &a1, vector<int> &a2) {
        int n = a1.size();
        int result = 0;
        
        // Check all possible subarrays
        for (int i = 0; i < n; i++) {
            int sum1 = 0, sum2 = 0;
            
            for (int j = i; j < n; j++) {
                
                // Calculate sum for current subarray
                sum1 += a1[j];
                sum2 += a2[j];
                
                // If sums are equal, update result
                if (sum1 == sum2) {
                    result = max(result, j - i + 1);
                }
            }
        }
        
        return result;
    }
};

/*
*
* Dry Run
*
* a1 = [0, 1, 0], a2 = [1, 0, 1]
* i = 0: 
* j = 0 -> sum1 = 0, sum2 = 1 (Not equal)
* j = 1 -> sum1 = 1, sum2 = 1 (Equal! result = max(0, 1-0+1) = 2)
* j = 2 -> sum1 = 1, sum2 = 2 (Not equal)
* i = 1:
* j = 1 -> sum1 = 1, sum2 = 0 (Not equal)
* j = 2 -> sum1 = 1, sum2 = 1 (Equal! result = max(2, 2-1+1) = 2)
* i = 2:
* j = 2 -> sum1 = 0, sum2 = 1 (Not equal)
* * Final result = 2
*/
```

---

### 2️⃣ Optimized Approach (HashMap)
Instead of recalculating the sums, we can utilize **Cumulative Sums (Prefix Sums)** and track their **Difference**. If the difference between the cumulative sums of the two arrays at two different points is identical, it implies that the sum of the elements between those two points is exactly the same in both arrays.

```cpp
// Intuition: If the difference (sum1 - sum2) is the same at two indices 'x' and 'y', it means the subarray from index x+1 to y has an equal sum in both arrays.
// Approach: Use running difference and a hash map to track the first occurrence of each difference; when the same diff repeats, update the span length.
// Time Complexity: O(N) — single pass over the arrays with O(1) average map operations.
// Space Complexity: O(N) — for storing differences in the hash map.

class Solution {
public:
    int equalSumSpan(vector<int>& a1, vector<int>& a2) {
        int n = a1.size();
        unordered_map<int, int> mp;    // maps diff -> first index it was seen
        int sum1 = 0, sum2 = 0, result = 0;

        for (int i = 0; i < n; i++) {
            sum1 += a1[i];
            sum2 += a2[i];
            int diff = sum1 - sum2;

            if (diff == 0) {
                // from 0..i is balanced
                result = max(result, i + 1);
            } else if (mp.count(diff))  {
                // seen this diff before, subarray (mp[diff]+1..i) is balanced
                result = max(result, i - mp[diff]);
            } else  {
                // first time seeing this diff
                mp[diff] = i;
            }
        }
        return result;
    }
};

/*
*
* Dry Run
*
* Example:
* a1 = [0, 1, 0, 0, 0, 0]
* a2 = [1, 0, 1, 0, 0, 1]
*
* i=0:
* sum1=0, sum2=1, diff=-1  → mp[-1]=0, result=0
* i=1:
* sum1=1, sum2=1, diff=0   → diff==0  → result=2
* i=2:
* sum1=1, sum2=2, diff=-1  → seen at 0 → span=2 → result=2
* i=3:
* sum1=1, sum2=2, diff=-1  → seen at 0 → span=3 → result=3
* i=4:
* sum1=1, sum2=2, diff=-1  → seen at 0 → span=4 → result=4
* i=5:
* sum1=1, sum2=3, diff=-2  → mp[-2]=5, result=4
*
* Final result = 4
*/
```

---

## 🧠 Key Insights
- **Cumulative Sum (Prefix Sum):** Running sums make continuous sequence calculations dramatically faster and remove the need to compute from scratch.
- **Hash Map for Tracking:** Whenever we need to match a subarray sum condition to a specific prior state (in this case, matching a specific difference), utilizing a Hash Map to store the *first occurrence* proves to be a highly effective O(1) technique.

---

## 🔍 Further Exploration
You can strengthen your prefix-sum and hashing logic by practicing these similar GeeksforGeeks problems:
1. Largest subarray with 0 sum
2. Longest Sub-Array with Sum K
3. Zero Sum Subarrays

---

## 🔗 References
- **GeeksforGeeks Problem:** [Longest Span in two Binary Arrays](http://geeksforgeeks.org/problems/longest-span-with-same-sum-in-two-binary-arrays5142/1)
- **Concepts:** Prefix Sum and Hashing

---

## 👨‍💻 Author
**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags
`#Array` `#Hash-Map` `#Prefix-Sum` `#GeeksforGeeks` `#Interview-Prep`
