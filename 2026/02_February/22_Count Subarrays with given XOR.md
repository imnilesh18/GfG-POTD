<div align="center">
  
# 🟧 Count Subarrays with given XOR
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/count-subarray-with-given-xor/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/problems/count-subarray-with-given-xor/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-58.86%25-green?style=for-the-badge)](https://www.geeksforgeeks.org/problems/count-subarray-with-given-xor/1)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/count-subarray-with-given-xor/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only** > This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the original **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given an array of integers `arr[]` and a number `k`, count the number of subarrays having the **XOR** of their elements as `k`.

*Note: It is guaranteed that the total count will fit within a 32-bit integer.*

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [4, 2, 2, 6, 4], k = 6
Output: 4
Explanation: The subarrays having XOR of their elements as 6 are [4, 2], [4, 2, 2, 6, 4], [2, 2, 6], and [6]. Hence, the answer is 4.
```

### Example 2
```text
Input: arr[] = [5, 6, 7, 8, 9], k = 5
Output: 2
Explanation: The subarrays having XOR of their elements as 5 are [5] and [5, 6, 7, 8, 9]. Hence, the answer is 2.
```

### Example 3
```text
Input: arr[] = [1, 1, 1, 1], k = 0
Output: 4
Explanation: The subarrays are [1, 1], [1, 1], [1, 1] and [1, 1, 1, 1].
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>

Let's break down `arr = [4, 2, 2, 6, 4]` and `k = 6`:
- `[4, 2]` 👉 `4 ^ 2 = 6`
- `[4, 2, 2, 6, 4]` 👉 `4 ^ 2 ^ 2 ^ 6 ^ 4 = 6`
- `[2, 2, 6]` 👉 `2 ^ 2 ^ 6 = 6`
- `[6]` 👉 `6`

Total sub-arrays found = 4.
</details>

---

## ⚙️ Constraints

> - `1 <= arr.size() <= 10^5`
> - `0 <= arr[i] <= 10^5`
> - `0 <= k <= 10^5`

---

## 🚀 Solution Approach

The optimized approach heavily relies on the **Prefix XOR** property and a **Hash Map**. 

```cpp
// Intuition: If the XOR of elements from start to index i is 'prefXOR', and we want a subarray ending at i with XOR 'k', the prefix XOR just before this subarray must have been 'prefXOR ^ k'.
// Approach: Traverse the array maintaining a running prefix XOR. Store the frequencies of all seen prefix XORs in a hash map. For each element, check if 'prefXOR ^ k' exists in the map and add its frequency to the result.
// Time Complexity: O(N) on average, where N is the size of the array, since hash map insertions and lookups take O(1) expected time.
// Space Complexity: O(N) in the worst case to store the prefix XOR frequencies in the hash map.
class Solution {
  public:
    // Function to find the count of subarrays of arr 
    // with XOR value equals to k
    int subarrayXor(vector<int>& arr, int k) {
        int res = 0; 
    
        // Create hash map that stores number of prefix arrays corresponding to a XOR value
        unordered_map<int, int> mp;
       
        int prefXOR = 0;
       
        for (int val : arr) {
           
            // Find XOR of current prefix
            prefXOR ^= val;
    
            // If prefXOR ^ k exists in mp, there is a valid subarray ending here
            res = res + mp[prefXOR ^ k];
    
            // If this prefix subarray itself has XOR equal to k, it forms a valid subarray
            if (prefXOR == k)
                res++;
    
            // Add the XOR of this subarray to the map
            mp[prefXOR]++;
        }
    
        // Return total count of subarrays having XOR equal to k
        return res;
    }
};

/*
Dry Run

Input: arr = [4, 2, 2, 6, 4], k = 6
Initialize: res = 0, prefXOR = 0, mp = empty

Iteration 1: val = 4
prefXOR = 0 ^ 4 = 4
prefXOR ^ k = 4 ^ 6 = 2
2 is not in mp -> res remains 0
prefXOR != k (4 != 6)
mp[4] becomes 1

Iteration 2: val = 2
prefXOR = 4 ^ 2 = 6
prefXOR ^ k = 6 ^ 6 = 0
0 is not in mp -> res remains 0
prefXOR == k (6 == 6) -> res becomes 1
mp[6] becomes 1

Iteration 3: val = 2
prefXOR = 6 ^ 2 = 4
prefXOR ^ k = 4 ^ 6 = 2
2 is not in mp -> res remains 1
prefXOR != k (4 != 6)
mp[4] becomes 2

Iteration 4: val = 6
prefXOR = 4 ^ 6 = 2
prefXOR ^ k = 2 ^ 6 = 4
mp has 4 with frequency 2 -> res = 1 + 2 = 3
prefXOR != k (2 != 6)
mp[2] becomes 1

Iteration 5: val = 4
prefXOR = 2 ^ 4 = 6
prefXOR ^ k = 6 ^ 6 = 0
0 is not in mp -> res remains 3
prefXOR == k (6 == 6) -> res = 3 + 1 = 4
mp[6] becomes 2

Final Output: res = 4
*/
```

---

## 🧠 Key Insights

* **XOR Reversibility Property:** The mathematical foundation relies on the idea that if `A ^ B = C`, then `A ^ C = B`. 
* By converting this to arrays: if `Current Prefix XOR ^ Target XOR (k) = Required Prefix XOR`, we only need to lookup the count of `Required Prefix XOR` in the past elements to instantly know how many valid subarrays end at the current index.
* Doing this incrementally drops an $O(N^2)$ brute-force check to $O(N)$ linear time.

---

## 🔍 Further Exploration

If you enjoyed solving this, try these related classic coding problems:
- Subarray Sum Equals K (Very similar, using Addition/Subtraction instead of XOR)
- Longest Subarray with Zero Sum
- Count number of subarrays with given XOR (Alternative variations)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks - Count Subarrays with given XOR](https://www.geeksforgeeks.org/problems/count-subarray-with-given-xor/1)
- **Hash Maps in C++:** [std::unordered_map documentation](https://en.cppreference.com/w/cpp/container/unordered_map)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

Let's connect and code together!

---

## 🏷️ Tags

`#Arrays` `#Hash-Map` `#Prefix-Sum` `#Bit-Magic` `#GeeksforGeeks` `#Interview-Prep`
