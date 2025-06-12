/*
 * GfG Link: https://www.geeksforgeeks.org/problems/k-closest-elements3619/1
 *
 * K closest elements
 *
 * Difficulty: Medium Accuracy: 15.96% Submissions: 74K+ Points: 4 Average Time: 30m
 *
 * You are given a sorted array arr[] of unique integers, an integer k, and a target value x. Return exactly k elements from the array closest to x, excluding x if it exists.
 *
 * An element a is closer to x than b if:
 * a - x| < |b - x|, or
 |a - x| == |b - x| and a > b (i.e., prefer the larger element if tied)
 * Return the k closest elements in order of closeness.
 *
 * Examples:
 *
 * Input: arr[] = [1, 3, 4, 10, 12], k = 2, x = 4
 * Output: 3 1
 * Explanation: 4 is excluded, Closest elements to 4 are: 3 (1), 1 (3). So, the 2 closest elements are: 3 1
 *
 * Input: arr[] = [12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56], k = 4, x = 35
 * Output: 39 30 42 45
 * Explanation: First closest element to 35 is 39.
 * Second closest element to 35 is 30.
 * Third closest element to 35 is 42.
 * And fourth closest element to 35 is 45.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ k ≤ arr.size()
 * 1 ≤ x ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Binary search to find the last element < x, then use two pointers to find k closest elements using absolute difference and tiebreaker
// Time Complexity: O(log n + k) => O(log n) for binary search and O(k) for collecting k closest elements
// Space Complexity: O(k) => storing the result of k elements
class Solution {
public:
    vector<int> printKClosest(vector<int> arr, int k, int x) {
        int n   = arr.size();
        int pos = -1;

        // Step 1: Binary Search to find last element < x
        int low = 0, high = n - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] < x) {
                pos = mid; // update pos if arr[mid] is less than x
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        // Step 2: Two pointers: Pick k closest using distance comparison
        int left = pos, right = pos + 1;

        if (right < n && arr[right] == x) {
            right++;
        }

        vector<int> result;

        while (left >= 0 && right < n && result.size() < k) {
            int leftDiff  = abs(arr[left] - x);
            int rightDiff = abs(arr[right] - x);

            // Prefer the smaller difference; if tie, prefer the larger element
            if (leftDiff < rightDiff) {
                result.push_back(arr[left]);
                left--;
            } else {
                result.push_back(arr[right]);
                right++;
            }
        }

        // Fill remaining if any
        while (left >= 0 && result.size() < k) {
            result.push_back(arr[left]);
            left--;
        }

        while (right < n && result.size() < k) {
            result.push_back(arr[right]);
            right++;
        }

        return result;
    }
};

/*
 *
 * Dry Run for Input: arr = [12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56], k = 4, x = 35
 *
 * Step 1: Binary search to find last element < x = 35
 * mid = 6 -> arr[6] = 42 > 35 => high = 5
 * mid = 2 -> arr[2] = 22 < 35 => pos = 2, low = 3
 * mid = 4 -> arr[4] = 35 == 35 => high = 3
 * mid = 3 -> arr[3] = 30 < 35 => pos = 3, low = 4
 * Binary search ends, pos = 3
 *
 * Step 2: left = 3 (arr[3] = 30), right = 4 (arr[4] = 35)
 * arr[right] == x → skip → right = 5 (arr[5] = 39)
 *
 * Step 3: Two-pointer selection:
 * left = 3 (30), right = 5 (39)
 *  |30 - 35| = 5, |39 - 35| = 4 → pick 39 → res = [39]
 * left = 3 (30), right = 6 (42)
 *  |30 - 35| = 5, |42 - 35| = 7 → pick 30 → res = [39, 30]
 * left = 2 (22), right = 6 (42)
 * |22 - 35| = 13, |42 - 35| = 7 → pick 42 → res = [39, 30, 42]
 * left = 2 (22), right = 7 (45)
 *  |22 - 35| = 13, |45 - 35| = 10 → pick 45 → res = [39, 30, 42, 45]
 *
 * 4 elements collected → done!
 *
 * Final Output: [39, 30, 42, 45]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Binary search to find the last element < x, then use two pointers to find k closest elements using absolute difference and tiebreaker
// Time Complexity: O(log n + k) => O(log n) for binary search and O(k) for collecting k closest elements
// Space Complexity: O(k) => storing the result of k elements
class Solution {
    int[] printKClosest(int[] arr, int k, int x) {
        int n   = arr.length;
        int pos = -1;

        // Step 1: Binary Search to find last element < x
        int low = 0, high = n - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] < x) {
                pos = mid; // update pos if arr[mid] is less than x
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        // Step 2: Two pointers: Pick k closest using distance comparison
        int left = pos, right = pos + 1;

        if (right < n && arr[right] == x) {
            right++;
        }

        ArrayList<Integer> resultList = new ArrayList<>();

        while (left >= 0 && right < n && resultList.size() < k) {
            int leftDiff  = Math.abs(arr[left] - x);
            int rightDiff = Math.abs(arr[right] - x);

            // Prefer the smaller difference; if tie, prefer the larger element
            if (leftDiff < rightDiff) {
                resultList.add(arr[left]);
                left--;
            } else {
                resultList.add(arr[right]);
                right++;
            }
        }

        // Fill remaining if any
        while (left >= 0 && resultList.size() < k) {
            resultList.add(arr[left]);
            left--;
        }

        while (right < n && resultList.size() < k) {
            resultList.add(arr[right]);
            right++;
        }

        // Convert ArrayList to array for return
        int[] result = new int[resultList.size()];
        for (int i = 0; i < resultList.size(); i++) {
            result[i] = resultList.get(i);
        }

        return result;
    }
}

/*
 *
 * Dry Run for Input: arr = [12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56], k = 4, x = 35
 *
 * Step 1: Binary search to find last element < x = 35
 * mid = 6 -> arr[6] = 42 > 35 => high = 5
 * mid = 2 -> arr[2] = 22 < 35 => pos = 2, low = 3
 * mid = 4 -> arr[4] = 35 == 35 => high = 3
 * mid = 3 -> arr[3] = 30 < 35 => pos = 3, low = 4
 * Binary search ends, pos = 3
 *
 * Step 2: left = 3 (arr[3] = 30), right = 4 (arr[4] = 35)
 * arr[right] == x → skip → right = 5 (arr[5] = 39)
 *
 * Step 3: Two-pointer selection:
 * left = 3 (30), right = 5 (39)
 *  |30 - 35| = 5, |39 - 35| = 4 → pick 39 → res = [39]
 * left = 3 (30), right = 6 (42)
 *  |30 - 35| = 5, |42 - 35| = 7 → pick 30 → res = [39, 30]
 * left = 2 (22), right = 6 (42)
 * |22 - 35| = 13, |42 - 35| = 7 → pick 42 → res = [39, 30, 42]
 * left = 2 (22), right = 7 (45)
 *  |22 - 35| = 13, |45 - 35| = 10 → pick 45 → res = [39, 30, 42, 45]
 *
 * 4 elements collected → done!
 *
 * Final Output: [39, 30, 42, 45]
 *
 */
