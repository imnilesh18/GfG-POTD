/*
 * GfG Link: https://www.geeksforgeeks.org/problems/substrings-of-length-k-with-k-1-distinct-elements/1
 *
 * Substrings of length k with k-1 distinct elements
 *
 * Difficulty: Medium Accuracy: 57.85% Submissions: 25K+ Points: 4 Average Time: 15m
 *
 * Given a string s consisting only lowercase alphabets and an integer k. Find the count of all substrings of length k which have exactly k-1 distinct characters.
 *
 * Examples:
 *
 * Input: s = "abcc", k = 2
 * Output: 1
 * Explaination: Possible substring of length k = 2 are,
 * ab : 2 distinct characters
 * bc : 2 distinct characters
 * cc : 1 distinct characters
 * Only one valid substring so, count is equal to 1.
 *
 * Input: "aabab", k = 3
 * Output: 3
 * Explaination: Possible substring of length k = 3 are,
 * aab : 2 distinct charcters
 * aba : 2 distinct characters
 * bab : 2 distinct characters
 * All these substring are valid so, the total count is equal to 3.
 *
 * Constrains:
 * 1 ≤ s.size() ≤ 10^5
 * 2 ≤ k ≤ 27
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute-force. Check every substring of length k, count the number of distinct characters using a frequency array, and check if it equals k - 1.
// Time Complexity: O(n * k), where n is the length of the string and k is the size of the window. We iterate over all substrings of length k and count distinct characters.
// Space Complexity: O(1), using a fixed-size frequency array of 26.
class Solution {
public:
    int substrCount(string& s, int k) {
        int n      = s.length();
        int result = 0;

        for (int i = 0; i <= n - k; i++) {
            vector<int> freq(26, 0); // reset frequency array for each substring

            for (int j = i; j < i + k; j++) {
                freq[s[j] - 'a']++; // count frequency of characters in current substring
            }

            int count = 0;
            for (int l = 0; l < 26; l++) {
                if (freq[l] > 0) {
                    count++; // count distinct characters
                }
            }

            if (count == k - 1) {
                result++; // valid substring
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "aabab", k = 3
 *
 * Substrings of length 3:
 *
 * 1. "aab" → freq[a]=2, freq[b]=1 → distinct=2 → valid → result = 1
 * 2. "aba" → freq[a]=2, freq[b]=1 → distinct=2 → valid → result = 2
 * 3. "bab" → freq[b]=2, freq[a]=1 → distinct=2 → valid → result = 3
 *
 * Final result = 3
 *
 */

// Approach 2: Sliding window with a frequency array. Maintain a window of size 'k', track frequency of characters. When window reaches size k, check if it has exactly k-1 distinct characters.
// Time Complexity: O(n), where n is the length of the string. Each character is added and removed from the window at most once.
// Space Complexity: O(1), using a fixed-size frequency array of size 26 for lowercase English letters.
class Solution {
public:
    int substrCount(string& s, int k) {
        int n = s.length();

        vector<int> freq(26, 0);  // frequency array to store count of characters in current window
        int         distinct = 0; // number of distinct characters in current window
        int         result   = 0; // to store final count of valid substrings

        int i = 0;                // window start
        int j = 0;                // window end

        while (j < n) {
            if (freq[s[j] - 'a'] == 0) {
                distinct++;     // new character enters the window
            }
            freq[s[j] - 'a']++; // increment frequency of current character

            if (j - i + 1 > k) {
                // window size exceeded, shrink from left
                freq[s[i] - 'a']--; // remove character at position i
                if (freq[s[i] - 'a'] == 0) {
                    distinct--;     // character completely removed from window
                }
                i++;                // move window start
            }

            if (j - i + 1 == k) {
                // when window size is exactly k
                if (distinct == k - 1) {
                    result++; // valid substring
                }
            }

            j++; // expand window
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "aabab", k = 3
 *
 * Initial values:
 * i = 0, j = 0, freq = all 0s, distinct = 0, result = 0
 *
 * Step-by-step:
 *
 * j = 0 → char = 'a'
 * - freq[a] = 1, distinct = 1 → window = "a" → size < k → continue
 *
 * j = 1 → char = 'a'
 * - freq[a] = 2 → window = "aa" → size < k → continue
 *
 * j = 2 → char = 'b'
 * - freq[b] = 1, distinct = 2 → window = "aab" → size = k
 * - distinct = 2 == k-1 → result = 1
 *
 * j = 3 → char = 'a'
 * - freq[a] = 3 → window = "aaba" → size = 4 > k
 * - shrink from left: i = 1, freq[a] = 2 → window = "aba"
 * - size = 3, distinct = 2 == k-1 → result = 2
 *
 * j = 4 → char = 'b'
 * - freq[b] = 2 → window = "abab" → size = 4 > k
 * - shrink from left: i = 2, freq[a] = 1 → window = "bab"
 * - size = 3, distinct = 2 == k-1 → result = 3
 *
 * End of loop, return result = 3
 *
 * Output: 3
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force. Check every substring of length k, count the number of distinct characters using a frequency array, and check if it equals k - 1.
// Time Complexity: O(n * k), where n is the length of the string and k is the size of the window. We iterate over all substrings of length k and count distinct characters.
// Space Complexity: O(1), using a fixed-size frequency array of 26.
class Solution {
    public int substrCount(String s, int k) {
        int n      = s.length();
        int result = 0;

        for (int i = 0; i <= n - k; i++) {
            int[] freq = new int[26]; // reset frequency array for each substring

            for (int j = i; j < i + k; j++) {
                freq[s.charAt(j) - 'a']++; // count frequency of characters in current substring
            }

            int count = 0;
            for (int l = 0; l < 26; l++) {
                if (freq[l] > 0) {
                    count++; // count distinct characters
                }
            }

            if (count == k - 1) {
                result++; // valid substring
            }
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "aabab", k = 3
 *
 * Substrings of length 3:
 *
 * 1. "aab" → freq[a]=2, freq[b]=1 → distinct=2 → valid → result = 1
 * 2. "aba" → freq[a]=2, freq[b]=1 → distinct=2 → valid → result = 2
 * 3. "bab" → freq[b]=2, freq[a]=1 → distinct=2 → valid → result = 3
 *
 * Final result = 3
 *
 */

// Approach 2: Sliding window with a frequency array. Maintain a window of size 'k', track frequency of characters. When window reaches size k, check if it has exactly k-1 distinct characters.
// Time Complexity: O(n), where n is the length of the string. Each character is added and removed from the window at most once.
// Space Complexity: O(1), using a fixed-size frequency array of size 26 for lowercase English letters.
class Solution {
    public int substrCount(String s, int k) {
        int n = s.length();

        int[] freq = new int[26]; // frequency array to store count of characters in current window
        int distinct = 0;         // number of distinct characters in current window
        int result   = 0;         // to store final count of valid substrings

        int i = 0;                // window start
        int j = 0;                // window end

        while (j < n) {
            if (freq[s.charAt(j) - 'a'] == 0) {
                distinct++;            // new character enters the window
            }
            freq[s.charAt(j) - 'a']++; // increment frequency of current character

            if (j - i + 1 > k) {
                // window size exceeded, shrink from left
                freq[s.charAt(i) - 'a']--; // remove character at position i
                if (freq[s.charAt(i) - 'a'] == 0) {
                    distinct--;            // character completely removed from window
                }
                i++;                       // move window start
            }

            if (j - i + 1 == k) {
                // when window size is exactly k
                if (distinct == k - 1) {
                    result++; // valid substring
                }
            }

            j++; // expand window
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "aabab", k = 3
 *
 * Initial values:
 * i = 0, j = 0, freq = all 0s, distinct = 0, result = 0
 *
 * Step-by-step:
 *
 * j = 0 → char = 'a'
 * - freq[a] = 1, distinct = 1 → window = "a" → size < k → continue
 *
 * j = 1 → char = 'a'
 * - freq[a] = 2 → window = "aa" → size < k → continue
 *
 * j = 2 → char = 'b'
 * - freq[b] = 1, distinct = 2 → window = "aab" → size = k
 * - distinct = 2 == k-1 → result = 1
 *
 * j = 3 → char = 'a'
 * - freq[a] = 3 → window = "aaba" → size = 4 > k
 * - shrink from left: i = 1, freq[a] = 2 → window = "aba"
 * - size = 3, distinct = 2 == k-1 → result = 2
 *
 * j = 4 → char = 'b'
 * - freq[b] = 2 → window = "abab" → size = 4 > k
 * - shrink from left: i = 2, freq[a] = 1 → window = "bab"
 * - size = 3, distinct = 2 == k-1 → result = 3
 *
 * End of loop, return result = 3
 *
 * Output: 3
 *
 */
