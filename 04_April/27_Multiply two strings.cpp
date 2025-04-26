/*
 * Multiply two strings
 *
 * Difficulty: Medium Accuracy: 20.06% Submissions: 223K+ Points: 4 Average Time: 20m
 *
 * Given two numbers as strings s1 and s2. Calculate their Product.
 * Note: The numbers can be negative and You are not allowed to use any built-in function or convert the strings to integers. There can be zeros in the begining of the numbers. You don't need to specify '+' sign in the begining of positive numbers.
 *
 * Examples:
 *
 * Input: s1 = "0033", s2 = "2"
 * Output: "66"
 * Explanation: 33 * 2 = 66
 * Input: s1 = "11", s2 = "23"
 * Output: "253"
 * Explanation: 11 * 23  = 253
 *
 * Input: s1 = "123", s2 = "0"
 * Output: "0"
 * Explanation: Anything multiplied by 0 is equal to 0.
 *
 * Constraints:
 * 1 ≤ s1.size() ≤ 10^3
 * 1 ≤ s2.size() ≤ 10^3
 */

// Intuition:
/*
 * Approach: Using String Manipulation – (m * n) Time and O(m + n) Space
 *
 * The overall idea is to simulate the manual multiplication process using string manipulation and integer arithmetic, while considering the signs of the input numbers and properly handling carries.
 *
 * SchoolMultiply
 * School Multiplication
 *
 * Step By Step implementation:
 *
 * Handling Zeroes:
 * - Return 0 if a=0 or b=0.
 *
 * Handling Negative Numbers:
 * - It checks if the first character of each string is ‘-‘. If either a or b is negative, it toggles the negative flag and removes the negative sign from the respective string.
 *
 * Initialization:
 * - The product list is initialized with zeros, where the length of the list is set to accommodate the potential maximum length of the product string.
 *
 * Nested Loops:
 * - The outer loop iterates through the characters of string b from right to left, treating them as digits.
 * - The inner loop iterates through the characters of string a from right to left, treating them as digits.
 *
 * Multiplying and Carrying:
 * - Within the inner loop, it calculates the product of the current digits from a and b, adds any carry from previous calculations, and updates the corresponding position in the product list.
 * - It also calculates a new carry for the next iteration.
 *
 * Handling carry:
 * - After the inner loop completes, it handles any remaining carry by propagating it to the previous positions in the product list.
 *
 * Constructing Result:
 * - It constructs a result string res by joining the elements of the product list.
 * - It removes any leading zeros from the res string.
 * - If the negative flag is set, it adds a negative sign to the res string.
 *
 * Finally, it returns the res string, which represents the product of the two input numbers.
 */

/************************************************************ C++ ************************************************/

// Approach: Using String Manipulation – (n * m) Time and (n + m) Space
// Time Complexity: O(n * m) where n = s1.size(), m = s2.size(), because every digit of s1 is multiplied with every digit of s2
// Space Complexity: O(n + m) to store the intermediate and final result
class Solution {
public:
    /*You are required to complete below function */
    string multiplyStrings(string& s1, string& s2) {
        int n1 = s1.size(), n2 = s2.size();

        if (n1 == 0 || n2 == 0) {
            return "0";
        }

        // check if string are negative
        int nn = 1, mm = 1;
        if (s1[0] == '-') {
            nn = -1;
        }
        if (s2[0] == '-') {
            mm = -1;
        }

        int isNeg = nn * mm;   // determine if result will be negative

        // will keep the result number in vector in reverse order
        vector<int> result(n1 + n2, 0);

        // index by s1
        int i1 = 0;

        // index by s2
        int i2 = 0;

        // go from right to left by s1
        for (int i = n1 - 1; i >= 0; i--) {
            if (s1[i] == '-') {
                continue;
            }
            int carry = 0;
            int n1    = s1[i] - '0';
            i2 = 0;

            // go from right to left by s2
            for (int j = n2 - 1; j >= 0; j--) {
                if (s2[j] == '-') {
                    continue;
                }
                int n2 = s2[j] - '0';

                // multiply and add this result to the existing result
                int sum = n1 * n2 + result[i1 + i2] + carry;

                // carry for next iteration
                carry = sum / 10;

                // store result
                result[i1 + i2] = sum % 10;

                i2++;
            }

            // store carry in next cell
            if (carry > 0) {
                result[i1 + i2] += carry;
            }

            i1++;
        }

        // ignore '0's from the right
        int i = result.size() - 1;
        while (i >= 0 && result[i] == 0) {
            i--;
        }

        // if all were '0's - means either both or one of s1 or s2 were '0'
        if (i == -1) {
            return "0";
        }

        // generate the result string
        string s = "";

        while (i >= 0) {
            s += to_string(result[i--]);
        }

        // if negative
        if (isNeg == -1) {
            s = "-" + s;
        }

        return s;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s1 = "0033", s2 = "2"
 *
 * - Step 1: Remove leading zeros → s1 becomes "33", s2 remains "2".
 * - Step 2: Both are positive, no sign change needed.
 * - Step 3: Initialize result vector of size 2 + 1 = 3 → result = [0, 0, 0]
 * - Step 4: Start multiplying from last digit:
 *  - i = 1 (s1[i] = 3), j = 0 (s2[j] = 2)
 *      -> 3 * 2 = 6
 *      -> result[0] += 6 → result = [6, 0, 0]
 *
 *  - i = 0 (s1[i] = 3), j = 0 (s2[j] = 2)
 *      -> 3 * 2 = 6
 *      -> result[1] += 6 → result = [6, 6, 0]
 * - Step 5: No carry remains.
 * - Step 6: Ignore leading 0 at the end.
 * - Step 7: Build result string from end to start → "66"
 *
 * Final Output: "66"
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Using String Manipulation – (m * n) Time and O(m + n) Space
// Time Complexity: O(m * n), where m and n are the lengths of the strings. Each digit of one number is multiplied with every digit of the other.
// Space Complexity: O(m + n), to store the intermediate and final results in an array of size m+n.
class Solution {
    public String multiplyStrings(String s1, String s2) {
        int n1 = s1.length(), n2 = s2.length();

        // If any string is empty, return "0"
        if (n1 == 0 || n2 == 0) {
            return "0";
        }

        // Check if strings are negative
        int nn = 1, mm = 1;
        if (s1.charAt(0) == '-') {
            nn = -1;
        }
        if (s2.charAt(0) == '-') {
            mm = -1;
        }

        int isNeg = nn * mm; // Determine final sign of result

        // Array to store result digits
        int[] result = new int[n1 + n2];

        int i1 = 0; // Index for s1
        int i2 = 0; // Index for s2

        // Traverse from right to left of s1
        for (int i = n1 - 1; i >= 0; i--) {
            if (s1.charAt(i) == '-') {
                continue; // Skip negative sign
            }
            int carry   = 0;
            int n1Digit = s1.charAt(i) - '0'; // Convert char to digit
            i2 = 0;

            // Traverse from right to left of s2
            for (int j = n2 - 1; j >= 0; j--) {
                if (s2.charAt(j) == '-') {
                    continue;                     // Skip negative sign
                }
                int n2Digit = s2.charAt(j) - '0'; // Convert char to digit

                // Multiply digits and add carry + existing result
                int sum = n1Digit * n2Digit + result[i1 + i2] + carry;

                // Calculate carry for next step
                carry = sum / 10;

                // Store the current digit
                result[i1 + i2] = sum % 10;

                i2++;
            }

            // If any carry left after inner loop
            if (carry > 0) {
                result[i1 + i2] += carry;
            }

            i1++;
        }

        // Skip leading zeros
        int i = result.length - 1;
        while (i >= 0 && result[i] == 0) {
            i--;
        }

        // If all digits are zero
        if (i == -1) {
            return "0";
        }

        // Build the result string
        String s = "";
        while (i >= 0) {
            s += Integer.toString(result[i--]);
        }

        // Apply negative sign if needed
        if (isNeg == -1) {
            s = "-" + s;
        }

        return s;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s1 = "0033", s2 = "2"
 * Step 1: After ignoring leading zeros -> s1 = "33", s2 = "2"
 * Step 2: Both positive, so isNeg = 1
 * Step 3: result array of size 4 initialized to {0, 0, 0, 0}
 * Step 4:
 * - Multiply 3 (from s1) * 2 (from s2) = 6
 * - Add to result[0] -> result[0] = 6
 * - Multiply next 3 (from s1) * 2 (from s2) = 6
 * - Add to result[1] -> result[1] = 6
 * Step 5: Result array becomes {6,6,0,0}
 * Step 6: Read result array in reverse -> "66"
 * Final Output: "66"
 *
 */
