/*
 * GfG Link: https://www.geeksforgeeks.org/problems/remove-the-balls--170647/1
 *
 * Remove the balls
 *
 * Difficulty: Medium Accuracy: 58.66% Submissions: 28K+ Points: 4
 *
 * You are given two arrays, color and radius, representing a sequence of balls:
 * color[i] is the color of the i-th ball.
 * radius[i] is the radius of the i-th ball.
 * If two consecutive balls have the same color and radius, remove them both. Repeat this process until no more such pairs exist.
 * Return the number of balls remaining after all possible removals.
 *
 * Examples:
 *
 * Input: color[] = [2, 3, 5], radius[] = [3, 3, 5]
 * Output: 3
 * Explanation: All the 3 balls have different colors and radius.
 *
 * Input: color[] = [2, 2, 5], radius[] = [3, 3, 5]
 * Output: 1
 * Explanation: First ball and second ball have same color 2 and same radius 3. So, after removing only one ball is left. It cannot be removed from the array. Hence, the final array has length 1.
 *
 * Constraints:
 * 1 ≤ color.size() = radius.size() ≤ 10^5
 * 1 ≤ color[i] ≤ 10^9
 * 1 ≤ radius[i] ≤ 10^9
 */

/************************************************************ C++ ************************************************/

// Approach: Use a stack to simulate pair removals — if the top of the stack has same color and radius as current, pop it, else push current index.
// Time Complexity: O(n) — Each element is pushed and popped at most once.
// Space Complexity: O(n) — In worst case, all elements are unique and stored in the stack.
class Solution {
public:
    int findLength(vector<int>& color, vector<int>& radius) {
        int n = color.size(); // Total number of balls

        stack<int> st;        // Stack to keep indices of non-removed balls

        for (int i = 0; i < n; i++) {
            // If top of stack has same color and radius → remove both
            if (!st.empty() && color[i] == color[st.top()] && radius[i] == radius[st.top()]) {
                st.pop();   // Remove the matched pair
            } else {
                st.push(i); // Otherwise, keep the current ball
            }
        }

        return st.size(); // Remaining balls after all removals
    }
};

/*
 *
 * Dry Run
 * Input: color = [1, 1, 2, 3, 3, 2], radius = [2, 2, 3, 4, 4, 3]
 *
 * Step-by-step execution:
 * i = 0 → (1,2) → stack is empty → push index 0 → stack = [0]
 * i = 1 → (1,2) == color[0],radius[0] → pop → stack = []
 * i = 2 → (2,3) → stack is empty → push index 2 → stack = [2]
 * i = 3 → (3,4) → not same as color[2],radius[2] → push index 3 → stack = [2,3]
 * i = 4 → (3,4) == color[3],radius[3] → pop → stack = [2]
 * i = 5 → (2,3) == color[2],radius[2] → pop → stack = []
 *
 * Final stack is empty → return 0
 *
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a stack to simulate pair removals — if the top of the stack has same color and radius as current, pop it, else push current index.
// Time Complexity: O(n) — Each element is pushed and popped at most once.
// Space Complexity: O(n) — In worst case, all elements are unique and stored in the stack.
class Solution {
    public int findLength(int[] color, int[] radius) {
        int n = color.length;              // Total number of balls

        Stack<Integer> st = new Stack<>(); // Stack to keep indices of balls

        for (int i = 0; i < n; i++) {
            // Check if current ball matches the top of the stack
            if (!st.isEmpty() &&
                color[i] == color[st.peek()] &&
                radius[i] == radius[st.peek()]) {
                st.pop();   // Remove matching pair
            } else {
                st.push(i); // Keep current ball index
            }
        }

        return st.size(); // Remaining balls after all removals
    }
}

/*
 *
 * Dry Run
 * Input: color = [1, 1, 2, 3, 3, 2], radius = [2, 2, 3, 4, 4, 3]
 *
 * Step-by-step execution:
 * i = 0 → (1,2) → stack is empty → push index 0 → stack = [0]
 * i = 1 → (1,2) == color[0],radius[0] → pop → stack = []
 * i = 2 → (2,3) → stack is empty → push index 2 → stack = [2]
 * i = 3 → (3,4) → not same as color[2],radius[2] → push index 3 → stack = [2,3]
 * i = 4 → (3,4) == color[3],radius[3] → pop → stack = [2]
 * i = 5 → (2,3) == color[2],radius[2] → pop → stack = []
 *
 * Final stack is empty → return 0
 *
 *
 */
