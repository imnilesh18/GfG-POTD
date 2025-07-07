/*
 * GfG Link: https://www.geeksforgeeks.org/problems/next-greater-element/1
 *
 * Next Greater Element in Circular Array
 *
 * Difficulty: Medium Accuracy: 56.97% Submissions: 40K+ Points: 4
 *
 * Given a circular integer array arr[], the task is to determine the next greater element (NGE) for each element in the array.
 *
 * The next greater element of an element arr[i] is the first element that is greater than arr[i] when traversing circularly. If no such element exists, return -1 for that position.
 *
 * Circular Property:
 * Since the array is circular, after reaching the last element, the search continues from the beginning until we have looked at all elements once.
 *
 * Examples:
 *
 * Input: arr[] = [1, 3, 2, 4]
 * Output: [3, 4, 4, -1]
 * Explanation:
 * The next greater element for 1 is 3.
 * The next greater element for 3 is 4.
 * The next greater element for 2 is 4.
 * The next greater element for 4 does not exist, so return -1.
 *
 * Input: arr[] = [0, 2, 3, 1, 1]
 * Output: [2, 3, -1, 2, 2]
 * Explanation:
 * The next greater element for 0 is 2.
 * The next greater element for 2 is 3.
 * The next greater element for 3 does not exist, so return -1.
 * The next greater element for 1 is 2 (from circular traversal).
 * The next greater element for 1 is 2 (from circular traversal).
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute-force – For each element, check the next n−1 elements circularly to find the next bigger element.
// Time Complexity: O(n²) – Outer loop runs n times, and for each i, inner loop can run up to n times in worst case.
// Space Complexity: O(1) – No extra space used apart from the output vector.
class Solution {
public:
    vector<int> nextLargerElement(vector<int>& arr) {
        int n = arr.size();                       // Size of the array

        vector<int> result(n, -1);                // Result initialized with -1s (next greater not found by default)

        // Iterate for all the elements of the array
        for (int i = 0; i < n; i++) {             // Fix index i
            for (int j = 1; j < n; j++) {         // Check next n−1 elements circularly
                // Checking for next greater element
                if (arr[i] < arr[(i + j) % n]) {  // If current element is smaller than next circular element
                    result[i] = arr[(i + j) % n]; // Assign the next greater
                    break;                        // No need to check further
                }
            }
        }

        return result;                            // Return the result
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 7, 3, 5, 1], n = 5
 * result initialized to [-1, -1, -1, -1, -1]
 *
 * i = 0: arr[0] = 2
 *  j = 1 → arr[1] = 7 → 2 < 7 → result[0] = 7, break
 *  result = [7, -1, -1, -1, -1]
 *
 * i = 1: arr[1] = 7
 *  j = 1 → arr[2] = 3 → 7 < 3 → false
 *  j = 2 → arr[3] = 5 → false
 *  j = 3 → arr[4] = 1 → false
 *  j = 4 → arr[0] = 2 → false → no greater found
 *  result = [7, -1, -1, -1, -1]
 *
 * i = 2: arr[2] = 3
 *  j = 1 → arr[3] = 5 → 3 < 5 → result[2] = 5, break
 *  result = [7, -1, 5, -1, -1]
 *
 * i = 3: arr[3] = 5
 *  j = 1 → arr[4] = 1 → false
 *  j = 2 → arr[0] = 2 → false
 *  j = 3 → arr[1] = 7 → 5 < 7 → result[3] = 7, break
 *  result = [7, -1, 5, 7, -1]
 *
 * i = 4: arr[4] = 1
 *  j = 1 → arr[0] = 2 → 1 < 2 → result[4] = 2, break
 *  result = [7, -1, 5, 7, 2]
 *
 * Final Output: [7, -1, 5, 7, 2]
 */

// Approach 2: O(n) monotonic stack – traverse twice, using a stack of indices to assign next bigger elements as they arrive.
// Time Complexity: O(n) – each index is pushed and popped at most once.
// Space Complexity: O(n) – auxiliary stack for indices.
class Solution {
public:
    vector<int> nextLargerElement(vector<int>& arr) {
        int         n = arr.size();             // Size of the array
        vector<int> result(n, -1);              // Result initialized to -1s
        stack<int>  st;                         // Stack to store indices of waiting elements

        for (int i = 0; i < 2 * n; i++) {       // Traverse twice for circularity
            int idx = i % n;                    // Actual index in arr
            int num = arr[idx];                 // Current number

            // While current num is bigger than arr at the top index
            while (!st.empty() && num > arr[st.top()]) {
                result[st.top()] = num;         // Assign it as the next greater
                st.pop();                       // Remove that index
            }

            if (i < n) {                        // Only push original indices on first pass
                st.push(idx);                   // Add index to stack
            }
        }
        return result;                          // Return filled results
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 7, 3, 5, 1], n = 5
 * result initialized to [-1, -1, -1, -1, -1]
 * st = []
 *
 * i = 0: idx=0, num=2
 *  st empty → push 0 → st=[0]
 *
 * i = 1: idx=1, num=7
 *  7 > arr[0]=2 → result[0]=7; pop → st=[]
 *  push 1 → st=[1]; result=[7,-1,-1,-1,-1]
 *
 * i = 2: idx=2, num=3
 *  3 ≤ arr[1]=7 → push 2 → st=[1,2]
 *
 * i = 3: idx=3, num=5
 *  5 > arr[2]=3 → result[2]=5; pop → st=[1]
 *  5 ≤ arr[1]=7 → stop; push 3 → st=[1,3]; result=[7,-1,5,-1,-1]
 *
 * i = 4: idx=4, num=1
 *  1 ≤ arr[3]=5 → push 4 → st=[1,3,4]
 *
 * i = 5: idx=0, num=2
 *  2 > arr[4]=1 → result[4]=2; pop → st=[1,3]
 *  2 ≤ arr[3]=5 → stop
 *
 * i = 6: idx=1, num=7
 *  7 > arr[3]=5 → result[3]=7; pop → st=[1]
 *  7 ≤ arr[1]=7 → stop
 *
 * i = 7: idx=2, num=3
 *  3 ≤ arr[1]=7 → nothing
 *
 * i = 8: idx=3, num=5
 *  5 ≤ arr[1]=7 → nothing
 *
 * i = 9: idx=4, num=1
 *  1 ≤ arr[1]=7 → nothing
 *
 * End: st=[1] → result[1] stays -1
 * Final Output: [7, -1, 5, 7, 2]
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force – For each element, check the next n−1 elements circularly to find the next bigger element.
// Time Complexity: O(n²) – Outer loop runs n times, and for each i, inner loop can run up to n times in worst case.
// Space Complexity: O(1) – No extra space used apart from the output list.
class Solution {
    public ArrayList<Integer> nextLargerElement(int[] arr) {
        int n = arr.length;                            // Size of the array

        ArrayList<Integer> result = new ArrayList<>(); // Result initialized with -1s

        for (int k = 0; k < n; k++) {
            result.add(-1);
        }

        // Iterate for all the elements of the array
        for (int i = 0; i < n; i++) {                // Fix index i
            for (int j = 1; j < n; j++) {            // Check next n−1 elements circularly
                // Checking for next greater element
                if (arr[i] < arr[(i + j) % n]) {     // If current element is smaller than next circular element
                    result.set(i, arr[(i + j) % n]); // Assign the next greater
                    break;                           // No need to check further
                }
            }
        }

        return result;                            // Return the result
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 7, 3, 5, 1], n = 5
 * result initialized to [-1, -1, -1, -1, -1]
 *
 * i = 0: arr[0] = 2
 *  j = 1 → arr[1] = 7 → 2 < 7 → result[0] = 7, break
 *  result = [7, -1, -1, -1, -1]
 *
 * i = 1: arr[1] = 7
 *  j = 1 → arr[2] = 3 → 7 < 3 → false
 *  j = 2 → arr[3] = 5 → false
 *  j = 3 → arr[4] = 1 → false
 *  j = 4 → arr[0] = 2 → false → no greater found
 *  result = [7, -1, -1, -1, -1]
 *
 * i = 2: arr[2] = 3
 *  j = 1 → arr[3] = 5 → 3 < 5 → result[2] = 5, break
 *  result = [7, -1, 5, -1, -1]
 *
 * i = 3: arr[3] = 5
 *  j = 1 → arr[4] = 1 → false
 *  j = 2 → arr[0] = 2 → false
 *  j = 3 → arr[1] = 7 → 5 < 7 → result[3] = 7, break
 *  result = [7, -1, 5, 7, -1]
 *
 * i = 4: arr[4] = 1
 *  j = 1 → arr[0] = 2 → 1 < 2 → result[4] = 2, break
 *  result = [7, -1, 5, 7, 2]
 *
 * Final Output: [7, -1, 5, 7, 2]
 */

// Approach 2: O(n) monotonic stack – traverse twice, using a stack of indices to assign next bigger elements as they arrive.
// Time Complexity: O(n) – each index is pushed and popped at most once.
// Space Complexity: O(n) – auxiliary stack for indices.
class Solution {
    public ArrayList<Integer> nextLargerElement(int[] arr) {
        int n = arr.length;                        // Size of the array
        ArrayList<Integer> result = new ArrayList<>();

        for (int k = 0; k < n; k++) {              // Initialize result with -1s
            result.add(-1);
        }

        Stack<Integer> st = new Stack<>();         // Stack to store indices of waiting elements

        for (int i = 0; i < 2 * n; i++) {          // Traverse twice for circularity
            int idx = i % n;                       // Actual index in arr
            int num = arr[idx];                    // Current number

            // While current num is bigger than arr at the top index
            while (!st.isEmpty() && num > arr[st.peek()]) {
                result.set(st.pop(), num);         // Assign it as the next greater
            }

            if (i < n) {                           // Only push original indices on first pass
                st.push(idx);                      // Add index to stack
            }
        }
        return result;                             // Return filled results
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 7, 3, 5, 1], n = 5
 * result initialized to [-1, -1, -1, -1, -1]
 * st = []
 *
 * i = 0: idx = 0, num = 2
 *   st empty → push 0 → st = [0]
 *
 * i = 1: idx = 1, num = 7
 *   7 > arr[0] = 2 → result[0] = 7; pop → st = []
 *   push 1 → st = [1]; result = [7, -1, -1, -1, -1]
 *
 * i = 2: idx = 2, num = 3
 *   3 ≤ arr[1] = 7 → push 2 → st = [1, 2]
 *
 * i = 3: idx = 3, num = 5
 *   5 > arr[2] = 3 → result[2] = 5; pop → st = [1]
 *   5 ≤ arr[1] = 7 → stop; push 3 → st = [1, 3]
 *   result = [7, -1, 5, -1, -1]
 *
 * i = 4: idx = 4, num = 1
 *   1 ≤ arr[3] = 5 → push 4 → st = [1, 3, 4]
 *
 * i = 5: idx = 0, num = 2
 *   2 > arr[4] = 1 → result[4] = 2; pop → st = [1, 3]
 *   2 ≤ arr[3] = 5 → stop
 *
 * i = 6: idx = 1, num = 7
 *   7 > arr[3] = 5 → result[3] = 7; pop → st = [1]
 *   7 ≤ arr[1] = 7 → stop
 *
 * i = 7: idx = 2, num = 3
 *   3 ≤ arr[1] = 7 → nothing
 *
 * i = 8: idx = 3, num = 5
 *   5 ≤ arr[1] = 7 → nothing
 *
 * i = 9: idx = 4, num = 1
 *   1 ≤ arr[1] = 7 → nothing
 *
 * End: st = [1] → result[1] stays -1
 * Final Output: [7, -1, 5, 7, 2]
 */
