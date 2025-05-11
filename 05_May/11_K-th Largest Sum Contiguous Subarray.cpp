/*
 * GfG Link: https://www.geeksforgeeks.org/problems/k-th-largest-sum-contiguous-subarray/1
 *
 * K-th Largest Sum Contiguous Subarray
 *
 * Difficulty: Medium Accuracy: 54.33% Submissions: 31K+ Points: 4 Average Time: 20m
 *
 * Given an array arr[] of size n, find the sum of the K-th largest sum among all contiguous subarrays. In other words, identify the K-th largest sum from all possible subarrays and return it.
 *
 * Examples:
 *
 * Input: arr[] = [3, 2, 1], k = 2
 * Output: 5
 * Explanation: The different subarray sums we can get from the array are = [6, 5, 3, 2, 1]. Where 5 is the 2nd largest.
 *
 * Input: arr[] = [2, 6, 4, 1], k = 3
 * Output: 11
 * Explanation: The different subarray sums we can get from the arrayare = [13, 12, 11, 10, 8, 6, 5, 4, 2, 1]. Where 11 is the 3rd largest.
 *
 * Constraints:
 * 1 <= arr.size() <= 1000
 * 1 <= k <= (n*(n+1))/2
 * -10^5 <= arr[i] <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use prefix sums to calculate all contiguous subarray sums and maintain a min-heap of size k to find the k-th largest sum.
// Time Complexity: O(n^2 * log k) — O(n^2) subarrays, and each heap operation takes O(log k)
// Space Complexity: O(n + k) — O(n) for prefix sum array and O(k) for the heap
class Solution {
public:
    int kthLargest(vector<int>& arr, int k) {
        int n = arr.size();

        // Prefix sum array to store cumulative sums
        vector<int> sum(n + 1);

        sum[0] = 0;
        sum[1] = arr[0];
        for (int i = 2; i <= n; i++) {
            sum[i] = sum[i - 1] + arr[i - 1];
        }

        // Min heap to keep track of top k largest sums
        priority_queue<int, vector<int>, greater<int> > pq;

        // Outer loop for start of subarray
        for (int i = 1; i <= n; i++) {
            // Inner loop for end of subarray
            for (int j = i; j <= n; j++) {
                // Calculate subarray sum from index i to j
                int x = sum[j] - sum[i - 1];

                // If heap size is less than k, just add the sum
                if (pq.size() < k) {
                    pq.push(x);
                }else{
                    // If current sum is greater than the smallest in heap, replace it
                    if (pq.top() < x) {
                        pq.pop();
                        pq.push(x);
                    }
                }
            }
        }

        // Top of the heap is the k-th largest sum
        return pq.top();
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 6, 4, 1], k = 3
 * Step 1: Calculate prefix sum array
 * sum = [0, 2, 8, 12, 13]
 *
 * Step 2: Evaluate all subarray sums using sum[j] - sum[i-1]
 * Subarrays and their sums:
 * [2] => 2           → heap: [2]
 * [2,6] => 8         → heap: [2, 8]
 * [2,6,4] => 12      → heap: [2, 8, 12]
 * [2,6,4,1] => 13    → 13 > 2 → pop 2 → heap: [8, 12, 13]
 * [6] => 6           → 6 < 8 → skip
 * [6,4] => 10        → 10 > 8 → pop 8 → heap: [10, 13, 12]
 * [6,4,1] => 11      → 11 > 10 → pop 10 → heap: [11, 13, 12]
 * [4] => 4           → 4 < 11 → skip
 * [4,1] => 5         → 5 < 11 → skip
 * [1] => 1           → 1 < 11 → skip
 *
 * Final Heap: [11, 13, 12]
 * Return: 11 (3rd largest sum)
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use prefix sums to calculate all contiguous subarray sums and maintain a min-heap of size k to find the k-th largest sum.
// Time Complexity: O(n^2 * log k) — O(n^2) subarrays, and each heap operation takes O(log k)
// Space Complexity: O(n + k) — O(n) for prefix sum array and O(k) for the heap
class Solution {
    public static int kthLargest(int[] arr, int k) {
        int n = arr.length;

        // Prefix sum array to store cumulative sums
        int[] sum = new int[n + 1];

        sum[0] = 0;
        sum[1] = arr[0];
        for (int i = 2; i <= n; i++) {
            sum[i] = sum[i - 1] + arr[i - 1];
        }

        // Min-heap to store the top k largest sums
        PriorityQueue<Integer> pq = new PriorityQueue<>();

        // Outer loop: start index of subarray
        for (int i = 1; i <= n; i++) {
            // Inner loop: end index of subarray
            for (int j = i; j <= n; j++) {
                // Calculate subarray sum from index i to j
                int x = sum[j] - sum[i - 1];

                // Add to heap if size < k
                if (pq.size() < k) {
                    pq.offer(x);
                } else {
                    // If current sum is larger than smallest in heap, replace it
                    if (pq.peek() < x) {
                        pq.poll();
                        pq.offer(x);
                    }
                }
            }
        }

        // The k-th largest sum will be at the top of the heap
        return pq.peek();
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 6, 4, 1], k = 3
 *
 * Step 1: Calculate prefix sum array
 * sum = [0, 2, 8, 12, 13]
 *
 * Step 2: Evaluate all subarray sums using sum[j] - sum[i-1]
 * Subarrays and their sums:
 * [2] => 2           → heap: [2]
 * [2,6] => 8         → heap: [2, 8]
 * [2,6,4] => 12      → heap: [2, 8, 12]
 * [2,6,4,1] => 13    → 13 > 2 → pop 2 → heap: [8, 12, 13]
 * [6] => 6           → 6 < 8 → skip
 * [6,4] => 10        → 10 > 8 → pop 8 → heap: [10, 13, 12]
 * [6,4,1] => 11      → 11 > 10 → pop 10 → heap: [11, 13, 12]
 * [4] => 4           → 4 < 11 → skip
 * [4,1] => 5         → 5 < 11 → skip
 * [1] => 1           → 1 < 11 → skip
 *
 * Final Heap: [11, 13, 12]
 * Return: 11 (3rd largest sum)
 *
 */
