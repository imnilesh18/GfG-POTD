/*
 * GfG Link: https://www.geeksforgeeks.org/problems/smallest-divisor/1
 *
 * Smallest Divisor
 *
 * Difficulty: Medium Accuracy: 50.74% Submissions: 12K+ Points: 4 Average Time: 25m
 *
 * Given an integer array arr[] and an integer k (where k ≥ arr.length), find the smallest positive integer divisor such that the sum of the ceiling values of each element in arr[] divided by this divisor is less than or equal to k.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 5, 9], k = 6
 * Output: 5
 * Explanation: 5 is the smallest divisor having sum of quotients (1 + 1 + 1 + 2 = 5) less than or equal to 6.
 *
 * Input: arr[] = [1, 1, 1, 1], k = 4
 * Output: 1
 * Explanation: 1 is the smallest divisor having sum of quotients (1 + 1 + 1 + 1 = 4) less than or equal to 4.
 *
 * Constraints:
 * 1  ≤  arr.size()  ≤ 10^5
 * 1  ≤  arr[i]  ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Use binary search on the divisor in the range [1, max(arr)], and for each candidate divisor, check if the sum of ceil(arr[i]/divisor) is ≤ k; adjust search bounds based on validity.
// Time Complexity: O(n log m) where n = arr.size() and m = max(arr) due to binary search over [1, m] and O(n) check each time.
// Space Complexity: O(1) auxiliary space besides input.
class Solution {
public:

    bool valid(vector<int>& arr, int mid, int k) {
        int sum = 0;

        for (int i = 0; i < arr.size(); i++) {
            sum += ceil((double)arr[i] / mid); // add the ceiling of arr[i]/mid
            if (sum > k) {
                return false;                  // early exit if sum already exceeds k
            }
        }

        return sum <= k;  // sum ≤ k
    }

    int smallestDivisor(vector<int>& arr, int k) {
        int low    = 1;
        int high   = *max_element(arr.begin(), arr.end());
        int result = 0;

        while (low <= high) {
            int mid = (low + high) / 2;  // mid candidate divisor

            if (valid(arr, mid, k)) {
                result = mid;            // mid works, record and try smaller
                high   = mid - 1;        // search left half
            } else {
                low = mid + 1;           // mid too small, search right half
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example: arr = [1, 2, 5, 9], k = 6
 * low = 1, high = 9, result = 0
 * 1) mid = (1+9)/2 = 5
 *    valid? sum = ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5) = 1+1+1+2 = 5 ≤ 6 → true
 *    result = 5, high = 4
 * 2) mid = (1+4)/2 = 2
 *    valid? sum = ceil(1/2)+ceil(2/2)+ceil(5/2)+ceil(9/2) = 1+1+3+5 = 10 > 6 → false
 *    low = 3
 * 3) mid = (3+4)/2 = 3
 *    valid? sum = ceil(1/3)+ceil(2/3)+ceil(5/3)+ceil(9/3) = 1+1+2+3 = 7 > 6 → false
 *    low = 4
 * 4) mid = (4+4)/2 = 4
 *    valid? sum = ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4) = 1+1+2+3 = 7 > 6 → false
 *    low = 5
 * Loop ends (low=5 > high=4), return result = 5
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use binary search on the divisor in the range [1, max(arr)], and for each candidate divisor, check if the sum of ceil(arr[i]/divisor) is ≤ k; adjust search bounds based on validity.
// Time Complexity: O(n log m) where n = arr.length and m = max(arr) due to binary search over [1, m] and O(n) check each time.
// Space Complexity: O(1) auxiliary space besides input.
class Solution {
    public boolean valid(int[] arr, int mid, int k) {
        int sum = 0;

        for (int i = 0; i < arr.length; i++) {
            sum += Math.ceil((double)arr[i] / mid); // add the ceiling of arr[i]/mid
            if (sum > k) {
                return false;                       // early exit if sum already exceeds k
            }
        }

        return sum <= k;  // sum ≤ k
    }
    
    public int smallestDivisor(int[] arr, int k) {
        int low    = 1;
        int high   = Arrays.stream(arr).max().getAsInt();
        int result = 0;

        while (low <= high) {
            int mid = (low + high) / 2;  // mid candidate divisor

            if (valid(arr, mid, k)) {
                result = mid;            // mid works, record and try smaller
                high   = mid - 1;        // search left half
            } else {
                low = mid + 1;           // mid too small, search right half
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example: arr = [1, 2, 5, 9], k = 6
 * low = 1, high = 9, result = 0
 * 1) mid = (1+9)/2 = 5
 *    valid? sum = ceil(1/5)+ceil(2/5)+ceil(5/5)+ceil(9/5) = 1+1+1+2 = 5 ≤ 6 → true
 *    result = 5, high = 4
 * 2) mid = (1+4)/2 = 2
 *    valid? sum = ceil(1/2)+ceil(2/2)+ceil(5/2)+ceil(9/2) = 1+1+3+5 = 10 > 6 → false
 *    low = 3
 * 3) mid = (3+4)/2 = 3
 *    valid? sum = ceil(1/3)+ceil(2/3)+ceil(5/3)+ceil(9/3) = 1+1+2+3 = 7 > 6 → false
 *    low = 4
 * 4) mid = (4+4)/2 = 4
 *    valid? sum = ceil(1/4)+ceil(2/4)+ceil(5/4)+ceil(9/4) = 1+1+2+3 = 7 > 6 → false
 *    low = 5
 * Loop ends (low=5 > high=4), return result = 5
 *
 */
