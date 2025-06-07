/*
 * GfG Link: https://www.geeksforgeeks.org/problems/longest-span-with-same-sum-in-two-binary-arrays5142/1
 *
 * Longest Span in two Binary Arrays
 *
 * Difficulty: Medium Accuracy: 48.22% Submissions: 14K+ Points: 4
 *
 * Given two binary arrays, a1[] and a2[]. Find the length of longest common span (i, j) where j>= i such that a1[i] + a1[i+1] + .... + a1[j] =  a2[i] + a2[i+1] + ... + a2[j].
 *
 * Examples:
 *
 * Input: a1[] = [0, 1, 0, 0, 0, 0], a2[] = [1, 0, 1, 0, 0, 1]
 * Output: 4
 * Explanation: The longest span with same sum is from index 1 to 4 following zero based indexing.
 *
 * Input: a1[] = [0, 1, 0, 1, 1, 1, 1], a2[] = [1, 1, 1, 1, 1, 0, 1]
 * Output: 6
 * Explanation: The longest span with same sum is from index 1 to 6 following zero based indexing.
 *
 * Constraints:
 * 1 <= a1.size() = a2.size() <= 10^6
 * 0 <= a1[i], a2[i] <= 1
 */

/************************************************************ C++ ************************************************/

// Approach 1: Use brute force nested loops to check every possible subarray and update the maximum length when the sums of a1 and a2 are equal.
// Time Complexity: O(n^2) due to the two nested loops over the array of size n.
// Space Complexity: O(1) since only a constant amount of extra space (sum1, sum2, result) is used.
class Solution {
public:
    int longestCommonSum(vector<int>& a1, vector<int>& a2) {
        int n      = a1.size();
        int result = 0;                // stores the maximum length found so far

        // Check all possible subarrays by choosing start index i
        for (int i = 0; i < n; i++) {
            int sum1 = 0;              // cumulative sum of a1 from i to j
            int sum2 = 0;              // cumulative sum of a2 from i to j

            // Extend the subarray to end index j
            for (int j = i; j < n; j++) {
                // Accumulate sums for current subarray [i..j]
                sum1 += a1[j];
                sum2 += a2[j];

                // If the two sums match, update result with current span length
                if (sum1 == sum2) {
                    result = max(result, j - i + 1);
                }
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 * a1 = [0, 1, 0, 0, 0, 0]
 * a2 = [1, 0, 1, 0, 0, 1]
 *
 * i=0:
 *   sum1=0, sum2=0
 *   j=0: sum1=0, sum2=1 → not equal
 *   j=1: sum1=1, sum2=1 → equal, length=2, result=2
 *   j=2: sum1=1, sum2=2 → not equal
 *   ...
 *
 * i=1:
 *   sum1=0, sum2=0
 *   j=1: sum1=1, sum2=0 → not equal
 *   j=2: sum1=1, sum2=1 → equal, length=2, result=2
 *   j=3: sum1=1, sum2=1 → equal, length=3, result=3
 *   j=4: sum1=1, sum2=1 → equal, length=4, result=4
 *   j=5: sum1=1, sum2=2 → not equal
 *
 * i=2...5: (no longer span >4 found)
 *
 * Final result = 4  (span from index 1 to 4)
 */

// Approach 2: Use running difference and a hash map to track the first occurrence of each difference; when the same diff repeats, update the span length.
// Time Complexity: O(n) — single pass over the arrays with O(1) average map operations.
// Space Complexity: O(n) — for storing differences in the hash map.
class Solution {
public:
    int longestCommonSum(vector<int>& a1, vector<int>& a2) {
        int n = a1.size();
        unordered_map<int, int> mp;    // maps diff -> first index it was seen
        int sum1 = 0, sum2 = 0, result = 0;

        for (int i = 0; i < n; i++) {
            sum1 += a1[i];
            sum2 += a2[i];
            int diff = sum1 - sum2;

            if (diff == 0) {
                // from 0..i is balanced
                result = max(result, i + 1);
            }else if (mp.count(diff)) {
                // seen this diff before, subarray (mp[diff]+1..i) is balanced
                result = max(result, i - mp[diff]);
            }else {
                // first time seeing this diff
                mp[diff] = i;
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 * a1 = [0, 1, 0, 0, 0, 0]
 * a2 = [1, 0, 1, 0, 0, 1]
 *
 * i=0:
 *   sum1=0, sum2=1, diff=-1  → mp[-1]=0, result=0
 * i=1:
 *   sum1=1, sum2=1, diff=0   → diff==0  → result=2
 * i=2:
 *   sum1=1, sum2=2, diff=-1  → seen at 0 → span=2 → result=2
 * i=3:
 *   sum1=1, sum2=2, diff=-1  → seen at 0 → span=3 → result=3
 * i=4:
 *   sum1=1, sum2=2, diff=-1  → seen at 0 → span=4 → result=4
 * i=5:
 *   sum1=1, sum2=3, diff=-2  → mp[-2]=5, result=4
 *
 * Final result = 4
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Use brute force nested loops to check every possible subarray and update the maximum length when the sums of a1 and a2 are equal.
// Time Complexity: O(n^2) due to the two nested loops over the array of size n.
// Space Complexity: O(1) since only a constant amount of extra space (sum1, sum2, result) is used.
class Solution {
    public int longestCommonSum(int[] a1, int[] a2) {
        int n      = a1.length;
        int result = 0;                // stores the maximum length found so far

        // Check all possible subarrays by choosing start index i
        for (int i = 0; i < n; i++) {
            int sum1 = 0;              // cumulative sum of a1 from i to j
            int sum2 = 0;              // cumulative sum of a2 from i to j

            // Extend the subarray to end index j
            for (int j = i; j < n; j++) {
                // Accumulate sums for current subarray [i..j]
                sum1 += a1[j];
                sum2 += a2[j];

                // If the two sums match, update result with current span length
                if (sum1 == sum2) {
                    result = Math.max(result, j - i + 1);
                }
            }
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example:
 * a1 = [0, 1, 0, 0, 0, 0]
 * a2 = [1, 0, 1, 0, 0, 1]
 *
 * i=0:
 *   sum1=0, sum2=0
 *   j=0: sum1=0, sum2=1 → not equal
 *   j=1: sum1=1, sum2=1 → equal, length=2, result=2
 *   j=2: sum1=1, sum2=2 → not equal
 *   ...
 *
 * i=1:
 *   sum1=0, sum2=0
 *   j=1: sum1=1, sum2=0 → not equal
 *   j=2: sum1=1, sum2=1 → equal, length=2, result=2
 *   j=3: sum1=1, sum2=1 → equal, length=3, result=3
 *   j=4: sum1=1, sum2=1 → equal, length=4, result=4
 *   j=5: sum1=1, sum2=2 → not equal
 *
 * i=2...5: (no longer span >4 found)
 *
 * Final result = 4  (span from index 1 to 4)
 */

// Approach 2: Use running difference and a HashMap to track the first occurrence of each difference; when the same diff repeats, update the span length.
// Time Complexity: O(n) — single pass over the arrays with O(1) average map operations.
// Space Complexity: O(n) — for storing differences in the HashMap.
class Solution {
    public int longestCommonSum(int[] a1, int[] a2) {
        int n = a1.length;
        Map<Integer, Integer> map = new HashMap<>();  // diff -> first index
        int sum1 = 0, sum2 = 0, result = 0;

        for (int i = 0; i < n; i++) {
            sum1 += a1[i];
            sum2 += a2[i];
            int diff = sum1 - sum2;

            if (diff == 0) {
                // from 0..i is balanced
                result = i + 1;
            }else if (map.containsKey(diff)) {
                // seen this diff before, subarray (map.get(diff)+1..i) is balanced
                result = Math.max(result, i - map.get(diff));
            }else {
                // first time seeing this diff
                map.put(diff, i);
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example:
 * a1 = [0, 1, 0, 0, 0, 0]
 * a2 = [1, 0, 1, 0, 0, 1]
 *
 * i=0:
 *   sum1=0, sum2=1, diff=-1  → map.put(-1,0), result=0
 * i=1:
 *   sum1=1, sum2=1, diff=0   → diff==0  → result=2
 * i=2:
 *   sum1=1, sum2=2, diff=-1  → seen at 0 → span=2 → result=2
 * i=3:
 *   sum1=1, sum2=2, diff=-1  → seen at 0 → span=3 → result=3
 * i=4:
 *   sum1=1, sum2=2, diff=-1  → seen at 0 → span=4 → result=4
 * i=5:
 *   sum1=1, sum2=3, diff=-2  → map.put(-2,5), result=4
 *
 * Final result = 4
 */
