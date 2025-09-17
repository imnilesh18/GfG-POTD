# 🧩 Decode the String

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=flat&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/decode-the-string2444/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg)
![Accuracy](https://img.shields.io/badge/Accuracy-44.28%25-brightgreen.svg)
![Points](https://img.shields.io/badge/Points-4-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/decode-the-string2444/1).

---

## Problem Statement

Given an encoded string `s`, decode it by expanding the pattern `k[substring]`, where the substring inside brackets is written `k` times. `k` is guaranteed to be a positive integer, and `encodedString` contains only lowercase English alphabets.

Return the final decoded string.

**Note:** The test cases are generated so that the length of the output string will never exceed 10<sup>5</sup>.

---

## Examples

**Input:**

```
s = "3[b2[ca]]"
```

**Output:**

```
"bcacabcacabcaca"
```

**Explanation:**
Inner substring “2[ca]” breakdown into “caca”.
Now, new string becomes “3[bcaca]”
Similarly “3[bcaca]” becomes “bcacabcacabcaca” which is final result.

<br>

**Input:**

```
s = "3[ab]"
```

**Output:**

```
"ababab"
```

**Explanation:**
The substring "ab" is repeated 3 times giving "ababab".

<details>
<summary><b>📖 Example 1 Breakdown (Walkthrough)</b></summary>

Let's trace `s = "3[b2[ca]]"`:

1.  We start parsing. We see `3`. This is our multiplier `k`.
2.  We hit `[`. This means we must save the multiplier (3) and the string we've built so far (which is "") onto stacks. We reset to handle the inner content.
3.  We see `b`. We append it to our _new_ current string. `current = "b"`.
4.  We see `2`. This is a new multiplier for the _next_ level.
5.  We hit `[`. We must save our current state again.
    - Push multiplier (2) to the number stack.
    - Push the string ("b") to the string stack.
    - Reset `current` to "".
6.  We see `c`. Append it. `current = "c"`.
7.  We see `a`. Append it. `current = "ca"`.
8.  We hit `]`. This closes the _inner_ scope.
    - Pop the multiplier: `repeatTimes = 2`.
    - Pop the previous string: `decoded = "b"`.
    - Repeat the _current_ string ("ca") 2 times ("caca") and append it to the popped string ("b").
    - Update `current` = "b" + "caca" = "bcaca".
9.  We hit the final `]`. This closes the _outer_ scope.
    - Pop the multiplier: `repeatTimes = 3`.
    - Pop the previous string: `decoded = ""` (the initial empty string).
    - Repeat the _current_ string ("bcaca") 3 times.
    - Update `current` = "" + "bcacabcacabcaca".
10. We finish the loop. Final result: `bcacabcacabcaca`.

</details>

---

## 📊 Constraints

<div style="background-color: #282c34; padding: 15px; border-radius: 5px; color: #abb2bf;">
<ul>
    <li><code>1 ≤ |s| ≤ 10^5</code></li>
    <li><code>1 ≤ k ≤ 100</code></li>
</ul>
</div>

---

## 🚀 Solution Approaches

The problem has a clear nested, recursive structure, making it a perfect candidate for a **Stack-based solution**. When we encounter an opening bracket `[`, it signals the start of a new, nested "job." We need to save the state of our _current_ job (the multiplier we just saw and the string we built _before_ this bracket) and start the new one. When we hit a closing bracket `]`, the nested job is done, and we can "restore" our previous job, merging the results.

### Optimized Approach: Iterative (Two Stacks)

We use two stacks: one for numbers (`numStack`) and one for strings (`strStack`).

1.  Iterate through the string `s` character by character.
2.  If `c` is a digit: Update the current multiplier `k` (handling multi-digit numbers like "12" by using `k = k * 10 + ...`).
3.  If `c` is `[`: Push the _current_ `k` onto `numStack` and the _current_ string onto `strStack`. Reset `k = 0` and `current = ""` to start building the new nested substring.
4.  If `c` is `]`: This signifies the end of a nested segment.
    - Pop the multiplier `repeatTimes` from `numStack`.
    - Pop the `decoded` (previous) string from `strStack`.
    - Append the _current_ string to `decoded` `repeatTimes` times.
    - Set this newly formed string (`decoded`) as the _new_ `current` string.
5.  If `c` is an alphabet char: Append it to the `current` string.
6.  The final `current` string after the loop is the answer.

### C++ Solution

```cpp
// Intuition: The problem has a recursive structure (patterns within patterns). A stack is the natural data structure
// to manage this nested context iteratively, saving the state (multiplier and previous string) before starting a new sub-problem.
// Approach: Use two stacks (one for numbers and one for strings) to iteratively build the decoded string.
//   1. Iterate character by character.
//   2. If digit: Build the multiplier k (handles multiple digits like '12').
//   3. If '[': Push k onto numStack, push the 'current' string onto strStack. Reset k=0 and current="".
//   4. If ']': Pop repeat count (k) from numStack, pop previous string (prev) from strStack.
//   5.          Create the new string by appending the 'current' (nested) string to 'prev', k times. Update 'current' to this new string.
//   6. If alphabet: Append char to 'current'.
//   7. After the loop, 'current' holds the final decoded string.
// Time Complexity: O(n), where n is the length of the input string 's'. Each character is processed once (pushed/popped onto stacks in O(1) or appended).
// Space Complexity: O(n). In the worst case (e.g., "1[1[1[1[a]]]]"), the stacks store a significant portion of the input string segments.
class Solution {
public:
    string decodedString(string& s) {
      stack<int>    numStack;       // Stack to store multipliers.
      stack<string> strStack;       // Stack to store the strings built so far (the context before '[').
      string        current;        // Current substring being built (inside the most recent '[').
      int           k = 0;          // Current multiplier.

      for (char c : s) {
          if (isdigit(c)) {
              // Build the multiplier k (handles multiple digits, e.g., "12[a]").
              k = k * 10 + (c - '0');
          } else if (c == '[') {
              // Save state: Push the current multiplier and the string built *so far* onto their stacks.
              numStack.push(k);
              strStack.push(current);

              // Reset k and current for the new *nested* substring we are about to build.
              k       = 0;
              current = "";
          } else if (c == ']') {
              // End of a segment. Time to decode and merge.
              int repeatTimes = numStack.top(); // Get how many times this segment repeats.
              numStack.pop();
              string decoded = strStack.top(); // Get the string context *before* this segment started.
              strStack.pop();

              // Append the current substring (e.g., "ca") repeated repeatTimes (e.g., 2)
              // to the decoded string (e.g., "b").
              while (repeatTimes--) {
                  decoded += current;
              }
              // This fully decoded segment (e.g., "bcaca") becomes the new "current" string,
              // ready to be appended or used in the next loop iteration (which might be another ']').
              current = decoded;
          } else {
              // Regular alphabet character.
              // Append the current character to the current substring being built.
              current.push_back(c);
          }
      }
      return current; // The final string processed.
    }
};

/*
 * Dry Run:
 * Example: s = "3[b2[ca]]"
 *
 * c = '3': k = 3
 * c = '[': numStack.push(3), strStack.push(""). k=0, current=""
 * c = 'b': current = "b"
 * c = '2': k = 2
 * c = '[': numStack.push(2), strStack.push("b"). k=0, current=""
 * c = 'c': current = "c"
 * c = 'a': current = "ca"
 * c = ']':
 * - repeatTimes = numStack.pop() -> 2
 * - decoded = strStack.pop() -> "b"
 * - Repeat loop (2 times):
 * - decoded = "b" + "ca" = "bca"
 * - decoded = "bca" + "ca" = "bcaca"
 * - current = "bcaca"
 * c = ']':
 * - repeatTimes = numStack.pop() -> 3
 * - decoded = strStack.pop() -> ""
 * - Repeat loop (3 times):
 * - decoded = "" + "bcaca" = "bcaca"
 * - decoded = "bcaca" + "bcaca" = "bcacabcaca"
 * - decoded = "bcacabcaca" + "bcaca" = "bcacabcacabcaca"
 * - current = "bcacabcacabcaca"
 *
 * End of loop. Return current: "bcacabcacabcaca"
 */
```

---

## 🔑 Key Insights

The iterative stack approach perfectly mirrors the recursive nature of the problem (often called "Depth-First Search" parsing).

- Pushing onto the stacks (when hitting `[`) is equivalent to making a recursive call (saving the current state before descending).
- Popping from the stacks (when hitting `]`) is equivalent to _returning_ from a recursive call (restoring the previous state and using the returned value).
- This avoids the overhead of the system's call stack in a deep-nested recursion and gives us direct control over the state.

---

## 🏕️ Further Exploration

- [Valid Parentheses](https://www.geeksforgeeks.org/problems/parenthesis-checker2744/1) (Stack fundamental)
- [Basic Calculator](https://leetcode.com/problems/basic-calculator/) (A much harder version of stack-based expression parsing)
- [Number of Atoms](https://leetcode.com/problems/number-of-atoms/) (Similar nested parsing problem using stacks)

---

## 📚 References

- [Original GFG Problem Link](https://www.geeksforgeeks.org/problems/decode-the-string2444/1)

---

## 🧑‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Stack](https://img.shields.io/badge/Stack-blue.svg)
![String](https://img.shields.io/badge/String-green.svg)
![Recursion](https://img.shields.io/badge/Recursion-purple.svg)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-darkgreen.svg)

---

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

This repository and its content are provided for educational purposes only. The problem statement, constraints, and examples are based on the material provided by GeeksforGeeks.
