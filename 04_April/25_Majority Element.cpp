// GfG Link: https://www.geeksforgeeks.org/problems/majority-element-1587115620/1

/*
 * Majority Element
 *
 * Difficulty: Medium Accuracy: 27.82% Submissions: 704K+ Points: 4 Average Time: 59m
 *
 * Given an array arr[]. Find the majority element in the array. If no majority element exists, return -1.
 * Note: A majority element in an array is an element that appears strictly more than arr.size()/2 times in the array.
 *
 * Examples:
 *
 * Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
 * Output: 1
 * Explanation: Since, 1 is present more than 7/2 times, so it is the majority element.
 *
 * Input: arr[] = [7]
 * Output: 7
 * Explanation: Since, 7 is single element and present more than 1/2 times, so it is the majority element.
 *
 * Input: arr[] = [2, 13]
 * Output: -1
 * Explanation: Since, no element is present more than 2/2 times, so there is no majority element.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute-force approach by checking the frequency of each element using nested loops
// Time Complexity: O(n^2), because for each element we loop through the array to count its occurrences
// Space Complexity: O(1), no extra space is used apart from variables
class Solution {
public:
    int majorityElement(vector<int>& arr) {
        int n = arr.size();

        // Loop to consider each element as a candidate for majority
        for (int i = 0; i < n; i++) {
            int count = 0;

            // Inner loop to count the frequency of arr[i]
            for (int j = 0; j < n; j++) {
                if (arr[i] == arr[j]) {
                    count++;   // Increment count if arr[i] matches arr[j]
                }
            }

            // Check if count of arr[i] is more than half the size of the array
            if (count > n / 2) {
                return arr[i];   // Return arr[i] as it is the majority element
            }
        }

        // If no majority element found, return -1
        return -1;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
 * n = 7
 * i = 0 → arr[i] = 1
 * count = 0 → compare arr[i] with all elements:
 *   arr[0] == 1 → count = 1
 *   arr[1] == 1 → count = 2
 *   arr[2] == 2 → skip
 *   arr[3] == 1 → count = 3
 *   arr[4] == 3 → skip
 *   arr[5] == 5 → skip
 *   arr[6] == 1 → count = 4
 * Since count = 4 > 7/2 → return 1 as majority element
 *
 */

// Approach 2: Use a hash map (unordered_map) to count the occurrences of each element while traversing the array once
// Time Complexity: O(n), as we traverse the array once and perform constant time map operations
// Space Complexity: O(n), in the worst case all elements are unique and stored in the map
class Solution {
public:
    int majorityElement(vector<int>& arr) {
        int n = arr.size();         // Get the size of the array
        unordered_map<int, int> mp; // Hash map to store frequency of elements

        // Traverse the array and count occurrences using the hash map
        for (int num : arr) {
            mp[num]++;   // Increment frequency of current element

            // Check if current element count exceeds n / 2
            if (mp[num] > n / 2) {
                return num;   // Return current element if it's the majority
            }
        }

        // If no majority element is found, return -1
        return -1;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
 * n = 7
 * Initialize empty map: mp = {}
 * num = 1 → mp[1] = 1 → not > 3.5
 * num = 1 → mp[1] = 2 → not > 3.5
 * num = 2 → mp[2] = 1 → not > 3.5
 * num = 1 → mp[1] = 3 → not > 3.5
 * num = 3 → mp[3] = 1 → not > 3.5
 * num = 5 → mp[5] = 1 → not > 3.5
 * num = 1 → mp[1] = 4 → 4 > 3.5 → return 1
 *
 */

// Approach 3: Moore's Voting Algorithm - find a potential candidate and verify if it is the majority
// Time Complexity: O(n), as we traverse the array twice (once to find the candidate, once to verify it)
// Space Complexity: O(1), no extra space is used
class Solution {
public:
    int majorityElement(vector<int>& arr) {
        int n   = arr.size();     // Get the size of the array
        int cnt = 0;              // Counter to track potential majority element
        int el;                   // Variable to store potential majority element

        // First pass: Find a candidate for majority element
        for (int i = 0; i < n; i++) {
            if (cnt == 0) {
                cnt = 1;          // Reset counter to 1
                el  = arr[i];     // Assume current element as candidate
            } else if (arr[i] == el) {
                cnt++;            // Increment counter if same as candidate
            } else {
                cnt--;            // Decrement counter if different
            }
        }

        int cnt1 = 0;       // Counter to verify if candidate is actually the majority

        // Second pass: Verify the candidate by counting its actual occurrences
        for (int i = 0; i < n; i++) {
            if (arr[i] == el) {
                cnt1++;       // Count occurrences of candidate
            }
        }

        // If the candidate occurs more than n/2 times, return it
        if (cnt1 > n / 2) {
            return el;
        }

        // Otherwise, no majority element exists
        return -1;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
 * n = 7
 * First loop to find candidate:
 * i = 0 → cnt = 0 → cnt = 1, el = 1
 * i = 1 → arr[1] == el → cnt = 2
 * i = 2 → arr[2] != el → cnt = 1
 * i = 3 → arr[3] == el → cnt = 2
 * i = 4 → arr[4] != el → cnt = 1
 * i = 5 → arr[5] != el → cnt = 0
 * i = 6 → cnt = 0 → cnt = 1, el = 1
 *
 * Second loop to verify candidate:
 * Count how many times 1 appears → cnt1 = 4
 *
 * Since cnt1 = 4 > 7/2 = 3.5 → return 1
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute-force approach by checking the frequency of each element using nested loops
// Time Complexity: O(n^2), because for each element we count its occurrences in the entire array
// Space Complexity: O(1), since no additional space is used apart from loop counters and variables
class Solution {
    static int majorityElement(int arr[]) {
        int n = arr.length; // Get the size of the array

        // Loop to consider each element as a candidate for majority
        for (int i = 0; i < n; i++) {
            int count = 0; // Initialize count of current element

            // Inner loop to count the frequency of arr[i]
            for (int j = 0; j < n; j++) {
                if (arr[i] == arr[j]) {
                    count++; // Increment count if arr[i] matches arr[j]
                }
            }

            // Check if count of arr[i] is more than half the size of the array
            if (count > n / 2) {
                return arr[i]; // Return arr[i] as it is the majority element
            }
        }

        // If no majority element found, return -1
        return -1;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
 * n = 7
 * i = 0 → arr[i] = 1
 * count = 0
 *   j = 0 → arr[0] == 1 → count = 1
 *   j = 1 → arr[1] == 1 → count = 2
 *   j = 2 → arr[2] == 2 → no match
 *   j = 3 → arr[3] == 1 → count = 3
 *   j = 4 → arr[4] == 3 → no match
 *   j = 5 → arr[5] == 5 → no match
 *   j = 6 → arr[6] == 1 → count = 4
 * Now count = 4 > 7/2 = 3.5 → return 1
 *
 */

// Approach 2: Use a HashMap to count the occurrences of each element during a single traversal of the array
// Time Complexity: O(n), since we traverse the array once and perform O(1) operations on the HashMap
// Space Complexity: O(n), in the worst case all elements are unique and stored in the HashMap
class Solution {
    static int majorityElement(int arr[]) {
        int n = arr.length;                         // Get the length of the array
        Map<Integer, Integer> mp = new HashMap<>(); // HashMap to store frequency of elements

        // Traverse the array and count occurrences using the hash map
        for (int num : arr) {
            // Update the frequency count of the current number
            mp.put(num, mp.getOrDefault(num, 0) + 1);

            // Check if current element count exceeds n / 2
            if (mp.get(num) > n / 2) {
                return num; // Return current element if it's the majority
            }
        }

        // If no majority element is found, return -1
        return -1;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
 * n = 7
 * Initialize empty HashMap: mp = {}
 * num = 1 → mp = {1=1} → 1 <= 3.5
 * num = 1 → mp = {1=2} → 2 <= 3.5
 * num = 2 → mp = {1=2, 2=1} → 1 <= 3.5
 * num = 1 → mp = {1=3, 2=1} → 3 <= 3.5
 * num = 3 → mp = {1=3, 2=1, 3=1} → 1 <= 3.5
 * num = 5 → mp = {1=3, 2=1, 3=1, 5=1} → 1 <= 3.5
 * num = 1 → mp = {1=4, 2=1, 3=1, 5=1} → 4 > 3.5 → return 1
 *
 */

// Approach 3: Moore's Voting Algorithm - find a potential candidate in one pass, then verify it in a second pass
// Time Complexity: O(n), as we traverse the array twice (once to find the candidate, once to verify it)
// Space Complexity: O(1), no extra space is used
class Solution {
    static int majorityElement(int arr[]) {
        int n       = arr.length; // Get the length of the array
        int count   = 0;          // Counter to track potential majority element
        int element = 0;          // Variable to store potential majority element

        // First pass: Find a candidate for majority element
        for (int i = 0; i < n; i++) {
            if (count == 0) {
                count   = 1;      // Reset counter
                element = arr[i]; // Assume current element as candidate
            } else if (arr[i] == element) {
                count++;          // Increment if same as candidate
            } else {
                count--;          // Decrement if different
            }
        }

        int count1 = 0; // Counter to verify candidate

        // Second pass: Count occurrences of the candidate
        for (int i = 0; i < n; i++) {
            if (arr[i] == element) {
                count1++; // Count how many times candidate appears
            }
        }

        // If candidate occurs more than n/2 times, return it
        if (count1 > n / 2) {
            return element;
        }

        // Otherwise, return -1 indicating no majority element
        return -1;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = [1, 1, 2, 1, 3, 5, 1]
 * n = 7
 * First pass (finding candidate):
 * i = 0 → count = 0 → count = 1, element = 1
 * i = 1 → arr[1] == element → count = 2
 * i = 2 → arr[2] != element → count = 1
 * i = 3 → arr[3] == element → count = 2
 * i = 4 → arr[4] != element → count = 1
 * i = 5 → arr[5] != element → count = 0
 * i = 6 → count = 0 → count = 1, element = 1
 *
 * Second pass (verifying candidate):
 * Count how many times 1 appears → count1 = 4
 *
 * Since count1 = 4 > 7/2 = 3.5 → return 1
 *
 */
