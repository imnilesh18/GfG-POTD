/*
 * GfG Link: https://www.geeksforgeeks.org/problems/sum-of-subarray-minimum/1
 *
 * Sum of subarray minimum
 *
 * Difficulty: Medium Accuracy: 46.92% Submissions: 12K+ Points: 4 Average Time: 30m
 *
 * Given an array arr[] of positive integers, find the total sum of the minimum elements of every possible subarrays.
 * Note: It is guaranteed that the total sum will fit within a 32-bit unsigned integer.
 *
 * Examples:
 *
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 17
 * Explanation: Subarrays are [3], [1], [2], [4], [3, 1], [1, 2], [2, 4], [3, 1, 2], [1, 2, 4], [3, 1, 2, 4]. Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1. Sum of all these is 17.
 * Input: arr[] = [71, 55, 82, 55]
 * Output: 593
 * Explanation: The sum of the minimum of all the subarrays is 593.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 3*10^4
 * 1 ≤ arr[i] ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute force by iterating all subarrays and tracking the minimum element for each
// Time Complexity: O(n^2) due to the nested loops over start and end indices of subarrays
// Space Complexity: O(1) uses only a few integer variables regardless of input size
class Solution {
public:
    int sumSubMins(vector<int>& arr) {
        int n      = arr.size();      // total number of elements in the array
        int result = 0;               // accumulator for sum of subarray minimums

        // iterate over all possible starting points of subarrays
        for (int i = 0; i < n; i++) {
            int mini = arr[i];        // initialize minimum to the first element of the subarray
            // extend the subarray one element at a time
            for (int j = i; j < n; j++) {
                // update the minimum for the current subarray [i..j]
                mini = min(mini, arr[j]);

                // add the current minimum to the result
                result += mini;
            }
        }
        return result;                // return the total sum
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 17
 *
 * i = 0:
 *   mini = arr[0] = 3
 *   j = 0: mini = min(3, arr[0]=3) = 3, result += 3         => result = 3
 *   j = 1: mini = min(3, arr[1]=1) = 1, result += 1         => result = 4
 *   j = 2: mini = min(1, arr[2]=2) = 1, result += 1         => result = 5
 *   j = 3: mini = min(1, arr[3]=4) = 1, result += 1         => result = 6
 *
 * i = 1:
 *   mini = arr[1] = 1
 *   j = 1: mini = min(1, arr[1]=1) = 1, result += 1         => result = 7
 *   j = 2: mini = min(1, arr[2]=2) = 1, result += 1         => result = 8
 *   j = 3: mini = min(1, arr[3]=4) = 1, result += 1         => result = 9
 *
 * i = 2:
 *   mini = arr[2] = 2
 *   j = 2: mini = min(2, arr[2]=2) = 2, result += 2         => result = 11
 *   j = 3: mini = min(2, arr[3]=4) = 2, result += 2         => result = 13
 *
 * i = 3:
 *   mini = arr[3] = 4
 *   j = 3: mini = min(4, arr[3]=4) = 4, result += 4         => result = 17
 *
 * Final result = 17
 */

// Approach 2: Use monotonic stacks to compute Next Smaller to Left (NSL) and Next Smaller to Right (NSR) for each element, then sum each element’s contribution as arr[i] * leftDistance * rightDistance
// Time Complexity: O(n) since each element is pushed and popped at most once from each stack
// Space Complexity: O(n) for storing NSL, NSR arrays and the stacks
class Solution {
public:

    vector<int> getNSL(vector<int>& arr, int n) {
        vector<int> result(n);
        stack<int>  st;

        for (int i = 0; i < n; i++) {
            // pop until you find a smaller element or stack becomes empty
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            // if empty, no smaller to left; else top of stack is NSL
            result[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        return result;
    }
    
    vector<int> getNSR(vector<int>& arr, int n) {
        vector<int> result(n);
        stack<int>  st;

        for (int i = n - 1; i >= 0; i--) {
            // pop until you find a strictly smaller element or stack becomes empty
            while (!st.empty() && arr[st.top()] > arr[i]) {
                st.pop();
            }
            // if empty, no smaller to right; else top of stack is NSR
            result[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        return result;
    }

    int sumSubMins(vector<int>& arr) {
        int         n   = arr.size();
        vector<int> NSL = getNSL(arr, n);
        vector<int> NSR = getNSR(arr, n);

        int sum = 0;

        for (int i = 0; i < n; i++) {
            // distance to previous smaller on left
            int leftD = i - NSL[i];
            // distance to next smaller on right
            int rightD = NSR[i] - i;
            // each element contributes arr[i] * leftD * rightD
            sum += arr[i] * leftD * rightD;
        }
        return sum;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 17
 *
 * Compute NSL:
 * i=0: st empty ⇒ NSL[0]=-1, push 0
 * i=1: pop 0 (3≥1), st empty ⇒ NSL[1]=-1, push 1
 * i=2: arr[top]=1<2 ⇒ NSL[2]=1, push 2
 * i=3: arr[top]=2<4 ⇒ NSL[3]=2, push 3
 * NSL = [-1, -1, 1, 2]
 *
 * Compute NSR:
 * i=3: st empty ⇒ NSR[3]=4, push 3
 * i=2: arr[top]=4>2, pop 3; st empty ⇒ NSR[2]=4, push 2
 * i=1: arr[top]=2>1, pop 2; st empty ⇒ NSR[1]=4, push 1
 * i=0: arr[top]=1<3 ⇒ NSR[0]=1, push 0
 * NSR = [1, 4, 4, 4]
 *
 * Contributions:
 * i=0: leftD=0-(-1)=1, rightD=1-0=1 ⇒ 3*1*1 = 3  ⇒ sum=3
 * i=1: leftD=1-(-1)=2, rightD=4-1=3 ⇒ 1*2*3 = 6  ⇒ sum=9
 * i=2: leftD=2-1=1,    rightD=4-2=2 ⇒ 2*1*2 = 4  ⇒ sum=13
 * i=3: leftD=3-2=1,    rightD=4-3=1 ⇒ 4*1*1 = 4  ⇒ sum=17
 *
 * Final result = 17
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute force by iterating all subarrays and tracking the minimum element for each
// Time Complexity: O(n^2) due to the nested loops over start and end indices of subarrays
// Space Complexity: O(1) uses only a few integer variables regardless of input size
class Solution {
    public int sumSubMins(int[] arr) {
        int n      = arr.length;      // total number of elements in the array
        int result = 0;               // accumulator for sum of subarray minimums

        // iterate over all possible starting points of subarrays
        for (int i = 0; i < n; i++) {
            int mini = arr[i];        // initialize minimum to the first element of the subarray
            // extend the subarray one element at a time
            for (int j = i; j < n; j++) {
                // update the minimum for the current subarray [i..j]
                mini = Math.min(mini, arr[j]);

                // add the current minimum to the result
                result += mini;
            }
        }
        return result;                // return the total sum
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 17
 *
 * i = 0:
 *   mini = arr[0] = 3
 *   j = 0: mini = Math.min(3, arr[0]=3) = 3, result += 3         => result = 3
 *   j = 1: mini = Math.min(3, arr[1]=1) = 1, result += 1         => result = 4
 *   j = 2: mini = Math.min(1, arr[2]=2) = 1, result += 1         => result = 5
 *   j = 3: mini = Math.min(1, arr[3]=4) = 1, result += 1         => result = 6
 *
 * i = 1:
 *   mini = arr[1] = 1
 *   j = 1: mini = Math.min(1, arr[1]=1) = 1, result += 1         => result = 7
 *   j = 2: mini = Math.min(1, arr[2]=2) = 1, result += 1         => result = 8
 *   j = 3: mini = Math.min(1, arr[3]=4) = 1, result += 1         => result = 9
 * a
 * i = 2:
 *   mini = arr[2] = 2
 *   j = 2: mini = Math.min(2, arr[2]=2) = 2, result += 2         => result = 11
 *   j = 3: mini = Math.min(2, arr[3]=4) = 2, result += 2         => result = 13
 *
 * i = 3:
 *   mini = arr[3] = 4
 *   j = 3: mini = Math.min(4, arr[3]=4) = 4, result += 4         => result = 17
 *
 * Final result = 17
 */

// Approach 2: Use monotonic stacks to compute Next Smaller to Left (NSL) and Next Smaller to Right (NSR) for each element, then sum each element’s contribution as arr[i] * leftDistance * rightDistance
// Time Complexity: O(n) since each element is pushed and popped at most once from each stack
// Space Complexity: O(n) for storing NSL, NSR arrays and the stacks
class Solution {
    public int[] getNSL(int[] arr, int n) {
        int[] result = new int[n];
        Deque<Integer> st = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            // pop until you find a smaller element or stack becomes empty
            while (!st.isEmpty() && arr[st.peek()] >= arr[i]) {
                st.pop();
            }
            // if empty, no smaller to left; else top of stack is NSL
            result[i] = st.isEmpty() ? -1 : st.peek();
            st.push(i);
        }
        return result;
    }

    public int[] getNSR(int[] arr, int n) {
        int[] result = new int[n];
        Deque<Integer> st = new ArrayDeque<>();

        for (int i = n - 1; i >= 0; i--) {
            // pop until you find a strictly smaller element or stack becomes empty
            while (!st.isEmpty() && arr[st.peek()] > arr[i]) {
                st.pop();
            }
            // if empty, no smaller to right; else top of stack is NSR
            result[i] = st.isEmpty() ? n : st.peek();
            st.push(i);
        }
        return result;
    }

    public int sumSubMins(int[] arr) {
        int n = arr.length;
        int[] NSL = getNSL(arr, n);
        int[] NSR = getNSR(arr, n);

        int sum = 0;

        for (int i = 0; i < n; i++) {
            // distance to previous smaller on left
            int leftD = i - NSL[i];
            // distance to next smaller on right
            int rightD = NSR[i] - i;
            // each element contributes arr[i] * leftD * rightD
            sum += arr[i] * leftD * rightD;
        }
        return sum;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [3, 1, 2, 4]
 * Output: 17
 *
 * Compute NSL:
 * i=0: stack empty ⇒ NSL[0]=-1, push 0
 * i=1: pop 0 (3≥1), stack empty ⇒ NSL[1]=-1, push 1
 * i=2: arr[stack.peek()]=1<2 ⇒ NSL[2]=1, push 2
 * i=3: arr[stack.peek()]=2<4 ⇒ NSL[3]=2, push 3
 * NSL = [-1, -1, 1, 2]
 *
 * Compute NSR:
 * i=3: stack empty ⇒ NSR[3]=4, push 3
 * i=2: pop 3 (4>2), stack empty ⇒ NSR[2]=4, push 2
 * i=1: pop 2 (2>1), stack empty ⇒ NSR[1]=4, push 1
 * i=0: arr[stack.peek()]=1<3 ⇒ NSR[0]=1, push 0
 * NSR = [1, 4, 4, 4]
 *
 * Contributions:
 * i=0: leftD=1, rightD=1 ⇒ 3*1*1 = 3  ⇒ sum=3
 * i=1: leftD=2, rightD=3 ⇒ 1*2*3 = 6  ⇒ sum=9
 * i=2: leftD=1, rightD=2 ⇒ 2*1*2 = 4  ⇒ sum=13
 * i=3: leftD=1, rightD=1 ⇒ 4*1*1 = 4  ⇒ sum=17
 *
 * Final result = 17
 */
