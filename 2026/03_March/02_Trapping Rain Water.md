# 🌊 Trapping Rain Water

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/trapping-rain-water-1587115621/1">
    <img src="https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksForGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-33.14%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-8-blue?style=for-the-badge" alt="Points" />
</div>

<br/>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array `arr[]` with non-negative integers representing the height of blocks. If the width of each block is `1`, compute how much water can be trapped between the blocks during the rainy season.

---

## 💡 Examples

### Example 1

```text
Input: arr[] = [3, 0, 1, 0, 4, 0, 2]
Output: 10
Explanation: Total water trapped = 0 + 3 + 2 + 3 + 0 + 2 + 0 = 10 units.
```

### Example 2

```text
Input: arr[] = [3, 0, 2, 0, 4]
Output: 7
Explanation: Total water trapped = 0 + 3 + 1 + 3 + 0 = 7 units.
```

### Example 3

```text
Input: arr[] = [1, 2, 3, 4]
Output: 0
Explanation: We cannot trap water as there is no height bound on both sides.
```

### Example 4

```text
Input: arr[] = [2, 1, 5, 3, 1, 0, 4]
Output: 9
Explanation: Total water trapped = 0 + 1 + 0 + 1 + 3 + 4 + 0 = 9 units.
```

<details>
<summary>📖 Example 2 Breakdown</summary>

Given `arr[] = [3, 0, 2, 0, 4]`

1. At index 0 (`3`): Cannot trap water (no left boundary). `Water = 0`
2. At index 1 (`0`): Bounded by `3` on the left and `4` on the right. Max height it can hold is `min(3, 4) = 3`. `Water = 3 - 0 = 3`
3. At index 2 (`2`): Bounded by `3` on the left and `4` on the right. Max height is `min(3, 4) = 3`. `Water = 3 - 2 = 1`
4. At index 3 (`0`): Bounded by `3` on the left and `4` on the right. Max height is `min(3, 4) = 3`. `Water = 3 - 0 = 3`
5. At index 4 (`4`): Cannot trap water (no right boundary). `Water = 0`

**Total Water** = `0 + 3 + 1 + 3 + 0 = 7` units.

</details>

---

## ⚙️ Constraints

- $1 < arr.size() < 10^5$
- $0 < arr[i] < 10^3$

**Expected Complexities:**
- **Time Complexity:** $O(n)$
- **Auxiliary Space:** $O(1)$

---

## 🏢 Company Tags
`Flipkart` `Amazon` `Microsoft` `Google` `Goldman Sachs`

---

## 💻 Solution Approach

### Prefix and Suffix Max Arrays (O(n) Space)

Here is a straightforward and intuitive approach that pre-calculates the maximum block height to the left and to the right of every block using prefix and suffix arrays. 

```cpp
// Intuition: The amount of water trapped above any block is determined by the minimum of the maximum heights to its left and right, minus its own height.
// Approach: Create two arrays to store the maximum height to the left and right of every element. Then, iterate through the array and calculate the trapped water at each block using `min(leftMax[i], rightMax[i]) - arr[i]`.
// Time Complexity: O(n) where n is the size of the array, as we iterate through the array three times.
// Space Complexity: O(n) to store the leftMax and rightMax arrays.

class Solution {
  public:
    int maxWater(vector<int> &arr) {
        int n = arr.size(); // Get the total number of blocks

        // Compute the maximum height to the left of each block
        vector<int> leftMax(n);
        leftMax[0] = arr[0];
        for(int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], arr[i]);
        }

        // Compute the maximum height to the right of each block
        vector<int> rightMax(n);
        rightMax[n - 1] = arr[n - 1];
        for(int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], arr[i]);
        }

        // Calculate the total accumulated water
        int waterTrapped = 0;
        for(int i = 0; i < n; i++) {
            // Water at current block = min(tallest left, tallest right) - current block height
            int h = min(leftMax[i], rightMax[i]) - arr[i];
            waterTrapped += h;
        }
        return waterTrapped;
    }
};

/*
*
* Dry Run
* Input: arr[] = [3, 0, 2, 0, 4]
* * 1. Initialization: n = 5
* * 2. leftMax Array Calculation:
* i = 0: leftMax[0] = 3
* i = 1: max(3, 0) = 3 -> leftMax[1] = 3
* i = 2: max(3, 2) = 3 -> leftMax[2] = 3
* i = 3: max(3, 0) = 3 -> leftMax[3] = 3
* i = 4: max(3, 4) = 4 -> leftMax[4] = 4
* leftMax = [3, 3, 3, 3, 4]
* * 3. rightMax Array Calculation:
* i = 4: rightMax[4] = 4
* i = 3: max(4, 0) = 4 -> rightMax[3] = 4
* i = 2: max(4, 2) = 4 -> rightMax[2] = 4
* i = 1: max(4, 0) = 4 -> rightMax[1] = 4
* i = 0: max(4, 3) = 4 -> rightMax[0] = 4
* rightMax = [4, 4, 4, 4, 4]
* * 4. Calculating Trapped Water:
* i = 0: min(3, 4) - 3 = 0, waterTrapped = 0
* i = 1: min(3, 4) - 0 = 3, waterTrapped = 3
* i = 2: min(3, 4) - 2 = 1, waterTrapped = 4
* i = 3: min(3, 4) - 0 = 3, waterTrapped = 7
* i = 4: min(4, 4) - 4 = 0, waterTrapped = 7
* * Output: 7
*
*/
```

---

## 🔍 Key Insights

- The core concept is that a block can hold water exactly equal to `min(max_left_height, max_right_height) - block_height`.
- **Optimization Note:** While this solution requires $O(n)$ space, it can be optimized to the expected $O(1)$ auxiliary space by utilizing the **Two Pointer** technique, calculating `leftMax` and `rightMax` dynamically on the fly from both ends of the array.

---

## 🚀 Further Exploration

- Can you write the $O(1)$ space solution using the Two Pointer approach?
- Check out **Container With Most Water** for a variation of this problem.
- Practice related problems like **Largest Rectangle in Histogram**.

---

## 🔗 References

- **GeeksforGeeks Problem:** [Trapping Rain Water](https://www.geeksforgeeks.org/problems/trapping-rain-water-1587115621/1)
- **Concept Reference:** Prefix and Suffix Arrays, Two Pointers Technique.

---

## 👤 Author

**Nilesh** GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![C++](https://img.shields.io/badge/Language-C++-blue?style=flat-square) ![Array](https://img.shields.io/badge/Topic-Array-lightgrey?style=flat-square) ![Dynamic Programming](https://img.shields.io/badge/Topic-Dynamic_Programming-orange?style=flat-square) ![Prefix Sum](https://img.shields.io/badge/Topic-Prefix_Sum-yellow?style=flat-square)