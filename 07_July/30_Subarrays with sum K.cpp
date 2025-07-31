/*
 * GfG Link: https://www.geeksforgeeks.org/problems/subarrays-with-sum-k/1
 *
 * Subarrays with sum K
 *
 * Difficulty: Medium Accuracy: 49.74% Submissions: 88K+ Points: 4
 *
 * Given an unsorted array arr[] of integers, find the number of subarrays whose sum exactly equal to a given number k.
 *
 * Examples:
 *
 * Input: arr[] = [10, 2, -2, -20, 10], k = -10
 * Output: 3
 * Explaination: Subarrays: arr[0...3], arr[1...4], arr[3...4] have sum exactly equal to -10.
 *
 * Input: arr[] = [9, 4, 20, 3, 10, 5], k = 33
 * Output: 2
 * Explaination: Subarrays: arr[0...2], arr[2...4] have sum exactly equal to 33.
 *
 * Input: arr[] = [1, 3, 5], k = 0
 * Output: 0
 * Explaination: No subarray with 0 sum.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * -10^3 ≤ arr[i] ≤ 10^3
 * -10^5 ≤ k ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Intuition: The problem can be efficiently solved using the concept of prefix sums. If the cumulative sum up to index 'i' is 'sum_i' and the cumulative sum up to index 'j' (where j < i) is 'sum_j', then the sum of the subarray from 'j+1' to 'i' is 'sum_i - sum_j'. We are looking for subarrays where 'sum_i - sum_j = k'. This can be rewritten as 'sum_j = sum_i - k'. So, for each cumulative sum 'sum_i' we encounter, we just need to find how many times we have previously seen the cumulative sum 'sum_i - k'. A hash map is perfect for storing and retrieving the frequencies of these prefix sums in constant average time.

// Approach:
// 1. Initialize an unordered_map 'mp' to store the frequency of each prefix sum encountered.
// 2. Initialize 'result' to 0 to count the subarrays and 'cumSum' to 0 for the current prefix sum.
// 3. Add a key-value pair {0, 1} to the map. This is a crucial step to handle cases where a subarray with the required sum 'k' starts from the beginning of the array (index 0).
// 4. Iterate through the input array 'arr' from left to right.
// 5. In each iteration, add the current element to 'cumSum'.
// 6. Check if the map 'mp' contains the key 'cumSum - k'.
// 7. If it does, it means there are subarrays ending at the current index with a sum of 'k'. Add the frequency of 'cumSum - k' (i.e., mp[cumSum - k]) to our 'result'.
// 8. Increment the frequency of the current 'cumSum' in the map.
// 9. After the loop finishes, return the final 'result'.

// Time Complexity: O(N), where N is the size of the array. This is because we traverse the array only once, and the hash map operations (insertion and lookup) take O(1) time on average.
// Space Complexity: O(N), where N is the size of the array. In the worst-case scenario, all prefix sums could be unique, requiring the hash map to store N entries.
class Solution {
public:
    int cntSubarrays(vector<int>& arr, int k) {
        // Use an unordered_map to store prefix sums and their frequencies.
        unordered_map<int, int> mp;
        int result = 0; // Initialize count of subarrays with sum k.

        int cumSum = 0; // This will store the cumulative sum of elements.

        // Insert a prefix sum of 0 with a frequency of 1.
        // This handles subarrays that start from index 0.
        mp.insert({ 0, 1 });

        // Iterate through the array elements.
        for (int i = 0; i < arr.size(); i++) {
            // Update the cumulative sum with the current element.
            cumSum += arr[i];

            // Check if a subarray with sum 'k' ending at the current index exists.
            // This is true if (cumSum - k) has been seen before.
            if (mp.find(cumSum - k) != mp.end()) {
                // Add the frequency of (cumSum - k) to the result.
                // Each occurrence of (cumSum - k) represents a valid subarray.
                result += mp[cumSum - k];
            }

            // Increment the frequency of the current cumulative sum in the map.
            mp[cumSum]++;
        }

        // Return the total count of subarrays.
        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Example: arr[] = [10, 2, -2, -20, 10], k = -10
 *
 * Initial State:
 * result = 0
 * cumSum = 0
 * mp = {0: 1}
 *
 * Iteration 1 (i=0, arr[i]=10):
 * cumSum = 0 + 10 = 10
 * Check for (cumSum - k) = (10 - (-10)) = 20 in mp. Not found.
 * Increment mp[10]. mp becomes {0: 1, 10: 1}
 *
 * Iteration 2 (i=1, arr[i]=2):
 * cumSum = 10 + 2 = 12
 * Check for (cumSum - k) = (12 - (-10)) = 22 in mp. Not found.
 * Increment mp[12]. mp becomes {0: 1, 10: 1, 12: 1}
 *
 * Iteration 3 (i=2, arr[i]=-2):
 * cumSum = 12 - 2 = 10
 * Check for (cumSum - k) = (10 - (-10)) = 20 in mp. Not found.
 * Increment mp[10]. mp becomes {0: 1, 10: 2, 12: 1}
 *
 * Iteration 4 (i=3, arr[i]=-20):
 * cumSum = 10 - 20 = -10
 * Check for (cumSum - k) = (-10 - (-10)) = 0 in mp. Found! mp[0] is 1.
 * result = result + mp[0] = 0 + 1 = 1. (Subarray [10, 2, -2, -20] has sum -10)
 * Increment mp[-10]. mp becomes {0: 1, 10: 2, 12: 1, -10: 1}
 *
 * Iteration 5 (i=4, arr[i]=10):
 * cumSum = -10 + 10 = 0
 * Check for (cumSum - k) = (0 - (-10)) = 10 in mp. Found! mp[10] is 2.
 * result = result + mp[10] = 1 + 2 = 3.
 * (Subarray [2, -2, -20, 10] corresponds to the first time prefix sum 10 was seen)
 * (Subarray [-20, 10] corresponds to the second time prefix sum 10 was seen)
 * Increment mp[0]. mp becomes {0: 2, 10: 2, 12: 1, -10: 1}
 *
 * End of loop.
 * Final result: 3
 *
 */

/************************************************************ JAVA ************************************************/

// Intuition: The problem can be efficiently solved using the concept of prefix sums. If the cumulative sum up to index 'i' is 'sum_i' and the cumulative sum up to index 'j' (where j < i) is 'sum_j', then the sum of the subarray from 'j+1' to 'i' is 'sum_i - sum_j'. We are looking for subarrays where 'sum_i - sum_j = k'. This can be rewritten as 'sum_j = sum_i - k'. So, for each cumulative sum 'sum_i' we encounter, we just need to find how many times we have previously seen the cumulative sum 'sum_i - k'. A HashMap is perfect for storing and retrieving the frequencies of these prefix sums in constant average time.

// Approach:
// 1. Initialize a HashMap 'map' to store the frequency of each prefix sum encountered.
// 2. Initialize 'result' to 0 to count the subarrays and 'cumSum' to 0 for the current prefix sum.
// 3. Add a key-value pair {0, 1} to the map. This is a crucial step to handle cases where a subarray with the required sum 'k' starts from the beginning of the array (index 0).
// 4. Iterate through the input array 'arr' from left to right.
// 5. In each iteration, add the current element to 'cumSum'.
// 6. Check if the map 'map' contains the key 'cumSum - k'.
// 7. If it does, it means there are subarrays ending at the current index with a sum of 'k'. Add the frequency of 'cumSum - k' (i.e., map.get(cumSum - k)) to our 'result'.
// 8. Increment the frequency of the current 'cumSum' in the map using getOrDefault to handle new sums.
// 9. After the loop finishes, return the final 'result'.

// Time Complexity: O(N), where N is the size of the array. This is because we traverse the array only once, and the HashMap operations (insertion and lookup) take O(1) time on average.
// Space Complexity: O(N), where N is the size of the array. In the worst-case scenario, all prefix sums could be unique, requiring the HashMap to store N entries.
class Solution {
    public int cntSubarrays(int arr[], int k) {
        // Use a HashMap to store prefix sums and their frequencies.
        HashMap<Integer, Integer> map = new HashMap<>();
        int result = 0; // Initialize count of subarrays with sum k.

        int cumSum = 0; // This will store the cumulative sum of elements.

        // Insert a prefix sum of 0 with a frequency of 1.
        // This handles subarrays that start from index 0.
        map.put(0, 1);

        // Iterate through the array elements.
        for (int i = 0; i < arr.length; i++) {
            // Update the cumulative sum with the current element.
            cumSum += arr[i];

            // Check if a subarray with sum 'k' ending at the current index exists.
            // This is true if (cumSum - k) has been seen before.
            if (map.containsKey(cumSum - k)) {
                // Add the frequency of (cumSum - k) to the result.
                // Each occurrence of (cumSum - k) represents a valid subarray.
                result += map.get(cumSum - k);
            }

            // Increment the frequency of the current cumulative sum in the map.
            map.put(cumSum, map.getOrDefault(cumSum, 0) + 1);
        }

        // Return the total count of subarrays.
        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Example: arr[] = [10, 2, -2, -20, 10], k = -10
 *
 * Initial State:
 * result = 0
 * cumSum = 0
 * map = {0: 1}
 *
 * Iteration 1 (i=0, arr[i]=10):
 * cumSum = 0 + 10 = 10
 * Check for (cumSum - k) = (10 - (-10)) = 20 in map. Not found.
 * Increment map.get(10). map becomes {0: 1, 10: 1}
 *
 * Iteration 2 (i=1, arr[i]=2):
 * cumSum = 10 + 2 = 12
 * Check for (cumSum - k) = (12 - (-10)) = 22 in map. Not found.
 * Increment map.get(12). map becomes {0: 1, 10: 1, 12: 1}
 *
 * Iteration 3 (i=2, arr[i]=-2):
 * cumSum = 12 - 2 = 10
 * Check for (cumSum - k) = (10 - (-10)) = 20 in map. Not found.
 * Increment map.get(10). map becomes {0: 1, 10: 2, 12: 1}
 *
 * Iteration 4 (i=3, arr[i]=-20):
 * cumSum = 10 - 20 = -10
 * Check for (cumSum - k) = (-10 - (-10)) = 0 in map. Found! map.get(0) is 1.
 * result = result + map.get(0) = 0 + 1 = 1. (Subarray [10, 2, -2, -20] has sum -10)
 * Increment map.get(-10). map becomes {0: 1, 10: 2, 12: 1, -10: 1}
 *
 * Iteration 5 (i=4, arr[i]=10):
 * cumSum = -10 + 10 = 0
 * Check for (cumSum - k) = (0 - (-10)) = 10 in map. Found! map.get(10) is 2.
 * result = result + map.get(10) = 1 + 2 = 3.
 * (Subarray [2, -2, -20, 10] corresponds to the first time prefix sum 10 was seen)
 * (Subarray [-20, 10] corresponds to the second time prefix sum 10 was seen)
 * Increment map.get(0). map becomes {0: 2, 10: 2, 12: 1, -10: 1}
 *
 * End of loop.
 * Final result: 3
 *
 */
