/*
 * GfG Link: https://www.geeksforgeeks.org/problems/powerfull-integer--170647/1
 *
 * Powerful Integer
 *
 * Difficulty: Medium Accuracy: 51.91% Submissions: 45K+ Points: 4
 *
 * You are given a 2D integer array intervals[][] of length n, where each intervals[i] = [start, end] represents a closed interval (i.e., all integers from start to end, inclusive). You are also given an integer k. An integer is called Powerful if it appears in at least k intervals. Find the maximum Powerful Integer.
 *
 * Note: If no integer occurs at least k times return -1.
 *
 * Examples:
 *
 * Input : n = 3, intervals[][] = [[1, 3], [4, 6], [3, 4]], k = 2
 * Output: 4
 * Explanation: Integers 3 and 4 appear in 2 intervals. The maximum is 4.
 *
 * Input : n = 4, intervals[][] = [[1, 4], [12, 45], [3, 8], [10, 12]], k = 3
 * Output: -1
 * Explanation: No integer appears in at least 3 intervals.
 *
 * Input : n = 5, intervals[][] = [[16, 21], [5, 8], [12, 17], [17, 29], [9, 24]], k = 3
 * Output: 21
 * Explanation: Integers 16, 17, 18, 19, 20 and 21 appear in at least 3 intervals. The maximum is 21.
 *
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 1 ≤ intervals[i][0] ≤ intervals[i][1] ≤ 109
 * 1 ≤ k ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Intuition:
// The problem asks for the maximum integer that is covered by at least 'k' intervals.
// This can be visualized as finding the rightmost point on a number line where the "coverage" or "overlap" count is 'k' or more.
// A line sweep algorithm is a natural fit. We only care about the points where the coverage count changes: the start and end points of the intervals.

// Approach:
// 1. We use a sorted map (std::map in C++) to track the changes in the number of active intervals. The map's keys will be the points on the number line, and the values will be the change in coverage (+1 for start, -1 for end).
// 2. For each interval [start, end], we signify that at 'start', the number of active intervals increases by one (map[start]++), and at 'end + 1', it decreases by one (map[end + 1]--).
// 3. We then iterate through the map, which processes the points in sorted order. We maintain a running sum ('temp') of the active intervals.
// 4. As we sweep from left to right, if we find a segment where the coverage ('temp') is >= k, the end of that segment is a candidate for our answer. The logic captures the end of the rightmost powerful segment.

// Time Complexity: O(N * log N)
// Populating the map takes N insertions, and each insertion into a std::map takes O(log N) time, leading to O(N * log N).
// The final traversal of the map takes O(M), where M is the number of unique endpoints (M <= 2N).
// Thus, the overall complexity is dominated by the map insertions.

// Space Complexity: O(N)
// In the worst-case scenario, all 2N endpoints (N starts and N ends) are unique, so the map will store up to 2N key-value pairs.

class Solution {
public:
    int powerfulInteger(vector<vector<int> >& intervals, int k) {
        map<int, int> mp; // Use a map to store points and the change in coverage at that point. Map keeps keys sorted.

        // Mark interval start and
        // end+1 with +1 and -1 respectively. This creates a difference array.
        for (auto& x : intervals) {
            mp[x[0]]     += 1; // An interval starts here, coverage increases.
            mp[x[1] + 1] -= 1; // An interval ends at x[1], so coverage decreases at the *next* integer.
        }

        int result = -1; // Stores the maximum powerful integer found so far.
        int temp   = 0;  // Tracks the current number of overlapping intervals (running prefix sum).

        // Traverse the map (sorted keys) and
        // track frequency using prefix sum.
        for (auto& x : mp) {
            // This block checks if the *change* at the current point is positive or negative.
            if (mp[x.first] >= 0) {       // Case for interval starts or net positive change.
                temp += mp[x.first];      // Update the running count of active intervals.
                if (temp >= k) {          // If the coverage becomes powerful...
                    result = x.first;     // ...the start of this powerful segment is a candidate for the answer.
                }
            } else {                      // Case for interval ends (net negative change).
                // Check the coverage level *before* applying the negative change.
                if (temp >= k) {          // If the segment ending at `x.first - 1` was powerful...
                    result = x.first - 1; // ...its end (`x.first - 1`) is the largest powerful integer in that segment.
                }
                temp += mp[x.first];      // Apply the negative change to the running count.
            }
        }

        return result; // Return the largest powerful integer found.
    }
};

/*
 * Dry Run
 * Example: intervals = [[1, 3], [4, 6], [3, 4]], k = 2
 *
 * 1. Populate map:
 * - From [1, 3]: mp[1]++ becomes 1, mp[4]-- becomes -1. Map: {1: 1, 4: -1}
 * - From [4, 6]: mp[4]++ becomes 0, mp[7]-- becomes -1. Map: {1: 1, 4: 0, 7: -1}
 * - From [3, 4]: mp[3]++ becomes 1, mp[5]-- becomes -1. Map: {1: 1, 3: 1, 4: 0, 5: -1, 7: -1}
 *
 * 2. Initialize:
 * result = -1
 * temp = 0
 *
 * 3. Traverse map:
 * - x = {1, 1}: change is positive. temp becomes 0 + 1 = 1. temp < k. result remains -1.
 * (Intervals [1, 2] have coverage 1)
 *
 * - x = {3, 1}: change is positive. temp becomes 1 + 1 = 2. temp >= k, so result becomes 3.
 * (Interval [3, 3] has coverage 2)
 *
 * - x = {4, 0}: change is non-negative. temp becomes 2 + 0 = 2. temp >= k, so result becomes 4.
 * (Interval [4, 4] has coverage 2)
 *
 * - x = {5, -1}: change is negative. Check temp before change: temp (2) >= k. Yes.
 * Update result = 5 - 1 = 4.
 * Now update temp: temp becomes 2 + (-1) = 1.
 * (Intervals [5, 6] have coverage 1)
 *
 * - x = {7, -1}: change is negative. Check temp before change: temp (1) < k. No update.
 * Update temp: temp becomes 1 + (-1) = 0.
 *
 * 4. End of loop. Return result.
 * Final Answer: 4
 */

/************************************************************ JAVA ************************************************/

// Intuition:
// The problem asks for the maximum integer that is covered by at least 'k' intervals.
// This can be visualized as finding the rightmost point on a number line where the "coverage" or "overlap" count is 'k' or more.
// A line sweep algorithm is a natural fit. We only care about the points where the coverage count changes: the start and end points of the intervals.

// Approach:
// 1. We use a sorted map (TreeMap in Java) to track the changes in the number of active intervals. The map's keys will be the points on the number line, and the values will be the change in coverage (+1 for start, -1 for end).
// 2. For each interval [start, end], we signify that at 'start', the number of active intervals increases by one (map.put(start, ...)), and at 'end + 1', it decreases by one (map.put(end + 1, ...)).
// 3. We then iterate through the map, which processes the points in sorted order. We maintain a running sum ('count') of the active intervals.
// 4. As we sweep from left to right, we use the specific logic from the C++ version to check the state and update the result, ensuring we find the rightmost powerful integer.

// Time Complexity: O(N * log N)
// Populating the TreeMap takes N insertions, and each insertion takes O(log N) time, leading to O(N * log N).
// The final traversal of the map takes O(M), where M is the number of unique endpoints (M <= 2N).
// Thus, the overall complexity is dominated by the map insertions.

// Space Complexity: O(N)
// In the worst-case scenario, all 2N endpoints (N starts and N ends) are unique, so the map will store up to 2N key-value pairs.

class Solution {
    public int powerfulInteger(int[][] intervals, int k) {
        Map<Integer, Integer> map = new TreeMap<>(); // Use a TreeMap to store points and the change in coverage at that point. TreeMap keeps keys sorted.

        // Mark interval start and
        // end+1 with +1 and -1 respectively. This creates a difference array.
        for (int[] x : intervals) {
            map.put(x[0], map.getOrDefault(x[0], 0) + 1);         // An interval starts here, coverage increases.
            map.put(x[1] + 1, map.getOrDefault(x[1] + 1, 0) - 1); // An interval ends at x[1], so coverage decreases at the *next* integer.
        }

        int result = -1;  // Stores the maximum powerful integer found so far.
        int count  = 0;   // Tracks the current number of overlapping intervals (running prefix sum).

        // Traverse the map (sorted keys) and
        // track frequency using prefix sum.
        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            int point  = entry.getKey();
            int change = entry.getValue();

            // This block checks if the *change* at the current point is positive or negative.
            if (change >= 0) {          // Case for interval starts or net positive change.
                count += change;        // Update the running count of active intervals.
                if (count >= k) {       // If the coverage becomes powerful...
                    result = point;     // ...the start of this powerful segment is a candidate for the answer.
                }
            } else {                    // Case for interval ends (net negative change).
                // Check the coverage level *before* applying the negative change.
                if (count >= k) {       // If the segment ending at `point - 1` was powerful...
                    result = point - 1; // ...its end (`point - 1`) is the largest powerful integer in that segment.
                }
                count += change;        // Apply the negative change to the running count.
            }
        }

        return result; // Return the largest powerful integer found.
    }
}

/*
 * Dry Run
 * Example: intervals = [[1, 3], [4, 6], [3, 4]], k = 2
 *
 * 1. Populate map:
 * - From [1, 3]: map.put(1, 1), map.put(4, -1). Map: {1: 1, 4: -1}
 * - From [4, 6]: map.put(4, 0), map.put(7, -1). Map: {1: 1, 4: 0, 7: -1}
 * - From [3, 4]: map.put(3, 1), map.put(5, -1). Map: {1: 1, 3: 1, 4: 0, 5: -1, 7: -1}
 *
 * 2. Initialize:
 * result = -1
 * count = 0
 *
 * 3. Traverse map:
 * - entry = {1, 1}: change is positive. count becomes 0 + 1 = 1. count < k. result remains -1.
 * (Intervals [1, 2] have coverage 1)
 *
 * - entry = {3, 1}: change is positive. count becomes 1 + 1 = 2. count >= k, so result becomes 3.
 * (Interval [3, 3] has coverage 2)
 *
 * - entry = {4, 0}: change is non-negative. count becomes 2 + 0 = 2. count >= k, so result becomes 4.
 * (Interval [4, 4] has coverage 2)
 *
 * - entry = {5, -1}: change is negative. Check count before change: count (2) >= k. Yes.
 * Update result = 5 - 1 = 4.
 * Now update count: count becomes 2 + (-1) = 1.
 * (Intervals [5, 6] have coverage 1)
 *
 * - entry = {7, -1}: change is negative. Check count before change: count (1) < k. No update.
 * Update count: count becomes 1 + (-1) = 0.
 *
 * 4. End of loop. Return result.
 * Final Answer: 4
 */
