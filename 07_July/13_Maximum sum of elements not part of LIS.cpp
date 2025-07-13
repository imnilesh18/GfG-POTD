/*
 * GfG Link: https://www.geeksforgeeks.org/problems/maximum-sum-of-elements-not-part-of-lis/1
 *
 * Maximum sum of elements not part of LIS
 *
 * Difficulty: Medium Accuracy: 28.43% Submissions: 6K+ Points: 4
 *
 * Given an array arr[] of positive integers, your task is to find the maximum possible sum of all elements that are not part of the Longest Increasing Subsequence (LIS).
 *
 * Examples:
 * Input: arr[] = [4, 6, 1, 2, 3, 8]
 * Output: 10
 * Explanation: The elements which are not in LIS is 4 and 6.
 *
 * Input: arr[] = [5, 4, 3, 2, 1]
 * Output: 14
 * Explanation: The elements which are not in LIS is 5, 4, 3 and 2.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^3
 * 1 ≤ arr[i] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Bottom-up DP to find LIS length and track the minimum sum for that LIS, then subtract from total.
// Time Complexity: O(n²) due to the nested loops over i and j.
// Space Complexity: O(n) for the dp and dpMinSum arrays.
class Solution {
public:
    int nonLisMaxSum(vector<int>& arr) {
        int n     = arr.size();                            // number of elements
        int total = accumulate(arr.begin(), arr.end(), 0); // sum of all elements

        vector<int> dp(n, 1);                              // dp[i] = length of LIS ending at i (at least 1)
        vector<int> dpMinSum(n);                           // dpMinSum[i] = minimum sum of an LIS of length dp[i] ending at i

        for (int i = 0; i < n; i++) {
            dpMinSum[i] = arr[i];        // initialize with the element itself
        }

        int maxLIS    = 1;               // global maximum LIS length found so far
        int minLISsum = arr[0];          // minimum sum among all LIS of length maxLIS

        // build dp[] and dpMinSum[]
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    int currLen = dp[j] + 1;                   // potential new LIS length
                    int currSum = dpMinSum[j] + arr[i];        // corresponding sum

                    if (currLen > dp[i]) {
                        dp[i]       = currLen;                 // update LIS length at i
                        dpMinSum[i] = currSum;                 // update min sum for this new length
                    }else if (currLen == dp[i]) {
                        // if same length, keep the smaller sum
                        dpMinSum[i] = min(dpMinSum[i], currSum);
                    }
                }
            }
            // update global maxLIS and its min sum
            if (dp[i] > maxLIS) {
                maxLIS    = dp[i];
                minLISsum = dpMinSum[i];
            }else if (dp[i] == maxLIS) {
                minLISsum = min(minLISsum, dpMinSum[i]);
            }
        }

        return total - minLISsum;        // sum of elements not in any minimal‐sum LIS
    }
};

/*
 *
 * Dry Run
 *
 * Example: arr = [4, 6, 1, 2, 3, 8]
 * total = 24
 * dp init      = [1,1,1,1,1,1]
 * dpMinSum init= [4,6,1,2,3,8]
 * maxLIS = 1, minLISsum = 4
 *
 * i=0: nothing changes
 *
 * i=1 (arr[1]=6):
 *   j=0: 4<6 → currLen=2, currSum=4+6=10
 *     dp[1]=2, dpMinSum[1]=10
 *   maxLIS=2, minLISsum=10
 *
 * i=2 (1): no j<2 with arr[j]<1 → dp[2]=1
 *
 * i=3 (2):
 *   j=2: 1<2 → currLen=2, currSum=1+2=3
 *     dp[3]=2, dpMinSum[3]=3
 *   dp[3]==maxLIS → minLISsum = min(10,3)=3
 *
 * i=4 (3):
 *   j=2: 1<3 → currLen=2, currSum=1+3=4 → dp[4]=2, dpMinSum[4]=4
 *   j=3: 2<3 → currLen=3, currSum=3+3=6 → dp[4]=3, dpMinSum[4]=6
 *   dp[4]>maxLIS → maxLIS=3, minLISsum=6
 *
 * i=5 (8):
 *   j=0: 4<8 → currLen=2, sum=4+8=12 → dp[5]=2
 *   j=1: 6<8 → currLen=3, sum=10+8=18 → dp[5]=3, dpMinSum[5]=18
 *   j=2: 1<8 → currLen=2, sum=1+8=9  → no change
 *   j=3: 2<8 → currLen=3, sum=3+8=11 → dpMinSum[5]=min(18,11)=11
 *   j=4: 3<8 → currLen=4, sum=6+8=14 → dp[5]=4, dpMinSum[5]=14
 *   dp[5]>maxLIS → maxLIS=4, minLISsum=14
 *
 * result = total - minLISsum = 24 - 14 = 10
 */

/************************************************************ JAVA ************************************************/

// Approach: Bottom-up DP to find LIS length and track the minimum sum for that LIS, then subtract from total.
// Time Complexity: O(n²) due to the nested loops over i and j.
// Space Complexity: O(n) for the dp and dpMinSum arrays.
class Solution {
    public int nonLisMaxSum(int[] arr) {
        int n     = arr.length;                         // number of elements
        int total = 0;                                  // sum of all elements

        for (int v : arr) {
            total += v;
        }

        int[] dp       = new int[n];                    // dp[i] = length of LIS ending at i (min 1)
        int[] dpMinSum = new int[n];                    // dpMinSum[i] = min sum of an LIS of length dp[i] ending at i
        for (int i = 0; i < n; i++) {
            dp[i]       = 1;                            // each element alone is LIS length 1
            dpMinSum[i] = arr[i];                       // sum initialized to the element itself
        }

        int maxLIS    = 1;                              // global max LIS length
        int minLISsum = arr[0];                         // min sum among LIS of length maxLIS

        // build dp[] and dpMinSum[]
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) {
                    int currLen = dp[j] + 1;            // potential new LIS length
                    int currSum = dpMinSum[j] + arr[i]; // corresponding sum

                    if (currLen > dp[i]) {
                        dp[i]       = currLen;          // update LIS length at i
                        dpMinSum[i] = currSum;          // update min sum for this new length
                    } else if (currLen == dp[i]) {
                        // if same length, keep the smaller sum
                        dpMinSum[i] = Math.min(dpMinSum[i], currSum);
                    }
                }
            }
            // update global maxLIS and its min sum
            if (dp[i] > maxLIS) {
                maxLIS    = dp[i];
                minLISsum = dpMinSum[i];
            } else if (dp[i] == maxLIS) {
                minLISsum = Math.min(minLISsum, dpMinSum[i]);
            }
        }

        return total - minLISsum;                      // sum of elements not in any minimal‑sum LIS
    }
}

/*
 *
 * Dry Run
 *
 * Example: arr = [4, 6, 1, 2, 3, 8]
 * total = 24
 * dp init      = [1,1,1,1,1,1]
 * dpMinSum init= [4,6,1,2,3,8]
 * maxLIS = 1, minLISsum = 4
 *
 * i=0: no inner loop → dp=[1,1,1,1,1,1], maxLIS=1, minLISsum=4
 *
 * i=1 (6):
 *   j=0: 4<6 → currLen=2, currSum=10 → dp[1]=2, dpMinSum[1]=10
 *   maxLIS=2, minLISsum=10
 *
 * i=2 (1): no j<2 with arr[j]<1 → dp[2]=1
 *
 * i=3 (2):
 *   j=2: 1<2 → currLen=2, currSum=3 → dp[3]=2, dpMinSum[3]=3
 *   dp[3]==maxLIS → minLISsum=min(10,3)=3
 *
 * i=4 (3):
 *   j=2: 1<3 → currLen=2, currSum=4 → dp[4]=2, dpMinSum[4]=4
 *   j=3: 2<3 → currLen=3, currSum=6 → dp[4]=3, dpMinSum[4]=6
 *   dp[4]>maxLIS → maxLIS=3, minLISsum=6
 *
 * i=5 (8):
 *   j=0: 4<8 → currLen=2,sum=12 → dp[5]=2
 *   j=1: 6<8 → currLen=3,sum=18 → dp[5]=3, dpMinSum[5]=18
 *   j=2: 1<8 → currLen=2,sum=9  → no change
 *   j=3: 2<8 → currLen=3,sum=11 → dpMinSum[5]=11
 *   j=4: 3<8 → currLen=4,sum=14 → dp[5]=4, dpMinSum[5]=14
 *   dp[5]>maxLIS → maxLIS=4, minLISsum=14
 *
 * result = 24 - 14 = 10
 */
