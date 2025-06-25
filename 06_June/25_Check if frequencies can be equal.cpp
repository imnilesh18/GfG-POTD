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
// Time Complexity: O(n), where n = s.length(), due to single pass over the string and fixed 26-element loop.
// Space Complexity: O(1), using only a fixed-size array of 26 integers.

class Solution {
public:
    bool sameFreq(string& s) {
        vector<int> freq(26, 0);  // Count frequency of each character (a-z)

        for (char ch : s) {
            freq[ch - 'a']++;
        }

        int maxFreqValue   = INT_MIN;  // Track the maximum frequency
        int maxFreqCounter = 0;        // How many chars have that maximum
        int minFreqValue   = INT_MAX;  // Track the minimum frequency (among >0)
        int minFreqCounter = 0;        // How many chars have that minimum

        for (int f : freq) {
            if (f == 0) {
                continue;
            }

            if (f == maxFreqValue) {
                maxFreqCounter++;
            }
            if (f == minFreqValue) {
                minFreqCounter++;
            }
            if (f > maxFreqValue) {
                maxFreqValue = f; maxFreqCounter = 1;
            }
            if (f < minFreqValue) {
                minFreqValue = f; minFreqCounter = 1;
            }
        }

        // Case 1: all frequencies are already the same
        if (maxFreqValue == minFreqValue) {
            return true;
        }
        // Case A: two distinct freqs differ by 1, and the higher one occurs exactly once
        if ((maxFreqValue - minFreqValue) == 1 && maxFreqCounter == 1) {
            return true;
        }
        // Case B: one char has freq==1, and removing it leaves all remaining chars at the same freq
        if (minFreqValue == 1 && minFreqCounter == 1) {
            int nextMin = INT_MAX;
            for (int f : freq) {
                if (f > minFreqValue) {
                    nextMin = min(nextMin, f);
                }
            }
            if (nextMin == maxFreqValue) {
                return true;
            }
        }

        // Otherwise, can't equalize with a single removal
        return false;
    }
};

/*
 *
 * Dry Run
 * Input: s = "aabbccc"
 *
 * freq counts → a:2, b:2, c:3
 * maxFreqValue=3 (c), maxFreqCounter=1
 * minFreqValue=2 (a,b), minFreqCounter=2
 *
 * Case A: max-min = 1 and maxFreqCounter==1 → true
 * Output: true
 */

/*
 *
 * Dry Run
 * Input: s = "aabbccd"
 *
 * freq counts → a:2, b:2, c:2, d:1
 * maxFreqValue=2 (a,b,c), maxFreqCounter=3
 * minFreqValue=1 (d),     minFreqCounter=1
 *
 * Case B: minFreqValue==1 && minFreqCounter==1 → check nextMin among >1 → nextMin=2 == maxFreqValue → true
 * Output: true
 */

/************************************************************ JAVA ************************************************/

// Approach: Count frequency of each character and analyze if at most one character removal can make all frequencies equal.
// Time Complexity: O(n), where n = s.length(), due to single pass over the string and fixed 26-element loop.
// Space Complexity: O(1), using only a fixed-size array of 26 integers.
class Solution {
    boolean sameFreq(String s) {
        int[] freq = new int[26];  // Count frequency of each character (a-z)

        for (char ch : s.toCharArray()) {
            freq[ch - 'a']++;
        }

        int maxFreqValue   = Integer.MIN_VALUE;  // Track the maximum frequency
        int maxFreqCounter = 0;                  // How many chars have that maximum
        int minFreqValue   = Integer.MAX_VALUE;  // Track the minimum frequency (among >0)
        int minFreqCounter = 0;                  // How many chars have that minimum

        for (int f : freq) {
            if (f == 0) {
                continue;
            }

            if (f == maxFreqValue) {
                maxFreqCounter++;
            }
            if (f == minFreqValue) {
                minFreqCounter++;
            }
            if (f > maxFreqValue) {
                maxFreqValue = f; maxFreqCounter = 1;
            }
            if (f < minFreqValue) {
                minFreqValue = f; minFreqCounter = 1;
            }
        }

        // Case 1: all frequencies are already the same
        if (maxFreqValue == minFreqValue) {
            return true;
        }
        // Case A: two distinct freqs differ by 1, and the higher one occurs exactly once
        if ((maxFreqValue - minFreqValue) == 1 && maxFreqCounter == 1) {
            return true;
        }
        // Case B: one char has freq==1, and removing it leaves all remaining chars at the same freq
        if (minFreqValue == 1 && minFreqCounter == 1) {
            int nextMin = Integer.MAX_VALUE;
            for (int f : freq) {
                if (f > minFreqValue) {
                    nextMin = Math.min(nextMin, f);
                }
            }
            if (nextMin == maxFreqValue) {
                return true;
            }
        }

        // Otherwise, can't equalize with a single removal
        return false;
    }
}

/*
 *
 * Dry Run
 * Input: s = "aabbccc"
 *
 * freq counts → a:2, b:2, c:3
 * maxFreqValue=3 (c), maxFreqCounter=1
 * minFreqValue=2 (a,b), minFreqCounter=2
 *
 * Case A: max-min = 1 and maxFreqCounter==1 → true
 * Output: true
 */

/*
 *
 * Dry Run
 * Input: s = "aabbccd"
 *
 * freq counts → a:2, b:2, c:2, d:1
 * maxFreqValue=2 (a,b,c), maxFreqCounter=3
 * minFreqValue=1 (d),     minFreqCounter=1
 *
 * Case B: minFreqValue==1 && minFreqCounter==1 → check nextMin among >1 → nextMin=2 == maxFreqValue → true
 * Output: true
 */
