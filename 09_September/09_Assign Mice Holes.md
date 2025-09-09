# 🐭 Assign Mice Holes

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-55.93%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-purple?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/assign-mice-holes3053/1).

---

## Problem Statement

You are given two arrays **mices[]** and **holes[]** of the same size. The array **mices[]** represents the positions of the mice on a straight line, while the array **holes[]** represents the positions of the holes on the same line. Each hole can accommodate exactly one mouse. A mouse can either stay in its current position, move one step to the right, or move one step to the left, and each move takes **one** minute. The task is to assign each mouse to a distinct hole in such a way that the time taken by the last mouse to reach its hole is **minimized**.

---

## Examples

### Example 1:

```
Input: mices[] = [4, -4, 2], holes[] = [4, 0, 5]
Output: 4
Explanation:
Assign the mouse at position 4 to the hole at position 4 (time = 0).
Assign the mouse at position -4 to the hole at position 0 (time = 4).
Assign the mouse at position 2 to the hole at position 5 (time = 3).
Hence, the maximum time required by any mouse is 4 minutes.
```

<details>
<summary>📖 Example Breakdown (Example 1)</summary>
<br>
Let's analyze this. We want to minimize the *maximum time* any single mouse takes. This suggests we need to find an optimal pairing.

- **Mice Positions:** `[4, -4, 2]`
- **Hole Positions:** `[4, 0, 5]`

Consider an alternative assignment:

- Mouse at 4 -> Hole at 0 (Time = 4)
- Mouse at -4 -> Hole at 5 (Time = 9)
- Mouse at 2 -> Hole at 4 (Time = 2)
  The maximum time here is **9**, which is worse than the optimal answer of 4.

The key insight is that if we sort both arrays, the optimal pairing is to match the i-th mouse with the i-th hole.

- **Sorted Mice:** `[-4, 2, 4]`
- **Sorted Holes:** `[0, 4, 5]`

Now, let's pair them by their sorted index:

1.  **Pair 1 (i=0):** Mouse at `-4` goes to Hole at `0`. Time = `abs(-4 - 0)` = **4**
2.  **Pair 2 (i=1):** Mouse at `2` goes to Hole at `4`. Time = `abs(2 - 4)` = **2**
3.  **Pair 3 (i=2):** Mouse at `4` goes to Hole at `5`. Time = `abs(4 - 5)` = **1**

The times taken are [4, 2, 1]. The maximum of these values is **4**. This greedy strategy gives us the minimal possible maximum time.

</details>

### Example 2:

```
Input: mices[] = [1, 2], holes[] = [20, 10]
Output: 18
Explanation:
Assign the mouse at position 1 to the hole at position 10 (time = 9).
Assign the mouse at position 2 to the hole at position 20 (time = 18).
Hence, the maximum time required by any mouse is 18 minutes.
```

---

## 📏 Constraints

<div style="background-color: #282c34; padding: 15px; border-radius: 5px; color: #abb2bf;">
<ul>
  <li><code>1 ≤ mices.size() = holes.size() ≤ 10^5</code></li>
  <li><code>-10^5 ≤ mices[i] , holes[i] ≤ 10^5</code></li>
</ul>
</div>

---

## Solution Approaches

### 🚀 Optimized Greedy Approach (Sorting)

The intuition is that to minimize the maximum travel time, we must prevent any "cross-overs." This means the mouse at the leftmost position (after sorting) should go to the hole at the leftmost position (after sorting), the second-leftmost mouse to the second-leftmost hole, and so on.

If we pair the i-th mouse (in sorted order) with the i-th hole (in sorted order), we guarantee that no mouse has to make an unnecessarily long journey just because a closer hole was taken by a mouse that was farther away. The bottleneck (maximum time) is minimized by this strategy.

#### C++ Solution

```cpp
// Intuition: To minimize the max time, we must pair mice and holes such that their relative order is preserved.
// Pairing the i-th smallest mouse with the i-th smallest hole is the optimal strategy.
// Any other pairing would necessarily lead to a larger or equal maximum distance for at least one mouse.
//
// Approach:
// 1. Sort the `mices` array to order mice positions.
// 2. Sort the `holes` array to order hole positions.
// 3. Initialize `maxDiff = 0` to store the maximum time taken.
// 4. Iterate from i = 0 to n-1 (where n is the number of mice/holes).
// 5. In each iteration, calculate the time for the i-th pair: `diff = abs(mices[i] - holes[i])`.
// 6. Update `maxDiff` with the maximum difference found so far: `maxDiff = max(maxDiff, diff)`.
// 7. After the loop, `maxDiff` will hold the time taken by the last mouse in the optimal assignment, which is our answer.
//
// Time Complexity: O(N log N), dominated by the two sorting operations. The final loop is O(N).
// Space Complexity: O(1) (or O(log N) for the sort recursion stack), as we modify arrays in-place.

class Solution {
  public:
    int assignHole(vector<int>& mices, vector<int>& holes) {
        int n = mices.size(); // Get the number of mice (which equals number of holes)

        // Sort both arrays to apply the greedy strategy
        sort(mices.begin(), mices.end());
        sort(holes.begin(), holes.end());

        // Finding max difference between
        // ith mice and hole
        int max = 0; // Initialize the maximum time (our answer) to 0

        // Iterate through each mouse-hole pair in their sorted order
        for(int i = 0; i < n; ++i)
        {
            // Calculate the time taken for the current pair
            int diff = abs(mices[i] - holes[i]);

            // If this pair's time is the largest we've seen, update the max
            if (max < diff)
                max = diff;
        }

        // Return the overall maximum time, which is the minimal time possible for the last mouse.
        return max;
    }
};

/*
*
* Dry Run
* * Input: mices[] = [4, -4, 2], holes[] = [4, 0, 5]
* n = 3
* * 1. Sort mices: [-4, 2, 4]
* 2. Sort holes: [0, 4, 5]
* 3. Initialize max = 0
* * 4. Loop:
* i = 0:
* diff = abs(mices[0] - holes[0]) = abs(-4 - 0) = 4
* Is max (0) < diff (4)? Yes.
* Set max = 4
* * i = 1:
* diff = abs(mices[1] - holes[1]) = abs(2 - 4) = 2
* Is max (4) < diff (2)? No.
* max remains 4
* * i = 2:
* diff = abs(mices[2] - holes[2]) = abs(4 - 5) = 1
* Is max (4) < diff (1)? No.
* max remains 4
* * 5. Loop finishes.
* 6. Return max (4).
*
*/
```

---

## 💡 Key Insights

This problem is a classic example of a **greedy algorithm**. The core proof of why this works is based on the idea that any "cross-pairing" (where the i-th mouse is not paired with the i-th hole) is suboptimal or equivalent.

Assume you have a sorted configuration and you pair mouse `i` with hole `j` and mouse `j` with hole `i` (where `i < j`). The positions must be `m_i <= m_j` and `h_i <= h_j`. The maximum time in this swap would be `max(abs(m_i - h_j), abs(m_j - h_i))`. This maximum is always greater than or equal to the non-crossed pairing's maximum of `max(abs(m_i - h_i), abs(m_j - h_j))`. Therefore, the greedy strategy of matching by sorted index never produces a worse result and is proven to be optimal.

---

## 🧭 Further Exploration

- [Activity Selection Problem (GFG)](https://www.geeksforgeeks.org/problems/activity-selection-1587115620/1)
- [N meetings in one room (GFG)](https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1)
- [Minimum Platforms (GFG)](https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1)
- [Job Sequencing Problem (GFG)](https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1)

---

## 🔗 References

- [Original GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/assign-mice-holes3053/1)

---

## 👨‍💻 Author

- [![GitHub](https://img.shields.io/badge/GitHub-imnilesh18-blue?style=for-the-badge&logo=github)](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Greedy](https://img.shields.io/badge/Greedy-Algorithm-orange?style=for-the-badge)
![Sorting](https://img.shields.io/badge/Sorting-blueviolet?style=for-the-badge)
![Arrays](https://img.shields.io/badge/Arrays-gray?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)

---

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

This repository is for educational purposes only. All problem statements, examples, and constraints are the property of GeeksforGeeks.
