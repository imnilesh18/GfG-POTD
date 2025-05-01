/*
 * GfG Link: https://www.geeksforgeeks.org/problems/maximum-value-in-a-bitonic-array3001/1
 *
 * Bitonic Point
 *
 * Difficulty: EasyAccuracy: 58.67%Submissions: 137K+Points: 2Average Time: 15m
 *
 * Given an array of integers arr[] that is first strictly increasing and then maybe strictly decreasing, find the bitonic point, that is the maximum element in the array.
 * Bitonic Point is a point before which elements are strictly increasing and after which elements are strictly decreasing.
 *
 * Note: It is guaranteed that the array contains exactly one bitonic point.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 4, 5, 7, 8, 3]
 * Output: 8
 * Explanation: Elements before 8 are strictly increasing [1, 2, 4, 5, 7] and elements after 8 are strictly decreasing [3].
 *
 * Input: arr[] = [10, 20, 30, 40, 50]
 * Output: 50
 * Explanation: Elements before 50 are strictly increasing [10, 20, 30 40] and there are no elements after 50.
 *
 * Input: arr[] = [120, 100, 80, 20, 0]
 * Output: 120
 * Explanation: There are no elements before 120 and elements after 120 are strictly decreasing [100, 80, 20, 0].
 *
 * Constraints:
 * 3 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^6
 */

// Intuition:

/*
 * A Bitonic array is one that increases strictly to a point and then strictly decreases.
 * The point where the array changes direction (from increasing to decreasing) is called the Bitonic Point (Peak).
 * Since the array increases and then decreases, the peak element is greater than its neighbors.
 * We can use binary search to efficiently find this peak element by checking mid and its neighbors.
 *
 * Example:
 * Input: arr[] = [1, 2, 4, 5, 7, 8, 3]
 * Step 1: low = 1, high = 5 (excluding first and last which are edge cases)
 * Step 2: mid = (1 + 5) / 2 = 3 → arr[3] = 5
 *         → arr[3] < arr[4] → Move right → low = 4
 * Step 3: mid = (4 + 5) / 2 = 4 → arr[4] = 7
 *         → arr[4] < arr[5] → Move right → low = 5
 * Step 4: mid = 5 → arr[5] = 8
 *         → arr[5] > arr[4] && arr[5] > arr[6] → Peak found → return 8
 *
 * Conclusion:
 * By checking the relationship between mid and its neighbors, we can keep narrowing the search space.
 * This guarantees an O(log n) time complexity for finding the Bitonic Point.
 */

/************************************************************ C++ ************************************************/

// Approach: Use Binary Search to find the peak (bitonic point) where arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]
// Time Complexity: O(log n) – We are reducing the search space by half each time using binary search.
// Space Complexity: O(1) – No extra space is used apart from variables.
class Solution {
public:
    int findMaximum(vector<int>& arr) {
        int n = arr.size();

        // If array has only one element or first element is greater than second, it's the maximum
        if (n == 1 || arr[0] > arr[1]) {
            return arr[0];
        }

        // If last element is greater than its previous, it's the maximum
        if (arr[n - 1] > arr[n - 2]) {
            return arr[n - 1];
        }

        // Initialize search space for binary search
        int low = 1, high = n - 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // If middle element is greater than its neighbors, it's the peak
            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
                return arr[mid];
            }

            // If middle is smaller than next, peak lies to the right
            if (arr[mid] < arr[mid + 1]) {
                low = mid + 1;
            }
            // Else, peak lies to the left
            else{
                high = mid - 1;
            }
        }

        // Return the element at high as fallback (though this point is never reached due to constraints)
        return arr[high];
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 2, 4, 5, 7, 8, 3]
 * n = 7
 * Initial: low = 1, high = 5
 *
 * Iteration 1:
 * mid = (1+5)/2 = 3, arr[mid] = 5
 * arr[3] = 5 < arr[4] = 7 → Go right → low = 4
 *
 * Iteration 2:
 * mid = (4+5)/2 = 4, arr[mid] = 7
 * arr[4] = 7 < arr[5] = 8 → Go right → low = 5
 *
 * Iteration 3:
 * mid = (5+5)/2 = 5, arr[mid] = 8
 * arr[5] = 8 > arr[4] = 7 and arr[5] > arr[6] = 3 → Peak found
 * Return 8
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Binary Search to find the peak (bitonic point) where arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]
// Time Complexity: O(log n) – We reduce the search space by half in each step using binary search.
// Space Complexity: O(1) – Constant space used, no additional data structures.
class Solution {
    public int findMaximum(int[] arr) {
        int n = arr.length;

        // If array has only one element or first element is greater than second, it's the maximum
        if (n == 1 || arr[0] > arr[1]) {
            return arr[0];
        }

        // If last element is greater than its previous, it's the maximum
        if (arr[n - 1] > arr[n - 2]) {
            return arr[n - 1];
        }

        // Binary search space: excluding first and last (already checked)
        int low = 1, high = n - 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // If middle element is greater than both neighbors, it's the peak
            if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
                return arr[mid];
            }

            // If mid is smaller than next, go right
            if (arr[mid] < arr[mid + 1]) {
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }

        // Fallback return, although this line won't be reached due to guaranteed constraints
        return arr[high];
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 2, 4, 5, 7, 8, 3]
 * n = 7
 * Initial: low = 1, high = 5
 *
 * Iteration 1:
 * mid = (1 + 5) / 2 = 3, arr[mid] = 5
 * arr[3] = 5 < arr[4] = 7 → Move right → low = 4
 *
 * Iteration 2:
 * mid = (4 + 5) / 2 = 4, arr[4] = 7
 * arr[4] = 7 < arr[5] = 8 → Move right → low = 5
 *
 * Iteration 3:
 * mid = (5 + 5) / 2 = 5, arr[5] = 8
 * arr[5] > arr[4] and arr[5] > arr[6] → Peak found → return 8
 *
 */
