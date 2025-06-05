/*
 * GfG Link: https://www.geeksforgeeks.org/problems/count-the-paths4332/1
 *
 * Count the paths
 *
 * Difficulty: Medium Accuracy: 42.71% Submissions: 37K+ Points: 4 Average Time: 10m
 *
 * Given a Directed Acyclic Graph (DAG) with V nodes labeled from 0 to V-1, and a list of directed edges, count the total number of distinct paths from a given start node to a destination node. Each edge is represented as edges[i] = [u, v], indicating a directed edge from u to v.
 *
 * Examples :
 *
 * Input: edges[][] = [[0,1], [0,3], [2,0], [2,1], [1,3]], V = 4, src = 2, dest = 3
 * Output: 3
 * Explanation: There are three ways to reach at 3 from 2. These are: 2 -> 1 -> 3, 2 -> 0 -> 3 and 2 -> 0 -> 1 -> 3.
 * Print-all-paths-1
 *
 * Input: edges[][] = [[0,1], [1,2], [1,3], [2,3]], V = 4, src = 0, dest = 3
 * Output: 2
 * Explanation: There is two way to reach at 3 from 0 that is : 0 -> 1 -> 2 -> 3 and 0 -> 1 -> 3.
 * Print-all-paths-2
 *
 * Constraints:
 * 2  ≤  V  ≤  10^3
 * 1  ≤   E = edges.size()  ≤  (V * (V - 1)) / 2
 */

/************************************************************ C++ ************************************************/

// Approach: Use DFS with memoization (top-down DP) to count all distinct paths from src to dest in a DAG.
// Time Complexity: O(V + E) in the worst case since each node and edge is visited once due to memoization.
// Space Complexity: O(V + E) for adjacency list and dp array.
class Solution {
public:
    // Recursive DFS function to count paths from u to dest
    int dfs(int u, int dest, vector<vector<int> >& adj, vector<int>& dp) {
        // Base Case: If current node is destination, count as 1 path
        if (u == dest) {
            return 1;
        }

        // If result already computed for u, return it
        if (dp[u] != -1) {
            return dp[u];
        }

        int count = 0;

        // Explore all neighbors of current node u
        for (int v : adj[u]) {
            count += dfs(v, dest, adj, dp);  // Recursive call to child node v
        }

        // Store result in dp array before returning
        return dp[u] = count;  // Total paths from u to dest
    }
    int countPaths(vector<vector<int> >& edges, int V, int src, int dest) {
        // Step 1: Build adjacency list from edge list
        vector<vector<int> > adj(V);  // Adjacency list

        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);  // Directed edge u -> v
        }

        // Step 2: Initialize dp array with -1 to represent uncomputed states
        vector<int> dp(1001, -1);

        // Step 3: Start DFS from source to destination
        return dfs(src, dest, adj, dp);
    }
};

/*
 *
 * Dry Run
 *
 * Input: edges = [[0,1], [0,3], [2,0], [2,1], [1,3]], V = 4, src = 2, dest = 3
 *
 * Build adjacency list:
 * adj[0] = [1, 3]
 * adj[1] = [3]
 * adj[2] = [0, 1]
 *
 * Call dfs(2, 3)
 *   -> u=2, not dest, dp[2] = -1
 *   -> neighbors: 0 and 1
 *       -> dfs(0, 3)
 *           -> u=0, not dest, dp[0] = -1
 *           -> neighbors: 1 and 3
 *               -> dfs(1, 3)
 *                   -> u=1, not dest, dp[1] = -1
 *                   -> neighbor: 3
 *                       -> dfs(3, 3) => base case hit => return 1
 *                   -> dp[1] = 1
 *               -> dfs(3, 3) => base case hit => return 1
 *           -> total for dp[0] = 1 (from 1->3) + 1 (direct 0->3) = 2
 *       -> dfs(1, 3) => dp[1] = 1 (memoized)
 *   -> total for dp[2] = 2 (via 0) + 1 (via 1) = 3
 *
 * Final answer = 3
 * Output: 3
 */

/************************************************************ JAVA ************************************************/

// Approach: Use DFS with memoization (top-down DP) to count all distinct paths from src to dest in a DAG.
// Time Complexity: O(V + E) in the worst case since each node and edge is visited once due to memoization.
// Space Complexity: O(V + E) for adjacency list and dp array.
class Solution {
    // Recursive DFS function to count paths from u to dest
    public int dfs(int u, int dest, List<List<Integer> > adj, int[] dp) {
        // Base Case: If current node is destination, count as 1 path
        if (u == dest) {
            return 1;
        }

        // If result already computed for u, return it
        if (dp[u] != -1) {
            return dp[u];
        }

        int count = 0;

        // Explore all neighbors of current node u
        for (int v : adj.get(u)) {
            count += dfs(v, dest, adj, dp);  // Recursive call to child node v
        }

        // Store result in dp array before returning
        return dp[u] = count;  // Total paths from u to dest
    }
    public int countPaths(int[][] edges, int V, int src, int dest) {
        // Step 1: Build adjacency list from edge list
        List<List<Integer> > adj = new ArrayList<>();

        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        for (int i = 0; i < edges.length; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            adj.get(u).add(v);  // Directed edge u -> v
        }

        // Step 2: Initialize dp array with -1 to represent uncomputed states
        int[] dp = new int[1001];
        Arrays.fill(dp, -1);

        // Step 3: Start DFS from source to destination
        return dfs(src, dest, adj, dp);
    }
}

/*
 *
 * Dry Run
 *
 * Input: edges = [[0,1], [0,3], [2,0], [2,1], [1,3]], V = 4, src = 2, dest = 3
 *
 * Build adjacency list:
 * adj[0] = [1, 3]
 * adj[1] = [3]
 * adj[2] = [0, 1]
 *
 * Call dfs(2, 3)
 *   -> u=2, not dest, dp[2] = -1
 *   -> neighbors: 0 and 1
 *       -> dfs(0, 3)
 *           -> u=0, not dest, dp[0] = -1
 *           -> neighbors: 1 and 3
 *               -> dfs(1, 3)
 *                   -> u=1, not dest, dp[1] = -1
 *                   -> neighbor: 3
 *                       -> dfs(3, 3) => base case hit => return 1
 *                   -> dp[1] = 1
 *               -> dfs(3, 3) => base case hit => return 1
 *           -> total for dp[0] = 1 (from 1->3) + 1 (direct 0->3) = 2
 *       -> dfs(1, 3) => dp[1] = 1 (memoized)
 *   -> total for dp[2] = 2 (via 0) + 1 (via 1) = 3
 *
 * Final answer = 3
 * Output: 3
 */
