/*
 * GfG Link: https://www.geeksforgeeks.org/problems/next-element-with-greater-frequency--170637/1
 *
 * Next element with greater frequency
 *
 * Difficulty: Medium Accuracy: 70.47% Submissions: 7K+ Points: 4
 *
 * Given an array arr[] of integers, for each element, find the closest element to its right that has a higher frequency than the current element.
 * If no such element exists, return -1 for that position.
 *
 * Examples:
 *
 * Input: arr[] = [2, 1, 1, 3, 2, 1]
 * Output: [1, -1, -1, 2, 1, -1]
 * Explanation: Frequencies: 1 → 3 times, 2 → 2 times, 3 → 1 time.
 * For arr[0] = 2, the next element 1 has a higher frequency → 1.
 * For arr[1] and arr[2], no element to the right has a higher frequency → -1.
 * For arr[3] = 3, the next element 2 has a higher frequency → 2.
 * For arr[4] = 2, the next element 1 has a higher frequency → 1.
 * For arr[5] = 1, no elements to the right → -1.
 *
 * Input: arr[] = [5, 1, 5, 6, 6]
 * Output: [-1, 5, -1, -1, -1]
 * Explanation: Frequencies: 1 → 1 time, 5 → 2 times, 6 → 2 times.
 * For arr[0] and arr[2], no element to the right has a higher frequency → -1.
 * For arr[1] = 1, the next element 5 has a higher frequency → 5.
 * For arr[3] and arr[4], no element to the right has a higher frequency → -1.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute-force – For each element, scan to the right until you find one with strictly higher frequency.
// Time Complexity: O(n²) – two nested loops in the worst case.
// Space Complexity: O(n) – for the frequency map (output vector not counted).
class Solution {
public:
    vector<int> findGreater(vector<int>& arr) {
        int                     n = arr.size();
        vector<int>             result(n, -1);
        unordered_map<int, int> freq;

        for (int x : arr) {
            freq[x]++;                                            // build frequency map
        }
        // for each position, scan to its right for next with higher freq
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (freq[arr[j]] > freq[arr[i]]) {                // found higher-frequency
                    result[i] = arr[j];
                    break;
                }
            }
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 1, 1, 3, 2, 1], freq: {1→3, 2→2, 3→1}
 * result = [-1,-1,-1,-1,-1,-1]
 *
 * i=0 (2): scan j=1→1 (3>2) → result[0]=1
 * i=1 (1): scan j=2→1 (3!>3), j=3→3(1!>3), j=4→2(2!>3), j=5→1(3!>3) → stays -1
 * i=2 (1): same as i=1 → -1
 * i=3 (3): scan j=4→2 (2>1) → result[3]=2
 * i=4 (2): scan j=5→1 (3>2) → result[4]=1
 * i=5 (1): no j→ result[5]=-1
 *
 * Final: [1,-1,-1,2,1,-1]
 */

// Approach 2: O(n) stack – use a stack of indices to track “waiting” positions, resolving when a higher-freq arrives.
// Time Complexity: O(n) – each index is pushed/popped at most once.
// Space Complexity: O(n) – for the frequency map and the stack.
class Solution {
public:
    vector<int> findGreater(vector<int>& arr) {
        int                     n = arr.size();
        vector<int>             result(n, -1);
        unordered_map<int, int> freq;

        for (int x : arr) {
            freq[x]++;
        }

        stack<int> st;                                           // will hold indices

        // traverse from left to right
        for (int i = 0; i < n; i++) {
            // resolve any stack tops whose freq < current freq
            while (!st.empty() && freq[arr[i]] > freq[arr[st.top()]]) {
                result[st.top()] = arr[i];
                st.pop();
            }
            st.push(i);
        }
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr = [2, 1, 1, 3, 2, 1], freq: {1→3, 2→2, 3→1}
 * result=[-1,-1,-1,-1,-1,-1], st=[]
 *
 * i=0 (2): st empty → push 0
 * i=1 (1): freq[1]=3 > freq[2]=2 → pop0→result[0]=1; push1
 * i=2 (1): freq[1]=3 !> freq[1]=3 → push2
 * i=3 (3): freq[3]=1 !>3 → push3
 * i=4 (2): freq[2]=2 !>1? actually 2>freq[3]=1 → pop3→result[3]=2; 2!>3→stop; push4
 * i=5 (1): freq[1]=3>freq[2]=2→pop4→result[4]=1; 3!>3(stop? no pop2? 3!>3); push5
 *
 * Remaining st=[1,2,5] → they stay -1
 *
 * Final: [1,-1,-1,2,1,-1]
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force – For each element, scan to the right until you find one with strictly higher frequency.
// Time Complexity: O(n²) – two nested loops in the worst case.
// Space Complexity: O(n) – for the frequency map (output list not counted).
class Solution {
    public ArrayList<Integer> findGreater(int[] arr) {
        int n = arr.length;
        ArrayList<Integer>    result = new ArrayList<>(Collections.nCopies(n, -1));
        Map<Integer, Integer> freq   = new HashMap<>();

        for (int x : arr) {
            freq.put(x, freq.getOrDefault(x, 0) + 1);
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (freq.get(arr[j]) > freq.get(arr[i])) {
                    result.set(i, arr[j]);
                    break;
                }
            }
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: [2,1,1,3,2,1], freq={1→3,2→2,3→1}
 * result=[-1,-1,-1,-1,-1,-1]
 *
 * i=0: scan→j=1→1(3>2)→result[0]=1
 * i=1,2: no higher→-1
 * i=3: j=4→2(2>1)→result[3]=2
 * i=4: j=5→1(3>2)→result[4]=1
 * i=5: none→-1
 *
 * Final: [1,-1,-1,2,1,-1]
 */

// Approach 2: O(n) stack – use a stack of indices to track “waiting” positions, resolving when a higher-freq arrives.
// Time Complexity: O(n) – each index is pushed/popped at most once.
// Space Complexity: O(n) – for the frequency map and the stack.
class Solution {
    public ArrayList<Integer> findGreater(int[] arr) {
        int n = arr.length;
        ArrayList<Integer>    result = new ArrayList<>(Collections.nCopies(n, -1));
        Map<Integer, Integer> freq   = new HashMap<>();

        for (int x : arr) {
            freq.put(x, freq.getOrDefault(x, 0) + 1);
        }

        Stack<Integer> st = new Stack<>();   // holds indices

        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && freq.get(arr[i]) > freq.get(arr[st.peek()])) {
                result.set(st.pop(), arr[i]);
            }
            st.push(i);
        }
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: [2,1,1,3,2,1], freq={1→3,2→2,3→1}
 * result=[-1,-1,-1,-1,-1,-1], st=[]
 *
 * i=0: push0
 * i=1: 3>2→pop0→res[0]=1; push1
 * i=2: 3!>3→push2
 * i=3: 1!>3→push3
 * i=4: 2>1→pop3→res[3]=2; 2!>3→push4
 * i=5: 3>2→pop4→res[4]=1; 3!>3→push5
 *
 * Remaining [1,2,5] → -1
 * Final: [1,-1,-1,2,1,-1]
 */
