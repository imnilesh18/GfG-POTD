/*
 * GfG Link: https://www.geeksforgeeks.org/problems/smallest-distant-window3132/1
 *
 * Smallest distinct window
 *
 * Difficulty: Medium Accuracy: 31.85% Submissions: 101K+ Points: 4
 *
 * Given a string str, your task is to find the length of the smallest window that contains all the characters of the given string at least once.
 *
 * Example:
 *
 * Input: str = "aabcbcdbca"
 * Output: 4
 * Explanation: Sub-String "dbca" has the smallest length that contains all the characters of str.
 *
 * Input: str = "aaab"
 * Output: 2
 * Explanation: Sub-String "ab" has the smallest length that contains all the characters of str.
 *
 * Input: str = "geeksforgeeks"
 * Output: 8
 * Explanation: There are multiple substring with smallest length that contains all characters of str, "geeksfor" and "forgeeks".
 *
 * Constraints:
 * 1 ≤ str.size() ≤ 10^5
 * str contains only lower-case english alphabets.
 */

/************************************************************ C++ ************************************************/

// Approach: Use sliding window and hashing. First, count all distinct characters in the string. Then use two pointers to find the smallest window containing all these characters.
// Time Complexity: O(N) - each character is visited at most twice (once by j and once by i).
// Space Complexity: O(1) - constant space used (only arrays of size 26 for lowercase letters).
class Solution {
public:
    int findSubString(string& str) {
        int n = str.size();

        // to store whether a character is visited or not
        vector<bool> visited(26, false);
        int          distinct = 0;

        // count distinct characters in the string
        for (int i = 0; i < n; i++) {
            if (visited[str[i] - 'a'] == false) {
                visited[str[i] - 'a'] = true;
                distinct++;
            }
        }

        // to store the frequency of characters in the current window
        vector<int> cur(26, 0);
        int         cnt    = 0;   // to count how many unique characters are present in the current window
        int         result = n;   // initialize with maximum possible window size
        int         i = 0, j = 0; // sliding window pointers

        while (j < n) {
            // include current character in the window
            cur[str[j] - 'a']++;

            // if it is the first occurrence in the window
            if (cur[str[j] - 'a'] == 1) {
                cnt++;
            }

            // if current window contains all distinct characters
            while (cnt == distinct) {
                // update the minimum window size
                result = min(result, j - i + 1);

                // exclude the character at start of the window
                cur[str[i] - 'a']--;

                // if a distinct character is removed from the window
                if (cur[str[i] - 'a'] == 0) {
                    cnt--;
                }

                // shrink the window from left
                i++;
            }

            // expand the window from right
            j++;
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: str = "aabcbcdbca"
 * Distinct characters = {a, b, c, d} => 4
 *
 * Step-by-step:
 *
 * j = 0: include 'a' → cur[a]=1 → cnt=1
 * j = 1: include 'a' → cur[a]=2 → cnt=1
 * j = 2: include 'b' → cur[b]=1 → cnt=2
 * j = 3: include 'c' → cur[c]=1 → cnt=3
 * j = 4: include 'b' → cur[b]=2 → cnt=3
 * j = 5: include 'c' → cur[c]=2 → cnt=3
 * j = 6: include 'd' → cur[d]=1 → cnt=4 → all distinct included
 *
 * Now try shrinking from i=0:
 * i = 0: cur[a]=1 → cnt=4 → window = "aabcbcd" → size = 7
 * i = 1: cur[a]=0 → cnt=3 → window broken → result = 7
 *
 * j = 7: include 'b' → cur[b]=3 → cnt=4 not yet
 * j = 8: include 'c' → cur[c]=3
 * j = 9: include 'a' → cur[a]=1 → cnt=4 again
 *
 * Now shrink from i:
 * i = 2: cur[b]=2
 * i = 3: cur[c]=2
 * i = 4: cur[b]=1
 * i = 5: cur[c]=1
 * i = 6: cur[d]=0 → cnt=3 → window = "dbca" → size = 4 → result updated to 4
 *
 * Final result = 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use sliding window and hashing. First, count all distinct characters in the string. Then use two pointers to find the smallest window containing all these characters.
// Time Complexity: O(N) - each character is visited at most twice (once by j and once by i).
// Space Complexity: O(1) - constant space used (only arrays of size 26 for lowercase letters).
class Solution {
    public int findSubString(String str) {
        int n = str.length();

        // to mark visited characters
        boolean[] visited = new boolean[26];
        int distinct = 0;

        // count total distinct characters in the string
        for (int i = 0; i < n; i++) {
            if (!visited[str.charAt(i) - 'a']) {
                visited[str.charAt(i) - 'a'] = true;
                distinct++;
            }
        }

        // to store frequency of characters in current window
        int[] cur = new int[26];
        int cnt    = 0;
        int result = n;
        int i = 0, j = 0;

        while (j < n) {
            // include character at position j
            char ch = str.charAt(j);
            cur[ch - 'a']++;

            // if it's first occurrence in window
            if (cur[ch - 'a'] == 1) {
                cnt++;
            }

            // if current window contains all distinct characters
            while (cnt == distinct) {
                // update minimum window size
                result = Math.min(result, j - i + 1);

                // remove character at position i from window
                char leftChar = str.charAt(i);
                cur[leftChar - 'a']--;

                // if a distinct character is completely removed
                if (cur[leftChar - 'a'] == 0) {
                    cnt--;
                }

                i++; // shrink window from left
            }

            j++; // expand window from right
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: str = "aabcbcdbca"
 * Distinct characters = {a, b, c, d} => 4
 *
 * Step-by-step:
 *
 * j = 0: include 'a' → cur[a]=1 → cnt=1
 * j = 1: include 'a' → cur[a]=2 → cnt=1
 * j = 2: include 'b' → cur[b]=1 → cnt=2
 * j = 3: include 'c' → cur[c]=1 → cnt=3
 * j = 4: include 'b' → cur[b]=2 → cnt=3
 * j = 5: include 'c' → cur[c]=2 → cnt=3
 * j = 6: include 'd' → cur[d]=1 → cnt=4 → all distinct included
 *
 * Shrink from i=0:
 * i = 0: cur[a]=1 → cnt=4 → window = "aabcbcd" → size = 7
 * i = 1: cur[a]=0 → cnt=3 → window broken → result = 7
 *
 * j = 7: include 'b'
 * j = 8: include 'c'
 * j = 9: include 'a' → cur[a]=1 → cnt=4 again
 *
 * Shrink from i=2:
 * i = 2: cur[b]=2
 * i = 3: cur[c]=2
 * i = 4: cur[b]=1
 * i = 5: cur[c]=1
 * i = 6: cur[d]=0 → cnt=3 → window = "dbca" → size = 4 → result updated to 4
 *
 * Final result = 4
 *
 */
