# 🔠 Word Search

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-32.69%25-blue?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 🧐 Problem Statement

You are given a matrix `mat[][]` of size `n*m` containing English alphabets and a string `word`. Check if the `word` exists on the `mat[][]` or not. The word can be constructed by using letters from adjacent cells, either horizontally or vertically. The same cell cannot be used more than once.

### 📊 Constraints

-   `1 ≤ n, m ≤ 6`
-   `1 ≤ word.size() ≤ 15`
-   `mat` and `word` consists of only lowercase and uppercase English letters.

---

## 📂 Examples

### Example 1

```bash
Input: mat[][] = [['T', 'E', 'E'], ['S', 'G', 'K'], ['T', 'E', 'L']], word = "GEEK"
Output: true
Explanation: Word "GEEK" can be found in the given grid as follows.

```

### Example 2

```bash
Input: mat[][] = [['T', 'E', 'U'], ['S', 'G', 'K'], ['T', 'E', 'L']], word = "GEEK"
Output: false
Explanation: Word "GEEK" cannot be found in the given grid.

```

### Example 3

```bash
Input: mat[][] = [['A', 'B', 'A'], ['B', 'A', 'B']], word = "AB"
Output: true
Explanation: There are multiple ways to construct the word "AB".

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's verify Example 1:

* **Grid**:
```
T E E
S G K
T E L

```


* **Word**: "GEEK"
* **Process**:
1. Start search. Find 'G' at `(1, 1)`.
2. Look neighbors. 'E' found at `(0, 1)` (Up).
3. Look neighbors of `(0, 1)`. 'E' found at `(0, 2)` (Right).
4. Look neighbors of `(0, 2)`. 'K' found at `(1, 2)` (Down).
5. Sequence matched: G -> E -> E -> K. Return `true`.



</details>

---

## 💡 Solution Approaches

### 1️⃣ Backtracking (Depth First Search)

The problem asks to find a specific path in a grid. This is a classic application of **Backtracking**. We iterate through every cell; if a cell matches the first character of the word, we initiate a Depth First Search (DFS). During DFS, we mark the current cell as visited (to avoid reusing it) and explore all four possible directions (Up, Down, Left, Right). If we find the complete word, we return true. If a path fails, we backtrack by unmarking the visited cell.

```cpp
// Intuition: Treat the grid as a graph. Use DFS to explore paths. If a path matches the word, return true. If we hit a dead end, backtrack.
// Approach: Iterate through each cell. If it matches word[0], start DFS. In DFS, mark visited, recurse 4 directions, then unmark (backtrack).
// Time Complexity: O(N * M * 4^L) where N*M is grid size and L is word length. In worst case, we explore 4 directions depth L.
// Space Complexity: O(L) for the recursion stack depth.

class Solution {
  public:
    int m, n;
    vector<vector<int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    bool find(vector<vector<char>>& mat, int i, int j, int idx, string& word) {
        // Base Case: All characters found
        if(idx == word.length()) {
            return true;
        }
        
        // Boundary check, visited check ('$'), or character mismatch
        if(i < 0 || j < 0 || i >= m || j >= n || mat[i][j] == '$') {
            return false;
        }
        
        // Mismatch check (implicit in logic but good for clarity if moved up)
        if(mat[i][j] != word[idx]) {
            return false;
        }
        
        char temp = mat[i][j]; // Store current char
        mat[i][j] = '$';       // Mark as visited
        
        // Explore all 4 directions
        for(auto &dir : directions) {
            int new_i = i + dir[0];
            int new_j = j + dir[1];
            
            // Recurse for next character
            if(find(mat, new_i, new_j, idx + 1, word)){
                return true;
            }
        }
        
        mat[i][j] = temp; // Backtrack: Restore char
        
        return false;
    }
    
    bool isWordExist(vector<vector<char>>& mat, string& word) {
        m = mat.size();
        n = mat[0].size();
        
        // Iterate over every cell to find starting point
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                // If first char matches, start DFS
                if(mat[i][j] == word[0] && find(mat, i, j, 0, word)) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

/*
*
* Dry Run
* Input: mat = {{'A', 'B'}, {'C', 'D'}}, word = "BD"
*
* 1. isWordExist starts. m=2, n=2.
* 2. Loop i=0, j=0: mat[0][0] is 'A'. != word[0] ('B'). Skip.
* 3. Loop i=0, j=1: mat[0][1] is 'B'. == word[0].
* Call find(mat, 0, 1, 0, "BD").
*
* Inside find(0, 1, 0):
* - word[0] 'B' matches mat[0][1].
* - Mark mat[0][1] = '$'.
* - Try directions:
* a. Down (1, 0): new_i=1, new_j=1. Call find(1, 1, 1).
* Inside find(1, 1, 1):
* - mat[1][1] is 'D'. Matches word[1] ('D').
* - Mark mat[1][1] = '$'.
* - Try directions...
* - Next recursive call asks for idx=2.
* - idx (2) == word.length() (2). Return true.
* b. find(1, 1, 1) returned true.
* - find(0, 1, 0) returns true.
*
* 4. isWordExist receives true. Returns true.
* Output: true
*/

```

---

## 🔑 Key Insights

* **Backtracking Strategy**: The core is to temporarily modify the state (mark as visited with `$` or any special char) and revert it after exploring. This ensures that for a specific path, a cell is used only once, but it becomes available again for other potential paths starting from different origins or branching differently.
* **Pruning**: The recursion stops immediately (`return false`) if boundaries are violated or characters don't match, preventing unnecessary calculations.
* **Direction Array**: Using a `directions` vector simplifies the code for checking neighbors compared to writing four separate recursive calls manually.

---

## 🚀 Further Exploration

* **Word Search II**: Find all words from a dictionary in a grid (uses Trie + Backtracking).
* **Number of Islands**: Another classic grid traversal problem.
* **Rat in a Maze**: Pathfinding with constraints.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/word-search/1)

---

## 🙋‍♂️ Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

</div>

> **Educational Purpose Only**: This repository contains solutions for educational purposes. Please use them responsibly and avoid simple copy-pasting for competitive programming. Learning the logic is key!
