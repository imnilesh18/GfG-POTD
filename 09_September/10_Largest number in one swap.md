# 🔢 Largest number in one swap

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes.
> The solutions are provided for learning, practice, and reference only.
> The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/largest-number-in-one-swap1520/1).

<br>

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-blue.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-35.23%25-yellow.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-green.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)

</div>

---

## 📝 Problem Statement

Given a string `s` representing a number, return the **lexicographically largest** string that can be obtained by swapping at most **one pair** of characters in `s`.

---

## 📖 Examples

### Example 1

```
Input: s = "768"
Output: "867"
Explanation: Swapping the 1st and 3rd characters (7 and 8 respectively) gives the lexicographically largest string.
```

### Example 2

```
Input: s = "333"
Output: "333"
Explanation: Performing any swaps gives the same result i.e "333".
```

<details>
<summary><strong>📖 Example Breakdown (s = "768")</strong></summary>
<br>
To get the lexicographically largest string, we want the largest possible digit at the most significant position (leftmost).

1.  **Original String:** `768`
2.  **Goal:** Find a smaller digit on the left that can be swapped with a larger digit on its right.
3.  **Scan from right to left:**
    - Start at `8`. It's the largest digit seen so far.
    - Move to `6`. `6` is smaller than the largest digit seen so far (`8`). This is a potential swap candidate. We can swap `6` with `8`. Current best swap is (`6` at index 1, `8` at index 2).
    - Move to `7`. `7` is smaller than the largest digit seen so far (`8`). This is another potential swap. We can swap `7` with `8`. This is better because it places the `8` at an earlier position (index 0).
4.  **Optimal Swap:** Swap `s[0]` ('7') with `s[2]` ('8').
5.  **Result:** `867`. This is the largest possible number.
</details>

---

## 📊 Constraints

<div>

`1 ≤ |s| ≤ 10^5`
`'0' ≤ s[i] ≤ '9'`

</div>

---

## 💡 Solution Approaches

The core idea is to find the leftmost digit that is smaller than some digit to its right. To maximize the number, this leftmost digit should be swapped with the largest possible digit to its right.

### C++ Solution

```cpp
// Intuition: To make the number lexicographically largest, we should place the largest possible digit at the most significant (leftmost) position available.
// Approach: We traverse the string from right to left. We keep track of the maximum digit found so far and its index. If we find a digit that is smaller than this maximum digit, it means we have a potential swap. We record the indices of this smaller digit (l) and the maximum digit (r). Since we are iterating from the right, the last such swap we find will involve the leftmost possible digit, guaranteeing the lexicographically largest result.
// Time Complexity: O(N), where N is the length of the string, because we iterate through the string once.
// Space Complexity: O(1), as we only use a few variables to store indices and the max digit.

class Solution {
  public:
    string largestSwap(string &s) {
        char maxDigit = '0'; // Stores the maximum digit found so far from the right
        int maxIndx = -1;    // Index of the maximum digit
        int l = -1, r = -1;  // Indices for the swap (left and right)

        // Traverse from right to left to find the best swap
        for (int i = s.size() - 1; i >= 0; i--)
        {
            // If the current digit is larger than the max we've seen, update max
            if (s[i] > maxDigit)
            {
                maxDigit = s[i];
                maxIndx = i;
            }
            // If the current digit is smaller than the max found to its right
            else if (s[i] < maxDigit)
            {
                // This is a potential swap, store the indices
                l = i;       // The smaller digit's index
                r = maxIndx; // The larger digit's index
            }
        }

        // If 'l' was never updated, it means the string is already in descending order
        if (l == -1) return s;

        // Perform the optimal swap found
        swap(s[l], s[r]);

        return s;
    }
};

/*
*
* Dry Run
*
* Input: s = "768"
*
* 1. Initialize: maxDigit = '0', maxIndx = -1, l = -1, r = -1
*
* 2. Loop from right (i = 2 to 0):
* - i = 2 (s[2] = '8'):
* - '8' > '0', so update maxDigit = '8', maxIndx = 2.
*
* - i = 1 (s[1] = '6'):
* - '6' < maxDigit ('8'), so a swap is possible.
* - Update l = 1, r = 2.
*
* - i = 0 (s[0] = '7'):
* - '7' < maxDigit ('8'), so another swap is possible.
* - Update l = 0, r = 2. This is better as it affects a more significant digit.
*
* 3. Loop ends. Final values: l = 0, r = 2.
*
* 4. Since l is not -1, perform swap(s[0], s[2]).
* - s becomes "867".
*
* 5. Return "867".
*
*/
```

---

## 🚀 Key Insights

- **Right-to-Left Traversal**: By scanning from the right, we can efficiently keep track of the largest digit available for a swap for any given position `i`.
- **Greedy Choice**: For each position `i`, we check if swapping `s[i]` with the largest digit to its right (`maxDigit`) would create a larger number.
- **Leftmost Swap**: The loop naturally finds the leftmost possible position `l` for a swap that yields the maximum lexicographical result because it continues to update `l` as it moves left.

---

## 🔗 Further Exploration

- [Largest Number in K Swaps](https://www.geeksforgeeks.org/problems/largest-number-in-k-swaps-1587115620/1)
- [Next Permutation](https://www.geeksforgeeks.org/problems/next-permutation5226/1)
- [Smallest number on left](https://www.geeksforgeeks.org/problems/smallest-number-on-left3403/1)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks | Largest number in one swap](https://www.geeksforgeeks.org/problems/largest-number-in-one-swap1520/1)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div>

`Greedy` `String` `Array` `GeeksforGeeks`

</div>

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

> ⚠️ **Reminder**: This content is for educational purposes only. Always try to solve problems on your own before looking at solutions.
