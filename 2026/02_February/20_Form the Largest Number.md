# 🔢 Form the Largest Number

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array1117/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array1117/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-37.82%25-green?style=for-the-badge)](https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array1117/1)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array1117/1)
[![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array of integers `arr[]` representing **non-negative** integers, arrange them so that after **concatenating** all of them in order, it results in the **largest** possible number. Since the result may be very large, return it as a string.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [3, 30, 34, 5, 9]
Output: "9534330"
Explanation: Given numbers are [3, 30, 34, 5, 9], the arrangement [9, 5, 34, 3, 30] gives the largest value.
```

### Example 2
```text
Input: arr[] = [54, 546, 548, 60]
Output: "6054854654"
Explanation: Given numbers are [54, 546, 548, 60], the arrangement [60, 548, 546, 54] gives the largest value.
```

### Example 3
```text
Input: arr[] = [3, 4, 6, 5, 9]
Output: "96543"
Explanation: Given numbers are [3, 4, 6, 5, 9], the arrangement [9, 6, 5, 4, 3] gives the largest value.
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>
<br>

1. We have numbers `[3, 30, 34, 5, 9]`.
2. Convert them to strings: `["3", "30", "34", "5", "9"]`.
3. We need a way to sort them. Standard sorting would place `"30"` before `"3"`, but `"30" + "3" = "303"`, while `"3" + "30" = "330"`. So `"3"` must come before `"30"`.
4. Using the custom rule `(s1 + s2) > (s2 + s1)`, the sorted order becomes `["9", "5", "34", "3", "30"]`.
5. Join them: `"9" + "5" + "34" + "3" + "30" = "9534330"`.

</details>

---

## ⚠️ Constraints

> - `1 <= arr.size() <= 10^5`
> - `0 <= arr[i] <= 10^5`

**Expected Complexities:**
- **Time Complexity:** $O(N \log N)$
- **Auxiliary Space:** $O(N)$

---

## 🛠️ Solution Approach

### Optimized Approach (Custom Sorting Comparator)

The optimal approach is to treat each number as a string and define a custom sorting logic. Instead of comparing two numbers purely by their lexicographical order, we compare the concatenations of two string representations.

```cpp
// Intuition: To form the largest number, we need a custom sorting rule. Comparing two numbers x and y by concatenating them (xy vs yx) determines their relative order in the final result.
// Approach:
// 1. Convert all integers in the input array to their string representations.
// 2. Define a custom comparison function that returns true if concatenating the first string with the second (`s1 + s2`) is lexicographically greater than the reverse (`s2 + s1`).
// 3. Sort the vector of strings using this custom comparator. This places elements in an order that forms the largest number when joined.
// 4. Concatenate the sorted strings to get the final result.
// 5. Handle the edge case where the input contains only zeros. If the largest number after sorting is "0", the result should be "0".
// Time Complexity: O(N * logN), where N is the number of elements in the array. The sort function dominates the complexity.
// Space Complexity: O(N), for storing the string representations of the numbers.

class Solution {
  public:
    // Custom comparator to sort strings for largest number formation
    static bool myCompare(string& s1, string& s2) {
        // Compare concatenated strings to decide order
        return (s1 + s2) > (s2 + s1);
    }

    // Function to return the largest concatenated number
    string findLargest(vector<int>& arr) {

        vector<string> numbers;
        // Convert all integers to strings
        for(int ele: arr) {
            numbers.push_back(to_string(ele));
        }

        // Sort the array using the custom comparator
        sort(numbers.begin(), numbers.end(), myCompare);

        // If the first element is "0", all numbers are zeros
        if (numbers[0] == "0") {
            return "0";
        }

        // Concatenate the sorted array to form the result
        string res = "";
        for (string& num : numbers) {
            res.append(num);
        }

        return res;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [3, 30, 34, 5, 9]
*
* 1. Convert to strings: ["3", "30", "34", "5", "9"]
*
* 2. Custom Sort:
* - Compare "9" and "5": "95" > "59" -> order: ["9", "5", ...]
* - Compare "5" and "34": "534" > "345" -> order: ["9", "5", "34", ...]
* - Compare "34" and "3": "343" > "334" -> order: ["9", "5", "34", "3", ...]
* - Compare "3" and "30": "330" > "303" -> order: ["9", "5", "34", "3", "30"]
*
* Sorted array: ["9", "5", "34", "3", "30"]
*
* 3. Concatenate: "9" + "5" + "34" + "3" + "30" = "9534330"
*
* 4. Return: "9534330"
*
*/
```

---

## 🧠 Key Insights

* **Custom Sorting Trick:** Standard lexicographical sorting breaks down when comparing subsets. E.g., `"3"` vs `"30"`. Lexicographically, `"30" > "3"`, but `"30" + "3" = "303"`, while `"3" + "30" = "330"`. Using `X+Y > Y+X` inherently checks which order generates the largest combined block.
* **Transitive Property:** If `A+B > B+A` and `B+C > C+B`, then it automatically holds that `A+C > C+A`. This mathematical property validates the use of the sorting algorithm.
* **Edge Case Handling:** We must gracefully handle inputs containing exclusively zeros (e.g., `[0, 0, 0]`). Without the check `numbers[0] == "0"`, the output would erroneously be `"000"` instead of a plain `"0"`.

---

## 🔍 Further Exploration

* Look up the equivalent problem **[LeetCode 179: Largest Number](https://leetcode.com/problems/largest-number/)** to practice on multiple platforms.
* Explore radix sort variations.

---

## 📑 References

* **GeeksforGeeks Problem:** [Form the Largest Number](https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array1117/1)
* C++ `std::sort` Reference: [cppreference](https://en.cppreference.com/w/cpp/algorithm/sort)

---

## 👨‍💻 Author

* [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`Arrays` `Data Structures` `Sorting` `Paytm` `Zoho` `Amazon` `Microsoft` `MakeMyTrip`
