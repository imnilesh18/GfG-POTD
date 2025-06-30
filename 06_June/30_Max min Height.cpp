/*
 * GfG Link: https://www.geeksforgeeks.org/problems/max-min-height--170647/1
 *
 * Max min Height
 *
 * Difficulty: Hard Accuracy: 62.86% Submissions: 18K+ Points: 8
 *
 * Given a garden with n flowers planted in a row, that is represented by an array arr[], where arr[i] denotes the height of the ith flower.You will water them for k days. In one day you can water w continuous flowers. Whenever you water a flower its height increases by 1 unit. You have to maximize the minimum height of all flowers after  k days of watering.
 *
 * Examples:
 *
 * Input: arr[] = [2, 3, 4, 5, 1], k = 2, w = 2
 * Output: 2
 * Explanation: The minimum height after watering is 2.
 * Day 1: Water the last two flowers -> arr becomes [2, 3, 4, 6, 2]
 * Day 2: Water the last two flowers -> arr becomes [2, 3, 4, 7, 3]
 *
 * Input: arr[] = [5, 8], k = 5, w = 1
 * Output: 9
 * Explanation: The minimum height after watering is 9.
 * Day 1 - Day 4: Water the first flower -> arr becomes [9, 8]
 * Day 5: Water the second flower -> arr becomes [9, 9]
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ w ≤ arr.size()
 * 1 ≤ k ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Use binary search to maximize the minimum possible height. For each candidate height, check if it can be achieved by at most k waterings using a difference array for efficient range update simulation.
// Time Complexity: O(n * log k), where n is the size of arr and log k is from binary search steps.
// Space Complexity: O(n), for the water difference array.
class Solution {
public:
    // Helper function to check if targetHeight can be achieved with <= k waterings
    bool isPossible(vector<int>& arr, int k, int w, int targetHeight) {
        int         n = arr.size();
        vector<int> water(n + 1, 0);  // Difference array for efficient range addition
        int         daysUsed  = 0;
        int         currWater = 0;

        for (int i = 0; i < n; i++) {
            currWater += water[i];  // Add the effect of previous waterings
            int currHeight = arr[i] + currWater;
            if (currHeight < targetHeight) {
                int need = targetHeight - currHeight; // Water needed at this point
                daysUsed += need;
                if (daysUsed > k) {                   // If exceeded allowed waterings, not possible
                    return false;
                }
                currWater += need;        // Add immediate effect
                water[i]  += need;        // Start effect at i
                if (i + w <= n) {
                    water[i + w] -= need; // End effect after window
                }
            }
        }
        return true;
    }

    // Main function to maximize the minimum height
    int maxMinHeight(vector<int>& arr, int k, int w) {
        int low  = *min_element(arr.begin(), arr.end());
        int high = low + k;

        int result = 0;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (isPossible(arr, k, w, mid)) {
                result = mid;        // Try to go higher
                low    = mid + 1;
            } else {
                high = mid - 1;      // Try lower
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 2, 2, 2, 1, 1], k = 2, w = 3
 *
 * 1. Binary search: low = 1, high = 3 (since min(arr)=1, max we can reach = 1 + k = 3)
 * 2. Try mid = 2:
 *     - isPossible(arr, 2, 3, 2):
 *         i=0: currHeight = 2, no water needed.
 *         i=1: currHeight = 2, no water needed.
 *         i=2: currHeight = 2, no water needed.
 *         i=3: currHeight = 2, no water needed.
 *         i=4: currHeight = 1, need 1 water. daysUsed = 1, water[4] += 1.
 *         i=5: currWater includes water[4]=1, so currHeight = 1+1=2, no more water needed.
 *         All daysUsed = 1 <= 2. So mid=2 is possible.
 *     - Update result=2, low=3
 * 3. Try mid = 3:
 *     - isPossible(arr, 2, 3, 3):
 *         i=0: currHeight = 2, need 1 water. daysUsed = 1, water[0] += 1, water[3] -= 1.
 *         i=1: currWater=1, currHeight=3, no water needed.
 *         i=2: currWater=1, currHeight=3, no water needed.
 *         i=3: currWater+=water[3]=-1 (currWater=0), currHeight=2, need 1 water. daysUsed = 2, water[3] += 1, water[6] -= 1.
 *         i=4: currWater=1, currHeight=2, need 1 water. daysUsed = 3 (> k), return false.
 *     - mid=3 is not possible, high=2
 * 4. Loop ends. Return result=2.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use binary search to maximize the minimum possible height. For each candidate height, check if it can be achieved by at most k waterings using a difference array for efficient range update simulation.
// Time Complexity: O(n * log k), where n is the size of arr and log k is from binary search steps.
// Space Complexity: O(n), for the water difference array.
class Solution {
    // Helper function to check if targetHeight can be achieved with <= k waterings
    private boolean isPossible(int[] arr, int k, int w, int targetHeight) {
        int n = arr.length;
        int[] water = new int[n + 1]; // Difference array for efficient range addition
        int daysUsed  = 0;
        int currWater = 0;

        for (int i = 0; i < n; i++) {
            currWater += water[i]; // Add the effect of previous waterings
            int currHeight = arr[i] + currWater;
            if (currHeight < targetHeight) {
                int need = targetHeight - currHeight; // Water needed at this point
                daysUsed += need;
                if (daysUsed > k) {                   // If exceeded allowed waterings, not possible
                    return false;
                }
                currWater += need;        // Add immediate effect
                water[i]  += need;        // Start effect at i
                if (i + w <= n) {
                    water[i + w] -= need; // End effect after window
                }
            }
        }
        return true;
    }
    
    // Main function to maximize the minimum height
    public int maxMinHeight(int[] arr, int k, int w) {
        int low = Integer.MAX_VALUE;

        for (int v : arr) {
            low = Math.min(low, v);
        }
        int high = low + k;

        int result = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (isPossible(arr, k, w, mid)) {
                result = mid;      // Try to go higher
                low    = mid + 1;
            } else {
                high = mid - 1;    // Try lower
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 2, 2, 2, 1, 1], k = 2, w = 3
 *
 * 1. Binary search: low = 1, high = 3 (since min(arr)=1, max we can reach = 1 + k = 3)
 * 2. Try mid = 2:
 *     - isPossible(arr, 2, 3, 2):
 *         i=0: currHeight = 2, no water needed.
 *         i=1: currHeight = 2, no water needed.
 *         i=2: currHeight = 2, no water needed.
 *         i=3: currHeight = 2, no water needed.
 *         i=4: currHeight = 1, need 1 water. daysUsed = 1, water[4] += 1.
 *         i=5: currWater includes water[4]=1, so currHeight = 1+1=2, no more water needed.
 *         All daysUsed = 1 <= 2. So mid=2 is possible.
 *     - Update result=2, low=3
 * 3. Try mid = 3:
 *     - isPossible(arr, 2, 3, 3):
 *         i=0: currHeight = 2, need 1 water. daysUsed = 1, water[0] += 1, water[3] -= 1.
 *         i=1: currWater=1, currHeight=3, no water needed.
 *         i=2: currWater=1, currHeight=3, no water needed.
 *         i=3: currWater+=water[3]=-1 (currWater=0), currHeight=2, need 1 water. daysUsed = 2, water[3] += 1, water[6] -= 1.
 *         i=4: currWater=1, currHeight=2, need 1 water. daysUsed = 3 (> k), return false.
 *     - mid=3 is not possible, high=2
 * 4. Loop ends. Return result=2.
 *
 */
