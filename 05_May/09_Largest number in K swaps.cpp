/*
 * Largest number in K swaps
 *
 * Difficulty: Medium Accuracy: 18.84 % Submissions : 114K + Points : 4 Average Time: 30m
 *
 * Given a number k and string s of digits denoting a positive integer, build the largest number possible by performing swap operations on the digits of s at most k times.
 *
 * Examples:
 *
 * Input: s = "1234567", k = 4
 *                        Output : 7654321
 * Explanation:              Three swaps can make the input 1234567 to 7654321, swapping 1 with 7, 2 with 6 and finally 3 with 5.
 *
 * Input: s = "3435335", k = 3
 *                        Output : 5543333
 * Explanation:              Three swaps can make the input 3435335 to 5543333, swapping 3 with 5, 4 with 5 and finally 3 with 4.
 *
 * Input: s = "1034", k = 2
 *                     Output : 4301
 * Explanation:           Two swaps can make the input 1034 to 4301, swapping 1 with 4 and finally 0 with 3.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 15
 * 1 ≤ k ≤ 7
 *
 */

/************************************************************ C++ ************************************************/

// Approach: Use recursive backtracking to generate all permutations by swapping digits to form the largest number within k swaps.
// Time Complexity: O((n^2)^k) in the worst case due to exploring all combinations of swaps up to k levels deep.
// Space Complexity: O(n) due to the recursion stack and string copies.
class Solution {
public:
    string findMax(string& s, int k) {
        // Base case: If no swaps are left, return the current number
        if (k == 0) {
            return s;
        }

        int    n   = s.size();
        string ans = s;

        // Traverse all pairs of characters in the string
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                // Swap only if it increases the value at position i
                if (s[i] < s[j]) {
                    // Perform the swap
                    swap(s[i], s[j]);

                    // Recursive call with one less allowed swap
                    ans = max(ans, findMax(s, k - 1));

                    // Backtrack to the original state
                    swap(s[i], s[j]);
                }
            }
        }

        return ans;
    }
    // Wrapper function to call recursive utility
    string findMaximumNum(string s, int k) {
        return findMax(s, k);
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "1034", k = 2
 * Initial: s = "1034", k = 2
 *
 * Step 1: Try all i=0 swaps
 *   - swap s[0]=1 with s[3]=4 → "4031"
 *   - recurse with k=1
 *     → Try swapping s[0]=4 with s[1]=0, s[2]=3, s[3]=1 → max becomes "4301"
 *     - Backtrack to "1034"
 *
 * Step 2: Try i=1, s[1]=0 with s[2]=3, s[3]=4 → swap s[1] with s[3] gives "1430"
 *   - recurse with k=1 → swap s[2]=3 with s[3]=0 gives "1403"
 *   - Backtrack
 *
 * Final maximum among all: "4301"
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use backtracking with pruning by always trying to place the maximum possible digit at each index.
// Time Complexity: O(n^2) in practice due to pruning (though worst case can be (n^2)^k).
// Space Complexity: O(n) for recursion stack and string builders.
class Solution {
    // Function to keep the maximum result
    static void match(String curr, StringBuilder result) {
        // If current number is lexicographically larger, update result
        if (curr.compareTo(result.toString()) > 0) {
            result.replace(0, result.length(), curr);
        }
    }
    // Function to set highest possible digits at given index
    static void setDigit(StringBuilder s, int index, StringBuilder res, int k) {
        // Base case: If no swaps left or index reaches end, check if current is better
        if (k == 0 || index == s.length() - 1) {
            match(s.toString(), res);
            return;
        }

        int maxDigit = 0;

        // Find the maximum digit from index to end
        for (int i = index; i < s.length(); i++) {
            maxDigit = Math.max(maxDigit, s.charAt(i) - '0');
        }

        // If current index already has max digit, just move to next
        if (s.charAt(index) - '0' == maxDigit) {
            setDigit(s, index + 1, res, k);
            return;
        }

        // Try all swaps with the maxDigit found
        for (int i = index + 1; i < s.length(); i++) {
            // Only consider positions with maxDigit
            if (s.charAt(i) - '0' == maxDigit) {
                // Swap max digit to current index
                char temp = s.charAt(index);
                s.setCharAt(index, s.charAt(i));
                s.setCharAt(i, temp);

                // Recurse for next index with one less swap
                setDigit(s, index + 1, res, k - 1);

                // Backtrack to previous state
                s.setCharAt(i, s.charAt(index));
                s.setCharAt(index, temp);
            }
        }
    }
    // Function to find the largest number after k swaps
    static String findMaximumNum(String s, int k) {
        // Initial result is the input itself
        StringBuilder res = new StringBuilder(s);

        // Start recursive processing from index 0
        setDigit(new StringBuilder(s), 0, res, k);
        return res.toString();
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "1034", k = 2
 *
 * Initial res = "1034"
 *
 * Step 1: index = 0 → maxDigit from [0:] = 4
 *         Swap 1 <-> 4 → "4031", k = 1
 *
 * Step 2: index = 1 → maxDigit from [1:] = 3
 *         Swap 0 <-> 3 → "4301", k = 0
 *
 * Step 3: k == 0 → match("4301", res) → update res = "4301"
 *
 * Backtrack all swaps → explore any remaining options (none better)
 *
 * Final Output: "4301"
 *
 */
