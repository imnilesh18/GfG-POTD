/*
 * GfG Link: https://www.geeksforgeeks.org/problems/kth-element-in-matrix/1
 * This question is same as : https://www.geeksforgeeks.org/problems/kth-smallest-number-in-multiplication-table/1
 *
 * Kth element in Matrix
 *
 * Difficulty: MediumAccuracy: 61.42%Submissions: 61K+Points: 4Average Time: 35m
 *
 * Given a matrix mat[][] of size n*n, where each row and column is sorted in non-decreasing order. Find the kth smallest element in the matrix.
 *
 * Examples:
 * Input: n = 4, mat[][] = [[16, 28, 60, 64], [22, 41, 63, 91], [27, 50, 87, 93], [36, 78, 87, 94]], k = 3
 * Output: 27
 * Explanation: 27 is the 3rd smallest element.
 *
 * Input: n = 4, mat[][] = [[10, 20, 30, 40], [15, 25, 35, 45], [24, 29, 37, 48], [32, 33, 39, 50]], k = 7
 * Output: 30
 * Explanation: 30 is the 7th smallest element.
 *
 * Constraints:
 * 1 <= n <= 500
 * 1 <= mat[i][j] <= 10000
 * 1 <= k <= n*n
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute-force — collect all elements into a vector, sort, and return the k-th smallest
// Time Complexity: O(n² log(n²)) = O(n² log n) due to sorting n² elements
// Space Complexity: O(n²) for storing all elements
class Solution {
public:
    int kthSmallest(vector<vector<int> >& matrix, int k) {
        int n = matrix.size();

        vector<int> result;                // store all matrix elements

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result.push_back(matrix[i][j]);
            }
        }
        sort(result.begin(), result.end()); // sort ascending
        return result[k - 1];               // return k-th smallest (1-based)
    }
};

/*
 *
 * Dry Run
 * Input: matrix = [[10,20,30,40],
 *                  [15,25,35,45],
 *                  [24,29,37,48],
 *                  [32,33,39,50]], k = 7
 * result before sort: [10,20,30,40,15,25,35,45,24,29,37,48,32,33,39,50]
 * after sort: [10,15,20,24,25,29,30,32,33,35,37,39,40,45,48,50]
 * k=7 → result[6] = 30
 *
 */

// Approach 2: Max‐heap — maintain a max-heap of size k, push/pop to keep k smallest
// Time Complexity: O(n² log k) for pushing n² elements into a heap of size ≤ k
// Space Complexity: O(k) for the heap
class Solution {
public:
    int kthSmallest(vector<vector<int> >& matrix, int k) {
        int n = matrix.size();

        priority_queue<int> pq; // max-heap

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val = matrix[i][j];
                if (pq.size() < k) {
                    pq.push(val);
                } else if (val < pq.top()) {
                    pq.pop();
                    pq.push(val);
                }
            }
        }
        return pq.top(); // root is k-th smallest
    }
};

/*
 *
 * Dry Run
 * Input: matrix = [[1,5,9],
 *                  [10,11,13],
 *                  [12,13,15]], k = 8
 * heap evolution (size≤8):
 * push 1,5,9,10,11,13,12,13 → heap = [13,13,12,11,10,9,5,1]
 * next 15 → 15>13 skip
 * top of heap = 13 → 8th smallest
 *
 */

// Approach 3: Binary-search on value range + “count ≤ mid” via two-pointer per row
// Time Complexity: O(n log(max−min)) where each count is O(n)
// Space Complexity: O(1)
class Solution {
public:
    // count how many elements ≤ mid
    int count(int mid, vector<vector<int> >& matrix) {
        int n = matrix.size();

        int i = 0;
        int j = n - 1;

        int countSum = 0;

        while (i < n && j >= 0) {
            if (matrix[i][j] <= mid) {
                countSum += (j + 1);
                i++;
            } else {
                j--;
            }
        }
        return countSum;
    }
    int kthSmallest(vector<vector<int> >& matrix, int k) {
        int n = matrix.size();

        int l = matrix[0][0];
        int h = matrix[n - 1][n - 1];

        while (l < h) {
            int mid = l + (h - l) / 2;
            if (count(mid, matrix) >= k) {
                h = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
};

/*
 *
 * Dry Run
 * Input: matrix = [[1,5,9],
 *                  [10,11,13],
 *                  [12,13,15]], k = 6
 * l=1, h=15
 * mid=8 → countLE(8)=3 (row0:3,row1:0,row2:0) <6 → l=9
 * mid=12 → countLE(12)=5 (row0:3,row1:2,row2:0) <6 → l=13
 * mid=14 → countLE(14)=8 (row0:3,row1:3,row2:2) ≥6 → h=14
 * mid=13 → countLE(13)=8 ≥6 → h=13
 * l==h==13 → return 13
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force — collect all elements into a list, sort, and return the k-th smallest
// Time Complexity: O(n² log(n²)) = O(n² log n) due to sorting n² elements
// Space Complexity: O(n²) for storing all elements
class Solution {
    public int kthSmallest(int[][] matrix, int k) {
        int n = matrix.length;

        List<Integer> result = new ArrayList<>(); // store all matrix elements

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result.add(matrix[i][j]);
            }
        }
        result.sort(null);        // sort ascending
        return result.get(k - 1); // return k-th smallest (1-based)
    }
}

/*
 *
 * Dry Run
 * Input: matrix = [[10,20,30,40],
 *                  [15,25,35,45],
 *                  [24,29,37,48],
 *                  [32,33,39,50]], k = 7
 * result before sort: [10,20,30,40,15,25,35,45,24,29,37,48,32,33,39,50]
 * after sort: [10,15,20,24,25,29,30,32,33,35,37,39,40,45,48,50]
 * k=7 → result.get(6) = 30
 *
 */

// Approach 2: Max‐heap — maintain a max-heap of size k, push/pop to keep k smallest
// Time Complexity: O(n² log k) for pushing n² elements into a heap of size ≤ k
// Space Complexity: O(k) for the heap
class Solution {
    public int kthSmallest(int[][] matrix, int k) {
        int n = matrix.length;

        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder()); // max-heap

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int val = matrix[i][j];
                if (pq.size() < k) {
                    pq.offer(val);
                } else if (val < pq.peek()) {
                    pq.poll();
                    pq.offer(val);
                }
            }
        }
        return pq.peek(); // root is k-th smallest
    }
}

/*
 *
 * Dry Run
 * Input: matrix = [[1,5,9],
 *                  [10,11,13],
 *                  [12,13,15]], k = 8
 * heap evolution (size≤8):
 * push 1,5,9,10,11,13,12,13 → heap = [13,13,12,11,10,9,5,1]
 * next 15 → 15>13 skip
 * top of heap = 13 → 8th smallest
 *
 */

// Approach 3: Binary-search on value range + “count ≤ mid” via two-pointer per row
// Time Complexity: O(n log(max−min)) where each count is O(n)
// Space Complexity: O(1)
class Solution {
    // count how many elements ≤ mid
    private int count(int mid, int[][] matrix) {
        int n = matrix.length;

        int i = 0;
        int j = n - 1;

        int countSum = 0;

        while (i < n && j >= 0) {
            if (matrix[i][j] <= mid) {
                countSum += (j + 1);
                i++;
            } else {
                j--;
            }
        }
        return countSum;
    }
    public int kthSmallest(int[][] matrix, int k) {
        int n = matrix.length;

        int l = matrix[0][0];
        int h = matrix[n - 1][n - 1];

        while (l < h) {
            int mid = l + (h - l) / 2;
            if (count(mid, matrix) >= k) {
                h = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
}

/*
 *
 * Dry Run
 * Input: matrix = [[1,5,9],
 *                  [10,11,13],
 *                  [12,13,15]], k = 6
 * l=1, h=15
 * mid=8 → count(8)=3 (row0:3,row1:0,row2:0) <6 → l=9
 * mid=12 → count(12)=5 (row0:3,row1:2,row2:0) <6 → l=13
 * mid=14 → count(14)=8 (row0:3,row1:3,row2:2) ≥6 → h=14
 * mid=13 → count(13)=8 ≥6 → h=13
 * l==h==13 → return 13
 *
 */
