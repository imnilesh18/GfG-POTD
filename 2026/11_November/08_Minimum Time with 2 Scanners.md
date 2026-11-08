# 🟩 Minimum Time with 2 Scanners

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/find-the-minimum-time0253/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-19.53%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Geek has `n` documents that need to be scanned using two scanners. 
* **Scanner 1** takes `s1` units of time to scan one document.
* **Scanner 2** takes `s2` units of time to scan one document.

Both scanners can operate simultaneously, and each scanner can scan only one document at a time. A scanner can start scanning its next document immediately after finishing the current one. 

Find the **minimum time required** to scan all `n` documents.

---

## 💡 Examples

```text
Input: n = 2, s1 = 2, s2 = 4
Output: 4

```

We can either scan both documents using scanner 1, which takes `2 × 2 = 4` units of time, or scan one document using each scanner simultaneously, which takes `max(2, 4) = 4` units of time. Both approaches require 4 units of time.

```text
Input: n = 2, s1 = 1, s2 = 3
Output: 2
Explanation: The optimal approach is to scan both documents using scanner 1, which takes 2 × 1 = 2 units of time.

```

---

## ⚠️ Constraints

> * `1 ≤ n, s1, s2 ≤ 10^6`
> * `1 ≤ s1 * n, s2 * n ≤ 10^9`
> 
> 

---

## 🚀 Solution Approaches

### Optimal Approach (Binary Search on Answer)

**Intuition:**
The number of documents scanned increases monotonically as time increases. This monotonic nature allows us to use Binary Search on the answer space (time) to find the absolute minimum time needed to scan 'n' documents.

```cpp
// Intuition: The number of documents scanned increases as time increases, which gives a monotonic function. This allows us to use binary search on the answer (time) to find the absolute minimum time needed to scan 'n' documents.
// Approach: Set search boundaries for time from 1 to the worst-case maximum time (scanning all docs with the faster scanner). At each step, calculate the total documents scanned in 'mid' time using both scanners. If the total is greater than or equal to 'n', save 'mid' as a potential answer and search lower halves for a better minimum. Otherwise, search the upper half.
// Time Complexity: O(log(min(s1, s2) * n)) because we are applying binary search over the time range.
// Space Complexity: O(1) as we only use a few variables for the binary search state.

class Solution {
  public:
    int minTime(int n, int s1, int s2) {
        
        // Setup binary search boundaries
        // Minimum possible time is 1
        int low = 1;
        
        // Max possible time is scanning all docs with the faster scanner
        int high = min(s1, s2) * n;
        int ans = high;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            // Check total documents scanned in 'mid' time
            int docsScanned = (mid / s1) + (mid / s2);
            
            if (docsScanned >= n) {
                // Potential answer found, try to find a smaller time
                ans = mid;
                high = mid - 1;
            } else {
                // Not enough documents, need more time
                low = mid + 1;
            }
        }
        
        return ans;
    }
};

/*
*
* Dry Run
*
Input: n = 2, s1 = 2, s2 = 4
Faster scanner is s1 (takes 2 units). Max time = 2 * 2 = 4.
low = 1, high = 4, ans = 4

First iteration
mid = 1 + (4 - 1) / 2 = 2
docsScanned = (2 / 2) + (2 / 4) = 1 + 0 = 1
1 is less than 2, so low becomes 3

Second iteration
mid = 3 + (4 - 3) / 2 = 3
docsScanned = (3 / 2) + (3 / 4) = 1 + 0 = 1
1 is less than 2, so low becomes 4

Third iteration
mid = 4 + (4 - 4) / 2 = 4
docsScanned = (4 / 2) + (4 / 4) = 2 + 1 = 3
3 is greater than or equal to 2, ans becomes 4, high becomes 3

Loop terminates since low (4) is greater than high (3)
Final Answer: 4
*/

```

---

## 🧠 Key Insights

* **Monotonicity is Key:** Whenever a problem asks for a "minimum time" or "maximum capacity" and the condition (e.g., docs scanned >= n) switches from `false` to `true` permanently at a certain threshold, **Binary Search on Answer** is highly effective.
* **Math bounds:** Calculating `high = min(s1, s2) * n` sets an efficient and safe upper bound, preventing unnecessary wide searches and protecting against potential overflow.

---

## 🔗 Further Exploration

* Practice finding monotonic conditions in other problems.
* Similar concepts: "Koko Eating Bananas", "Allocate Minimum Number of Pages", or "Capacity To Ship Packages Within D Days".

---

## 📚 References

* **Problem Link:** [Minimum Time with 2 Scanners on GeeksforGeeks](https://www.geeksforgeeks.org/problems/find-the-minimum-time0253/1)
* **Company Tags:** Oracle

---

## 👤 Author

**Nilesh Kumar**

GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#binary-search` `#mathematics` `#oracle` `#geeksforgeeks` `#c++`