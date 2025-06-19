/*
 * GfG Link: https://www.geeksforgeeks.org/problems/case-specific-sorting-of-strings4845/1
 *
 * Case-specific Sorting of Strings
 *
 * Difficulty: Medium Accuracy: 69.88% Submissions: 62K+ Points: 4 Average Time: 45m
 *
 * Given a string s consisting of only uppercase and lowercase characters. The task is to sort uppercase and lowercase letters separately such that if the ith place in the original string had an Uppercase character then it should not have a lowercase character after being sorted and vice versa.
 *
 * Examples :
 *
 * Input: s = "GEekS"
 * Output: EGekS
 * Explanation: Sorted form of given string with the same case of character will result in output as EGekS.
 *
 * Input: s = "XWMSPQ"
 * Output: MPQSWX
 * Explanation: Since all characters are of the same case We can simply perform a sorting operation on the entire string.
 *
 * Constraints:
 * 1 ≤ s.length() ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: Separate lowercase and uppercase letters, sort each group, then rebuild the string by choosing from the appropriate sorted group based on the original character’s case.
// Time Complexity: O(n + k log k) where n = length of s, k is roughly n/2 for each group; overall dominated by sorting at O(n log n).
// Space Complexity: O(n) extra space for the two buckets storing characters.
class Solution {
public:
    string caseSort(string& s) {
        int n = s.length();

        vector<char> lower;  // to hold all lowercase letters
        vector<char> upper;  // to hold all uppercase letters

        // 1) Partition into lowercase and uppercase buckets
        for (char ch : s) {
            if (islower(ch)) {
                lower.push_back(ch);
            } else {
                upper.push_back(ch);
            }
        }

        // 2) Sort both buckets independently
        sort(lower.begin(), lower.end());
        sort(upper.begin(), upper.end());

        // 3) Reconstruct result by consuming from sorted buckets
        string result = s;  // initialize result with original size
        int    l      = 0;  // index for lowercase bucket
        int    u      = 0;  // index for uppercase bucket

        for (int i = 0; i < n; i++) {
            if (islower(s[i])) {
                result[i] = lower[l++];  // place next sorted lowercase
            } else {
                result[i] = upper[u++];  // place next sorted uppercase
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "dCbA"
 *
 * Step 1: Partition
 *   lower = ['d','b']
 *   upper = ['C','A']
 *
 * Step 2: Sort buckets
 *   lower -> ['b','d']
 *   upper -> ['A','C']
 *
 * Step 3: Reconstruct result
 *   i=0: s[0]='d' is lower -> result[0] = lower[0] = 'b'
 *   i=1: s[1]='C' is upper -> result[1] = upper[0] = 'A'
 *   i=2: s[2]='b' is lower -> result[2] = lower[1] = 'd'
 *   i=3: s[3]='A' is upper -> result[3] = upper[1] = 'C'
 *
 * Final result = "bAdC"
 */

// Approach 2: Count lowercase and uppercase letters using fixed-size frequency arrays, then rebuild the string by picking the next available character from the corresponding frequency array in order.
// Time Complexity: O(n + 26) ⇒ O(n), where n = length of s.
// Space Complexity: O(1) extra space for two fixed-size arrays of length 26.
class Solution {
public:
    string caseSort(string& s) {
        int n = s.size();

        int lower[26] = { 0 };
        int upper[26] = { 0 };

        // 1) Count frequencies
        for (char ch : s) {
            if (islower(ch)) {
                lower[ch - 'a']++;
            } else {
                upper[ch - 'A']++;
            }
        }

        // 2) Reconstruct result by consuming counts
        string result = s;
        int    l      = 0; // index for lowercase freq array
        int    u      = 0; // index for uppercase freq array

        for (int i = 0; i < n; i++) {
            if (islower(s[i])) {
                while (lower[l] == 0) {
                    l++;
                }
                result[i] = 'a' + l;
                lower[l]--;
            } else {
                while (upper[u] == 0) {
                    u++;
                }
                result[i] = 'A' + u;
                upper[u]--;
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "dCbA"
 *
 * Step 1: Count frequencies
 *   lower['d'-'a']=1, lower['b'-'a']=1
 *   upper['C'-'A']=1, upper['A'-'A']=1
 *
 * lower = [b:1, d:1], upper = [A:1, C:1]
 *
 * Step 2: Reconstruct result
 *   i=0: s[0]='d' is lower
 *         l=0 -> lower[0]=0, l=1 -> lower[1]=1
 *         result[0]='a'+1='b', lower[1]→0
 *   i=1: s[1]='C' is upper
 *         u=0 -> upper[0]=1
 *         result[1]='A'+0='A', upper[0]→0
 *   i=2: s[2]='b' is lower
 *         l=1 -> lower[1]=0, l=2 -> lower[2]=1
 *         result[2]='a'+2='c'?
 *         (Note: here lower indices correspond: a→0,b→1,c→2,d→3. Actually b at index1 consumed, so next nonzero is at index3.)
 *         Correct scan: l moves to 3 → lower[3]=1
 *         result[2]='a'+3='d', lower[3]→0
 *   i=3: s[3]='A' is upper
 *         u=0 -> upper[0]=0, u=1 -> upper[1]=0, u=2 -> upper[2]=1
 *         result[3]='A'+2='C', upper[2]→0
 *
 * Final result = "bAdC"
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Separate lowercase and uppercase letters into two lists, sort each list, then rebuild the string by picking from the appropriate sorted list based on the original character’s case.
// Time Complexity: O(n + k log k) where n = length of s, k ≈ n/2 for each list; overall dominated by sorting at O(n log n).
// Space Complexity: O(n) extra space for the two lists storing characters.
class Solution {
    public static String caseSort(String s) {
        int n = s.length();

        List<Character> lower = new ArrayList<>();  // to hold all lowercase letters
        List<Character> upper = new ArrayList<>();  // to hold all uppercase letters

        // 1) Partition into lowercase and uppercase lists
        for (char ch : s.toCharArray()) {
            if (Character.isLowerCase(ch)) {
                lower.add(ch);
            } else {
                upper.add(ch);
            }
        }

        // 2) Sort both lists independently
        Collections.sort(lower);
        Collections.sort(upper);

        // 3) Reconstruct result by consuming from sorted lists
        StringBuilder result = new StringBuilder(n);
        int           l      = 0; // index for lowercase list
        int           u      = 0; // index for uppercase list

        for (char ch : s.toCharArray()) {
            if (Character.isLowerCase(ch)) {
                result.append(lower.get(l++));  // place next sorted lowercase
            } else {
                result.append(upper.get(u++));  // place next sorted uppercase
            }
        }

        return result.toString();
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "dCbA"
 *
 * Step 1: Partition
 *   lower = ['d','b']
 *   upper = ['C','A']
 *
 * Step 2: Sort lists
 *   lower -> ['b','d']
 *   upper -> ['A','C']
 *
 * Step 3: Reconstruct result
 *   i=0: ch='d' is lower -> append lower[0] = 'b'
 *   i=1: ch='C' is upper -> append upper[0] = 'A'
 *   i=2: ch='b' is lower -> append lower[1] = 'd'
 *   i=3: ch='A' is upper -> append upper[1] = 'C'
 *
 * Final result = "bAdC"
 */

// Approach 2: Count lowercase and uppercase letters using two size-26 arrays, then rebuild the string by selecting the next character from the appropriate count array in order.
// Time Complexity: O(n + 26) ⇒ O(n), where n = length of s.
// Space Complexity: O(1) extra space for two fixed-size int arrays of length 26.
class Solution {
    public static String caseSort(String s) {
        int n = s.length();

        int[] lower = new int[26];
        int[] upper = new int[26];

        // 1) Count frequencies
        for (char ch : s.toCharArray()) {
            if (Character.isLowerCase(ch)) {
                lower[ch - 'a']++;
            } else {
                upper[ch - 'A']++;
            }
        }

        // 2) Reconstruct result by consuming counts
        StringBuilder result = new StringBuilder(n);
        int           l      = 0; // pointer for lowercase freq
        int           u      = 0; // pointer for uppercase freq

        for (char ch : s.toCharArray()) {
            if (Character.isLowerCase(ch)) {
                while (lower[l] == 0) {
                    l++;
                }
                result.append((char)('a' + l));
                lower[l]--;
            } else {
                while (upper[u] == 0) {
                    u++;
                }
                result.append((char)('A' + u));
                upper[u]--;
            }
        }

        return result.toString();
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "dCbA"
 *
 * Step 1: Count frequencies
 *   lower['d'-'a']=1, lower['b'-'a']=1
 *   upper['C'-'A']=1, upper['A'-'A']=1
 *
 * lower = [b:1, d:1], upper = [A:1, C:1]
 *
 * Step 2: Reconstruct result
 *   i=0: ch='d' is lower
 *         l=0 -> lower[0]=0, l=1 -> lower[1]=1
 *         append 'a'+1='b', lower[1]=0
 *   i=1: ch='C' is upper
 *         u=0 -> upper[0]=1
 *         append 'A'+0='A', upper[0]=0
 *   i=2: ch='b' is lower
 *         l=1 -> lower[1]=0, l=2->0, l=3->1
 *         append 'a'+3='d', lower[3]=0
 *   i=3: ch='A' is upper
 *         u=0->0, u=1->0, u=2->1
 *         append 'A'+2='C', upper[2]=0
 *
 * Final result = "bAdC"
 */
