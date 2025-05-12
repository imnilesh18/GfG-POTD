/*
 * GfG Link: https://www.geeksforgeeks.org/problems/ncr1019/1
 *
 * nCr
 *
 * Difficulty: Medium Accuracy: 14.82% Submissions: 320K+ Points: 4
 *
 * Given two integer values n and r, the task is to find the value of Binomial Coefficient nCr
 *
 * A binomial coefficient nCr can be defined as the coefficient of xr in the expansion of (1 + x)n that gives the number of ways to choose r objects from a set of n objects without considering the order.
 * The binomial coefficient nCr is calculated as : C(n,r) = n! / r! * (n-r) !
 * Note: If r is greater than n, return 0.
 * It is guaranteed that the value of nCr will fit within a 32-bit integer.
 *
 * Examples:
 *
 * Input: n = 5, r = 2
 * Output: 10
 * Explaination: The value of 5C2 is calculated as 5!/(5−2)!*2! = 5!/3!*2! = 10.
 *
 * Input: n = 2, r = 4
 * Output: 0
 * Explaination: Since r is greater than n, thus 2C4 = 0
 *
 * Input: n = 5, r = 0
 * Output: 1
 * Explaination: The value of 5C0 is calculated as 5!/(5−0)!*0! = 5!/5!*0! = 1.
 *
 * Constraints:
 * 1 ≤ n ≤ 100
 * 1 ≤ r ≤ 100
 */

/************************************************************ C++ ************************************************/

// Approach: Use optimized multiplicative formula to compute nCr without full factorials. Compute in O(r) by multiplying r terms from numerator and denominator.
// Time Complexity: O(r) - Loop runs r times to compute the coefficient.
// Space Complexity: O(1) - Uses only constant space for variables.
class Solution {
public:
    int nCr(int n, int r) {
        if (r > n) {
            return 0;         // If r > n, binomial coefficient is 0
        }

        if (r > n - r) {
            r = n - r;   // Use symmetry: nCr == nC(n - r)
        }

        long long result = 1; // Initialize result as 1, using long long to prevent overflow

        // Apply the multiplicative formula: nCr = n*(n-1)*...*(n-r+1) / r!
        for (int i = 0; i < r; i++) {
            result *= (n - i);      // Multiply numerator part
            result /= (i + 1);      // Divide by denominator part
        }

        return result;  // Return final computed nCr
    }
};

/*
 *
 * Dry Run
 * Input: n = 6, r = 2
 * Step 1: result = 1
 * Step 2: i = 0 → result = result * (6 - 0) / (0 + 1) = 1 * 6 / 1 = 6
 * Step 3: i = 1 → result = result * (6 - 1) / (1 + 1) = 6 * 5 / 2 = 30 / 2 = 15
 * Final result = 15
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use optimized multiplicative formula to compute nCr without full factorials. Compute in O(r) by multiplying r terms from numerator and denominator.
// Time Complexity: O(r) - Loop runs r times to compute the coefficient.
// Space Complexity: O(1) - Uses only constant space for variables.
class Solution {
    public int nCr(int n, int r) {
        if (r > n) {
            return 0;        // If r > n, binomial coefficient is 0
        }

        if (r > n - r) {
            r = n - r;   // Use symmetry: nCr == nC(n - r)
        }

        long result = 1; // Use long to prevent overflow during multiplication

        // Apply the multiplicative formula: nCr = n*(n-1)*...*(n-r+1) / r!
        for (int i = 0; i < r; i++) {
            result *= (n - i);      // Multiply numerator
            result /= (i + 1);      // Divide by denominator
        }

        return (int)result; // Return result as int (given constraint: fits in 32-bit int)
    }
}

/*
 *
 * Dry Run
 * Input: n = 6, r = 2
 * Step 1: result = 1
 * Step 2: i = 0 → result = result * (6 - 0) / (0 + 1) = 1 * 6 / 1 = 6
 * Step 3: i = 1 → result = result * (6 - 1) / (1 + 1) = 6 * 5 / 2 = 30 / 2 = 15
 * Final result = 15
 *
 */
