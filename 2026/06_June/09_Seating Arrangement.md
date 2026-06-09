# 🪑 Seating Arrangement

<div align="center">
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/seating-arrangement--170647/1)
[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)](https://www.geeksforgeeks.org/problems/seating-arrangement--170647/1)
[![Accuracy: 49.85%](https://img.shields.io/badge/Accuracy-49.85%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/seating-arrangement--170647/1)
[![Points: 2](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/seating-arrangement--170647/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](#-license)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an integer `k` representing the number of people to be seated and an array `seats[]`, where `0` denotes an empty seat and `1` denotes an occupied seat. 

Determine whether it is possible to seat all `k` people such that **no two occupied seats are adjacent** (including both the newly seated people and the originally seated people).

---

## 💡 Examples

### Example 1
```text
Input: k = 2, seats[] = [0, 0, 1, 0, 0, 0, 1]
Output: true
Explanation: The two people can sit at index 0 and 4.
```

### Example 2
```text
Input: k = 1, seats[] = [0, 1, 0]
Output: false
Explanation: There is no way to get a seat for one person.
```

### Example 3
```text
Input: k = 0, seats[] = [0, 0, 0, 1, 1]
Output: false
Explanation: The seating arrangement already contains two adjacent occupied seats at indices 3 and 4.
```

<details>
<summary>📖 Example Breakdown (Click to Expand)</summary>

Let's trace **Example 1**: `k = 2`, `seats[] = [0, 0, 1, 0, 0, 0, 1]`

1. **Index 0:** `seats[0]` is `0`. Left boundary is effectively empty, right neighbor is `0`. Valid! Seat a person.
   * Update: `seats[0] = 1`, `k = 1`.
2. **Index 1:** `seats[1]` is `0`. Left neighbor `seats[0]` is now `1`. Invalid! Skip.
3. **Index 2:** `seats[2]` is `1`. Already occupied. Skip.
4. **Index 3:** `seats[3]` is `0`. Left neighbor `seats[2]` is `1`. Invalid! Skip.
5. **Index 4:** `seats[4]` is `0`. Left neighbor is `0`, right neighbor is `0`. Valid! Seat a person.
   * Update: `seats[4] = 1`, `k = 0`.
6. **Goal reached:** Since `k` is now `0`, we successfully seated everyone. Return `true`.

</details>

---

## ⚠️ Constraints

* **0 ≤ k ≤ 10^5**
* **1 ≤ seats.size() ≤ 10^5**
* **seats[i] == 0 or seats[i] == 1**

---

## 🚀 Solution Approach

### Greedy Approach

**Intuition:**
A greedy approach works perfectly here. We can iterate through the seats and place a person at the earliest available valid empty seat. We just need to check the immediate left and right neighbors. We must also ensure no two `1`s are adjacent in the original array before evaluating empty spots.

```cpp
// Intuition: A greedy approach works perfectly here. We can iterate through the seats and place a person at the earliest available valid empty seat. We just need to check left and right neighbors. We also must ensure no two '1's are adjacent in the original array.
// Approach: Iterate through the array. If a seat is occupied (1), verify the next seat isn't also occupied to catch invalid initial states. If a seat is empty (0) and we still have people to seat (k > 0), check if both adjacent seats (if they exist) are empty. If yes, seat the person (change 0 to 1) and decrement k. After the loop, return true if k <= 0.
// Time Complexity: O(N) because we traverse the seats array exactly once, performing constant time operations at each step.
// Space Complexity: O(1) as we modify the given array in-place without utilizing any extra memory structures.

class Solution {
  public:
    bool canSeatAllPeople(int k, vector<int> &seats) {
        int n = seats.size();
        
        for (int i = 0; i < n; ++i) {
            if (seats[i] == 1) {
                // Check for pre-existing adjacent occupied seats to catch invalid arrays
                if (i < n - 1 && seats[i + 1] == 1) {
                    return false; 
                }
            } else if (k > 0) {
                // Verify left and right spots are either empty or we are at boundaries
                bool left_empty = (i == 0) || (seats[i - 1] == 0);
                bool right_empty = (i == n - 1) || (seats[i + 1] == 0);
                
                if (left_empty && right_empty) {
                    // Seat person and update target count
                    seats[i] = 1; 
                    k--;
                }
            }
        }
        
        // Return true if we successfully seated everyone needed
        return k <= 0;
    }
};

/*
*
* Dry Run
*
* Input: k = 2, seats = [0, 0, 1, 0, 0, 0, 1]
* 
* i = 0: seats[0] is 0. Left boundary is empty, right is 0. Seat placed. seats[0] becomes 1, k = 1.
* i = 1: seats[1] is 0. Left is 1 (newly seated). Cannot place here.
* i = 2: seats[2] is 1. Next seat is 0. No violation found.
* i = 3: seats[3] is 0. Left is 1. Cannot place here.
* i = 4: seats[4] is 0. Left is 0, right is 0. Seat placed. seats[4] becomes 1, k = 0.
* i = 5: seats[5] is 0. Left is 1 (newly seated). Cannot place here.
* i = 6: seats[6] is 1. Array ends.
* 
* Final check: k <= 0 is true. Return true.
*/
```

---

## 🧠 Key Insights

* **In-Place Modification:** Updating the `seats` array directly (`seats[i] = 1`) safely cascades the "occupied" status to the next iteration, automatically preventing us from placing a person right next to the one we just seated.
* **Boundary Checks:** Evaluating `(i == 0)` and `(i == n - 1)` handles the edge cases smoothly without requiring separate logic outside the main loop.
* **Early State Validation:** The problem implicitly requires evaluating if the starting array is valid (i.e., no two `1`s are next to each other to begin with). Failing this check early returns `false`.

---

## 🔗 Further Exploration

If you enjoyed this problem, you might want to try these related challenges:
* **Can Place Flowers** (LeetCode 605) - *Highly similar logic pattern.*
* **Maximize Distance to Closest Person** (LeetCode 849)

---

## 📚 References

* **Original Problem:** [GeeksforGeeks - Seating Arrangement](https://www.geeksforgeeks.org/problems/seating-arrangement--170647/1)

---

## 👨‍💻 Author

**Nilesh**
* GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`#arrays` `#greedy` `#geeksforgeeks` `#c++` `#data-structures` `#algorithms`