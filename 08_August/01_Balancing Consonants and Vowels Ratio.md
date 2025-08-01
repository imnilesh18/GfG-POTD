# ⚖️ Balancing Consonants and Vowels Ratio

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/balancing-consonants-and-vowels-ratio/1).

<div align="center">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GFG Badge"/>
    <img src="https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge" alt="Difficulty Badge"/>
    <img src="https://img.shields.io/badge/Accuracy-52.97%25-blue.svg?style=for-the-badge" alt="Accuracy Badge"/>
    <img src="https://img.shields.io/badge/Points-4-orange.svg?style=for-the-badge" alt="Points Badge"/>
    <img src="https://img.shields.io/badge/License-MIT-black.svg?style=for-the-badge" alt="License Badge"/>
</div>

---

## 📝 Problem Statement

Given an array of strings `arr[]`, where each `arr[i]` consists of lowercase English alphabets, your task is to count the number of **balanced substrings** that can be formed by concatenating one or more contiguous strings from `arr[]`.

A **balanced string** is defined as a string that contains an equal number of vowels and consonants.

---

## 🧪 Examples

### Example 1:
```
Input: arr[] = ["aeio", "aa", "bc", "ot", "cdbd"]
Output: 4
```
<details>
<summary>📖 Example Breakdown</summary>

The goal is to find contiguous subarrays of `arr` which, when concatenated, have an equal number of vowels and consonants.

* **`arr[0..4]` → "aeioaabcotcdbd"**
    * Vowels: a, e, i, o, a, a, o (7)
    * Consonants: b, c, t, c, d, b, d (7)
    * Counts are equal (7 == 7). This is a **balanced** substring. (Count = 1)
* **`arr[1..2]` → "aabc"**
    * Vowels: a, a (2)
    * Consonants: b, c (2)
    * Counts are equal (2 == 2). This is a **balanced** substring. (Count = 2)
* **`arr[1..3]` → "aabcot"**
    * Vowels: a, a, o (3)
    * Consonants: b, c, t (3)
    * Counts are equal (3 == 3). This is a **balanced** substring. (Count = 3)
* **`arr[3..3]` → "ot"**
    * Vowels: o (1)
    * Consonants: t (1)
    * Counts are equal (1 == 1). This is a **balanced** substring. (Count = 4)

The total count of such balanced substrings is **4**.

</details>

### Example 2:
```
Input: arr[] = ["ab", "be"]
Output: 3
```

### Example 3:
```
Input: arr[] = ["tz", "gfg", "ae"]
Output: 0
```

---

## ⛓️ Constraints

> ```
> 1 ≤ arr.size() ≤ 10^5
> 1 ≤ arr[i].size() ≤ 10^5
> The total number of characters in all strings combined is less than 10^5.
> ```

---

## 💡 Solution Approaches

### 1. Brute-force Approach
The most straightforward method is to generate every possible contiguous subarray, concatenate the strings within it, and then manually count the vowels and consonants to check for a balance.

#### C++ Solution
```cpp
// Intuition:
// The most direct way is to check every possible contiguous subarray. For each subarray, we form the complete string and count vowels and consonants to see if they are equal.
//
// Approach:
// 1. Use a nested loop to generate all subarrays. The outer loop `i` sets the start, and the inner loop `j` sets the end.
// 2. For each subarray from `i` to `j`, concatenate all strings `arr[k]` where `k` is from `i` to `j`.
// 3. Iterate through the concatenated string, counting vowels and consonants.
// 4. If the counts are equal, increment the result counter.
//
// Time Complexity: O(N^2 * L), where N is the number of strings and L is the total number of characters. The nested loops are O(N^2), and concatenation/counting takes O(L) in the worst case.
// Space Complexity: O(L) to store the temporary concatenated string.
class Solution {
public:
    // Helper to check if a character is a vowel
    bool isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    int countBalanced(vector<string>& arr) {
        int n = arr.size();
        int result = 0;

        // Outer loop for the starting index of the subarray
        for (int i = 0; i < n; i++) {
            string s = ""; // Temporary string for concatenation
            // Inner loop for the ending index of the subarray
            for (int j = i; j < n; j++) {
                s += arr[j]; // Concatenate the next string in the window
                int v = 0, c = 0; // Vowel and consonant counters

                // Count vowels and consonants in the current concatenated string
                for (char ch : s) {
                    if (isVowel(ch)) v++;
                    else c++;
                }

                // If counts are equal, we found a balanced substring
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
* result = 0
*
* i = 0:
* j = 0: s = "ab"   -> v=1, c=1. Balanced! result = 1.
* j = 1: s = "abbe" -> v=2, c=2. Balanced! result = 2.
*
* i = 1:
* j = 1: s = "be"   -> v=1, c=1. Balanced! result = 3.
*
* Final Output: 3
*/
```

#### Java Solution
```java
/*
// Intuition:
// The most direct way is to check every possible contiguous subarray. For each subarray, we form the complete string and count vowels and consonants to see if they are equal.
//
// Approach:
// 1. Use a nested loop to generate all subarrays. The outer loop `i` sets the start, and the inner loop `j` sets the end.
// 2. For each subarray from `i` to `j`, concatenate all strings `arr[k]` where `k` is from `i` to `j`.
// 3. Iterate through the concatenated string, counting vowels and consonants.
// 4. If the counts are equal, increment the result counter.
//
// Time Complexity: O(N^2 * L), where N is the number of strings and L is the total number of characters. The nested loops are O(N^2), and concatenation/counting takes O(L) in the worst case.
// Space Complexity: O(L) to store the temporary concatenated string.
*/
class Solution {
    // Helper to check if a character is a vowel
    public static boolean isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    public static int countBalanced(String[] arr) {
        int n = arr.length;
        int result = 0;

        // Outer loop for the starting index of the subarray
        for (int i = 0; i < n; i++) {
            StringBuilder s = new StringBuilder(); // Use StringBuilder for efficiency
            // Inner loop for the ending index of the subarray
            for (int j = i; j < n; j++) {
                s.append(arr[j]); // Concatenate the next string
                int v = 0, c = 0; // Vowel and consonant counters

                // Count vowels and consonants in the current string
                for (int k = 0; k < s.length(); k++) {
                    if (isVowel(s.charAt(k))) v++;
                    else c++;
                }

                // If counts are equal, we found a balanced substring
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
* result = 0
*
* i = 0:
* j = 0: s = "ab"   -> v=1, c=1. Balanced! result = 1.
* j = 1: s = "abbe" -> v=2, c=2. Balanced! result = 2.
*
* i = 1:
* j = 1: s = "be"   -> v=1, c=1. Balanced! result = 3.
*
* Final Output: 3
*/
```

---

### 2. Optimized Approach (Prefix Sum & Hash Map)

The brute-force approach is too slow due to repeated concatenations and counting. A more efficient method transforms the problem. Let's assign a score of `+1` to each vowel and `-1` to each consonant. A string is balanced if its total score is `0`.

We can pre-calculate the score for each string in `arr`. Then, we can use a **prefix sum** (or running total) of these scores. If a prefix sum `P` repeats, it means the subarray between the two occurrences has a total score of `0`, making it a balanced substring. A hash map is perfect for tracking the frequencies of these prefix sums.

#### C++ Solution
```cpp
// Intuition:
// Transform the problem into finding subarrays with a sum of 0. We can assign +1 to vowels and -1 to consonants. A balanced string has a total score of 0. This is a classic prefix sum problem.
//
// Approach:
// 1. Create a map to store the frequency of prefix sums, initializing `freq[0] = 1` for the empty prefix.
// 2. Initialize `prefix = 0` and `result = 0`.
// 3. Iterate through each string in `arr`.
// 4. For each string, calculate its net score (vowels - consonants).
// 5. Add this score to the `prefix`.
// 6. A balanced subarray is one with a net score of 0. If the prefix sum at index `j` is equal to the prefix sum at index `i` (where i < j), the subarray `arr[i+1...j]` has a sum of 0.
// 7. Therefore, `result += freq[prefix]` adds the number of times this prefix has been seen before.
// 8. Increment the frequency of the current `prefix`: `freq[prefix]++`.
//
// Time Complexity: O(L), where L is the total number of characters across all strings. Each character is processed once to calculate scores.
// Space Complexity: O(N), where N is the number of strings, for the hash map which stores at most N+1 distinct prefix sums.
class Solution {
public:
    bool isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    int countBalanced(vector<string>& arr) {
        int n = arr.size();
        int result = 0;
        int prefix = 0;
        unordered_map<int, int> freq;
        freq[0] = 1; // Base case: an empty prefix has a sum of 0 and occurs once

        // Iterate through each string in the array
        for (const string& s : arr) {
            int score = 0;
            // Calculate the score for the current string
            for (char ch : s) {
                if (isVowel(ch)) score++; // +1 for a vowel
                else score--;             // -1 for a consonant
            }
            prefix += score; // Update the running prefix sum

            // If this prefix sum has been seen before, it means the subarray(s)
            // between the previous occurrences and now are balanced.
            result += freq[prefix];

            // Increment the frequency of the current prefix sum
            freq[prefix]++;
        }
        return result;
    }
};

/*
*
* Dry Run
*
* arr = ["ab", "be"]
* freq = {0: 1}, prefix = 0, result = 0
*
* String "ab":
* score = 0 (+1 for 'a', -1 for 'b')
* prefix = 0 + 0 = 0
* result += freq[0] -> result = 0 + 1 = 1
* freq[0] becomes 2.  freq = {0: 2}
*
* String "be":
* score = 0 (-1 for 'b', +1 for 'e')
* prefix = 0 + 0 = 0
* result += freq[0] -> result = 1 + 2 = 3
* freq[0] becomes 3.  freq = {0: 3}
*
* Final Output: 3
*/
```

#### Java Solution
```java
/*
// Intuition:
// Transform the problem into finding subarrays with a sum of 0. We can assign +1 to vowels and -1 to consonants. A balanced string has a total score of 0. This is a classic prefix sum problem.
//
// Approach:
// 1. Create a map to store the frequency of prefix sums, initializing `freq[0] = 1` for the empty prefix.
// 2. Initialize `prefix = 0` and `result = 0`.
// 3. Iterate through each string in `arr`.
// 4. For each string, calculate its net score (vowels - consonants).
// 5. Add this score to the `prefix`.
// 6. A balanced subarray is one with a net score of 0. If the prefix sum at index `j` is equal to the prefix sum at index `i` (where i < j), the subarray `arr[i+1...j]` has a sum of 0.
// 7. Therefore, `result += freq.getOrDefault(prefix, 0)` adds the number of times this prefix has been seen before.
// 8. Increment the frequency of the current `prefix` in the map.
//
// Time Complexity: O(L), where L is the total number of characters across all strings. Each character is processed once.
// Space Complexity: O(N), where N is the number of strings, for the HashMap which stores at most N+1 distinct prefix sums.
*/
class Solution {
    public static boolean isVowel(char ch) {
        return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
    }

    public static int countBalanced(String[] arr) {
        int result = 0;
        int prefix = 0;
        Map<Integer, Integer> freq = new HashMap<>();
        freq.put(0, 1); // Base case: an empty prefix has a sum of 0

        // Iterate through each string
        for (String str : arr) {
            int score = 0;
            // Calculate score for the current string
            for (char ch : str.toCharArray()) {
                if (isVowel(ch)) score++; // +1 for vowel
                else score--;             // -1 for consonant
            }
            prefix += score; // Update running prefix sum

            // Add the number of times this prefix sum has occurred before
            result += freq.getOrDefault(prefix, 0);

            // Increment the count for the current prefix sum
            freq.put(prefix, freq.getOrDefault(prefix, 0) + 1);
        }
        return result;
    }
}

/*
*
* Dry Run
*
* arr = ["ab", "be"]
* freq = {0: 1}, prefix = 0, result = 0
*
* String "ab":
* score = 0 ('a':+1, 'b':-1)
* prefix = 0 + 0 = 0
* result += freq.get(0) -> result = 0 + 1 = 1
* freq.put(0, 2). freq = {0: 2}
*
* String "be":
* score = 0 ('b':-1, 'e':+1)
* prefix = 0 + 0 = 0
* result += freq.get(0) -> result = 1 + 2 = 3
* freq.put(0, 3). freq = {0: 3}
*
* Final Output: 3
*/
```

---

## 🎯 Key Insights

* **Problem Transformation**: The core idea is to convert the vowel/consonant balancing problem into a "subarray with zero sum" problem. By assigning scores (`+1`/`-1`), we can use mathematical techniques.
* **Prefix Sum & Hashing**: This is a powerful combination for solving many subarray/substring problems. The prefix sum allows us to find the sum of any subarray in O(1) time, and the hash map allows us to efficiently track and retrieve the counts of these sums. This avoids the O(N^2) complexity of the naive approach.

---

## 🔎 Further Exploration

* What if you needed to find the **longest** balanced substring instead of the count?
* How would you adapt the solution if the required ratio of vowels to consonants was 2:1 instead of 1:1?
* Can this approach be used for problems involving more than two character classes (e.g., vowels, consonants, digits)?

---

## 📚 References

* **Original Problem:** [https://www.geeksforgeeks.org/problems/balancing-consonants-and-vowels-ratio/1](https://www.geeksforgeeks.org/problems/balancing-consonants-and-vowels-ratio/1)
* **Related Concept:** [Subarray Sums Divisible by K](https://www.geeksforgeeks.org/problems/subarray-sums-divisible-by-k/0) (uses a similar prefix sum/hashing technique).

---

## 👨‍💻 Author

* **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div align="center">
    <img src="https://img.shields.io/badge/Prefix%20Sum-4B0082?style=for-the-badge" alt="Prefix Sum Tag"/>
    <img src="https://img.shields.io/badge/HashMap-8A2BE2?style=for-the-badge" alt="HashMap Tag"/>
    <img src="https://img.shields.io/badge/String-DB7093?style=for-the-badge" alt="String Tag"/>
    <img src="https://img.shields.io/badge/Subarray-FF7F50?style=for-the-badge" alt="Subarray Tag"/>
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge" alt="GeeksforGeeks Tag"/>
</div>

---

## 📜 License

This project is licensed under the **MIT License**.

> **Note**: This is for educational purposes only. The solutions are provided for learning and reference. Always try to solve the problem on your own first.