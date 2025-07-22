/*
 * GfG Link: https://www.geeksforgeeks.org/problems/sum-of-subarrays2229/1
 *
 * Sum of Subarrays
 *
 * Difficulty: Medium Accuracy: 23.85% Submissions: 29K+ Points: 4
 *
 * Given an array arr[], find the sum of all the subarrays of the given array
 * Note: It is guaranteed that the total sum will fit within a 32-bit integer range.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3]
 * Output: 20
 * Explanation: All subarray sums are: [1] = 1, [2] = 2, [3] = 3, [1, 2] = 3, [2, 3] = 5, [1, 2, 3] = 6. Thus total sum is 1 + 2 + 3 + 3 + 5 + 6 = 20.
 *
 * Input: arr[] = [1, 3]
 * Output: 8
 * Explanation: All subarray sums are: [1] = 1, [3] = 3, [1, 3] = 4. Thus total sum is 1 + 3 + 4 = 8.
 *
 * Constraints :
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Intuition: Instead of generating every single subarray and summing them up (which is slow, O(n^2)), we can reframe the problem. Let's think about each number individually and how much it contributes to the final total sum. An element's total contribution is its value multiplied by the number of times it appears across all possible subarrays. A subarray is defined by a start and end point. For an element at index 'i' to be included, the subarray must start at or before 'i' and end at or after 'i'. The number of starting choices is (i + 1) and the number of ending choices is (n - i). Multiplying these gives the total number of subarrays the element arr[i] is in. By summing up these contributions for every element, we get the total sum of all subarrays in a single pass.
// Approach: Calculate each element's contribution to the total sum. The contribution of arr[i] is arr[i] multiplied by the number of subarrays it appears in, which is (i + 1) * (n - i).
// Time Complexity: O(n) - We iterate through the array once.
// Space Complexity: O(1) - We use constant extra space.
class Solution {
public:
    int subarraySum(vector<int>& arr) {
        int n      = arr.size();
        int result = 0;

        // Calculate the sum of all subarrays using the contribution formula.
        for (int i = 0; i < n; i++) {
            result += (arr[i] * (i + 1) * (n - i));
        }

        // Return the total sum of all subarrays.
        return result;
    }
};

/*
 *****************************************************************
 * Dry Run
 * Example Array: arr[] = [1, 2, 3, 4]
 * Array Size (n): 4
 * Initial result = 0
 *****************************************************************
 *
 * --- Loop 1: i = 0, Element arr[0] = 1 ---
 * Subarrays containing 1:
 * Starts at index 0, ends at 0: [1]
 * Starts at index 0, ends at 1: [1, 2]
 * Starts at index 0, ends at 2: [1, 2, 3]
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Total Occurrences: (0 + 1) * (4 - 0) = 1 * 4 = 4
 * Contribution: 1 * 4 = 4
 * Update result: result = 0 + 4 = 4
 *
 * --- Loop 2: i = 1, Element arr[1] = 2 ---
 * Subarrays containing 2:
 * Starts at index 0, ends at 1: [1, 2]
 * Starts at index 0, ends at 2: [1, 2, 3]
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Starts at index 1, ends at 1: [2]
 * Starts at index 1, ends at 2: [2, 3]
 * Starts at index 1, ends at 3: [2, 3, 4]
 * Total Occurrences: (1 + 1) * (4 - 1) = 2 * 3 = 6
 * Contribution: 2 * 6 = 12
 * Update result: result = 4 + 12 = 16
 *
 * --- Loop 3: i = 2, Element arr[2] = 3 ---
 * Subarrays containing 3:
 * Starts at index 0, ends at 2: [1, 2, 3]
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Starts at index 1, ends at 2: [2, 3]
 * Starts at index 1, ends at 3: [2, 3, 4]
 * Starts at index 2, ends at 2: [3]
 * Starts at index 2, ends at 3: [3, 4]
 * Total Occurrences: (2 + 1) * (4 - 2) = 3 * 2 = 6
 * Contribution: 3 * 6 = 18
 * Update result: result = 16 + 18 = 34
 *
 * --- Loop 4: i = 3, Element arr[3] = 4 ---
 * Subarrays containing 4:
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Starts at index 1, ends at 3: [2, 3, 4]
 * Starts at index 2, ends at 3: [3, 4]
 * Starts at index 3, ends at 3: [4]
 * Total Occurrences: (3 + 1) * (4 - 3) = 4 * 1 = 4
 * Contribution: 4 * 4 = 16
 * Update result: result = 34 + 16 = 50
 *
 *****************************************************************
 * Final Result
 * The loop finishes.
 * The final value of result is 50.
 * The function returns 50.
 *****************************************************************
 */

/************************************************************ JAVA ************************************************/

// Intuition: Instead of generating every single subarray and summing them up (which is slow, O(n^2)), we can reframe the problem. Let's think about each number individually and how much it contributes to the final total sum. An element's total contribution is its value multiplied by the number of times it appears across all possible subarrays. A subarray is defined by a start and end point. For an element at index 'i' to be included, the subarray must start at or before 'i' and end at or after 'i'. The number of starting choices is (i + 1) and the number of ending choices is (n - i). Multiplying these gives the total number of subarrays the element arr[i] is in. By summing up these contributions for every element, we get the total sum of all subarrays in a single pass.
// Approach: Calculate each element's contribution to the total sum. The contribution of arr[i] is arr[i] multiplied by the number of subarrays it appears in, which is (i + 1) * (n - i).
// Time Complexity: O(n) - We iterate through the array once.
// Space Complexity: O(1) - We use constant extra space.
class Solution {
    public int subarraySum(int[] arr) {
        int n      = arr.length;
        int result = 0;

        // Calculate the sum of all subarrays using the contribution formula.
        for (int i = 0; i < n; i++) {
            result += (arr[i] * (i + 1) * (n - i));
        }

        // Return the total sum of all subarrays.
        return result;
    }
}

/*
 *****************************************************************
 * Dry Run
 * Example Array: arr[] = [1, 2, 3, 4]
 * Array Size (n): 4
 * Initial result = 0
 *****************************************************************
 *
 * --- Loop 1: i = 0, Element arr[0] = 1 ---
 * Subarrays containing 1:
 * Starts at index 0, ends at 0: [1]
 * Starts at index 0, ends at 1: [1, 2]
 * Starts at index 0, ends at 2: [1, 2, 3]
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Total Occurrences: (0 + 1) * (4 - 0) = 1 * 4 = 4
 * Contribution: 1 * 4 = 4
 * Update result: result = 0 + 4 = 4
 *
 * --- Loop 2: i = 1, Element arr[1] = 2 ---
 * Subarrays containing 2:
 * Starts at index 0, ends at 1: [1, 2]
 * Starts at index 0, ends at 2: [1, 2, 3]
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Starts at index 1, ends at 1: [2]
 * Starts at index 1, ends at 2: [2, 3]
 * Starts at index 1, ends at 3: [2, 3, 4]
 * Total Occurrences: (1 + 1) * (4 - 1) = 2 * 3 = 6
 * Contribution: 2 * 6 = 12
 * Update result: result = 4 + 12 = 16
 *
 * --- Loop 3: i = 2, Element arr[2] = 3 ---
 * Subarrays containing 3:
 * Starts at index 0, ends at 2: [1, 2, 3]
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Starts at index 1, ends at 2: [2, 3]
 * Starts at index 1, ends at 3: [2, 3, 4]
 * Starts at index 2, ends at 2: [3]
 * Starts at index 2, ends at 3: [3, 4]
 * Total Occurrences: (2 + 1) * (4 - 2) = 3 * 2 = 6
 * Contribution: 3 * 6 = 18
 * Update result: result = 16 + 18 = 34
 *
 * --- Loop 4: i = 3, Element arr[3] = 4 ---
 * Subarrays containing 4:
 * Starts at index 0, ends at 3: [1, 2, 3, 4]
 * Starts at index 1, ends at 3: [2, 3, 4]
 * Starts at index 2, ends at 3: [3, 4]
 * Starts at index 3, ends at 3: [4]
 * Total Occurrences: (3 + 1) * (4 - 3) = 4 * 1 = 4
 * Contribution: 4 * 4 = 16
 * Update result: result = 34 + 16 = 50
 *
 *****************************************************************
 * Final Result
 * The loop finishes.
 * The final value of result is 50.
 * The function returns 50.
 *****************************************************************
 */
