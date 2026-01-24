# 🟢 Josephus problem

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge&logo=geeksforgeeks)
![Accuracy](https://img.shields.io/badge/Accuracy-57.26%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p>This repository and its content are intended solely for educational purposes.</p>
  <p>Solutions are provided for learning, practice, and reference only.</p>
  <p>Problem statement and test cases are based on the <a href="https://www.geeksforgeeks.org/problems/josephus-problem/1">GeeksforGeeks problem</a>.</p>
</div>

---

## 📝 Problem Statement

You are playing a game with `n` people standing in a circle, numbered from `1` to `n`. Starting from person 1, every `k`th person is eliminated in a circular fashion. The process continues until only one person remains.

Given integers `n` and `k`, return the **position** (1-based index) of the person who will survive.

---

## 📊 Examples

```bash
Input: n = 5, k = 2
Output: 3
Explanation: 
Firstly, the person at position 2 is killed.
Then the person at position 4 is killed.
Then the person at position 1 is killed.
Finally, the person at position 5 is killed.
So the person at position 3 survives.

```

```bash
Input: n = 7, k = 3
Output: 4
Explanation: The elimination order is 3 → 6 → 2 → 7 → 5 → 1, and the person at position 4 survives.

```

<details>
<summary><b>📖 Example Breakdown (n=5, k=2)</b></summary>

Let's visualize the circle as an array `[1, 2, 3, 4, 5]`. We eliminate every 2nd person.

1. **Start:** `[1, 2, 3, 4, 5]`. Count 2 starting from 1. Person **2** is eliminated.
* Remaining: `[1, 3, 4, 5]`. Next count starts from 3.


2. **Step 2:** Count 2 starting from 3. Person **4** is eliminated.
* Remaining: `[1, 3, 5]`. Next count starts from 5.


3. **Step 3:** Count 2 starting from 5. Wrap around to 1. Person **1** is eliminated.
* Remaining: `[3, 5]`. Next count starts from 3.


4. **Step 4:** Count 2 starting from 3. Person **5** is eliminated.
* Remaining: `[3]`.


5. **Survivor:** Person **3**.

</details>

---

## 🛑 Constraints

* $1 \leq n, k \leq 500$

---

## 💡 Solution Approaches

### 🚀 Iterative Approach (Optimized Space)

#### Brief Intuition

The problem can be solved using the recursive formula for the Josephus problem: . This essentially maps the survivor's position in a circle of size  to a circle of size . By building this up from the base case (1 person, position 0 in 0-based indexing), we can find the answer iteratively in  time and  space.

```cpp
// Intuition: The position of the survivor shifts by k in each step. We can build the solution from the base case of 1 person up to n people using the relation J(n, k) = (J(n-1, k) + k) % n.
// Approach: Iterate from i = 1 to N, updating the survivor's 0-based index using the modular arithmetic formula. Finally, convert to 1-based index.
// Time Complexity: O(N) as we iterate from 1 to N exactly once.
// Space Complexity: O(1) as we use only constant extra space for variables.

class Solution {
  public:
    int josephus(int N, int k){

        // Initialize variables i and ans with 1 and 0
        // respectively. 'ans' holds the 0-based index of the survivor for current size i.
        int i = 1, ans = 0;
    
        // Run a while loop till i <= N to compute survivor for each circle size
        while (i <= N) {
    
            // Update the Value of ans and Increment i by 1
            // recurrence relation: J(i, k) = (J(i-1, k) + k) % i
            ans = (ans + k) % i;
            i++;
        }
    
        // Return required answer
        // Add 1 to convert from 0-based index to 1-based index
        return ans + 1;
    }
};

/*
*
* Dry Run
* Input: N = 5, k = 2
*
* Initial State: i = 1, ans = 0 (Base case for 1 person: index 0 is the survivor)
*
* Loop 1 (i = 1):
* ans = (0 + 2) % 1 = 0
* i becomes 2
*
* Loop 2 (i = 2):
* ans = (0 + 2) % 2 = 0
* i becomes 3
*
* Loop 3 (i = 3):
* ans = (0 + 2) % 3 = 2
* i becomes 4
*
* Loop 4 (i = 4):
* ans = (2 + 2) % 4 = 0
* i becomes 5
*
* Loop 5 (i = 5):
* ans = (0 + 2) % 5 = 2
* i becomes 6
*
* Loop End (i > N)
*
* Return: ans + 1 = 2 + 1 = 3
* Output: 3
*
*/

```

---

## 🔑 Key Insights

* **Recursive Structure:** The problem has optimal substructure. If we eliminate one person, we are left with a subproblem of size , but the indices shift.
* **0-based Indexing:** The modulo operator `%` works naturally with 0-based indexing. That is why we compute the answer as 0-based `ans` throughout the loop and only add `1` at the very end to satisfy the problem requirement.
* **Space Optimization:** While a naive recursion takes  stack space, the iterative solution effectively calculates the same values using just two integer variables, achieving  auxiliary space.

---

## 🚀 Further Exploration

* **Linear Time:** This solution is . Can we do better if  is small or very large?
* **Generalization:** What if  changes at every step?
* **Related Problems:**
* [Find the Winner of the Circular Game (LeetCode)](https://leetcode.com/problems/find-the-winner-of-the-circular-game/)



---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/josephus-problem/1)
* [Wikipedia: Josephus Problem](https://en.wikipedia.org/wiki/Josephus_problem)

---

## 🧑‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> **Note:** This repository is for educational purposes only. Please respect the coding platforms' terms of service.
