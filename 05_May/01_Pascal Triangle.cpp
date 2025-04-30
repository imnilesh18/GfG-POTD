/*
 * Pascal Triangle
 *
 * Difficulty: Medium Accuracy: 23.68% Submissions: 118K+ Points: 4 Average Time: 20m
 *
 * Given a positive integer n, return the nth row of pascal's triangle.
 * Pascal's triangle is a triangular array of the binomial coefficients formed by summing up the elements of previous row.
 *
 * Examples:
 *
 * Input: n = 4
 * Output: [1, 3, 3, 1]
 * Explanation: 4th row of pascal's triangle is [1, 3, 3, 1].
 *
 * Input: n = 5
 * Output: [1, 4, 6, 4, 1]
 * Explanation: 5th row of pascal's triangle is [1, 4, 6, 4, 1].
 *
 * Input: n = 1
 * Output: [1]
 * Explanation: 1st row of pascal's triangle is [1].
 *
 * Constraints:
 * 1 ≤ n ≤ 20
 */

/************************************************************ C++ ************************************************/

// Approach: Use Binomial Coefficient formula to generate nth row directly: C(n-1, 0), C(n-1, 1), ..., C(n-1, n-1)
// Time Complexity: O(n), as we compute n elements using the iterative binomial coefficient formula.
// Space Complexity: O(n), for storing the result vector.
class Solution {
public:
    vector<int> nthRowOfPascalTriangle(int n) {
        vector<int> result;        // To store the nth row of Pascal's Triangle

        result.push_back(1);       // First element is always 1

        long long ans = 1;         // Used to compute binomial coefficients iteratively
        for (int col = 1; col < n; col++) {
            ans = ans * (n - col); // Multiply with (n - col) for numerator part of binomial
            ans = ans / col;       // Divide by col for denominator part of binomial
            result.push_back(ans); // Append the computed coefficient
        }
        return result;             // Return the final nth row
    }
};

/*
 *
 * Dry Run
 * Input: n = 5
 * Step 1: Initialize result = [1], ans = 1
 * col = 1: ans = 1 * (5-1) = 4, ans = 4 / 1 = 4 → result = [1, 4]
 * col = 2: ans = 4 * (5-2) = 12, ans = 12 / 2 = 6 → result = [1, 4, 6]
 * col = 3: ans = 6 * (5-3) = 12, ans = 12 / 3 = 4 → result = [1, 4, 6, 4]
 * col = 4: ans = 4 * (5-4) = 4, ans = 4 / 4 = 1 → result = [1, 4, 6, 4, 1]
 * Final Output: [1, 4, 6, 4, 1]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Binomial Coefficient to calculate each element of the nth row directly as C(n-1, k)
// Time Complexity: O(n), since we compute each coefficient in a single pass using previous value
// Space Complexity: O(n), for storing the result list of size n
class Solution {
    ArrayList<Integer> nthRowOfPascalTriangle(int n) {
        ArrayList<Integer> result = new ArrayList<>(); // To store nth row

        result.add(1);                                 // First element is always 1

        long ans = 1;                                  // Will hold the binomial coefficient
        for (int col = 1; col < n; col++) {
            ans = ans * (n - col);                     // Multiply with (n - col)
            ans = ans / col;                           // Divide by col to get next coefficient
            result.add((int)ans);                      // Add to result list after typecast
        }

        return result; // Return the constructed row
    }
}

/*
 *
 * Dry Run
 * Input: n = 5
 * Initial result = [1], ans = 1
 * col = 1: ans = 1 * (5-1) = 4 → 4 / 1 = 4 → result = [1, 4]
 * col = 2: ans = 4 * (5-2) = 12 → 12 / 2 = 6 → result = [1, 4, 6]
 * col = 3: ans = 6 * (5-3) = 12 → 12 / 3 = 4 → result = [1, 4, 6, 4]
 * col = 4: ans = 4 * (5-4) = 4 → 4 / 4 = 1 → result = [1, 4, 6, 4, 1]
 * Final Output: [1, 4, 6, 4, 1]
 *
 */
