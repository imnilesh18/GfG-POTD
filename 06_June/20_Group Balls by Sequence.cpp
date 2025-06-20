/*
 * GfG Link: https://www.geeksforgeeks.org/problems/group-balls-by-sequence/1
 *
 * Group Balls by Sequence
 *
 * Difficulty: Medium Accuracy: 38.4% Submissions: 2K+ Points: 4
 *
 * You are given an array arr[] of positive integers, where each element arr[i] represents the number written on the i-th ball, and a positive integer k.
 * Your task is to determine whether it is possible to rearrange all the balls into groups such that:
 * Each group contains exactly k balls.
 * The numbers in each group are consecutive integers
 *
 * Examples:
 *
 * Input: arr[] = [10, 1, 2, 11], k = 2
 * Output: true
 * Explanation: The hand can be rearranged as [1, 2], [10, 11]. There are two groups of size 2. Each group has 2 consecutive cards.
 *
 * Input: arr[] = [7, 8, 9, 10, 11], k = 2
 * Output: false
 * Explanation: The hand cannot be rearranged into groups of 2, since there are 5 cards, and 5 cards cannot be divided into groups of 2.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 106
 * 0 ≤ arr[i] ≤ 105
 * 1 ≤ k ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1: Sort the array and greedily form consecutive groups of size k by marking used elements.
// Time Complexity: O(n log n + n·k) due to sorting and scanning for each group, which is O(n log n) when k ≪ n.
// Space Complexity: O(1) extra space (in-place marking with -1), aside from the input array.
class Solution {
public:
    bool validgroup(vector<int>& arr, int k) {
        int n = arr.size();                   // total number of balls

        sort(arr.begin(), arr.end());         // bring consecutive numbers together

        for (int i = 0; i < n; i++) {
            if (arr[i] == -1) {                // already used in a previous group
                continue;
            }

            int curr  = arr[i];               // the next expected number in the group
            int count = 0;                    // how many balls have been added to the current group

            for (int j = i; j < n; j++) {
                if (arr[j] == curr) {         // found the next consecutive ball
                    curr++;                   // expect the next number in sequence
                    count++;                  // one more ball added to this group
                    arr[j] = -1;              // mark this ball as used
                }

                if (count == k) {              // the group is complete
                    break;
                }
            }

            if (count != k) {                  // could not form a full group of size k
                return false;
            }
        }
        return true;                          // all balls successfully grouped
    }
};

/*
 *
 * Dry Run on arr = [3, 1, 4, 2, 2, 3], k = 3
 *
 * Initial array: [3, 1, 4, 2, 2, 3]
 * After sort:     [1, 2, 2, 3, 3, 4]
 *
 * i = 0: arr[0] = 1 (!= -1)
 *   curr = 1, count = 0
 *   j = 0: arr[0] == 1 → mark -1, curr = 2, count = 1
 *   j = 1: arr[1] == 2 → mark -1, curr = 3, count = 2
 *   j = 2: arr[2] == 2 (≠ 3) skip
 *   j = 3: arr[3] == 3 → mark -1, curr = 4, count = 3 → group formed [1,2,3]
 *
 * i = 1: arr[1] == -1 skip
 * i = 2: arr[2] = 2 (!= -1)
 *   curr = 2, count = 0
 *   j = 2: arr[2] == 2 → mark -1, curr = 3, count = 1
 *   j = 3: arr[3] == -1 skip
 *   j = 4: arr[4] == 3 → mark -1, curr = 4, count = 2
 *   j = 5: arr[5] == 4 → mark -1, curr = 5, count = 3 → group formed [2,3,4]
 *
 * i = 3,4,5: all == -1 skip
 *
 * All balls grouped successfully → return true
 */

// Approach 2: Use a frequency map to count occurrences, then for each smallest available number greedily form consecutive sequences by decrementing counts.
// Time Complexity: O(n log n + m·k) where n = arr.size(), m = number of unique keys (m ≤ n), overall O(n log n + n) ≈ O(n log n).
// Space Complexity: O(n) extra space for the map.
class Solution {
public:
    bool validgroup(vector<int>& arr, int k) {
        int           n = arr.size();
        map<int, int> mp;                     // frequency map

        // count each value
        for (int val : arr) {
            mp[val]++;
        }

        // iterate in ascending order of values
        for (auto p : mp) {
            int val  = p.first;              // current value
            int freq = p.second;             // how many sequences start here

            if (freq == 0) {                 // already used up
                continue;
            }

            // try to build freq sequences of length k starting at val
            for (int i = 1; i < k; i++) {
                int nextVal = val + i;

                // if not enough nextVal to pair with all freq sequences, fail
                if (mp[nextVal] < freq) {
                    return false;
                }

                // consume freq of nextVal
                mp[nextVal] -= freq;
            }
        }
        return true;                         // all sequences formed successfully
    }
};

/*
 *
 * Dry Run on arr = [3, 1, 4, 2, 2, 3], k = 3
 *
 * Build map: {1:1, 2:2, 3:2, 4:1}
 *
 * Entry (1,1): freq=1
 *  i=1 → nextVal=2, mp[2]=2 ≥ 1 → mp[2]=2−1=1
 *  i=2 → nextVal=3, mp[3]=2 ≥ 1 → mp[3]=2−1=1
 *  Map now {1:1, 2:1, 3:1, 4:1}
 *
 * Entry (2,1): freq=1
 *  i=1 → nextVal=3, mp[3]=1 ≥ 1 → mp[3]=1−1=0
 *  i=2 → nextVal=4, mp[4]=1 ≥ 1 → mp[4]=1−1=0
 *  Map now {1:1, 2:1, 3:0, 4:0}
 *
 * Entry (3,0): freq=0 → skip
 * Entry (4,0): freq=0 → skip
 *
 * All entries processed successfully → return true
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Sort the array and greedily form consecutive groups of size k by marking used elements.
// Time Complexity: O(n log n + n·k) due to sorting and scanning for each group, which is O(n log n) when k ≪ n.
// Space Complexity: O(1) extra space (in-place marking with -1), aside from the input array.
class Solution {
    public boolean validgroup(int[] arr, int k) {
        int n = arr.length;                  // total number of balls

        Arrays.sort(arr);                    // bring consecutive numbers together

        for (int i = 0; i < n; i++) {
            if (arr[i] == -1) {              // already used in a previous group
                continue;
            }

            int curr  = arr[i];              // the next expected number in the group
            int count = 0;                   // how many balls have been added to the current group

            for (int j = i; j < n; j++) {
                if (arr[j] == curr) {        // found the next consecutive ball
                    curr++;                  // expect the next number in sequence
                    count++;                 // one more ball added to this group
                    arr[j] = -1;             // mark this ball as used
                }

                if (count == k) {            // the group is complete
                    break;
                }
            }

            if (count != k) {                // could not form a full group of size k
                return false;
            }
        }

        return true;                         // all balls successfully grouped
    }
}

/*
 *
 * Dry Run on arr = [3, 1, 4, 2, 2, 3], k = 3
 *
 * Initial array: [3, 1, 4, 2, 2, 3]
 * After sort:     [1, 2, 2, 3, 3, 4]
 *
 * i = 0: arr[0] = 1 (!= -1)
 *   curr = 1, count = 0
 *   j = 0: arr[0] == 1 → mark -1, curr = 2, count = 1
 *   j = 1: arr[1] == 2 → mark -1, curr = 3, count = 2
 *   j = 2: arr[2] == 2 (≠ 3) skip
 *   j = 3: arr[3] == 3 → mark -1, curr = 4, count = 3 → group formed [1,2,3]
 *
 * i = 1: arr[1] == -1 skip
 * i = 2: arr[2] = 2 (!= -1)
 *   curr = 2, count = 0
 *   j = 2: arr[2] == 2 → mark -1, curr = 3, count = 1
 *   j = 3: arr[3] == -1 skip
 *   j = 4: arr[4] == 3 → mark -1, curr = 4, count = 2
 *   j = 5: arr[5] == 4 → mark -1, curr = 5, count = 3 → group formed [2,3,4]
 *
 * i = 3,4,5: all == -1 skip
 *
 * All balls grouped successfully → return true
 */

// Approach 2: Use a sorted TreeMap to count occurrences, then for each smallest available number greedily form consecutive sequences by decrementing counts.
// Time Complexity: O(n log n + m·k) where n = arr.length, m = number of unique keys (m ≤ n), overall O(n log n + n) ≈ O(n log n).
// Space Complexity: O(n) extra space for the map.
class Solution {
    public boolean validgroup(int[] arr, int k) {
        int n = arr.length;
        TreeMap<Integer, Integer> mp = new TreeMap<>();  // frequency map

        // count each value
        for (int val : arr) {
            mp.put(val, mp.getOrDefault(val, 0) + 1);
        }

        // iterate in ascending order of keys
        for (Map.Entry<Integer, Integer> entry : mp.entrySet()) {
            int val  = entry.getKey();
            int freq = entry.getValue();

            if (freq == 0) {                // already used up
                continue;
            }

            // try to build freq sequences of length k starting at val
            for (int i = 1; i < k; i++) {
                int nextVal = val + i;

                int nextFreq = mp.getOrDefault(nextVal, 0);
                if (nextFreq < freq) {      // insufficient to continue all sequences
                    return false;
                }

                mp.put(nextVal, nextFreq - freq);
            }
        }

        return true;                       // all sequences formed successfully
    }
}

/*
 *
 * Dry Run on arr = [3, 1, 4, 2, 2, 3], k = 3
 *
 * Build map: {1=1, 2=2, 3=2, 4=1}
 *
 * Entry (1,1): freq=1
 *  i=1 → nextVal=2, mp[2]=2 ≥ 1 → mp[2]=2−1=1
 *  i=2 → nextVal=3, mp[3]=2 ≥ 1 → mp[3]=2−1=1
 *  Map now {1=1, 2=1, 3=1, 4=1}
 *
 * Entry (2,1): freq=1
 *  i=1 → nextVal=3, mp[3]=1 ≥ 1 → mp[3]=1−1=0
 *  i=2 → nextVal=4, mp[4]=1 ≥ 1 → mp[4]=1−1=0
 *  Map now {1=1, 2=1, 3=0, 4=0}
 *
 * Entry (3,0): freq=0 → skip
 * Entry (4,0): freq=0 → skip
 *
 * All entries processed successfully → return true
 */
