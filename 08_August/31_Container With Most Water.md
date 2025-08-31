# 💧 Container With Most Water

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-296236?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-53.84%25-green.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only

This repository and its content are intended solely for educational purposes. The solutions provided are for learning, practice, and reference only. The problem statement and test cases are based on the [Container With Most Water](https://www.geeksforgeeks.org/problems/container-with-most-water0535/1) problem on GeeksforGeeks.

---

## 🎯 Problem Statement

Given an array `arr[]` of non-negative integers, where each element `arr[i]` represents the height of a vertical line, find the maximum amount of water that can be contained between any two lines, together with the x-axis.

**Note:** In the case of a single vertical line, it will not be able to hold water.


---

## 🧪 Examples

Here are a few example test cases to illustrate the problem:

**Example 1:**
```
Input: arr[] = [1, 5, 4, 3]
Output: 6
Explanation: 
The lines at indices 1 and 3 (heights 5 and 3) are 2 units apart.
Height of container = min(5, 3) = 3.
Total area to hold water = 3 * 2 = 6.
```

**Example 2:**
```
Input: arr[] = [3, 1, 2, 4, 5]
Output: 12
Explanation:
The lines at indices 0 and 4 (heights 3 and 5) are 4 units apart.
Height of container = min(3, 5) = 3.
Total area to hold water = 3 * 4 = 12.
```

<details>
<summary>📖 Example 1 Breakdown</summary>

Let's walk through `arr[] = [1, 5, 4, 3]`.

1.  **Initialize**:
    * Left pointer `i = 0` (height `arr[0] = 1`).
    * Right pointer `j = 3` (height `arr[3] = 3`).
    * `maxWater = 0`.

2.  **Iteration 1**:
    * `h = min(arr[0], arr[3]) = min(1, 3) = 1`.
    * `w = j - i = 3 - 0 = 3`.
    * `area = h * w = 1 * 3 = 3`.
    * `maxWater = max(0, 3) = 3`.
    * Since `arr[i] < arr[j]`, we increment `i` to `1`.

3.  **Iteration 2**:
    * `i = 1`, `j = 3`.
    * `h = min(arr[1], arr[3]) = min(5, 3) = 3`.
    * `w = j - i = 3 - 1 = 2`.
    * `area = h * w = 3 * 2 = 6`.
    * `maxWater = max(3, 6) = 6`.
    * Since `arr[j] < arr[i]`, we decrement `j` to `2`.

4.  **Iteration 3**:
    * `i = 1`, `j = 2`.
    * `h = min(arr[1], arr[2]) = min(5, 4) = 4`.
    * `w = j - i = 2 - 1 = 1`.
    * `area = h * w = 4 * 1 = 4`.
    * `maxWater` remains `6`.
    * Since `arr[j] < arr[i]`, we decrement `j` to `1`.

5.  **End**:
    * Now `i = 1` and `j = 1`. The loop condition `i < j` is false.
    * The loop terminates.

We return `maxWater = 6`.

</details>

---

## ⛓️ Constraints

The following constraints apply to the input array `arr`:

-   `1 ≤ arr.size() ≤ 10^5`
-   `0 ≤ arr[i] ≤ 10^4`

---

## 💡 Solution Approaches

The problem can be solved efficiently using a **two-pointer approach**. A brute-force solution would involve checking every pair of lines, resulting in an O(n²) time complexity, which is too slow for the given constraints.

### Optimized Approach (Two Pointers)

The intuition is that the area of the container is limited by the shorter of the two vertical lines. To find a potentially larger area, we must increase the height component. If we move the pointer of the taller line, the width will decrease, and the height will still be limited by the shorter line, guaranteeing a smaller or equal area. Therefore, the only way to potentially increase the area is by moving the pointer of the shorter line inward.

#### C++ Solution
```cpp
// Intuition: The maximum area is limited by the shorter of the two lines. To find a larger potential area, we must try to increase the height of the container. This can only be achieved by moving the pointer of the shorter line inward.
// Approach: Use a two-pointer technique. Initialize one pointer 'i' at the beginning and another 'j' at the end of the array. In each step, calculate the area formed by the lines at i and j. Update the maximum area found so far. Then, move the pointer that points to the shorter line inward. Continue until the pointers cross.
// Time Complexity: O(N), as each pointer traverses the array only once.
// Space Complexity: O(1), as we only use a few variables to store state.
class Solution {
  public:
    int maxWater(vector<int> &arr) {
        int n = arr.size(); // Get the total number of lines.
        
        int i = 0;          // Initialize the left pointer.
        int j = n - 1;      // Initialize the right pointer.
        int maxWater = 0;   // Variable to store the maximum water found.
        
        // Loop until the two pointers meet.
        while(i < j) {
            
            // Calculate the width of the container.
            int w = j - i;
            // The height is limited by the shorter of the two lines.
            int h = min(arr[i], arr[j]);
            
            // Calculate the current area.
            int area = w * h;
            
            // Update the maximum water if the current area is larger.
            maxWater = max(maxWater, area);
            
            // Move the pointer that points to the shorter line inward.
            if (arr[i] > arr[j]) {
                j--;
            } else {
                i++;
            }
        }
        return maxWater; // Return the maximum water found.
    }
    
    /*
    *
    * Dry Run for arr[] = [1, 5, 4, 3]
    * * Initial State:
    * i = 0, j = 3, maxWater = 0
    * arr = [1, 5, 4, 3]
    *
    * Iteration 1:
    * i = 0, j = 3
    * h = min(arr[0], arr[3]) = min(1, 3) = 1
    * w = 3 - 0 = 3
    * area = 1 * 3 = 3
    * maxWater = max(0, 3) = 3
    * arr[i] < arr[j], so i becomes 1.
    *
    * Iteration 2:
    * i = 1, j = 3
    * h = min(arr[1], arr[3]) = min(5, 3) = 3
    * w = 3 - 1 = 2
    * area = 3 * 2 = 6
    * maxWater = max(3, 6) = 6
    * arr[j] < arr[i], so j becomes 2.
    *
    * Iteration 3:
    * i = 1, j = 2
    * h = min(arr[1], arr[2]) = min(5, 4) = 4
    * w = 2 - 1 = 1
    * area = 4 * 1 = 4
    * maxWater = max(6, 4) = 6
    * arr[j] < arr[i], so j becomes 1.
    *
    * End of Loop:
    * i is now 1, j is now 1. The condition i < j is false.
    * Return maxWater = 6.
    *
    */
};
```

#### Java Solution
```java
// Intuition: The maximum area is limited by the shorter of the two lines. To find a larger potential area, we must try to increase the height of the container. This can only be achieved by moving the pointer of the shorter line inward.
// Approach: Use a two-pointer technique. Initialize one pointer 'i' at the beginning and another 'j' at the end of the array. In each step, calculate the area formed by the lines at i and j. Update the maximum area found so far. Then, move the pointer that points to the shorter line inward. Continue until the pointers cross.
// Time Complexity: O(N), as each pointer traverses the array only once.
// Space Complexity: O(1), as we only use a few variables to store state.
class Solution {
    public int maxWater(int arr[]) {
        int n = arr.length; // Get the total number of lines.

        int i = 0;          // Initialize the left pointer.
        int j = n - 1;      // Initialize the right pointer.
        int maxWater = 0;   // Variable to store the maximum water found.

        // Loop until the two pointers meet.
        while (i < j) {
            
            // Calculate the width of the container.
            int w = j - i;
            // The height is limited by the shorter of the two lines.
            int h = Math.min(arr[i], arr[j]);
            
            // Calculate the current area.
            int area = w * h;
            
            // Update the maximum water if the current area is larger.
            maxWater = Math.max(maxWater, area);
            
            // Move the pointer that points to the shorter line inward.
            if (arr[i] > arr[j]) {
                j--;
            } else {
                i++;
            }
        }
        return maxWater; // Return the maximum water found.
    }
    
    /*
    *
    * Dry Run for arr[] = [1, 5, 4, 3]
    * * Initial State:
    * i = 0, j = 3, maxWater = 0
    * arr = [1, 5, 4, 3]
    *
    * Iteration 1:
    * i = 0, j = 3
    * h = min(arr[0], arr[3]) = min(1, 3) = 1
    * w = 3 - 0 = 3
    * area = 1 * 3 = 3
    * maxWater = max(0, 3) = 3
    * arr[i] < arr[j], so i becomes 1.
    *
    * Iteration 2:
    * i = 1, j = 3
    * h = min(arr[1], arr[3]) = min(5, 3) = 3
    * w = 3 - 1 = 2
    * area = 3 * 2 = 6
    * maxWater = max(3, 6) = 6
    * arr[j] < arr[i], so j becomes 2.
    *
    * Iteration 3:
    * i = 1, j = 2
    * h = min(arr[1], arr[2]) = min(5, 4) = 4
    * w = 2 - 1 = 1
    * area = 4 * 1 = 4
    * maxWater = max(6, 4) = 6
    * arr[j] < arr[i], so j becomes 1.
    *
    * End of Loop:
    * i is now 1, j is now 1. The condition i < j is false.
    * Return maxWater = 6.
    *
    */
}

```

---

## 🔑 Key Insights

-   The area of a container is always `width * min(height_left, height_right)`.
-   Starting with the maximum possible width (the two ends of the array) is a greedy approach.
-   By moving the shorter line's pointer, we explore possibilities of increasing the height, which is the only way to potentially get a larger area since the width is guaranteed to decrease.

---

## 🚀 Further Exploration

If you enjoyed this problem, consider exploring these related challenges:

-   [Trapping Rain Water](https://www.geeksforgeeks.org/trapping-rain-water/)
-   [3Sum](https://leetcode.com/problems/3sum/)
-   [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)

---

## 📚 References

-   **Original Problem:** [GeeksforGeeks - Container With Most Water](https://www.geeksforgeeks.org/problems/container-with-most-water0535/1)
-   **Two-Pointer Technique:** [GeeksforGeeks Article](https://www.geeksforgeeks.org/two-pointers-technique/)

---

## 👨‍💻 Author

-   **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Array](https://img.shields.io/badge/Array-20232A?style=for-the-badge&logo=argo&logoColor=white)
![Two Pointers](https://img.shields.io/badge/Two_Pointers-E95420?style=for-the-badge&logo=apache&logoColor=white)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-296236?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Medium](https://img.shields.io/badge/Medium-yellow?style=for-the-badge)

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder:** The solutions here are for educational purposes. It's important to understand the concepts and not just copy the code. Happy coding!