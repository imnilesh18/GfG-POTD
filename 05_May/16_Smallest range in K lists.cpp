/*
 * GfG Link: https://www.geeksforgeeks.org/problems/find-smallest-range-containing-elements-from-k-lists/1
 *
 * Smallest range in K lists
 *
 * Difficulty: Hard Accuracy: 43.21% Submissions: 30K+ Points: 8 Average Time: 40m
 *
 * Given a 2d integer array arr[][] of size k*n, where each row is sorted in ascending order. Your task is to find the smallest range [l, r] that includes at least one element from each of the k lists. If more than one such ranges are found, return the first one.
 *
 * Examples:
 *
 * Input: n = 5, k = 3, arr[][] = [[4, 7, 9, 12, 15], [0, 8, 10, 14, 20], [6, 12, 16, 30, 50]]
 * Output: [6, 8]
 * Explanation: Smallest range is formed by  number 7 from the first list, 8 from second list and 6 from the third list.
 *
 * Input: n = 5, k = 3, arr[][] = [[1, 3, 5, 7, 9], [0, 2, 4, 6, 8], [2, 3, 5, 7, 11]]
 * Output: [1, 2]
 * Explanation: Smallest range is formed by number 1 present in first list and 2 is present in both 2nd and 3rd list.
 *
 * Input: n = 2, k = 3, arr[][] = [[2, 4], [1, 7], [20, 40]]
 * Output: [4, 20]
 * Explanation: Smallest range is formed by number 4 from the first list, 7 from second list and 20 from the third list.
 *
 * Constraints:
 * 1 <= k, n <= 500
 * 0 <= arr[ i ] <= 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Use a min-heap to always get the smallest current element across the lists, track the maximum element so far, and slide the window to find the smallest range that includes one element from each list.
// Time Complexity: O(n * log k), where n is the number of elements per list and k is the number of lists. Each insertion/removal from the heap takes log k time and there are at most n * k elements.
// Space Complexity: O(k), for storing k elements in the min-heap at a time.
class Solution {
public:
    vector<int> findSmallestRange(vector<vector<int>>& arr) {
        int n = arr.size();    // number of rows (k lists)
        int m = arr[0].size(); // number of elements in each row

        // Min-heap to store the current minimum element from each list
        // Pair structure: {element_value, {row_index, column_index}}
        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>,
                       greater<>> minHeap;

        int maxVal   = INT_MIN; // To track the current maximum among heap elements
        int maxEl    = -1;      // Final max of the smallest range
        int minEl    = -1;      // Final min of the smallest range
        int minRange = INT_MAX; // Initialize minRange to maximum possible

        // Initialize heap with first element from each list and update maxVal
        for (int i = 0; i < n; i++) {
            minHeap.push({ arr[i][0], { i, 0 } });
            maxVal = max(maxVal, arr[i][0]); // Update the maximum value so far
        }

        // Iterate until we reach the end of any list
        while (true) {
            auto top = minHeap.top(); // Get the smallest current element
            minHeap.pop();

            int minVal = top.first;         // Current minimum value
            int row    = top.second.first;  // Row of the min element
            int col    = top.second.second; // Column of the min element

            // Update the range if current [minVal, maxVal] is smaller
            if (maxVal - minVal < minRange) {
                minRange = maxVal - minVal;
                minEl    = minVal;
                maxEl    = maxVal;
            }

            // If this list is exhausted, we can't find further complete ranges
            if (col + 1 == m) {
                break;
            }

            // Push the next element from the same row into the heap
            int nextVal = arr[row][col + 1];
            minHeap.push({ nextVal, { row, col + 1 } });

            // Update maxVal if needed
            maxVal = max(maxVal, nextVal);
        }

        return { minEl, maxEl }; // Return the smallest range
    }
};

/*
 *
 * Dry Run
 * Input: n = 5, k = 3
 * arr = [
 *  [4, 7, 9, 12, 15],
 *  [0, 8, 10, 14, 20],
 *  [6, 12, 16, 30, 50]
 *]
 *
 * Step 1: Push 4, 0, 6 into minHeap. maxVal = 6
 * Heap = [(0, (1, 0)), (4, (0, 0)), (6, (2, 0))] → minVal = 0, range = 6-0 = 6
 *
 * Step 2: Pop 0, push 8 (from arr[1][1]) → Heap = [(4, (0, 0)), (6, (2, 0)), (8, (1, 1))] → maxVal = 8
 * New range = 8-4 = 4 → Update range [4, 8]
 *
 * Step 3: Pop 4, push 7 → Heap = [(6, (2, 0)), (8, (1, 1)), (7, (0, 1))] → maxVal = 8
 * New range = 8-6 = 2 → Update range [6, 8]
 *
 * Step 4: Pop 6, push 12 → Heap = [(7, (0, 1)), (8, (1, 1)), (12, (2, 1))] → maxVal = 12
 * New range = 12-7 = 5 → Do not update
 *
 * Continue this process... but range [6, 8] remains smallest including all lists.
 *
 * Final output: [6, 8]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a min-heap to always get the smallest current element across the lists, track the maximum element so far, and slide the window to find the smallest range that includes one element from each list.
// Time Complexity: O(n * log k), where n is the number of elements per list and k is the number of lists. Each insertion/removal from the heap takes log k time and there are at most n * k elements.
// Space Complexity: O(k), for storing k elements in the min-heap at a time.
class Solution {
    static class Node {
        int val, row, col;
        Node(int val, int row, int col) {
            this.val = val;
            this.row = row;
            this.col = col;
        }
    }

    public ArrayList<Integer> findSmallestRange(int[][] arr) {
        int n = arr.length;    // rows
        int m = arr[0].length; // columns

        PriorityQueue<Node> minHeap = new PriorityQueue<>((a, b)->a.val - b.val);

        int maxVal   = Integer.MIN_VALUE;
        int maxEl    = -1;
        int minEl    = -1;
        int minRange = Integer.MAX_VALUE;

        // Initialize minHeap with first element from each list and set maxVal
        for (int i = 0; i < n; i++) {
            minHeap.add(new Node(arr[i][0], i, 0));
            maxVal = Math.max(maxVal, arr[i][0]);
        }

        while (true) {
            Node top    = minHeap.poll(); // Get the minimum element
            int  minVal = top.val;
            int  row    = top.row;
            int  col    = top.col;

            // Update smallest range if current range is smaller
            if (maxVal - minVal < minRange) {
                minRange = maxVal - minVal;
                minEl    = minVal;
                maxEl    = maxVal;
            }

            // If the current list is exhausted, stop the process
            if (col + 1 == m) {
                break;
            }

            // Push the next element from the same list
            int nextVal = arr[row][col + 1];
            minHeap.add(new Node(nextVal, row, col + 1));

            // Update maxVal if necessary
            maxVal = Math.max(maxVal, nextVal);
        }

        ArrayList<Integer> result = new ArrayList<>();
        result.add(minEl);
        result.add(maxEl);
        return result;
    }
}

/*
 *
 * Dry Run
 * Input: arr = [
 *   [4, 7, 9, 12, 15],
 *   [0, 8, 10, 14, 20],
 *   [6, 12, 16, 30, 50]
 *]
 *
 * Initial: Insert 4, 0, 6 → maxVal = 6
 * Heap: [0, 4, 6] → minVal = 0 → range = 6
 *
 * Pop 0 → Push 8 → Heap = [4, 6, 8], maxVal = 8 → range = 4
 *
 * Pop 4 → Push 7 → Heap = [6, 8, 7], maxVal = 8 → range = 2 → Update minEl = 6, maxEl = 8
 *
 * Pop 6 → Push 12 → Heap = [7, 8, 12], maxVal = 12 → range = 5 → No update
 *
 * Further pops won't lead to smaller range
 * Final result = [6, 8]
 *
 */
