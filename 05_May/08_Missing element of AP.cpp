/*
 * Missing element of AP
 *
 * Difficulty: Medium Accuracy: 34.32% Submissions: 63K+ Points: 4
 *
 * Given a sorted array arr[] that represents an Arithmetic Progression (AP) with exactly one missing element, find the missing number.
 *
 * Note: An element will always exist that, upon inserting into a sequence forms Arithmetic progression. If the given sequence already forms a valid complete AP, return the (n+1)-th element that would come next in the sequence.
 *
 * Examples:
 *
 * Input: arr[] = [2, 4, 8, 10, 12, 14]
 * Output: 6
 * Explanation: Actual AP should be 2, 4, 6, 8, 10, 12, 14.
 *
 * Input: arr[] = [1, 6, 11, 16, 21, 31]
 * Output: 26
 * Explanation: Actual AP should be 1, 6, 11, 16, 21, 26, 31.
 *
 * Input: arr[] = [4, 7, 10, 13, 16]
 * Output: 19
 * Explanation: Since the sequence already forms a valid AP, the next element after 16 in the sequence would be 19. Therefore, the output is 19.
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 2*10^7
 */

/************************************************************ C++ ************************************************/

// Approach: Use Binary Search to find the first element that breaks the AP pattern. If no element is missing, return next AP element.
// Time Complexity: O(log n) – Binary search narrows down the search range by half at each step.
// Space Complexity: O(1) – Only constant extra space used.
class Solution {
public:
    // Utility function to find the missing element using binary search
    int findMissingUtil(vector<int>& arr, int low, int high, int diff) {
        if (high <= low) {
            return INT_MAX;
        }

        // Find index of middle element
        int mid = low + (high - low) / 2;

        // If the next element after mid is not following AP, return the expected one
        if (arr[mid + 1] - arr[mid] != diff) {
            return arr[mid] + diff;
        }

        // If the previous element before mid is not following AP, return the expected one
        if (mid > 0 && arr[mid] - arr[mid - 1] != diff) {
            return arr[mid - 1] + diff;
        }

        // If element at mid is correct, search in the right half
        if (arr[mid] == arr[0] + mid * diff) {
            return findMissingUtil(arr, mid + 1, high, diff);
        }

        // Else search in the left half
        return findMissingUtil(arr, low, mid - 1, diff);
    }

    int findMissing(vector<int>& arr) {
        int n = arr.size();

        // Estimate the common difference of the AP
        int diff = (arr[1] - arr[0] == arr[n - 1] - arr[n - 2]) ? arr[1] - arr[0] :
                   ((arr[1] - arr[0] == (arr[n - 1] - arr[0]) / n) ? arr[1] - arr[0] :
                    arr[n - 1] - arr[n - 2]);

        // If all elements are the same
        if (diff == 0) {
            return arr[0];
        }

        // Find the missing element using binary search
        int res = findMissingUtil(arr, 0, n - 1, diff);

        // If no element is missing, return the next AP element
        return (res == INT_MAX) ? (arr[0] + (n) * diff) : res;
    }
};

/*
 *
 * Dry Run
 * Input: arr[] = [2, 4, 8, 10, 12, 14]
 *
 * Step 1: n = 6
 * Step 2: Estimate diff:
 *  - arr[1] - arr[0] = 2
 *  - arr[n-1] - arr[n-2] = 2
 *  => diff = 2
 *
 * Step 3: Call findMissingUtil(arr, 0, 5, 2)
 *
 * First Call:
 *  low = 0, high = 5, mid = 2
 *  arr[2] = 8, arr[3] = 10 → diff is 2 → OK
 *  arr[2] == arr[0] + 2 * 2 → 8 == 2 + 4 → OK
 *  → Recur right: findMissingUtil(3, 5, 2)
 *
 * Second Call:
 *  low = 3, high = 5, mid = 4
 *  arr[4] = 12, arr[5] = 14 → diff is 2 → OK
 *  arr[4] == arr[0] + 4 * 2 → 12 == 2 + 8 → OK
 *  → Recur right: findMissingUtil(5, 5, 2)
 *
 * Third Call:
 *  low = 5, high = 5 → return INT_MAX
 *
 * Final Step: res = INT_MAX → No missing in array → return next AP element:
 *  arr[0] + n * diff = 2 + 6 * 2 = 14 → already in array
 *  next = 16 → wrong! So backtrack...
 *
 * Missed logic in Dry Run. Let's go back!
 *
 * Redo First Call:
 *  mid = 2, arr[mid+1] - arr[mid] = 10 - 8 = 2 → OK
 *  arr[mid] - arr[mid-1] = 8 - 4 = 4 → Not equal to 2
 *  → Missing element is arr[mid-1] + diff = 4 + 2 = 6
 *
 * Output: 6
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Binary Search to find the first element that breaks the AP pattern. If no element is missing, return next AP element.
// Time Complexity: O(log n) – Binary search narrows down the search range by half at each step.
// Space Complexity: O(1) – Only constant extra space used.
class Solution {
    // Utility function to find missing element using binary search
    int findMissingUtil(int[] arr, int low, int high, int diff) {
        if (high <= low) {
            return Integer.MAX_VALUE;
        }

        // Find index of middle element
        int mid = low + (high - low) / 2;

        // If the next element after mid is not following AP, return the expected one
        if (arr[mid + 1] - arr[mid] != diff) {
            return arr[mid] + diff;
        }

        // If the previous element before mid is not following AP, return the expected one
        if (mid > 0 && arr[mid] - arr[mid - 1] != diff) {
            return arr[mid - 1] + diff;
        }

        // If element at mid is correct, search in the right half
        if (arr[mid] == arr[0] + mid * diff) {
            return findMissingUtil(arr, mid + 1, high, diff);
        }

        // Else search in the left half
        return findMissingUtil(arr, low, mid - 1, diff);
    }
    
    public int findMissing(int[] arr) {
        int n = arr.length;

        // Estimate the common difference of the AP
        int diff = (arr[1] - arr[0] == arr[n - 1] - arr[n - 2]) ? arr[1] - arr[0] :
                   ((arr[1] - arr[0] == (arr[n - 1] - arr[0]) / n) ? arr[1] - arr[0] :
                    arr[n - 1] - arr[n - 2]);

        // If all elements are the same
        if (diff == 0) {
            return arr[0];
        }

        // Find the missing element using binary search
        int res = findMissingUtil(arr, 0, n - 1, diff);

        // If no element is missing, return the next AP element
        return (res == Integer.MAX_VALUE) ? (arr[0] + n * diff) : res;
    }
}

/*
 *
 * Dry Run
 * Input: arr[] = [2, 4, 8, 10, 12, 14]
 *
 * Step 1: n = 6
 * Step 2: Estimate diff:
 *  - arr[1] - arr[0] = 2
 *  - arr[n-1] - arr[n-2] = 2
 *  => diff = 2
 *
 * Step 3: Call findMissingUtil(arr, 0, 5, 2)
 *
 * First Call:
 *  low = 0, high = 5, mid = 2
 *  arr[2] = 8, arr[3] = 10 → diff is 2 → OK
 *  arr[2] - arr[1] = 8 - 4 = 4 → Not equal to 2
 *  → Missing element is arr[1] + diff = 4 + 2 = 6
 *
 * Output: 6
 *
 */
