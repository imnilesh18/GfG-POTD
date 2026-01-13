# 🚌 Bus Ticket Change (Lemonade Change)

<p align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-Easy-green?style=for-the-badge&logo=geeksforgeeks" alt="GFG">
  <img src="https://img.shields.io/badge/Accuracy-52.02%25-blue?style=for-the-badge" alt="Accuracy">
  <img src="https://img.shields.io/badge/Points-2-yellow?style=for-the-badge" alt="Points">
  <img src="https://img.shields.io/badge/Language-C++-orange?style=for-the-badge" alt="Language">
</p>

> [!WARNING]
> **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/lemonade-change/1).

---

## 📝 Problem Statement

You are given an array `arr[]` representing passengers in a queue. Each bus ticket costs **5 coins**, and `arr[i]` denotes the note a passenger uses to pay (which can be **5**, **10**, or **20**).

You must serve the passengers in the given order and always provide the correct change so that each passenger effectively pays exactly **5 coins**.

Your task is to determine whether it is possible to serve **all passengers** in the queue without ever running out of change.

---

## 🔍 Examples

### Example 1
```text
Input: arr[] = [5, 5, 5, 10, 20]
Output: true
Explanation: 
1. First 3 customers pay 5. We collect three 5s.
2. Fourth customer pays 10. We give back one 5. (Remaining: two 5s, one 10).
3. Fifth customer pays 20. We give back one 10 and one 5.
All customers served.

```

### Example 2

```text
Input: arr[] = [5, 5, 10, 10, 20]
Output: false

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's walk through Example 2: `[5, 5, 10, 10, 20]`

1. **Passenger 1 (5):** We take 5. `Wallet: {5: 1, 10: 0}`.
2. **Passenger 2 (5):** We take 5. `Wallet: {5: 2, 10: 0}`.
3. **Passenger 3 (10):** We take 10, give back 5. `Wallet: {5: 1, 10: 1}`.
4. **Passenger 4 (10):** We take 10, give back 5. `Wallet: {5: 0, 10: 2}`.
5. **Passenger 5 (20):** Needs 15 change.
* Option A (10 + 5): We have 10s, but **no** 5s. Impossible.
* Option B (5 + 5 + 5): We have no 5s. Impossible.
* **Result:** Cannot serve passenger 5. Return `false`.



</details>

---

## 🛑 Constraints

* `1 ≤ arr.size() ≤ 10^5`
* `arr[i]` contains only `{5, 10, 20}`

---

## 💡 Solution Approach

### Greedy Approach (O(n))

The core problem is managing the "change" inventory.

* **$5 bills** are the most valuable for giving change because they can be used for both $10 (needs one 5) and $20 (needs 15 total) payments.
* **$10 bills** are less useful; they can only be used to help give change for a $20 payment.

**Strategy:** Always hold onto $5 bills as long as possible. When giving change for a $20, prioritize giving a $10 + $5 over three $5s.

```cpp
// Intuition: Since 5 is the smallest unit needed for change, we want to hoard them. When returning 15 (for a 20 bill), spending a 10 is 'cheaper' than spending two extra 5s because 10s have limited use.
// Approach: Iterate through the queue maintaining counts of 5s and 10s. For 10: return one 5. For 20: prefer returning 10+5, else 5+5+5. If at any point we lack change, return false.
// Time Complexity: O(N) - We iterate through the array once.
// Space Complexity: O(1) - We only store two integer counters.

class Solution {
  public:
    bool canServe(vector<int>& arr) {
    
        // counts of 5 and 10 notes
        int five = 0, ten = 0; 
    
        for (int i = 0; i < arr.size(); ++i) {
            
            // no change needed
            if (arr[i] == 5) {
                five++; 
            } 
            else if (arr[i] == 10) {
                
                // need one 5
                if (five == 0) return false; 
                five--; ten++;
            } 
            else {
                
                // b == 20
                // prefer 10+5 to save 5 notes
                if (ten > 0 && five > 0) {
                    ten--; five--;
                } 
                else if (five >= 3) {
                    five -= 3;
                } 
                else return false;
            }
        }
        return true;
    }
};

/*
*
* Dry Run
* Input: arr[] = [5, 5, 10, 10, 20]
* * i=0 (5) : five=1, ten=0
* i=1 (5) : five=2, ten=0
* i=2 (10): Give 5. five=1, ten=1
* i=3 (10): Give 5. five=0, ten=2
* i=4 (20): Need 15 change.
* - Try 10+5: have ten, but five=0. Fail.
* - Try 5+5+5: five=0. Fail.
* Result: false
*
*/

```

---

## 🔑 Key Insights

1. **Greedy Choice Property:** At the decision point (making change for 20), choosing to give `10 + 5` is always better or equal to giving `5 + 5 + 5` because it saves the more versatile $5 bills.
2. **Resource Hierarchy:** A 5 bill is strictly more versatile than a 10 bill in this context.
3. **Simplicity:** No need for DP or recursion; simple state tracking (`five`, `ten`) is sufficient.

---

## 🔗 Further Exploration

* **Lemonade Change** (LeetCode 860) - Identical problem.
* **Coin Change** - Solved using Dynamic Programming when greedy doesn't work (arbitrary coin denominations).

---

## 📚 References

* **[GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/lemonade-change/1)**

---

## 👤 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🔖 Tags

---

## 📜 License

This project is licensed under the [MIT License](https://www.google.com/search?q=LICENSE).

> **Note:** This repository is for learning purposes only. Please respect the Code of Conduct and contribution guidelines.
