# 📈 Minimum Increment or Double Operations to Convert

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/minimum-steps-to-get-desired-array5519/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy: 49.53%](https://img.shields.io/badge/Accuracy-49.53%25-blue?style=for-the-badge)]()
[![Points: 4](https://img.shields.io/badge/Points-4-brightgreen?style=for-the-badge)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]`. Initially, you have another array containing only `0`s.
In one operation, you may either:
1. Choose any one element and **increase its value by 1**.
2. **Double the values of all elements** in the array simultaneously.

Find the **minimum number of operations** required to transform the initial all-zero array into the given array `arr[]`.

---

## 🚀 Examples

### Example 1
```text
Input: arr[] = [16, 16, 16]
Output: 7
Explanation: 
First, increase each element to make the array [1, 1, 1] (3 steps).
Then, multiply the whole array by 2 four times:
[1,1,1] -> [2,2,2] -> [4,4,4] -> [8,8,8] -> [16,16,16]
Total steps = 3 + 4 = 7.
```

### Example 2
```text
Input: arr[] = [2, 3]
Output: 4
Explanation: 
Start from [0, 0].
Increase both elements to get [1, 1] (2 steps)
Multiply once: [2, 2] (1 step)
Increase second element once: [2, 3] (1 step)
Total steps = 2 + 1 + 1 = 4.
```

<details>
<summary>📖 Example Breakdown</summary>

Let's break down how we achieve **[2, 3]** starting from `[0, 0]`:
- Initial State: `[0, 0]`
- **Step 1:** Increment index 0 -> `[1, 0]`
- **Step 2:** Increment index 1 -> `[1, 1]`
- **Step 3:** Double all elements -> `[2, 2]`
- **Step 4:** Increment index 1 -> `[2, 3]`

*Total Steps = 4.*
</details>

---

## 🛑 Constraints

> - `1 ≤ arr.size() ≤ 10^5`
> - `0 ≤ arr[i] ≤ 10^9`

---

## 💡 Solution Approaches

### Reverse Engineering (Greedy Approach)
Instead of building the array from `0`s up to `arr[]`, it is much easier to start with `arr[]` and reduce it to all `0`s using the reverse operations:
1. **Decrement by 1** (Reverse of increment): Do this whenever an element is odd.
2. **Divide by 2** (Reverse of double): Do this whenever all elements are even. 

By calculating the total decrements (odd states) and the maximum divisions required by any single number, we can easily find the optimal minimum operations.

```cpp
// Intuition: To find the minimum operations efficiently, we reverse engineer the process. Starting from the target array, we reduce elements to 0 by decrementing odd numbers (representing increments) and dividing by 2 (representing array doubling).
// Approach: Iterate through each element. Count the number of -1 operations needed (when odd) and /2 operations needed (when even) to reduce it to 0. Add all -1 operations to total, and track the maximum /2 operations across all elements.
// Time Complexity: O(n * log(max(arr[i]))) because for each of the n elements, we divide by 2 logarithmically until it reaches 0.
// Space Complexity: O(1) as we only use a few integer variables for counting, utilizing constant extra space.

class Solution {
  public:
    int countMinOperations(vector<int>& arr) {
        int maxDoubles = 0; // Tracks the maximum double operations needed for the entire array
        int totalIncrements = 0; // Tracks the total increment operations needed for all elements
        
        for (int num : arr) {
            int doubles = 0; // Double operations for the current number
            
            // Reduce the current number to 0
            while (num > 0) {
                if (num % 2 == 1) {
                    // If odd, it must have been incremented individually
                    totalIncrements++;
                    num--; 
                } else {
                    // If even, it could have been doubled globally
                    doubles++;
                    num /= 2; 
                }
            }
            
            // The overall array doubles is the maximum required by any single element
            maxDoubles = max(maxDoubles, doubles);
        }
        
        return totalIncrements + maxDoubles;
    }
};

/*
* Dry Run
* Input: arr = [2, 3]
* 
* Process 2:
* - num = 2 (even) -> doubles = 1, num = 1
* - num = 1 (odd) -> totalIncrements = 1, num = 0
* Current maxDoubles = max(0, 1) = 1
* 
* Process 3:
* - num = 3 (odd) -> totalIncrements = 1 + 1 = 2, num = 2
* - num = 2 (even) -> doubles = 1, num = 1
* - num = 1 (odd) -> totalIncrements = 2 + 1 = 3, num = 0
* Current maxDoubles = max(1, 1) = 1
* 
* Total steps = totalIncrements (3) + maxDoubles (1) = 4
* Output: 4
*/
```

---

## 🔍 Key Insights
- **Greedy Reversal:** Building upward forces you to make complex choices about *when* to double. Tearing downward removes the ambiguity—if a number is odd, you *must* decrement.
- **Bitwise Analogy:** The number of decrements exactly equals the number of set bits (1s) in the binary representation of the number. The number of divisions by 2 exactly equals the position of the highest set bit.

---

## 🔗 Further Exploration
- Try thinking about how this can be implemented in a single pass using built-in bit manipulation functions like `__builtin_popcount()` and `__builtin_clz()`.
- Related Problems: Minimum Operations to reduce X to Zero, Minimum Moves to Equal Array Elements.

---

## 📚 References
- **GeeksforGeeks Problem:** [Minimum Increment or Double Operations to Convert](https://www.geeksforgeeks.org/problems/minimum-steps-to-get-desired-array5519/1)

---

## 👤 Author
**Nilesh Kumar**
- GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`Array` `Greedy` `Math` `GeeksforGeeks` `Dynamic Programming`