# 🔠 Longest Substring with K Uniques

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-34.65%25-green?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-4-blue?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1).

---

## 📝 Problem Statement

You are given a string `s` consisting only of lowercase alphabets and an integer `k`. Your task is to find the **length** of the **longest substring** that contains exactly `k` distinct characters.

**Note:** If no such substring exists, return `-1`.

---

## ⚙️ Constraints

> - `1 <= s.size() <= 10^5`
> - `1 <= k <= 26`

---

## 💡 Examples

**Example 1:**
```text
Input: s = "aabacbebebe", k = 3
Output: 7
Explanation: The longest substring with exactly 3 distinct characters is "cbebebe", which includes 'c', 'b', and 'e'.
```

**Example 2:**
```text
Input: s = "aaaa", k = 2
Output: -1
Explanation: There's no substring with 2 distinct characters.
```

**Example 3:**
```text
Input: s = "aabaaab", k = 2
Output: 7
Explanation: The entire string "aabaaab" has exactly 2 unique characters 'a' and 'b', making it the longest valid substring.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

**Input:** `s = "aabacbebebe"`, `k = 3`

1. Initialize two pointers `i = 0` and `j = 0`, and a map to store character frequencies.
2. Expand the window by moving `j` to the right. When the window becomes `"aabac"` (length 5), we have exactly 3 unique characters (`a`, `b`, `c`). Update `result = max(-1, 5) = 5`.
3. Move `j` to the next character `b`. The window is `"aabacb"` (length 6) with 3 unique characters. Update `result = max(5, 6) = 6`.
4. Move `j` to the next character `e`. The window is `"aabacbe"` (length 7). Now we have 4 unique characters, which is greater than `k (3)`.
5. We must shrink the window from the left by moving `i` forward and decreasing the frequency of characters at `s[i]`. We do this until the number of distinct characters in our map drops back to 3.
6. This expanding and shrinking process continues until `j` reaches the end of the string.
7. The longest valid window found during this process is `"cbebebe"` which has a length of `7`.

</details>

---

## 🚀 Solution Approaches

### Sliding Window with Frequency Map

This problem can be optimally solved using the **Sliding Window** technique with a hash map to keep track of character frequencies.
- We maintain a window `[i...j]` that slides across the string. 
- We expand the window by moving the right pointer `j` and adding `s[j]` to our frequency map.
- If the number of distinct characters (the size of the map) exceeds `k`, the window becomes invalid. We shrink it by moving the left pointer `i` and decreasing character counts until we have exactly `k` distinct characters again.
- Whenever the map contains exactly `k` distinct characters, we calculate the current window's length and update our maximum result.

<details>
<summary><b>💻 C++ Solution</b></summary>

```cpp
// Intuition: Track character frequencies dynamically to find the longest valid substring using a two-pointer approach.
// Approach: Use sliding window with two pointers and a frequency map to maintain exactly k distinct characters in the window; expand right pointer, shrink left when distinct count exceeds k, and update max length when count == k.
// Time Complexity: O(n), where n = s.length(), since each character is processed at most twice (once by j and once by i).
// Space Complexity: O(1) (bounded by alphabet size 26), for the unordered_map storing character frequencies.
class Solution {
public:
    int longestKSubstr(string& s, int k) {
        int n = s.length();
        unordered_map<char, int> mp; // map to store frequency of chars in current window

        int i = 0;                   // left pointer of window
        int j = 0;                   // right pointer of window

        int result = -1;             // store max length found

        while (j < n) {
            mp[s[j]]++;   // include s[j] in window

            // if more than k distinct, shrink from left
            if (mp.size() > k) {
                mp[s[i]]--;          // decrement freq of s[i]
                if (mp[s[i]] == 0) { // if freq becomes 0, remove from map
                    mp.erase(s[i]);
                }
                i++;                 // move left pointer
            }

            // if exactly k distinct, update result
            if (mp.size() == k) {
                result = max(result, j - i + 1);
            }
            j++;  // expand right pointer
        }
        return result;
    }
};

/*
 *
 * Dry Run on Input: s = "aabacbebebe", k = 3
 *
 * i=0, j=0: window="a", mp={a:1}         => size=1 < 3, result stays -1
 * i=0, j=1: window="aa", mp={a:2}        => size=1 < 3, result stays -1
 * i=0, j=2: window="aab", mp={a:2,b:1}   => size=2 < 3, result stays -1
 * i=0, j=3: window="aaba", mp={a:3,b:1}  => size=2 < 3, result stays -1
 * i=0, j=4: window="aabac", mp={a:3,b:1,c:1} => size=3 == 3, result = 5
 * i=0, j=5: window="aabacb", mp={a:3,b:2,c:1} => size=3 == 3, result = 6
 * i=0, j=6: window="aabacbe", mp={a:3,b:2,c:1,e:1} => size=4 > 3
 * shrink: remove s[0]='a' -> mp={a:2,b:2,c:1,e:1}, i=1 => size=4 >3
 * shrink: remove s[1]='a' -> mp={a:1,b:2,c:1,e:1}, i=2 => size=4 >3
 * shrink: remove s[2]='b' -> mp={a:1,b:1,c:1,e:1}, i=3 => size=4 >3
 * shrink: remove s[3]='a' -> mp={a:0->erase,b:1,c:1,e:1}, i=4 => size=3
 * window="cb e", now size==3, result stays 6
 * i=4, j=6 window="cb e": length= j-i+1 = 6-4+1=3, result=6
 * i=4, j=7: include 'b' -> mp={c:1,e:1,b:2}, size=3, result = max(6,7-4+1=4)=6
 * i=4, j=8: include 'e' -> mp={c:1,e:2,b:2}, size=3, result = max(6,8-4+1=5)=6
 * i=4, j=9: include 'b' -> mp={c:1,e:2,b:3}, size=3, result = max(6,9-4+1=6)=6
 * i=4, j=10: include 'e' -> mp={c:1,e:3,b:3}, size=3, result = max(6,10-4+1=7)=7
 *
 * Final result = 7 (substring "cbebebe")
 */
```
</details>

<details>
<summary><b>☕ Java Solution</b></summary>

```java
// Intuition: Track character frequencies dynamically to find the longest valid substring using a two-pointer approach.
// Approach: Use sliding window with two pointers and a frequency map to maintain exactly k distinct characters in the window; expand right pointer, shrink left when distinct count exceeds k, and update max length when count == k.
// Time Complexity: O(n), where n = s.length(), since each character is processed at most twice (once by j and once by i).
// Space Complexity: O(1) (bounded by alphabet size 26), for the HashMap storing character frequencies.
class Solution {
    public int longestKSubstr(String s, int k) {
        int n = s.length();
        Map<Character, Integer> mp = new HashMap<>(); // map to store frequency of chars in current window

        int i = 0;                                    // left pointer of window
        int j = 0;                                    // right pointer of window

        int result = -1;                              // store max length found

        while (j < n) {
            // include s.charAt(j) in window
            char cj = s.charAt(j);
            mp.put(cj, mp.getOrDefault(cj, 0) + 1);

            // if more than k distinct, shrink from left
            if (mp.size() > k) {
                char ci = s.charAt(i);
                mp.put(ci, mp.get(ci) - 1);         // decrement freq of s.charAt(i)
                if (mp.get(ci) == 0) {              // if freq becomes 0, remove from map
                    mp.remove(ci);
                }
                i++;                                // move left pointer
            }

            // if exactly k distinct, update result
            if (mp.size() == k) {
                result = Math.max(result, j - i + 1);
            }
            j++; // expand right pointer
        }

        return result;
    }
}

/*
 *
 * Dry Run on Input: s = "aabacbebebe", k = 3
 *
 * i=0, j=0: window="a", mp={a=1}             => size=1 < 3, result stays -1
 * i=0, j=1: window="aa", mp={a=2}            => size=1 < 3, result stays -1
 * i=0, j=2: window="aab", mp={a=2,b=1}       => size=2 < 3, result stays -1
 * i=0, j=3: window="aaba", mp={a=3,b=1}      => size=2 < 3, result stays -1
 * i=0, j=4: window="aabac", mp={a=3,b=1,c=1} => size=3 == 3, result = 5
 * i=0, j=5: window="aabacb", mp={a=3,b:2,c=1}=> size=3 == 3, result = 6
 * i=0, j=6: window="aabacbe", mp={a=3,b:2,c:1,e=1} => size=4 > 3
 * shrink: remove s[0]='a' -> mp={a=2,b:2,c:1,e=1}, i=1 => size=4 > 3
 * i=1, j=6 window="abacbe"
 * (only one shrink per iteration as per code)
 * if size still > k, window will shrink further in subsequent j-iterations
 * after this iteration size=4 so result not updated
 * i=1, j=7: include 'b' -> mp={a=2,b=3,c=1,e=1}, size=4 > 3
 * shrink: remove s[1]='a' -> mp={a=1,b=3,c=1,e=1}, i=2 => size=4 > 3
 * i=2, j=7 window="bacbeb"
 * i=2, j=8: include 'e' -> mp={a=1,b=3,c=1,e=2}, size=4 > 3
 * shrink: remove s[2]='b' -> mp={a=1,b=2,c=1,e=2}, i=3 => size=4 > 3
 * i=3, j=8 window="acbebe"
 * i=3, j=9: include 'b' -> mp={a=1,b=3,c=1,e=2}, size=4 > 3
 * shrink: remove s[3]='a' -> mp={b=3,c=1,e=2}, i=4 => size=3
 * window="cbebeb", now size==3, result = max(6,9-4+1=6)=6
 * i=4, j=10: include 'e' -> mp={b=3,c=1,e=3}, size=3, result = max(6,10-4+1=7)=7
 *
 * Final result = 7 (substring "cbebebe")
 */
```
</details>

---

## 🧠 Key Insights

- **Sliding Window:** This pattern allows us to find subarrays/substrings without nested loops, making the solution highly optimal at $O(n)$ time complexity. We expand the right pointer to find a sequence and shrink the left pointer whenever the condition is violated.
- **Constant Space Bounds:** Even though we use a hash map, its maximum possible size is `26` because the string contains only lowercase English alphabets. Therefore, the space complexity strictly bounds to $O(1)$.

---

## 🔍 Further Exploration

You can practice these similar sliding window problems:
1. Longest Substring Without Repeating Characters
2. Subarrays with exactly K distinct integers
3. Smallest window in a string containing all characters of another string

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks - Longest Substring with K Uniques](https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1)

---

## ✍️ Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

`sliding-window` `hash-map` `string` `two-pointers` `geeksforgeeks` `medium`