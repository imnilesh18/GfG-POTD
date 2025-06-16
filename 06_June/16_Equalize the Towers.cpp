/*
 *
 * GfG Link: https://www.geeksforgeeks.org/problems/equalize-the-towers2804/1
 *
 * Equalize the Towers
 *
 * Difficulty: Medium Accuracy: 48.36% Submissions: 5K+ Points: 4
 *
 * You are given an array heights[] representing the heights of towers and another array cost[] where each element represents the cost of modifying the height of respective tower.
 *
 * The goal is to make all towers of same height by either adding or removing blocks from each tower.
 * Modifying the height of tower (add or remove) 'i' by 1 unit costs cost[i].
 * Return the minimum cost to equalize the heights of all towers.
 *
 * Examples:
 *
 * Input: heights[] = [1, 2, 3], cost[] = [10, 100, 1000]
 * Output: 120
 * Explanation: The heights can be equalized by either "Removing one block from 3 and adding one in 1" or "Adding two blocks in 1 and adding one in 2". Since the cost of operation in tower 3 is 1000, the first process would yield 1010 while the second one yields 120.
 *
 * Input: heights[] = [7, 1, 5], cost[] = [1, 1, 1]
 * Output: 6
 * Explanation: The minimum cost to equalize the towers is 6, achieved by setting all towers to height 5.
 *
 * Constraints:
 * 1 ≤ heights.size() = cost.size() ≤ 10^5
 * 1 ≤ heights[i] ≤ 10^4
 * 1 ≤ cost[i] ≤ 10^3
 */
/************************************************************ C++ ************************************************/

// Approach 1: Brute-force by trying each tower's height as the target and computing total cost for each.
// Time Complexity: O(n^2) — two nested loops over n towers.
// Space Complexity: O(1) — only constant extra variables used.
class Solution {
public:
    int minCost(vector<int>& heights, vector<int>& cost) {
        int n = heights.size();

        long long result = LLONG_MAX;  // will hold the minimum cost found

        // Try each tower's height as the target height
        for (int i = 0; i < n; i++) {
            long long total = 0;  // cost to make all towers height = heights[i]

            // Calculate cost to equalize every tower to heights[i]
            for (int j = 0; j < n; j++) {
                total += abs(heights[j] - heights[i]) * cost[j];
            }

            result = min(result, total);  // update minimum cost if this is lower
        }

        return (int)result;  // cast back to int for GfG signature
    }
};

/*
 *
 * Dry Run on heights = [1,2,3], cost = [10,100,1000]
 *
 * i = 0, target = heights[0] = 1
 *   total = |1-1|*10 + |2-1|*100 + |3-1|*1000
 *         = 0 + 100 + 2000 = 2100
 *   result = min(LLONG_MAX,2100) = 2100
 *
 * i = 1, target = heights[1] = 2
 *   total = |1-2|*10 + |2-2|*100 + |3-2|*1000
 *         = 10 + 0 + 1000 = 1010
 *   result = min(2100,1010) = 1010
 *
 * i = 2, target = heights[2] = 3
 *   total = |1-3|*10 + |2-3|*100 + |3-3|*1000
 *         = 20 + 100 + 0 = 120
 *   result = min(1010,120) = 120
 *
 * Final result returned = 120
 */

// Approach 2: Binary Search on the target height based on convex cost function.
// Time Complexity: O(n * log(maxHeight - minHeight)) — Binary search over height range with O(n) cost calculation each time.
// Space Complexity: O(1) — Only constant extra space used.
class Solution {
public:
    // Helper function to compare cost at mid vs mid + 1
    bool check(vector<int>& heights, vector<int>& cost, int mid) {
        long long costMid   = 0;
        long long costMidP1 = 0;

        for (int i = 0; i < heights.size(); i++) {
            costMid   += (long long)abs(heights[i] - mid) * cost[i];
            costMidP1 += (long long)abs(heights[i] - (mid + 1)) * cost[i];
        }

        return costMid < costMidP1;  // true if mid gives smaller cost than mid+1 (move left)
    }
    
    int minCost(vector<int>& heights, vector<int>& cost) {
        // Define search boundaries for binary search
        int low  = *min_element(heights.begin(), heights.end());
        int high = *max_element(heights.begin(), heights.end());

        int targetH = 0;  // best height found

        while (low <= high) {
            int mid = (low + high) / 2;

            // Move toward the side with lower cost
            if (check(heights, cost, mid)) {
                targetH = mid;
                high    = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // Calculate final cost using chosen target height
        long long result = 0;
        for (int i = 0; i < heights.size(); i++) {
            result += (long long)abs(heights[i] - targetH) * cost[i];
        }

        return (int)result;
    }
};

/*
 *
 * Dry Run
 * heights = [1,2,3], cost = [10,100,1000]
 *
 * low = 1, high = 3
 * mid = 2
 *   costMid = |1-2|*10 + |2-2|*100 + |3-2|*1000 = 10 + 0 + 1000 = 1010
 *   costMidP1 = |1-3|*10 + |2-3|*100 + |3-3|*1000 = 20 + 100 + 0 = 120
 *   costMid < costMidP1 → true → targetH = 2, high = 1
 *
 * loop ends
 * Final targetH = 2
 * Final cost = 10 + 0 + 1000 = 1010
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force by trying each tower's height as the target and computing total cost for each.
// Time Complexity: O(n^2) — two nested loops over n towers.
// Space Complexity: O(1) — only constant extra variables used.
class Solution {
    public int minCost(int[] heights, int[] cost) {
        int n = heights.length;

        long result = Long.MAX_VALUE;  // will hold the minimum cost found

        // Try each tower's height as the target height
        for (int i = 0; i < n; i++) {
            long total = 0;  // cost to make all towers height = heights[i]

            // Calculate cost to equalize every tower to heights[i]
            for (int j = 0; j < n; j++) {
                total += Math.abs(heights[j] - heights[i]) * (long)cost[j];
            }

            result = Math.min(result, total);  // update minimum cost if this is lower
        }

        return (int)result;   // cast back to int as expected
    }
}

/*
 *
 * Dry Run on heights = [1,2,3], cost = [10,100,1000]
 *
 * i = 0, target = heights[0] = 1
 *   total = |1-1|*10 + |2-1|*100 + |3-1|*1000
 *         = 0 + 100 + 2000 = 2100
 *   result = min(Long.MAX_VALUE,2100) = 2100
 *
 * i = 1, target = heights[1] = 2
 *   total = |1-2|*10 + |2-2|*100 + |3-2|*1000
 *         = 10 + 0 + 1000 = 1010
 *   result = min(2100,1010) = 1010
 *
 * i = 2, target = heights[2] = 3
 *   total = |1-3|*10 + |2-3|*100 + |3-3|*1000
 *         = 20 + 100 + 0 = 120
 *   result = min(1010,120) = 120
 *
 * Final result returned = 120
 */

// Approach 2: Binary Search on the target height based on convex cost function.
// Time Complexity: O(n * log(maxHeight - minHeight)) — Binary search over height range with O(n) cost calculation each time.
// Space Complexity: O(1) — Only constant extra space used.
class Solution {
    // Helper function to compare cost at mid vs mid + 1
    public boolean check(int[] heights, int[] cost, int mid) {
        long costMid   = 0;
        long costMidP1 = 0;

        for (int i = 0; i < heights.length; i++) {
            costMid   += (long)Math.abs(heights[i] - mid) * cost[i];
            costMidP1 += (long)Math.abs(heights[i] - (mid + 1)) * cost[i];
        }

        return costMid < costMidP1;  // true if mid gives smaller cost than mid+1 (move left)
    }

    public int minCost(int[] heights, int[] cost) {
        // Define search boundaries for binary search
        int low  = Arrays.stream(heights).min().getAsInt();
        int high = Arrays.stream(heights).max().getAsInt();

        int targetH = 0;  // best height found

        while (low <= high) {
            int mid = (low + high) / 2;

            // Move toward the side with lower cost
            if (check(heights, cost, mid)) {
                targetH = mid;
                high    = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // Calculate final cost using chosen target height
        long result = 0;
        for (int i = 0; i < heights.length; i++) {
            result += (long)Math.abs(heights[i] - targetH) * cost[i];
        }

        return (int)result;
    }
}

/*
 *
 * Dry Run
 * heights = [1,2,3], cost = [10,100,1000]
 *
 * low = 1, high = 3
 * mid = 2
 *   costMid = |1-2|*10 + |2-2|*100 + |3-2|*1000 = 10 + 0 + 1000 = 1010
 *   costMidP1 = |1-3|*10 + |2-3|*100 + |3-3|*1000 = 20 + 100 + 0 = 120
 *   costMid < costMidP1 → true → targetH = 2, high = 1
 *
 * loop ends
 * Final targetH = 2
 * Final cost = 10 + 0 + 1000 = 1010
 *
 */
