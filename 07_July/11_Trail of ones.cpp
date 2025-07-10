/*
 * GfG Link: https://www.geeksforgeeks.org/problems/trail-of-ones3242/1
 *
 * Trail of ones
 *
 * Difficulty: Medium Accuracy: 51.16% Submissions: 34K+ Points: 4
 * Given an integer n, the task is to count the number of binary strings of length n that contains at least one pair of consecutive 1's.
 * Note: A binary string is a sequence made up of only 0's and 1's.
 *
 * Examples:
 *
 * Input: n = 2
 * Output: 1
 * Explanation: There are 4 strings of length 2, the strings are 00, 01, 10, and 11. Only the string 11 has consecutive 1's.
 *
 * Input: n = 3
 * Output: 3
 * Explanation: There are 8 strings of length 3, the strings are 000, 001, 010, 011, 100, 101, 110 and 111. The strings with consecutive 1's are 011, 110 and 111.
 *
 * Input: n = 5
 * Output: 19
 * Explanation: There are 19 strings having at least one pair of consecutive 1's.
 *
 * Constraints:
 * 2 ≤ n ≤ 30
 */

/************************************************************ C++ ************************************************/

// Approach: Use an iterative Fibonacci-based recurrence—at each length i, double the previous count (append 0 or 1) and add Fib(i) for new “11” endings.
// Time Complexity: O(n) because we loop from 3 to n once.
// Space Complexity: O(1) using only a fixed number of integer variables.
class Solution {
public:
    int countConsec(int n) {
        if (n == 2) {                // Base: only "11" has consecutive 1’s when length = 2
            return 1;
        }

        int firstNum  = 0;          // Fib(i-2)
        int secondNum = 1;          // Fib(i-1)
        int thirdNum;               // Fib(i)
        int result = 1;             // Count of “bad” strings for length = 2

        for (int i = 3; i <= n; ++i) {
            thirdNum  = firstNum + secondNum;     // Compute Fib(i)
            result    = result * 2 + thirdNum;    // Double previous + new “11” endings
            firstNum  = secondNum;                // Shift window
            secondNum = thirdNum;
        }

        return result;               // Final count for length = n
    }
};

/*
 *
 * Dry Run
 *
 * Let n = 5
 * Initialization before loop: firstNum=0, secondNum=1, result=1
 *
 * i = 3:
 *   thirdNum = 0 + 1 = 1
 *   result   = 1*2 + 1 = 3
 *   firstNum = 1, secondNum = 1
 *
 * i = 4:
 *   thirdNum = 1 + 1 = 2
 *   result   = 3*2 + 2 = 8
 *   firstNum = 1, secondNum = 2
 *
 * i = 5:
 *   thirdNum = 1 + 2 = 3
 *   result   = 8*2 + 3 = 19
 *   firstNum = 2, secondNum = 3
 *
 * Return 19, which matches the count for n=5.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use an iterative Fibonacci-based recurrence—at each length i, double the previous count (append 0 or 1) and add Fib(i) for new “11” endings.
// Time Complexity: O(n) because we loop from 3 to n once.
// Space Complexity: O(1) using only a fixed number of integer variables.
class Solution {
    public int countConsec(int n) {
        if (n == 2) {               // Base: only "11" has consecutive 1’s when length = 2
            return 1;
        }

        int firstNum  = 0;          // Fib(i-2)
        int secondNum = 1;          // Fib(i-1)
        int thirdNum;               // Fib(i)
        int result = 1;             // Count of “bad” strings for length = 2

        for (int i = 3; i <= n; i++) {
            thirdNum  = firstNum + secondNum;     // Compute Fib(i)
            result    = result * 2 + thirdNum;    // Double previous + new “11” endings
            firstNum  = secondNum;                // Shift window
            secondNum = thirdNum;
        }
        return result;              // Final count for length = n
    }
}

/*
 *
 * Dry Run
 *
 * Let n = 5
 * Initialization before loop: firstNum=0, secondNum=1, result=1
 *
 * i = 3:
 *   thirdNum = 0 + 1 = 1
 *   result   = 1*2 + 1 = 3
 *   firstNum = 1, secondNum = 1
 *
 * i = 4:
 *   thirdNum = 1 + 1 = 2
 *   result   = 3*2 + 2 = 8
 *   firstNum = 1, secondNum = 2
 *
 * i = 5:
 *   thirdNum = 1 + 2 = 3
 *   result   = 8*2 + 3 = 19
 *   firstNum = 2, secondNum = 3
 *
 * Return 19, which matches the count for n=5.
 *
 */
