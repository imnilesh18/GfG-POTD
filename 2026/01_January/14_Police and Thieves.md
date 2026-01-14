# 👮 Police and Thieves

<div align="center">

[![Status](https://img.shields.io/badge/Status-Active-success.svg)]()
[![Platform](https://img.shields.io/badge/Platform-GeeksforGeeks-orange.svg)](https://www.geeksforgeeks.org/problems/police-and-thieves--141631/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-red.svg)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-34.03%25-blue.svg)]()
[![Points](https://img.shields.io/badge/Points-4-green.svg)]()
[![License](https://img.shields.io/badge/License-MIT-purple.svg)]()

</div>

---

### ⚠️ Educational Use Only

> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given an array `arr[]`, where each element contains either a `'P'` for policeman or a `'T'` for thief. Find the **maximum number of thieves** that can be caught by the police.

Keep in mind the following conditions:

1.  Each policeman can catch **only one** thief.
2.  A policeman cannot catch a thief who is more than `k` units away from him.

---

## 📊 Examples

### Example 1

```python
Input: arr[] = ['P', 'T', 'T', 'P', 'T'], k = 1
Output: 2
Explanation: Maximum 2 thieves can be caught.
First policeman catches first thief and second policeman can catch either second or third thief.

```

### Example 2

```python
Input: arr[] = ['T', 'T', 'P', 'P', 'T', 'P'], k = 2
Output: 3
Explanation: Maximum 3 thieves can be caught.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Consider `arr[] = ['T', 'T', 'P', 'P', 'T', 'P']` with `k = 2`.

- We scan for the first `P` and first `T`.
- `P` is found at index 2. `T` is found at index 0.
- Distance is `|2 - 0| = 2`, which is `<= k` (2). **Caught!** Count = 1.
- Move to next `P` (index 3) and next `T` (index 1).
- Distance `|3 - 1| = 2 <= k`. **Caught!** Count = 2.
- Move to next `P` (index 5) and next `T` (index 4).
- Distance `|5 - 4| = 1 <= k`. **Caught!** Count = 3.
- Total caught: 3.

</details>

---

## 🛑 Constraints

- $1 \leq arr.size() \leq 10^5$
- $1 \leq k \leq 1000$
- $arr[i] = 'P'  or  'T'$

---

## 💡 Solution Approaches

### 1️⃣ Two Pointer Greedy Approach

#### Intuition

The problem asks to maximize the number of pairings between policemen and thieves within a specific distance constraint. Since the array order is fixed, we can employ a greedy strategy. We iterate through the array using two pointers: one identifying the next available policeman and the other identifying the next available thief. The "greedy" part comes from always trying to match the earliest available policeman with the earliest available thief. If they are within range `k`, we pair them. If one is too far behind the other (making the distance `> k`), that specific individual (who is behind) has missed their chance to match with the current or any future counterpart (who will be even further away), so we move past them.

#### Algorithm

1. Initialize two pointers `i` (for policemen) and `j` (for thieves) to `0`.
2. Traverse the array while both pointers are within bounds:

- Advance `i` until it points to `'P'`.
- Advance `j` until it points to `'T'`.
- If valid positions are found:
- **Catch condition:** If `abs(i - j) <= k`, increment the answer, and advance both `i` and `j` (since both are now "occupied").
- **Thief unreachable:** If `j < i` (thief is to the left) and distance `> k`, this thief cannot be caught by this or any future policeman. Increment `j`.
- **Policeman too far:** If `i < j` (policeman is to the left) and distance `> k`, this policeman cannot catch this or any future thief. Increment `i`.

3. Return the total count.

#### 💻 C++ Solution

```cpp
// Intuition: Greedily match the earliest available policeman with the earliest available thief if within range k.
// Approach: Use two pointers to scan for the next policeman and the next thief; match them if their indices differ by at most k, otherwise advance the earlier pointer.
// Time Complexity: O(n) – each element is visited at most once by each pointer.
// Space Complexity: O(1) – only a fixed number of integer variables are used.
class Solution {
public:
    int catchThieves(vector<char>& arr, int k) {
        int n      = arr.size();
        int i      = 0;    // pointer to scan for 'P'
        int j      = 0;    // pointer to scan for 'T'
        int count = 0;    // total thieves caught

        while (i < n && j < n) {
            // move i to the next policeman
            while (i < n && arr[i] != 'P') {
                i++;
            }
            // move j to the next thief
            while (j < n && arr[j] != 'T') {
                j++;
            }

            // if both pointers are valid and within k distance, catch!
            if (i < n && j < n && abs(i - j) <= k) {
                count++;
                i++;
                j++;
            }
            // if thief is too far left, move thief pointer right
            else if (j < n && j < i) {
                j++;
            }
            // if policeman is too far left, move policeman pointer right
            else if (i < n && i < j) {
                i++;
            }
        }
        return count;
    }
};

/*
 *
 * Dry Run 1
 * Input: arr[] = ['T','T','P','P','T','P'], k = 2
 * Output: 3
 *
 * Steps:
 * i=0, j=0
 * skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 * |2−0|=2≤2 ⇒ count=1; i→3; j→1
 * skip i stays 3 (arr[3]='P'), skip j stays 1 (arr[1]='T')
 * |3−1|=2≤2 ⇒ count=2; i→4; j→2
 * skip i→5 (arr[5]='P'), skip j→4 (arr[4]='T')
 * |5−4|=1≤2 ⇒ count=3; i→6; j→5
 * i or j out of range ⇒ end.
 */

/*
 *
 * Dry Run 2
 * Input: arr[] = ['T','T','P','T','T','P','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 * skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 * |2−0|=2>1 and j<i ⇒ j→1
 * |2−1|=1≤1 ⇒ count=1; i→3; j→2
 * skip i→5 (arr[5]='P'), skip j→3 (arr[3]='T')
 * |5−3|=2>1 and j<i ⇒ j→4
 * |5−4|=1≤1 ⇒ count=2; i→6; j→5
 * i out of range ⇒ end.
 */

/*
 *
 * Dry Run 3
 * Input: arr[] = ['P','P','T','P','T','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 * skip i stays 0 (arr[0]='P'), skip j→2 (arr[2]='T')
 * |0−2|=2>1 and i<j ⇒ i→1
 * skip i stays 1 (arr[1]='P')
 * |1−2|=1≤1 ⇒ count=1; i→2; j→3
 * skip i→3 (arr[3]='P'), skip j→4 (arr[4]='T')
 * |3−4|=1≤1 ⇒ count=2; i→4; j→5
 * skip i→5 (arr[5]='T')→i→6; end.
 */

```

#### ☕ Java Solution

```java
// Intuition: Greedily match the earliest available policeman with the earliest available thief if within range k.
// Approach: Use two pointers to scan for the next policeman and the next thief; match them if their indices differ by at most k, otherwise advance the earlier pointer.
// Time Complexity: O(n) – each element is visited at most once by each pointer.
// Space Complexity: O(1) – only a fixed number of integer variables are used.
class Solution {
    public int catchThieves(char[] arr, int k) {
        int n      = arr.length;
        int i      = 0;    // pointer to scan for 'P'
        int j      = 0;    // pointer to scan for 'T'
        int count = 0;    // total thieves caught

        while (i < n && j < n) {
            // move i to the next policeman
            while (i < n && arr[i] != 'P') {
                i++;
            }
            // move j to the next thief
            while (j < n && arr[j] != 'T') {
                j++;
            }

            // if both pointers are valid and within k distance, catch!
            if (i < n && j < n && Math.abs(i - j) <= k) {
                count++;
                i++;
                j++;
            }
            // if thief is too far left, move thief pointer right
            else if (j < n && j < i) {
                j++;
            }
            // if policeman is too far left, move policeman pointer right
            else if (i < n && i < j) {
                i++;
            }
        }
        return count;
    }
}

/*
 *
 * Dry Run 1
 * Input: arr[] = ['T','T','P','P','T','P'], k = 2
 * Output: 3
 *
 * Steps:
 * i=0, j=0
 * skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 * |2−0|=2≤2 ⇒ count=1; i→3; j→1
 * skip i stays 3 (arr[3]='P'), skip j stays 1 (arr[1]='T')
 * |3−1|=2≤2 ⇒ count=2; i→4; j→2
 * skip i→5 (arr[5]='P'), skip j→4 (arr[4]='T')
 * |5−4|=1≤2 ⇒ count=3; i→6; j→5
 * i or j out of range ⇒ end.
 */

/*
 *
 * Dry Run 2
 * Input: arr[] = ['T','T','P','T','T','P','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 * skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 * |2−0|=2>1 and j<i ⇒ j→1
 * |2−1|=1≤1 ⇒ count=1; i→3; j→2
 * skip i→5 (arr[5]='P'), skip j→3 (arr[3]='T')
 * |5−3|=2>1 and j<i ⇒ j→4
 * |5−4|=1≤1 ⇒ count=2; i→6; j→5
 * i out of range ⇒ end.
 */

/*
 *
 * Dry Run 3
 * Input: arr[] = ['P','P','T','P','T','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 * skip i stays 0 (arr[0]='P'), skip j→2 (arr[2]='T')
 * |0−2|=2>1 and i<j ⇒ i→1
 * skip i stays 1 (arr[1]='P')
 * |1−2|=1≤1 ⇒ count=1; i→2; j→3
 * skip i→3 (arr[3]='P'), skip j→4 (arr[4]='T')
 * |3−4|=1≤1 ⇒ count=2; i→4; j→5
 * skip i→5 (arr[5]='T')→i→6; end.
 */

```

---

## 🔑 Key Insights

- **Greedy is Optimal:** By attempting to match the first available policeman with the first available thief, we ensure that we don't "waste" a policeman on a thief who could have been caught by an earlier policeman, thus saving the later policeman for a thief further down the line.
- **Sequential Scan:** The problem essentially boils down to two linear scans running in parallel. This avoids nested loops which would lead to complexity.
- **Distance Check:** The condition `abs(i - j) <= k` is the primary check. The logic handles the case where `abs(i - j) > k` by simply moving the pointer that is trailing behind, as that element has lost its chance to be part of a valid pair.

---

## 🚀 Further Exploration

- **Variant:** What if a policeman can catch multiple thieves?
- **Variant:** What if the range `k` is different for each policeman?
- **Similar Problem:** [Assign Cookies](https://leetcode.com/problems/assign-cookies/) - Matching constraints greedily.

---

## 🔗 References

- [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/police-and-thieves--141631/1)

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

- $Greedy$
- $Algorithms$
- $two-pointer-algorithm$

---

## 📜 License

<details>
<summary><b>MIT License</b></summary>

Copyright (c) 2026 Nilesh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

</details>

**⚠️ Educational Use Only**
