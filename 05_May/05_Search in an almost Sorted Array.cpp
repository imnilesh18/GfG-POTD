/*
 * GfG Link: https://www.geeksforgeeks.org/problems/search-in-an-almost-sorted-array/1
 *
 * Search in an almost Sorted Array
 *
 * Difficulty: MediumAccuracy: 55.8%Submissions: 3K+Points: 4Average Time: 20m
 *
 * Given a sorted integer array arr[] consisting of distinct elements, where some elements of the array are moved to either of the adjacent positions, i.e. arr[i] may be present at arr[i-1] or arr[i+1].
 * Given an integer target.  You have to return the index ( 0-based ) of the target in the array. If target is not present return -1.
 *
 * Examples:
 * Input: arr[] = [10, 3, 40, 20, 50, 80, 70], target = 40
 * Output: 2
 * Explanation: Index of 40 in the given array is 2.
 *
 * Input: arr[] = [10, 3, 40, 20, 50, 80, 70], target = 90
 * Output: -1
 * Explanation: 90 is not present in the array.
 *
 * Input: arr[] = [-20], target = -20
 * Output: 0
 * Explanation: -20 is the only element present in the array.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * -10^9 <= arr[i] <= 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Modified Binary Search checking mid, mid-1, and mid+1 due to possible adjacent swaps
// Time Complexity: O(log n) – since we eliminate at least two elements each time (mid and its adjacent positions)
// Space Complexity: O(1) – only constant extra space used
class Solution {
public:
    int findTarget(vector<int>& arr, int target) {
        int l = 0, r = arr.size() - 1;

        while (r >= l) {
            int mid = l + (r - l) / 2;        // calculate mid avoiding overflow

            // Check the middle 3 positions
            if (arr[mid] == target) {
                return mid;
            }
            if (mid > l && arr[mid - 1] == target) {
                return mid - 1;
            }
            if (mid < r && arr[mid + 1] == target) {
                return mid + 1;
            }

            // If target is smaller, move to the left skipping mid and mid-1
            if (arr[mid] > target) {
                r = mid - 2;
            }
            // If target is larger, move to the right skipping mid and mid+1
            else {
                l = mid + 2;
            }
        }

        // Element not found
        return -1;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [10, 3, 40, 20, 50, 80, 70], target = 40
 *
 * Initial: l = 0, r = 6
 * Step 1:
 *  mid = 3, arr[mid] = 20
 *  arr[mid] != target, arr[mid - 1] = 40 -> match found
 *  return mid - 1 = 2
 *
 * Output: 2
 *
 * Example 2:
 * Input: arr = [10, 3, 40, 20, 50, 80, 70], target = 90
 *
 * Initial: l = 0, r = 6
 * Step 1: mid = 3, arr[mid] = 20 -> 20 < 90 -> l = 5
 * Step 2: mid = 5, arr[mid] = 80 -> 80 < 90 -> l = 7 (> r)
 * Exit loop, return -1
 *
 * Output: -1
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Modified Binary Search by checking mid, mid-1, and mid+1 because elements may be displaced to adjacent positions
// Time Complexity: O(log n) – since we eliminate at least two elements each iteration
// Space Complexity: O(1) – constant space used
class Solution {
    public int findTarget(int arr[], int target) {
        int l = 0, r = arr.length - 1;

        while (r >= l) {
            int mid = l + (r - l) / 2; // avoid overflow

            // Check the middle 3 positions
            if (arr[mid] == target) {
                return mid;
            }
            if (mid > l && arr[mid - 1] == target) {
                return mid - 1;
            }
            if (mid < r && arr[mid + 1] == target) {
                return mid + 1;
            }

            // If target is smaller, move left skipping mid and mid-1
            if (arr[mid] > target) {
                r = mid - 2;
            }
            // If target is greater, move right skipping mid and mid+1
            else {
                l = mid + 2;
            }
        }

        // Target not found
        return -1;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [10, 3, 40, 20, 50, 80, 70], target = 40
 *
 * Initial: l = 0, r = 6
 * Step 1:
 *  mid = 3 -> arr[mid] = 20
 *  arr[mid] != target
 *  arr[mid - 1] = 40 == target -> return mid - 1 = 2
 *
 * Output: 2
 *
 * Input: arr = [10, 3, 40, 20, 50, 80, 70], target = 90
 *
 * Initial: l = 0, r = 6
 * Step 1: mid = 3, arr[mid] = 20 -> target > 20, l = 5
 * Step 2: mid = 5, arr[mid] = 80 -> target > 80, l = 7
 * Loop ends (l > r), return -1
 *
 * Output: -1
 *
 */
