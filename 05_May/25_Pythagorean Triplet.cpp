/*
 * GfG Link: https://www.geeksforgeeks.org/problems/pythagorean-triplet3018/1
 *
 * Pythagorean Triplet
 *
 * Difficulty: Medium Accuracy: 24.77% Submissions: 227K+ Points: 4 Average Time: 20m
 *
 * Given an array arr[], return true if there is a triplet (a, b, c) from the array (where a, b, and c are on different indexes) that satisfies a2 + b2 = c2, otherwise return false.
 *
 * Examples:
 *
 * Input: arr[] = [3, 2, 4, 6, 5]
 * Output: true
 * Explanation: a=3, b=4, and c=5 forms a pythagorean triplet.
 *
 * Input: arr[] = [3, 8, 5]
 * Output: false
 * Explanation: No such triplet possible.
 *
 * Input: arr[] = [1, 1, 1]
 * Output: false
 *
 * Constraints:
 * 1 <= arr.size() <= 10^5
 * 1 <= arr[i] <= 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute force using three nested loops to check all triplets if a^2 + b^2 == c^2
// Time Complexity: O(n^3) - Three nested loops to check all triplets.
// Space Complexity: O(1) - No extra space used.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            int a = arr[i];         // First element
            for (int j = i + 1; j < n; j++) {
                int b = arr[j];     // Second element
                for (int k = j + 1; k < n; k++) {
                    int c = arr[k]; // Third element

                    int a2 = a * a; // Square of a
                    int b2 = b * b; // Square of b
                    int c2 = c * c; // Square of c

                    // Check if any combination satisfies the Pythagorean triplet condition
                    if (a2 + b2 == c2 || b2 + c2 == a2 || a2 + c2 == b2) {
                        return true;
                    }
                }
            }
        }
        return false; // If no triplet found
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Triplets tried (a, b, c):
 *(3, 1, 4) => 9 + 1 != 16
 *(3, 1, 6) => 9 + 1 != 36
 *(3, 1, 5) => 9 + 1 != 25
 *(3, 4, 6) => 9 + 16 != 36
 *(3, 4, 5) => 9 + 16 == 25 => Found! Return true
 *
 */

// Approach 2: Square all elements and sort. Then fix one as hypotenuse and use two pointers to find if a^2 + b^2 = c^2.
// Time Complexity: O(n^2) - One loop for each element and two-pointer traversal.
// Space Complexity: O(1) - No extra space used apart from in-place modifications.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            arr[i] = arr[i] * arr[i]; // Square each element
        }

        sort(begin(arr), end(arr));  // Sort the squared array

        // Fix one element (as hypotenuse) and use two pointers to find other two
        for (int i = n - 1; i >= 2; i--) {
            int target = arr[i]; // Hypotenuse

            int l = 0;
            int r = i - 1;

            while (l < r) {
                int sum = arr[l] + arr[r]; // Sum of two smaller squares

                if (sum == target) {
                    return true; // Found a valid triplet
                }

                (sum < target) ? l++ : r--; // Move pointers accordingly
            }
        }

        return false; // No triplet found
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * After squaring: [9, 1, 16, 36, 25]
 * After sorting: [1, 9, 16, 25, 36]
 * Fix 36 as hypotenuse
 * Check 1 + 25 = 26, move left pointer
 * Check 9 + 25 = 34, move left pointer
 * Check 16 + 25 = 41, move right pointer
 * Now fix 25 as hypotenuse
 * Check 1 + 16 = 17, move left pointer
 * Check 9 + 16 = 25 => Found! Return true
 *
 */

// Approach 3: Use a set for O(1) lookups. For each pair (a, b), check if sqrt(a^2 + b^2) exists in the set.
// Time Complexity: O(n^2) - Checking every unique pair of elements.
// Space Complexity: O(n) - Set used to store all array elements.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        // Insert all elements into a set for O(1) lookup
        unordered_set<int> st(arr.begin(), arr.end());

        // Check every pair (a, b) to see if there's a c such that c^2 = a^2 + b^2
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int a = arr[i];
                int b = arr[j];

                // Calculate potential value of c using Pythagoras theorem
                int c = sqrt(a * a + b * b);

                // If c is an integer and exists in the set, return true
                if (c * c == a * a + b * b && st.count(c)) {
                    return true;
                }
            }
        }

        // No valid Pythagorean triplet found
        return false;
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Set: {1, 3, 4, 5, 6}
 * Check pair (3, 1) → c = sqrt(10) → not integer
 * Check pair (3, 4) → c = sqrt(25) = 5 → 5 in set → Found! Return true
 *
 */

// Approach 4: Use a boolean presence array to quickly check existence of a, b, and c while trying all possible (a, b) pairs.
// Time Complexity: O(maxEl^2) - We iterate over all pairs (a, b) from 1 to maxElement.
// Space Complexity: O(maxEl) - For the visited boolean array.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        // Step 1: Find the maximum element in the array
        int maxEl = 0;

        for (int i = 0; i < n; i++) {
            maxEl = max(maxEl, arr[i]);
        }
        // Alternate (cleaner) way: int maxEl = *max_element(arr.begin(), arr.end());

        // Step 2: Create a boolean array to mark presence of each number
        vector<bool> visited(maxEl + 1, false);
        for (int i = 0; i < n; i++) {
            visited[arr[i]] = true;
        }

        // Step 3: Try all possible combinations of a and b
        for (int a = 1; a <= maxEl; a++) {
            // Skip if 'a' is not present in original array
            if (!visited[a]) {
                continue;
            }

            for (int b = 1; b <= maxEl; b++) {
                // Skip if 'b' is not present
                if (!visited[b]) {
                    continue;
                }

                // Calculate c using Pythagoras theorem
                int c = sqrt(a * a + b * b);

                // Skip if c^2 is not a perfect square or c is out of bounds
                if (c * c != a * a + b * b || c > maxEl) {
                    continue;
                }

                // If c exists in the array, we found a Pythagorean triplet
                if (visited[c]) {
                    return true;
                }
            }
        }

        // No triplet found
        return false;
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * maxEl = 6
 * visited[] = [false, true, false, true, true, true, true]
 * Try a = 3, b = 4 => c = sqrt(9 + 16) = sqrt(25) = 5 => 5 is present → Found! Return true
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute force using three nested loops to check all triplets if a^2 + b^2 == c^2
// Time Complexity: O(n^3) - Three nested loops to check all triplets.
// Space Complexity: O(1) - No extra space used.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            int a = arr[i];         // First element
            for (int j = i + 1; j < n; j++) {
                int b = arr[j];     // Second element
                for (int k = j + 1; k < n; k++) {
                    int c = arr[k]; // Third element

                    int a2 = a * a; // Square of a
                    int b2 = b * b; // Square of b
                    int c2 = c * c; // Square of c

                    // Check if any combination satisfies the Pythagorean triplet condition
                    if (a2 + b2 == c2 || b2 + c2 == a2 || a2 + c2 == b2) {
                        return true;
                    }
                }
            }
        }
        return false; // If no triplet found
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Triplets tried (a, b, c):
 *(3, 1, 4) => 9 + 1 != 16
 *(3, 1, 6) => 9 + 1 != 36
 *(3, 1, 5) => 9 + 1 != 25
 *(3, 4, 6) => 9 + 16 != 36
 *(3, 4, 5) => 9 + 16 == 25 => Found! Return true
 *
 */

// Approach 2: Square all elements and sort. Then fix one as hypotenuse and use two pointers to find if a^2 + b^2 = c^2.
// Time Complexity: O(n^2) - One loop for each element and two-pointer traversal.
// Space Complexity: O(1) - No extra space used apart from in-place modifications.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            arr[i] = arr[i] * arr[i]; // Square each element
        }

        Arrays.sort(arr); // Sort the squared array

        // Fix one element (as hypotenuse) and use two pointers
        for (int i = n - 1; i >= 2; i--) {
            int target = arr[i]; // Hypotenuse

            int l = 0;
            int r = i - 1;

            while (l < r) {
                int sum = arr[l] + arr[r]; // Sum of two smaller squares

                if (sum == target) {
                    return true; // Found a valid triplet
                }

                if (sum < target) {
                    l++; // Increase left pointer
                } else {
                    r--; // Decrease right pointer
                }
            }
        }

        return false; // No triplet found
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * After squaring: [9, 1, 16, 36, 25]
 * After sorting: [1, 9, 16, 25, 36]
 * Fix 36 as hypotenuse
 * Check 1 + 25 = 26, move left pointer
 * Check 9 + 25 = 34, move left pointer
 * Check 16 + 25 = 41, move right pointer
 * Now fix 25 as hypotenuse
 * Check 1 + 16 = 17, move left pointer
 * Check 9 + 16 = 25 => Found! Return true
 *
 */

// Approach 3: Use a set for O(1) lookups. For each pair (a, b), check if sqrt(a^2 + b^2) exists in the set.
// Time Complexity: O(n^2) - Checking every unique pair of elements.
// Space Complexity: O(n) - Set used to store all array elements.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        // Insert all elements into a set for O(1) lookup
        Set<Integer> set = new HashSet<>();

        for (int num : arr) {
            set.add(num);
        }

        // Check every pair (a, b)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int a = arr[i];
                int b = arr[j];

                // Calculate potential c
                int c = (int)Math.sqrt(a * a + b * b);

                // If c is integer and exists in set, return true
                if (c * c == a * a + b * b && set.contains(c)) {
                    return true;
                }
            }
        }

        // No valid triplet found
        return false;
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Set: {1, 3, 4, 5, 6}
 * Check pair (3, 1) → c = sqrt(10) → not integer
 * Check pair (3, 4) → c = sqrt(25) = 5 → 5 in set → Found! Return true
 *
 */

// Approach 4: Use a boolean presence array to quickly check existence of a, b, and c while trying all possible (a, b) pairs.
// Time Complexity: O(maxEl^2) - We iterate over all pairs (a, b) from 1 to maxElement.
// Space Complexity: O(maxEl) - For the visited boolean array.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        // Step 1: Find maximum element in array
        int maxEl = 0;

        for (int i = 0; i < n; i++) {
            maxEl = Math.max(maxEl, arr[i]);
        }

        // Step 2: Create a boolean array for presence check
        boolean[] visited = new boolean[maxEl + 1];
        for (int i = 0; i < n; i++) {
            visited[arr[i]] = true;
        }

        // Step 3: Try all combinations of a and b
        for (int a = 1; a <= maxEl; a++) {
            if (!visited[a]) {
                continue;
            }

            for (int b = 1; b <= maxEl; b++) {
                if (!visited[b]) {
                    continue;
                }

                int c = (int)Math.sqrt(a * a + b * b);

                if (c * c != a * a + b * b || c > maxEl) {
                    continue;
                }

                if (visited[c]) {
                    return true;
                }
            }
        }

        return false; // No triplet found
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * maxEl = 6
 * visited[] = [false, true, false, true, true, true, true]
 * Try a = 3, b = 4 => c = sqrt(25) = 5 → 5 is present → Found! Return true
 *
 */
