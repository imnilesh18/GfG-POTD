# 💻 Unoccupied Computers

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/unoccupied-computers-1646661078/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-1cb15b?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-45.04%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-green?style=for-the-badge" alt="License" />
</div>

<br>

<div align="center">
  <b>⚠️ Educational Use Only</b><br>
  <i>This repository and its content are intended solely for educational purposes.<br>
  Solutions are provided for learning, practice, and reference only.<br>
  Problem statement and test cases are based on the GeeksforGeeks problem.</i>
</div>

---

## 📝 Problem Statement

A cafe has **`n`** computers. The customer events are represented by a string **`s`** of uppercase English letters, where each distinct letter appears exactly twice:
* The **first occurrence** denotes the customer's arrival.
* The **second occurrence** denotes the customer's departure.

A customer is assigned a computer only if one is available at the time of arrival, otherwise, the customer is **rejected** and does not use a computer.

Return the number of customers who could not be assigned a computer upon arrival.

---

## 💡 Examples

### Example 1
```text
Input: n = 3, s = "GACCBDDBAGEE"
Output: 1
Explanation: Only D will not be able to get any computer. So the answer is 1.

```

### Example 2

```text
Input: n = 1, s = "ABCBAC"
Output: 2
Explanation: B and C will not be able to get any computers. So the answer is 2.

```

1. **`A`** arrives (Computers in use: 0/1). `A` gets a computer.
2. **`B`** arrives (Computers in use: 1/1). `B` is rejected (Count: 1).
3. **`C`** arrives (Computers in use: 1/1). `C` is rejected (Count: 2).
4. **`B`** departs. Since `B` was rejected, no computer is freed.
5. **`A`** departs. `A` frees a computer (Computers in use: 0/1).
6. **`C`** departs. Since `C` was rejected, no computer is freed.

Total rejected = **2**.

---

## ⚠️ Constraints

> * `1 ≤ n ≤ 26`
> * `1 ≤ |s| ≤ 52`
> * `s` consists of uppercase English letters and each letter occurs exactly 2 times.
> 
> 

---

## 🚀 Solution Approach

### Optimized Simulation (Hash/State Array)

We can simulate the arrival and departure process using a fixed-size array to keep track of each unique customer's state.

```cpp
// Intuition: We need to simulate the arrival and departure of customers. By tracking each customer's state (not arrived, using computer, rejected) using an array, we can correctly manage computer allocations and rejections.
// Approach: 
// 1. Initialize a state array of size 26 for 'A'-'Z' to track customer status (0: Not arrived, 1: Using computer, 2: Rejected).
// 2. Iterate through the string `s`. For each character, check its state.
// 3. If it's the first occurrence (state == 0): If computers are available (`occupied < n`), assign one (state = 1, occupied++). Otherwise, mark as rejected (state = 2, rejected_count++).
// 4. If it's the second occurrence: If they were using a computer (state == 1), free it up (occupied--). If rejected, do nothing.
// 5. Return the total `rejected_count`.
// Time Complexity: O(|s|) where |s| is the length of string s. We iterate through the string exactly once.
// Space Complexity: O(1) as we use a fixed-size array of 26 integers.

class Solution {
  public:
    int solve(int n, string s) {
        // state array to track each customer (A-Z)
        // 0: Not arrived, 1: Using a computer, 2: Rejected
        int state[26] = {0}; 

        int occupied = 0; // Tracks currently used computers
        int rejected_count = 0; // Tracks total rejected customers

        for (char c : s) {
            int id = c - 'A'; // Map 'A'-'Z' to index 0-25

            if (state[id] == 0) {
                // Customer is arriving for the first time
                if (occupied < n) {
                    // Computer is available, assign it
                    occupied++;
                    state[id] = 1;
                } else {
                    // No computer available, reject customer
                    rejected_count++;
                    state[id] = 2;
                }
            } else {
                // Customer is departing (second occurrence)
                if (state[id] == 1) {
                    // Only free up a computer if the customer was actually using one
                    occupied--;
                }
                // If state was 2 (rejected), they just leave without freeing any computer
            }
        }

        return rejected_count;
    }
};

/*
*
* Dry Run
* Input: n = 1, s = "ABCBAC"
* 
* Initialization: state = [0]*26, occupied = 0, rejected = 0
* 
* 1. 'A' arrives: state['A']==0. occupied(0) < n(1). Assign. occupied=1, state['A']=1
* 2. 'B' arrives: state['B']==0. occupied(1) == n(1). Reject. rejected=1, state['B']=2
* 3. 'C' arrives: state['C']==0. occupied(1) == n(1). Reject. rejected=2, state['C']=2
* 4. 'B' departs: state['B']==2. Do nothing.
* 5. 'A' departs: state['A']==1. Free computer. occupied=0.
* 6. 'C' departs: state['C']==2. Do nothing.
* 
* Final rejected_count = 2
*
*/

```

---

## 🔑 Key Insights

* **Three-State Tracking**: Standard frequency arrays only tell you *how many times* a character appeared. A 3-state tracking system (0 = Not Seen, 1 = Using, 2 = Rejected) perfectly captures the logical flow of the simulation.
* **Separation of Concerns**: We only decrement the `occupied` counter if the departing customer was *actually assigned* a computer (State `1`). If they were rejected on arrival (State `2`), their departure doesn't affect the cafe's capacity.

---

## 🌍 Further Exploration

* **Related Topics**: String Processing, Hash Map, Simulation.
* **Similar Problems**:
* *Design a Parking System* (Simulation logic)
* *First Unique Character in a String* (Using frequency/state maps)



---

## 🔗 References

* **Original Problem**: [GeeksforGeeks - Unoccupied Computers](https://www.geeksforgeeks.org/problems/unoccupied-computers-1646661078/1)
* **C++ Array Initialization**: [cppreference.com](https://en.cppreference.com/w/cpp/language/aggregate_initialization)

---

## 🧑‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`#Hash` `#Simulation` `#String` `#GeeksforGeeks` `#Easy` `#CPP`