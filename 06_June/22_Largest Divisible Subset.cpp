/*
 * GfG Link: https://www.geeksforgeeks.org/problems/largest-divisible-subset--170643/1
 *
 * Largest Divisible Subset
 *
 * Difficulty: Medium Accuracy: 43.48% Submissions: 9K+ Points: 4 Average Time: 20m
 *
 * Given an array arr[] of distinct positive integers. Your task is to find the largest subset such that for every pair of elements (x, y) in the subset, either x divides y or y divides x.
 * Note : If multiple subsets of the same maximum length exist, return the one that is lexicographically greatest, after sorting the subset in ascending order.
 *
 * Examples:
 *
 * Input: arr[] = [1, 16, 7, 8, 4]
 * Output: [1, 4, 8, 16]
 * Explanation: The largest divisible subset is [1, 4, 8, 16], where each element divides the next one. This subset is already the lexicographically greatest one.
 *
 * Input: arr[] = [2, 4, 3, 8]
 * Output: [2, 4, 8]
 * Explanation: The largest divisible subset is [2, 4, 8], where each element divides the next one. This subset is already the lexicographically greatest one.
 *
 * Constraint:
 * 1 ≤ arr.size() ≤ 10^3
 * 1  ≤ arr[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach:
// - We are trying to find the largest divisible subset in the given array.
// - We use a backtracking approach where at each index, we make two choices:
//   1) Include the current element in the subset if it is divisible by the previous one.
//   2) Skip the current element.
// - If we include an element, we add it to a temporary list (`temp`) and proceed to the next index recursively.
// - Once all indices are processed, we check if the current subset (`temp`) is larger (or lexicographically greater if sizes are equal) than the stored result (`result`), and update `result` if necessary.

// Time Complexity:
// - Sorting the array takes O(n log n). The recursion explores all subsets, and for each element, we either include it or not, resulting in O(2^n) calls.
// - So, the total time complexity is O(n log n + 2^n) due to sorting and the recursive calls.

// Space Complexity:
// - The space complexity is O(n) for the recursion stack and the temporary storage (`temp`), which holds a subset at any given point.

class Solution {
public:
    // Helper function for recursion with backtracking
    void solve(int idx, vector<int>& arr, vector<int>& result, vector<int>& temp, int prev) {
        if (idx >= arr.size()) {
            // replace if strictly larger, or same size but lexicographically greater
            if (temp.size() > result.size() ||
                (temp.size() == result.size() && temp > result)) {
                result = temp;
            }
            return;
        }

        // include arr[idx] if divisible
        if (prev == -1 || arr[idx] % prev == 0) {
            temp.push_back(arr[idx]);                    // Add the element to temp
            solve(idx + 1, arr, result, temp, arr[idx]); // Recurse for the next element
            temp.pop_back();                             // Backtrack, remove the element from temp
        }

        // skip arr[idx]
        solve(idx + 1, arr, result, temp, prev);  // Recurse for the next element without including arr[idx]
    }
    // Function to return the largest divisible subset
    vector<int> largestSubset(vector<int>& arr) {
        sort(arr.begin(), arr.end());    // Sort the array to ensure lexicographical order
        vector<int> result, temp;        // To store the largest subset and temporary subset during recursion
        solve(0, arr, result, temp, -1); // Start the recursive function
        return result;                   // Return the largest subset found
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 4, 8]
 *
 * 1. Sort the array (although it's already sorted): [1, 2, 4, 8]
 * 2. Initial Call: `solve(0, [1, 2, 4, 8], result = [], temp = [], prev = -1)`
 *  - `temp = []`
 *  - `prev = -1` (no previous element, so we can include `1`)
 *  - Include `1` → `temp = [1]`
 *  - Call: `solve(1, [1, 2, 4, 8], result = [], temp = [1], prev = 1)`
 *
 * 3. Second Call: `solve(1, [1, 2, 4, 8], result = [], temp = [1], prev = 1)`
 *  - `temp = [1]`
 *  - `prev = 1` (we can include `2` because `2 % 1 == 0`)
 *  - Include `2` → `temp = [1, 2]`
 *  - Call: `solve(2, [1, 2, 4, 8], result = [], temp = [1, 2], prev = 2)`
 *
 * 4. Third Call: `solve(2, [1, 2, 4, 8], result = [], temp = [1, 2], prev = 2)`
 *  - `temp = [1, 2]`
 *  - `prev = 2` (we can include `4` because `4 % 2 == 0`)
 *  - Include `4` → `temp = [1, 2, 4]`
 *  - Call: `solve(3, [1, 2, 4, 8], result = [], temp = [1, 2, 4], prev = 4)`
 *
 * 5. Fourth Call: `solve(3, [1, 2, 4, 8], result = [], temp = [1, 2, 4], prev = 4)`
 *  - `temp = [1, 2, 4]`
 *  - `prev = 4` (we can include `8` because `8 % 4 == 0`)
 *  - Include `8` → `temp = [1, 2, 4, 8]`
 *  - Call: `solve(4, [1, 2, 4, 8], result = [], temp = [1, 2, 4, 8], prev = 8)`
 *
 * 6. Fifth Call: `solve(4, [1, 2, 4, 8], result = [], temp = [1, 2, 4, 8], prev = 8)`
 *  - `idx = 4`, which is out of bounds. Check if `temp` is larger than `result`.
 *  - `temp.size() = 4`, `result.size() = 0` → Update `result = [1, 2, 4, 8]`
 *  - Return to the previous call.
 *
 * 7. Backtrack and explore other options:
 *  - Skip `8` → Call: `solve(4, [1, 2, 4, 8], result = [1, 2, 4, 8], temp = [1, 2, 4], prev = 4)`
 *  - Continue backtracking.
 *
 * 8. Eventually, return to the first call: `result = [1, 2, 4, 8]`
 *
 * Output: `[1, 2, 4, 8]`
 */

// Approach:
// - This solution uses dynamic programming (DP) with memoization to find the largest divisible subset from the given array.
// - At each index, we make two choices:
//   1) Include the current element in the subset if it is divisible by the previous element in the subset.
//   2) Skip the current element and move to the next index.
// - The `dp` table stores the best subset for every state `(idx, prev_idx)` where `idx` is the current element's index and `prev_idx` is the last included index.
// - The function is recursively called with two options (including or skipping the current element), and the larger subset (or lexicographically larger if sizes are the same) is stored in the memoization table.

// Time Complexity:
// - Sorting the array takes O(n log n). The recursion explores all possible subsets, and for each element, we either include it or skip it, leading to O(2^n) calls.
// - The total time complexity is O(n log n + 2^n) due to sorting and the recursive calls.

// Space Complexity:
// - The space complexity is O(n^2) because the memoization table `dp` has dimensions `n x (n + 1)`, and the recursion stack uses O(n) space.
//   Therefore, the overall space complexity is O(n^2).

class Solution {
public:
    // Memoization table to store the best subsets
    vector<vector<vector<int> > > dp;

    // Helper function for recursion with memoization
    vector<int> solve(int idx, vector<int>& arr, int prev_idx) {
        // Base case: if idx is out of bounds, return an empty vector
        if (idx == arr.size()) {
            return {};
        }

        // If already computed, return the result from dp
        if (dp[idx][prev_idx + 1].size() > 0) {
            return dp[idx][prev_idx + 1];
        }

        // Option 1: Take arr[idx] if divisible by arr[prev_idx]
        vector<int> taken;
        if (prev_idx == -1 || arr[idx] % arr[prev_idx] == 0) {
            taken = solve(idx + 1, arr, idx);      // Take current element
            taken.insert(taken.begin(), arr[idx]); // Add current element to the result
        }

        // Option 2: Skip arr[idx]
        vector<int> not_take = solve(idx + 1, arr, prev_idx);  // Skip current element

        // Compare the result from both options and store the larger one
        vector<int> result = (not_take.size() > taken.size() || (not_take.size() == taken.size() && not_take > taken))
                              ? not_take : taken;

        // Memoize the result and return
        return dp[idx][prev_idx + 1] = result;
    }
    vector<int> largestSubset(vector<int>& arr) {
        int n = arr.size();

        sort(arr.begin(), arr.end());  // Sort the array to ensure lexicographical order

        // Initialize dp table once in the function
        dp = vector<vector<vector<int> > >(n, vector<vector<int> >(n + 1));

        // Start the recursion with no previous element (-1) and from index 0
        return solve(0, arr, -1);
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 4, 8]
 *
 * 1. Sort the array (already sorted): [1, 2, 4, 8]
 * 2. Initial Call: `solve(0, [1, 2, 4, 8], dp, result = [], temp = [], prev_idx = -1)`
 *  - `prev_idx = -1` (no previous element, so we can include `1`)
 *  - Include `1` → `temp = [1]`
 *  - Call: `solve(1, [1, 2, 4, 8], dp, result = [], temp = [1], prev_idx = 0)`
 *
 * 3. Second Call: `solve(1, [1, 2, 4, 8], dp, result = [], temp = [1], prev_idx = 0)`
 *  - `prev_idx = 0` (we can include `2` because `2 % 1 == 0`)
 *  - Include `2` → `temp = [1, 2]`
 *  - Call: `solve(2, [1, 2, 4, 8], dp, result = [], temp = [1, 2], prev_idx = 1)`
 *
 * 4. Third Call: `solve(2, [1, 2, 4, 8], dp, result = [], temp = [1, 2], prev_idx = 1)`
 *  - `prev_idx = 1` (we can include `4` because `4 % 2 == 0`)
 *  - Include `4` → `temp = [1, 2, 4]`
 *  - Call: `solve(3, [1, 2, 4, 8], dp, result = [], temp = [1, 2, 4], prev_idx = 2)`
 *
 * 5. Fourth Call: `solve(3, [1, 2, 4, 8], dp, result = [], temp = [1, 2, 4], prev_idx = 2)`
 *  - `prev_idx = 2` (we can include `8` because `8 % 4 == 0`)
 *  - Include `8` → `temp = [1, 2, 4, 8]`
 *  - Call: `solve(4, [1, 2, 4, 8], dp, result = [], temp = [1, 2, 4, 8], prev_idx = 3)`
 *
 * 6. Fifth Call: `solve(4, [1, 2, 4, 8], dp, result = [], temp = [1, 2, 4, 8], prev_idx = 3)`
 *  - `idx = 4`, which is out of bounds. Check if `temp` is larger than `result`.
 *  - `temp.size() = 4`, `result.size() = 0` → Update `result = [1, 2, 4, 8]`
 *  - Return to the previous call.
 *
 * 7. Backtrack and explore other options:
 *  - Skip `8` → Call: `solve(4, [1, 2, 4, 8], dp, result = [1, 2, 4, 8], temp = [1, 2, 4], prev_idx = 2)`
 *  - Continue backtracking.
 *
 * 8. Eventually, return to the first call: `result = [1, 2, 4, 8]`
 *
 * Output: `[1, 2, 4, 8]`
 */

/************************************************************ JAVA ************************************************/

// Approach:
// - We are trying to find the largest divisible subset in the given array.
// - We use a backtracking approach where at each index, we make two choices:
//   1) Include the current element in the subset if it is divisible by the previous one.
//   2) Skip the current element.
// - If we include an element, we add it to a temporary list (`temp`) and proceed to the next index recursively.
// - Once all indices are processed, we check if the current subset (`temp`) is larger (or lexicographically greater if sizes are equal) than the stored result (`result`), and update `result` if necessary.

// Time Complexity:
// - Sorting the array takes O(n log n). The recursion explores all subsets, and for each element, we either include it or not, resulting in O(2^n) calls.
// - So, the total time complexity is O(n log n + 2^n) due to sorting and the recursive calls.

// Space Complexity:
// - The space complexity is O(n) for the recursion stack and the temporary storage (`temp`), which holds a subset at any given point.

class Solution {
    // Helper function for recursion with backtracking
    private void solve(int idx, int[] arr, ArrayList<Integer> result, ArrayList<Integer> temp, int prev) {
        if (idx >= arr.length) {
            // replace if strictly larger, or same size but lexicographically greater
            if (temp.size() > result.size() ||
                (temp.size() == result.size() && isLexGreater(temp, result))) {
                result.clear();
                result.addAll(temp);
            }
            return;
        }

        // include arr[idx] if divisible
        if (prev == -1 || arr[idx] % prev == 0) {
            temp.add(arr[idx]);                                  // Add the element to temp
            solve(idx + 1, arr, result, temp, arr[idx]);         // Recurse for the next element
            temp.remove(temp.size() - 1);                        // Backtrack, remove the element from temp
        }

        // skip arr[idx]
        solve(idx + 1, arr, result, temp, prev);                // Recurse for the next element without including arr[idx]
    }
    // Function to return the largest divisible subset
    public ArrayList<Integer> largestSubset(int[] arr) {
        Arrays.sort(arr);                                       // Sort the array to ensure lexicographical order
        ArrayList<Integer> result = new ArrayList<>();          // To store the largest subset
        ArrayList<Integer> temp   = new ArrayList<>();          // Temporary subset during recursion
        solve(0, arr, result, temp, -1);                        // Start the recursive function
        return result;                                          // Return the largest subset found
    }
    // Helper function to compare two lists lexicographically
    private boolean isLexGreater(ArrayList<Integer> a, ArrayList<Integer> b) {
        for (int i = 0; i < a.size(); i++) {
            if (a.get(i) > b.get(i)) {
                return true;
            }
            if (a.get(i) < b.get(i)) {
                return false;
            }
        }
        return false;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [1, 2, 4, 8]
 *
 * 1. Sort the array (although it's already sorted): [1, 2, 4, 8]
 * 2. Initial Call: solve(0, [1, 2, 4, 8], result = [], temp = [], prev = -1)
 *    - temp = []
 *    - prev = -1 (no previous element, so we can include 1)
 *    - Include 1 → temp = [1]
 *    - Call: solve(1, [1, 2, 4, 8], result = [], temp = [1], prev = 1)
 *
 * 3. solve(1, ...):
 *    - temp = [1], prev = 1 (2 % 1 == 0)
 *    - Include 2 → temp = [1, 2]
 *    - Call: solve(2, ..., temp = [1, 2], prev = 2)
 *
 * 4. solve(2, ...):
 *    - temp = [1, 2], prev = 2 (4 % 2 == 0)
 *    - Include 4 → temp = [1, 2, 4]
 *    - Call: solve(3, ..., temp = [1, 2, 4], prev = 4)
 *
 * 5. solve(3, ...):
 *    - temp = [1, 2, 4], prev = 4 (8 % 4 == 0)
 *    - Include 8 → temp = [1, 2, 4, 8]
 *    - Call: solve(4, ..., temp = [1, 2, 4, 8], prev = 8)
 *
 * 6. solve(4, ...):
 *    - idx = 4 (out of bounds). temp.size() = 4 > result.size() = 0
 *    - Update result = [1, 2, 4, 8]
 *    - Return and backtrack
 *
 * 7. Backtrack and skip options, but no larger subset found.
 *
 * Final Output: [1, 2, 4, 8]
 */

// Approach:
// - This solution uses dynamic programming (DP) with memoization to find the largest divisible subset from the given array.
// - At each index, we make two choices:
//   1) Include the current element in the subset if it is divisible by the previous element in the subset.
//   2) Skip the current element and move to the next index.
// - The `dp` table stores the best subset for every state `(idx, prev_idx)` where `idx` is the current element's index and `prev_idx` is the last included index.
// - The function is recursively called with two options (including or skipping the current element), and the larger subset (or lexicographically larger if sizes are the same) is stored in the memoization table.

// Time Complexity:
// - Sorting the array takes O(n log n). The recursion explores all possible subsets, and for each element, we either include it or skip it, leading to O(2^n) calls.
// - The total time complexity is O(n log n + 2^n) due to sorting and the recursive calls.

// Space Complexity:
// - The space complexity is O(n^2) because the memoization table `dp` has dimensions `n x (n + 1)`, and the recursion stack uses O(n) space.
class Solution {
    // Memoization table to store the best subsets for each state (idx, prev_idx + 1)
    private ArrayList<ArrayList<ArrayList<Integer> > > dp;

    // Helper function for recursion with memoization
    private ArrayList<Integer> solve(int idx, int[] arr, int prev_idx) {
        // Base case: if idx is out of bounds, return an empty list
        if (idx == arr.length) {
            return new ArrayList<>();
        }

        // If already computed, return the result from dp
        ArrayList<Integer> cached = dp.get(idx).get(prev_idx + 1);
        if (!cached.isEmpty()) {
            return new ArrayList<>(cached);
        }

        // Option 1: Take arr[idx] if divisible by arr[prev_idx]
        ArrayList<Integer> taken = new ArrayList<>();
        if (prev_idx == -1 || arr[idx] % arr[prev_idx] == 0) {
            ArrayList<Integer> nextTaken = solve(idx + 1, arr, idx);   // Recurse including current element
            taken = new ArrayList<>(nextTaken);                        // Clone to avoid mutation
            taken.add(0, arr[idx]);                                    // Prepend current element
        }

        // Option 2: Skip arr[idx]
        ArrayList<Integer> nextNotTake = solve(idx + 1, arr, prev_idx);
        ArrayList<Integer> not_take    = new ArrayList<>(nextNotTake); // Clone to avoid mutation

        // Compare and choose the larger or lexicographically greater subset
        ArrayList<Integer> result;
        if (not_take.size() > taken.size() ||
            (not_take.size() == taken.size() && lexCompare(not_take, taken) > 0)) {
            result = not_take;
        } else {
            result = taken;
        }

        // Memoize a clone of the result and return
        dp.get(idx).set(prev_idx + 1, new ArrayList<>(result));
        return result;
    }
    // Lexicographical comparison: returns >0 if a > b
    private int lexCompare(List<Integer> a, List<Integer> b) {
        for (int i = 0; i < a.size(); i++) {
            int cmp = Integer.compare(a.get(i), b.get(i));
            if (cmp != 0) {
                return cmp;
            }
        }
        return 0;
    }
    public ArrayList<Integer> largestSubset(int[] arr) {
        // Sort the array to ensure lexicographical order
        Arrays.sort(arr);
        int n = arr.length;

        // Initialize dp table of size n x (n+1)
        dp = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            ArrayList<ArrayList<Integer> > row = new ArrayList<>(n + 1);
            for (int j = 0; j <= n; j++) {
                row.add(new ArrayList<>());
            }
            dp.add(row);
        }

        // Start recursion with prev_idx = -1
        ArrayList<Integer> ans = solve(0, arr, -1);
        return ans;
    }
}
