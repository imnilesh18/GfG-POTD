# ⚖️ Balancing with Distinct Powers

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
  <img src="https://img.shields.io/badge/Accuracy-67.39%25-blue?style=for-the-badge" alt="Accuracy: 67.39%" />
  <img src="https://img.shields.io/badge/Points-2-blue?style=for-the-badge" alt="Points: 2" />
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a simple weighing scale with two pans, a target weight **$b$**, and a set of weights where each weight is a distinct power of **$a$**, find if the scale can be balanced[cite: 1]. 
The scale is balanced if: **$b$ + (some powers of $a$) = (some other powers of $a$)**[cite: 1].

**Note:** Exactly one weight is available for each power of **$a$**, so each power can be used at most once[cite: 1].

---

## 💡 Examples

### Example 1

```text
Input: a = 4, b = 11[cite: 1]
Output: true[cite: 1]
Explanation: 11 + 4 + 1 = 16. So, target = 11 can be balanced using powers of 4[cite: 1].
```

### Example 2

```text
Input: a = 3, b = 5[cite: 1]
Output: true[cite: 1]
Explanation: 5 + 3 + 1 = 9. So, target = 5 can be balanced using powers of 3[cite: 1].
```

<details>
<summary>📖 <b>Example Breakdown (a = 3, b = 5)</b></summary>
<br>

To balance target $5$ using powers of $3$ ($3^0=1, 3^1=3, 3^2=9$):
1. Place the target $5$ on the left pan.
2. Place the weights $3^1=3$ and $3^0=1$ on the left pan alongside the target ($5 + 3 + 1 = 9$).
3. Place the weight $3^2=9$ on the right pan.
4. The scale balances perfectly ($9 = 9$).

</details>

---

## ⚙️ Constraints

> - **$2 \leq a \leq 10^9$**[cite: 1]
> - **$1 \leq b \leq 10^9$**[cite: 1]
> - **Expected Time Complexity:** $O(\log b)$[cite: 1]
> - **Expected Auxiliary Space:** $O(1)$[cite: 1]

---

## 🧠 Solution Approaches

### Mathematical Base Conversion (Optimized Approach)

**Intuition:** 
The problem essentially asks if the number $b$ can be represented in base $a$ using only the coefficients $\{-1, 0, 1\}$. By continuously taking the modulo of $b$ with $a$, we extract its base $a$ digits. If a digit is $1$ or $0$, we simply process it. If it is $a - 1$, it acts as a $-1$ on the current side of the scale, meaning we must "carry over" an additional $1$ to the next higher power on the opposite side. If any other remainder occurs, balancing is impossible.

```cpp
// Intuition: The problem asks if 'b' can be represented in base 'a' using only coefficients {-1, 0, 1}. This translates to checking if each digit in base 'a' is either 0, 1, or equivalent to -1 (which is a-1).
// Approach: Extract digits by taking b % a. If the digit is 0 or 1, move to the next power. If the digit is a - 1, it acts as a -1, so we add a carry of 1 to the next power. Any other digit makes balancing impossible.
// Time Complexity: O(log_a(b)) because we are continuously dividing 'b' by 'a', successfully reducing the problem size logarithmically.
// Space Complexity: O(1) because we only use a few auxiliary variables for our calculation.
class Solution {
  public:
    bool balancePan(int a, int b) {
        while (b > 0) {
            // Extract the current least significant digit in base 'a'
            int rem = b % a;
            
            // Check if remainder corresponds to coefficient 0 or 1
            if (rem == 0 || rem == 1) {
                b = b / a; // Move to the next digit normally
            } 
            // Check if remainder corresponds to coefficient -1 (which is a - 1 in modulo a)
            else if (rem == a - 1) {
                b = (b / a) + 1; // Carry over 1 to the next higher power
            } 
            // Any other remainder means it's impossible to balance under the constraints
            else {
                return false; // Invalid digit found, balancing fails
            }
        }
        
        return true; // All digits processed successfully
    }
};

/*
*
* Dry Run
* Input: a = 3, b = 5
* Iteration 1:
* b = 5, rem = 5 % 3 = 2.
* rem == 2 (which equals a - 1). 
* b = (5 / 3) + 1 = 1 + 1 = 2.
* Iteration 2:
* b = 2, rem = 2 % 3 = 2.
* rem == 2 (which equals a - 1).
* b = (2 / 3) + 1 = 0 + 1 = 1.
* Iteration 3:
* b = 1, rem = 1 % 3 = 1.
* rem == 1.
* b = 1 / 3 = 0.
* Loop terminates. Returns true.
*
*/
```

---

## 🔑 Key Insights

- **Base representation modification:** Standard base conversion yields digits from $0$ to $a-1$. This problem requires a modified base system where the allowed digits are only $0, 1$, and $-1$. 
- **Modulo Arithmetic:** The mathematical trick here is recognizing that a remainder of $a - 1$ is perfectly equivalent to a coefficient of $-1$ combined with a $+1$ carry sent to the next decimal place (just like borrowing in standard subtraction).
- **Early Exit:** The algorithm instantly returns `false` the moment it encounters a remainder that is neither $0$, $1$, nor $a-1$, making it highly efficient.

---

## 🚀 Further Exploration

If you enjoyed this problem, you might want to practice these related GeeksforGeeks problems:
* **Check if a number is power of another number**
* **Find the missing weights (Balance Scale Problem variants)**
* **Base Conversion problems**

---

## 🔗 References

* **Original Problem:** [GeeksforGeeks - Balancing with Distinct Powers](https://www.geeksforgeeks.org/problems/balancing-pan5038/1)[cite: 1]
* **Topic Tags:** Mathematics[cite: 1]

---

## 👨‍💻 Author

**Nilesh Kumar**  
🔗 GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#Mathematics` `#Base-Conversion` `#Modulo-Arithmetic` `#GeeksforGeeks` `#C++`
