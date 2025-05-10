/*
 * Longest Subarray with Majority Greater than K
 *
 * Difficulty: Medium Accuracy: 53.66% Submissions: 10K+ Points: 4
 *
 * Given an array arr[] and an integer k, the task is to find the length of longest subarray in which the count of elements greater than k is more than the count of elements less than or equal to k.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3, 4, 1], k = 2
 * Output: 3
 * Explanation: The subarray [2, 3, 4] or [3, 4, 1] satisfy the given condition, and there is no subarray of length 4 or 5 which will hold the given condition, so the answer is 3.
 *
 * Input: arr[] = [6, 5, 3, 4], k = 2
 * Output: 4
 * Explanation: In the subarray [6, 5, 3, 4], there are 4 elements > 2 and 0 elements <= 2, so it is the longest subarray.
 *
 * Constraints:
 * 1 <= arr.size() <= 10^6
 * 1 <= arr[i] <= 10^6
 * 0 <= k <= 10^6
 */

/************************************************************ C++ ************************************************/

// Approach: Convert elements > k to +1 and <= k to -1, and reduce the problem to finding the longest subarray with a positive prefix sum. We use a hash map to store first occurrences of prefix sums and process to get the maximum subarray length with more +1s than -1s.
// Time Complexity: O(n) – We traverse the array a constant number of times.
// Space Complexity: O(n) – For storing prefix indices in the hashmap.
class Solution {
public:
    int longestSubarray(vector<int>& arr, int k) {
        int n = arr.size();
        unordered_map<int, int> prefIdx; // Map to store first occurrence of prefix sums
        int sum = 0, res = 0;

        // Step 1: Calculate prefix sum by replacing values:
        // > k => +1, <= k => -1
        for (int i = 0; i < n; i++) {
            sum += (arr[i] > k ? 1 : -1); // Convert element to +1 or -1

            // Store the first index at which this prefix sum occurs
            if (prefIdx.find(sum) == prefIdx.end()) {
                prefIdx[sum] = i;
            }
        }

        // Handle edge case where all elements are <= k
        if (prefIdx.find(-n) != prefIdx.end()) {
            return 0;
        }

        // Ensure a starting point for subarrays of all possible sums
        prefIdx[-n] = n;

        // Step 2: Normalize prefix indices to maintain min index for each prefix sum
        for (int i = -n + 1; i <= n; i++) {
            if (prefIdx.find(i) == prefIdx.end()) {
                prefIdx[i] = prefIdx[i - 1];
            }else{
                prefIdx[i] = min(prefIdx[i], prefIdx[i - 1]);
            }
        }

        // Step 3: Recalculate sum and find max length where sum > 0
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (arr[i] > k ? 1 : -1);

            if (sum > 0) {
                res = i + 1;                          // Entire subarray from 0 to i has more +1s
            }else {
                res = max(res, i - prefIdx[sum - 1]); // Use stored prefix to find max length
            }
        }

        return res;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 3, 4, 1], k = 2
 * Convert array: [-1, -1, +1, +1, -1]
 * Step 1: Prefix sum values:
 * Index 0: -1  → store prefIdx[-1] = 0
 * Index 1: -2  → store prefIdx[-2] = 1
 * Index 2: -1  → already exists
 * Index 3:  0  → store prefIdx[0]  = 3
 * Index 4: -1  → already exists
 *
 * Step 2: Normalize prefIdx
 * For all values from -n to n, fill or minimize prefIdx[i] using prefIdx[i-1]
 *
 * Step 3: Traverse again to find longest subarray with sum > 0
 * Running sum:
 * i=0: -1 → res = 0
 * i=1: -2 → res = 0
 * i=2: -1 → check i - prefIdx[sum - 1] = 2 - prefIdx[-2] = 2 - 1 = 1 → res = 1
 * i=3: 0  → i - prefIdx[-1] = 3 - 0 = 3 → res = 3
 * i=4: -1 → i - prefIdx[-2] = 4 - 1 = 3 → res = 3
 *
 * Final Answer = 3
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Convert elements > k to +1 and <= k to -1, and reduce the problem to finding the longest subarray with a positive prefix sum. We use a HashMap to store first occurrences of prefix sums and process to get the maximum subarray length with more +1s than -1s.
// Time Complexity: O(n) – We traverse the array a constant number of times.
// Space Complexity: O(n) – For storing prefix indices in the HashMap.
class Solution {
    static int longestSubarray(int[] arr, int k) {
        int n = arr.length;
        Map<Integer, Integer> prefIdx = new HashMap<>();
        int sum = 0, res = 0;

        // Step 1: Build prefix sum map based on conversion: >k → +1, <=k → -1
        for (int i = 0; i < n; i++) {
            sum += (arr[i] > k ? 1 : -1);

            // Store first occurrence of each prefix sum
            if (!prefIdx.containsKey(sum)) {
                prefIdx.put(sum, i);
            }
        }

        // Handle edge case
        if (prefIdx.containsKey(-n)) {
            return 0;
        }
        prefIdx.put(-n, n);

        // Step 2: Normalize prefix indices to maintain minimum index for each prefix sum
        int[] minIdx = new int[2 * n + 1];
        Arrays.fill(minIdx, n);  // fill with max possible index
        for (Map.Entry<Integer, Integer> entry : prefIdx.entrySet()) {
            minIdx[entry.getKey() + n] = entry.getValue();
        }
        for (int i = 1; i < minIdx.length; i++) {
            minIdx[i] = Math.min(minIdx[i], minIdx[i - 1]);
        }

        // Step 3: Traverse to find max subarray length with sum > 0
        sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (arr[i] > k ? 1 : -1);
            if (sum > 0) {
                res = i + 1;
            } else {
                int idx = minIdx[sum - 1 + n];
                if (idx < n) {
                    res = Math.max(res, i - idx);
                }
            }
        }

        return res;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 3, 4, 1], k = 2
 * Converted: [-1, -1, +1, +1, -1]
 * Step 1: Prefix sums and their first indices:
 * sum=-1 at i=0 → map[-1]=0
 * sum=-2 at i=1 → map[-2]=1
 * sum=-1 again → already exists
 * sum=0 at i=3 → map[0]=3
 * sum=-1 again → already exists
 *
 * Step 2: Normalize prefix min indices for -n to +n using array
 * Step 3: Running sum and max length check:
 * i=0, sum=-1 → res = 0
 * i=1, sum=-2 → res = 0
 * i=2, sum=-1 → i - minIdx[-2 + n] = 2 - 1 = 1
 * i=3, sum=0  → i - minIdx[-1 + n] = 3 - 0 = 3 → res = 3
 * i=4, sum=-1 → i - minIdx[-2 + n] = 4 - 1 = 3 → res = 3
 *
 * Output: 3
 *
 */
