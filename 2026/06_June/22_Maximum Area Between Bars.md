<div align="center">

# 🌊 Maximum Area Between Bars

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/dam-of-candies--141631/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)]()
[![Accuracy](https://img.shields.io/badge/Accuracy-39.48%25-green?style=for-the-badge)]()
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)]()
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](https://opensource.org/licenses/MIT)

> **⚠️ Educational Use Only**
> 
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the **GeeksforGeeks** platform.

</div>

---

## 📝 Problem Statement

Given an integer array `height[]`, where `height[i]` represents the height of the $i^{th}$ bar arranged in a row, find the **maximum rectangular area** that can be formed by selecting any two bars. The area is calculated based on the original positions of the selected bars, meaning the width is determined by the number of bars **between** the two selected bars.

---

## 🛑 Constraints

> - $1 \le \text{height.size()} \le 10^5$
> - $1 \le \text{height}[i] \le 10^4$

---

## 💡 Examples

### Example 1
```text
Input: height[] = [2, 5, 4, 3, 7]
Output: 10
Explanation: The maximum rectangular area is formed by selecting the bars of heights 5 and 7.
There are 2 bars between them (heights 4 and 3), so the area is: min(5, 7) × 2 = 10
```

### Example 2
```text
Input: height[] = [1, 3, 4]
Output: 1
Explanation: Selecting bars 1 and 4 gives one bar between them, so the area is: min(1, 4) × 1 = 1
```

<details>
<summary><b>📖 Example Breakdown (Walkthrough)</b></summary>
<br>

Consider `height[] = [2, 5, 4, 3, 7]`:

- Let's test `left = 1` (height `5`) and `right = 4` (height `7`).
- The width between them is `right - left - 1` = `4 - 1 - 1` = `2` bars.
- The limiting height is `min(5, 7) = 5`.
- Area = `5 * 2 = 10`. 
- No other combination yields a larger area. Using the two pointers approach helps us find this optimally without checking all $O(N^2)$ pairs.

</details>

---

## 🚀 Solution Approach

### Two Pointers Approach

We can solve this efficiently using the **Two Pointers Approach**. The maximum potential width occurs when we select the first and last bars. Since the area is bottlenecked by the shorter bar, we can only potentially increase our area by discarding the shorter bar and moving its pointer inward, hoping to find a taller bar. 

```cpp
// Intuition: We need to maximize the area between two bars, which is bottlenecked by the shorter bar. By starting with the maximum possible width and moving the pointer with the shorter bar inward, we explore the potential for a larger area with a taller bar.
// Approach: Initialize two pointers, left at the beginning and right at the end of the array. At each step, calculate the area formed by the two pointers: min(height[left], height[right]) * (right - left - 1). Update the maximum area. Then, move the pointer that points to the shorter bar towards the other pointer. Repeat until the pointers cross.
// Time Complexity: O(n) because each element is visited at most once by the two pointers moving towards each other.
// Space Complexity: O(1) as no extra space is used, only a few variables to track pointers and area.

class Solution {
  public:
    int maxArea(vector<int> &height) {
        int n = height.size();
        
        // initialize two pointers
        int left = 0;
        int right = n - 1;
        int max_area = 0;

        // traverse while pointers don't cross
        while (left < right) {
            // calculate the number of bars between left and right
            int width = right - left - 1;
            
            // area is constrained by the smaller height
            int current_area = min(height[left], height[right]) * width;
            
            // update max_area if a larger area is found
            max_area = max(max_area, current_area);

            // move the pointer with the smaller height inward
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return max_area;
    }
};

/*
*
* Dry Run
*
* Input: height[] = [2, 5, 4, 3, 7]
* left = 0, right = 4, max_area = 0
*
* Iteration 1:
* width = 4 - 0 - 1 = 3
* current_area = min(2, 7) * 3 = 2 * 3 = 6
* max_area = max(0, 6) = 6
* height[left] (2) < height[right] (7) -> left moves to 1
*
* Iteration 2:
* left = 1, right = 4
* width = 4 - 1 - 1 = 2
* current_area = min(5, 7) * 2 = 5 * 2 = 10
* max_area = max(6, 10) = 10
* height[left] (5) < height[right] (7) -> left moves to 2
*
* Iteration 3:
* left = 2, right = 4
* width = 4 - 2 - 1 = 1
* current_area = min(4, 7) * 1 = 4 * 1 = 4
* max_area remains 10
* height[left] (4) < height[right] (7) -> left moves to 3
*
* Iteration 4:
* left = 3, right = 4
* width = 4 - 3 - 1 = 0
* current_area = min(3, 7) * 0 = 0
* max_area remains 10
* height[left] (3) < height[right] (7) -> left moves to 4
*
* left = 4, right = 4. Loop terminates.
* Final max_area = 10
*
*/
```

---

## 🔑 Key Insights
- **Greedy Choice**: A wider gap provides a larger baseline area. As we close the gap (decreasing width), the only way to get a larger area is to find a significantly taller bar. Thus, it only makes sense to replace the **shorter** boundary.
- **Why it works**: By dropping the shorter bar, we eliminate sub-optimal pairs safely because pairing the current shorter bar with any inner bar would only yield a smaller width *and* a height no larger than the current shorter bar.

---

## 🔍 Further Exploration
- **Container With Most Water**: A classic LeetCode problem (LeetCode 11) that follows almost the exact same logic, except the width includes the boundary bars themselves `(j - i)`.
- **Trapping Rain Water**: Another excellent two-pointer problem focusing on boundaries, but summing up trapped units rather than finding a single maximal rectangle.

---

## 🔗 References
- **GeeksforGeeks Problem**: [Maximum Area Between Bars](https://www.geeksforgeeks.org/problems/dam-of-candies--141631/1)
- **Concepts**: Two Pointers Algorithm, Greedy Algorithms

---

## ✍️ Author
**Nilesh** [GitHub - imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#two-pointer-algorithm` `#Algorithms` `#Arrays` `#GeeksforGeeks` `#C++`