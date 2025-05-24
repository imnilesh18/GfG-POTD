/*
 * GfG Link: https://www.geeksforgeeks.org/problems/sum-of-all-substrings-of-a-number-1587115621/1
 *
 * Sum of all substrings of a number
 *
 * Difficulty: Medium Accuracy: 38.11% Submissions: 58K+ Points: 4
 *
 * Given an integer s represented as a string, the task is to get the sum of all possible sub-strings of this string.
 *
 * Note: The number may have leading zeros.
 * It is guaranteed that the total sum will fit within a 32-bit signed integer.
 *
 * Examples:
 *
 * Input: s = "6759"
 * Output: 8421
 * Explanation:
 * Sum = 6 + 7 + 5 + 9 + 67 + 75 + 59 + 675 + 759 + 6759 = 8421
 *
 * Input: s = "421"
 * Output: 491
 * Explanation:
 * Sum = 4 + 2 + 1 + 42 + 21 + 421 = 491
 *
 * Constraints:
 * 1 <= |s| <= 9
 */

/************************************************************ C++ ************************************************/

// Approach: Use dynamic computation by iterating from right to left, maintaining a running multiplier (place_value) to capture the weight of each digit across all substrings it contributes to.
// Time Complexity: O(n) – Each character is processed once in a single loop.
// Space Complexity: O(1) – Only a few variables are used for calculations, no extra space required.
class Solution {
public:
    int sumSubstrings(string& s) {
        int n = s.length();

        int place_value = 1; // Multiplier that keeps track of place values for contribution
        int sum         = 0; // Final sum of all substrings

        for (int i = n - 1; i >= 0; i--) {
            int digit = s[i] - '0'; // Convert character to integer

            // Add contribution of current digit to sum
            sum += digit * (i + 1) * place_value;

            // Update the place value for the next digit (towards left)
            place_value = place_value * 10 + 1;
        }

        return sum; // Return the total sum of all substrings
    }
};

/*
 *
 * Dry Run
 * Input: s = "123"
 *
 * i = 2, digit = 3
 *   sum = 3 * (2+1) * 1 = 9
 *   place_value = 1 * 10 + 1 = 11
 *
 * i = 1, digit = 2
 *   sum = 9 + 2 * (1+1) * 11 = 9 + 44 = 53
 *   place_value = 11 * 10 + 1 = 111
 *
 * i = 0, digit = 1
 *   sum = 53 + 1 * (0+1) * 111 = 53 + 111 = 164
 *
 * Final sum = 164
 *
 * Substrings of "123": 1, 2, 3, 12, 23, 123
 * Sum: 1 + 2 + 3 + 12 + 23 + 123 = 164 ✅
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use dynamic computation by iterating from right to left, maintaining a running multiplier (placeValue) to capture the weight of each digit across all substrings it contributes to.
// Time Complexity: O(n) – Each character is processed once in a single loop.
// Space Complexity: O(1) – Only a few variables are used for calculations, no extra space required.
class Solution {
    public static int sumSubstrings(String s) {
        int n = s.length();

        int place_value = 1; // Multiplier to keep track of how many times a digit contributes
        int sum         = 0; // Final sum of all substrings

        for (int i = n - 1; i >= 0; i--) {
            int digit = s.charAt(i) - '0'; // Convert character to integer

            // Add the contribution of the current digit
            sum += digit * (i + 1) * place_value;

            // Update the place value for next iteration
            place_value = place_value * 10 + 1;
        }

        return sum; // Return the total sum
    }
}

/*
 *
 * Dry Run
 * Input: s = "123"
 *
 * i = 2, digit = 3
 *   sum = 3 * (2+1) * 1 = 9
 *   placeValue = 1 * 10 + 1 = 11
 *
 * i = 1, digit = 2
 *   sum = 9 + 2 * (1+1) * 11 = 9 + 44 = 53
 *   placeValue = 11 * 10 + 1 = 111
 *
 * i = 0, digit = 1
 *   sum = 53 + 1 * (0+1) * 111 = 53 + 111 = 164
 *
 * Final sum = 164
 *
 * Substrings of "123": 1, 2, 3, 12, 23, 123
 * Sum: 1 + 2 + 3 + 12 + 23 + 123 = 164 ✅
 *
 */
