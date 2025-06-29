/*
 * GfG Link: https://www.geeksforgeeks.org/problems/split-array-largest-sum--141634/1
 *
 * Split Array Largest Sum
 *
 * Difficulty: Hard Accuracy: 58.9% Submissions: 52K+ Points: 8
 *
 * Given an array arr[] and an integer k, divide the array into k contiguous subarrays such that the maximum sum among these subarrays is minimized. Find this minimum possible maximum sum.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3, 4], k = 3
 * Output: 4
 * Exaplanation: Optimal Split is [1, 2], [3], [4]. Maximum sum of all subarrays is 4, which is minimum possible for 3 splits.
 *
 * Input: arr[] = [1, 1, 2], k = 2
 * Output: 2
 * Exaplanation: Splitting the array as [1, 1] and [2] is optimal. This results in a maximum sum subarray of 2.
 *
 * Constraints:
 * 1 ≤ k ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Binary Search on the answer range (max element to total sum). Use greedy check to verify if mid can split array into at most k parts.
// Time Complexity: O(n * log(sum - max)), where n = size of array, because for each binary search iteration we traverse the array once.
// Space Complexity: O(1), no extra space used apart from variables.
class Solution {
public:
    // Check if we can split the array into at most k subarrays such that no subarray has a sum greater than mid
    bool check(int mid, vector<int>& arr, int k) {
        int n = arr.size();

        int count = 1; // Start with 1 subarray
        int sum   = 0; // Running sum of current subarray

        for (int i = 0; i < n; i++) {
            // If any element is greater than mid, we cannot make such a split
            if (arr[i] > mid) {
                return false;
            }

            sum += arr[i]; // Add current element to current subarray

            // If the sum exceeds mid, we need to start a new subarray
            if (sum > mid) {
                count++;
                sum = arr[i]; // Start new subarray with current element
            }
        }
        return count <= k; // Return true if we used k or fewer subarrays
    }
    int splitArray(vector<int>& arr, int k) {
        int n = arr.size();

        int low    = *max_element(arr.begin(), arr.end());        // Minimum possible max subarray sum
        int high   = accumulate(arr.begin(), arr.end(), 0);       // Maximum possible max subarray sum
        int result = 0;

        // Binary search for the minimum max subarray sum
        while (low <= high) {
            int mid = (low + high) / 2;

            if (check(mid, arr, k)) {
                result = mid;      // Mid is a possible answer
                high   = mid - 1;  // Try to find a smaller one
            } else {
                low = mid + 1;     // Increase mid to try bigger max sum
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 3, 4], k = 3
 * Step 1: low = max(arr) = 4, high = sum(arr) = 10
 *
 * Binary Search Iteration 1:
 * mid = (4 + 10) / 2 = 7
 * check(7): [1+2+3=6] < 7 → add 4 → 6+4=10 > 7 ⇒ split before 4
 * → Subarrays: [1,2,3], [4] → count = 2 <= 3 → valid
 * result = 7, high = 6
 *
 * Binary Search Iteration 2:
 * mid = (4 + 6) / 2 = 5
 * check(5): 1+2=3 → add 3 → 3+3=6 > 5 ⇒ split ⇒ [1,2], [3]
 * → add 4 → 3+4=7 > 5 ⇒ split ⇒ [4]
 * → Subarrays: [1,2], [3], [4] → count = 3 → valid
 * result = 5, high = 4
 *
 * Binary Search Iteration 3:
 * mid = (4 + 4) / 2 = 4
 * check(4): 1+2=3 → add 3 → 3+3=6 > 4 ⇒ split ⇒ [1,2], [3]
 * → add 4 → 3+4=7 > 4 ⇒ split ⇒ [4]
 * → Subarrays: [1,2], [3], [4] → count = 3 → valid
 * result = 4, high = 3
 *
 * End: low = 4, high = 3 ⇒ exit loop
 * Final answer: 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Binary Search on the answer range (max element to total sum). Use greedy check to verify if mid can split array into at most k parts.
// Time Complexity: O(n * log(sum - max)), where n = size of array, because for each binary search iteration we traverse the array once.
// Space Complexity: O(1), no extra space used apart from variables.
class Solution {
    // Check if we can split the array into at most k subarrays such that no subarray has a sum greater than mid
    public boolean check(int mid, int[] arr, int k) {
        int n = arr.length;

        int count = 1; // Start with 1 subarray
        int sum   = 0; // Running sum of current subarray

        for (int i = 0; i < n; i++) {
            // If any element is greater than mid, we cannot make such a split
            if (arr[i] > mid) {
                return false;
            }

            sum += arr[i]; // Add current element to current subarray

            // If the sum exceeds mid, we need to start a new subarray
            if (sum > mid) {
                count++;
                sum = arr[i]; // Start new subarray with current element
            }
        }
        return count <= k; // Return true if we used k or fewer subarrays
    }
    public int splitArray(int[] arr, int k) {
        int n = arr.length;

        int low    = Arrays.stream(arr).max().getAsInt();        // Minimum possible max subarray sum
        int high   = Arrays.stream(arr).sum();                   // Maximum possible max subarray sum
        int result = 0;

        // Binary search for the minimum max subarray sum
        while (low <= high) {
            int mid = (low + high) / 2;

            if (check(mid, arr, k)) {
                result = mid;     // Mid is a possible answer
                high   = mid - 1; // Try to find a smaller one
            } else {
                low = mid + 1;    // Increase mid to try bigger max sum
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 3, 4], k = 3
 * Step 1: low = max(arr) = 4, high = sum(arr) = 10
 *
 * Binary Search Iteration 1:
 * mid = (4 + 10) / 2 = 7
 * check(7): [1+2+3=6] < 7 → add 4 → 6+4=10 > 7 ⇒ split before 4
 * → Subarrays: [1,2,3], [4] → count = 2 <= 3 → valid
 * result = 7, high = 6
 *
 * Binary Search Iteration 2:
 * mid = (4 + 6) / 2 = 5
 * check(5): 1+2=3 → add 3 → 3+3=6 > 5 ⇒ split ⇒ [1,2], [3]
 * → add 4 → 3+4=7 > 5 ⇒ split ⇒ [4]
 * → Subarrays: [1,2], [3], [4] → count = 3 → valid
 * result = 5, high = 4
 *
 * Binary Search Iteration 3:
 * mid = (4 + 4) / 2 = 4
 * check(4): 1+2=3 → add 3 → 3+3=6 > 4 ⇒ split ⇒ [1,2], [3]
 * → add 4 → 3+4=7 > 4 ⇒ split ⇒ [4]
 * → Subarrays: [1,2], [3], [4] → count = 3 → valid
 * result = 4, high = 3
 *
 * End: low = 4, high = 3 ⇒ exit loop
 * Final answer: 4
 */
