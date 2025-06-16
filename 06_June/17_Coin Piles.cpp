/*
 * GfG Link: https://www.geeksforgeeks.org/problems/coin-piles5152/1
 *
 * Coin Piles
 *
 * Difficulty: Medium Accuracy: 20.51% Submissions: 24K+ Points: 4 Average Time: 20m
 *
 * You are given an array arr[] of integers, where each element represents the number of coins in a pile. You are also given an integer k.
 * Your task is to remove the minimum number of coins such that the absolute difference between the number of coins in any two remaining piles is at most k.
 *
 * Note: You can also remove a pile by removing all the coins of that pile.
 *
 * Examples:
 *
 * Input: arr[] = [2, 2, 2, 2], k = 0
 * Output: 0
 * Explanation: For any two piles the difference in the number of coins is <= 0. So no need to remove any coin.
 *
 * Input: arr[] = [1, 5, 1, 2, 5, 1], k = 3
 * Output : 2
 * Explanation: If we remove one coin each from both the piles containing 5 coins, then for any two piles the absolute difference in the number of coins is <= 3.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^4
 * 0 ≤ k ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Sort the array, then for each element arr[i], assume it's the smallest allowed value. Use upper_bound to find the last pile that can remain with value ≤ arr[i]+k. Remove coins from all piles before i and from those after idx that exceed arr[i]+k.
// Time Complexity: O(n log n) - due to sorting and binary search for each element.
// Space Complexity: O(n) - for storing prefix sums.
class Solution {
public:
    int minimumCoins(vector<int>& arr, int k) {
        int n = arr.size();

        // Sort the array to process piles in increasing order
        sort(arr.begin(), arr.end());

        // Compute prefix sum array to calculate sum in range efficiently
        vector<int> prefix(n, 0);
        prefix[0] = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }

        int result = INT_MAX; // Store minimum coins to remove
        int prev   = 0;       // Sum of coins to be removed from piles before index i

        for (int i = 0; i < n; i++) {
            // Find index of first pile > arr[i] + k using upper_bound
            int idx = upper_bound(arr.begin() + i, arr.end(), arr[i] + k) - arr.begin();

            if (i > 0) {
                prev = prefix[i - 1]; // Coins to remove from all piles before i
            }

            // Coins to remove from all piles beyond idx that are > arr[i] + k
            int totalToRemove = prev + prefix[n - 1] - prefix[idx - 1] - (arr[i] + k) * (n - idx);

            // Update result with minimum coins to remove
            result = min(result, totalToRemove);
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 5, 1, 2, 5, 1], k = 3
 * Step 1: Sort arr => [1, 1, 1, 2, 5, 5]
 * Step 2: prefix = [1, 2, 3, 5, 10, 15]
 *
 * Loop i = 0 (arr[i] = 1)
 * - upper_bound for 1 + 3 = 4 → idx = 4 (arr[4] = 5)
 * - prev = 0
 * - totalToRemove = 0 + 15 - 5 - (1+3)*(6-4) = 15 - 5 - 8 = 2
 * - result = min(INF, 2) = 2
 *
 * Loop i = 1 (arr[i] = 1)
 * - upper_bound for 1+3=4 → idx = 4
 * - prev = prefix[0] = 1
 * - totalToRemove = 1 + 15 - 5 - 8 = 3
 * - result = min(2, 3) = 2
 *
 * Loop i = 2 (arr[i] = 1)
 * - upper_bound idx = 4
 * - prev = 2
 * - totalToRemove = 2 + 15 - 5 - 8 = 4
 * - result = min(2, 4) = 2
 *
 * Loop i = 3 (arr[i] = 2)
 * - upper_bound for 2+3=5 → idx = 6
 * - prev = prefix[2] = 3
 * - totalToRemove = 3 + 15 - 15 - 0 = 3
 * - result = min(2, 3) = 2
 *
 * Loop i = 4 (arr[i] = 5)
 * - upper_bound for 5+3=8 → idx = 6
 * - prev = prefix[3] = 5
 * - totalToRemove = 5 + 15 - 15 - 0 = 5
 * - result = min(2, 5) = 2
 *
 * Loop i = 5 (arr[i] = 5)
 * - same as above, totalToRemove = 10
 * - result = min(2, 10) = 2
 *
 * Final Answer: 2
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Sort the array, then for each element arr[i], assume it's the smallest allowed value. Use upper_bound to find the last pile that can remain with value ≤ arr[i]+k. Remove coins from all piles before i and from those after idx that exceed arr[i]+k.
// Time Complexity: O(n log n) - due to sorting and binary search for each element.
// Space Complexity: O(n) - for storing prefix sums.
class Solution {
    // Custom upper_bound implementation (first index with value > target)
    private int upperBound(int[] arr, int start, int end, int target) {
        int low = start, high = end;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] <= target) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;
    }
    
    public int minimumCoins(int[] arr, int k) {
        int n = arr.length;

        // Sort the array to process piles in increasing order
        Arrays.sort(arr);

        // Compute prefix sum array to calculate sum in range efficiently
        int[] prefix = new int[n];
        prefix[0]    = arr[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }

        int result = Integer.MAX_VALUE; // Store minimum coins to remove
        int prev   = 0;                 // Sum of coins to be removed from piles before index i

        for (int i = 0; i < n; i++) {
            // Find index of first element greater than arr[i] + k using binary search
            int idx = upperBound(arr, i, n, arr[i] + k);

            if (i > 0) {
                prev = prefix[i - 1]; // Coins to remove from all piles before i
            }

            // Coins to remove from all piles beyond idx that are > arr[i] + k
            int totalToRemove = prev + prefix[n - 1] - prefix[idx - 1] - (arr[i] + k) * (n - idx);

            // Update result with minimum coins to remove
            result = Math.min(result, totalToRemove);
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 5, 1, 2, 5, 1], k = 3
 * Step 1: Sort arr => [1, 1, 1, 2, 5, 5]
 * Step 2: prefix = [1, 2, 3, 5, 10, 15]
 *
 * Loop i = 0 (arr[i] = 1)
 * - upper_bound for 1 + 3 = 4 → idx = 4 (arr[4] = 5)
 * - prev = 0
 * - totalToRemove = 0 + 15 - 5 - (1+3)*(6-4) = 15 - 5 - 8 = 2
 * - result = min(INF, 2) = 2
 *
 * Loop i = 1 (arr[i] = 1)
 * - upper_bound for 1+3=4 → idx = 4
 * - prev = prefix[0] = 1
 * - totalToRemove = 1 + 15 - 5 - 8 = 3
 * - result = min(2, 3) = 2
 *
 * Loop i = 2 (arr[i] = 1)
 * - upper_bound idx = 4
 * - prev = 2
 * - totalToRemove = 2 + 15 - 5 - 8 = 4
 * - result = min(2, 4) = 2
 *
 * Loop i = 3 (arr[i] = 2)
 * - upper_bound for 2+3=5 → idx = 6
 * - prev = prefix[2] = 3
 * - totalToRemove = 3 + 15 - 15 - 0 = 3
 * - result = min(2, 3) = 2
 *
 * Loop i = 4 (arr[i] = 5)
 * - upper_bound for 5+3=8 → idx = 6
 * - prev = prefix[3] = 5
 * - totalToRemove = 5 + 15 - 15 - 0 = 5
 * - result = min(2, 5) = 2
 *
 * Loop i = 5 (arr[i] = 5)
 * - same as above, totalToRemove = 10
 * - result = min(2, 10) = 2
 *
 * Final Answer: 2
 *
 */
