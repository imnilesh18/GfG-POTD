/*
 * Unique Number III
 *
 * Difficulty: Medium Accuracy: 49.87% Submissions: 60K+ Points: 4 Average Time: 20m
 *
 * Given an array of integers arr[] where, every element appears thrice except for one which occurs once.
 * Find that element which occurs once.
 *
 * Examples:
 *
 * Input: arr[] = [1, 10, 1, 1]
 * Output: 10
 * Explanation: 10 occurs once in the array while the other element 1 occurs thrice.
 *
 * Input: arr[] = [3, 2, 1, 34, 34, 1, 2, 34, 2, 1]
 * Output: 3
 * Explanation: All elements except 3 occurs thrice in the array.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * arr.size() % 3 = 1
 * -10^9 ≤ arr[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Use bitwise counting for each bit position to identify the unique number. For each bit from 0 to 31, count how many numbers in the array have that bit set. If the count modulo 3 is not 0, then the unique number has that bit set.
// Time Complexity: O(32 * n) => O(n), where n is the size of the array, since we check each of the 32 bits for all n elements.
// Space Complexity: O(1), using only a fixed number of integer variables regardless of input size.
class Solution {
public:
    int getSingle(vector<int>& arr) {
        int element = 0;               // This will store the final result
        int mask    = 0;               // To isolate each bit position
        int ones    = 0;               // To count the number of set bits at position i

        for (int i = 0; i < 32; i++) { // Iterate over each bit position (0 to 31)
            ones = 0;
            mask = (1 << i);           // Set mask with a 1 at the ith position
            for (int j = 0; j < arr.size(); j++) {
                if (arr[j] & mask) {   // Check if the ith bit is set in arr[j]
                    ones++;            // Increment count of set bits at ith position
                }
            }
            if ((ones % 3) != 0) {  // If count is not divisible by 3, that bit is set in the unique element
                element |= mask;    // Set the ith bit in the result
            }
        }
        return element;   // Return the element that appears once
    }
};

/*
 *
 * Dry Run
 * Input: arr = [3, 2, 1, 34, 34, 1, 2, 34, 2, 1]
 * Binary Representation:
 * 3  = 00000011
 * 2  = 00000010
 * 1  = 00000001
 * 34 = 00100010
 *
 * Loop over i = 0 to 31:
 * i = 0 (LSB):
 * Count bits set at position 0: 3 (3x from 1s and 1x from 3) => Total = 6 => 6 % 3 == 0 => don't set bit
 * i = 1:
 * Count bits set: 4 => 4 % 3 = 1 => set bit 1 in element => element = 00000010
 * i = 2:
 * Count bits set: 1 (only 3 has it) => 1 % 3 = 1 => set bit 2 => element = 00000110 (6)
 *...
 * Final element becomes 00000011 => 3
 * Output: 3
 */

/************************************************************ JAVA ************************************************/

// Approach: Use bitwise counting for each bit position to identify the unique number. For each bit from 0 to 31, count how many numbers in the array have that bit set. If the count modulo 3 is not 0, then the unique number has that bit set.
// Time Complexity: O(32 * n) => O(n), where n is the size of the array, since we check each of the 32 bits for all n elements.
// Space Complexity: O(1), using only a fixed number of integer variables regardless of input size.
class Solution {
    public int getSingle(int[] arr) {
        int result = 0; // This will store the unique number
        int mask, count;

        for (int i = 0; i < 32; i++) { // Loop through each bit position
            count = 0;
            mask  = (1 << i);          // Create a mask with only ith bit set

            for (int num : arr) {
                if ((num & mask) != 0) { // Check if the ith bit is set in num
                    count++;
                }
            }

            if ((count % 3) != 0) { // If count is not divisible by 3, this bit belongs to the unique number
                result |= mask;     // Set the ith bit in result
            }
        }

        return result; // Return the unique number
    }
}

/*
 *
 * Dry Run
 * Input: arr = [3, 2, 1, 34, 34, 1, 2, 34, 2, 1]
 * Binary Representation:
 * 3  = 00000011
 * 2  = 00000010
 * 1  = 00000001
 * 34 = 00100010
 *
 * Loop over i = 0 to 31:
 * i = 0 (LSB):
 * Count of set bits at bit 0 = 6 => 6 % 3 == 0 => do not set bit
 * i = 1:
 * Count of set bits at bit 1 = 4 => 4 % 3 = 1 => set bit 1 => result = 00000010
 * i = 2:
 * Count of set bits = 1 => 1 % 3 = 1 => set bit 2 => result = 00000110
 *...
 * Final result becomes 00000011 => 3
 * Output: 3
 */
