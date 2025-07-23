/*
 * GfG Link: https://www.geeksforgeeks.org/problems/last-moment-before-all-ants-fall-out-of-a-plank/1
 *
 * Last Moment Before All Ants Fall Out
 *
 * Difficulty: Medium Accuracy: 79.99% Submissions: 4K+ Points: 4
 *
 * We have a wooden plank of length n units. Some ants are walking on the plank, each ant moves with a speed of 1 unit per second, with some moving left and others right.
 * When two ants moving in two different directions meet at some point, they change their directions and continue moving again. Assume changing directions does not take any additional time. When an ant reaches one end of the plank at a time t, it falls out of the plank immediately.
 *
 * Given an integer n and two integer arrays left[] and right[], the positions of the ants moving to the left and the right, return the time when the last ant(s) fall out of the plank.
 *
 * Examples :
 *
 * Input: n = 4, left[] = [2], right[] = [0, 1, 3]
 * Output: 4
 * Explanation: As seen in the above image, the last ant falls off the plank at t = 4.
 *
 * Input:  n = 4, left[] = [], right[] = [0, 1, 2, 3, 4]
 * Output: 4
 * Explanation: All ants are going to the right, the ant at index 0 needs 4 seconds to fall.
 * Input: n = 3, left[] = [0], right[] = [3]
 * Output: 0
 * Explanation: The ants will fall off the plank as they are already on the end of the plank.
 *
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 0 ≤ left.length, right.length ≤ n + 1
 * 0 ≤ left[i], right[i] ≤ n
 * 1 ≤ left.length + right.length ≤ n + 1
 * All values of left and right are unique, and each value can appear only in one of the two arrays.
 */

/************************************************************ C++ ************************************************/

// Approach: The key insight is that when ants collide, they change directions. This is physically equivalent to them passing through each other. Therefore, we can ignore collisions. The problem simplifies to finding the maximum time any single ant takes to fall off the plank. An ant at position 'p' moving left takes 'p' seconds. An ant at 'p' moving right takes 'n - p' seconds. The last moment is the maximum of all these individual times.
// Time Complexity: O(L + R), where L and R are the number of ants moving left and right, respectively. We iterate through both arrays once.
// Space Complexity: O(1), as we only use a few variables to store the result.
class Solution {
public:
    int getLastMoment(int n, vector<int>& left, vector<int>& right) {
        int result = 0;

        // For ants moving left, time to fall is their starting position.
        // We need the maximum of these times.
        for (int i = 0; i < left.size(); i++) {
            result = max(result, left[i]);
        }

        // For ants moving right, time to fall is (n - their position).
        // We need the maximum of these times as well.
        for (int i = 0; i < right.size(); i++) {
            result = max(result, n - right[i]);
        }

        // The final result is the maximum time found among all ants.
        return result;
    }
};

/*
 *
 * Dry Run for n = 4, left = [2], right = [0, 1, 3]
 *
 * 1. Initialization:
 * - n = 4
 * - result = 0
 *
 * 2. Process `left` array:
 * - Ant at position 2 is moving left. Time to fall = 2.
 * - result = max(0, 2) = 2.
 *
 * 3. Process `right` array:
 * - Ant at position 0 is moving right. Time to fall = 4 - 0 = 4.
 * - result = max(2, 4) = 4.
 * - Ant at position 1 is moving right. Time to fall = 4 - 1 = 3.
 * - result = max(4, 3) = 4.
 * - Ant at position 3 is moving right. Time to fall = 4 - 3 = 1.
 * - result = max(4, 1) = 4.
 *
 * 4. Final Result:
 * - The function returns `result`, which is 4.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: The key insight is that when ants collide, it's equivalent to them passing through each other. So, we can ignore collisions. The problem becomes finding the maximum time any single ant takes to fall off. An ant at position 'p' moving left takes 'p' seconds. An ant at 'p' moving right takes 'n - p' seconds. The last moment is the maximum of all these times.
// Time Complexity: O(L + R), where L and R are the lengths of the left and right arrays. We perform a single pass over each array.
// Space Complexity: O(1), as no extra space proportional to the input size is used.
class Solution {
    public int getLastMoment(int n, int left[], int right[]) {
        int maxTime = 0;

        // For ants moving left, time to fall is their position.
        // Find the maximum time among them.
        for (int pos : left) {
            maxTime = Math.max(maxTime, pos);
        }

        // For ants moving right, time to fall is (n - position).
        // Find the maximum time among them and update the overall max.
        for (int pos : right) {
            maxTime = Math.max(maxTime, n - pos);
        }

        // The result is the maximum time required by any single ant.
        return maxTime;
    }
}

/*
 *
 * Dry Run for n = 4, left = {2}, right = {0, 1, 3}
 *
 * 1. Initialization:
 * - n = 4
 * - maxTime = 0
 *
 * 2. Process `left` array:
 * - Ant at position 2 moves left. Time = 2.
 * - maxTime = Math.max(0, 2) which is 2.
 *
 * 3. Process `right` array:
 * - Ant at position 0 moves right. Time = 4 - 0 = 4.
 * - maxTime = Math.max(2, 4) which is 4.
 * - Ant at position 1 moves right. Time = 4 - 1 = 3.
 * - maxTime = Math.max(4, 3) which is 4.
 * - Ant at position 3 moves right. Time = 4 - 3 = 1.
 * - maxTime = Math.max(4, 1) which is 4.
 *
 * 4. Final Result:
 * - The method returns `maxTime`, which is 4.
 *
 */
