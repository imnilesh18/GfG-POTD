/*
 * GfG Link: https://www.geeksforgeeks.org/problems/max-sum-in-sub-arrays0824/1
 *
 * Max Score from Subarray Mins
 *
 * Difficulty: Medium Accuracy: 43.26% Submissions: 120K+ Points: 4
 *
 * You are given an array arr[] of integers. Your task is to select any two indices i and j such that i < j. From the subarray arr[i...j], find the smallest and second smallest elements. Add these two numbers to get the score of that subarray.
 *
 * Your goal is to return the maximum score that can be obtained from any subarray of arr[] with length at least 2.
 *
 * Examples :
 *
 * Input: arr[] = [4, 3, 5, 1]
 * Output: 8
 * Explanation: All subarrays with at least 2 elements and find the two smallest numbers in each:
 * [4, 3] → 3 + 4 = 7
 * [4, 3, 5] → 3 + 4 = 7
 * [4, 3, 5, 1] → 1 + 3 = 4
 * [3, 5] → 3 + 5 = 8
 * [3, 5, 1] → 1 + 3 = 4
 * [5, 1] → 1 + 5 = 6
 * Maximum Score is 8.
 *
 * Input: arr[] = [1, 2, 3]
 * Output: 5
 * Explanation: All subarray with at least 2 elements and find the two smallest numbers in each:
 * [1, 2] → 1 + 2 = 3
 * [1, 2, 3] → 1 + 2 = 3
 * [2, 3] → 2 + 3 = 5
 * Maximum Score is 5
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute force – For each subarray from i to j, track minimum and second minimum to compute score
// Time Complexity: O(n^2) – Nested loop over all subarrays of size ≥ 2
// Space Complexity: O(1) – Only constant variables used
class Solution {
public:
    int maxSum(vector<int>& arr) {
        int n      = arr.size();
        int maxSum = 0;  // to store the final maximum score

        // iterate over each element in the array except the last one
        for (int i = 0; i < n - 1; i++) {
            int mini       = arr[i];     // assume current element as minimum
            int secondMini = arr[i + 1]; // assume next element as second minimum

            // iterate from i+1 to end to form subarrays
            for (int j = i + 1; j < n; j++) {
                // if current element is smaller or equal to mini
                if (mini >= arr[j]) {
                    secondMini = mini;   // current mini becomes secondMini
                    mini       = arr[j]; // update mini to smaller value
                }
                // if it's smaller than secondMini but not smaller than mini
                else if (secondMini > arr[j]) {
                    secondMini = arr[j]; // update secondMini
                }

                // update maxSum if current score is greater
                maxSum = max(maxSum, mini + secondMini);
            }
        }

        return maxSum;
    }
};

/*
 *
 * Dry Run
 * Input: arr = [4, 3, 5, 1]
 *
 * Outer loop starts at i = 0
 * mini = 4, secondMini = 3
 * j = 1 → arr[1] = 3
 * → mini >= 3 → secondMini = 4, mini = 3
 * → score = 3 + 4 = 7, maxSum = 7
 *
 * j = 2 → arr[2] = 5
 * → 5 > mini and > secondMini → no update to mini/secondMini
 * → score = 3 + 4 = 7
 *
 * j = 3 → arr[3] = 1
 * → mini >= 1 → secondMini = 3, mini = 1
 * → score = 1 + 3 = 4
 *
 * i = 1
 * → mini = 3, secondMini = 5
 * j = 2 → arr[2] = 5
 * → secondMini remains 5
 * → score = 3 + 5 = 8 → maxSum = 8
 *
 * j = 3 → arr[3] = 1
 * → mini >= 1 → secondMini = 3, mini = 1
 * → score = 1 + 3 = 4
 *
 * i = 2
 * → mini = 5, secondMini = 1
 * j = 3 → arr[3] = 1
 * → mini >= 1 → secondMini = 5, mini = 1
 * → score = 1 + 5 = 6
 *
 * Final maxSum = 8 ✅
 *
 */

// Approach 2: Check only adjacent pairs since the max (min + secondMin) always comes from size‑2 subarrays
// Time Complexity: O(n) – Single pass through the array
// Space Complexity: O(1) – Only constant extra variables used
class Solution {
public:
    int maxSum(vector<int>& arr) {
        int n      = arr.size();
        int result = arr[0] + arr[1];  // initialize with first pair sum

        // scan through all adjacent pairs
        for (int i = 1; i < n - 1; i++) {
            result = max(result, arr[i] + arr[i + 1]);
        }

        return result;
    }
};

/*
 *
 * Dry Run
 * Input: arr = [4, 3, 5, 1]
 *
 * result = arr[0] + arr[1] = 4 + 3 = 7
 *
 * i = 1 → arr[1] + arr[2] = 3 + 5 = 8
 * → result = max(7, 8) = 8
 *
 * i = 2 → arr[2] + arr[3] = 5 + 1 = 6
 * → result = max(8, 6) = 8
 *
 * Final result = 8 ✅
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute force – For each subarray from i to j, track minimum and second minimum to compute score
// Time Complexity: O(n^2) – Nested loop over all subarrays of size ≥ 2
// Space Complexity: O(1) – Only constant variables used
class Solution {
    public int maxSum(int arr[]) {
        int n      = arr.length;
        int maxSum = 0;  // to store the final maximum score

        // iterate over each element in the array except the last one
        for (int i = 0; i < n - 1; i++) {
            int mini       = arr[i];     // assume current element as minimum
            int secondMini = arr[i + 1]; // assume next element as second minimum

            // iterate from i+1 to end to form subarrays
            for (int j = i + 1; j < n; j++) {
                // if current element is smaller or equal to mini
                if (mini >= arr[j]) {
                    secondMini = mini;   // current mini becomes secondMini
                    mini       = arr[j]; // update mini to smaller value
                }
                // if it's smaller than secondMini but not smaller than mini
                else if (secondMini > arr[j]) {
                    secondMini = arr[j]; // update secondMini
                }

                // update maxSum if current score is greater
                maxSum = Math.max(maxSum, mini + secondMini);
            }
        }

        return maxSum;
    }
}

/*
 *
 * Dry Run
 * Input: arr = [4, 3, 5, 1]
 *
 * Outer loop starts at i = 0
 * mini = 4, secondMini = 3
 * j = 1 → arr[1] = 3
 * → mini >= 3 → secondMini = 4, mini = 3
 * → score = 3 + 4 = 7, maxSum = 7
 *
 * j = 2 → arr[2] = 5
 * → 5 > mini and > secondMini → no update to mini/secondMini
 * → score = 3 + 4 = 7
 *
 * j = 3 → arr[3] = 1
 * → mini >= 1 → secondMini = 3, mini = 1
 * → score = 1 + 3 = 4
 *
 * i = 1
 * → mini = 3, secondMini = 5
 * j = 2 → arr[2] = 5
 * → secondMini remains 5
 * → score = 3 + 5 = 8 → maxSum = 8
 *
 * j = 3 → arr[3] = 1
 * → mini >= 1 → secondMini = 3, mini = 1
 * → score = 1 + 3 = 4
 *
 * i = 2
 * → mini = 5, secondMini = 1
 * j = 3 → arr[3] = 1
 * → mini >= 1 → secondMini = 5, mini = 1
 * → score = 1 + 5 = 6
 *
 * Final maxSum = 8 ✅
 *
 */

// Approach 2: Check only adjacent pairs since the max (min + secondMin) always comes from size‑2 subarrays
// Time Complexity: O(n) – Single pass through the array
// Space Complexity: O(1) – Only constant extra variables used
class Solution {
public:
    int maxSum(vector<int>& arr) {
        int n      = arr.size();
        int result = arr[0] + arr[1];  // initialize with first pair sum

        // scan through all adjacent pairs
        for (int i = 1; i < n - 1; i++) {
            result = max(result, arr[i] + arr[i + 1]);
        }

        return result;
    }
};

/*
 *
 * Dry Run
 * Input: arr = [4, 3, 5, 1]
 *
 * result = arr[0] + arr[1] = 4 + 3 = 7
 *
 * i = 1 → arr[1] + arr[2] = 3 + 5 = 8
 * → result = max(7, 8) = 8
 *
 * i = 2 → arr[2] + arr[3] = 5 + 1 = 6
 * → result = max(8, 6) = 8
 *
 * Final result = 8 ✅
 *
 */
