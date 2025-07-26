/*
 * GfG Link: https://www.geeksforgeeks.org/problems/majority-vote/1
 *
 * Majority Element - More Than n / 3
 *
 * Difficulty: Medium Accuracy: 48.1 % Submissions : 180K + Points : 4 Average Time: 15m
 *
 * Given an array arr[] consisting of n integers, the task is to find all the array elements which occurs more than floor(n / 3) times.
 *
 * Note: The returned array of majority elements should be sorted.
 *
 * Examples:
 *
 * Input: arr[] = [2, 2, 3, 1, 3, 2, 1, 1]
 * Output: [1, 2]
 * Explanation: The frequency of 1 and 2 is 3, which is more than floor n / 3 (8 / 3 = 2).
 *
 * Input:  arr[] = [-5, 3, -5]
 * Output: [-5]
 * Explanation: The frequency of - 5 is 2, which is more than floor n / 3 (3 / 3 = 1).
 *
 * Input:  arr[] = [3, 2, 2, 4, 1, 4]
 * Output: []
 * Explanation: There is no majority element.
 *
 * Constraint:
 * 1 ≤ arr.size() ≤ 10 ^ 6
 * -10 ^ 5 ≤ arr[i] ≤ 10 ^ 5
 */

/************************************************************ C++ ************************************************/

// Approach: This problem is solved using an extended version of the Boyer-Moore Voting Algorithm. Since we need elements appearing more than n/3 times, there can be at most two such majority elements. The algorithm works in two passes. The first pass identifies two potential candidates by maintaining two counters. When we see a number that's not one of our current candidates, we decrement both counters. If a counter is zero, we pick the new number as a candidate. This effectively "cancels out" triplets of distinct numbers. The second pass verifies if these two candidates truly appear more than n/3 times by counting their actual frequencies.
// Time Complexity: O(n), as the algorithm involves two linear passes through the array.
// Space Complexity: O(1), as we only use a constant amount of extra space for counters and candidate variables.
class Solution {
public:
    vector<int> findMajority(vector<int>& arr) {
        int count1 = 0, count2 = 0;
        // ele1 and ele2 will store our two candidates for majority elements.
        int ele1 = 0, el2 = 0;

        // First Pass: Find two potential candidates.
        for (int num : arr) {
            // If count1 is 0 and the current number is not our second candidate,
            // it becomes the new first candidate.
            if (count1 == 0 && num != el2) {
                ele1   = num;
                count1 = 1;
            }
            // If count2 is 0 and the current number is not our first candidate,
            // it becomes the new second candidate.
            else if (count2 == 0 && num != ele1) {
                el2    = num;
                count2 = 1;
            }
            // If the number matches a candidate, increment its count.
            else if (num == ele1) {
                count1++;
            } else if (num == el2) {
                count2++;
            }
            // If the number is different from both candidates, decrement both counts.
            else {
                count1--;
                count2--;
            }
        }

        /*
         *
         * Dry Run for arr[] = [2, 2, 3, 1, 3, 2, 1, 1], n=8, n/3=2
         *
         * 1. First Pass (Finding Candidates):
         * - Initial: ele1=0, count1=0, el2=0, count2=0
         * - num=2: ele1=2, count1=1
         * - num=2: count1=2
         * - num=3: el2=3, count2=1
         * - num=1: count1--, count2-- -> count1=1, count2=0
         * - num=3: count1=1, count2=0. num != ele1. count2==0 -> el2=3, count2=1
         * - num=2: count1++ -> count1=2
         * - num=1: count1--, count2-- -> count1=1, count2=0
         * - num=1: count1=1, count2=0. num != ele1. count2==0 -> el2=1, count2=1
         * - Final Candidates: ele1=2, el2=1
         *
         * 2. Second Pass (Verification):
         * - Reset counts: count1=0, count2=0
         * - Count for ele1 (2): 3 times.
         * - Count for el2 (1): 3 times.
         *
         * 3. Result Generation:
         * - Is count1 (3) > n/3 (2)? Yes. Add 2 to result. result=[2].
         * - Is count2 (3) > n/3 (2)? Yes. Add 1 to result. result=[2, 1].
         * - Sort result: [1, 2].
         *
         */

        // Second Pass: Verify actual counts of the candidates.
        count1 = 0, count2 = 0;
        for (int num : arr) {
            if (num == ele1) {
                count1++;
            }
            if (num == el2) {
                count2++;
            }
        }

        int         votes = arr.size();
        vector<int> result;

        // Add valid candidates to the result if their count > n/3.
        if (count1 > votes / 3) {
            result.push_back(ele1);
        }
        // Ensure we don't add the same element twice if ele1 and el2 ended up being the same.
        if (count2 > votes / 3 && el2 != ele1) {
            result.push_back(el2);
        }

        // Sort the final result as required by the problem statement.
        // A simple swap is enough since there are at most 2 elements.
        if (result.size() == 2 && result[0] > result[1]) {
            swap(result[0], result[1]);
        }

        return result;
    }
};

/************************************************************ JAVA ************************************************/

// Approach: This problem is solved using an extended version of the Boyer-Moore Voting Algorithm. Since we need elements appearing more than n/3 times, there can be at most two such majority elements. The algorithm works in two passes. The first pass identifies two potential candidates by maintaining two counters. When we see a number that's not one of our current candidates, we decrement both counters. If a counter is zero, we pick the new number as a candidate. This effectively "cancels out" triplets of distinct numbers. The second pass verifies if these two candidates truly appear more than n/3 times by counting their actual frequencies.
// Time Complexity: O(n), as the algorithm involves two linear passes through the array.
// Space Complexity: O(1), as we only use a constant amount of extra space for counters and candidate variables.
class Solution {
    public ArrayList<Integer> findMajority(int[] arr) {
        int count1 = 0, count2 = 0;
        // ele1 and el2 will store our two candidates for majority elements.
        // Initialize with a value that might not be in the array, e.g., Integer.MIN_VALUE
        int ele1 = Integer.MIN_VALUE, el2 = Integer.MIN_VALUE;

        // First Pass: Find two potential candidates.
        for (int num : arr) {
            // If count1 is 0 and the current number is not our second candidate,
            // it becomes the new first candidate.
            if (count1 == 0 && num != el2) {
                ele1   = num;
                count1 = 1;
            }
            // If count2 is 0 and the current number is not our first candidate,
            // it becomes the new second candidate.
            else if (count2 == 0 && num != ele1) {
                el2    = num;
                count2 = 1;
            }
            // If the number matches a candidate, increment its count.
            else if (num == ele1) {
                count1++;
            } else if (num == el2) {
                count2++;
            }
            // If the number is different from both candidates, decrement both counts.
            else {
                count1--;
                count2--;
            }
        }

        /*
         *
         * Dry Run for arr[] = [2, 2, 3, 1, 3, 2, 1, 1], n=8, n/3=2
         *
         * 1. First Pass (Finding Candidates):
         * - Initial: ele1=MIN, count1=0, el2=MIN, count2=0
         * - num=2: ele1=2, count1=1
         * - num=2: count1=2
         * - num=3: el2=3, count2=1
         * - num=1: count1--, count2-- -> count1=1, count2=0
         * - num=3: count1=1, count2=0. num != ele1. count2==0 -> el2=3, count2=1
         * - num=2: count1++ -> count1=2
         * - num=1: count1--, count2-- -> count1=1, count2=0
         * - num=1: count1=1, count2=0. num != ele1. count2==0 -> el2=1, count2=1
         * - Final Candidates: ele1=2, el2=1
         *
         * 2. Second Pass (Verification):
         * - Reset counts: count1=0, count2=0
         * - Count for ele1 (2): 3 times.
         * - Count for el2 (1): 3 times.
         *
         * 3. Result Generation:
         * - Is count1 (3) > n/3 (2)? Yes. Add 2 to result. result=[2].
         * - Is count2 (3) > n/3 (2)? Yes. Add 1 to result. result=[2, 1].
         * - Sort result: [1, 2].
         *
         */

        // Second Pass: Verify actual counts of the candidates.
        count1 = 0;
        count2 = 0;
        for (int num : arr) {
            if (num == ele1) {
                count1++;
            }
            if (num == el2) {
                count2++;
            }
        }

        int votes = arr.length;
        ArrayList<Integer> result = new ArrayList<>();

        // Add valid candidates to the result if their count > n/3.
        if (count1 > votes / 3) {
            result.add(ele1);
        }
        // Ensure we don't add the same element twice if ele1 and el2 ended up being the same.
        if (count2 > votes / 3 && el2 != ele1) {
            result.add(el2);
        }

        // Sort the final result as required by the problem statement.
        Collections.sort(result);

        return result;
    }
}
