<div align="center">

# 🟧 Subset Sum on Generated Sequence

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/tricky-subset-problem1557/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](#)
[![Accuracy: 37.44%](https://img.shields.io/badge/Accuracy-37.44%25-blue?style=for-the-badge)](#)
[![Points: 4](https://img.shields.io/badge/Points-4-success?style=for-the-badge)](#)
[![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](#)

⚠️ **Educational Use Only**
<br>
*This repository and its content are intended solely for educational purposes.*
*Solutions are provided for learning, practice, and reference only.*
*Problem statement and test cases are based on the GeeksforGeeks problem.*
</div>

---

## 📝 Problem Statement

There are `n` children standing in a queue, each assigned a number `arr[i]`. The teacher writes `s` on a paper and gives it to the first child. 

Each child writes the **sum of all numbers already on the paper** plus their assigned number `arr[i]`, then passes it to the next child.

Your task is to return `true` if a given target number `x` can be formed by adding some of the numbers written on the paper; otherwise, return `false`.

### 🚨 Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^9`
- `1 ≤ s ≤ 10^9`
- `0 ≤ x ≤ 10^9`

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [1, 2, 4, 2], s = 1, x = 7
Output: true
Explanation: 
The sequence of numbers written on the paper will be:
- Initial: 1
- 1st student: 1 + 1 = 2
- 2nd student: (1 + 2) + 2 = 5
- 3rd student: (1 + 2 + 5) + 4 = 12
- 4th student: (1 + 2 + 5 + 12) + 2 = 22
Final sequence: 1, 2, 5, 12, 22. 
Using 2 and 5 we can form exactly 7.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

1. **Start with** `s = 1`. Sequence: `[1]`. Cumulative sum `prefSum = 1`.
2. **First Element (`arr[0] = 1`)**: Calculate `prefSum + arr[0]` = `1 + 1 = 2`. 
   - Sequence becomes `[1, 2]`. 
   - `prefSum` updates to `1 + 2 = 3`.
3. **Second Element (`arr[1] = 2`)**: Calculate `3 + 2 = 5`. 
   - Sequence becomes `[1, 2, 5]`. 
   - `prefSum` updates to `3 + 5 = 8`.
4. **Third Element (`arr[2] = 4`)**: Calculate `8 + 4 = 12`. 
   - Sequence becomes `[1, 2, 5, 12]`. 
   - `prefSum` updates to `8 + 12 = 20`.
5. **Fourth Element (`arr[3] = 2`)**: Calculate `20 + 2 = 22`. 
   - Sequence becomes `[1, 2, 5, 12, 22]`.
6. **Greedy search for 7**: 
   - 22 > 7 (Skip)
   - 12 > 7 (Skip)
   - 5 <= 7 (Take 5, Target = 7 - 5 = 2)
   - 2 <= 2 (Take 2, Target = 2 - 2 = 0)
   - Target reached 0! Return `true`.

</details>

### Example 2

```text
Input: arr[] = [51, 88], s = 100, x = 500
Output: false
Explanation: 
The final sequence of numbers on the paper is 100, 151, 339. 
Using these numbers we cannot form exactly 500.
```

---

## 💻 Solution Approaches

### 1️⃣ Greedy Approach (Optimal)

```cpp
// Intuition: The sequence generated grows in a super-increasing manner because each new element is the sum of all previous elements plus a positive integer. Due to this property, a greedy approach from the largest generated element perfectly determines if the target sum can be formed without needing complex DP.
// Approach: 
// 1. Initialize a sequence array and append the starting value `s`.
// 2. Iterate through `arr`, generating the next number by adding the current `prefSum` to `arr[i]`.
// 3. Append this new number to the sequence and update `prefSum`.
// 4. Iterate backward through the generated sequence, greedily subtracting elements from `target` if they are less than or equal to `target`.
// 5. Finally, return true if `target` becomes 0, else false.
// Time Complexity: O(n), where n is the size of the array, for building the sequence and traversing it once.
// Space Complexity: O(n), for storing the generated sequence in an auxiliary array.

class Solution {
  public:
    // Check whether x can be formed.
    bool isPossible(vector<int> &arr, int s, int x) {
    
        // Generate the sequence written on the paper.
        vector<long long> seq;
        seq.push_back(s); // Add initial value
    
        long long prefSum = s; // Track running total of all elements in sequence
    
        for (int val : arr) {
            // New sequence value is current total sum + array value
            long long cur = prefSum + val;
            seq.push_back(cur);
            
            // Update running total for the next iteration
            prefSum += cur;
        }
    
        // Greedily subtract the largest possible values.
        long long target = x;
    
        // Traverse backwards starting from the largest generated number
        for (int i = seq.size() - 1; i >= 0; i--) {
            // If the current sequence number fits, subtract it from our target
            if (seq[i] <= target)
                target -= seq[i];
        }
    
        // If we exactly reduced the target to 0, it's possible
        return target == 0;
    }
};

/*
* Dry Run
* 
* Input: arr = [1, 2, 4, 2], s = 1, x = 7
* 
* 1. Sequence Generation Phase:
*    - Init: seq = [1], prefSum = 1
*    - arr[0]=1 : cur = 1 + 1 = 2.   seq = [1, 2],           prefSum = 1+2 = 3
*    - arr[1]=2 : cur = 3 + 2 = 5.   seq = [1, 2, 5],        prefSum = 3+5 = 8
*    - arr[2]=4 : cur = 8 + 4 = 12.  seq = [1, 2, 5, 12],    prefSum = 8+12 = 20
*    - arr[3]=2 : cur = 20 + 2 = 22. seq = [1, 2, 5, 12, 22], prefSum = 20+22 = 42
* 
* 2. Greedy Matching Phase (target = 7):
*    - i = 4 (seq[4]=22) : 22 > target (7) -> skip
*    - i = 3 (seq[3]=12) : 12 > target (7) -> skip
*    - i = 2 (seq[2]=5)  : 5 <= target (7) -> target = 7 - 5 = 2
*    - i = 1 (seq[1]=2)  : 2 <= target (2) -> target = 2 - 2 = 0
*    - i = 0 (seq[0]=1)  : 1 > target (0) -> skip
* 
* 3. Result Phase:
*    - target == 0 is true. Return true.
*/
```

---

## 🧠 Key Insights
- **Super-Increasing Sequence Property:** Because each element in the sequence is calculated as the sum of *all* previous elements plus a positive number, the sequence is "super-increasing".
- **Greedy is Optimal:** In a super-increasing sequence, any element `seq[i]` is strictly greater than the sum of all elements before it. This guarantees that if `seq[i]` can fit into the remaining target, you *must* take it, making the greedy choice 100% reliable.

---

## 🔗 Further Exploration
- **Related Topics:**
  - Greedy Algorithms
  - Prefix Sum Arrays
  - Subset Sum Problem (DP vs Greedy variations)
- **Similar Problems:**
  - [GeeksforGeeks: Subset Sum Problem (DP Variant)](https://www.geeksforgeeks.org/subset-sum-problem-dp-25/)
  - [LeetCode 322: Coin Change](https://leetcode.com/problems/coin-change/) (Compare when Greedy fails vs when it works)

---

## 📚 References
- **Original Problem:** [Subset Sum on Generated Sequence (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/tricky-subset-problem1557/1)

---

## 👨‍💻 Author

**Nilesh**  
[![GitHub](https://img.shields.io/badge/GitHub-imnilesh18-181717?style=flat-square&logo=github)](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Greedy` `Prefix Sum` `Array` `GeeksforGeeks` `C++` `DSA` `Math`