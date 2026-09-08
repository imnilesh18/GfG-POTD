# 🔠 Word in Grid - All Occurrences

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy: 22.88%](https://img.shields.io/badge/Accuracy-22.88%25-blue?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-success?style=for-the-badge)
![License: MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a 2D grid `mat[][]` of size `n × m` consisting of characters and a string `word`, find all starting positions where the word occurs in the grid.

* The word can be formed from any cell by moving in any of the **8 directions** (2 horizontal, 2 vertical, and 4 diagonal) in a straight line without changing direction.
* Each cell can be used at most once per occurrence.
* Return all unique starting coordinates in **lexicographically smallest order**.

---

## 💡 Examples

```text
Input: mat[][] = {{a,b,a,b},{a,b,e,b},{e,b,e,b}}, word = "abe"
Output: {{0,0}, {0,2}, {1,0}}
```

```text
Input: mat[][] = {{G,E,E,K,S,F,O,R,G,E,E,K,S}, 
                  {G,E,E,K,S,Q,U,I,Z,G,E,E,K}, 
                  {I,D,E,Q,A,P,R,A,C,T,I,C,E}}, word = "GEEKS"
Output: {{0,0}, {0,8}, {1,0}}
```

<details>
<summary>📖 <strong>Example Breakdown</strong> (Click to expand)</summary>

For the first example: `mat[][] = {{a,b,a,b},{a,b,e,b},{e,b,e,b}}`, `word = "abe"`

* From coordinate `(0,0)`: Moving in the **right-down diagonal** direction, we find 'a' at `(0,0)`, 'b' at `(1,1)`, and 'e' at `(2,2)`. This forms "abe".
* From coordinate `(0,2)`: Moving in the **left-down diagonal** direction, we find 'a' at `(0,2)`, 'b' at `(1,1)`, and 'e' at `(2,0)`. This forms "abe".
* From coordinate `(1,0)`: Moving in the **horizontally right** direction, we find 'a' at `(1,0)`, 'b' at `(1,1)`, and 'e' at `(1,2)`. This forms "abe".

Final Output Coordinates: `{{0,0}, {0,2}, {1,0}}`
</details>

---

## ⚙️ Constraints

> * `1 <= n <= m <= 50`
> * `1 <= |word| <= 20`

---

## 🧠 Solution Approach

### Optimized Directional Search (DFS variant)

We approach this by iterating through every cell in the grid. Whenever we find a character that matches the first letter of our target word, we explore all 8 possible straight-line directions using a predefined direction array. If the subsequent characters match the rest of the word without going out of bounds, we record the starting position.

```cpp
// Intuition: To find the word in the grid, we need to check every cell as a potential starting point. Once the first letter matches, we check all 8 possible straight-line directions to see if the rest of the word follows.
// Approach:
// 1. Loop through every cell (i, j) in the grid.
// 2. If the cell matches the first character of the word, explore all 8 directions using dx and dy arrays.
// 3. For each direction, move step by step and match characters up to the word's length.
// 4. If a full match is found, store the starting coordinates and break to avoid duplicate entries for the same starting cell.
// Time Complexity: O(N * M * L) where N and M are grid dimensions and L is the length of the word. The constant factor 8 is ignored in Big-O.
// Space Complexity: O(1) auxiliary space (excluding the output array) as we only use a few variables.

class Solution {
public:
    vector<vector<int>> searchWord(vector<vector<char>> &mat, string &word) {
        int n = mat.size();
        int m = mat[0].size();
        int len = word.length();
        vector<vector<int>> ans;

        // Arrays to represent the 8 possible directions (horizontal, vertical, diagonal)
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // If the first character matches, check all 8 directions
                if (mat[i][j] == word[0]) {
                    bool found = false;

                    for (int dir = 0; dir < 8; dir++) {
                        int currX = i + dx[dir];
                        int currY = j + dy[dir];
                        int k;

                        // Check if the remaining characters match in the current direction
                        for (k = 1; k < len; k++) {
                            // Boundary checks to ensure we don't go out of grid
                            if (currX < 0 || currX >= n || currY < 0 || currY >= m)
                                break;
                            // Stop checking if character mismatch occurs
                            if (mat[currX][currY] != word[k])
                                break;

                            // Move to the next cell in the same direction
                            currX += dx[dir];
                            currY += dy[dir];
                        }

                        // If the full word was matched in this direction
                        if (k == len) {
                            found = true;
                            break; // Stop searching other directions for this starting cell
                        }
                    }

                    // Add unique starting coordinate
                    if (found) {
                        ans.push_back({i, j});
                    }
                }
            }
        }

        return ans;
    }
};

/*
*
* Dry Run
* 
* Input: mat = {{a,b,a,b},{a,b,e,b},{e,b,e,b}}, word = "abe"
* 
* Step 1: i = 0, j = 0. mat[0][0] == 'a' (Matches word[0]).
*         Check 8 directions.
*         Direction right-down (dx=1, dy=1):
*         k = 1: currX=1, currY=1 -> mat[1][1] == 'b'. Matches.
*         k = 2: currX=2, currY=2 -> mat[2][2] == 'e'. Matches.
*         k = 3: loop ends. Match found!
*         ans = {{0,0}}
* 
* Step 2: i = 0, j = 1. mat[0][1] == 'b'. No match.
* 
* Step 3: i = 0, j = 2. mat[0][2] == 'a' (Matches word[0]).
*         Direction left-down (dx=1, dy=-1):
*         k = 1: currX=1, currY=1 -> mat[1][1] == 'b'. Matches.
*         k = 2: currX=2, currY=0 -> mat[2][0] == 'e'. Matches.
*         Match found! ans = {{0,0}, {0,2}}
* 
* Step 4: i = 1, j = 0. mat[1][0] == 'a' (Matches word[0]).
*         Direction right (dx=0, dy=1):
*         k = 1: currX=1, currY=1 -> mat[1][1] == 'b'. Matches.
*         k = 2: currX=1, currY=2 -> mat[1][2] == 'e'. Matches.
*         Match found! ans = {{0,0}, {0,2}, {1,0}}
* 
* Output: {{0,0}, {0,2}, {1,0}}
*
*/
```

---

## 🔑 Key Insights

* **Direction Arrays:** Using `dx[]` and `dy[]` arrays is an incredibly clean way to traverse 2D grids in multiple directions without writing redundant `if-else` blocks.
* **Early Stopping:** By immediately breaking the inner loops upon going out of bounds or encountering a mismatched character, the algorithm avoids unnecessary computations, optimizing performance.
* **Uniqueness:** Setting `found = true` and `break;` inside the loop ensures that even if a word starts at `(i,j)` and can be formed in multiple directions, the starting coordinate `(i,j)` is only added once to our answer vector.

---

## 🔎 Further Exploration

*   **Boggle (Find all possible words in a board):** A more advanced variation of this problem where paths do not have to be strictly straight lines.
*   **Word Search II (LeetCode):** Finding multiple words simultaneously in a grid using a Trie data structure alongside Backtracking.

---

## 🔗 References

*   **GeeksforGeeks Problem:** [Word in Grid - All Occurrences](https://www.geeksforgeeks.org/problems/find-the-string-in-grid0111/1)
*   **Concepts:** Matrix Traversal, Depth First Search (DFS)

---

## 👨‍💻 Author
**Nilesh Kumar**  
GitHub: [@imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
`#DFS` `#Matrix` `#Recursion` `#GeeksForGeeks` `#C++`