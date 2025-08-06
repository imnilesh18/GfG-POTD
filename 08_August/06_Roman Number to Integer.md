# 🏛️ Roman Number to Integer

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/roman-number-to-integer3201/1).

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-43.31%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

---

## 📜 Problem Statement

Given a string `s` in Roman number format, your task is to convert it to an integer. Various symbols and their values are given below.

**Note:** `I = 1`, `V = 5`, `X = 10`, `L = 50`, `C = 100`, `D = 500`, `M = 1000`

---

## 💡 Examples

### Example 1

```
Input: s = "IX"
Output: 9
Explanation: IX is a Roman symbol which represents 10 – 1 = 9.
```

### Example 2

```
Input: s = "XL"
Output: 40
Explanation: XL is a Roman symbol which represents 50 – 10 = 40.
```

### Example 3

```
Input: s = "MCMIV"
Output: 1904
Explanation: M is 1000, CM is 1000 – 100 = 900, and IV is 4. So we have total as 1000 + 900 + 4 = 1904.
```

<details>
<summary>📖 Example Breakdown (MCMIV)</summary>
<br>
Let's walk through the string "MCMIV" step-by-step:
<ol>
    <li><strong>M</strong>: The current character is 'M'. We look ahead, but we're at the end of this sub-problem for now. Add 1000. `result = 1000`.</li>
    <li><strong>C</strong>: The current character is 'C' (100). The next character is 'M' (1000). Since `100 < 1000`, this is a subtractive case. We calculate `1000 - 100 = 900` and add it to the result. `result = 1000 + 900 = 1900`. We skip the next character 'M'.</li>
    <li><strong>I</strong>: The current character is 'I' (1). The next character is 'V' (5). Since `1 < 5`, this is another subtractive case. We calculate `5 - 1 = 4` and add it to the result. `result = 1900 + 4 = 1904`. We skip the next character 'V'.</li>
    <li>The string is fully processed. The final integer is <strong>1904</strong>.</li>
</ol>
</details>

---

## ⛓️ Constraints

> `1 ≤ length of s ≤ 15`
>
> `s` contains only the characters `('I', 'V', 'X', 'L', 'C', 'D', 'M')`.
>
> It is guaranteed that `s` is a valid Roman numeral in the range `[1, 3999]`.

---

## ⚙️ Solution Approaches

The key to solving this problem is recognizing the subtractive rule in Roman numerals. When a smaller value symbol appears before a larger value symbol, we subtract the smaller value. Otherwise, we add the symbol's value. We can iterate through the string and apply this logic.

### C++ Solution

```cpp
// Intuition: The value of a Roman numeral is determined by adding or subtracting the values of its symbols. The core idea is that if a symbol of smaller value comes before a symbol of larger value, it's a subtraction (like IV = 4, IX = 9). Otherwise, it's an addition.
// Approach: Iterate through the string from left to right. For each symbol, check if the next symbol represents a larger value. If it does, subtract the current symbol's value from the next one, add the result to our total, and skip the next symbol. If not, simply add the current symbol's value to the total. A hash map is used for quick lookups of symbol values.
// Time Complexity: O(N), where N is the length of the Roman numeral string. We traverse the string once.
// Space Complexity: O(1), as the hash map stores a fixed number of key-value pairs (7 Roman symbols), which is constant space.
class Solution {
  public:
    int romanToDecimal(string &s) {
        // Map to store the integer values of Roman numerals
        unordered_map<char, int> romanMap = {{'I', 1},
                                             {'V', 5},
                                             {'X', 10},
                                             {'L', 50},
                                             {'C', 100},
                                             {'D', 500},
                                             {'M', 1000}};

        int result = 0; // Initialize the final integer result

        // Loop through the Roman numeral string
        for (int i = 0; i < s.length(); i++) {

            // Check for the subtractive case: current symbol's value is less than the next's
            if (i + 1 < s.length() && romanMap[s[i]] < romanMap[s[i + 1]]) {
                // Subtract current from next and add to the result (e.g., IX = 10 - 1)
                result += romanMap[s[i + 1]] - romanMap[s[i]];

                // Skip the next symbol as it has been processed
                i++;
            }

            else {

                // Additive case: just add the current symbol's value
                result += romanMap[s[i]];
            }
        }

        return result; // Return the final converted integer

    }
};

/*
*
* Dry Run
* Input: s = "MCMIV"
*
* 1. Initialize romanMap with values, result = 0.
*
* 2. i = 0, s[0] = 'M'.
* - Check: i+1 (1) < 5 and romanMap['M'] (1000) < romanMap['C'] (100) is false.
* - else block: result = 0 + 1000 = 1000.
*
* 3. i = 1, s[1] = 'C'.
* - Check: i+1 (2) < 5 and romanMap['C'] (100) < romanMap['M'] (1000) is true.
* - if block: result = 1000 + (romanMap['M'] - romanMap['C']) = 1000 + (1000 - 100) = 1900.
* - Increment i to 2.
*
* 4. i = 3, s[3] = 'I'.
* - Check: i+1 (4) < 5 and romanMap['I'] (1) < romanMap['V'] (5) is true.
* - if block: result = 1900 + (romanMap['V'] - romanMap['I']) = 1900 + (5 - 1) = 1904.
* - Increment i to 4.
*
* 5. Loop ends as i is now 5.
*
* 6. Return result: 1904.
*
*/
```

### Java Solution

```java
// Intuition: The value of a Roman numeral is determined by adding or subtracting the values of its symbols. The core idea is that if a symbol of smaller value comes before a symbol of larger value, it's a subtraction (like IV = 4, IX = 9). Otherwise, it's an addition.
// Approach: Iterate through the string from left to right. For each symbol, check if the next symbol represents a larger value. If it does, subtract the current symbol's value from the next one, add the result to our total, and skip the next symbol. If not, simply add the current symbol's value to the total. A HashMap is used for quick lookups of symbol values.
// Time Complexity: O(N), where N is the length of the Roman numeral string. We traverse the string once.
// Space Complexity: O(1), as the HashMap stores a fixed number of key-value pairs (7 Roman symbols), which is constant space.
class Solution {
    public int romanToDecimal(String s) {
        // Map to store the integer values of Roman numerals
        HashMap<Character, Integer> romanMap = new HashMap<>();
        romanMap.put('I', 1);
        romanMap.put('V', 5);
        romanMap.put('X', 10);
        romanMap.put('L', 50);
        romanMap.put('C', 100);
        romanMap.put('D', 500);
        romanMap.put('M', 1000);

        int result = 0; // Initialize the final integer result

        // Loop through the Roman numeral string
        for (int i = 0; i < s.length(); i++) {

            // Check for the subtractive case: current symbol's value is less than the next's
            if (i + 1 < s.length() && romanMap.get(s.charAt(i)) <
                                    romanMap.get(s.charAt(i + 1))) {
                // Subtract current from next and add to the result (e.g., XL = 50 - 10)
                result += romanMap.get(s.charAt(i + 1)) -
                          romanMap.get(s.charAt(i));

                // Skip the next symbol as it has been processed
                i++;
            }
            else {
                // Additive case: just add the current symbol's value
                result += romanMap.get(s.charAt(i));
            }
        }

        return result; // Return the final converted integer

    }
}

/*
*
* Dry Run
* Input: s = "MCMIV"
*
* 1. Initialize romanMap with values, result = 0.
*
* 2. i = 0, s.charAt(0) = 'M'.
* - Check: i+1 (1) < 5 and romanMap.get('M') (1000) < romanMap.get('C') (100) is false.
* - else block: result = 0 + 1000 = 1000.
*
* 3. i = 1, s.charAt(1) = 'C'.
* - Check: i+1 (2) < 5 and romanMap.get('C') (100) < romanMap.get('M') (1000) is true.
* - if block: result = 1000 + (romanMap.get('M') - romanMap.get('C')) = 1000 + (1000 - 100) = 1900.
* - Increment i to 2.
*
* 4. i = 3, s.charAt(3) = 'I'.
* - Check: i+1 (4) < 5 and romanMap.get('I') (1) < romanMap.get('V') (5) is true.
* - if block: result = 1900 + (romanMap.get('V') - romanMap.get('I')) = 1900 + (5 - 1) = 1904.
* - Increment i to 4.
*
* 5. Loop ends as i is now 5.
*
* 6. Return result: 1904.
*
*/
```

---

## 🧠 Key Insights

The optimized approach hinges on a single, elegant observation: when processing the string from left to right, a symbol's value is only ever subtracted if it is immediately followed by a symbol of a larger value.

By checking `s[i+1]`, we can decide whether to add `value(s[i])` or to add `value(s[i+1]) - value(s[i])`. This avoids complex look-behinds or multiple passes, resulting in a clean and efficient O(N) solution.

---

## 🚀 Further Exploration

- Integer to Roman: The inverse problem, where you convert an integer into its Roman numeral representation. This requires handling place values and the same subtractive rules.
- Explore other numeral systems and their conversion algorithms.

---

## 📚 References

- [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/roman-number-to-integer3201/1)
- [Roman Numerals - Wikipedia](https://en.wikipedia.org/wiki/Roman_numerals)

---

## 👨‍💻 Author

- Created by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Roman](https://img.shields.io/badge/Roman-E4AD5D?style=for-the-badge)
![String](https://img.shields.io/badge/String-5682A4?style=for-the-badge)
![HashMap](https://img.shields.io/badge/HashMap-FF7F7F?style=for-the-badge)
![Math](https://img.shields.io/badge/Math-5DADE4?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

> **Note**: This is for educational purposes only. The problem and its constraints are from GeeksforGeeks.
