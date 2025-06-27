/*
 * GfG Link: https://www.geeksforgeeks.org/problems/counting-elements-in-two-arrays/1
 *
 * Counting elements in two arrays
 *
 * Difficulty: Medium Accuracy: 37.12% Submissions: 81K+ Points: 4 Average Time: 20m
 *
 * You are given two unsorted arrays a[] and b[]. Both arrays may contain duplicate elements. For each element in a[], your task is to count how many elements in b[] are less than or equal to that element.
 *
 * Examples:
 *
 * Input: a[] = [4, 8, 7, 5, 1], b[] = [4, 48, 3, 0, 1, 1, 5]
 * Output: [5, 6, 6, 6, 3]
 * Explanation:
 * For a[0] = 4, there are 5 elements in b (4, 3, 0, 1, 1) that are ≤ 4.
 * For a[1] = 8 and a[2] = 7, there are 6 elements in b that are ≤ 8 and ≤ 7.
 * For a[3] = 5, there are 6 elements in b that are ≤ 5.
 * For a[4] = 1, there are 3 elements in b (0, 1, 1) that are ≤ 1.
 *
 * Input: a[] = [10, 20], b[] = [30, 40, 50]
 * Output: [0, 0]
 * Explanation:
 * For a[0] = 10 and a[1] = 20, there are no elements in b that are less than or equal to 10 or 20. Hence, the output is [0, 0].
 *
 * Constraints:
 * 1 ≤ a.size(), b.size() ≤ 10^5
 * 0 ≤ a[i], b[j] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: For each element in a, iterate through b and count elements ≤ a[i] using a nested loop.
// Time Complexity: O(n * m) where n = a.size() and m = b.size().
// Space Complexity: O(n) for the result array.
class Solution {
public:
    vector<int> countLessEq(vector<int>& a, vector<int>& b) {
        int n = a.size();                 // number of elements in a
        int m = b.size();                 // number of elements in b

        vector<int> result(n);            // answer array

        // For each element in a[], count how many in b[] are ≤ a[i]
        for (int i = 0; i < n; i++) {
            int count = 0;                // reset count for a[i]
            for (int j = 0; j < m; j++) {
                if (b[j] <= a[i]) {       // if b[j] is ≤ current a[i]
                    count++;              // increment count
                }
            }
            result[i] = count;            // store the count in result
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: Initialize result = [0,0,0,0,0]
 *
 * Step 3: i = 0, a[0] = 4
 *   count = 0
 *   j=0: b[0]=4 ≤4 → count=1
 *   j=1: b[1]=48>4 → count=1
 *   j=2: b[2]=3 ≤4 → count=2
 *   j=3: b[3]=0 ≤4 → count=3
 *   j=4: b[4]=1 ≤4 → count=4
 *   j=5: b[5]=1 ≤4 → count=5
 *   j=6: b[6]=5>4 → count=5
 *   result[0] = 5
 *
 * Step 4: i = 1, a[1] = 8
 *   count = 0
 *   j=0: b[0]=4 ≤8 → count=1
 *   j=1: b[1]=48>8 → count=1
 *   j=2: b[2]=3 ≤8 → count=2
 *   j=3: b[3]=0 ≤8 → count=3
 *   j=4: b[4]=1 ≤8 → count=4
 *   j=5: b[5]=1 ≤8 → count=5
 *   j=6: b[6]=5 ≤8 → count=6
 *   result[1] = 6
 *
 * Step 5: i = 2, a[2] = 7
 *   count = 0
 *   j iterations identical to i=1 except skip b[6]? No, b[6]=5 ≤7 → count=6
 *   result[2] = 6
 *
 * Step 6: i = 3, a[3] = 5
 *   count = 0
 *   j=0:4 ≤5→1; j=1:48>5; j=2:3≤5→2; j=3:0≤5→3; j=4:1≤5→4; j=5:1≤5→5; j=6:5≤5→6
 *   result[3] = 6
 *
 * Step 7: i = 4, a[4] = 1
 *   count = 0
 *   j=0:4>1; j=1:48>1; j=2:3>1; j=3:0≤1→1; j=4:1≤1→2; j=5:1≤1→3; j=6:5>1
 *   result[4] = 3
 *
 * Final result = [5, 6, 6, 6, 3]
 */

// Approach 2: Sort b, then for each element in a, perform binary search to find the first index where b[idx] > a[i]; that index equals the count of ≤ a[i].
// Time Complexity: O(m log m + n log m) where m = b.size() for sorting and n = a.size() for binary searches.
// Space Complexity: O(1) extra (excluding output vector).
class Solution {
public:
    // Custom binary search: returns the first index > x in sorted b[], which is the count of elements ≤ x
    int binarySearch(vector<int>& b, int x) {
        int low = 0, high = b.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // avoid overflow
            if (b[mid] <= x) {
                low = mid + 1;                // move right to find first > x
            }else {
                high = mid - 1;               // move left
            }
        }
        return low;                          // low is the count of elements ≤ x
    }

    vector<int> countLessEq(vector<int>& a, vector<int>& b) {
        int n = a.size();                   // number of elements in a
        int m = b.size();                   // number of elements in b

        vector<int> result(n);              // answer array

        sort(b.begin(), b.end());           // sort b for binary search

        // For each element in a[], count how many in b[] are ≤ a[i] via binarySearch
        for (int i = 0; i < n; i++) {
            result[i] = binarySearch(b, a[i]);
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: Sort b → b = [0,1,1,3,4,5,48]
 *
 * Step 3: i = 0, a[0] = 4
 *   binarySearch(b,4):
 *     low=0, high=6
 *     mid=3 → b[3]=3 ≤4 → low=4
 *     mid=(4+6)/2=5 → b[5]=5>4 → high=4
 *     mid=(4+4)/2=4 → b[4]=4 ≤4 → low=5
 *     loop ends (low=5, high=4) → return 5
 *   result[0]=5
 *
 * Step 4: i = 1, a[1] = 8
 *   binarySearch(b,8):
 *     low=0, high=6
 *     mid=3 → 3≤8 → low=4
 *     mid=5 → 5≤8 → low=6
 *     mid=6 → 48>8 → high=5
 *     loop ends (low=6, high=5) → return 6
 *   result[1]=6
 *
 * Step 5: i = 2, a[2] = 7
 *   binarySearch(b,7) → same as x=8 until mid=5 (5≤7 → low=6), then high=5 → return 6
 *   result[2]=6
 *
 * Step 6: i = 3, a[3] = 5
 *   binarySearch(b,5):
 *     low=0, high=6
 *     mid=3 → 3≤5 → low=4
 *     mid=5 → 5≤5 → low=6
 *     mid=6 → 48>5 → high=5
 *     loop ends → return 6
 *   result[3]=6
 *
 * Step 7: i = 4, a[4] = 1
 *   binarySearch(b,1):
 *     low=0, high=6
 *     mid=3 → 3>1 → high=2
 *     mid=1 → 1≤1 → low=2
 *     mid=2 → 1≤1 → low=3
 *     loop ends (low=3, high=2) → return 3
 *   result[4]=3
 *
 * Final result = [5, 6, 6, 6, 3]
 */

// Approach 3: Sort array b, then for each element in a use std::upper_bound to get the first position > a[i], whose index equals the count of elements ≤ a[i].
// Time Complexity: O(m log m + n log m) where m = b.size() for sorting and n = a.size() for n binary searches.
// Space Complexity: O(1) extra space (ignoring the output vector).
class Solution {
public:
    vector<int> countLessEq(vector<int>& a, vector<int>& b) {
        int n = a.size();                 // number of elements in a
        int m = b.size();                 // number of elements in b

        vector<int> result(n);            // answer array

        sort(b.begin(), b.end());         // sort b to enable binary search

        // For each a[i], upper_bound returns iterator to first element > a[i]
        // distance from b.begin() gives count of elements ≤ a[i]
        for (int i = 0; i < n; i++) {
            result[i] = upper_bound(b.begin(), b.end(), a[i]) - b.begin();
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: sort b → [0, 1, 1, 3, 4, 5, 48]
 *
 * Step 3: Compute result:
 *   i = 0, a[0] = 4
 *     upper_bound(..., 4) points to element 5 at index 5 → result[0] = 5
 *   i = 1, a[1] = 8
 *     upper_bound(..., 8) points to element 48 at index 6 → result[1] = 6
 *   i = 2, a[2] = 7
 *     upper_bound(..., 7) also points to 48 at index 6 → result[2] = 6
 *   i = 3, a[3] = 5
 *     upper_bound(..., 5) points to 48 at index 6 → result[3] = 6
 *   i = 4, a[4] = 1
 *     upper_bound(..., 1) points to element 3 at index 3 → result[4] = 3
 *
 * Final result = [5, 6, 6, 6, 3]
 */

// Approach 4: Use a fixed-size frequency array for b (range 0–100000), build its prefix sums, then for each element in a look up the count in O(1).
// Time Complexity: O(m + U + n) where m = b.size(), U = 100001 (constant), and n = a.size().
// Space Complexity: O(U) for the frequency/prefix array.
class Solution {
public:
    vector<int> countLessEq(vector<int>& a, vector<int>& b) {
        int n = a.size();                         // number of elements in a
        int m = b.size();                         // number of elements in b

        vector<int> result(n);                    // answer array
        vector<int> freq(100001, 0);              // freq[i] = count of i in b

        // fill frequency array
        for (int i = 0; i < m; i++) {
            freq[b[i]]++;                         // increment count of value b[i]
        }

        // compute prefix sums so freq[i] = count of elements ≤ i
        for (int i = 1; i < 100001; i++) {
            freq[i] += freq[i - 1];
        }

        // for each element in a, lookup count in freq[]
        for (int i = 0; i < n; i++) {
            result[i] = freq[a[i]];
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: Initialize freq[0..100000] all to 0
 *
 * Step 3: Fill freq from b:
 *   b values → increment:
 *   freq[4] = 1, freq[48] = 1, freq[3] = 1, freq[0] = 1, freq[1] = 2 (two 1's), freq[5] = 1
 *
 * Step 4: Prefix sum up to relevant range:
 *   freq[0] = 1
 *   freq[1] = 1+2 = 3
 *   freq[2] = 3+0 = 3
 *   freq[3] = 3+1 = 4
 *   freq[4] = 4+1 = 5
 *   freq[5] = 5+1 = 6
 *   ...
 *   freq[7] = 6
 *   freq[8] = 6
 *   freq[48] accumulates to 7 but values >8 are irrelevant for a
 *
 * Step 5: Build result:
 *   a[0]=4 → result[0] = freq[4] = 5
 *   a[1]=8 → result[1] = freq[8] = 6
 *   a[2]=7 → result[2] = freq[7] = 6
 *   a[3]=5 → result[3] = freq[5] = 6
 *   a[4]=1 → result[4] = freq[1] = 3
 *
 * Output: [5, 6, 6, 6, 3]
 */

// Approach 5: Build a frequency array of b up to the maximum of a, compute its prefix sums, then for each element in a, look up the count in O(1).
// Time Complexity: O(n + m + maxA) where n = a.size(), m = b.size(), and maxA = max(a).
// Space Complexity: O(maxA) for the frequency/prefix array.
class Solution {
public:
    vector<int> countLessEq(vector<int>& a, vector<int>& b) {
        int         n = a.size();                    // number of elements in a
        int         m = b.size();                    // number of elements in b
        vector<int> result(n);                       // answer array

        int maxA = *max_element(a.begin(), a.end()); // find the maximum value in a

        vector<int> freq(maxA + 1, 0);               // freq[i] = count of i in b (if i <= maxA)

        // Build frequency array for b[]
        for (int i = 0; i < m; i++) {
            if (b[i] <= maxA) {
                freq[b[i]]++;                     // increment count of b[i]
            }
        }

        // Convert freq[] into prefix sum array so freq[i] = count of elements ≤ i
        for (int i = 1; i <= maxA; i++) {
            freq[i] += freq[i - 1];
        }

        // For each element in a, the answer is freq[a[i]] (number of b elements ≤ a[i])
        for (int i = 0; i < n; i++) {
            result[i] = freq[a[i]];
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: maxA = 8 (maximum of a[])
 * Step 3: Initialize freq[0..8] = {0,0,0,0,0,0,0,0,0}
 *
 * Step 4: Build freq from b:
 *   i=0: b[0]=4 ≤8 → freq[4]++ → freq = {0,0,0,0,1,0,0,0,0}
 *   i=1: b[1]=48>8 → skip
 *   i=2: b[2]=3 ≤8 → freq[3]++ → freq = {0,0,0,1,1,0,0,0,0}
 *   i=3: b[3]=0 ≤8 → freq[0]++ → freq = {1,0,0,1,1,0,0,0,0}
 *   i=4: b[4]=1 ≤8 → freq[1]++ → freq = {1,1,0,1,1,0,0,0,0}
 *   i=5: b[5]=1 ≤8 → freq[1]++ → freq = {1,2,0,1,1,0,0,0,0}
 *   i=6: b[6]=5 ≤8 → freq[5]++ → freq = {1,2,0,1,1,1,0,0,0}
 *
 * Step 5: Prefix sum over freq:
 *   i=1: freq[1]+=freq[0] → 2+1=3 → freq[1]=3
 *   i=2: freq[2]+=freq[1] → 0+3=3 → freq[2]=3
 *   i=3: freq[3]+=freq[2] → 1+3=4 → freq[3]=4
 *   i=4: freq[4]+=freq[3] → 1+4=5 → freq[4]=5
 *   i=5: freq[5]+=freq[4] → 1+5=6 → freq[5]=6
 *   i=6: freq[6]+=freq[5] → 0+6=6 → freq[6]=6
 *   i=7: freq[7]+=freq[6] → 0+6=6 → freq[7]=6
 *   i=8: freq[8]+=freq[7] → 0+6=6 → freq[8]=6
 *   Final freq = {1,3,3,4,5,6,6,6,6}
 *
 * Step 6: Build result for each a[i]:
 *   a[0]=4 → result[0]=freq[4]=5
 *   a[1]=8 → result[1]=freq[8]=6
 *   a[2]=7 → result[2]=freq[7]=6
 *   a[3]=5 → result[3]=freq[5]=6
 *   a[4]=1 → result[4]=freq[1]=3
 *
 * Output: [5, 6, 6, 6, 3]
 */

/************************************************************ JAVA ************************************************/

// Approach 1: For each element in a, iterate through b and count elements ≤ a[i] using a nested loop.
// Time Complexity: O(n * m) where n = a.length and m = b.length.
// Space Complexity: O(n) for the result list.
class Solution {
    public static ArrayList<Integer> countLessEq(int a[], int b[]) {
        int n = a.length;                              // number of elements in a
        int m = b.length;                              // number of elements in b
        ArrayList<Integer> result = new ArrayList<>(); // answer list

        // For each element in a[], count how many in b[] are ≤ a[i]
        for (int i = 0; i < n; i++) {
            int count = 0;                        // reset count for a[i]
            for (int j = 0; j < m; j++) {
                if (b[j] <= a[i]) {               // if b[j] is ≤ current a[i]
                    count++;                      // increment count
                }
            }
            result.add(count);                    // add the count to result
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: Initialize result = []
 *
 * Step 3: i = 0, a[0] = 4
 *   count = 0
 *   j=0: b[0]=4 ≤4 → count=1
 *   j=1: b[1]=48>4 → count=1
 *   j=2: b[2]=3 ≤4 → count=2
 *   j=3: b[3]=0 ≤4 → count=3
 *   j=4: b[4]=1 ≤4 → count=4
 *   j=5: b[5]=1 ≤4 → count=5
 *   j=6: b[6]=5>4 → count=5
 *   result = [5]
 *
 * Step 4: i = 1, a[1] = 8
 *   count = 0
 *   j=0:4 ≤8→1; j=1:48>8; j=2:3≤8→2; j=3:0≤8→3; j=4:1≤8→4; j=5:1≤8→5; j=6:5≤8→6
 *   result = [5, 6]
 *
 * Step 5: i = 2, a[2] = 7
 *   count = 0
 *   same j-loop logic → count = 6
 *   result = [5, 6, 6]
 *
 * Step 6: i = 3, a[3] = 5
 *   count = 0
 *   j=0:4≤5→1; j=1:48>5; j=2:3≤5→2; j=3:0≤5→3; j=4:1≤5→4; j=5:1≤5→5; j=6:5≤5→6
 *   result = [5, 6, 6, 6]
 *
 * Step 7: i = 4, a[4] = 1
 *   count = 0
 *   j=0:4>1; j=1:48>1; j=2:3>1; j=3:0≤1→1; j=4:1≤1→2; j=5:1≤1→3; j=6:5>1
 *   result = [5, 6, 6, 6, 3]
 *
 * Final result = [5, 6, 6, 6, 3]
 */

// Approach 2: Sort b, then for each element in a, perform binary search to find the first index where b[idx] > a[i]; that index equals the count of ≤ a[i].
// Time Complexity: O(m log m + n log m) where m = b.length for sorting and n = a.length for binary searches.
// Space Complexity: O(1) extra (excluding output list).
class Solution {
    // Custom binary search: returns the first index > x in sorted b[], which is the count of elements ≤ x
    public static int binarySearch(int[] b, int x) {
        int low = 0, high = b.length - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;  // avoid overflow
            if (b[mid] <= x) {
                low = mid + 1;                 // move right to find first > x
            }else {
                high = mid - 1;                // move left
            }
        }
        return low;                           // low is the count of elements ≤ x
    }

    public static ArrayList<Integer> countLessEq(int[] a, int[] b) {
        int n = a.length;                              // number of elements in a
        int m = b.length;                              // number of elements in b
        ArrayList<Integer> result = new ArrayList<>(); // answer list

        Arrays.sort(b);                                // sort b for binary search

        // For each element in a[], count how many in b[] are ≤ a[i] via binarySearch
        for (int i = 0; i < n; i++) {
            result.add(binarySearch(b, a[i]));
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: Sort b → b = [0,1,1,3,4,5,48]
 *
 * Step 3: i = 0, a[0] = 4
 *   binarySearch(b,4):
 *     low=0, high=6
 *     mid=3 → b[3]=3 ≤4 → low=4
 *     mid=5 → b[5]=5>4 → high=4
 *     mid=4 → b[4]=4 ≤4 → low=5
 *     loop ends → return 5
 *   result = [5]
 *
 * Step 4: i = 1, a[1] = 8
 *   binarySearch(b,8) → final low=6 → return 6
 *   result = [5, 6]
 *
 * Step 5: i = 2, a[2] = 7
 *   binarySearch(b,7) → return 6
 *   result = [5, 6, 6]
 *
 * Step 6: i = 3, a[3] = 5
 *   binarySearch(b,5) → return 6
 *   result = [5, 6, 6, 6]
 *
 * Step 7: i = 4, a[4] = 1
 *   binarySearch(b,1):
 *     low=0, high=6
 *     mid=3 → 3>1 → high=2
 *     mid=1 → 1≤1 → low=2
 *     mid=2 → 1≤1 → low=3
 *     loop ends → return 3
 *   result = [5, 6, 6, 6, 3]
 *
 * Final result = [5, 6, 6, 6, 3]
 */

// Approach 4: Use a fixed-size frequency array for b (range 0–100000), build its prefix sums, then for each element in a look up the count in O(1).
// Time Complexity: O(m + U + n) where m = b.length, U = 100001 (constant), and n = a.length.
// Space Complexity: O(U) for the frequency/prefix array.
class Solution {
    public static ArrayList<Integer> countLessEq(int a[], int b[]) {
        int n = a.length;                              // number of elements in a
        int m = b.length;                              // number of elements in b

        ArrayList<Integer> result = new ArrayList<>(); // answer list
        int[] freq = new int[100001];                  // freq[i] = count of i in b

        // fill frequency array
        for (int i = 0; i < m; i++) {
            freq[b[i]]++;                         // increment count of value b[i]
        }

        // compute prefix sums so freq[i] = count of elements ≤ i
        for (int i = 1; i < freq.length; i++) {
            freq[i] += freq[i - 1];
        }

        // for each element in a, lookup count in freq[]
        for (int i = 0; i < n; i++) {
            result.add(freq[a[i]]);
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: Initialize freq[0..100000] all to 0
 *
 * Step 3: Fill freq from b:
 *   freq[4]=1, freq[48]=1, freq[3]=1, freq[0]=1, freq[1]=2, freq[5]=1
 *
 * Step 4: Prefix sum:
 *   freq[0]=1
 *   freq[1]=1+2=3
 *   freq[2]=3
 *   freq[3]=3+1=4
 *   freq[4]=4+1=5
 *   freq[5]=5+1=6
 *   ...
 *   freq[7]=6, freq[8]=6
 *
 * Step 5: Build result:
 *   result = [freq[4], freq[8], freq[7], freq[5], freq[1]]
 *          = [5, 6, 6, 6, 3]
 *
 * Output: [5, 6, 6, 6, 3]
 */

// Approach 5: Build a frequency array of b up to the maximum of a, compute its prefix sums, then for each element in a, look up the count in O(1).
// Time Complexity: O(n + m + maxA) where n = a.length, m = b.length, and maxA = max(a).
// Space Complexity: O(maxA) for the frequency/prefix array.
class Solution {
    public static ArrayList<Integer> countLessEq(int a[], int b[]) {
        int n = a.length;                              // number of elements in a
        int m = b.length;                              // number of elements in b
        ArrayList<Integer> result = new ArrayList<>(); // answer list

        int maxA = 0;

        for (int val : a) {
            if (val > maxA) {
                maxA = val;                          // find the maximum value in a
            }
        }

        int[] freq = new int[maxA + 1];              // freq[i] = count of i in b (if i <= maxA)

        // Build frequency array for b[]
        for (int i = 0; i < m; i++) {
            if (b[i] <= maxA) {
                freq[b[i]]++;                        // increment count of b[i]
            }
        }

        // Convert freq[] into prefix sum array so freq[i] = count of elements ≤ i
        for (int i = 1; i <= maxA; i++) {
            freq[i] += freq[i - 1];
        }

        // For each element in a, the answer is freq[a[i]] (number of b elements ≤ a[i])
        for (int i = 0; i < n; i++) {
            result.add(freq[a[i]]);
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example:
 *   a = [4, 8, 7, 5, 1]
 *   b = [4, 48, 3, 0, 1, 1, 5]
 *
 * Step 1: n = 5, m = 7
 * Step 2: maxA = 8 (maximum of a[])
 * Step 3: Initialize freq[0..8] = {0,0,0,0,0,0,0,0,0}
 *
 * Step 4: Build freq from b:
 *   i=0: b[0]=4 ≤8 → freq[4]++ → freq = {0,0,0,0,1,0,0,0,0}
 *   i=1: b[1]=48>8 → skip
 *   i=2: b[2]=3 ≤8 → freq[3]++ → freq = {0,0,0,1,1,0,0,0,0}
 *   i=3: b[3]=0 ≤8 → freq[0]++ → freq = {1,0,0,1,1,0,0,0,0}
 *   i=4: b[4]=1 ≤8 → freq[1]++ → freq = {1,1,0,1,1,0,0,0,0}
 *   i=5: b[5]=1 ≤8 → freq[1]++ → freq = {1,2,0,1,1,0,0,0,0}
 *   i=6: b[6]=5 ≤8 → freq[5]++ → freq = {1,2,0,1,1,1,0,0,0}
 *
 * Step 5: Prefix sum over freq:
 *   i=1: freq[1]+=freq[0] → 2+1=3 → freq[1]=3
 *   i=2: freq[2]+=freq[1] → 0+3=3 → freq[2]=3
 *   i=3: freq[3]+=freq[2] → 1+3=4 → freq[3]=4
 *   i=4: freq[4]+=freq[3] → 1+4=5 → freq[4]=5
 *   i=5: freq[5]+=freq[4] → 1+5=6 → freq[5]=6
 *   i=6: freq[6]+=freq[5] → 0+6=6 → freq[6]=6
 *   i=7: freq[7]+=freq[6] → 0+6=6 → freq[7]=6
 *   i=8: freq[8]+=freq[7] → 0+6=6 → freq[8]=6
 *   Final freq = {1,3,3,4,5,6,6,6,6}
 *
 * Step 6: Build result for each a[i]:
 *   a[0]=4 → result[0]=freq[4]=5
 *   a[1]=8 → result[1]=freq[8]=6
 *   a[2]=7 → result[2]=freq[7]=6
 *   a[3]=5 → result[3]=freq[5]=6
 *   a[4]=1 → result[4]=freq[1]=3
 *
 * Output: [5, 6, 6, 6, 3]
 */
