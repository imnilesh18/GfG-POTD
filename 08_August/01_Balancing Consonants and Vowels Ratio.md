# Balancing Consonants and Vowels Ratio

[![GeeksforGeeks Problem Link](https://img.shields.io/badge/Practice%20on-GeeksforGeeks-brightgreen)](https://www.geeksforgeeks.org/problems/balancing-consonants-and-vowels-ratio/1)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow)
![Accuracy](https://img.shields.io/badge/Accuracy-52.97%25-blue)
![Points](https://img.shields.io/badge/Points-4-orange)

---

> ⚠️ **This repository and its content are intended solely for educational purposes.**  
> Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the [GeeksforGeeks problem "Balancing Consonants and Vowels Ratio"](https://www.geeksforgeeks.org/problems/balancing-consonants-and-vowels-ratio/1).

---

## 📝 Problem Statement

Given an array of strings `arr[]`, where each `arr[i]` consists of lowercase English alphabets, your task is to count the number of **balanced substrings** that can be formed by concatenating one or more contiguous strings from `arr[]`.

A **balanced string** is defined as a string that contains an equal number of vowels and consonants.

---

## 📈 Examples

**Example 1**

```
Input: arr[] = ["aeio", "aa", "bc", "ot", "cdbd"]
Output: 4

Explanation:
The balanced substrings are:
- arr[0..4] → "aeioaabcotcdbd"
- arr[1..2] → "aabc"
- arr[1..3] → "aabcot"
- arr[3..3] → "ot"
```

**Example 2**

```
Input: arr[] = ["ab", "be"]
Output: 3

Explanation:
The balanced substrings are:
- arr[0..0] → "ab"
- arr[0..1] → "abbe"
- arr[1..1] → "be"
```

**Example 3**

```
Input: arr[] = ["tz", "gfg", "ae"]
Output: 0

Explanation:
No balanced substrings are found.
```

---

## 🔒 Constraints

- **1 ≤ arr.size() ≤ 10⁵**
- **1 ≤ arr[i].size() ≤ 10⁵**
- The total number of characters in all strings combined is less than 10⁵.

---

## 🛠️ Solution Approaches

### 1. Naive (Brute-force) Approach

Generate all possible contiguous subarrays, concatenate their strings, and count vowels and consonants. If their counts are equal, increment the result.

#### C++ Brute-force Code

```cpp
/*
// Intuition:
// Try every possible subarray, concatenate, and check if vowels == consonants.
//
// Approach:
// For each i, try every j >= i, concatenate, and count vowels/consonants.
//
// Time Complexity:
// O(n^2 * l) where n = arr.size(), l = total length of all strings.
//
// Space Complexity:
// O(l) for the temporary concatenated string.
*/
class Solution {
public:
    // Checks if a character is a vowel
    bool isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    // Counts the number of balanced subarrays
    int countBalanced(vector<string>& arr) {
        int n = arr.size();
        int result = 0;

        for (int i = 0; i < n; i++) {
            string s = ""; // Temporary string for concatenation

            for (int j = i; j < n; j++) {
                s += arr[j]; // Concatenate next string
                int v = 0, c = 0; // Vowel and consonant counters

                // Count vowels and consonants in the current string
                for (char ch : s) {
                    if (isVowel(ch)) v++;
                    else c++;
                }

                // If counts are equal, increment result
                if (v == c) result++;
            }
        }

        return result;
    }
};

/*
*
* Dry Run
*
* arr = ["ab", "be"]
* i = 0
*   j = 0: s = "ab"   -> v=1 c=1  (balanced) => result=1
*   j = 1: s = "abbe" -> v=2 c=2  (balanced) => result=2
* i = 1
*   j = 1: s = "be"   -> v=1 c=1  (balanced) => result=3
* Output: 3
*/
```

---

#### Java Brute-force Code

```java
/*
// Intuition:
// Try every possible subarray, concatenate, and check if vowels == consonants.

// Approach:
// For each starting index, build every possible contiguous subarray, concatenate, and count vowels/consonants.

// Time Complexity:
// O(n^2 * l) where n = arr.length, l = total length of all strings (since each subarray is concatenated and scanned).

// Space Complexity:
// O(l) for the temporary concatenated string.
*/
public class Solution {
    // Checks if a character is a vowel
    public static boolean isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    // Counts the number of balanced subarrays
    public static int countBalanced(String[] arr) {
        int n = arr.length;
        int result = 0;

        for (int i = 0; i < n; i++) {
            String s = ""; // Temporary string for concatenation

            for (int j = i; j < n; j++) {
                s += arr[j]; // Concatenate next string
                int v = 0, c = 0; // Vowel and consonant counters

                // Count vowels and consonants in the current string
                for (char ch : s.toCharArray()) {
                    if (isVowel(ch)) v++;
                    else c++;
                }

                // If counts are equal, increment result
                if (v == c) result++;
            }
        }

        return result;
    }
}

/*
*
* Dry Run
*
* arr = ["ab", "be"]
* i = 0
*   j = 0: s = "ab"   -> v=1 c=1  (balanced) => result=1
*   j = 1: s = "abbe" -> v=2 c=2  (balanced) => result=2
* i = 1
*   j = 1: s = "be"   -> v=1 c=1  (balanced) => result=3
* Output: 3
*/
```

---

### 2. Optimized Approach (Prefix Sum & Hash Map)

**Idea:**

- Assign a score to each string:  
  +1 for every vowel, -1 for every consonant.
- Compute the prefix sum of these scores.
- If the same prefix sum appears more than once, the subarray between those indices is balanced.
- Use a HashMap to track the frequency of each prefix sum.

#### C++ Optimized Code

```cpp
/*
// Intuition:
// Transform the array into scores (+1 vowel, -1 consonant), use prefix sum to find balanced subarrays.
//
// Approach:
// 1. For each string, calculate score.
// 2. Maintain prefix sum.
// 3. Use unordered_map to store frequency of prefix sums.
// 4. For each prefix, add its frequency to result before updating.
//
// Time Complexity:
// O(n * l) - n = number of strings, l = average length of each string.
//
// Space Complexity:
// O(n) - for prefix sum frequency map.
*/
class Solution {
public:
    // Checks if a character is a vowel
    bool isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    // Counts the number of balanced subarrays
    int countBalanced(vector<string>& arr) {
        int n = arr.size(), result = 0, prefix = 0;
        unordered_map<int, int> freq;
        freq[0] = 1; // Empty prefix is balanced

        for (int i = 0; i < n; i++) {
            int score = 0;
            for (char ch : arr[i]) {
                if (isVowel(ch)) score++;    // +1 for vowel
                else score--;               // -1 for consonant
            }
            prefix += score;                // Running prefix sum

            result += freq[prefix];         // Add count of previous same prefix
            freq[prefix]++;                 // Increment prefix sum frequency
        }
        return result;
    }
};

/*
*
* Dry Run
*
* arr = ["ab", "be"]
* freq = {0:1}
* prefix = 0, result = 0
* i=0: score = 0 (a:+1, b:-1), prefix=0, result+=1 (freq[0]=1), freq[0]=2
* i=1: score = 0 (b:-1, e:+1), prefix=0, result+=2 (freq[0]=2), freq[0]=3
* Output: 3
*/
```

---

#### Java Optimized Code

```java
/*
// Intuition:
// Convert the problem to prefix sum of (vowels - consonants) per block.
// If prefix sum repeats, subarray in between is balanced.
//
// Approach:
// 1. For each string, calculate score (+1 vowel, -1 consonant).
// 2. Maintain running prefix sum.
// 3. Use HashMap to count how many times each prefix has appeared.
// 4. For each prefix, add its count to result before increment.
//
// Time Complexity:
// O(n * l) - n = arr.length, l = average string length, since each char is processed once.
//
// Space Complexity:
// O(n) - due to the prefix sum map (at most n unique sums).
*/
public class Solution {
    // Checks if a character is a vowel
    public static boolean isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    // Counts the number of balanced subarrays
    public static int countBalanced(String[] arr) {
        int n = arr.length, res = 0, prefix = 0;
        Map<Integer, Integer> freq = new HashMap<>();
        freq.put(0, 1); // Empty prefix is considered balanced

        for (String str : arr) {
            int score = 0;
            for (char ch : str.toCharArray()) {
                if (isVowel(ch)) score++;    // +1 for vowel
                else score--;               // -1 for consonant
            }

            prefix += score; // Running sum of scores

            res += freq.getOrDefault(prefix, 0); // Add the number of previous same sums

            freq.put(prefix, freq.getOrDefault(prefix, 0) + 1); // Increment sum count
        }
        return res;
    }
}

/*
*
* Dry Run
*
* arr = ["ab", "be"]
* freq = {0:1}
* prefix = 0, res = 0
* str = "ab": score = 0 (a:+1, b:-1), prefix=0, res+=1 (freq[0]=1), freq[0]=2
* str = "be": score = 0 (b:-1, e:+1), prefix=0, res+=2 (freq[0]=2), freq[0]=3
* Output: 3
*/
```

---

## 💡 Key Insights

- The **prefix sum trick** allows us to efficiently count subarrays with equal numbers of vowels and consonants in linear time.
- Hash map stores the number of times a particular prefix sum has occurred, enabling quick calculation of the result.

---

## 🧩 Further Exploration

- Can you generalize this method to different character classes (digits, uppercase, etc.)?
- What if the string can contain non-English letters?

---

## 📚 References

- [GeeksforGeeks Problem Page](https://www.geeksforgeeks.org/problems/balancing-consonants-and-vowels-ratio/1)

---

## 👤 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`prefix-sum` `hashmap` `string` `subarray` `vowel` `consonant` `geeksforgeeks`

---

## 📄 License

This repository is released under the [MIT License](./LICENSE).

**This repository and its solutions are provided for educational purposes only and are not intended for commercial use. Please refer to the [GeeksforGeeks problem statement](https://www.geeksforgeeks.org/problems/balancing-consonants-and-vowels-ratio/1) for original content and copyright.**
