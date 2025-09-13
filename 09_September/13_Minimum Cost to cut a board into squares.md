# 🔪 Minimum Cost to cut a board into squares

![GFG](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-60.83%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=for-the-badge)

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/minimum-cost-to-cut-a-board-into-squares/1).

---

## Problem Statement

Given a board of dimensions **n × m** that needs to be cut into **n\*m** squares. The cost of making a cut along a horizontal or vertical edge is provided in two arrays:

- **x[]**: Cutting costs along the vertical edges (length-wise).
- **y[]**: Cutting costs along the horizontal edges (width-wise).

Find the **minimum total cost** required to cut the board into squares optimally.

---

## Examples

**Example 1:**

```text
Input:
n = 4, m = 6
x[] = [2, 1, 3, 1, 4]
y[] = [4, 1, 2]

Output: 42
Explanation:
Initially no. of horizontal segments = 1 & no. of vertical segments = 1.
Optimal way to cut into square is:
• Pick 4 (from x) -> vertical cut, Cost = 4 × 1 (horizontal segments) = 4,
  Now, horizontal segments = 1, vertical segments = 2.
• Pick 4 (from y) -> horizontal cut, Cost = 4 × 2 (vertical segments) = 8,
  Now, horizontal segments = 2, vertical segments = 2.
• Pick 3 (from x) -> vertical cut, Cost = 3 × 2 (horizontal segments) = 6,
  Now, horizontal segments = 2, vertical segments = 3.
• Pick 2 (from x) -> vertical cut, Cost = 2 × 2 (horizontal segments) = 4,
  Now, horizontal segments = 2, vertical segments = 4.
• Pick 2 (from y) -> horizontal cut, Cost = 2 × 4 (vertical segments) = 8,
  Now, horizontal segments = 3, vertical segments = 4.
• Pick 1 (from x) -> vertical cut, Cost = 1 × 3 (horizontal segments) = 3,
  Now, horizontal segments = 3, vertical segments = 5.
• Pick 1 (from x) -> vertical cut, Cost = 1 × 3 (horizontal segments) = 3,
  Now, horizontal segments = 3, vertical segments = 6.
• Pick 1 (from y) -> horizontal cut, Cost = 1 × 6 (vertical segments) = 6,
  Now, horizontal segments = 4, vertical segments = 6.
So, the total cost = 4 + 8 + 6 + 4 + 8 + 3 + 3 + 6 = 42.
```

<details>
<summary><b>📖 Example 1 Breakdown</b></summary>
<br>
This is a greedy problem. To minimize the cost, we must always perform the **most expensive cut** available (from either horizontal or vertical options) first.
<br><br>
<b>Why?</b>
<ul>
    <li>When we make a vertical cut (cost `x[i]`), the cost is multiplied by the current number of <b>horizontal segments</b> (`hCount`).</li>
    <li>When we make a horizontal cut (cost `y[j]`), the cost is multiplied by the current number of <b>vertical segments</b> (`vCount`).</li>
</ul>
By making the most expensive cut while the multiplier (the segment count from the *other* direction) is still small, we minimize its contribution to the total cost. If we wait, other cuts will increase the segment count, making that expensive cut even more costly later.
<br><br>
<b>Walkthrough:</b>
1.  All cuts sorted descending: `x=[4, 3, 2, 1, 1]`, `y=[4, 2, 1]`
2.  Initial state: `hCount = 1`, `vCount = 1`, `Cost = 0`
3.  Compare max(x) and max(y): `x=4`, `y=4`. They are equal. Let's pick the vertical cut (from `x`).
    -   Cost += `4 * hCount` = `4 * 1` = 4.
    -   New state: `hCount = 1`, `vCount = 2`, `Total Cost = 4`.
    -   Remaining cuts: `x=[3, 2, 1, 1]`, `y=[4, 2, 1]`
4.  Compare max(x) and max(y): `x=3`, `y=4`. Pick `y=4`.
    -   Cost += `4 * vCount` = `4 * 2` = 8.
    -   New state: `hCount = 2`, `vCount = 2`, `Total Cost = 12`.
    -   Remaining cuts: `x=[3, 2, 1, 1]`, `y=[2, 1]`
5.  Compare max(x) and max(y): `x=3`, `y=2`. Pick `x=3`.
    -   Cost += `3 * hCount` = `3 * 2` = 6.
    -   New state: `hCount = 2`, `vCount = 3`, `Total Cost = 18`.
    -   Remaining cuts: `x=[2, 1, 1]`, `y=[2, 1]`
6.  Compare max(x) and max(y): `x=2`, `y=2`. Pick `x=2`.
    -   Cost += `2 * hCount` = `2 * 2` = 4.
    -   New state: `hCount = 2`, `vCount = 4`, `Total Cost = 22`.
    -   Remaining cuts: `x=[1, 1]`, `y=[2, 1]`
7.  Compare max(x) and max(y): `x=1`, `y=2`. Pick `y=2`.
    -   Cost += `2 * vCount` = `2 * 4` = 8.
    -   New state: `hCount = 3`, `vCount = 4`, `Total Cost = 30`.
    -   Remaining cuts: `x=[1, 1]`, `y=[1]`
8.  Compare max(x) and max(y): `x=1`, `y=1`. Pick `x=1`.
    -   Cost += `1 * hCount` = `1 * 3` = 3.
    -   New state: `hCount = 3`, `vCount = 5`, `Total Cost = 33`.
    -   Remaining cuts: `x=[1]`, `y=[1]`
9.  Compare max(x) and max(y): `x=1`, `y=1`. Pick `x=1`.
    -   Cost += `1 * hCount` = `1 * 3` = 3.
    -   New state: `hCount = 3`, `vCount = 6`, `Total Cost = 36`.
    -   Remaining cuts: `x=[]`, `y=[1]`
10. `x` is empty. Process all remaining `y` cuts.
    -   Pick `y=1`. Cost += `1 * vCount` = `1 * 6` = 6.
    -   New state: `hCount = 4`, `vCount = 6`, `Total Cost = 42`.
11. Final cost is **42**.
</details>

**Example 2:**

```text
Input:
n = 4, m = 4
x[] = [1, 1, 1]
y[] = [1, 1, 1]

Output: 15
Explanation:
All costs are 1. The order doesn't matter as much, but the logic holds.
If we make all 3 horizontal cuts first:
Cost = 1*1 + 1*1 + 1*1 = 3 (hCount=4, vCount=1)
Then make all 3 vertical cuts:
Cost = 1*4 + 1*4 + 1*4 = 12
Total = 3 + 12 = 15.
```

---

## Constraints

```text
2 ≤ n, m ≤ 10^3
1 ≤ x[i], y[j] ≤ 10^3
```

---

## Solution Approaches

### 🚀 Optimized Greedy Approach

The core idea is to always make the most expensive cut first, regardless of whether it's horizontal or vertical. This is a **greedy strategy**.

When we make a cut, the cost of that cut is its base cost multiplied by the number of segments it cuts through.

- A **vertical cut** cuts through all current **horizontal segments**.
- A **horizontal cut** cuts through all current **vertical segments**.

Every cut we make increases the segment count for future cuts in the _other_ direction. By prioritizing the most expensive cuts, we ensure they are made when their multipliers (the segment counts) are as low as possible, thus minimizing the total cost.

The approach involves sorting both cost arrays and using a two-pointer technique to process the cuts in descending order of cost.

### C++ Solution

```cpp
// Intuition: This is a greedy problem. To minimize the total cost, we should always make the most expensive cut first.
// Why? Because every cut we make increases the number of segments the *other* direction's cuts must go through.
// A vertical cut (cost x[i]) costs `x[i] * hCount` (horizontal segments).
// A horizontal cut (cost y[j]) costs `y[j] * vCount` (vertical segments).
// By making the most expensive cut while the multiplier (segment count from the other direction) is minimal, we minimize the total cost.

// Approach:
// 1. Sort both cost arrays, x (vertical) and y (horizontal), in ascending order.
// 2. Initialize segment counts: hCount = 1 (for horizontal segments) and vCount = 1 (for vertical segments).
// 3. Use two pointers, `i` starting at the end of sorted `x` (x.size() - 1) and `j` at the end of sorted `y` (y.size() - 1). This lets us process cuts from highest cost to lowest.
// 4. Loop while both `i` and `j` are valid (>= 0).
// 5. In the loop, compare x[i] and y[j] (the two most expensive remaining cuts).
// 6. If x[i] >= y[j], make the vertical cut:
//    - Add its cost (x[i] * hCount) to totalCost.
//    - Increment vCount (a vertical cut adds one more vertical segment).
//    - Decrement `i`.
// 7. Else (y[j] > x[i]), make the horizontal cut:
//    - Add its cost (y[j] * vCount) to totalCost.
//    - Increment hCount (a horizontal cut adds one more horizontal segment).
//    - Decrement `j`.
// 8. After the main loop, one of the arrays might still have remaining cuts.
// 9. Process any remaining vertical cuts (while i >= 0), adding their cost (x[i] * hCount) to the total.
// 10. Process any remaining horizontal cuts (while j >= 0), adding their cost (y[j] * vCount) to the total.
// 11. Return the totalCost.

// Time Complexity: O(N log N + M log M), where N = x.size() and M = y.size(), dominated by the sorting. The two-pointer merge step is O(N + M).
// Space Complexity: O(1) (or O(logN + logM) for sorting recursion stack, depending on the sort implementation). No extra data structures are used.

class Solution {
  public:
    int minCost(int n, int m,
                    vector<int>& x, vector<int>& y) {

        // Sort the cutting costs in ascending order
        // We will traverse from the end to simulate picking the largest costs first
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());

        // Start with 1 horizontal segment and 1 vertical segment (the whole board)
        int hCount = 1, vCount = 1;

        // Pointers to the end of the sorted arrays (highest costs)
        int i = x.size() - 1, j = y.size() - 1;
        int totalCost = 0;

        // Loop while there are cuts available in both arrays
        while (i >= 0 && j >= 0) {

            // Choose the larger cost cut to minimize future costs.
            // This is the greedy choice.
            if (x[i] >= y[j]) {
                // Perform the vertical cut (cost x[i])
                // This cut spans all current 'hCount' horizontal segments
                totalCost += x[i] * hCount;
                vCount++; // This cut adds a new vertical segment
                i--; // Move to the next most expensive vertical cut
            }
            else {
                // Perform the horizontal cut (cost y[j])
                // This cut spans all current 'vCount' vertical segments
                totalCost += y[j] * vCount;
                hCount++; // This cut adds a new horizontal segment
                j--; // Move to the next most expensive horizontal cut
            }
        }

        // Process any remaining vertical cuts
        // This happens if we ran out of horizontal cuts first
        while (i >= 0) {
            totalCost += x[i] * hCount; // Cost uses the final horizontal segment count
            vCount++; // Not strictly needed for cost calculation, but correct
            i--;
        }

        // Process any remaining horizontal cuts
        // This happens if we ran out of vertical cuts first
        while (j >= 0) {
            totalCost += y[j] * vCount; // Cost uses the final vertical segment count
            hCount++; // Not strictly needed for cost calculation, but correct
            j--;
        }

        return totalCost; // Return the accumulated minimum cost
    }
};

/*
*
* Dry Run
* Input: n = 4, m = 6, x[] = [2, 1, 3, 1, 4], y[] = [4, 1, 2]
*
* 1. Sorted x[]: [1, 1, 2, 3, 4] (size 5)
* Sorted y[]: [1, 2, 4] (size 3)
*
* 2. Init: hCount = 1, vCount = 1, totalCost = 0
* Pointers: i = 4 (val x[4]=4), j = 2 (val y[2]=4)
*
* 3. Loop 1 (i=4, j=2):
* - x[4] (4) >= y[2] (4). True.
* - Pick vertical cut cost 4.
* - totalCost += x[4] * hCount = 4 * 1 = 4.
* - vCount becomes 2.
* - i becomes 3. (TotalCost = 4)
*
* 4. Loop 2 (i=3, j=2):
* - x[3] (3) >= y[2] (4). False.
* - Pick horizontal cut cost 4.
* - totalCost += y[2] * vCount = 4 * 2 = 8.
* - hCount becomes 2.
* - j becomes 1. (TotalCost = 4 + 8 = 12)
*
* 5. Loop 3 (i=3, j=1):
* - x[3] (3) >= y[1] (2). True.
* - Pick vertical cut cost 3.
* - totalCost += x[3] * hCount = 3 * 2 = 6.
* - vCount becomes 3.
* - i becomes 2. (TotalCost = 12 + 6 = 18)
*
* 6. Loop 4 (i=2, j=1):
* - x[2] (2) >= y[1] (2). True.
* - Pick vertical cut cost 2.
* - totalCost += x[2] * hCount = 2 * 2 = 4.
* - vCount becomes 4.
* - i becomes 1. (TotalCost = 18 + 4 = 22)
*
* 7. Loop 5 (i=1, j=1):
* - x[1] (1) >= y[1] (2). False.
* - Pick horizontal cut cost 2.
* - totalCost += y[1] * vCount = 2 * 4 = 8.
* - hCount becomes 3.
* - j becomes 0. (TotalCost = 22 + 8 = 30)
*
* 8. Loop 6 (i=1, j=0):
* - x[1] (1) >= y[0] (1). True.
* - Pick vertical cut cost 1.
* - totalCost += x[1] * hCount = 1 * 3 = 3.
* - vCount becomes 5.
* - i becomes 0. (TotalCost = 30 + 3 = 33)
*
* 9. Loop 7 (i=0, j=0):
* - x[0] (1) >= y[0] (1). True.
* - Pick vertical cut cost 1.
* - totalCost += x[0] * hCount = 1 * 3 = 3.
* - vCount becomes 6.
* - i becomes -1. (TotalCost = 33 + 3 = 36)
*
* 10. Main loop (i >= 0 && j >= 0) terminates because i = -1.
*
* 11. Remaining vertical cuts (i >= 0) loop: Skipped (i = -1).
*
* 12. Remaining horizontal cuts (j >= 0) loop:
* - j = 0.
* - totalCost += y[0] * vCount = 1 * 6 = 6.
* - hCount becomes 4.
* - j becomes -1. (TotalCost = 36 + 6 = 42)
*
* 13. Loop terminates.
*
* 14. Return totalCost: 42.
*
*/
```

---

## 💡 Key Insights

The problem has an optimal substructure and the greedy choice property. The minimum total cost is achieved by always picking the most expensive cut available (from either `x` or `y`). This ensures that the highest-cost cuts are multiplied by the smallest possible segment counts. Sorting both cost arrays allows us to efficiently compare the "next most expensive" cut from both dimensions in O(N log N + M log M) time.

---

## 🔗 References

- **Original Problem:** [https://www.geeksforgeeks.org/problems/minimum-cost-to-cut-a-board-into-squares/1](https://www.geeksforgeeks.org/problems/minimum-cost-to-cut-a-board-into-squares/1)

---

## 🧑‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`greedy` `sorting` `array` `geeksforgeeks` `medium` `potd`

---

## 📜 License

This project is licensed under the MIT License - see the LICENSE file for details.

**This is an educational repository.** The solutions are provided for learning purposes and are based on the problem statements from GeeksforGeeks.
