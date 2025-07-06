/*
 * GfG Link: https://www.geeksforgeeks.org/problems/maximum-sum-combination/1
 *
 * Maximum Sum Combination
 *
 * Difficulty: Medium Accuracy: 49.69% Submissions: 79K+ Points: 4 Average Time: 30m
 *
 * You are given two integer arrays a[] and b[] of equal size. A sum combination is formed by adding one element from a[] and one from b[], using each index pair (i, j) at most once. Return the top k maximum sum combinations, sorted in non-increasing order.
 *
 * Examples:
 *
 * Input: a[] = [3, 2], b[] = [1, 4], k = 2
 * Output: [7, 6]
 * Explanation: Possible sums: 3 + 1 = 4, 3 + 4 = 7, 2 + 1 = 3, 2 + 4 = 6, Top 2 sums are 7 and 6.
 *
 * Input: a[] = [1, 4, 2, 3], b[] = [2, 5, 1, 6], k = 3
 * Output: [10, 9, 9]
 * Explanation: The top 3 maximum possible sums are : 4 + 6 = 10, 3 + 6 = 9, and 4 + 5 = 9
 *
 * Constraints:
 * 1 ≤ a.size() = b.size() ≤ 10^5
 * 1 ≤ k ≤ a.size()
 * 1 ≤ a[i], b[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute-force all pair sums, sort descending, pick top k.
// Time Complexity: O((n^2) log(n^2)) — generate n^2 sums and sort them.
// Space Complexity: O(n^2) — storing all n^2 pair sums.
class Solution {
public:
    vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
        int n = a.size();

        // collect all possible sums of one element from 'a' and one from 'b'
        vector<int> combinedSum;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                combinedSum.push_back(a[i] + b[j]);  // push sum a[i] + b[j]
            }
        }

        // sort descending to bring largest sums to front
        sort(combinedSum.rbegin(), combinedSum.rend());

        // extract the top k sums
        vector<int> result;
        for (int idx = 0; idx < k; ++idx) {
            result.push_back(combinedSum[idx]);  // append the idx-th largest sum
        }

        return result;  // return top k sums
    }
};

/*
 *
 * Dry Run
 *
 * Input: a = [3, 2], b = [1, 4], k = 2
 *
 * vector<int> combinedSum;
 * // i=0, j=0 -> 3 + 1 = 4   → combinedSum = [4]
 * // i=0, j=1 -> 3 + 4 = 7   → combinedSum = [4, 7]
 * // i=1, j=0 -> 2 + 1 = 3   → combinedSum = [4, 7, 3]
 * // i=1, j=1 -> 2 + 4 = 6   → combinedSum = [4, 7, 3, 6]
 *
 * sort(combinedSum.rbegin(), combinedSum.rend());
 * // combinedSum after sort = [7, 6, 4, 3]
 *
 * vector<int> result;
 * // idx = 0 → result = [7]
 * // idx = 1 → result = [7, 6]
 *
 * return result;  // returns [7, 6]
 */

// Approach 2: Max‑heap + visited set to merge two descending arrays and extract top k sums without generating all n^2 pairs.
// Time Complexity: O(n log n + k log k) — sorting two arrays in O(n log n) and performing k heap pops/pushes in O(k log k).
// Space Complexity: O(k) — heap and visited set hold up to O(k) entries.
class Solution {
public:
    vector<int> topKSumPairs(vector<int>& a, vector<int>& b, int k) {
        int n = a.size();

        // sort both arrays in descending order
        sort(a.rbegin(), a.rend());                     // O(n log n)
        sort(b.rbegin(), b.rend());                     // O(n log n)

        // max-heap storing {sum, {i, j}}
        priority_queue<pair<int, pair<int, int>>> pq;
        set<pair<int, int>> st;                          // visited index‑pairs

        // seed with the largest pair (0,0)
        pq.push({ a[0] + b[0], { 0, 0 } });
        st.insert({ 0, 0 });

        vector<int> result;
        result.reserve(k);

        while (result.size() < k) {
            auto top = pq.top(); pq.pop();              // pop current max sum
            int  sum = top.first;
            int  i   = top.second.first;
            int  j   = top.second.second;

            result.push_back(sum);                      // record it

            // push neighbor (i, j+1) if within bounds and not seen
            if (j + 1 < n && st.emplace(i, j + 1).second) {
                pq.push({ a[i] + b[j + 1], { i, j + 1 } });
            }
            // push neighbor (i+1, j) if within bounds and not seen
            if (i + 1 < n && st.emplace(i + 1, j).second) {
                pq.push({ a[i + 1] + b[j], { i + 1, j } });
            }
        }
        return result;  // top k sums
    }
};

/*
 *
 * Dry Run
 *
 * Input: a = [2, 4, 1], b = [3, 5, 2], k = 4
 *
 * Step 1: sort descending
 *   a → [4, 2, 1]
 *   b → [5, 3, 2]
 *
 * Step 2: initialize
 *   pq = {(9, (0,0))}      // 4+5=9
 *   st = {(0,0)}
 *   result = []
 *
 * Step 3: pop (9,0,0)
 *   result = [9]
 *   push (i, j+1) = (0,1): sum=4+3=7
 *   push (i+1, j) = (1,0): sum=2+5=7
 *   pq = {(7,(0,1)), (7,(1,0))}
 *   st = {(0,0), (0,1), (1,0)}
 *
 * Step 4: pop one 7, say (7,1,0)
 *   result = [9, 7]
 *   push (1,1): 2+3=5
 *   push (2,0): 1+5=6
 *   pq = {(7,(0,1)), (6,(2,0)), (5,(1,1))}
 *   st adds (1,1), (2,0)
 *
 * Step 5: pop next 7 (7,0,1)
 *   result = [9, 7, 7]
 *   push (0,2): 4+2=6
 *   (1,1) already in st, skip
 *   pq = {(6,(2,0)), (6,(0,2)), (5,(1,1))}
 *   st adds (0,2)
 *
 * Step 6: pop 6 (6,2,0)
 *   result = [9, 7, 7, 6]
 *   push (2,1): 1+3=4
 *   (3,0) OOB, skip
 *   pq = {(6,(0,2)), (5,(1,1)), (4,(2,1))}
 *   st adds (2,1)
 *
 * result.size()==4 → stop.
 * Output: [9, 7, 7, 6]
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force all pair sums, sort descending, pick top k.
// Time Complexity: O((n^2) log(n^2)) — generate n^2 sums and sort them.
// Space Complexity: O(n^2) — storing all n^2 pair sums.
class Solution {
    public ArrayList<Integer> topKSumPairs(int[] a, int[] b, int k) {
        int n = a.length;

        // collect all possible sums of one element from 'a' and one from 'b'
        ArrayList<Integer> combinedSum = new ArrayList<>();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                combinedSum.add(a[i] + b[j]);  // push sum a[i] + b[j]
            }
        }

        // sort descending to bring largest sums to front
        Collections.sort(combinedSum, Collections.reverseOrder());

        // extract the top k sums
        ArrayList<Integer> result = new ArrayList<>();
        for (int idx = 0; idx < k; ++idx) {
            result.add(combinedSum.get(idx));  // append the idx-th largest sum
        }

        return result;  // return top k sums
    }
}

/*
 *
 * Dry Run
 *
 * Input: a = [3, 2], b = [1, 4], k = 2
 *
 * ArrayList<Integer> combinedSum = new ArrayList<>();
 * // i=0, j=0 -> 3 + 1 = 4   → combinedSum = [4]
 * // i=0, j=1 -> 3 + 4 = 7   → combinedSum = [4, 7]
 * // i=1, j=0 -> 2 + 1 = 3   → combinedSum = [4, 7, 3]
 * // i=1, j=1 -> 2 + 4 = 6   → combinedSum = [4, 7, 3, 6]
 *
 * Collections.sort(combinedSum, Collections.reverseOrder());
 * // combinedSum after sort = [7, 6, 4, 3]
 *
 * ArrayList<Integer> result = new ArrayList<>();
 * // idx = 0 → result = [7]
 * // idx = 1 → result = [7, 6]
 *
 * return result;  // returns [7, 6]
 */

// Approach 2: Max-heap + visited set to merge two descending arrays and extract top k sums without generating all n^2 pairs.
// Time Complexity: O(n log n + k log k) — sorting two arrays in O(n log n) and performing k heap pops/pushes in O(k log k).
// Space Complexity: O(k) — heap and visited set hold up to O(k) entries.
class Solution {
    // helper to reverse a sorted array in-place
    private void reverse(int[] arr) {
        for (int l = 0, r = arr.length - 1; l < r; l++, r--) {
            int tmp = arr[l]; arr[l] = arr[r]; arr[r] = tmp;
        }
    }
    public ArrayList<Integer> topKSumPairs(int[] a, int[] b, int k) {
        int n = a.length;

        // sort both arrays in descending order
        Arrays.sort(a); reverse(a);                   // O(n log n)
        Arrays.sort(b); reverse(b);                   // O(n log n)

        // max-heap storing int[]{sum, i, j}
        PriorityQueue<int[]> pq = new PriorityQueue<>(
            (x, y)->Integer.compare(y[0], x[0])
            );
        Set<String> st = new HashSet<>();             // visited "i#j"

        // seed with the largest pair (0,0)
        pq.offer(new int[]{ a[0] + b[0], 0, 0 });
        st.add("0#0");

        ArrayList<Integer> result = new ArrayList<>(k);

        while (result.size() < k) {
            int[] top = pq.poll();                    // pop current max
            int sum = top[0], i = top[1], j = top[2];
            result.add(sum);                          // record it

            // push neighbor (i, j+1)
            if (j + 1 < n) {
                String key1 = i + "#" + (j + 1);
                if (st.add(key1)) {
                    pq.offer(new int[]{ a[i] + b[j + 1], i, j + 1 });
                }
            }
            // push neighbor (i+1, j)
            if (i + 1 < n) {
                String key2 = (i + 1) + "#" + j;
                if (st.add(key2)) {
                    pq.offer(new int[]{ a[i + 1] + b[j], i + 1, j });
                }
            }
        }
        return result;  // top k sums
    }
}

/*
 *
 * Dry Run
 *
 * Input: a = [2, 4, 1], b = [3, 5, 2], k = 4
 *
 * Step 1: sort descending
 *   a → [4, 2, 1]
 *   b → [5, 3, 2]
 *
 * Step 2: initialize
 *   pq = {[9,0,0]}         // 4+5=9
 *   st = {"0#0"}
 *   result = []
 *
 * Step 3: poll [9,0,0]
 *   result = [9]
 *   offer [7,0,1], key="0#1"
 *   offer [7,1,0], key="1#0"
 *
 * Step 4: poll [7,1,0]
 *   result = [9,7]
 *   offer [5,1,1], key="1#1"
 *   offer [6,2,0], key="2#0"
 *
 * Step 5: poll [7,0,1]
 *   result = [9,7,7]
 *   offer [6,0,2], key="0#2"
 *   skip "1#1" (already in)
 *
 * Step 6: poll [6,2,0]
 *   result = [9,7,7,6]
 *   offer [4,2,1], key="2#1"
 *
 * size==4 → stop.
 * Output: [9, 7, 7, 6]
 */
