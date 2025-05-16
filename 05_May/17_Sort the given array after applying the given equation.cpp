/*
 * GfG Link: https://www.geeksforgeeks.org/problems/sort-the-given-array-after-applying-the-given-equation0304/1
 *
 * Sort the given array after applying the given equation
 *
 * Difficulty: Medium Accuracy: 33.58% Submissions: 12K+ Points: 4
 *
 * Given an integer array arr[] sorted in ascending order, along with three integers: A, B, and C. The task is to transform each element x in the array using the quadratic function A*(x2) + B*x + C. After applying this transformation to every element, return the modified array in sorted order.
 *
 * Examples:
 *
 * Input: arr[] = [-4, -2, 0, 2, 4], A = 1, B = 3, C = 5
 * Output: [3, 5, 9, 15, 33]
 * Explanation: After applying f(x) = 1*(x2)+ 3*x + 5 to each x, we get [9, 3, 5, 15, 33]. After sorting this array, the array becomes [3, 5, 9, 15, 33].
 *
 * Input: arr[] = [-3, -1, 2, 4], A = -1, B = 0, C = 0
 * Output: [-16, -9, -4, -1]
 * Explanation: After applying f(x) = -1*(x2) + 0*x + 0 to each x, we get [ -9, -1, -4, -16 ]. After sorting this array, the array becomes  [-16, -9, -4, -1].
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * -10^3 ≤ arr[i], A, B, C ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1: Apply the quadratic function A*x^2 + B*x + C to each element, store in a new array, and sort it.
// Time Complexity: O(N log N), where N is the size of the array due to the sorting step.
// Space Complexity: O(N), for storing the transformed array.
class Solution {
public:
    vector<int> sortArray(vector<int>& arr, int A, int B, int C) {
        vector<int> result;

        // Traverse each element in the input array
        for (int& x : arr) {
            // Apply the quadratic equation: A*x^2 + B*x + C
            int ans = A * x * x + B * x + C;
            result.push_back(ans); // Store the result in the new array
        }

        // Sort the transformed array
        sort(result.begin(), result.end());

        return result; // Return the sorted transformed array
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [-4, -2, 0, 2, 4], A = 1, B = 3, C = 5
 *
 * Step 1: Apply the equation f(x) = x^2 + 3x + 5
 *   x = -4 => 1*(-4)^2 + 3*(-4) + 5 = 16 - 12 + 5 = 9
 *   x = -2 => 1*(-2)^2 + 3*(-2) + 5 = 4 - 6 + 5 = 3
 *   x =  0 => 1*(0)^2 + 3*(0) + 5 = 0 + 0 + 5 = 5
 *   x =  2 => 1*(2)^2 + 3*(2) + 5 = 4 + 6 + 5 = 15
 *   x =  4 => 1*(4)^2 + 3*(4) + 5 = 16 + 12 + 5 = 33
 *
 * Step 2: Transformed array = [9, 3, 5, 15, 33]
 * Step 3: Sort the array => [3, 5, 9, 15, 33]
 *
 * Output: [3, 5, 9, 15, 33]
 *
 */

// Approach 2: Use a two-pointer approach to fill the result array from either end based on the parabola direction (upward/downward) determined by A.
// Time Complexity: O(N), since we traverse the array once using two pointers.
// Space Complexity: O(N), for storing the transformed and sorted result array.
class Solution {
public:

    // Evaluate the quadratic function for a given x
    int evaluate(int x, int A, int B, int C) {
        return A * x * x + B * x + C;
    }
    vector<int> sortArray(vector<int>& arr, int A, int B, int C) {
        int         n = arr.size();
        vector<int> result(n, 0); // Result array of the same size

        int l = 0;                // Left pointer
        int r = n - 1;            // Right pointer

        // Set index based on direction of parabola
        int idx = (A >= 0) ? n - 1 : 0;

        // Two-pointer approach to fill result array from correct end
        while (l <= r) {
            int leftVal  = evaluate(arr[l], A, B, C); // f(arr[l])
            int rightVal = evaluate(arr[r], A, B, C); // f(arr[r])

            if (A >= 0) {                             // Parabola opens upwards; fill from end
                if (leftVal > rightVal) {
                    result[idx--] = leftVal;
                    l++;
                } else {
                    result[idx--] = rightVal;
                    r--;
                }
            } else { // Parabola opens downwards; fill from start
                if (leftVal < rightVal) {
                    result[idx++] = leftVal;
                    l++;
                } else {
                    result[idx++] = rightVal;
                    r--;
                }
            }
        }

        return result; // Return the sorted transformed array
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [-4, -2, 0, 2, 4], A = 1, B = 3, C = 5
 * Function: f(x) = 1*x^2 + 3*x + 5
 *
 * Initial: l = 0, r = 4, idx = 4 (since A >= 0)
 *
 * Step 1:
 *   leftVal = f(-4) = 16 -12 + 5 = 9
 *   rightVal = f(4) = 16 +12 + 5 = 33
 *   -> rightVal > leftVal → result[4] = 33, r--
 *
 * Step 2:
 *   leftVal = f(-4) = 9
 *   rightVal = f(2) = 4 + 6 + 5 = 15
 *   -> rightVal > leftVal → result[3] = 15, r--
 *
 * Step 3:
 *   leftVal = f(-4) = 9
 *   rightVal = f(0) = 0 + 0 + 5 = 5
 *   -> leftVal > rightVal → result[2] = 9, l++
 *
 * Step 4:
 *   leftVal = f(-2) = 4 -6 + 5 = 3
 *   rightVal = f(0) = 5
 *   -> rightVal > leftVal → result[1] = 5, r--
 *
 * Step 5:
 *   leftVal = f(-2) = 3
 *   rightVal = f(-2) = 3
 *   -> rightVal >= leftVal → result[0] = 3, r--
 *
 * Final result: [3, 5, 9, 15, 33]
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Apply the quadratic function A*x^2 + B*x + C to each element, store in a new ArrayList, and sort it.
// Time Complexity: O(N log N), where N is the size of the array due to sorting.
// Space Complexity: O(N), for storing the transformed elements in a new list.
class Solution {
    public ArrayList<Integer> sortArray(int[] arr, int A, int B, int C) {
        ArrayList<Integer> result = new ArrayList<>();

        // Traverse each element in the input array
        for (int x : arr) {
            // Apply the quadratic function: A*x^2 + B*x + C
            int ans = A * x * x + B * x + C;
            result.add(ans); // Store the result in the list
        }

        // Sort the transformed list
        Collections.sort(result);

        return result; // Return the sorted list
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [-4, -2, 0, 2, 4], A = 1, B = 3, C = 5
 *
 * Step 1: Apply the equation f(x) = x^2 + 3x + 5
 *   x = -4 => 1*(-4)^2 + 3*(-4) + 5 = 16 - 12 + 5 = 9
 *   x = -2 => 1*(-2)^2 + 3*(-2) + 5 = 4 - 6 + 5 = 3
 *   x =  0 => 1*(0)^2 + 3*(0) + 5 = 0 + 0 + 5 = 5
 *   x =  2 => 1*(2)^2 + 3*(2) + 5 = 4 + 6 + 5 = 15
 *   x =  4 => 1*(4)^2 + 3*(4) + 5 = 16 + 12 + 5 = 33
 *
 * Step 2: Transformed list = [9, 3, 5, 15, 33]
 * Step 3: Sort the list => [3, 5, 9, 15, 33]
 *
 * Output: [3, 5, 9, 15, 33]
 *
 */

// Approach 2: Use a two-pointer approach to evaluate and insert transformed values based on the direction of the parabola (A >= 0 fills from end, A < 0 fills from start).
// Time Complexity: O(N), as each element is processed once using two pointers.
// Space Complexity: O(N), for storing the sorted transformed values in a new ArrayList.
class Solution {
    // Method to evaluate the quadratic equation for a given x
    private int evaluate(int x, int A, int B, int C) {
        return A * x * x + B * x + C;
    }
    public ArrayList<Integer> sortArray(int[] arr, int A, int B, int C) {
        int n = arr.length;
        ArrayList<Integer> result = new ArrayList<>(Collections.nCopies(n, 0)); // Initialize list with size n

        int l   = 0;                                                            // Left pointer
        int r   = n - 1;                                                        // Right pointer
        int idx = (A >= 0) ? n - 1 : 0;                                         // Start filling from end if A >= 0, else from start

        while (l <= r) {
            int leftVal  = evaluate(arr[l], A, B, C);
            int rightVal = evaluate(arr[r], A, B, C);

            if (A >= 0) {
                // Parabola opens upward → fill larger values at the end
                if (leftVal > rightVal) {
                    result.set(idx--, leftVal);
                    l++;
                } else {
                    result.set(idx--, rightVal);
                    r--;
                }
            } else {
                // Parabola opens downward → fill smaller values at the start
                if (leftVal < rightVal) {
                    result.set(idx++, leftVal);
                    l++;
                } else {
                    result.set(idx++, rightVal);
                    r--;
                }
            }
        }

        return result; // Return the sorted transformed list
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [-4, -2, 0, 2, 4], A = 1, B = 3, C = 5
 * Function: f(x) = 1*x^2 + 3*x + 5
 *
 * Initial: l = 0, r = 4, idx = 4 (since A >= 0)
 *
 * Step 1:
 *   leftVal = f(-4) = 16 - 12 + 5 = 9
 *   rightVal = f(4) = 16 + 12 + 5 = 33
 *   → result[4] = 33, r--
 *
 * Step 2:
 *   leftVal = f(-4) = 9
 *   rightVal = f(2) = 4 + 6 + 5 = 15
 *   → result[3] = 15, r--
 *
 * Step 3:
 *   leftVal = f(-4) = 9
 *   rightVal = f(0) = 5
 *   → result[2] = 9, l++
 *
 * Step 4:
 *   leftVal = f(-2) = 4 - 6 + 5 = 3
 *   rightVal = f(0) = 5
 *   → result[1] = 5, r--
 *
 * Step 5:
 *   leftVal = f(-2) = 3
 *   rightVal = f(-2) = 3
 *   → result[0] = 3, r--
 *
 * Final Output: [3, 5, 9, 15, 33]
 *
 */
