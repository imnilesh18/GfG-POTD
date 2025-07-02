/*
 * GfG Link: https://www.geeksforgeeks.org/problems/fruit-into-baskets-1663137462/1
 *
 * Longest subarray with Atmost two distinct integers
 *
 * Difficulty: Medium Accuracy: 47.98% Submissions: 109K+ Points: 4 Average Time: 30m
 *
 * Given an array arr[] consisting of positive integers, your task is to find the length of the longest subarray that contains at most two distinct integers.
 *
 * Examples:
 *
 * Input: arr[] = [2, 1, 2]
 * Output: 3
 * Explanation: The entire array [2, 1, 2] contains at most two distinct integers (2 and 1). Hence, the length of the longest subarray is 3.
 *
 * Input: arr[] = [3, 1, 2, 2, 2, 2]
 * Output: 5
 * Explanation: The longest subarray containing at most two distinct integers is [1, 2, 2, 2, 2], which has a length of 5.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use a sliding window with two pointers (i, j) and an unordered_map to track frequencies. Expand j until we have more than two distinct elements, then shrink i until we’re back to at most two.
// Time Complexity: O(n) — each element is added and removed at most once.
// Space Complexity: O(1) — the map holds at most 2 keys.
class Solution {
public:
    int totalElements(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> mp;

        int i      = 0;          // left boundary of window
        int j      = 0;          // right boundary of window
        int result = 0;          // best window size seen

        while (j < n) {
            // include arr[j] into the window
            mp[arr[j]]++;

            // if more than two distinct numbers, shrink from left
            while (mp.size() > 2) {
                mp[arr[i]]--;            // decrement freq of arr[i]
                if (mp[arr[i]] == 0) {   // if freq is zero, remove key
                    mp.erase(arr[i]);
                }
                i++;                     // move left boundary right
            }

            // window [i..j] is valid, update result
            result = max(result, j - i + 1);
            j++;                        // expand window to the right
        }

        return result;
    }
};

/*
 *
 * Dry Run
 * arr = [1, 2, 1, 2, 3, 2, 2]
 * i = 0, j = 0, mp = {}, result = 0
 *
 * j=0: add 1
 *   mp = {1:1}, size=1 ≤2 → result = max(0,1)=1
 *
 * j=1: add 2
 *   mp = {1:1,2:1}, size=2 ≤2 → result = max(1,2)=2
 *
 * j=2: add 1
 *   mp = {1:2,2:1}, size=2 → result = max(2,3)=3
 *
 * j=3: add 2
 *   mp = {1:2,2:2}, size=2 → result = max(3,4)=4
 *
 * j=4: add 3
 *   mp = {1:2,2:2,3:1}, size=3 >2 → shrink:
 *     i=0: remove arr[0]=1 → mp={1:1,2:2,3:1}, size=3
 *     i=1: remove arr[1]=2 → mp={1:1,2:1,3:1}, size=3
 *     i=2: remove arr[2]=1 → mp={2:1,3:1}, size=2, stop
 *   new window i=3..4 length=4-3+1=2 → result stays 4
 *
 * j=5: add 2
 *   mp = {2:2,3:1}, size=2 → window 3..5 length=3 → result=4
 *
 * j=6: add 2
 *   mp = {2:3,3:1}, size=2 → window 3..6 length=4 → result=4
 *
 * End loop → final result = 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a sliding window with two pointers (i, j) and a HashMap to track frequencies. Expand j until we have more than two distinct elements, then shrink i until we’re back to at most two.
// Time Complexity: O(n) — each element is added and removed at most once.
// Space Complexity: O(1) — the map holds at most 2 keys.
class Solution {
    public int totalElements(int[] arr) {
        int n = arr.length;
        Map<Integer, Integer> map = new HashMap<>();

        int i      = 0;       // left boundary of window
        int j      = 0;       // right boundary of window
        int result = 0;       // best window size seen

        while (j < n) {
            // include arr[j] into the window
            map.put(arr[j], map.getOrDefault(arr[j], 0) + 1);

            // if more than two distinct numbers, shrink from left
            while (map.size() > 2) {
                int count = map.get(arr[i]) - 1;
                if (count == 0) {
                    map.remove(arr[i]);     // remove key if freq is zero
                } else {
                    map.put(arr[i], count); // else update freq
                }
                i++;                        // move left boundary right
            }

            // window [i..j] is valid, update result
            result = Math.max(result, j - i + 1);
            j++;                           // expand window to the right
        }

        return result;
    }
}

/*
 *
 * Dry Run
 * arr = [1, 2, 1, 2, 3, 2, 2]
 * i = 0, j = 0, map = {}, result = 0
 *
 * j=0: add 1
 *   map = {1=1}, size=1 ≤2 → result = max(0,1)=1
 *
 * j=1: add 2
 *   map = {1=1,2=1}, size=2 ≤2 → result = max(1,2)=2
 *
 * j=2: add 1
 *   map = {1=2,2=1}, size=2 → result = max(2,3)=3
 *
 * j=3: add 2
 *   map = {1=2,2=2}, size=2 → result = max(3,4)=4
 *
 * j=4: add 3
 *   map = {1=2,2=2,3=1}, size=3 >2 → shrink:
 *     i=0: remove arr[0]=1 → map={1=1,2=2,3=1}, size=3
 *     i=1: remove arr[1]=2 → map={1=1,2=1,3=1}, size=3
 *     i=2: remove arr[2]=1 → map={2=1,3=1}, size=2, stop
 *   new window i=3..4 length=4-3+1=2 → result stays 4
 *
 * j=5: add 2
 *   map = {2=2,3=1}, size=2 → window 3..5 length=3 → result=4
 *
 * j=6: add 2
 *   map = {2=3,3=1}, size=2 → window 3..6 length=4 → result=4
 *
 * End loop → final result = 4
 *
 */
