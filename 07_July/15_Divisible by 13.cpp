/*
 * GfG Link: https://www.geeksforgeeks.org/problems/divisible-by-13/1
 *
 * Divisible by 13
 *
 * Difficulty: Medium Accuracy: 50.24% Submissions: 16K+ Points: 4
 *
 * Given a number represented as a string s (which may be very large), check whether it is divisible by 13 or not.
 *
 * Examples:
 *
 * Input : s = "2911285"
 * Output : true
 * Explanation: 2911285 / 13 = 223945, which is a whole number with no remainder.
 *
 * Input : s = "27"
 * Output : false
 * Explanation: 27 / 13 ≈ 2.0769..., which is not a whole number (there is a remainder).
 *
 * Constraints:
 * 1 ≤  s.size()  ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: 1 Convert the decimal string to an integer using stoi and check num % 13 == 0
// Time Complexity: O(n) for parsing the string of length n into an integer
// Space Complexity: O(1) extra space (ignoring input storage)
class Solution {
public:
    bool divby13(string& s) {
        // Convert the string to an integer
        int num = stoi(s);

        // Check if the number is divisible by 13
        return num % 13 == 0;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "2911285"
 *   stoi(s)       => 2911285
 *   2911285 % 13  => 0   // true
 *
 * Input: s = "27"
 *   stoi(s)       => 27
 *   27 % 13       => 1   // false
 */

// Approach 2: Compute remainder by processing digits one by one to avoid large integer conversion; use rem = (rem*10 + digit) % 13
// Time Complexity: O(n) where n = s.size()
// Space Complexity: O(1) extra space
class Solution {
public:
    bool divby13(string& s) {
        // Stores running remainder
        int rem = 0;

        // Process each digit and compute remainder modulo 13
        for (char ch : s) {
            rem = (rem * 10 + (ch - '0')) % 13;
        }

        // Final check for divisibility
        return rem == 0;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "2911285"
 *   rem = 0
 *   ch = '2' -> rem = (0*10 + 2) % 13 = 2
 *   ch = '9' -> rem = (2*10 + 9) % 13 = 29 % 13 = 3
 *   ch = '1' -> rem = (3*10 + 1) % 13 = 31 % 13 = 5
 *   ch = '1' -> rem = (5*10 + 1) % 13 = 51 % 13 = 12
 *   ch = '2' -> rem = (12*10 + 2) % 13 = 122 % 13 = 5
 *   ch = '8' -> rem = (5*10 + 8) % 13 = 58 % 13 = 6
 *   ch = '5' -> rem = (6*10 + 5) % 13 = 65 % 13 = 0   // true
 *
 * Input: s = "27"
 *   rem = 0
 *   ch = '2' -> rem = (0*10 + 2) % 13 = 2
 *   ch = '7' -> rem = (2*10 + 7) % 13 = 27 % 13 = 1  // false
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Convert the decimal string to an integer using Integer.parseInt and check num % 13 == 0
// Time Complexity: O(n) for parsing the string of length n into an integer
// Space Complexity: O(1) extra space (ignoring input storage)
class Solution {
    public boolean divby13(String s) {
        // Convert the string to an integer
        int num = Integer.parseInt(s);

        // Check if the number is divisible by 13
        return num % 13 == 0;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "2911285"
 *   Integer.parseInt(s) => 2911285
 *   2911285 % 13       => 0   // true
 *
 * Input: s = "27"
 *   Integer.parseInt(s) => 27
 *   27 % 13            => 1   // false
 */

// Approach 2: Compute remainder by processing each character digit and using modulo arithmetic to avoid large integer conversion
// Time Complexity: O(n) where n = s.length()
// Space Complexity: O(1) extra space
class Solution {
    public boolean divby13(String s) {
        // Stores running remainder
        int rem = 0;

        // Process each digit and compute remainder modulo 13
        for (char ch : s.toCharArray()) {
            rem = (rem * 10 + (ch - '0')) % 13;
        }

        // Final check for divisibility
        return rem == 0;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "2911285"
 *   rem = 0
 *   ch = '2' -> rem = (0*10 + 2) % 13 = 2
 *   ch = '9' -> rem = (2*10 + 9) % 13 = 29 % 13 = 3
 *   ch = '1' -> rem = (3*10 + 1) % 13 = 31 % 13 = 5
 *   ch = '1' -> rem = (5*10 + 1) % 13 = 51 % 13 = 12
 *   ch = '2' -> rem = (12*10 + 2) % 13 = 122 % 13 = 5
 *   ch = '8' -> rem = (5*10 + 8) % 13 = 58 % 13 = 6
 *   ch = '5' -> rem = (6*10 + 5) % 13 = 65 % 13 = 0   // true
 *
 * Input: s = "27"
 *   rem = 0
 *   ch = '2' -> rem = (0*10 + 2) % 13 = 2
 *   ch = '7' -> rem = (2*10 + 7) % 13 = 27 % 13 = 1   // false
 */
