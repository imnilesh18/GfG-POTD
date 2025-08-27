# 🔼 Count the number of possible triangles

<div align="center">

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/count-possible-triangles-1587115620/1).

</div>

<p align="center">
  <a href="https://www.geeksforgeeks.org/problems/count-possible-triangles-1587115620/1" target="_blank">
    <img src="https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=for-the-badge&logo=geeksforgeeks" alt="GFG Problem">
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty: Medium">
  <img src="https://img.shields.io/badge/Accuracy-28.53%25-orange?style=for-the-badge" alt="Accuracy: 28.53%">
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points: 4">
  <img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License: MIT">
</p>

---

## 📝 Problem Statement

Given an integer array `arr[]`. Find the **number** of triangles that can be formed with **three** different array elements as lengths of three sides of the triangle. A triangle with three given sides is only possible if the sum of any two sides is always **greater** than the third side.

### 📜 Examples

**Example 1:**
```
Input: arr[] = [4, 6, 3, 7]
Output: 3
Explanation: There are three triangles possible [3, 4, 6], [4, 6, 7] and [3, 6, 7].
Note that [3, 4, 7] is not a possible triangle.
```

<details>
<summary>📖 Example Breakdown</summary>

Let the sorted array be `[3, 4, 6, 7]`. A triangle can be formed by sides `a, b, c` if `a + b > c`, `a + c > b`, and `b + c > a`. If we ensure `a <= b <= c`, we only need to check `a + b > c`.

1.  **Triplet [3, 4, 6]:**
    * `a=3, b=4, c=6`
    * Check: `3 + 4 > 6` (True, 7 > 6).
    * This forms a valid triangle. ✅

2.  **Triplet [3, 4, 7]:**
    * `a=3, b=4, c=7`
    * Check: `3 + 4 > 7` (False, 7 is not greater than 7).
    * This is not a valid triangle. ❌

3.  **Triplet [3, 6, 7]:**
    * `a=3, b=6, c=7`
    * Check: `3 + 6 > 7` (True, 9 > 7).
    * This forms a valid triangle. ✅

4.  **Triplet [4, 6, 7]:**
    * `a=4, b=6, c=7`
    * Check: `4 + 6 > 7` (True, 10 > 7).
    * This forms a valid triangle. ✅

Total valid triangles: 3.
</details>

**Example 2:**
```
Input: arr[] = [10, 21, 22, 100, 101, 200, 300]
Output: 6
Explanation: There can be 6 possible triangles:
[10, 21, 22], [21, 100, 101], [22, 100, 101],
[10, 100, 101], [100, 101, 200] and [101, 200, 300].
```

**Example 3:**
```
Input: arr[] = [1, 2, 3]
Output: 0
Explanation: No triangles are possible.
```

---

## 🚨 Constraints

> `1 ≤ arr.size() ≤ 10^3`
> `0 ≤ arr[i] ≤ 10^5`

---

## 💡 Solution Approaches

### Approach 1: Brute-Force

The most straightforward way is to generate all possible triplets from the array and check if each triplet can form a triangle.

-   **Intuition:** Iterate through every combination of three elements and validate them using the triangle inequality theorem: the sum of any two sides must be greater than the third.
-   **Approach:**
    1.  Use three nested loops to select three distinct elements `arr[i]`, `arr[j]`, and `arr[k]`.
    2.  For each triplet, check if `arr[i] + arr[j] > arr[k]`, `arr[i] + arr[k] > arr[j]`, and `arr[j] + arr[k] > arr[i]`.
    3.  If all three conditions are true, increment a counter.
    4.  Return the final count.

This approach is simple but inefficient for larger inputs.

#### C++ Code

```cpp
// Intuition: Iterate through all possible triplets and check the triangle inequality.
// Approach: Use three nested loops to pick three sides. Check if the sum of any two is greater than the third.
// Time Complexity: O(N^3) - Three nested loops lead to cubic time complexity.
// Space Complexity: O(1) - No extra space is used besides a counter variable.
class Solution {
public:
    int countTriangles(vector<int>& arr) {
        int count = 0;
        int n = arr.size();
        // Iterate through all possible triplets
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    // Check triangle inequality
                    if (arr[i] + arr[j] > arr[k] &&
                        arr[i] + arr[k] > arr[j] &&
                        arr[j] + arr[k] > arr[i]) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
};

/*
*
* Dry Run
* Input: arr[] = [4, 6, 3, 7]
* 1. i=0 (4), j=1 (6), k=2 (3) -> (4,6,3) -> 4+3>6, 4+6>3, 6+3>4 -> Valid
* 2. i=0 (4), j=1 (6), k=3 (7) -> (4,6,7) -> 4+6>7, 4+7>6, 6+7>4 -> Valid
* 3. i=0 (4), j=2 (3), k=3 (7) -> (4,3,7) -> 4+3>7 (False) -> Invalid
* 4. i=1 (6), j=2 (3), k=3 (7) -> (6,3,7) -> 6+3>7, 6+7>3, 3+7>6 -> Valid
* Total Count: 3
*
*/
```

#### Java Code
```java
// Intuition: Iterate through all possible triplets and check the triangle inequality.
// Approach: Use three nested loops to pick three sides. Check if the sum of any two is greater than the third.
// Time Complexity: O(N^3) - Three nested loops lead to cubic time complexity.
// Space Complexity: O(1) - No extra space is used besides a counter variable.
class Solution {
    static int countTriangles(int arr[]) {
        int count = 0;
        int n = arr.length;
        // Iterate through all possible triplets
        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n; k++) {
                    // Check triangle inequality
                    if (arr[i] + arr[j] > arr[k] &&
                        arr[i] + arr[k] > arr[j] &&
                        arr[j] + arr[k] > arr[i]) {
                        count++;
                    }
                }
            }
        }
        return count;
    }
}

/*
*
* Dry Run
* Input: arr[] = [4, 6, 3, 7]
* 1. i=0 (4), j=1 (6), k=2 (3) -> (4,6,3) -> 4+3>6, 4+6>3, 6+3>4 -> Valid
* 2. i=0 (4), j=1 (6), k=3 (7) -> (4,6,7) -> 4+6>7, 4+7>6, 6+7>4 -> Valid
* 3. i=0 (4), j=2 (3), k=3 (7) -> (4,3,7) -> 4+3>7 (False) -> Invalid
* 4. i=1 (6), j=2 (3), k=3 (7) -> (6,3,7) -> 6+3>7, 6+7>3, 3+7>6 -> Valid
* Total Count: 3
*
*/
```

---

### Approach 2: Optimized (Sorting + Binary Search)

We can significantly improve the performance by first sorting the array. If the array is sorted, and we pick three sides `a, b, c` such that `a ≤ b ≤ c`, we only need to check one condition: `a + b > c`. The other two conditions (`a + c > b` and `b + c > a`) will always be true.

-   **Intuition:** By sorting the array, we simplify the triangle inequality check. For any two chosen sides `a` and `b`, we can efficiently find how many valid third sides `c` exist.
-   **Approach:**
    1.  Sort the input array `arr` in non-decreasing order.
    2.  Initialize a `count` variable to 0.
    3.  Iterate through the array with a loop for the first side, `arr[i]`, from `0` to `n-3`.
    4.  Inside, start another loop for the second side, `arr[j]`, from `i+1` to `n-2`.
    5.  For each pair `(arr[i], arr[j])`, find the sum `s = arr[i] + arr[j]`.
    6.  We need to find the number of elements `arr[k]` where `k > j` and `arr[k] < s`.
    7.  Use binary search to find the index of the first element that is greater than or equal to `s`. Let this index be `k`.
    8.  All elements between `j+1` and `k-1` are valid third sides. The number of such elements is `k - j - 1`.
    9.  Add this number to the total `count`.
    10. Return `count`.

#### C++ Code

```cpp
// Intuition: If we sort the array, for any two sides a and b (a <= b), we only need to find the number of sides c > b such that a + b > c. This simplifies the problem from three checks to one.
// Approach: Sort the array first. Then, fix the first two sides of the triangle using two nested loops (i and j). For each pair (arr[i], arr[j]), find their sum. Use binary search to find the count of elements greater than arr[j] but smaller than the sum.
// Time Complexity: O(N^2 * logN), where N is the number of elements. Sorting takes O(N logN), and the nested loops with binary search take O(N^2 logN).
// Space Complexity: O(1) or O(logN) depending on the sort implementation. No extra data structures are used.
class Solution {
  private:
    // Binary search to find the first index with a value >= x (upper bound)
    int binarySearch(std::vector<int>& arr, int left, int right, int x) {
        while (right >= left && right < arr.size()) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= x) {
                right = mid - 1; // Search in the left half
            } else {
                left = mid + 1; // Search in the right half
            }
        }
        return left;
    }

  public:
    // Function to count the number of possible triangles
    int countTriangles(std::vector<int>& arr) {
        int count = 0;
        int n = arr.size();
        sort(arr.begin(), arr.end()); // Sort the array
        
        // Fix the first element
        for (int i = 0; i < n - 2; i++) {
            if (arr[i] == 0) continue; // Sides cannot be zero
            int k = i + 2;
            // Fix the second element
            for (int j = i + 1; j < n - 1; j++) {
                // Find the upper bound for the third element
                int sum = arr[i] + arr[j];
                k = binarySearch(arr, k, n - 1, sum);
                // All elements from j+1 to k-1 are valid third sides
                count += k - j - 1;
            }
        }
        return count;
    }
};

/*
*
* Dry Run
* Input: arr[] = [4, 6, 3, 7]
* Sorted arr: [3, 4, 6, 7]
*
* i = 0 (arr[i] = 3):
* j = 1 (arr[j] = 4):
* sum = 3 + 4 = 7
* binarySearch for 7 in [6, 7] finds index 3 (value 7)
* count += 3 - 1 - 1 = 1. (Valid triangle: {3, 4, 6})
*
* i = 0 (arr[i] = 3):
* j = 2 (arr[j] = 6):
* sum = 3 + 6 = 9
* binarySearch for 9 in [7] finds index 4 (out of bounds)
* count += 4 - 2 - 1 = 1. Current count = 2. (Valid triangle: {3, 6, 7})
*
* i = 1 (arr[i] = 4):
* j = 2 (arr[j] = 6):
* sum = 4 + 6 = 10
* binarySearch for 10 in [7] finds index 4 (out of bounds)
* count += 4 - 2 - 1 = 1. Current count = 3. (Valid triangle: {4, 6, 7})
*
* Final count = 3
*
*/
```

#### Java Code
```java
// Intuition: If we sort the array, for any two sides a and b (a <= b), we only need to find the number of sides c > b such that a + b > c. This simplifies the problem from three checks to one.
// Approach: Sort the array first. Then, fix the first two sides of the triangle using two nested loops (i and j). For each pair (arr[i], arr[j]), find their sum. Use binary search to find the count of elements greater than arr[j] but smaller than the sum.
// Time Complexity: O(N^2 * logN), where N is the number of elements. Sorting takes O(N logN), and the nested loops with binary search take O(N^2 logN).
// Space Complexity: O(1) or O(logN) depending on the sort implementation. No extra data structures are used.
class Solution {
    // Binary search to find the first index with a value >= x (upper bound)
    private int binarySearch(int arr[], int left, int right, int x) {
        while (right >= left && right < arr.length) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= x) {
                right = mid - 1; // Search in the left half
            } else {
                left = mid + 1; // Search in the right half
            }
        }
        return left;
    }
    
    // Function to count the number of possible triangles
    public int countTriangles(int arr[]) {
        int count = 0;
        int n = arr.length;
        Arrays.sort(arr); // Sort the array
        
        // Fix the first element
        for (int i = 0; i < n - 2; i++) {
             if (arr[i] == 0) continue; // Sides cannot be zero
            int k = i + 2;
            // Fix the second element
            for (int j = i + 1; j < n - 1; j++) {
                // Find the upper bound for the third element
                int sum = arr[i] + arr[j];
                k = binarySearch(arr, k, n - 1, sum);
                // All elements from j+1 to k-1 are valid third sides
                count += k - j - 1;
            }
        }
        return count;
    }
}

/*
*
* Dry Run
* Input: arr[] = {4, 6, 3, 7}
* Sorted arr: {3, 4, 6, 7}
*
* i = 0 (arr[i] = 3):
* j = 1 (arr[j] = 4):
* sum = 3 + 4 = 7
* binarySearch for 7 in {6, 7} finds index 3 (value 7)
* count += 3 - 1 - 1 = 1. (Valid triangle: {3, 4, 6})
*
* i = 0 (arr[i] = 3):
* j = 2 (arr[j] = 6):
* sum = 3 + 6 = 9
* binarySearch for 9 in {7} finds index 4 (out of bounds)
* count += 4 - 2 - 1 = 1. Current count = 2. (Valid triangle: {3, 6, 7})
*
* i = 1 (arr[i] = 4):
* j = 2 (arr[j] = 6):
* sum = 4 + 6 = 10
* binarySearch for 10 in {7} finds index 4 (out of bounds)
* count += 4 - 2 - 1 = 1. Current count = 3. (Valid triangle: {4, 6, 7})
*
* Final count = 3
*
*/


```

---

## 🔑 Key Insights

-   **The Power of Sorting**: The core idea behind the optimized solution is that sorting the array reduces the three conditions of the triangle inequality (`a+b>c`, `a+c>b`, `b+c>a`) to just one. If we ensure `a ≤ b ≤ c`, the last two conditions are always true, so we only need to check if `a + b > c`.
-   **Efficient Counting**: After fixing two sides `a` and `b`, instead of iterating linearly to find the third side `c`, we can use binary search (or a two-pointer approach) to find the number of valid `c`'s in logarithmic or constant time, which dramatically improves the overall time complexity from O(N³) to O(N²logN) or O(N²).

---

## 🚀 Further Exploration

-   **3Sum Problem**: Find triplets in an array that sum up to a target value.
-   **Pythagorean Triplet**: Find triplets in an array that satisfy the Pythagorean theorem (`a² + b² = c²`).
-   **Count Possible Quadrilaterals**: Extend the logic to count how many valid quadrilaterals can be formed from the array elements.

---

## 📚 References

-   [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/count-possible-triangles-1587115620/1)
-   [Triangle Inequality Theorem](https://en.wikipedia.org/wiki/Triangle_inequality)

---

## 👨‍💻 Author

-   <a href="https://github.com/imnilesh18" target="_blank">`imnilesh18`</a>

---

## #️⃣ Tags

<p align="left">
  <img src="https://img.shields.io/badge/Array-2ea44f?style=for-the-badge" alt="Array">
  <img src="https://img.shields.io/badge/Sorting-2ea44f?style=for-the-badge" alt="Sorting">
  <img src="https://img.shields.io/badge/Two Pointers-2ea44f?style=for-the-badge" alt="Two Pointers">
  <img src="https://img.shields.io/badge/Binary Search-2ea44f?style=for-the-badge" alt="Binary Search">
  <img src="https://img.shields.io/badge/GeeksforGeeks-2ea44f?style=for-the-badge" alt="GeeksforGeeks">
</p>

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder**: This content is for educational purposes. It's rewarding to solve problems on your own! Use this as a guide to learn and improve.