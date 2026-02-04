# 🟧 Last Moment Before All Ants Fall Out

![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks)
![Accuracy](https://img.shields.io/badge/Accuracy-79.99%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)

> [!IMPORTANT]
> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/last-moment-before-all-ants-fall-out-of-a-plank/1).

---

## 📝 Problem Statement

We have a wooden plank of length `n` units. Some ants are walking on the plank, each ant moves with a speed of **1 unit per second**. Some of the ants move to the **left**, the other move to the **right**.

When two ants moving in two different directions meet at some point, they change their directions and continue moving again. Assume changing directions does not take any additional time.

When an ant reaches one end of the plank at a time `t`, it falls out of the plank immediately.

Given an integer `n` and two integer arrays `left[]` and `right[]`, the positions of the ants moving to the left and the right, return the moment when the last ant(s) fall out of the plank.

---

## 🧐 Examples

### Test Case 1

```text
Input:  n = 4, left[] = [2], right[] = [0, 1, 3]
Output: 4
Explanation: The last ant falls off the plank at t = 4.

```

<details>
<summary>📖 <strong>Example Breakdown</strong></summary>

Let's analyze the movement:

* Ants moving **left** are at position: `[2]`
* Time to fall = position `2`.


* Ants moving **right** are at positions: `[0, 1, 3]`
* Time to fall for ant at `0` = `4 - 0 = 4`.
* Time to fall for ant at `1` = `4 - 1 = 3`.
* Time to fall for ant at `3` = `4 - 3 = 1`.


* **Result:** The maximum of all these times is `4`.

</details>

### Test Case 2

```text
Input:  n = 4, left[] = [], right[] = [0, 1, 2, 3, 4]
Output: 4
Explanation: All ants are going to the right, the ant at index 0 needs 4 seconds to fall.

```

### Test Case 3

```text
Input:  n = 3, left[] = [0], right[] = [3]
Output: 0
Explanation: The ants will fall off the plank as they are already on the end of the plank.

```

---

## 🛑 Constraints

* `1 ≤ n ≤ 10^5`
* `0 ≤ left.length, right.length ≤ n + 1`
* `0 ≤ left[i], right[i] ≤ n`
* `1 ≤ left.length + right.length ≤ n + 1`
* All values of `left` and `right` are unique.

---

## 💡 Solution Approaches

### 1️⃣ Simulation / Brain Teaser (Pass-Through Logic)

#### Intuition

The problem states that ants reverse direction upon collision. Physically, if two ants are identical, an ant reversing direction is indistinguishable from two ants passing through each other without changing direction.
Therefore, we can simply calculate the time it takes for each ant to reach its respective end as if no collisions occur. The answer is simply the maximum of these times.

#### 💻 C++ Solution

```cpp
// Intuition: When ants collide, they reverse direction. This is equivalent to them passing through each other.
// Approach: Calculate the time for every ant to fall off assuming no collisions. Return the max.
// Time Complexity: O(L + R), where L and R are the number of ants moving left and right.
// Space Complexity: O(1), only a few variables used.

class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int result = 0;

        // For ants moving left, time to fall is their starting position 'p'.
        // We need the maximum of these times.
        for (int i = 0; i < left.size(); i++) {
            result = max(result, left[i]);
        }

        // For ants moving right, time to fall is 'n - p'.
        // We need the maximum of these times as well.
        for (int i = 0; i < right.size(); i++) {
            result = max(result, n - right[i]);
        }

        // The final result is the maximum time found among all ants.
        return result;
    }
};

/*
 * Dry Run
 *
 * Input: n = 4, left = [2], right = [0, 1, 3]
 *
 * 1. Ants moving left:
 * - Pos 2: takes 2s.
 * - Current max = 2.
 *
 * 2. Ants moving right:
 * - Pos 0: takes 4-0 = 4s. Max = max(2, 4) = 4.
 * - Pos 1: takes 4-1 = 3s. Max = max(4, 3) = 4.
 * - Pos 3: takes 4-3 = 1s. Max = max(4, 1) = 4.
 *
 * Result: 4
 */

```

#### ☕ Java Solution

```java
// Intuition: Treat collisions as ants passing through each other to simplify the simulation.
// Approach: Iterate through both arrays. For 'left' ants, time is pos. For 'right', time is n - pos.
// Time Complexity: O(L + R), single pass through input arrays.
// Space Complexity: O(1), constant extra space.

class Solution {
    public int getLastMoment(int n, int left[], int right[]) {
        int maxTime = 0;

        // For ants moving left, time to fall is their position.
        // Find the maximum time among them.
        for (int pos : left) {
            maxTime = Math.max(maxTime, pos);
        }

        // For ants moving right, time to fall is (n - position).
        // Find the maximum time among them and update the overall max.
        for (int pos : right) {
            maxTime = Math.max(maxTime, n - pos);
        }

        // The result is the maximum time required by any single ant.
        return maxTime;
    }
}

/*
 * Dry Run
 *
 * Input: n = 4, left = {2}, right = {0, 1, 3}
 *
 * 1. Init maxTime = 0
 * 2. Left array: {2} -> time=2. maxTime=2.
 * 3. Right array:
 * - {0} -> time=4. maxTime=4.
 * - {1} -> time=3. maxTime=4.
 * - {3} -> time=1. maxTime=4.
 *
 * Return 4.
 */

```

---

## 🗝️ Key Insights

* **Identity Swap:** When two identical particles collide and reverse, the system behaves exactly as if they passed through each other. This transforms a complex simulation problem into a simple mathematical one.
* **Max Distance:** The problem reduces to finding the ant that is furthest from its destination end.
* Max time for `left` ants = `max(left[i])`
* Max time for `right` ants = `max(n - right[i])`
* Total Max = `max(max_left, max_right)`



---

## 🚀 Further Exploration

* **Collision Counting:** Can you modify the logic to count how many collisions actually occurred?
* **Weighted Ants:** What if the ants had different weights or speeds?
* **Similar Problems:**
* [LeetCode 1503. Last Moment Before All Ants Fall Out of a Plank](https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/)
* Asteroid Collision problems often use stacks but involve similar directional logic.



---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/last-moment-before-all-ants-fall-out-of-a-plank/1)

---

## 🧑‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

> [!NOTE]
> This project is purely for educational and practice purposes.