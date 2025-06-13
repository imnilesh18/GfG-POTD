/*
 * GfG Link: https://www.geeksforgeeks.org/problems/koko-eating-bananas/1
 *
 * Koko Eating Bananas
 *
 * Difficulty: Medium Accuracy: 50.27% Submissions: 23K+ Points: 4 Average Time: 20m
 *
 * Koko is given an array arr[], where each element represents a pile of bananas. She has exactly k hours to eat all the bananas.
 * Each hour, Koko can choose one pile and eat up to s bananas from it.
 * If the pile has at least s bananas, she eats exactly s bananas.
 * If the pile has fewer than s bananas, she eats the entire pile in that hour.
 * Koko can only eat from one pile per hour.
 * Your task is to find the minimum value of s (bananas per hour) such that Koko can finish all the piles within k hours.
 *
 * Examples:
 *
 * Input: arr[] = [3, 6, 7, 11] , k = 8
 * Output: 4
 * Explanation: Koko eats at least 4 bananas per hour to finish all piles within 8 hours, as she can consume each pile in 1 + 2 + 2 + 3 = 8 hours.
 *
 * Input: arr[] = [30, 11, 23, 4, 20], k = 5
 * Output: 30
 * Explanation: With 30 bananas per hour, Koko completes each pile in 1 hour, totaling 5 hours, which matches k = 5.
 *
 * Input: arr[] = [5, 10, 15, 20], k = 7
 * Output: 10
 * Explanation: At 10 bananas per hour, Koko finishes in 7 hours, just within the k = 7 limit.
 *
 * Constraint:
 * 1 <= arr.size() <= 10^5
 * 1 <= arr[i] <= 10^6
 * arr.size() <= k <= 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Use binary search on possible eating speeds from 1 to max(arr). For each speed 'mid', check if Koko can eat all bananas within 'k' hours. Use ceiling division to compute hours needed per pile.
// Time Complexity: O(n * log(max(arr))) where n is the size of the array and max(arr) is the maximum pile size. Binary search runs in log(max) and for each mid, we loop through all n piles.
// Space Complexity: O(1) – only constant extra space is used.
class Solution {
public:

    // Function to check if Koko can finish all bananas at speed 'mid' within 'k' hours
    bool finish(vector<int>& arr, int mid, int k) {
        int hours = 0;

        for (int i = 0; i < arr.size(); i++) {
            hours += arr[i] / mid;         // Add full chunks
            if (arr[i] % mid != 0) {
                hours++;                   // Add 1 hour for leftover bananas
            }
        }

        return hours <= k;  // Return true if total hours needed is within limit
    }
    
    int kokoEat(vector<int>& arr, int k) {
        int low    = 1;
        int high   = *max_element(arr.begin(), arr.end()); // Max bananas in a pile
        int result = 0;

        while (low <= high) {
            int mid = (low + high) / 2;  // Mid speed

            if (finish(arr, mid, k)) {
                result = mid;        // Try smaller speed
                high   = mid - 1;
            } else {
                low = mid + 1;       // Need to try faster speed
            }
        }

        return result;  // Minimum speed at which Koko can eat all bananas
    }
};

/*
 *
 * Dry Run
 * Input: arr[] = [3, 6, 7, 11], k = 8
 * low = 1, high = 11 (max in array)
 *
 * 1st iteration: mid = (1+11)/2 = 6
 *   hours = ceil(3/6) + ceil(6/6) + ceil(7/6) + ceil(11/6)
 *         = 1 + 1 + 2 + 2 = 6 <= 8 → valid
 *   result = 6, try smaller → high = 5
 *
 * 2nd iteration: mid = (1+5)/2 = 3
 *   hours = ceil(3/3) + ceil(6/3) + ceil(7/3) + ceil(11/3)
 *         = 1 + 2 + 3 + 4 = 10 > 8 → too slow
 *   low = 4
 *
 * 3rd iteration: mid = (4+5)/2 = 4
 *   hours = ceil(3/4) + ceil(6/4) + ceil(7/4) + ceil(11/4)
 *         = 1 + 2 + 2 + 3 = 8 == 8 → valid
 *   result = 4, try smaller → high = 3
 *
 * Binary search ends → result = 4
 * Output: 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use binary search on eating speeds from 1 to max(arr). For each mid speed, compute the total hours needed. If within k, try smaller speeds. Else, try larger.
// Time Complexity: O(n * log(max(arr))) where n = arr.length and max(arr) is the largest pile. Binary search log(max), each step checks all piles.
// Space Complexity: O(1) – no extra space except for variables.
class Solution {
    // Helper function to check if Koko can finish all bananas at speed 'mid' within 'k' hours
    private boolean canFinish(int[] arr, int mid, int k) {
        int hours = 0;

        for (int bananas : arr) {
            hours += bananas / mid;
            if (bananas % mid != 0) {
                hours++; // Add extra hour if leftover bananas exist
            }
        }

        return hours <= k;
    }

    public int kokoEat(int[] arr, int k) {
        int low  = 1;
        int high = Integer.MIN_VALUE;

        // Find the maximum number in the array
        for (int bananas : arr) {
            high = Math.max(high, bananas);
        }

        int result = 0;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (canFinish(arr, mid, k)) {
                result = mid;       // Try smaller speed
                high   = mid - 1;
            } else {
                low = mid + 1;      // Try higher speed
            }
        }

        return result;
    }
}

/*
 *
 * Dry Run
 * Input: arr[] = [3, 6, 7, 11], k = 8
 * low = 1, high = 11 (max in array)
 *
 * 1st iteration: mid = (1+11)/2 = 6
 *   hours = ceil(3/6) + ceil(6/6) + ceil(7/6) + ceil(11/6)
 *         = 1 + 1 + 2 + 2 = 6 <= 8 → valid
 *   result = 6, try smaller → high = 5
 *
 * 2nd iteration: mid = (1+5)/2 = 3
 *   hours = ceil(3/3) + ceil(6/3) + ceil(7/3) + ceil(11/3)
 *         = 1 + 2 + 3 + 4 = 10 > 8 → too slow
 *   low = 4
 *
 * 3rd iteration: mid = (4+5)/2 = 4
 *   hours = ceil(3/4) + ceil(6/4) + ceil(7/4) + ceil(11/4)
 *         = 1 + 2 + 2 + 3 = 8 == 8 → valid
 *   result = 4, try smaller → high = 3
 *
 * Binary search ends → result = 4
 * Output: 4
 *
 */
