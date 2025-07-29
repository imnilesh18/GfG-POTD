/*
 * GfG Link: https://www.geeksforgeeks.org/problems/ascii-range-sum/1
 *
 * ASCII Range Sum
 *
 * Difficulty: Medium Accuracy: 52.59% Submissions: 14K+ Points: 4
 *
 * Given a string s consisting of lowercase English letters, for every character whose first and last occurrences are at different positions, calculate the sum of ASCII values of characters strictly between its first and last occurrence.
 * Return all such non-zero sums (order does not matter).
 *
 * Examples:
 *
 * Input: s = "abacab"
 * Output: [293, 294]
 * Explanation: characters 'a' and 'b' appear more than once:
 * 'a' : between positions 1 and 5 → characters are b, a, c and ascii sum is 98 + 97 + 99 = 294.
 * 'b' : between positions 2 and 6 → characters are a, c, a and ascii sum is 97 + 99 + 97 = 293.
 *
 * Input: s = "acdac"
 * Output: [197, 199]
 * Explanation: characters 'a' and 'c' appear more than once:
 * 'a' : between positions 1 and 4 → characters are c, d and ascii sum is 99 + 100 = 199.
 * 'c' : between positions 2 and 5 → characters are d, a and ascii sum is 100 + 97 = 197.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Intuition:
// The problem asks for sums of ASCII values in ranges defined by the first and last occurrences of certain characters. Calculating these sums repeatedly for each character can be slow. A more efficient method is to pre-calculate the prefix sums of ASCII values for the entire string. This allows us to find the sum of any sub-range in constant time, which significantly speeds up the process.

// Approach:
// 1. Initialize two arrays, `first` and `last`, of size 26 (for 'a' through 'z') with -1 to store the first and last indices of each character.
// 2. Iterate through the input string `s` once to populate the `first` and `last` index arrays. The first time a character is seen, its `first` index is set. Its `last` index is updated every time it's encountered.
// 3. Create a prefix sum array, `prefix_sum`, of size `n+1`. `prefix_sum[i]` will store the cumulative sum of ASCII values from the start of the string up to index `i-1`.
// 4. Iterate from 'a' to 'z' (i.e., index 0 to 25).
// 5. For each character, check if it appeared more than once by comparing its `first` and `last` indices (`first[i] < last[i]`).
// 6. If it did, calculate the sum of characters strictly between these indices using the prefix sum array. The sum for the range between `start` and `end` is `prefix_sum[end] - prefix_sum[start + 1]`.
// 7. If this sum is non-zero, add it to the result vector.
// 8. Finally, return the vector of sums.

// Time Complexity: O(N), where N is the length of the string.
// We have one pass to find indices (O(N)), one pass to calculate prefix sums (O(N)), and one pass over the 26-character alphabet (O(1)). This results in a total time complexity of O(N).

// Space Complexity: O(N), where N is the length of the string.
// The space is dominated by the prefix sum array, which has a size of N+1. The other arrays for indices are of constant size 26. Thus, the space complexity is O(N).

class Solution {
public:
    vector<int> asciirange(string& s) {
        // code here
        int         n = s.size();  // Get the length of the string.
        vector<int> first(26, -1); // Array to store the first occurrence index of each character.
        vector<int> last(26, -1);  // Array to store the last occurrence index of each character.

        // First pass: Find the first and last indices of each character.
        for (int i = 0; i < n; i++) {
            int char_idx = s[i] - 'a';   // Calculate index for the character (0 for 'a', 1 for 'b', etc.).
            if (first[char_idx] == -1) { // If this is the first time we see this character...
                first[char_idx] = i;     // ...record its index.
            }
            last[char_idx] = i;          // Always update the last seen index for the character.
        }

        // Second pass: Calculate prefix sums of ASCII values.
        vector<int> prefix_sum(n + 1, 0);                  // `prefix_sum[i]` stores sum of ASCIIs from s[0] to s[i-1].
        for (int i = 0; i < n; i++) {
            prefix_sum[i + 1] = prefix_sum[i] + (int)s[i]; // Add current character's ASCII value to the previous sum.
        }

        vector<int> ans; // Vector to store the resulting sums.
        // Iterate through all 26 possible lowercase characters.
        for (int i = 0; i < 26; i++) {
            int start = first[i]; // Get the first occurrence index.
            int end   = last[i];  // Get the last occurrence index.

            // Check if the character appears more than once (first and last positions are different).
            if (start != -1 && start < end) {
                // Calculate the sum of ASCII values strictly between start and end indices.
                // This is the total sum up to index (end-1) minus the total sum up to index start.
                // Using our prefix_sum array: sum = prefix_sum[end] - prefix_sum[start + 1].
                int sum = prefix_sum[end] - prefix_sum[start + 1];

                if (sum > 0) { // As per the problem, only add non-zero sums.
                    ans.push_back(sum);
                }
            }
        }
        return ans; // Return the final list of sums.
    }
};
/*
 *
 * Dry Run
 * Input: s = "abacab"
 *
 * 1. Initialization:
 * n = 6
 * first = [-1, -1, ..., -1] (size 26)
 * last = [-1, -1, ..., -1] (size 26)
 *
 * 2. Find First and Last Indices:
 * i=0, s[0]='a': first[0]=0, last[0]=0
 * i=1, s[1]='b': first[1]=1, last[1]=1
 * i=2, s[2]='a': last[0]=2
 * i=3, s[3]='c': first[2]=3, last[2]=3
 * i=4, s[4]='a': last[0]=4
 * i=5, s[5]='b': last[1]=5
 * Final indices:
 * 'a' (i=0): first=0, last=4
 * 'b' (i=1): first=1, last=5
 * 'c' (i=2): first=3, last=3
 *
 * 3. Calculate Prefix Sums:
 * ASCII values: a=97, b=98, c=99
 * s ASCII: [97, 98, 97, 99, 97, 98]
 * prefix_sum[0] = 0
 * prefix_sum[1] = 0 + 97 = 97
 * prefix_sum[2] = 97 + 98 = 195
 * prefix_sum[3] = 195 + 97 = 292
 * prefix_sum[4] = 292 + 99 = 391
 * prefix_sum[5] = 391 + 97 = 488
 * prefix_sum[6] = 488 + 98 = 586
 * Final prefix_sum: [0, 97, 195, 292, 391, 488, 586]
 *
 * 4. Calculate Range Sums:
 * - For 'a' (i=0):
 * start = 0, end = 4. Condition start < end is true.
 * Sum is for characters between index 0 and 4 -> s[1], s[2], s[3] -> "bac"
 * sum = prefix_sum[end] - prefix_sum[start + 1]
 * sum = prefix_sum[4] - prefix_sum[1] = 391 - 97 = 294.
 * ans = [294]
 *
 * - For 'b' (i=1):
 * start = 1, end = 5. Condition start < end is true.
 * Sum is for characters between index 1 and 5 -> s[2], s[3], s[4] -> "aca"
 * sum = prefix_sum[end] - prefix_sum[start + 1]
 * sum = prefix_sum[5] - prefix_sum[2] = 488 - 195 = 293.
 * ans = [294, 293]
 *
 * - For 'c' (i=2):
 * start = 3, end = 3. Condition start < end is false. Skip.
 *
 * - All other characters were not in the string (start = -1). Skip.
 *
 * 5. Return:
 * ans = [294, 293]
 *
 */

/************************************************************ JAVA ************************************************/

// Intuition:
// The core challenge is to efficiently calculate sums of ASCII values over multiple, specific ranges. A naive approach of re-calculating the sum for each required range would be too slow. The key insight is to pre-compute prefix sums of the string's ASCII values. This powerful technique allows us to find the sum of any sub-string in constant time, leading to a highly efficient overall solution.

// Approach:
// 1. First, we need to identify the start and end points for our sums. We can do this by finding the first and last occurrence indices for every character ('a' to 'z') in the string. Two integer arrays, `first` and `last`, are perfect for this.
// 2. Next, we create a prefix sum array. `prefixSum[i]` will store the cumulative sum of ASCII values from the beginning of the string up to, but not including, index `i`.
// 3. With our pre-computation done, we iterate through all 26 possible lowercase characters.
// 4. For each character that appears at least twice (i.e., its first and last indices are different), we use our `prefixSum` array to calculate the sum of ASCII values strictly between these indices. The sum for a range `(start, end)` is efficiently calculated as `prefixSum[end] - prefixSum[start + 1]`.
// 5. If the calculated sum is non-zero, we add it to our final answer list.
// 6. Finally, we return the list containing all such non-zero sums.

// Time Complexity: O(N), where N is the length of the string.
// We make one pass to find indices (O(N)), a second pass to build the prefix sum array (O(N)), and a final, constant-time pass over the 26-letter alphabet (O(1)). The complexity is thus O(N + N + 26), which simplifies to O(N).

// Space Complexity: O(N), where N is the length of the string.
// The dominant factor in space usage is the prefix sum array, which requires O(N) space. The arrays for storing character indices are of a constant size (26), so they don't affect the overall asymptotic complexity.
class Solution {
    public ArrayList<Integer> asciirange(String s) {
        // code here
        int n = s.length();        // Get the length of the input string.
        int[] first = new int[26]; // Array to store the first occurrence index of each character.
        int[] last  = new int[26]; // Array to store the last occurrence index of each character.

        // Initialize index arrays with -1 to signify that no character has been seen yet.
        Arrays.fill(first, -1);
        Arrays.fill(last, -1);

        // First pass: Find the first and last indices for each character.
        for (int i = 0; i < n; i++) {
            int charIdx = s.charAt(i) - 'a'; // Calculate index for the character (0 for 'a', 1 for 'b', etc.).
            if (first[charIdx] == -1) {      // If this is the first time we see this character...
                first[charIdx] = i;          // ...record its index.
            }
            last[charIdx] = i;               // Always update the last seen index for the character.
        }

        // Second pass: Calculate prefix sums of ASCII values for O(1) range sum queries.
        int[] prefixSum = new int[n + 1]; // prefixSum[i] stores sum of ASCIIs from s[0] to s[i-1].
        for (int i = 0; i < n; i++) {
            // Add current character's ASCII value to the previous sum.
            prefixSum[i + 1] = prefixSum[i] + s.charAt(i);
        }

        ArrayList<Integer> ans = new ArrayList<>(); // To store the results.

        // Iterate through all 26 possible lowercase letters to check each one.
        for (int i = 0; i < 26; i++) {
            int start = first[i]; // Get the first occurrence index.
            int end   = last[i];  // Get the last occurrence index.

            // Check if the character appears more than once (its first and last positions are different).
            if (start != -1 && start < end) {
                // Calculate the sum of characters strictly between start and end.
                // This equals the total sum up to index (end-1) minus the total sum up to index `start`.
                // Using our prefixSum array: sum = prefixSum[end] - prefixSum[start + 1].
                int sum = prefixSum[end] - prefixSum[start + 1];

                if (sum > 0) { // Add non-zero sums to the answer list.
                    ans.add(sum);
                }
            }
        }
        return ans; // Return the final list of sums.
    }
}

/*
 *
 * Dry Run
 * Input: s = "acdac"
 *
 * 1. Initialization:
 * n = 5
 * first = [-1, -1, ..., -1] (size 26)
 * last = [-1, -1, ..., -1] (size 26)
 *
 * 2. Find First and Last Indices:
 * i=0, s[0]='a': first[0]=0, last[0]=0
 * i=1, s[1]='c': first[2]=1, last[2]=1
 * i=2, s[2]='d': first[3]=2, last[3]=2
 * i=3, s[3]='a': last[0]=3
 * i=4, s[4]='c': last[2]=4
 * Final indices:
 * 'a' (i=0): first=0, last=3
 * 'c' (i=2): first=1, last=4
 * 'd' (i=3): first=2, last=2
 *
 * 3. Calculate Prefix Sums:
 * ASCII values: a=97, c=99, d=100
 * s ASCII: [97, 99, 100, 97, 99]
 * prefixSum[0] = 0
 * prefixSum[1] = 0 + 97 = 97
 * prefixSum[2] = 97 + 99 = 196
 * prefixSum[3] = 196 + 100 = 296
 * prefixSum[4] = 296 + 97 = 393
 * prefixSum[5] = 393 + 99 = 492
 * Final prefixSum: [0, 97, 196, 296, 393, 492]
 *
 * 4. Calculate Range Sums:
 * - For 'a' (i=0):
 * start = 0, end = 3. Condition `start < end` is true.
 * Sum is for characters between index 0 and 3 -> s[1], s[2] -> "cd"
 * sum = prefixSum[end] - prefixSum[start + 1]
 * sum = prefixSum[3] - prefixSum[1] = 296 - 97 = 199.
 * ans = [199]
 *
 * - For 'c' (i=2):
 * start = 1, end = 4. Condition `start < end` is true.
 * Sum is for characters between index 1 and 4 -> s[2], s[3] -> "da"
 * sum = prefixSum[end] - prefixSum[start + 1]
 * sum = prefixSum[4] - prefixSum[2] = 393 - 196 = 197.
 * ans = [199, 197]
 *
 * - For 'd' (i=3):
 * start = 2, end = 2. Condition `start < end` is false. Skip.
 *
 * - All other characters were not in the string (start = -1). Skip.
 *
 * 5. Return:
 * ans = [199, 197]
 *
 */
