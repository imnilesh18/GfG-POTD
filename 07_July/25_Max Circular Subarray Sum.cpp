/*
 * GfG Link: https://www.geeksforgeeks.org/problems/max-circular-subarray-sum-1587115620/1
 *
 * Max Circular Subarray Sum
 *
 * Difficulty: Hard Accuracy: 29.37% Submissions: 171K+ Points: 8 Average Time: 25m
 *
 * You are given a circular array arr[] of integers, find the maximum possible sum of a non-empty subarray. In a circular array, the subarray can start at the end and wrap around to the beginning. Return the maximum non-empty subarray sum, considering both non-wrapping and wrapping cases.
 *
 * Examples:
 *
 * Input: arr[] = [8, -8, 9, -9, 10, -11, 12]
 * Output: 22
 * Explanation: Starting from the last element of the array, i.e, 12, and moving in a circular fashion, we have max subarray as 12, 8, -8, 9, -9, 10, which gives maximum sum as 22.
 *
 * Input: arr[] = [10, -3, -4, 7, 6, 5, -4, -1]
 * Output: 23
 * Explanation: Maximum sum of the circular subarray is 23. The subarray is [7, 6, 5, -4, -1, 10].
 *
 * Input: arr[] = [5, -2, 3, 4]
 * Output: 12
 * Explanation: The circular subarray [3, 4, 5] gives the maximum sum of 12.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * -10^4 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: The maximum circular subarray sum is the maximum of two cases:
// 1. The maximum sum subarray is non-wrapping (found using Kadane's algorithm).
// 2. The maximum sum subarray is wrapping. This is equivalent to the total sum of the array minus the minimum sum non-wrapping subarray.
// An edge case exists if all numbers are negative. In this situation, the minimum sum subarray is the entire array, so `totalSum - minSum` would be 0. The correct answer is the largest (least negative) element, which is correctly found by the non-wrapping Kadane's (`maxSum`). The condition `minSum == totalSum` handles this edge case.
// Time Complexity: O(N), because we iterate through the array only once.
// Space Complexity: O(1), because we only use a few constant extra variables.
class Solution {
public:
    int maxCircularSum(vector<int>& arr) {
        // Initialize variables
        int totalSum   = 0;      // To store the sum of all elements in the array
        int currMaxSum = 0;      // Current maximum sum ending at the current element (for non-wrapping max)
        int currMinSum = 0;      // Current minimum sum ending at the current element (for non-wrapping min)
        int maxSum     = arr[0]; // Overall maximum subarray sum (non-wrapping)
        int minSum     = arr[0]; // Overall minimum subarray sum (non-wrapping)

        // Iterate through the array to find maxSum, minSum, and totalSum in one pass
        for (int i = 0; i < arr.size(); i++) {
            // --- Kadane's algorithm to find the maximum sum subarray (non-wrapping) ---
            // Decide whether to extend the current subarray or start a new one from arr[i]
            currMaxSum = max(currMaxSum + arr[i], arr[i]);
            // Update the overall maximum sum found so far
            maxSum = max(maxSum, currMaxSum);

            // --- Kadane's algorithm variant to find the minimum sum subarray (non-wrapping) ---
            // Decide whether to extend the current minimum subarray or start a new one from arr[i]
            currMinSum = min(currMinSum + arr[i], arr[i]);
            // Update the overall minimum sum found so far
            minSum = min(minSum, currMinSum);

            // Calculate the sum of all elements in the array
            totalSum = totalSum + arr[i];
        }

        // Case 1: The maximum sum is from a non-wrapping subarray
        int normalSum = maxSum;

        // Case 2: The maximum sum is from a wrapping subarray.
        // This is calculated as the total sum minus the minimum sum subarray.
        // The elements not in the minimum subarray form the wrapping maximum subarray.
        int circularSum = totalSum - minSum;

        // Edge Case: If all elements are negative, minSum will be equal to totalSum.
        // In this case, `circularSum` would be 0, which is incorrect.
        // The answer must be the largest element (which `maxSum` correctly holds).
        // So, if the array consists of all negative numbers, we return the non-wrapping sum.
        if (minSum == totalSum) {
            return normalSum;
        }

        // The final answer is the maximum of the non-wrapping sum and the wrapping sum.
        return max(normalSum, circularSum);
    }
};

/*
 *
 * Dry Run with Example: arr[] = [5, -2, 3, 4]
 *
 * Initial values:
 * totalSum = 0
 * currMaxSum = 0
 * currMinSum = 0
 * maxSum = 5 (initialized with arr[0])
 * minSum = 5 (initialized with arr[0])
 *
 * --- Loop Start ---
 *
 * i = 0, arr[0] = 5
 * currMaxSum = max(0 + 5, 5)     -> 5
 * maxSum     = max(5, 5)         -> 5
 * currMinSum = min(0 + 5, 5)     -> 5
 * minSum     = min(5, 5)         -> 5
 * totalSum   = 0 + 5             -> 5
 *
 * i = 1, arr[1] = -2
 * currMaxSum = max(5 + (-2), -2) -> max(3, -2)  -> 3
 * maxSum     = max(5, 3)         -> 5
 * currMinSum = min(5 + (-2), -2) -> min(3, -2)  -> -2
 * minSum     = min(5, -2)        -> -2
 * totalSum   = 5 + (-2)          -> 3
 *
 * i = 2, arr[2] = 3
 * currMaxSum = max(3 + 3, 3)     -> max(6, 3)   -> 6
 * maxSum     = max(5, 6)         -> 6
 * currMinSum = min(-2 + 3, 3)    -> min(1, 3)   -> 1
 * minSum     = min(-2, 1)        -> -2
 * totalSum   = 3 + 3             -> 6
 *
 * i = 3, arr[3] = 4
 * currMaxSum = max(6 + 4, 4)     -> max(10, 4)  -> 10
 * maxSum     = max(6, 10)        -> 10
 * currMinSum = min(1 + 4, 4)     -> min(5, 4)   -> 4
 * minSum     = min(-2, 4)        -> -2
 * totalSum   = 6 + 4             -> 10
 *
 * --- Loop End ---
 *
 * Final values after loop:
 * totalSum = 10
 * maxSum = 10  (This is the non-wrapping max subarray sum: [3, 4] gives 7, but wait, my dry run for maxSum is wrong. Let's recheck)
 *
 * Corrected Dry Run for maxSum:
 * i=0: currMaxSum=5, maxSum=5
 * i=1: currMaxSum=max(5-2, -2)=3, maxSum=max(5,3)=5
 * i=2: currMaxSum=max(3+3, 3)=6, maxSum=max(5,6)=6
 * i=3: currMaxSum=max(6+4, 4)=10, maxSum=max(6,10)=10
 * The non-wrapping max subarray is [5, -2, 3, 4], sum is 10.
 * Wait, that's not right either.
 * Let's re-re-check:
 * i=0, arr[0]=5: currMaxSum=5, maxSum=5
 * i=1, arr[1]=-2: currMaxSum=3, maxSum=5
 * i=2, arr[2]=3: currMaxSum=6, maxSum=6
 * i=3, arr[3]=4: currMaxSum=10, maxSum=10
 * Ah, the max subarray is the whole array [5, -2, 3, 4] with sum 10.
 * Let's check the example [5, -3, 4].
 * i=0, arr[0]=5: currMaxSum=5, maxSum=5
 * i=1, arr[1]=-3: currMaxSum=max(5-3, -3)=2, maxSum=max(5,2)=5
 * i=2, arr[2]=4: currMaxSum=max(2+4, 4)=6, maxSum=max(5,6)=6. The non-wrapping max is [5, -3, 4] which is 6.
 *
 * Let's go back to the original example: [5, -2, 3, 4].
 * Final values after loop:
 * totalSum = 10
 * maxSum = 10 (The subarray is [5, -2, 3, 4])
 * minSum = -2 (The subarray is [-2])
 *
 * --- Post-loop calculations ---
 *
 * normalSum = maxSum -> 10
 *
 * circularSum = totalSum - minSum -> 10 - (-2) -> 12
 * (This corresponds to the wrapping subarray [3, 4, 5])
 *
 * Check edge case:
 * is (minSum == totalSum)? -> is (-2 == 10)? -> No.
 *
 * Final return:
 * return max(normalSum, circularSum) -> max(10, 12) -> 12
 *
 * Output: 12
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: The maximum circular subarray sum is the maximum of two cases:
// 1. The maximum sum subarray is non-wrapping (found using Kadane's algorithm).
// 2. The maximum sum subarray is wrapping. This is equivalent to the total sum of the array minus the minimum sum non-wrapping subarray.
// An edge case exists if all numbers are negative. In this situation, the minimum sum subarray is the entire array, so `totalSum - minSum` would be 0. The correct answer is the largest (least negative) element, which is correctly found by the non-wrapping Kadane's (`maxSum`). The condition `minSum == totalSum` handles this edge case.
// Time Complexity: O(N), because we iterate through the array only once.
// Space Complexity: O(1), because we only use a few constant extra variables.
class Solution {
    public int maxCircularSum(int arr[]) {
        // Initialize variables
        int totalSum   = 0;      // To store the sum of all elements in the array
        int currMaxSum = 0;      // Current maximum sum ending at the current element (for non-wrapping max)
        int currMinSum = 0;      // Current minimum sum ending at the current element (for non-wrapping min)
        int maxSum     = arr[0]; // Overall maximum subarray sum (non-wrapping)
        int minSum     = arr[0]; // Overall minimum subarray sum (non-wrapping)

        // Iterate through the array to find maxSum, minSum, and totalSum in one pass
        for (int i = 0; i < arr.length; i++) {
            // --- Kadane's algorithm to find the maximum sum subarray (non-wrapping) ---
            // Decide whether to extend the current subarray or start a new one from arr[i]
            currMaxSum = Math.max(currMaxSum + arr[i], arr[i]);
            // Update the overall maximum sum found so far
            maxSum = Math.max(maxSum, currMaxSum);

            // --- Kadane's algorithm variant to find the minimum sum subarray (non-wrapping) ---
            // Decide whether to extend the current minimum subarray or start a new one from arr[i]
            currMinSum = Math.min(currMinSum + arr[i], arr[i]);
            // Update the overall minimum sum found so far
            minSum = Math.min(minSum, currMinSum);

            // Calculate the sum of all elements in the array
            totalSum = totalSum + arr[i];
        }

        // Case 1: The maximum sum is from a non-wrapping subarray
        int normalSum = maxSum;

        // Case 2: The maximum sum is from a wrapping subarray.
        // This is calculated as the total sum minus the minimum sum subarray.
        // The elements not in the minimum subarray form the wrapping maximum subarray.
        int circularSum = totalSum - minSum;

        // Edge Case: If all elements are negative, minSum will be equal to totalSum.
        // In this case, `circularSum` would be 0, which is incorrect.
        // The answer must be the largest element (which `maxSum` correctly holds).
        // So, if the array consists of all negative numbers, we return the non-wrapping sum.
        if (minSum == totalSum) {
            return normalSum;
        }

        // The final answer is the maximum of the non-wrapping sum and the wrapping sum.
        return Math.max(normalSum, circularSum);
    }
}

/*
 *
 * Dry Run with Example: arr[] = {5, -2, 3, 4}
 *
 * Initial values:
 * totalSum = 0
 * currMaxSum = 0
 * currMinSum = 0
 * maxSum = 5 (initialized with arr[0])
 * minSum = 5 (initialized with arr[0])
 *
 * --- Loop Start ---
 *
 * i = 0, arr[0] = 5
 * currMaxSum = Math.max(0 + 5, 5)     -> 5
 * maxSum     = Math.max(5, 5)         -> 5
 * currMinSum = Math.min(0 + 5, 5)     -> 5
 * minSum     = Math.min(5, 5)         -> 5
 * totalSum   = 0 + 5                  -> 5
 *
 * i = 1, arr[1] = -2
 * currMaxSum = Math.max(5 + (-2), -2) -> Math.max(3, -2)  -> 3
 * maxSum     = Math.max(5, 3)         -> 5
 * currMinSum = Math.min(5 + (-2), -2) -> Math.min(3, -2)  -> -2
 * minSum     = Math.min(5, -2)        -> -2
 * totalSum   = 5 + (-2)               -> 3
 *
 * i = 2, arr[2] = 3
 * currMaxSum = Math.max(3 + 3, 3)     -> Math.max(6, 3)   -> 6
 * maxSum     = Math.max(5, 6)         -> 6
 * currMinSum = Math.min(-2 + 3, 3)    -> Math.min(1, 3)   -> 1
 * minSum     = Math.min(-2, 1)        -> -2
 * totalSum   = 3 + 3                  -> 6
 *
 * i = 3, arr[3] = 4
 * currMaxSum = Math.max(6 + 4, 4)     -> Math.max(10, 4)  -> 10
 * maxSum     = Math.max(6, 10)        -> 10
 * currMinSum = Math.min(1 + 4, 4)     -> Math.min(5, 4)   -> 4
 * minSum     = Math.min(-2, 4)        -> -2
 * totalSum   = 6 + 4                  -> 10
 *
 * --- Loop End ---
 *
 * Final values after loop:
 * totalSum = 10
 * maxSum = 10 (The non-wrapping max subarray is [5, -2, 3, 4])
 * minSum = -2 (The subarray is [-2])
 *
 * --- Post-loop calculations ---
 *
 * normalSum = maxSum -> 10
 *
 * circularSum = totalSum - minSum -> 10 - (-2) -> 12
 * (This corresponds to the wrapping subarray {3, 4, 5})
 *
 * Check edge case:
 * is (minSum == totalSum)? -> is (-2 == 10)? -> No.
 *
 * Final return:
 * return Math.max(normalSum, circularSum) -> Math.max(10, 12) -> 12
 *
 * Output: 12
 *
 */
