/*
 * GfG Link: https://www.geeksforgeeks.org/problems/police-and-thieves--141631/1
 *
 * Police and Thieves
 *
 * Difficulty: Medium Accuracy: 34.03% Submissions: 29K+ Points: 4
 *
 * Given an array arr[], where each element contains either a 'P' for policeman or a 'T' for thief. Find the maximum number of thieves that can be caught by the police.
 * Keep in mind the following conditions :
 * Each policeman can catch only one thief.
 * A policeman cannot catch a thief who is more than k units away from him.
 *
 * Examples:
 *
 * Input: arr[] = ['P', 'T', 'T', 'P', 'T'], k = 1
 * Output: 2
 * Explanation: Maximum 2 thieves can be caught. First policeman catches first thief and second police man can catch either second or third thief.
 *
 * Input: arr[] = ['T', 'T', 'P', 'P', 'T', 'P'], k = 2
 * Output: 3
 * Explanation: Maximum 3 thieves can be caught.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 ≤ k ≤ 1000
 * arr[i] = 'P' or 'T'
 */

/************************************************************ C++ ************************************************/

// Approach: Use two pointers to scan for the next policeman and the next thief; match them if their indices differ by at most k, otherwise advance the earlier pointer.
// Time Complexity: O(n) – each element is visited at most once by each pointer.
// Space Complexity: O(1) – only a fixed number of integer variables are used.
class Solution {
public:
    int catchThieves(vector<char>& arr, int k) {
        int n     = arr.size();
        int i     = 0;    // pointer to scan for 'P'
        int j     = 0;    // pointer to scan for 'T'
        int count = 0;    // total thieves caught

        while (i < n && j < n) {
            // move i to the next policeman
            while (i < n && arr[i] != 'P') {
                i++;
            }
            // move j to the next thief
            while (j < n && arr[j] != 'T') {
                j++;
            }

            // if both pointers are valid and within k distance, catch!
            if (i < n && j < n && abs(i - j) <= k) {
                count++;
                i++;
                j++;
            }
            // if thief is too far left, move thief pointer right
            else if (j < n && j < i) {
                j++;
            }
            // if policeman is too far left, move policeman pointer right
            else if (i < n && i < j) {
                i++;
            }
        }
        return count;
    }
};

/*
 *
 * Dry Run 1
 * Input: arr[] = ['T','T','P','P','T','P'], k = 2
 * Output: 3
 *
 * Steps:
 * i=0, j=0
 *  skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 *  |2−0|=2≤2 ⇒ count=1; i→3; j→1
 *  skip i stays 3 (arr[3]='P'), skip j stays 1 (arr[1]='T')
 *  |3−1|=2≤2 ⇒ count=2; i→4; j→2
 *  skip i→5 (arr[5]='P'), skip j→4 (arr[4]='T')
 *  |5−4|=1≤2 ⇒ count=3; i→6; j→5
 *  i or j out of range ⇒ end.
 */

/*
 *
 * Dry Run 2
 * Input: arr[] = ['T','T','P','T','T','P','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 *  skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 *  |2−0|=2>1 and j<i ⇒ j→1
 *  |2−1|=1≤1 ⇒ count=1; i→3; j→2
 *  skip i→5 (arr[5]='P'), skip j→3 (arr[3]='T')
 *  |5−3|=2>1 and j<i ⇒ j→4
 *  |5−4|=1≤1 ⇒ count=2; i→6; j→5
 *  i out of range ⇒ end.
 */

/*
 *
 * Dry Run 3
 * Input: arr[] = ['P','P','T','P','T','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 *  skip i stays 0 (arr[0]='P'), skip j→2 (arr[2]='T')
 *  |0−2|=2>1 and i<j ⇒ i→1
 *  skip i stays 1 (arr[1]='P')
 *  |1−2|=1≤1 ⇒ count=1; i→2; j→3
 *  skip i→3 (arr[3]='P'), skip j→4 (arr[4]='T')
 *  |3−4|=1≤1 ⇒ count=2; i→4; j→5
 *  skip i→5 (arr[5]='T')→i→6; end.
 */

/************************************************************ JAVA ************************************************/

// Approach: Use two pointers to scan for the next policeman and the next thief; match them if their indices differ by at most k, otherwise advance the earlier pointer.
// Time Complexity: O(n) – each element is visited at most once by each pointer.
// Space Complexity: O(1) – only a fixed number of integer variables are used.
class Solution {
    public int catchThieves(char[] arr, int k) {
        int n     = arr.length;
        int i     = 0;    // pointer to scan for 'P'
        int j     = 0;    // pointer to scan for 'T'
        int count = 0;    // total thieves caught

        while (i < n && j < n) {
            // move i to the next policeman
            while (i < n && arr[i] != 'P') {
                i++;
            }
            // move j to the next thief
            while (j < n && arr[j] != 'T') {
                j++;
            }

            // if both pointers are valid and within k distance, catch!
            if (i < n && j < n && Math.abs(i - j) <= k) {
                count++;
                i++;
                j++;
            }
            // if thief is too far left, move thief pointer right
            else if (j < n && j < i) {
                j++;
            }
            // if policeman is too far left, move policeman pointer right
            else if (i < n && i < j) {
                i++;
            }
        }
        return count;
    }
}

/*
 *
 * Dry Run 1
 * Input: arr[] = ['T','T','P','P','T','P'], k = 2
 * Output: 3
 *
 * Steps:
 * i=0, j=0
 *  skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 *  |2−0|=2≤2 ⇒ count=1; i→3; j→1
 *  skip i stays 3 (arr[3]='P'), skip j stays 1 (arr[1]='T')
 *  |3−1|=2≤2 ⇒ count=2; i→4; j→2
 *  skip i→5 (arr[5]='P'), skip j→4 (arr[4]='T')
 *  |5−4|=1≤2 ⇒ count=3; i→6; j→5
 *  i or j out of range ⇒ end.
 */

/*
 *
 * Dry Run 2
 * Input: arr[] = ['T','T','P','T','T','P','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 *  skip i→2 (arr[2]='P'), skip j stays 0 (arr[0]='T')
 *  |2−0|=2>1 and j<i ⇒ j→1
 *  |2−1|=1≤1 ⇒ count=1; i→3; j→2
 *  skip i→5 (arr[5]='P'), skip j→3 (arr[3]='T')
 *  |5−3|=2>1 and j<i ⇒ j→4
 *  |5−4|=1≤1 ⇒ count=2; i→6; j→5
 *  i out of range ⇒ end.
 */

/*
 *
 * Dry Run 3
 * Input: arr[] = ['P','P','T','P','T','T'], k = 1
 * Output: 2
 *
 * Steps:
 * i=0, j=0
 *  skip i stays 0 (arr[0]='P'), skip j→2 (arr[2]='T')
 *  |0−2|=2>1 and i<j ⇒ i→1
 *  skip i stays 1 (arr[1]='P')
 *  |1−2|=1≤1 ⇒ count=1; i→2; j→3
 *  skip i→3 (arr[3]='P'), skip j→4 (arr[4]='T')
 *  |3−4|=1≤1 ⇒ count=2; i→4; j→5
 *  skip i→5 (arr[5]='T')→i→6; end.
 */
