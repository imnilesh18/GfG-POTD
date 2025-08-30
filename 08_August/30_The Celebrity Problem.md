# 🧍 The Celebrity Problem

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/the-celebrity-problem/1).

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/the-celebrity-problem/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG Link">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Accuracy-38.33%25-orange.svg?style=for-the-badge" alt="Accuracy: 38.33%">
  <img src="https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge" alt="Points: 4">
  <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License: MIT">
</p>

---

## 📄 Problem Statement

A celebrity is a person who is **known to all** but does not know anyone at a party. A party is being organized by some people. A square matrix `mat[][]` of size `n*n` is used to represent people at the party such that if an element of row `i` and column `j` is set to `1` it means the `i`th person knows the `j`th person.

You need to return the **index** of the celebrity in the party. If the celebrity does not exist, return `-1`.

**Note**: Follow 0-based indexing.

---

## 💡 Examples

### Example 1
```
Input:
mat[][] = [[1, 1, 0],
           [0, 1, 0],
           [1, 1, 1]]
Output: 1
Explanation:
0th and 2nd person both know 1st person, and 1st person does not know anyone.
Therefore, 1 is the celebrity.
```

### Example 2
```
Input:
mat[][] = [[1, 1], 
           [1, 1]]
Output: -1
Explanation:
Since both people at the party know each other, none of them is a celebrity.
```
<details>
  <summary>📖 Example 1 Breakdown</summary>
  
  Let's walk through `mat[][] = [[1, 1, 0], [0, 1, 0], [1, 1, 1]]` with `n=3`.

  A celebrity must have a row of all `0`s (except `mat[i][i]`) and a column of all `1`s (except `mat[i][i]`).

  - **Person 0**:
    - Row `[1, 1, 0]`: Knows person 1. **Not a celebrity**.
    - Column `[1, 0, 1]`: Not everyone knows person 0.
  - **Person 1**:
    - Row `[0, 1, 0]`: Knows only themself. This is a potential celebrity.
    - Column `[1, 1, 1]`: Everyone (0, 1, 2) knows person 1.
    - Conditions met: Person 1 knows no one else, and everyone else knows person 1. **So, 1 is the celebrity.**
  - **Person 2**:
    - Row `[1, 1, 1]`: Knows everyone. **Not a celebrity**.

  The output is `1`.
</details>

---

## ⛓️ Constraints

> `1 ≤ mat.size() ≤ 1000`
> `0 ≤ mat[i][j] ≤ 1`
> `mat[i][i] = 1`

---

## ⚙️ Solution Approaches

### Optimized Approach (Two Pointers)

The core idea is to eliminate candidates until only one potential celebrity remains. We use two pointers, `i` starting from the beginning and `j` from the end.

- If `mat[i][j] == 1`, it means person `i` knows person `j`. Therefore, `i` cannot be a celebrity. We move `i` forward.
- If `mat[i][j] == 0`, it means `i` does not know `j`. This implies `j` cannot be a celebrity (because a celebrity is known by everyone). We move `j` backward.

We repeat this until `i` and `j` meet. The person at this index is our *potential* celebrity. Finally, we must verify if this candidate is indeed a celebrity by checking their row (knows no one) and column (known by everyone).

#### C++ Code
```cpp
// Intuition: We can eliminate one person from being a celebrity candidate in each step.
// If person A knows person B, A cannot be a celebrity. If A does not know B, B cannot be a celebrity.
// This allows us to narrow down the potential celebrity to a single candidate.
// Approach:
// 1. Use two pointers, `i` starting at 0 and `j` at n-1.
// 2. Loop while `i < j`.
// 3. If mat[i][j] is 1, it means i knows j, so i is not a celebrity. Increment i.
// 4. Otherwise, i doesn't know j, so j is not a celebrity. Decrement j.
// 5. The loop ends when i == j, leaving us with one candidate `c = i`.
// 6. Verify the candidate `c`. Check if everyone knows `c` (mat[i][c] == 1 for all i != c)
//    and if `c` knows no one (mat[c][i] == 0 for all i != c).
// 7. If verification passes, return `c`. Otherwise, return -1.
// Time Complexity: O(n) - The first loop runs n-1 times. The verification loop runs n times.
// Space Complexity: O(1) - No extra space is used.
class Solution {
  public:
    int celebrity(vector<vector<int>>& mat) {
        int n = mat.size();

        // Initialize two pointers for candidate elimination
        int i = 0, j = n - 1;
        while (i < j) {
            
            // If i knows j, i can't be a celebrity.
            if (mat[i][j] == 1) 
                i++;
    
            // If i doesn't know j, j can't be a celebrity.
            else
                j--;
        }
    
        // The potential celebrity is at index i (or j, since they are equal)
        int c = i;
    
        // Verify if the candidate 'c' is truly a celebrity
        for (i = 0; i < n; i++) {
            // Skip self-check
            if(i == c) continue;
    
            // Check two conditions:
            // 1. `mat[c][i]`: Does c know anyone else? (Should be 0)
            // 2. `!mat[i][c]`: Does anyone not know c? (Should be 1)
            // If either fails, 'c' is not a celebrity
            if (mat[c][i] || !mat[i][c])
                return -1;
        }
    
        // If all checks pass, we found the celebrity
        return c;
        
    }
    /*
    *
    * Dry Run
    *
    * Input: mat[][] = [[1, 1, 0], [0, 1, 0], [1, 1, 1]], n = 3
    *
    * Elimination Phase:
    * i = 0, j = 2
    * mat[0][2] = 0. Person 2 is not a celebrity. j--.
    * i=0, j=1
    * mat[0][1] = 1. Person 0 is not a celebrity. i++.
    * i=1, j=1
    * Loop terminates. Candidate c = 1.
    *
    * Verification Phase (c = 1):
    * i = 0: mat[1][0] is 0 (1 knows 0? No). !mat[0][1] is !1=0 (0 knows 1? Yes). Condition `0 || 0` is false. Continue.
    * i = 1: continue (skip self)
    * i = 2: mat[1][2] is 0 (1 knows 2? No). !mat[2][1] is !1=0 (2 knows 1? Yes). Condition `0 || 0` is false. Continue.
    *
    * Loop finishes. All checks passed.
    * Return 1.
    *
    */
};
```

#### Java Code
```java
// Intuition: The problem can be solved by eliminating candidates. In any pair (i, j), if i knows j, i cannot be a celebrity.
// If i does not know j, j cannot be a celebrity. This allows us to find a single potential candidate in linear time.
// Approach:
// 1. Initialize two pointers, 'i' at 0 and 'j' at n-1.
// 2. Iterate while i < j. If person 'i' knows 'j', 'i' is eliminated, so we do i++.
// 3. Otherwise, 'j' is eliminated, so we do j--.
// 4. After the loop, a single candidate remains at index 'i'.
// 5. Verify this candidate. A person 'c' is a celebrity if they know no one (except themself) and everyone knows them.
// 6. Iterate through all people: if i != c, check if mat[c][i] == 1 (c knows i) or mat[i][c] == 0 (i doesn't know c).
// 7. If any of these conditions are true for any person, the candidate is invalid. Return -1.
// 8. If the candidate passes all checks, return their index.
// Time Complexity: O(n) - The elimination process takes O(n) and the verification takes O(n).
// Space Complexity: O(1) - Constant extra space is used.
class Solution {
    public int celebrity(int mat[][]) {
        int n = mat.length;
        
        // Use two pointers to find a potential celebrity candidate
        int i = 0;
        int j = n - 1;
        
        while (i < j) {
            // If i knows j, i cannot be a celebrity.
            if (mat[i][j] == 1) {
                i++;
            } 
            // If i does not know j, j cannot be a celebrity.
            else {
                j--;
            }
        }
        
        // 'i' is now our potential celebrity candidate.
        int c = i;
        
        // Verify the candidate.
        for (int k = 0; k < n; k++) {
            // We don't check the candidate against themself.
            if (k == c) continue;
            
            // Check if 'c' knows 'k' OR if 'k' does not know 'c'.
            // If either is true, 'c' is not a celebrity.
            if (mat[c][k] == 1 || mat[k][c] == 0) {
                return -1;
            }
        }
        
        // If the candidate passed all checks, return their index.
        return c;
    }
    /*
    *
    * Dry Run
    *
    * Input: mat[][] = [[1, 1, 0], [0, 1, 0], [1, 1, 1]], n = 3
    *
    * Elimination Phase:
    * i = 0, j = 2
    * mat[0][2] = 0. Person 2 is eliminated. j--.
    * i=0, j=1
    * mat[0][1] = 1. Person 0 is eliminated. i++.
    * i=1, j=1
    * Loop ends. Candidate c = 1.
    *
    * Verification Phase (c = 1):
    * k = 0: mat[1][0] is 0, mat[0][1] is 1. Conditions are false. Ok.
    * k = 1: continue (skip self)
    * k = 2: mat[1][2] is 0, mat[2][1] is 1. Conditions are false. Ok.
    *
    * Loop finishes.
    * Return 1.
    *
    */
}
```

---

## 🚀 Key Insights

- The **two-pointer elimination** strategy is highly efficient because, in each comparison, we can definitively rule out one of the two people from being a celebrity.
- A celebrity must simultaneously satisfy two conditions: their row in the adjacency matrix must be all zeros (they know no one), and their column must be all ones (everyone knows them). (Ignoring the diagonal `mat[i][i]`).
- After finding a single candidate, a **second pass for verification** is mandatory. The elimination phase only proves that no *other* person can be a celebrity, not that the remaining candidate *is* one.

---

## 🔭 Further Exploration

- [Find the Town Judge](https://leetcode.com/problems/find-the-town-judge/): A similar problem on LeetCode with a slightly different representation.
- [Number of Islands](https://www.geeksforgeeks.org/problems/find-the-number-of-islands/1): Another classic graph/matrix traversal problem.

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/the-celebrity-problem/1)
- [GFG Article on The Celebrity Problem](https://www.geeksforgeeks.org/the-celebrity-problem/)

---

## 🧑‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p align="left">
  <a href="https://github.com/search?q=topic%3Astack"><img src="https://img.shields.io/badge/Stack-blue?style=for-the-badge"></a>
  <a href="https://github.com/search?q=topic%3Agraph"><img src="https://img.shields.io/badge/Graph-228B22?style=for-the-badge"></a>
  <a href="https://github.com/search?q=topic%3Amatrix"><img src="https://img.shields.io/badge/Matrix-FF8C00?style=for-the-badge"></a>
  <a href="https://github.com/search?q=topic%3Ageeksforgeeks"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge"></a>
</p>

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

> **Note**: This is for educational purposes only. The problem and its constraints are from GeeksforGeeks.