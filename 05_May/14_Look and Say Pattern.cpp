/*
 * GfG Link: https://www.geeksforgeeks.org/problems/decode-the-pattern1138/1
 *
 * Look and Say Pattern
 *
 * Difficulty: Medium Accuracy: 62.54% Submissions: 33K+ Points: 4
 * Given an integer n. Return the nth row of the following look-and-say pattern.
 * 1
 * 11
 * 21
 * 1211
 * 111221
 * Look-and-Say Pattern:
 * To generate a member of the sequence from the previous member, read off the digits of the previous member, counting the number of digits in groups of the same digit. For example:
 *
 * 1 is read off as "one 1" or 11.
 * 11 is read off as "two 1s" or 21.
 * 21 is read off as "one 2, then one 1" or 1211.
 * 1211 is read off as "one 1, one 2, then two 1s" or 111221.
 * 111221 is read off as "three 1s, two 2s, then one 1" or 312211.
 *
 * Examples:
 *
 * Input: n = 5
 * Output: 111221
 * Explanation: The 5th row of the given pattern will be 111221.
 *
 * Input: n = 3
 * Output: 21
 * Explanation: The 3rd row of the given pattern will be 21.
 *
 * Constraints:
 * 1 ≤ n ≤ 30
 */

/*
 * Look and Say Pattern
 *
 * Sequence Progression:
 *   i       -------> 1 (Base Case)
 *   i + 1   -------> 1 times '1' written    -> "11"
 *   i + 2   -------> 2 times '1' written    -> "21"
 *   i + 3   -------> 1 times '2' & 1 times '1'
 *                     -> "12"       + "11" = "1211"
 *   i + 4   -------> 1 times '1' & 1 times '2' & 2 times '1'
 *                     -> "11" + "12" + "21" = "111221"
 *
 * So, n = 4 answer will be "1211"
 *
 * Input : n = 4
 * Output: "1211"
 *
 * Breakdown:
 *   n = 1  -> "1"
 *   n = 2  -> call(n – 1) = "1"  ⇒ 1×'1' → "11"
 *
 *               n = 3
 *               /   "11" → "21" (and so on)
 *              /
 *            n = 2
 *           /     "1" → "11"
 *          /
 *        n = 1
 *
 * Pseudocode:
 * func(n) {
 *     if (n == 1) {
 *         return "1";
 *     }
 *     string say = func(n - 1);
 *     // … run‑length encode `say` …
 * }
 *
 * Example 1: Say = "11"
 *   Indices:    0      1
 *             +-----+-----+
 *     Say[i]: | '1' | '1' |
 *             +-----+-----+
 *                     i=1
 *       ch = '1'
 *       count = 2
 *       result = "2" + '1' → "21"
 *
 * Example 2: Say = "2231"
 *   Indices:    0      1     2     3
 *             +-----+-----+-----+-----+
 *     Say[i]: | '2' | '2' | '3' | '1' |
 *             +-----+-----+-----+-----+
 *                       i=1
 *       ch = '2'
 *       count = 2
 *       result = "2" + '2' → "22"
 *
 *    Indices:    0      1     2     3
 *             +-----+-----+-----+-----+
 *     Say[i]: | '2' | '2' | '3' | '1' |
 *             +-----+-----+-----+-----+
 *                           i=2
 *       ch = '3'
 *       count = 1
 *       result = "22" + "13" → "2213"
 *
 *    Indices:    0      1     2     3
 *             +-----+-----+-----+-----+
 *     Say[i]: | '2' | '2' | '3' | '1' |
 *             +-----+-----+-----+-----+
 *                                 i=3
 *   Then at i=3:
 *       ch = '1'
 *       count = 1
 *       result = "2213" + "11" → "221311"
 */

/************************************************************ C++ ************************************************/

// Approach: Recursively build the sequence and apply run‑length encoding on the previous term.
// Time Complexity: O(2^n) in the worst case due to exponential string growth (n ≤ 30).
// Space Complexity: O(2^n) for recursion stack and storage of intermediate strings.
class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) {                               // Base case: first term is "1"
            return "1";
        }

        string say = countAndSay(n - 1);                           // Recursive call: get the (n‑1)th term
        // Processing:
        string result = "";                                        // Initialize result for the nth term

        for (int i = 0; i < say.length(); i++) {                   // Iterate over the previous term
            char ch    = say[i];                                   // Current character to count
            int  count = 1;                                        // At least one occurrence

            while (i < say.length() - 1 && say[i] == say[i + 1]) { // Count repeats
                count++;                                           // Increment count
                i++;                                               // Move to next character
            }

            result += to_string(count) + string(1, ch);     // Append "<count><char>"
        }

        return result;                             // Return the encoded string
    }
};

/*
 *
 * Dry Run
 *
 * Input: n = 4
 *
 * 1. countAndSay(4)
 *    └─> countAndSay(3)
 *         └─> countAndSay(2)
 *              └─> countAndSay(1) → returns "1"
 *
 * 2. Back to n=2:
 *      say = "1"
 *      for i=0: ch='1', count=1 → result = "11"
 *      return "11"
 *
 * 3. Back to n=3:
 *      say = "11"
 *      for i=0: ch='1', count=2 → result = "21"
 *      return "21"
 *
 * 4. Back to n=4:
 *      say = "21"
 *      i=0: ch='2', count=1 → result = "12"
 *      i=1: ch='1', count=1 → result += "11" → result = "1211"
 *      return "1211"
 *
 * Final Output: "1211"
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Recursively build the sequence and apply run‑length encoding on the previous term.
// Time Complexity: O(2^n) in the worst case due to exponential string growth (n ≤ 30).
// Space Complexity: O(2^n) for recursion stack and storage of intermediate strings.
class Solution {
    public String countAndSay(int n) {
        if (n == 1) { // Base case: first term is "1"
            return "1";
        }

        String        say    = countAndSay(n - 1);  // Recursive call: get the (n-1)th term
        StringBuilder result = new StringBuilder(); // Use StringBuilder for efficiency

        for (int i = 0; i < say.length(); i++) {
            char ch    = say.charAt(i); // Current character to count
            int  count = 1;             // At least one occurrence

            // Count consecutive repeating characters
            while (i < say.length() - 1 && say.charAt(i) == say.charAt(i + 1)) {
                count++;
                i++;
            }

            // Append "<count><char>" to the result
            result.append(count).append(ch);
        }

        return result.toString(); // Return the encoded string
    }
}

/*
 *
 * Dry Run
 *
 * Input: n = 4
 *
 * 1. countAndSay(4)
 *    └─> countAndSay(3)
 *         └─> countAndSay(2)
 *              └─> countAndSay(1) → returns "1"
 *
 * 2. Back to n=2:
 *      say = "1"
 *      for i=0: ch='1', count=1 → result = "11"
 *      return "11"
 *
 * 3. Back to n=3:
 *      say = "11"
 *      for i=0: ch='1', count=2 → result = "21"
 *      return "21"
 *
 * 4. Back to n=4:
 *      say = "21"
 *      i=0: ch='2', count=1 → result = "12"
 *      i=1: ch='1', count=1 → result += "11" → result = "1211"
 *      return "1211"
 *
 * Final Output: "1211"
 *
 */
