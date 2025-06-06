/*
 * GfG Link: https://www.geeksforgeeks.org/problems/search-pattern-rabin-karp-algorithm--141631/1
 *
 * Search Pattern (Rabin-Karp Algorithm)
 *
 * Difficulty: Medium Accuracy: 34.53% Submissions: 74K+ Points: 4 Average Time: 20m
 *
 * Given two strings:
 * A text string in which you want to search.
 * A pattern string that you are looking for within the text.
 * Return all positions (1-based indexing) where the pattern occurs as a substring in the text. If the pattern does not occur, return an empty list.
 * All characters in both strings are lowercase English letters (a to z).
 *
 * Examples:
 *
 * Input: text = "birthdayboy", pattern = "birth"
 * Output: [1]
 * Explanation: The string "birth" occurs at index 1 in text.
 *
 * Input: text = "geeksforgeeks", pattern = "geek"
 * Output: [1, 9]
 * Explanation: The string "geek" occurs twice in text, one starts are index 1 and the other at index 9.
 *
 * Constraints:
 * 1<= text.size() <=5*10^5
 * 1<= pattern.size() <= text.size()
 */

/************************************************************ C++ ************************************************/

// Approach: Rabin-Karp algorithm using rolling hash. Compute hash of pattern and compare it with rolling hash of substrings in text. If hashes match, verify with character comparison to avoid hash collision.
// Time Complexity: O(n + m) on average, where n = length of text and m = length of pattern; worst-case is O(nm) in case of hash collisions.
// Space Complexity: O(1) excluding result vector, as only a few variables are used for hashing.
class Solution {
public:
    // Helper function to compare pattern with substring of text at index idx
    bool isMatch(string& txt, string& pat, int idx) {
        for (int i = 0; i < pat.size(); i++) {
            if (txt[idx + i] != pat[i]) {
                return false;
            }
        }
        return true;
    }
    vector<int> search(string& pat, string& txt) {
        int m = pat.size();  // Length of pattern
        int n = txt.size();  // Length of text

        int base = 26;       // Base for hash (26 lowercase letters)
        int mod  = 101;      // A prime modulus to avoid overflow and reduce collisions

        vector<int> result;
        int         patHash = 0; // Hash value for pattern
        int         txtHash = 0; // Rolling hash value for text
        int         power   = 1; // Power of base (base^i)

        // Compute initial hash for pattern and first window of text
        for (int i = m - 1; i >= 0; i--) {
            int patVal = pat[i] - 'a' + 1;
            int txtVal = txt[i] - 'a' + 1;

            patHash = (patHash + patVal * power) % mod;
            txtHash = (txtHash + txtVal * power) % mod;
            power   = (power * base) % mod;
        }

        // Compare first window hash
        if (txtHash == patHash && isMatch(txt, pat, 0)) {
            result.push_back(1); // Store 1-based index
        }

        // Precompute highest power for sliding window (base^(m-1))
        int highestPower = 1;
        for (int i = 1; i < m; i++) {
            highestPower = (highestPower * base) % mod;
        }

        // Slide window across text
        for (int i = 1; i <= n - m; i++) {
            int leftVal = txt[i - 1] - 'a' + 1;

            // Remove leftmost character from hash
            txtHash = (txtHash - (leftVal * highestPower) % mod + mod) % mod;
            txtHash = (txtHash * base) % mod;

            // Add new character to hash
            int newVal = txt[i + m - 1] - 'a' + 1;
            txtHash = (txtHash + newVal) % mod;

            // If hashes match, verify with character comparison
            if (txtHash == patHash && isMatch(txt, pat, i)) {
                result.push_back(i + 1); // Store 1-based index
            }
        }

        return result;
    }
};

/*
 * Dry Run 1
 *
 * Input: text = "geeksforgeeks", pattern = "geek"
 *
 * Step 1: Initialize
 * pat = "geek", txt = "geeksforgeeks"
 * m = 4, n = 13, base = 26, mod = 101
 *
 * Step 2: Calculate hash for pat and first 4 characters of text
 * patHash = hash("geek") = (g*26^3 + e*26^2 + e*26^1 + k*26^0) % 101
 * txtHash = hash("geek") = same calculation
 * --> patHash == txtHash => isMatch => true => result.push_back(1)
 *
 * Step 3: Slide window:
 * i = 1 → window = "eeks"
 *  Remove 'g', add 's'
 *  txtHash ≠ patHash → skip
 * i = 2 → window = "eksf"
 *  Remove 'e', add 'f'
 *  txtHash ≠ patHash → skip
 * ...
 * i = 8 → window = "geek"
 *  Remove 's', add 'k'
 *  txtHash == patHash => isMatch => true => result.push_back(9)
 *
 * Final result: [1, 9]
 *
 * Dry Run 2
 *
 * Input:
 * text = "ccccbcccb"
 * pattern = "cccb"
 *
 * Step 1: Initialize
 * m = 4 (pattern length)
 * n = 9 (text length)
 * base = 26, mod = 101
 *
 * Step 2: Compute initial pattern hash and text hash for first window
 *
 * Pattern = "cccb" → values = c(3), c(3), c(3), b(2)
 * → patHash = 3*26^3 + 3*26^2 + 3*26^1 + 2*26^0
 *
 * First window in text = "cccc" → c(3), c(3), c(3), c(3)
 * → txtHash = 3*26^3 + 3*26^2 + 3*26^1 + 3*26^0
 *
 * ⇒ patHash ≠ txtHash ⇒ not a match
 *
 * Step 3: Slide the window across the text
 *
 * i = 1 → window = "cccb"
 * - Remove 'c', add 'b'
 * - New hash = matches patHash
 * - Call isMatch(text, pattern, 1)
 *  → text[1..4] = "cccb" == pattern → ✅ match
 * → result.push_back(2) [1-based index]
 *
 * i = 2 → window = "cbcc"
 * - Remove 'c', add 'c'
 * - Hash ≠ patHash → skip
 *
 * i = 3 → window = "bccb"
 * - Remove 'c', add 'b'
 * - Hash ≠ patHash → skip
 *
 * i = 4 → window = "cccb"
 * - Remove 'b', add 'b'
 * - Hash = patHash
 * - Call isMatch(text, pattern, 4)
 *  → text[4..7] = "cccb" == pattern → ✅ match
 * → result.push_back(5)
 *
 * i = 5 → window = "cccb"
 * - Remove 'c', add 'b'
 * - Hash = patHash
 * - Call isMatch(text, pattern, 5)
 *  → text[5..8] = "cccb" == pattern → ✅ match
 * → result.push_back(6)
 *
 * Final result: [2, 6]
 */

/************************************************************ JAVA ************************************************/

// Approach: Rabin-Karp algorithm using rolling hash. Compute hash of pattern and compare it with rolling hash of substrings in text. If hashes match, verify with character comparison to avoid hash collision.
// Time Complexity: O(n + m) on average, where n = length of text and m = length of pattern; worst-case is O(nm) in case of hash collisions.
// Space Complexity: O(1) excluding result vector, as only a few variables are used for hashing.
class Solution {
    // Helper function to compare pattern with substring of text at index idx
    private boolean isMatch(String txt, String pat, int idx) {
        for (int i = 0; i < pat.length(); i++) {
            if (txt.charAt(idx + i) != pat.charAt(i)) {
                return false;
            }
        }
        return true;
    }
    ArrayList<Integer> search(String pat, String txt) {
        int m = pat.length(); // Length of pattern
        int n = txt.length(); // Length of text

        int base = 26;        // Base for hash (26 lowercase letters)
        int mod  = 101;       // A prime modulus to avoid overflow and reduce collisions

        ArrayList<Integer> result = new ArrayList<>();
        int patHash = 0; // Hash value for pattern
        int txtHash = 0; // Rolling hash value for text
        int power   = 1; // Power of base (base^i)

        // Compute initial hash for pattern and first window of text
        for (int i = m - 1; i >= 0; i--) {
            int patVal = pat.charAt(i) - 'a' + 1;
            int txtVal = txt.charAt(i) - 'a' + 1;

            patHash = (patHash + patVal * power) % mod;
            txtHash = (txtHash + txtVal * power) % mod;
            power   = (power * base) % mod;
        }

        // Compare first window hash
        if (txtHash == patHash && isMatch(txt, pat, 0)) {
            result.add(1); // Store 1-based index
        }

        // Precompute highest power for sliding window (base^(m-1))
        int highestPower = 1;
        for (int i = 1; i < m; i++) {
            highestPower = (highestPower * base) % mod;
        }

        // Slide window across text
        for (int i = 1; i <= n - m; i++) {
            int leftVal = txt.charAt(i - 1) - 'a' + 1;

            // Remove leftmost character from hash
            txtHash = (txtHash - (leftVal * highestPower) % mod + mod) % mod;
            txtHash = (txtHash * base) % mod;

            // Add new character to hash
            int newVal = txt.charAt(i + m - 1) - 'a' + 1;
            txtHash = (txtHash + newVal) % mod;

            // If hashes match, verify with character comparison
            if (txtHash == patHash && isMatch(txt, pat, i)) {
                result.add(i + 1); // Store 1-based index
            }
        }

        return result;
    }
}

/*
 * Dry Run 1
 *
 * Input: text = "geeksforgeeks", pattern = "geek"
 *
 * Step 1: Initialize
 * pat = "geek", txt = "geeksforgeeks"
 * m = 4, n = 13, base = 26, mod = 101
 *
 * Step 2: Calculate hash for pat and first 4 characters of text
 * patHash = hash("geek") = (g*26^3 + e*26^2 + e*26^1 + k*26^0) % 101
 * txtHash = hash("geek") = same calculation
 * --> patHash == txtHash => isMatch => true => result.push_back(1)
 *
 * Step 3: Slide window:
 * i = 1 → window = "eeks"
 *  Remove 'g', add 's'
 *  txtHash ≠ patHash → skip
 * i = 2 → window = "eksf"
 *  Remove 'e', add 'f'
 *  txtHash ≠ patHash → skip
 * ...
 * i = 8 → window = "geek"
 *  Remove 's', add 'k'
 *  txtHash == patHash => isMatch => true => result.push_back(9)
 *
 * Final result: [1, 9]
 *
 * Dry Run 2
 *
 * Input:
 * text = "ccccbcccb"
 * pattern = "cccb"
 *
 * Step 1: Initialize
 * m = 4 (pattern length)
 * n = 9 (text length)
 * base = 26, mod = 101
 *
 * Step 2: Compute initial pattern hash and text hash for first window
 *
 * Pattern = "cccb" → values = c(3), c(3), c(3), b(2)
 * → patHash = 3*26^3 + 3*26^2 + 3*26^1 + 2*26^0
 *
 * First window in text = "cccc" → c(3), c(3), c(3), c(3)
 * → txtHash = 3*26^3 + 3*26^2 + 3*26^1 + 3*26^0
 *
 * ⇒ patHash ≠ txtHash ⇒ not a match
 *
 * Step 3: Slide the window across the text
 *
 * i = 1 → window = "cccb"
 * - Remove 'c', add 'b'
 * - New hash = matches patHash
 * - Call isMatch(text, pattern, 1)
 *  → text[1..4] = "cccb" == pattern → ✅ match
 * → result.push_back(2) [1-based index]
 *
 * i = 2 → window = "cbcc"
 * - Remove 'c', add 'c'
 * - Hash ≠ patHash → skip
 *
 * i = 3 → window = "bccb"
 * - Remove 'c', add 'b'
 * - Hash ≠ patHash → skip
 *
 * i = 4 → window = "cccb"
 * - Remove 'b', add 'b'
 * - Hash = patHash
 * - Call isMatch(text, pattern, 4)
 *  → text[4..7] = "cccb" == pattern → ✅ match
 * → result.push_back(5)
 *
 * i = 5 → window = "cccb"
 * - Remove 'c', add 'b'
 * - Hash = patHash
 * - Call isMatch(text, pattern, 5)
 *  → text[5..8] = "cccb" == pattern → ✅ match
 * → result.push_back(6)
 *
 * Final result: [2, 6]
 */
