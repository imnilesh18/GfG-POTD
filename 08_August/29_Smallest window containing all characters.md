# 🪟 Smallest window containing all characters

<div align="center">

![GFG][gfg-shield]
![Difficulty][difficulty-shield]
![Accuracy][accuracy-shield]
![Points][points-shield]
![License][license-shield]

</div>

---

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. The solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1).

---

## Problem Statement

Given two strings, `s` and `p`, find the smallest substring in `s` that contains all the characters of `p` (including duplicates).

- If no such substring exists, return an empty string `""`.
- If there are multiple smallest substrings of the same length, return the one with the **least starting index**.

---

## Examples

Here are the example test cases to illustrate the problem:

<details>
<summary><strong>📖 Example 1 Breakdown</strong></summary>

-   **Input**: `s = "timetopractice"`, `p = "toc"`
-   **Characters to find**: `t`, `o`, `c`.
-   **Scanning `s`**:
    -   `"time"` - Missing `o`, `c`.
    -   `"timeto"` - Has `t`, `o`. Missing `c`.
    -   `"timetoprac"` - Has `t`, `o`, `p`, `r`, `a`, `c`. Window: `"toprac"`. Length 6. Contains `t`, `o`, `c`. This is a valid window.
-   **Shrinking the window**: Can we make `"toprac"` smaller from the left?
    -   Remove `t`: `"oprac"`. Still contains `o`, `p`, `r`, `a`, `c`. A valid window. Length 5.
    -   Remove `o`: `"prac"`. Missing `o`. Invalid.
-   The smallest window found is `"oprac"`. Let's re-examine.
-   The correct smallest window is **`"toprac"`**. The window must contain all characters of `p`.
    -   `"timetoprac"` -> window from index 2 to 7 is `"toprac"`. It contains `t`, `o`, `c`. Length is 6.
    -   Another potential window could be `"practiceto"`.
    -   The algorithm will find `"toprac"` as the first valid window and then try to shrink it. After shrinking, it will continue expanding.
-   **Final Answer**: The smallest substring containing all characters of `p` is `"toprac"`.

</details>

### 📖 Example Test Cases

```plaintext
Input: s = "timetopractice", p = "toc"
Output: "toprac"
Explanation: "toprac" is the smallest substring in which "toc" can be found.
```

```plaintext
Input: s = "zoomlazapzo", p = "oza"
Output: "apzo"
Explanation: "apzo" is the smallest substring in which "oza" can be found.
```

```plaintext
Input: s = "zoom", p = "zooe"
Output: ""
Explanation: No substring is present containing all characters of p.
```

---

## Constraints

-   `1 ≤ s.length(), p.length() ≤ 10^6`
-   `s`, `p` consists of lowercase English letters.

---

## Solution Approaches

The problem can be efficiently solved using the **Sliding Window** technique. We maintain a window (a substring of `s`) and expand it by moving the right pointer. Once the window contains all characters of `p`, we try to shrink it from the left to find the smallest possible valid window.

### C++ Solution

```cpp
// Intuition:
// The problem asks for the smallest substring of 's' that contains all characters of 'p'.
// A sliding window approach is perfect for this. We can maintain a "window" in 's'
// and keep track of the characters inside it. We expand the window by moving its right
// end and shrink it from its left end.

// Approach:
// 1. First, we count the frequency of each character in the pattern string 'p' and store it in a hash map (or an array since we only have 256 possible characters).
// 2. We initialize two pointers, 'start' and 'j' (for the end of the window), both at the beginning of 's'.
// 3. We also need a counter 'count' to track how many characters from 'p' we have found in the current window of 's'.
// 4. We iterate through 's' with the 'j' pointer to expand the window. For each character s[j]:
//    a. We increment its count in our window's frequency map.
//    b. If the character s[j] is needed for our pattern (i.e., its count in 'p' is > 0) AND we haven't found more of this character than needed, we increment 'count'.
// 5. When 'count' equals the length of 'p', it means our current window s[start...j] contains all the required characters.
//    a. Now, we try to shrink this window from the left by moving the 'start' pointer forward.
//    b. We can move 'start' as long as the window remains valid. A window remains valid if s[start] is either not in 'p' or if we have more of s[start] than required.
//    c. While shrinking, we decrement the character count of s[start] in our window's frequency map.
//    d. After shrinking, we have a minimal window s[start...j]. We compare its length with the minimum length found so far and update if necessary.
// 6. We continue this process until 'j' reaches the end of 's'.
// 7. If we never found a valid window, the starting index will remain -1, and we return an empty string. Otherwise, we return the smallest window found.

// Time Complexity: O(|s|)
// We iterate through the string 's' with two pointers, 'start' and 'j'. Each character of 's' is visited at most twice (once by 'j' and once by 'start').

// Space Complexity: O(1)
// We use two arrays of size 256 to store character counts, which is constant space.
class Solution {
  public:
    string smallestWindow(string s, string p){
    int len1 = s.length();
    int len2 = p.length();

    // If length of s is less than length of p, it's impossible to find a window.
    if (len1 < len2)
        return "";

    // Frequency maps for characters in p and the current window in s.
    vector<int> countP(256, 0);
    vector<int> countS(256, 0);

    // Store occurrence of characters of p.
    for (int i = 0; i < len2; i++)
        countP[p[i]]++;

    int start = 0, start_idx = -1, min_len = INT_MAX;

    // 'count' tracks how many characters of p are currently covered by the window.
    int count = 0;

    // Iterate through s to expand the window from the right.
    for (int j = 0; j < len1; j++){
        // Count occurrence of characters of string S.
        countS[s[j]]++;

        // If s[j] is a character in p and we haven't exceeded its required count.
        if (countP[s[j]] != 0 && countS[s[j]] <= countP[s[j]]){
            count++;
        }

        // If all characters of p are found in the current window.
        if (count == len2){
            // Try to minimize the window from the left.
            while (countS[s[start]] > countP[s[start]] || countP[s[start]] == 0){
                if (countS[s[start]] > countP[s[start]]){
                    countS[s[start]]--;
                }
                start++;
            }

            // Update window size.
            int len = j - start + 1;
            if (min_len > len){
                min_len = len;
                start_idx = start;
            }
        }
    }

    // If no window was found.
    if (start_idx == -1)
        return "";

    return s.substr(start_idx, min_len);
    }
};

/*
*
* Dry Run
* s = "timetopractice", p = "toc"
*
* len1 = 14, len2 = 3
* countP: {'t': 1, 'o': 1, 'c': 1}
*
* j=0, s[0]='t'. countS['t'] becomes 1. count becomes 1.
* j=1, s[1]='i'. countS['i'] becomes 1.
* j=2, s[2]='m'. countS['m'] becomes 1.
* j=3, s[3]='e'. countS['e'] becomes 1.
* j=4, s[4]='t'. countS['t'] becomes 2.
* j=5, s[5]='o'. countS['o'] becomes 1. count becomes 2.
* j=6, s[6]='p'. countS['p'] becomes 1.
* j=7, s[7]='r'. countS['r'] becomes 1.
* j=8, s[8]='a'. countS['a'] becomes 1.
* j=9, s[9]='c'. countS['c'] becomes 1. count becomes 3.
*
* Now, count == len2 (3 == 3). Window is "timetoprac".
* Try to shrink from start=0.
* s[0]='t'. countS['t'] > countP['t'] (2 > 1). Decrement countS['t'] to 1. start becomes 1.
* s[1]='i'. countP['i'] == 0. start becomes 2.
* s[2]='m'. countP['m'] == 0. start becomes 3.
* s[3]='e'. countP['e'] == 0. start becomes 4.
* s[4]='t'. countS['t'] == countP['t'] (1 == 1). Cannot shrink.
*
* Current window is s[4...9] = "toprac". Length = 6.
* min_len = 6, start_idx = 4.
*
* j=10, s[10]='t'. countS['t'] becomes 2.
* count is still 3. Shrink again from start=4.
* s[4]='t'. countS['t'] > countP['t'] (2 > 1). Decrement countS['t'] to 1. start becomes 5.
* window s[5...10] = "opract". Length 6. No change in min_len.
*
* j=11, s[11]='i'. countS['i'] becomes 2.
* j=12, s[12]='c'. countS['c'] becomes 2.
* j=13, s[13]='e'. countS['e'] becomes 2.
*
* Loop ends.
* Return s.substr(4, 6) which is "toprac".
*
*/
```

### Java Solution

```java
// Intuition:
// The problem asks for the smallest substring of 's' that contains all characters of 'p'.
// A sliding window approach is perfect for this. We can maintain a "window" in 's'
// and keep track of the characters inside it. We expand the window by moving its right
// end and shrink it from its left end.

// Approach:
// 1. First, we count the frequency of each character in the pattern string 'p' and store it in a hash map (or an array since we only have 256 possible characters).
// 2. We initialize two pointers, 'start' and 'j' (for the end of the window), both at the beginning of 's'.
// 3. We also need a counter 'count' to track how many characters from 'p' we have found in the current window of 's'.
// 4. We iterate through 's' with the 'j' pointer to expand the window. For each character s.charAt(j):
//    a. We increment its count in our window's frequency map.
//    b. If the character s.charAt(j) is needed for our pattern (i.e., its count in 'p' is > 0) AND we haven't found more of this character than needed, we increment 'count'.
// 5. When 'count' equals the length of 'p', it means our current window s.substring(start, j+1) contains all the required characters.
//    a. Now, we try to shrink this window from the left by moving the 'start' pointer forward.
//    b. We can move 'start' as long as the window remains valid. A window remains valid if s.charAt(start) is either not in 'p' or if we have more of s.charAt(start) than required.
//    c. While shrinking, we decrement the character count of s.charAt(start) in our window's frequency map.
//    d. After shrinking, we have a minimal window s.substring(start, j+1). We compare its length with the minimum length found so far and update if necessary.
// 6. We continue this process until 'j' reaches the end of 's'.
// 7. If we never found a valid window, the starting index will remain -1, and we return an empty string. Otherwise, we return the smallest window found.

// Time Complexity: O(|s|)
// We iterate through the string 's' with two pointers, 'start' and 'j'. Each character of 's' is visited at most twice (once by 'j' and once by 'start').

// Space Complexity: O(1)
// We use two arrays of size 256 to store character counts, which is constant space.
class Solution {
    public static String smallestWindow(String s, String p) {
        int len1 = s.length();
        int len2 = p.length();

        // If length of s is less than length of p, it's impossible to find a window.
        if (len1 < len2) {
            return "";
        }

        // Frequency maps for characters in p and the current window in s.
        int[] countP = new int[256];
        int[] countS = new int[256];

        // Store occurrence of characters of p.
        for (int i = 0; i < len2; i++) {
            countP[p.charAt(i)]++;
        }

        int start = 0, start_idx = -1, min_len = Integer.MAX_VALUE;

        // 'count' tracks how many characters of p are currently covered by the window.
        int count = 0;

        // Iterate through s to expand the window from the right.
        for (int j = 0; j < len1; j++) {
            // Count occurrence of characters of string S.
            countS[s.charAt(j)]++;

            // If s.charAt(j) is a character in p and we haven't exceeded its required count.
            if (countP[s.charAt(j)] != 0 && countS[s.charAt(j)] <= countP[s.charAt(j)]) {
                count++;
            }

            // If all characters of p are found in the current window.
            if (count == len2) {
                // Try to minimize the window from the left.
                while (countS[s.charAt(start)] > countP[s.charAt(start)] || countP[s.charAt(start)] == 0) {
                    if (countS[s.charAt(start)] > countP[s.charAt(start)]) {
                        countS[s.charAt(start)]--;
                    }
                    start++;
                }

                // Update window size.
                int len = j - start + 1;
                if (min_len > len) {
                    min_len = len;
                    start_idx = start;
                }
            }
        }

        // If no window was found.
        if (start_idx == -1) {
            return "";
        }

        return s.substring(start_idx, start_idx + min_len);
    }
}

/*
*
* Dry Run
* s = "timetopractice", p = "toc"
*
* len1 = 14, len2 = 3
* countP: {'t': 1, 'o': 1, 'c': 1}
*
* j=0, s.charAt(0)='t'. countS['t'] becomes 1. count becomes 1.
* j=1, s.charAt(1)='i'. countS['i'] becomes 1.
* j=2, s.charAt(2)='m'. countS['m'] becomes 1.
* j=3, s.charAt(3)='e'. countS['e'] becomes 1.
* j=4, s.charAt(4)='t'. countS['t'] becomes 2.
* j=5, s.charAt(5)='o'. countS['o'] becomes 1. count becomes 2.
* j=6, s.charAt(6)='p'. countS['p'] becomes 1.
* j=7, s.charAt(7)='r'. countS['r'] becomes 1.
* j=8, s.charAt(8)='a'. countS['a'] becomes 1.
* j=9, s.charAt(9)='c'. countS['c'] becomes 1. count becomes 3.
*
* Now, count == len2 (3 == 3). Window is "timetoprac".
* Try to shrink from start=0.
* s.charAt(0)='t'. countS['t'] > countP['t'] (2 > 1). Decrement countS['t'] to 1. start becomes 1.
* s.charAt(1)='i'. countP['i'] == 0. start becomes 2.
* s.charAt(2)='m'. countP['m'] == 0. start becomes 3.
* s.charAt(3)='e'. countP['e'] == 0. start becomes 4.
* s.charAt(4)='t'. countS['t'] == countP['t'] (1 == 1). Cannot shrink.
*
* Current window is s.substring(4, 10) = "toprac". Length = 6.
* min_len = 6, start_idx = 4.
*
* j=10, s.charAt(10)='t'. countS['t'] becomes 2.
* count is still 3. Shrink again from start=4.
* s.charAt(4)='t'. countS['t'] > countP['t'] (2 > 1). Decrement countS['t'] to 1. start becomes 5.
* window s.substring(5, 11) = "opract". Length 6. No change in min_len.
*
* j=11, s.charAt(11)='i'. countS['i'] becomes 2.
* j=12, s.charAt(12)='c'. countS['c'] becomes 2.
* j=13, s.charAt(13)='e'. countS['e'] becomes 2.
*
* Loop ends.
* Return s.substring(4, 10) which is "toprac".
*
*/
```

---

## Key Insights

The **Sliding Window** technique is highly effective for problems involving finding a substring or subarray that satisfies certain conditions. The core idea is to efficiently scan the data structure (like a string or array) without re-computing values for overlapping subproblems.

-   **Two Pointers**: The use of `start` and `j` pointers defines the current window.
-   **Frequency Maps**: Using hash maps (or arrays for a fixed character set) is crucial for keeping track of character counts in O(1) time.
-   **Expand and Shrink**: The window expands until it's "valid" (contains all required characters) and then shrinks from the left to find the smallest possible valid window. This ensures we check all potential substrings in a single pass.

---

## Further Exploration

If you enjoyed this problem, consider exploring these related topics and problems on GeeksforGeeks:

-   [**Smallest distinct window**](https://www.geeksforgeeks.org/problems/smallest-distant-window3132/1)
-   [**Longest Substring Without Repeating Characters**](https://www.geeksforgeeks.org/problems/longest-distinct-characters-in-string5848/1)
-   [**Sliding Window Maximum**](https://www.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k3101/1)
-   Problems tagged with `sliding-window` and `two-pointers`.

---

## References

-   [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1)
-   [Sliding Window Technique Explained](https://www.geeksforgeeks.org/window-sliding-technique/)

---

## Author

-   Connect with me on GitHub: [imnilesh18](https://github.com/imnilesh18)

---

## Tags

![Sliding Window][tag-sliding-window]
![Two Pointers][tag-two-pointers]
![String][tag-string]
![Hashing][tag-hashing]
![GeeksforGeeks][tag-gfg]

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**Note**: This is for educational purposes only. All rights to the problem statement and examples belong to GeeksforGeeks.

[gfg-shield]: https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white
[difficulty-shield]: https://img.shields.io/badge/Difficulty-Hard-FF5733?style=for-the-badge
[accuracy-shield]: https://img.shields.io/badge/Accuracy-30.19%25-blue?style=for-the-badge
[points-shield]: https://img.shields.io/badge/Points-8-239120?style=for-the-badge
[license-shield]: https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge
[tag-sliding-window]: https://img.shields.io/badge/Sliding%20Window-2077FF?style=for-the-badge&logoColor=white
[tag-two-pointers]: https://img.shields.io/badge/Two%20Pointers-FF69B4?style=for-the-badge&logoColor=white
[tag-string]: https://img.shields.io/badge/String-563D7C?style=for-the-badge&logoColor=white
[tag-hashing]: https://img.shields.io/badge/Hashing-1DA1F2?style=for-the-badge&logoColor=white
[tag-gfg]: https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logoColor=white