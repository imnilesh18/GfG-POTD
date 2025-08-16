# Form the Largest Number 🔢

<div align="center">
  <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG Badge"/>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg" alt="Difficulty Badge"/>
  <img src="https://img.shields.io/badge/Accuracy-37.82%25-orange.svg" alt="Accuracy Badge"/>
  <img src="https://img.shields.io/badge/Points-4-blue.svg" alt="Points Badge"/>
  <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License Badge"/>
</div>

> [!WARNING] > **Educational Use Only**: This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks](https://www.geeksforgeeks.org/) problem.

---

## 📝 Problem Statement

Given an array of integers `arr[]` representing non-negative integers, arrange them so that after concatenating all of them in order, it results in the **largest** possible number. Since the result may be very large, return it as a string.

### Constraints:

- `1 ≤ arr.size() ≤ 10^5`
- `0 ≤ arr[i] ≤ 10^5`

---

## 🧪 Examples

<details>
<summary><strong>📖 Example 1 Breakdown</strong></summary>

### Input:

```
arr[] = [3, 30, 34, 5, 9]
```

### Output:

```
9534330
```

### Explanation:

To form the largest number, we need to decide the optimal order of the given numbers. Let's compare pairs of numbers by concatenating them in both possible orders:

- **Compare 9 and 5**: "95" > "59". So, 9 should come before 5.
- **Compare 5 and 34**: "534" > "345". So, 5 should come before 34.
- **Compare 34 and 3**: "343" > "334". So, 34 should come before 3.
- **Compare 3 and 30**: "330" > "303". So, 3 should come before 30.

Following this logic, the sorted arrangement that produces the largest number is `[9, 5, 34, 3, 30]`. Concatenating them gives `9534330`.

</details>

### Example 2:

```
Input: arr[] = [54, 546, 548, 60]
Output: 6054854654
```

**Explanation:** The arrangement `[60, 548, 546, 54]` gives the largest value.

### Example 3:

```
Input: arr[] = [3, 4, 6, 5, 9]
Output: 96543
```

**Explanation:** The arrangement `[9, 6, 5, 4, 3]` gives the largest value.

---

## 💡 Solution Approaches

### Optimized Approach (Custom Sort)

The core idea is to treat the numbers as strings and sort them using a custom comparison logic. Instead of comparing the numbers directly, we compare the concatenated results. For any two numbers `a` and `b`, if `b+a` is lexicographically greater than `a+b`, then `b` should come before `a` in the final arrangement. This ensures that the most significant digits contribute to making the number larger.

#### C++ Solution

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

#### Java Solution

```java
// Intuition: The problem can be solved by sorting the numbers in a custom order. The order is determined by which combination of two numbers (xy or yx) forms a larger number.
// Approach:
// 1. Convert the integer array to a list of strings.
// 2. Use a custom comparator with `Collections.sort()` to arrange the strings. The comparator checks `(s2 + s1).compareTo(s1 + s2)`.
// 3. This custom sort arranges numbers such that placing them in sequence creates the largest possible concatenated value.
// 4. Join the sorted strings to create the final result string.
// 5. Add a check for the case where the array contains only zeros to return "0".
// Time Complexity: O(N * logN), dominated by the sorting operation.
// Space Complexity: O(N), to hold the list of string numbers.

class Solution {
    // Function to return the largest concatenated number
    String findLargest(int[] arr) {

        // Convert the array of integers to a list of strings
        List<String> numbers = new ArrayList<>();
        for (int ele : arr) {
            numbers.add(String.valueOf(ele));
        }

        // Sort the list using a custom comparator
        Collections.sort(numbers, (s1, s2) -> (s2 + s1).compareTo(s1 + s2));

        // Handle the edge case where all numbers are zero
        if (numbers.get(0).equals("0")) {
            return "0";
        }

        // Concatenate the sorted strings
        StringBuilder res = new StringBuilder();
        for (String num : numbers) {
            res.append(num);
        }

        return res.toString();

    }
}

/*
*
* Dry Run
*
* Input: arr[] = [54, 546, 548, 60]
*
* 1. Convert to strings: ["54", "546", "548", "60"]
*
* 2. Custom Sort (s2+s1 vs s1+s2):
* - Compare "60" and "548": "60548" > "54860" -> order: ["60", "548", ...]
* - Compare "548" and "546": "548546" > "546548" -> order: ["60", "548", "546", ...]
* - Compare "546" and "54": "54654" > "54546" -> order: ["60", "548", "546", "54"]
*
* Sorted array: ["60", "548", "546", "54"]
*
* 3. Concatenate: "60" + "548" + "546" + "54" = "6054854654"
*
* 4. Return: "6054854654"
*
*/
```

---

## 🔑 Key Insights

- **Greedy Choice**: The custom sorting comparator makes a locally optimal choice at each step (picking the better of `ab` vs `ba`). This series of local optima leads to the global optimum because of the transitive nature of this comparison. If `a` should be before `b` and `b` before `c`, then `a` will correctly be placed before `c`.
- **String vs. Integer**: The problem cannot be solved by sorting the numbers in descending order. For example, `[3, 30]` would sort to `[30, 3]`, giving `303`, but the correct answer is `330`. Treating them as strings is essential.

---

## 🚀 Further Exploration

- [Largest Number in K swaps](https://www.geeksforgeeks.org/problems/largest-number-in-k-swaps-1587115620/1)
- [Minimum sum formed by digits](https://www.geeksforgeeks.org/problems/minimum-sum-formed-by-digits/0)
- [Sort an array according to the order defined by another array](https://www.geeksforgeeks.org/problems/relative-sorting4323/1)

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/largest-number-formed-from-an-array1117/1)
- [Custom Comparator in C++](https://www.geeksforgeeks.org/sort-c-stl/)
- [Custom Comparator in Java](https://www.geeksforgeeks.org/how-to-sort-an-arraylist-of-objects-by-property-in-java/)

---

## 🧑‍💻 Author

- **Connect with me:** [imnilesh18](https://github.com/imnilesh18)

---

## #️⃣ Tags

`#array` `#string` `#sorting` `#geeksforgeeks` `#greedy`

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

> **Note**: This is for educational purposes only. Always respect the terms of service of the platform where the problem originates.
