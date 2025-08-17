# 🔢 Sort by Absolute Difference

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-27.77%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/sort-by-absolute-difference-1587115621/1).

</div>

---

## 📝 Problem Statement

You are given a number `x` and an array `arr[]`. Your task is to **rearrange** the elements of the array according to the **absolute difference** with `x`, i.e., an element having a minimum difference comes first, and so on.

**Note**: If two or more elements are at equal distances, arrange them in the same sequence as in the given array.

---

## 🧪 Examples

### Example 1

```
Input:
x = 7, arr[] = [10, 5, 3, 9, 2]

Output:
[5, 9, 10, 3, 2]

Explanation:
Sorting the numbers according to the absolute difference with 7:
- |5 - 7| = 2
- |9 - 7| = 2
- |10 - 7| = 3
- |3 - 7| = 4
- |2 - 7| = 5
The sorted array is [5, 9, 10, 3, 2]. Note that 5 and 9 have the same absolute difference, so their relative order is maintained.
```

<details>
<summary>📖 Example Breakdown (x = 7, arr[] = [10, 5, 3, 9, 2])</summary>

1.  **Target Value (x):** `7`
2.  **Input Array:** `[10, 5, 3, 9, 2]`
3.  **Calculate Absolute Differences:**
    - `|10 - 7| = 3`
    - `|5 - 7| = 2`
    - `|3 - 7| = 4`
    - `|9 - 7| = 2`
    - `|2 - 7| = 5`
4.  **Pair Elements with Differences:**
    - `(10, diff=3)`
    - `(5, diff=2)`
    - `(3, diff=4)`
    - `(9, diff=2)`
    - `(2, diff=5)`
5.  **Sort based on Differences:** We need a stable sort.
    - The smallest difference is 2. The elements with this difference are 5 and 9. Since 5 appears before 9 in the original array, their order is preserved: `5, 9`.
    - The next smallest difference is 3, which corresponds to the element `10`.
    - The next smallest is 4, corresponding to `3`.
    - The largest difference is 5, corresponding to `2`.
6.  **Final Sorted Array:** Combining these gives us `[5, 9, 10, 3, 2]`.

</details>

### Example 2

```
Input:
x = 6, arr[] = [1, 2, 3, 4, 5]

Output:
[5, 4, 3, 2, 1]

Explanation:
Sorting the numbers according to the absolute difference with 6:
- |5 - 6| = 1
- |4 - 6| = 2
- |3 - 6| = 3
- |2 - 6| = 4
- |1 - 6| = 5
The sorted array is [5, 4, 3, 2, 1].
```

---

## ⛓️ Constraints

> `1 ≤ x ≤ 10^5`
>
> `1 ≤ arr.size() ≤ 10^5`
>
> `1 ≤ arr[i] ≤ 10^5`

---

## 💡 Solution Approaches

### Optimized Approach: Custom Stable Sort

The core of the problem is to sort an array based on a custom rule: the absolute difference of each element from a given value `x`. A crucial requirement is that if two elements have the same absolute difference, their original relative order must be preserved. This points directly to using a **stable sorting algorithm**.

- **C++:** We can use `std::stable_sort` with a custom comparator (lambda function). The lambda captures `x` to use it in the comparison logic.
- **Java:** While `Arrays.sort` for primitive arrays is not guaranteed to be stable, we can convert the `int[]` to an `Integer[]` and then use `Arrays.sort`, which is a stable sort (a variation of MergeSort) for object arrays.

---

### 💻 Code Implementation

#### C++

```cpp
// Intuition: The problem requires sorting based on the absolute difference of each element from a target value 'x'.
// A key constraint is to maintain the relative order of elements with equal differences, which calls for a stable sort.
// Approach: We use the `std::stable_sort` function from the C++ STL. A custom comparator, implemented as a lambda function,
// is provided to define the sorting logic. The lambda captures 'x' to calculate `abs(a - x)` and `abs(b - x)` for any two elements 'a' and 'b'.
// Time Complexity: O(n * log n), where n is the number of elements in the array. This is the standard time complexity for `std::stable_sort`.
// Space Complexity: O(1) or O(log n) depending on the implementation of stable_sort, but typically does not require extra space proportional to n.
class Solution {
  public:
    void rearrange(vector<int> &arr, int x) {
        // Use stable_sort to maintain the relative order of elements with equal differences.
        // A lambda function is used as a custom comparator.
        stable_sort(arr.begin(), arr.end(), [x](int a, int b) {
            // Compare elements based on their absolute difference from x.
            return abs(a - x) < abs(b - x);
        });
    }
};

/*
*
* Dry Run
*
* Input: x = 7, arr[] = [10, 5, 3, 9, 2]
*
* stable_sort begins comparing elements:
*
* - Compares 10 and 5:
* - abs(10 - 7) = 3
* - abs(5 - 7) = 2
* - 2 < 3 is true, so 5 should come before 10.
*
* - Compares 10 and 9:
* - abs(10 - 7) = 3
* - abs(9 - 7) = 2
* - 2 < 3 is true, so 9 should come before 10.
*
* - Compares 5 and 9:
* - abs(5 - 7) = 2
* - abs(9 - 7) = 2
* - The condition `abs(a - x) < abs(b - x)` is false (2 < 2 is false).
* - `stable_sort` preserves the original order of 5 and 9.
*
* - Compares 3 and 2:
* - abs(3 - 7) = 4
* - abs(2 - 7) = 5
* - 4 < 5 is true, so 3 should come before 2.
*
* After all comparisons, the sorted order is based on increasing absolute differences:
* Differences:
* 5: |5-7|=2
* 9: |9-7|=2
* 10: |10-7|=3
* 3: |3-7|=4
* 2: |2-7|=5
*
* Final array: [5, 9, 10, 3, 2]
*
*/
```

#### Java

```java
// Intuition: The goal is to reorder the array based on the absolute difference of its elements from a number 'x'.
// For elements with the same difference, their original order must be preserved. This implies a stable sorting mechanism.
// Approach: The standard `Arrays.sort` for primitive types is not guaranteed to be stable.
// To ensure stability, we first convert the `int[]` array to an `Integer[]` array. Then, we use `Arrays.sort`
// with a custom comparator. For objects, `Arrays.sort` uses a stable algorithm (Timsort/MergeSort).
// The comparator calculates `Math.abs(a - x) - Math.abs(b - x)` to sort in ascending order of differences.
// Time Complexity: O(n * log n), due to the sorting algorithm.
// Space Complexity: O(n), as we create a temporary `Integer` array to hold the elements for stable sorting.
class Solution {
    public void rearrange(int[] arr, int x) {
        // Convert int[] to Integer[] to use a stable sort for objects.
        Integer[] temp = new Integer[arr.length];
        for (int i = 0; i < arr.length; i++) {
            temp[i] = arr[i];
        }

        // Sort using a custom comparator. For objects, Arrays.sort is stable.
        Arrays.sort(temp, (a, b) -> Math.abs(a - x) - Math.abs(b - x));

        // Copy the sorted elements back to the original array.
        for (int i = 0; i < arr.length; i++) {
            arr[i] = temp[i];
        }
    }
}

/*
*
* Dry Run
*
* Input: x = 7, arr[] = [10, 5, 3, 9, 2]
*
* 1. Create Integer[] temp = [10, 5, 3, 9, 2]
*
* 2. Arrays.sort(temp, comparator) begins:
* The comparator `(a, b) -> Math.abs(a - x) - Math.abs(b - x)` is used.
* A negative result means 'a' comes before 'b'.
*
* - Comparing 10 and 5:
* - Math.abs(10 - 7) - Math.abs(5 - 7) = 3 - 2 = 1 (positive, so 5 comes first)
*
* - Comparing 5 and 9:
* - Math.abs(5 - 7) - Math.abs(9 - 7) = 2 - 2 = 0 (equal, stable sort preserves original order)
*
* - Comparing 10 and 3:
* - Math.abs(10 - 7) - Math.abs(3 - 7) = 3 - 4 = -1 (negative, so 10 comes first)
*
* 3. After the stable sort, `temp` becomes: [5, 9, 10, 3, 2]
*
* 4. The elements from `temp` are copied back into `arr`.
*
* Final array: [5, 9, 10, 3, 2]
*
*/
```

---

## 🔑 Key Insights

- The most critical part of this problem is the requirement for a **stable sort**. A standard quicksort might reorder elements with equal differences, violating the problem's constraint.
- Using built-in stable sorting functions (`std::stable_sort` in C++, `Arrays.sort` on objects in Java) with a custom comparator is the most efficient and straightforward way to solve this.
- Lambda expressions provide a concise way to define the custom comparison logic directly inside the sort function call.

---

## 🚀 Further Exploration

- [Sort an array according to the order defined by another array](https://www.geeksforgeeks.org/sort-array-according-order-defined-another-array/)
- [K-Pangrams](https://www.geeksforgeeks.org/problems/k-pangrams0909/1)
- [Sort an array of 0s, 1s and 2s](https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s4231/1)

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks | Sort by Absolute Difference](https://www.geeksforgeeks.org/problems/sort-by-absolute-difference-1587115621/1)
- **C++ `stable_sort`:** [cppreference.com](https://en.cppreference.com/w/cpp/algorithm/stable_sort)
- **Java `Arrays.sort`:** [Java Documentation](https://docs.oracle.com/javase/8/docs/api/java/util/Arrays.html#sort-T:A-java.util.Comparator-)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Arrays](https://img.shields.io/badge/Arrays-E95420?style=for-the-badge&logo=cplusplus&logoColor=white)
![Sorting](https://img.shields.io/badge/Sorting-00599C?style=for-the-badge&logo=visualstudiocode&logoColor=white)
![Custom Comparator](https://img.shields.io/badge/Custom_Comparator-A8B9CC?style=for-the-badge&logo=csharp&logoColor=white)
![Lambda Functions](https://img.shields.io/badge/Lambda-FF7700?style=for-the-badge&logo=amazons3&logoColor=white)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A gentle reminder:** The solutions provided are for educational purposes. They are meant to help you understand the problem-solving process and are not for direct submission.
