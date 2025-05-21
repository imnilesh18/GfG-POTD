/*
 * GfG Link: https://www.geeksforgeeks.org/problems/kth-smallest-number-in-multiplication-table/1
 *
 * Kth Smallest Number in Multiplication Table
 *
 * Difficulty: Hard Accuracy: 44.6% Submissions: 6K+ Points: 8
 *
 * Given three integers m, n and k. Consider a grid of m * n, where mat[i][j] = i * j (1 based index). The task is to return the kth smallest element in the m * n multiplication table.
 *
 * Examples :
 *
 * Input: m = 3, n = 3, k = 5
 * Output: 3
 * Explanation:
 * The 5th smallest element is 3.
 *
 * Input: m = 2, n = 3, k = 6
 * Output: 6
 * Explanation: [1, 2, 3][2, 4, 6]. The 6th smallest element is 6.
 *
 * Constraints:
 * 1 <= m, n <= 3 * 10^4
 * 1 <= k <= m * n
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute-force method where we generate all values of the multiplication table (i * j), store them in a list, sort it, and return the k-th smallest.
// Time Complexity: O(m * n log(m * n)) due to sorting the entire multiplication table values.
// Space Complexity: O(m * n) for storing all the values in the multiplication table.
class Solution {
public:
    int kthSmallest(int m, int n, int k) {
        vector<int> result;                // Create a vector to store all elements of the multiplication table

        for (int i = 1; i <= m; i++) {     // Loop through rows
            for (int j = 1; j <= n; j++) { // Loop through columns
                result.push_back(i * j);   // Insert product i*j into the result vector
            }
        }

        sort(result.begin(), result.end()); // Sort all the values

        return result[k - 1];               // Return the k-th smallest element (0-based index)
    }
};

/*
 *
 * Dry Run
 * Input: m = 3, n = 3, k = 5
 * Multiplication table:
 * Row 1: 1*1=1, 1*2=2, 1*3=3 → [1, 2, 3]
 * Row 2: 2*1=2, 2*2=4, 2*3=6 → [2, 4, 6]
 * Row 3: 3*1=3, 3*2=6, 3*3=9 → [3, 6, 9]
 * Combined result before sort: [1, 2, 3, 2, 4, 6, 3, 6, 9]
 * After sort: [1, 2, 2, 3, 3, 4, 6, 6, 9]
 * k = 5 → k-1 = 4 → result[4] = 3
 * Output: 3
 *
 */

// Approach 2: Use a max-heap (priority_queue) to keep track of the k smallest elements while traversing the multiplication table.
// Time Complexity: O(m * n * log k) because for each of the m*n elements, we may insert/remove from the heap of size k.
// Space Complexity: O(k) for maintaining a heap of at most k elements.
class Solution {
public:
    int kthSmallest(int m, int n, int k) {
        priority_queue<int> pq; // Max-heap to store k smallest elements

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int val = i * j; // Compute current cell value

                if (pq.size() < k) {
                    pq.push(val); // Push if heap is not full
                } else if (val < pq.top()) {
                    pq.pop();     // Remove the largest in heap
                    pq.push(val); // Push the smaller value
                }
            }
        }

        return pq.top(); // Top of the max-heap is the kth smallest
    }
};

/*
 *
 * Dry Run
 * Input: m = 3, n = 3, k = 5
 * Multiplication table values generated in order:
 * 1, 2, 3, 2, 4, 6, 3, 6, 9
 * Heap size increases till it has 5 elements:
 * Push: 1 → [1]
 * Push: 2 → [2,1]
 * Push: 3 → [3,2,1]
 * Push: 2 → [3,2,1,2]
 * Push: 4 → [4,3,1,2,2]
 * Next: 6 → skip (6 > top 4)
 * Next: 3 → 3 < 4 → pop 4, push 3 → [3,3,1,2,2]
 * Next: 6 → skip
 * Next: 9 → skip
 * Final heap (unordered): [3,3,1,2,2]
 * Top element = 3 → kth smallest
 *
 */

// Approach 3: Use Binary Search on the value space (1 to m*n). For each mid value, count how many elements are ≤ mid using a helper function.
// Time Complexity: O(m * log(m * n)) — Binary search with each count taking O(m).
// Space Complexity: O(1) — Constant space used.
class Solution {
public:
    // Function to count how many numbers are ≤ mid in the table
    int count(int mid, int m, int n) {
        int countSum = 0;

        for (int i = 1; i <= m; i++) {
            countSum += min(mid / i, n); // Each row contributes min(mid / i, n) elements
        }
        return countSum;
    }

    int kthSmallest(int m, int n, int k) {
        int l = 1;
        int h = m * n;

        while (l < h) {
            int mid = (l + h) / 2;

            if (count(mid, m, n) >= k) {
                h = mid;     // mid might be the answer
            } else {
                l = mid + 1; // ignore left half
            }
        }

        return l; // l is the k-th smallest number
    }
};

/*
 *
 * Dry Run
 * Input: m = 3, n = 3, k = 5
 * Search space: [1, 9] because max element is 3*3 = 9
 *
 * Step 1:
 * mid = (1+9)/2 = 5
 * count(5):
 *  i = 1 → 5/1 = 5 → min(5,3) = 3
 *  i = 2 → 5/2 = 2 → min(2,3) = 2
 *  i = 3 → 5/3 = 1 → min(1,3) = 1
 * Total = 3+2+1 = 6 → 6 ≥ 5 → h = 5
 *
 * Step 2:
 * mid = (1+5)/2 = 3
 * count(3):
 *  i = 1 → 3/1 = 3 → min(3,3) = 3
 *  i = 2 → 3/2 = 1 → min(1,3) = 1
 *  i = 3 → 3/3 = 1 → min(1,3) = 1
 * Total = 3+1+1 = 5 → 5 ≥ 5 → h = 3
 *
 * Step 3:
 * mid = (1+3)/2 = 2
 * count(2):
 *  i = 1 → 2/1 = 2 → min(2,3) = 2
 *  i = 2 → 2/2 = 1 → min(1,3) = 1
 *  i = 3 → 2/3 = 0 → min(0,3) = 0
 * Total = 2+1+0 = 3 → 3 < 5 → l = 3
 *
 * Now l == h == 3 → return 3
 *
 * Output: 3
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force method where we generate all values of the multiplication table (i * j), store them in a list, sort it, and return the k-th smallest.
// Time Complexity: O(m * n log(m * n)) due to sorting the entire multiplication table values.
// Space Complexity: O(m * n) for storing all the values in the multiplication table.
class Solution {
    public int kthSmallest(int m, int n, int k) {
        List<Integer> result = new ArrayList<>(); // List to store multiplication table elements

        for (int i = 1; i <= m; i++) {            // Loop through rows
            for (int j = 1; j <= n; j++) {        // Loop through columns
                result.add(i * j);                // Add i * j to the list
            }
        }

        Collections.sort(result); // Sort the entire list

        return result.get(k - 1); // Return the k-th smallest element (0-based indexing)
    }
}

/*
 *
 * Dry Run
 * Input: m = 3, n = 3, k = 5
 * Multiplication table:
 * Row 1: 1*1=1, 1*2=2, 1*3=3 → [1, 2, 3]
 * Row 2: 2*1=2, 2*2=4, 2*3=6 → [2, 4, 6]
 * Row 3: 3*1=3, 3*2=6, 3*3=9 → [3, 6, 9]
 * Combined result before sort: [1, 2, 3, 2, 4, 6, 3, 6, 9]
 * After sort: [1, 2, 2, 3, 3, 4, 6, 6, 9]
 * k = 5 → k-1 = 4 → result.get(4) = 3
 * Output: 3
 *
 */

// Approach 2: Use a max-heap (PriorityQueue with custom comparator) to maintain k smallest elements while traversing the table.
// Time Complexity: O(m * n * log k) due to insert/delete operations on a heap of size k.
// Space Complexity: O(k) to store up to k elements in the heap.
class Solution {
    public int kthSmallest(int m, int n, int k) {
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder()); // Max-heap

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int val = i * j;

                if (pq.size() < k) {
                    pq.add(val); // Add directly if heap isn't full
                } else if (val < pq.peek()) {
                    pq.poll();   // Remove largest
                    pq.add(val); // Add smaller value
                }
            }
        }

        return pq.peek(); // Return the kth smallest value
    }
}

/*
 *
 * Dry Run
 * Input: m = 3, n = 3, k = 5
 * Multiplication table values generated in order:
 * 1, 2, 3, 2, 4, 6, 3, 6, 9
 * Heap size increases till it has 5 elements:
 * Push: 1 → [1]
 * Push: 2 → [2,1]
 * Push: 3 → [3,2,1]
 * Push: 2 → [3,2,1,2]
 * Push: 4 → [4,3,1,2,2]
 * Next: 6 → skip (6 > top 4)
 * Next: 3 → 3 < 4 → pop 4, push 3 → [3,3,1,2,2]
 * Next: 6 → skip
 * Next: 9 → skip
 * Final heap (unordered): [3,3,1,2,2]
 * Top element = 3 → kth smallest
 *
 */

// Approach 3: Use Binary Search on the range [1, m*n]. For each mid, count how many elements are ≤ mid using a helper.
// Time Complexity: O(m * log(m * n)) because each binary search iteration counts O(m) elements.
// Space Complexity: O(1) — Only constant extra space.
class Solution {
    public int count(int mid, int m, int n) {
        int countSum = 0;

        for (int i = 1; i <= m; i++) {
            countSum += Math.min(mid / i, n); // Count how many elements in row i are ≤ mid
        }
        return countSum;
    }
    
    public int kthSmallest(int m, int n, int k) {
        int l = 1;
        int h = m * n;

        while (l < h) {
            int mid = (l + h) / 2;

            if (count(mid, m, n) >= k) {
                h = mid;     // mid might be part of the result
            } else {
                l = mid + 1; // look in the right half
            }
        }

        return l; // l will be the smallest number with at least k elements ≤ it
    }
}

/*
 *
 * Dry Run
 * Input: m = 3, n = 3, k = 5
 * Search space: [1, 9] because max element is 3*3 = 9
 *
 * Step 1:
 * mid = (1+9)/2 = 5
 * count(5):
 *  i = 1 → 5/1 = 5 → min(5,3) = 3
 *  i = 2 → 5/2 = 2 → min(2,3) = 2
 *  i = 3 → 5/3 = 1 → min(1,3) = 1
 * Total = 3+2+1 = 6 → 6 ≥ 5 → h = 5
 *
 * Step 2:
 * mid = (1+5)/2 = 3
 * count(3):
 *  i = 1 → 3/1 = 3 → min(3,3) = 3
 *  i = 2 → 3/2 = 1 → min(1,3) = 1
 *  i = 3 → 3/3 = 1 → min(1,3) = 1
 * Total = 3+1+1 = 5 → 5 ≥ 5 → h = 3
 *
 * Step 3:
 * mid = (1+3)/2 = 2
 * count(2):
 *  i = 1 → 2/1 = 2 → min(2,3) = 2
 *  i = 2 → 2/2 = 1 → min(1,3) = 1
 *  i = 3 → 2/3 = 0 → min(0,3) = 0
 * Total = 2+1+0 = 3 → 3 < 5 → l = 3
 *
 * Now l == h == 3 → return 3
 *
 * Output: 3
 *
 */
