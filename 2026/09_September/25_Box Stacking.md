# 📦 Box Stacking

<div align="center">
  
  ![GeeksForGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
  ![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
  ![Accuracy](https://img.shields.io/badge/Accuracy-41.0%25-green?style=for-the-badge)
  ![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
  ![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)
  
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given three arrays `height[]`, `width[]`, and `length[]` of size `n`, where `height[i]`, `width[i]`, and `length[i]` represent the dimensions of the `i`th box, find the maximum possible height of a stack formed using these boxes[cite: 1].

**Key Rules:**
* A box can be rotated so that any of its dimensions becomes its height[cite: 1].
* A box can be placed on top of another only if both dimensions of its base are **strictly smaller** than those of the box below[cite: 1].
* Multiple instances of the same box can be used[cite: 1].

---

## 💡 Examples

### Example 1

```text
Input: height[] = [4, 1, 4, 10], width[] = [6, 2, 5, 12], length[] = [7, 3, 6, 32]
Output: 60
Explanation: The total height of this stack is 10 + 32 + 4 + 4 + 6 + 1 + 3 = 60. No other combination of boxes produces a height greater than this[cite: 1].
```

### Example 2

```text
Input: height[] = [1, 4, 3], width[] = [2, 5, 4], length[] = [3, 6, 1]
Output: 15
Explanation: The total height of this stack is 4 + 6 + 1 + 1 + 3 = 15 No other combination of boxes produces a height greater than this[cite: 1].
```

<details>
<summary>📖 Example Breakdown (Example 2)</summary>

1. We are given boxes with dimensions `(1, 2, 3)`, `(4, 5, 6)`, and `(3, 4, 1)`[cite: 1].
2. Because we can rotate them, each box gives us up to 6 different configurations (representing different choices for the base and height)[cite: 1].
3. We sort all possible configurations by base area in descending order.
4. We build the highest possible stack using a Dynamic Programming approach (similar to Longest Increasing Subsequence).
5. The optimal combination yields a total max height of 15[cite: 1].

</details>

---

## ⚠️ Constraints

> - `1 ≤ height.size(), width.size(), length.size() ≤ 100`[cite: 1]
> - `1 ≤ height[i], width[i], length[i] ≤ 10^6`[cite: 1]

---

## 🚀 Solution Approaches

### 1. Dynamic Programming (LIS Variation)

The optimal approach models this problem as a variation of the Longest Increasing Subsequence (LIS) problem. Since we can place a box on another strictly larger box, we can rotate each box into all its permutations, sort them from largest base to smallest, and then find the maximum stacking height dynamically.

```cpp
// Intuition: The problem can be reduced to a variation of the Longest Increasing Subsequence (LIS) problem. Since boxes can be rotated, each box can generate 6 different configurations. By sorting these configurations by base area in descending order, we can use Dynamic Programming to find the maximum stack height where each box strictly fits on the one below it.
// Approach: 
// 1. Generate all 6 possible orientations (combinations of length, width, height) for each box and store them.
// 2. Sort all generated boxes in descending order of their base dimensions (length and width).
// 3. Initialize a DP array where dp[i] stores the maximum stack height with box i at the base.
// 4. Iterate backwards through the sorted boxes, and for each box, check all subsequent smaller boxes to see if they can be placed on top.
// 5. Update the DP value and keep track of the overall maximum height.
// Time Complexity: O(n^2) - Generating boxes takes O(n), sorting takes O(n log n), and the nested loop DP computes in O((6n)^2) which simplifies to O(n^2)[cite: 1].
// Space Complexity: O(n) - We use an array of size 6n to store box orientations and a DP array of size 6n, which simplifies to O(n) auxiliary space[cite: 1].
class Solution {
  public:
    // Function to find the maximum height 
    // with box i as base.
    int maxHeight(vector<int>& height, vector<int>& width, vector<int>& length) {
        int n = height.size();

        // Create a 2d array to store all 
        // orientations of boxes in (l, b, h)
        // manner.
        vector<vector<int>> boxes;
        boxes.reserve(n * 6);

        for (int i = 0; i < n; i++) {
            int a = height[i], b = width[i], c = length[i];

            // Push all 6 spatial permutations of the box dimensions
            boxes.push_back({a, b, c});
            boxes.push_back({a, c, b});
            boxes.push_back({b, a, c});
            boxes.push_back({b, c, a});
            boxes.push_back({c, a, b});
            boxes.push_back({c, b, a});
        }

        // Sort the boxes in descending 
        // order of length and width.
        sort(boxes.begin(), boxes.end(), [](auto &box1, auto &box2) {
            if (box1[0] == box2[0]) {
                if (box1[1] == box2[1]) 
                    return box1[2] > box2[2];
                else 
                    return box1[1] > box2[1];
            }
            return box1[0] > box2[0];
        });

        vector<int> dp(boxes.size());
        int ans = 0;

        // Check for all boxes starting as base.
        for (int i = boxes.size() - 1; i >= 0; i--) {
            dp[i] = boxes[i][2]; // Base condition: stack with just the current box

            // Check all the boxes that can be placed above box i 
            for (int j = i + 1; j < boxes.size(); j++) {

                // If dimensions of box j are strictly less 
                // than that size of box i
                if (boxes[i][0] > boxes[j][0] &&
                    boxes[i][1] > boxes[j][1]) {
                    // Update max stack height achievable with box i
                    dp[i] = max(dp[i], boxes[i][2] + dp[j]);
                }
            }

            // Track global maximum height across all possible bases
            ans = max(ans, dp[i]);
        }

        return ans;
    }
};

/*
*
* Dry Run
* Input: height = [1], width = [2], length = [3]
* 
* 1. Orientations generated:
* (1, 2, 3), (1, 3, 2), (2, 1, 3), (2, 3, 1), (3, 1, 2), (3, 2, 1)
* 
* 2. Sorted descending by length & width:
* (3, 2, 1), (3, 1, 2), (2, 3, 1), (2, 1, 3), (1, 3, 2), (1, 2, 3)
* 
* 3. DP Execution (Iterating backwards):
* dp[5] = 3 (box 1, 2, 3)
* dp[4] = 2 (box 1, 3, 2)
* dp[3] = 3 (box 2, 1, 3) -> can place nothing smaller on top
* dp[2] = 1 (box 2, 3, 1) -> can place nothing smaller on top
* ...
* ans evaluates max values for all possibilities yielding the highest valid stack height.
* Output: 3
*
*/
```

---

## 🧠 Key Insights

* **3D to 2D Reduction:** By enforcing that any dimension can be the height, generating all 6 permutations per box eliminates the need to "rotate on the fly," reducing the problem to stacking 2D rectangles in a valid descending order.
* **Topological Sorting Substitute:** Sorting the boxes by length and width in descending order acts like a topological sort. We guarantee that box `j` can only ever be placed on top of box `i` if `j > i` in our sorted array.
* **LIS Adaptability:** The inner logic mimics the classic $O(n^2)$ LIS approach, replacing the simple sequence check `arr[i] > arr[j]` with a strict 2D dimension check `l1 > l2 && w1 > w2`.

---

## 🔍 Further Exploration

*   **Longest Increasing Subsequence (LIS):** The fundamental concept this problem is built upon.
*   **Russian Doll Envelopes (LeetCode):** A highly similar 2D variation of this 3D stacking problem.
*   **Maximum Height of a Staircase:** Another greedy/DP constraint problem.

---

## 🔗 References

*   **GeeksforGeeks Problem:** [Box Stacking](https://www.geeksforgeeks.org/problems/box-stacking/1)[cite: 1]

---

## 👤 Author

*   **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Dynamic Programming` `Box Stacking` `LIS` `GeeksforGeeks` `C++`[cite: 1]
