/*
 * Substrings with same first and last characters
 *
 * Difficulty: Easy Accuracy: 50.0% Submissions: 16K+ Points: 2
 *
 * Given a string s consisting of lowercase characters, the task is to find the count of all substrings that start and end with the same character.
 *
 * Examples:
 *
 * Input: s = "abcab"
 * Output: 7
 * Explanation: There are 7 substrings where the first and last characters are the same: "a", "abca", "b", "bcab", "c", "a", and "b"
 *
 * Input: s = "aba"
 * Output: 4
 * Explanation: There are 4 substrings where the first and last characters are the same: "a", "aba", "b", "a"
 *
 * Constraints:
 * 1 <= |s| <= 10^4
 * s contains lower case english alphabets
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute force approach that checks all possible substrings and counts those where the first and last characters are the same.
// Time Complexity: O(n^2) - Two nested loops go through all substring pairs.
// Space Complexity: O(1) - No extra space used except a few variables.
class Solution {
public:
    int countSubstring(string s) {
        int count = 0;
        int n     = s.length();

        // Iterate over all starting indices of substrings
        for (int i = 0; i < n; i++) {
            // Iterate over all ending indices for the current starting index
            for (int j = i; j < n; j++) {
                // Check if first and last characters of the substring match
                if (s[i] == s[j]) {
                    count++; // If they match, increment the count
                }
            }
        }

        return count; // Return total count of valid substrings
    }
}

/*
 *
 * Dry Run
 *
 * Input: "aba"
 * n = 3
 *
 * Outer loop i = 0
 *   j = 0 -> s[0] == s[0] -> 'a' == 'a' -> count = 1
 *   j = 1 -> s[0] != s[1] -> 'a' != 'b' -> skip
 *   j = 2 -> s[0] == s[2] -> 'a' == 'a' -> count = 2
 *
 * Outer loop i = 1
 *   j = 1 -> s[1] == s[1] -> 'b' == 'b' -> count = 3
 *   j = 2 -> s[1] != s[2] -> 'b' != 'a' -> skip
 *
 * Outer loop i = 2
 *   j = 2 -> s[2] == s[2] -> 'a' == 'a' -> count = 4
 *
 * Final Count = 4
 *
 */

// Approach 2: Count the frequency of each character, then use combination formula:
// Total substrings = freq + (freq * (freq - 1)) / 2 for each character.
// Time Complexity: O(n + 26) ≈ O(n) - Traverse the string once and then a loop of fixed size 26.
// Space Complexity: O(1) - Fixed size frequency array used.
class Solution {
public:
    int countSubstring(string& s) {
        int n     = s.length();
        int count = 0;

        vector<int> freq(26, 0); // Frequency array for a-z

        // Count frequency of each character
        for (int i = 0; i < n; i++) {
            freq[s[i] - 'a']++;
        }

        // For each character, calculate valid substrings
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                // Substrings of length 1: freq[i]
                // Substrings of length >1: (freq[i] * (freq[i] - 1)) / 2
                count += freq[i] + (freq[i] * (freq[i] - 1)) / 2;
            }
        }
        return count;
    }
};

/*
 *
 * Dry Run
 *
 * Input: "aba"
 * freq['a' - 'a'] = 2
 * freq['b' - 'a'] = 1
 *
 * For 'a' (freq = 2):
 *   substrings = 2 (length 1) + (2 * (2 - 1)) / 2 = 2 + 1 = 3
 *
 * For 'b' (freq = 1):
 *   substrings = 1 (length 1) + (1 * 0) / 2 = 1 + 0 = 1
 *
 * Total substrings = 3 (for 'a') + 1 (for 'b') = 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute force approach that checks all possible substrings and counts those where the first and last characters are the same.
// Time Complexity: O(n^2) - Two nested loops go through all substring pairs.
// Space Complexity: O(1) - No extra space used except a few variables.
class Solution {
    public int countSubstring(String s) {
        int count = 0;
        int n     = s.length();

        // Iterate over all starting indices of substrings
        for (int i = 0; i < n; i++) {
            // Iterate over all ending indices for the current starting index
            for (int j = i; j < n; j++) {
                // Check if first and last characters of the substring match
                if (s.charAt(i) == s.charAt(j)) {
                    count++; // If they match, increment the count
                }
            }
        }

        return count; // Return total count of valid substrings
    }
}

/*
 *
 * Dry Run
 *
 * Input: "aba"
 * n = 3
 *
 * Outer loop i = 0
 *   j = 0 -> s.charAt(0) == s.charAt(0) -> 'a' == 'a' -> count = 1
 *   j = 1 -> s.charAt(0) != s.charAt(1) -> 'a' != 'b' -> skip
 *   j = 2 -> s.charAt(0) == s.charAt(2) -> 'a' == 'a' -> count = 2
 *
 * Outer loop i = 1
 *   j = 1 -> s.charAt(1) == s.charAt(1) -> 'b' == 'b' -> count = 3
 *   j = 2 -> s.charAt(1) != s.charAt(2) -> 'b' != 'a' -> skip
 *
 * Outer loop i = 2
 *   j = 2 -> s.charAt(2) == s.charAt(2) -> 'a' == 'a' -> count = 4
 *
 * Final Count = 4
 *
 */

// Approach 2: Count the frequency of each character, then use combination formula:
// Total substrings = freq + (freq * (freq - 1)) / 2 for each character.
// Time Complexity: O(n + 26) ≈ O(n) - Traverse the string once and then a loop of fixed size 26.
// Space Complexity: O(1) - Fixed size frequency array used.
class Solution {
    public int countSubstring(String s) {
        int n     = s.length();
        int count = 0;

        int[] freq = new int[26]; // Frequency array for lowercase letters

        // Count frequency of each character
        for (int i = 0; i < n; i++) {
            freq[s.charAt(i) - 'a']++;
        }

        // For each character, calculate valid substrings
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                // Substrings of length 1: freq[i]
                // Substrings of length >1: (freq[i] * (freq[i] - 1)) / 2
                count += freq[i] + (freq[i] * (freq[i] - 1)) / 2;
            }
        }

        return count;
    }
}

/*
 *
 * Dry Run
 *
 * Input: "aba"
 * freq['a' - 'a'] = 2
 * freq['b' - 'a'] = 1
 *
 * For 'a' (freq = 2):
 *   substrings = 2 (length 1) + (2 * (2 - 1)) / 2 = 2 + 1 = 3
 *
 * For 'b' (freq = 1):
 *   substrings = 1 (length 1) + (1 * 0) / 2 = 1 + 0 = 1
 *
 * Total substrings = 3 (for 'a') + 1 (for 'b') = 4
 *
 */
