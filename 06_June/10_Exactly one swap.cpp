/*
 * GfG Link: https://www.geeksforgeeks.org/problems/exactly-one-swap--170637/1
 *
 * Exactly one swap
 *
 * Difficulty: Medium Accuracy: 44.28% Submissions: 9K+ Points: 4
 *
 * Given a string s, return the number of distinct strings that can be obtained by exactly one swap of two different indices (i < j).
 *
 * Examples:
 *
 * Input: s = "geek"
 * Output: 6
 * Explanation: After one swap, There are only 6 distinct strings possible.(i.e "egek","eegk","geek","geke","gkee" and "keeg")
 *
 * Input: s = "aaaa"
 * Output: 1
 * Explanation: Only one distinct string is possible after one swap(i.e "aaaa")
 *
 * Constraints:
 * 2 ≤ s.size() ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute‐force all possible one‐swap variations by swapping each pair (i, j) and using a hash set to count unique results.
// Time Complexity: O(n³) in the worst case – O(n²) swaps × O(n) string‐hash/compare per insertion.
// Space Complexity: O(n³) – up to O(n²) distinct strings of length n stored in the set.
class Solution {
public:
    int countStrings(string& s) {
        int n = s.length();                              // length of the string

        unordered_set<string> set;                       // to store unique strings after one swap

        // Try every pair (i, j) with i < j
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(s[i], s[j]);                        // swap chars at i and j
                set.insert(s);                           // record the new string (duplicates are auto‐ignored)
                swap(s[i], s[j]);                        // swap back to restore original
            }
        }

        return set.size();                               // number of distinct one‐swap strings
    }
};

/*
 *
 * Dry Run
 *
 * Let s = "abca"
 * n = 4
 * set = {}
 *
 * i = 0, j = 1:
 *   swap(s[0], s[1]) → s = "baca"
 *   set.insert("baca") → set = {"baca"}
 *   swap back → s = "abca"
 *
 * i = 0, j = 2:
 *   swap(s[0], s[2]) → s = "cbaa"
 *   set.insert("cbaa") → set = {"baca","cbaa"}
 *   swap back → s = "abca"
 *
 * i = 0, j = 3:
 *   swap(s[0], s[3]) → s = "abca" (same)
 *   set.insert("abca") → set = {"baca","cbaa","abca"}
 *   swap back → s = "abca"
 *
 * i = 1, j = 2:
 *   swap(s[1], s[2]) → s = "acba"
 *   set.insert("acba") → set = {"baca","cbaa","abca","acba"}
 *   swap back → s = "abca"
 *
 * i = 1, j = 3:
 *   swap(s[1], s[3]) → s = "aacb"
 *   set.insert("aacb") → set = {"baca","cbaa","abca","acba","aacb"}
 *   swap back → s = "abca"
 *
 * i = 2, j = 3:
 *   swap(s[2], s[3]) → s = "abac"
 *   set.insert("abac") → set = {"baca","cbaa","abca","acba","aacb","abac"}
 *   swap back → s = "abca"
 *
 * Final set size = 6
 */

// Approach 2: Count distinct strings by tracking character frequencies. For each index i,
// subtract number of characters seen so far that are equal to s[i] to count how many swaps
// with different characters are possible. If any character appears more than once, add 1 more
// to include the case where a swap results in the same string.
// Time Complexity: O(n) – Single pass for counting + fixed 26-char check.
// Space Complexity: O(1) – Frequency array of size 26.
class Solution {
public:
    int countStrings(string& s) {
        int n = s.length();

        vector<int> mp(26, 0);         // frequency array for lowercase letters
        int         result = 0;

        for (int i = 0; i < n; i++) {
            result += (i - mp[s[i] - 'a']);   // count swaps with different chars seen so far
            mp[s[i] - 'a']++;                 // increment frequency of current character
        }

        for (int i = 0; i < 26; i++) {
            if (mp[i] > 1) {         // check if any character has duplicate
                result++;            // if yes, add one for swap that returns same string
                break;
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run – s = "aabb"
 *
 * Step 1: Initialize result = 0, mp = [0...0] (26 zeros)
 *
 * i = 0, s[0] = 'a':
 *   result += (0 - mp[0]) = 0 - 0 = 0 → result = 0
 *   mp[0]++ → mp = [1,0,0,...]
 *
 * i = 1, s[1] = 'a':
 *   result += (1 - mp[0]) = 1 - 1 = 0 → result = 0
 *   mp[0]++ → mp = [2,0,0,...]
 *
 * i = 2, s[2] = 'b':
 *   result += (2 - mp[1]) = 2 - 0 = 2 → result = 2
 *   mp[1]++ → mp = [2,1,0,...]
 *
 * i = 3, s[3] = 'b':
 *   result += (3 - mp[1]) = 3 - 1 = 2 → result = 4
 *   mp[1]++ → mp = [2,2,0,...]
 *
 * After loop: result = 4
 *
 * Check for duplicate chars:
 *   mp[0] = 2 → found duplicate → result = 5
 *
 * Final Answer = 5
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute‐force all possible one‐swap variations by swapping each pair (i, j) and using a hash set to count unique results.
// Time Complexity: O(n³) in the worst case – O(n²) swaps × O(n) string‐hash/compare per insertion.
// Space Complexity: O(n³) – up to O(n²) distinct strings of length n stored in the set.
class Solution {
    int countStrings(String s) {
        int n = s.length();                             // length of the string

        HashSet<String> set = new HashSet<>();          // to store unique strings after one swap

        // Try every pair (i, j) with i < j
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                char[] chars = s.toCharArray();         // convert to char array for easy swapping
                char temp = chars[i];                   // swap characters
                chars[i] = chars[j];
                chars[j] = temp;

                set.add(new String(chars));             // record new string; HashSet ensures uniqueness
            }
        }

        return set.size();                              // return the count of distinct swapped strings
    }
}

/*
 *
 * Dry Run
 *
 * Let s = "abca"
 * n = 4
 * set = {}
 *
 * i = 0, j = 1:
 *   swap s[0] and s[1] → "baca"
 *   set.add("baca") → set = {"baca"}
 *
 * i = 0, j = 2:
 *   swap s[0] and s[2] → "cbaa"
 *   set.add("cbaa") → set = {"baca", "cbaa"}
 *
 * i = 0, j = 3:
 *   swap s[0] and s[3] → "abca"
 *   set.add("abca") → set = {"baca", "cbaa", "abca"}
 *
 * i = 1, j = 2:
 *   swap s[1] and s[2] → "acba"
 *   set.add("acba") → set = {"baca", "cbaa", "abca", "acba"}
 *
 * i = 1, j = 3:
 *   swap s[1] and s[3] → "aacb"
 *   set.add("aacb") → set = {"baca", "cbaa", "abca", "acba", "aacb"}
 *
 * i = 2, j = 3:
 *   swap s[2] and s[3] → "abac"
 *   set.add("abac") → set = {"baca", "cbaa", "abca", "acba", "aacb", "abac"}
 *
 * Final set size = 6
 */

// Approach 2: Count distinct strings by tracking character frequencies. For each index i,
// subtract number of characters seen so far that are equal to s.charAt(i) to count how many swaps
// with different characters are possible. If any character appears more than once, add 1 more
// to include the case where a swap results in the same string.
// Time Complexity: O(n) – Single pass for counting + fixed 26-char check.
// Space Complexity: O(1) – Frequency array of size 26.
class Solution {
    int countStrings(String s) {
        int n = s.length();
        int[] mp = new int[26];         // frequency array
        int result = 0;

        for (int i = 0; i < n; i++) {
            result += (i - mp[s.charAt(i) - 'a']);   // swaps with different chars seen so far
            mp[s.charAt(i) - 'a']++;                 // increment current char freq
        }

        for (int i = 0; i < 26; i++) {
            if (mp[i] > 1) {         // duplicate character found
                result++;            // one extra swap that results in same string
                break;
            }
        }

        return result;
    }
}

/*
 *
 * Dry Run – s = "aabb"
 *
 * Step 1: Initialize result = 0, mp = [0...0] (26 zeros)
 *
 * i = 0, s[0] = 'a':
 *   result += (0 - mp[0]) = 0 - 0 = 0 → result = 0
 *   mp[0]++ → mp = [1,0,0,...]
 *
 * i = 1, s[1] = 'a':
 *   result += (1 - mp[0]) = 1 - 1 = 0 → result = 0
 *   mp[0]++ → mp = [2,0,0,...]
 *
 * i = 2, s[2] = 'b':
 *   result += (2 - mp[1]) = 2 - 0 = 2 → result = 2
 *   mp[1]++ → mp = [2,1,0,...]
 *
 * i = 3, s[3] = 'b':
 *   result += (3 - mp[1]) = 3 - 1 = 2 → result = 4
 *   mp[1]++ → mp = [2,2,0,...]
 *
 * After loop: result = 4
 *
 * Check for duplicate chars:
 *   mp[0] = 2 → found duplicate → result = 5
 *
 * Final Answer = 5
 */
