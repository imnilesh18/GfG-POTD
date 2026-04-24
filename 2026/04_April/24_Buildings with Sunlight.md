# 🌇 Buildings with Sunlight

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/buildings-receiving-sunlight3032/1"><img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" /></a>
    <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty: Easy" />
    <img src="https://img.shields.io/badge/Accuracy-40.46%25-blue?style=for-the-badge" alt="Accuracy: 40.46%" />
    <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points: 2" />
    <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License: MIT" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the GeeksforGeeks platform.

---

## 📝 Problem Statement

Given an array `arr[]` representing the heights of certain buildings that lie adjacent to each other, Sunlight starts falling from the **left side** of the buildings. If there is a building of a certain height, all the buildings to the right side of it having **lesser heights** cannot see the sun.

Find the total number of buildings that receive sunlight.

---

## 🔍 Examples

### Example 1
```text
Input: arr[] = [6, 2, 8, 4, 11, 13]
Output: 4
Explanation: Only the buildings with heights 6, 8, 11, and 13 receive sunlight; therefore, the output is 4.
```
<div align="center">
    <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/926489/Web/Other/blobid0_1776323808.png" alt="Example 1 Image" />
</div>

<details>
<summary>📖 <b>Example Breakdown</b></summary>

- **Building 1 (Height 6):** First building always gets sunlight. `Count = 1`, `Max Height = 6`.
- **Building 2 (Height 2):** Blocked by the building of height 6. `Count = 1`, `Max Height = 6`.
- **Building 3 (Height 8):** Taller than max height (6), so it gets sunlight. `Count = 2`, `Max Height = 8`.
- **Building 4 (Height 4):** Blocked by the building of height 8. `Count = 2`, `Max Height = 8`.
- **Building 5 (Height 11):** Taller than max height (8), so it gets sunlight. `Count = 3`, `Max Height = 11`.
- **Building 6 (Height 13):** Taller than max height (11), so it gets sunlight. `Count = 4`, `Max Height = 13`.

Total buildings receiving sunlight = 4.
</details>

### Example 2
```text
Input: arr[] = [2, 5, 1, 8, 3]
Output: 3
Explanation: Only buildings of height 2, 5 and 8 can see the sun, hence output is 3.
```
<div align="center">
    <img src="https://media.geeksforgeeks.org/img-practice/prod/addEditProblem/926489/Web/Other/blobid1_1776324095.png" alt="Example 2 Image" />
</div>

### Example 3
```text
Input: arr[] = [3, 3, 3, 1]
Output: 3
Explanation: The first three buildings (height 3) receive sunlight, while the last building (1) is blocked. Hence, the output is 3.
```

---

## 🚧 Constraints

- `1 ≤ arr.size() ≤ 10^5`
- `1 ≤ arr[i] ≤ 10^5`

---

## 💻 Solution Approach

### 🚀 Optimized Approach
We can iterate over the array of buildings from left to right. Since sunlight falls from the left, a building will only get sunlight if its height is greater than or equal to the maximum height of all the buildings to its left. We can maintain a running maximum and increment our answer whenever we encounter a building that matches or exceeds this maximum.

```cpp
// Intuition: Since sunlight comes from the left, a building receives sunlight only if it is strictly taller than or equal to the tallest building placed before it.
// Approach: Maintain a variable to track the maximum height seen so far. Iterate through the array; if the current building's height is greater than or equal to the running maximum, increment the count of illuminated buildings and update the running maximum.
// Time Complexity: O(n) because we traverse the array of buildings exactly once.
// Space Complexity: O(1) as we are only using a few variables to keep track of the answer and the maximum height.

class Solution {
  public:
    int visibleBuildings(vector<int>& arr) {

        // Answer is set to one as first
        // building will always get light
        int ans = 1;
        
        // It will hold the value of maximum
        // height of a building seen so far
        int maxi = arr[0];
        
        for (int i = 1; i < arr.size(); i++) {
            
            // If the current building has
            // a height greater than or equal to the maximum height so far
            if (arr[i] >= maxi) {
                
                // Increment the answer since this building can see the sun
                ans++;
                
                // Update maximum value to the current building's height
                maxi = arr[i];
            }
        }
        
        return ans;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [6, 2, 8, 4, 11, 13]
* * Initialization:
* ans = 1
* maxi = arr[0] = 6
* * Iteration:
* i = 1, arr[1] = 2. Is 2 >= 6? False.
* i = 2, arr[2] = 8. Is 8 >= 6? True. ans = 2, maxi = 8.
* i = 3, arr[3] = 4. Is 4 >= 8? False.
* i = 4, arr[4] = 11. Is 11 >= 8? True. ans = 3, maxi = 11.
* i = 5, arr[5] = 13. Is 13 >= 11? True. ans = 4, maxi = 13.
* * Final Result: ans = 4
*
*/
```

---

## 💡 Key Insights
- Tracking a "running maximum" is a classic and highly optimal technique for visibility or dominance problems parsing an array from one direction to another.
- The space complexity is highly optimized (O(1)) because we don't need to store the prefix maximums in an auxiliary array.

---

## 🔗 Further Exploration
- **Next Greater Element:** A variation where you need to find the next strictly greater element for each item.
- **Trapping Rain Water:** A popular problem evaluating bounds and boundaries on arrays of heights.

---

## 📚 References
- **Original Problem:** [GeeksforGeeks - Buildings receiving sunlight](https://www.geeksforgeeks.org/problems/buildings-receiving-sunlight3032/1)

---

## 👨‍💻 Author
Created and maintained by **[imnilesh18](https://github.com/imnilesh18)**.

## 🏷️ Tags
`Arrays` `Data Structures` `GeeksforGeeks` `C++` `Optimal`