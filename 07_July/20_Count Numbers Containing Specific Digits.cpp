/*
 * GfG Link: https://www.geeksforgeeks.org/problems/count-numbers-containing-specific-digits/1
 *
 * Count Numbers Containing Specific Digits
 *
 * Difficulty: Medium Accuracy: 20.0% Submissions: 20+ Points: 4 Average Time: 25m
 *
 * You are given an integer n representing the number of digits in a number, and an array arr[] containing digits from 0 to 9. Your have to count how many n-digit positive integers can be formed such that at least one digit from the array arr[] appears in the number.
 *
 * Examples:
 *
 * Input: n = 1, arr[] = [1, 2, 3]
 * Output: 3
 * Explanation: Only the single-digit numbers [1, 2, 3] satisfy the condition.
 *
 * Input: n = 2, arr[] = [3, 5]
 * Output: 34
 * Explanation: There are a total of 34  two digit numbers which contain atleast  one out of  [3, 5].
 *
 * Constraints:
 * 1 ≤ n ≤ 9
 * 1 ≤ arr.size() ≤ 10
 * 0 ≤ arr[i] ≤ 9
 */

/************************************************************ C++ ************************************************/

// Approach: Uses the principle of complementary counting. First, it calculates the total number of n-digit positive integers. Then, it calculates the number of n-digit integers that can be formed using only digits *not* present in the input array `arr`. The final answer is the difference between these two counts.
// Time Complexity: O(k + n), where k is the number of elements in arr and n is the number of digits. O(k) to build the set and O(n) for the power function.
// Space Complexity: O(k), where k is the number of elements in arr, used to store the forbidden digits in a hash set for efficient lookup.
class Solution {
public:
    // Helper function to calculate power (base^exp) using a simple loop.
    // This is sufficient for the constraints where n is not excessively large.
    int power(int base, int exp) {
        int res = 1; // Initialize result to 1

        for (int i = 0; i < exp; ++i) {
            res *= base; // Multiply result by base, 'exp' times
        }
        return res;      // Return the calculated power
    }

    int countValid(int n, vector<int>& arr) {
        // --- Step 1: Calculate the total number of n-digit positive integers ---
        // The first digit can be any from 1-9 (9 choices).
        // The subsequent n-1 digits can be any from 0-9 (10 choices).
        int total_numbers = 9 * power(10, n - 1);

        // --- Step 2: Count numbers formed with NO digits from arr (the exclusions) ---
        // Use an unordered_set for O(1) average time complexity lookups of forbidden digits.
        unordered_set<int> forbidden_digits(arr.begin(), arr.end());

        // Calculate how many digits are available to form the exclusion numbers.
        int allowed_count = 10 - forbidden_digits.size();

        // This variable will store the count of n-digit numbers without any forbidden digits.
        int numbers_to_exclude;

        // The logic splits based on whether '0' is allowed, as it cannot be the first digit.
        if (forbidden_digits.count(0)) {
            // Case A: '0' is in the forbidden list.
            // All 'allowed_count' digits are non-zero.
            // First digit choices: allowed_count. Other digits choices: allowed_count.
            numbers_to_exclude = power(allowed_count, n);
        } else {
            // Case B: '0' is NOT in the forbidden list (it is allowed).
            // First digit choices: allowed_count - 1 (since '0' cannot be the first digit).
            // Other n-1 digits choices: allowed_count (since '0' can be used here).
            numbers_to_exclude = (allowed_count - 1) * power(allowed_count, n - 1);
        }

        // --- Step 3: Subtract the exclusions from the total to get the final answer ---
        return total_numbers - numbers_to_exclude;
    }
};

/*
 *
 * Dry Run for Input: n = 2, arr[] = [3, 5]
 *
 * 1. `countValid(2, {3, 5})` is called.
 *
 * 2. Calculate `total_numbers`:
 * - n = 2.
 * - `power(10, n - 1)` becomes `power(10, 1)`, which returns 10.
 * - `total_numbers` = 9 * 10 = 90.
 * - This is correct, as there are 90 two-digit numbers (10 to 99).
 *
 * 3. Set up for calculating `numbers_to_exclude`:
 * - `forbidden_digits` set is created: {3, 5}.
 * - `allowed_count` = 10 - `forbidden_digits.size()` = 10 - 2 = 8.
 * - The allowed digits are {0, 1, 2, 4, 6, 7, 8, 9}.
 *
 * 4. Check if 0 is forbidden:
 * - `forbidden_digits.count(0)` is false, as 0 is not in {3, 5}.
 * - The code enters the `else` block.
 *
 * 5. Calculate `numbers_to_exclude` (numbers with no 3s and no 5s):
 * - `allowed_count - 1` = 8 - 1 = 7. (Choices for the first digit: {1, 2, 4, 6, 7, 8, 9})
 * - `power(allowed_count, n - 1)` becomes `power(8, 1)`, which returns 8. (Choices for the second digit: {0, 1, 2, 4, 6, 7, 8, 9})
 * - `numbers_to_exclude` = 7 * 8 = 56.
 *
 * 6. Final Calculation:
 * - `return total_numbers - numbers_to_exclude;`
 * - `return 90 - 56;`
 * - `return 34;`
 *
 * Final Output: 34
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Uses the principle of complementary counting. First, it calculates the total number of n-digit positive integers. Then, it calculates the number of n-digit integers that can be formed using only digits *not* present in the input array `arr`. The final answer is the difference between these two counts.
// Time Complexity: O(k + n), where k is the number of elements in arr and n is the number of digits. O(k) to build the set and O(n) for the power function.
// Space Complexity: O(k), where k is the number of elements in arr, used to store the forbidden digits in a hash set for efficient lookup.
class Solution {
    // Helper function to calculate power (base^exp) using a simple loop.
    // This is sufficient for the constraints where n is not excessively large.
    private int power(int base, int exp) {
        int res = 1; // Initialize result to 1

        for (int i = 0; i < exp; ++i) {
            res *= base; // Multiply result by base, 'exp' times
        }
        return res;      // Return the calculated power
    }
    
    public int countValid(int n, int[] arr) {
        // --- Step 1: Calculate the total number of n-digit positive integers ---
        // The first digit can be any from 1-9 (9 choices).
        // The subsequent n-1 digits can be any from 0-9 (10 choices).
        int totalNumbers = 9 * power(10, n - 1);

        // --- Step 2: Count numbers formed with NO digits from arr (the exclusions) ---
        // Use a HashSet for O(1) average time complexity lookups of forbidden digits.
        Set<Integer> forbiddenDigits = new HashSet<>();

        for (int digit : arr) {
            forbiddenDigits.add(digit);
        }

        // Calculate how many digits are available to form the exclusion numbers.
        int allowedCount = 10 - forbiddenDigits.size();

        // This variable will store the count of n-digit numbers without any forbidden digits.
        int numbersToExclude;

        // The logic splits based on whether '0' is allowed, as it cannot be the first digit.
        if (forbiddenDigits.contains(0)) {
            // Case A: '0' is in the forbidden list.
            // All 'allowedCount' digits are non-zero.
            // First digit choices: allowedCount. Other digits choices: allowedCount.
            numbersToExclude = power(allowedCount, n);
        } else {
            // Case B: '0' is NOT in the forbidden list (it is allowed).
            // First digit choices: allowedCount - 1 (since '0' cannot be the first digit).
            // Other n-1 digits choices: allowedCount (since '0' can be used here).
            numbersToExclude = (allowedCount - 1) * power(allowedCount, n - 1);
        }

        // --- Step 3: Subtract the exclusions from the total to get the final answer ---
        return totalNumbers - numbersToExclude;
    }
}

/*
 *
 * Dry Run for Input: n = 2, arr[] = {3, 5}
 *
 * 1. `countValid(2, {3, 5})` is called.
 *
 * 2. Calculate `totalNumbers`:
 * - n = 2.
 * - `power(10, n - 1)` becomes `power(10, 1)`, which returns 10.
 * - `totalNumbers` = 9 * 10 = 90.
 * - This is correct, as there are 90 two-digit numbers (10 to 99).
 *
 * 3. Set up for calculating `numbersToExclude`:
 * - `forbiddenDigits` set is created: {3, 5}.
 * - `allowedCount` = 10 - `forbiddenDigits.size()` = 10 - 2 = 8.
 * - The allowed digits are {0, 1, 2, 4, 6, 7, 8, 9}.
 *
 * 4. Check if 0 is forbidden:
 * - `forbiddenDigits.contains(0)` is false, as 0 is not in {3, 5}.
 * - The code enters the `else` block.
 *
 * 5. Calculate `numbersToExclude` (numbers with no 3s and no 5s):
 * - `allowedCount - 1` = 8 - 1 = 7. (Choices for the first digit: {1, 2, 4, 6, 7, 8, 9})
 * - `power(allowedCount, n - 1)` becomes `power(8, 1)`, which returns 8. (Choices for the second digit: {0, 1, 2, 4, 6, 7, 8, 9})
 * - `numbersToExclude` = 7 * 8 = 56.
 *
 * 6. Final Calculation:
 * - `return totalNumbers - numbersToExclude;`
 * - `return 90 - 56;`
 * - `return 34;`
 *
 * Final Output: 34
 *
 */
