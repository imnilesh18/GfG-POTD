# 🟥 Minimum K Consecutive Bit Flips

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/minimum-number-of-k-consecutive-bit-flips--171650/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-58.52%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-orange?style=for-the-badge" alt="Points" />
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License" />
  </a>
</p>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

You are given a binary array `arr[]` (containing only `0`s and `1`s) and an integer `k`. 

In one operation, you can select a contiguous subarray of length `k` and **flip all its bits** (i.e., change every `0` to `1` and every `1` to `0`).

Your task is to find the **minimum** number of such operations required to make the entire array consist of only `1`s. If it is not possible to do so, return `-1`.

---

## 💡 Examples

### Example 1
```text
Input: arr = [1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1], k = 2
Output: 4 
Explanation: 4 operations are required to convert all 0's to 1's.
1. Select subarray [2, 3] and flip all bits, resulting array will be [1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1]
2. Select subarray [4, 5] and flip all bits, resulting array will be [1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1]
3. Select subarray [5, 6] and flip all bits, resulting array will be [1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1]
4. Select subarray [6, 7] and flip all bits, resulting array will be [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
```

### Example 2
```text
Input: arr = [0, 0, 1, 1, 1, 0, 0], k = 3
Output: -1
Explanation: It is not possible to convert all elements to 1's by performing any number of operations.
```

<details>
<summary>📖 <b>Example Breakdown (Example 2 Walkthrough)</b></summary>

1. **Initial Array:** `[0, 0, 1, 1, 1, 0, 0]`, `k = 3`
2. **Index 0:** Element is `0`. We must flip `[0, 1, 2]`. 
   - Array becomes: `[1, 1, 0, 1, 1, 0, 0]`
   - Operations: `1`
3. **Index 1:** Element is `1`. Move ahead.
4. **Index 2:** Element is `0`. We must flip `[2, 3, 4]`.
   - Array becomes: `[1, 1, 1, 0, 0, 0, 0]`
   - Operations: `2`
5. **Index 3:** Element is `0`. We must flip `[3, 4, 5]`.
   - Array becomes: `[1, 1, 1, 1, 1, 1, 0]`
   - Operations: `3`
6. **Index 6:** Element is `0`, but we don't have `k=3` elements left to flip! Hence, it's impossible. Return `-1`.

</details>

---

## ⚙️ Constraints

- $1 \le arr.size() \le 10^6$
- $1 \le k \le arr.size()$

---

## 🚀 Solution Approach

### Optimized Approach (Sliding Window & Queue)

```cpp
// Intuition: Instead of manually flipping 'k' elements (which takes O(N*K) time), we use a queue and a flag to track the effect of recent flips in an active window of size 'k'. This reduces the time to O(N).
// Approach: 
// 1. Maintain a 'flag' to keep track of the active flips affecting the current element.
// 2. Use a queue to remember whether a flip was initiated at a past index.
// 3. Slide the window: if index >= k, remove the effect of the flip that fell out of our size 'k' window.
// 4. Determine the actual state of arr[i] by considering the active 'flag'.
// 5. If arr[i] is 0, we must flip a subarray of size 'k' starting here. Check if we have enough elements left. If so, increment the answer, toggle 'flag', and push 1 to the queue.
// Time Complexity: O(N) where N is the length of the array, as we iterate through the array once.
// Space Complexity: O(K) because the queue stores at most K elements corresponding to our active sliding window.

class Solution {
  public:
    int kBitFlips(vector<int> &arr, int k) {
        int n = arr.size(); 
        int res = 0, flag = 0;
        queue<int> q; 
    
        for (int i = 0; i < n; i++) {
            
            // Remove flip effect if it goes out of our k-sized window
            if(i >= k) {
                flag ^= q.front();
                q.pop();
            }
            
            // If flag = 1, then flip the current index virtually
            if(flag == 1)
                arr[i] ^= 1;
            
            // Finally, if arr[i] = 0, then we need to flip
            if(arr[i] == 0) {
                
                // Check if k elements are left to perform a valid flip
                if(i + k > n) 
                    return -1;
                
                res += 1;
                
                // Flip flag so that upcoming elements in the window are also flipped
                flag ^= 1;
                
                // If we flip, push 1 to the queue
                q.push(1);
            }
            else {
                // If we don't flip, push 0 to queue
                q.push(0);
            }
        }
    
        return res; 
    }
};

/*
Dry Run

Input: arr = [0, 0, 1, 1, 1, 0, 0], k = 3
Initialization: n = 7, res = 0, flag = 0, q = []

i = 0: arr[0]=0. Needs flip. Can flip (0+3<=7). res=1, flag=1, q=[1].
i = 1: flag=1 so arr[1] becomes 0^1=1. No flip needed. q=[1, 0].
i = 2: flag=1 so arr[2] becomes 1^1=0. Needs flip. Can flip (2+3<=7). res=2, flag=0, q=[1, 0, 1].
i = 3: i>=k(3>=3), pop q[0]=1, flag becomes 0^1=1. flag=1 so arr[3] becomes 1^1=0. Needs flip. Can flip (3+3<=7). res=3, flag=0, q=[0, 1, 1].
i = 4: i>=k(4>=3), pop q[0]=0, flag becomes 0^0=0. flag=0 so arr[4] stays 1. No flip needed. q=[1, 1, 0].
i = 5: i>=k(5>=3), pop q[0]=1, flag becomes 0^1=1. flag=1 so arr[5] becomes 0^1=1. No flip needed. q=[1, 0, 0].
i = 6: i>=k(6>=3), pop q[0]=1, flag becomes 1^1=0. flag=0 so arr[6] stays 0. Needs flip. Cannot flip (6+3 > 7). Return -1.

Output: -1
*/
```

---

## 🧠 Key Insights

- **Difference Array / Sliding Window Idea:** Flips have an inherently canceling property (`x ^ 1 ^ 1 = x`). By maintaining an active `flag` of the ongoing flips, we avoid physically modifying the array.
- **Queue Synchronization:** The queue acts as a history tracker of exact size `k`. When an element pops out of the queue, its effect on the ongoing `flag` is reversed using `XOR`.
- **Greedy Choice:** When parsing left-to-right, if we encounter a `0`, we have no choice but to flip the window starting at that index, as previous elements are locked to `1`.

---

## 🔍 Further Exploration

- [Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)
- [Minimum Swaps to Group All 1's Together](https://www.geeksforgeeks.org/problems/minimum-swaps-to-group-all-1s-together/)
- Understand **Sliding Window + Bit Manipulation** techniques in array manipulation problems.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Minimum K Consecutive Bit Flips](https://www.geeksforgeeks.org/problems/minimum-number-of-k-consecutive-bit-flips--171650/1)

---

## ✍️ Author

**Nilesh** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Prefix Sum` `#Bit Magic` `#Sliding Window` `#Arrays` `#Queue` `#GeeksforGeeks` `#Hard`