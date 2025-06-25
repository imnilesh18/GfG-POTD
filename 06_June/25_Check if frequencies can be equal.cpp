/*
 * GfG Link: https://www.geeksforgeeks.org/problems/check-frequencies4211/1
 *
 * Check if frequencies can be equal
 *
 * Difficulty: Medium Accuracy: 16.67% Submissions: 122K+ Points: 4
 *
 * Given a string s consisting only lowercase alphabetic characters, check whether it is possible to remove at most one character such that the  frequency of each distinct character in the string becomes same. Return true if it is possible; otherwise, return false.
 *
 * Examples:
 *
 * Input: s = "xyyz"
 * Output: true
 * Explanation: Removing one 'y' will make frequency of each distinct character to be 1.
 *
 * Input: s = "xyyzz"
 * Output: true
 * Explanation: Removing one 'x' will make frequency of each distinct character to be 2.
 *
 * Input: s = "xxxxyyzz"
 * Output: false
 * Explanation: Frequency can not be made same by removing at most one character.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Count frequency of each character and analyze if at most one character removal can make all frequencies equal.
// Time Complexity: O(n), where n is the length of the string `s`, due to frequency counting.
// Space Complexity: O(1), since we only use a fixed-size array of 26 characters.
class Solution {
public:
    bool sameFreq(string& s) {
        vector<int> freq(26, 0);  // Count frequency of each character (a-z)

        for (char ch : s) {
            freq[ch - 'a']++;  // Increment corresponding index
        }

        int maxFreqValue   = INT_MIN;    // Track the maximum frequency
        int maxFreqCounter = 0;          // Count how many characters have maxFreqValue
        int minFreqValue   = INT_MAX;    // Track the minimum frequency
        int minFreqCounter = 0;          // Count how many characters have minFreqValue

        for (int f : freq) {
            if (f == 0) {
                continue;  // Skip characters not in the string
            }

            if (f == maxFreqValue) {
                maxFreqCounter++;  // If frequency matches max, increment counter
            }

            if (f == minFreqValue) {
                minFreqCounter++;  // If frequency matches min, increment counter
            }

            if (f > maxFreqValue) {
                maxFreqValue   = f;   // Update max frequency
                maxFreqCounter = 1;   // Reset counter for new max
            }

            if (f < minFreqValue) {
                minFreqValue   = f;   // Update min frequency
                minFreqCounter = 1;   // Reset counter for new min
            }
        }

        // Case 1: All characters already have the same frequency
        if ((maxFreqValue - minFreqValue) == 0) {
            return true;
        }
        // Case 2 (Case A or Case B): Only one character has frequency off by 1, or there’s a single char with freq 1
        else if ((maxFreqValue - minFreqValue) == 1 && (maxFreqCounter == 1 ||
                                                        (minFreqValue == 1 && minFreqCounter == 1))) {
            return true;
        }

        return false;  // Not possible by removing only one character
    }
};

/*
 *
 * Dry Run
 * Input: s = "aabbccc"
 *
 * Step 1: Count frequencies:
 * a: 2, b: 2, c: 3
 *
 * freq = [2, 2, 3]
 *
 * minFreqValue = 2, minFreqCounter = 2  (a, b)
 * maxFreqValue = 3, maxFreqCounter = 1  (c)
 *
 * maxFreq - minFreq = 1
 * maxFreqCounter = 1 → Valid Case → Return true
 *
 * Output: true
 */

/*
 *
 * Dry Run
 * Input: s = "aabbccd"
 *
 * Step 1: Count frequencies:
 * a:2, b:2, c:2, d:1
 *
 * freq = [2, 2, 2, 1]
 *
 * minFreqValue = 1, minFreqCounter = 1  (d)
 * maxFreqValue = 2, maxFreqCounter = 3  (a, b, c)
 *
 * maxFreq - minFreq = 1
 * minFreqValue = 1 and minFreqCounter = 1 → Valid Case → Return true
 *
 * Output: true
 */

/************************************************************ JAVA ************************************************/

// Approach: Count frequency of each character and analyze if at most one character removal can make all frequencies equal.
// Time Complexity: O(n), where n is the length of the string `s`, due to frequency counting.
// Space Complexity: O(1), since we only use a fixed-size array of 26 characters.
class Solution {
    boolean sameFreq(String s) {
        int[] freq = new int[26];  // Count frequency of each character (a-z)

        for (char ch : s.toCharArray()) {
            freq[ch - 'a']++;  // Increment corresponding index
        }

        int maxFreqValue   = Integer.MIN_VALUE; // Track the maximum frequency
        int maxFreqCounter = 0;                 // Count how many characters have maxFreqValue
        int minFreqValue   = Integer.MAX_VALUE; // Track the minimum frequency
        int minFreqCounter = 0;                 // Count how many characters have minFreqValue

        for (int f : freq) {
            if (f == 0) {
                continue;  // Skip characters not in the string
            }

            if (f == maxFreqValue) {
                maxFreqCounter++;  // If frequency matches max, increment counter
            }

            if (f == minFreqValue) {
                minFreqCounter++;  // If frequency matches min, increment counter
            }

            if (f > maxFreqValue) {
                maxFreqValue   = f;    // Update max frequency
                maxFreqCounter = 1;    // Reset counter for new max
            }

            if (f < minFreqValue) {
                minFreqValue   = f;    // Update min frequency
                minFreqCounter = 1;    // Reset counter for new min
            }
        }

        // Case 1: All characters already have the same frequency
        if ((maxFreqValue - minFreqValue) == 0) {
            return true;
        }
        // Case 2 (Case A or Case B): Only one character has frequency off by 1, or there’s a single char with freq 1
        else if ((maxFreqValue - minFreqValue) == 1 && (maxFreqCounter == 1 ||
                                                        (minFreqValue == 1 && minFreqCounter == 1))) {
            return true;
        }

        return false;  // Not possible by removing only one character
    }
}

/*
 *
 * Dry Run
 * Input: s = "aabbccc"
 *
 * Step 1: Count frequencies:
 * a: 2, b: 2, c: 3
 *
 * freq = [2, 2, 3]
 *
 * minFreqValue = 2, minFreqCounter = 2  (a, b)
 * maxFreqValue = 3, maxFreqCounter = 1  (c)
 *
 * maxFreq - minFreq = 1
 * maxFreqCounter = 1 → Valid Case → Return true
 *
 * Output: true
 */

/*
 *
 * Dry Run
 * Input: s = "aabbccd"
 *
 * Step 1: Count frequencies:
 * a:2, b:2, c:2, d:1
 *
 * freq = [2, 2, 2, 1]
 *
 * minFreqValue = 1, minFreqCounter = 1  (d)
 * maxFreqValue = 2, maxFreqCounter = 3  (a, b, c)
 *
 * maxFreq - minFreq = 1
 * minFreqValue = 1 and minFreqCounter = 1 → Valid Case → Return true
 *
 * Output: true
 */
