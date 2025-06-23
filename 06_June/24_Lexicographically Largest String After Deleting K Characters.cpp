/*
 * GfG Link: https://www.geeksforgeeks.org/problems/lexicographically-largest-string-after-deleting-k-characters/1
 *
 * Lexicographically Largest String After Deleting K Characters
 *
 * Difficulty: Medium Accuracy: 70.41% Submissions: 385+ Points: 4 Average Time: 15m
 *
 * Given a string s consisting of lowercase English letters and an integer k, your task is to remove exactly k characters from the string. The resulting string must be the largest possible in lexicographical  order, while maintain the relative order of the remaining characters.
 *
 * Examples:
 *
 * Input: s = "ritz" ,k = 2
 * Output: tz
 * Explaination:By removing two characters in all possible ways, we get: "ri", "rt", "rz", "it", "iz", and "tz".Among these, "tz" is lexicographically largest string.
 *
 * Input: s = "zebra" ,k = 3
 * Output: zr
 * Explaination:Removing "e", "b", and "a" results in "zr", which is lexicographically largest string.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^5
 * 0 ≤ k< s.size()
 */

/************************************************************ C++ ************************************************/

// Approach: Use a greedy stack-based method to remove smaller preceding characters when a larger character is encountered, ensuring the remaining string of length n-k is lexicographically maximal.
// Time Complexity: O(n) where n = s.length(), since each character is pushed and popped at most once.
// Space Complexity: O(n) for the additional result string.
class Solution {
public:
    string maxSubseq(string& s, int k) {
        int    n        = s.length();
        int    toRemove = k;         // number of characters we still need to remove
        string result   = "";        // acts like a stack to build the answer

        for (int i = 0; i < n; i++) {
            // while we can remove characters, and the current character s[i] is greater
            // than the last in result, pop to make result lexicographically larger
            while (!result.empty() && toRemove > 0 && s[i] > result.back()) {
                result.pop_back();
                toRemove--;
            }
            result.push_back(s[i]); // include current character
        }

        // if we haven't removed enough (e.g., string was non-decreasing), trim from the end
        result.resize(n - k);
        return result;
    }
};

/*
 *
 * Dry Run 1
 *
 * Input: s = "cadbzf", k = 2
 * n = 6, toRemove = 2, result = ""
 * i=0: char='c'; result="" → push 'c' → result="c"
 * i=1: char='a'; 'a'>'c'? No → push 'a' → result="ca"
 * i=2: char='d'; 'd'>'a' & toRemove>0 → pop 'a' (toRemove=1) → result="c"
 *                     'd'>'c' & toRemove>0 → pop 'c' (toRemove=0) → result=""
 *             → push 'd' → result="d"
 * i=3: char='b'; toRemove=0 → push 'b' → result="db"
 * i=4: char='z'; push 'z' → result="dbz"
 * i=5: char='f'; push 'f' → result="dbzf"
 * After loop: resize to n-k = 4 → result="dbzf"
 *
 *
 * Dry Run 2
 *
 * Input: s = "zrptllivngoi", k = 11
 * n = 13, toRemove = 11, result = ""
 * i=0: 'z'; push → "z"
 * i=1: 'r'; 'r'>'z'? No → push → "zr"
 * i=2: 'p'; 'p'>'r'? No → push → "zrp"
 * i=3: 't'; 't'>'p'? Yes & toRemove>0 → pop 'p'(10) → "zr"; 't'>'r'? Yes & toRemove>0 → pop 'r'(9) → "z"; 't'>'z'? No → push 't' → "zt"
 * i=4: 'l'; toRemove=9 → 'l'>'t'? No → push → "ztl"
 * i=5: 'l'; push → "ztll"
 * i=6: 'i'; push → "ztlli"
 * i=7: 'v'; 'v'>'i'? Yes&→pop'i'(8)→"ztll"; 'v'>'l'?Yes&→pop'l'(7)→"ztl"; 'v'>'t'?Yes&→pop't'(6)→"zt"; 'v'>'z'?No→push →"ztv"
 * i=8: 'n'; 'n'>'v'? No → push → "ztvn"
 * i=9: 'g'; push → "ztvng"
 * i=10:'o'; 'o'>'g'?Yes&→pop'g'(5)→"ztvn"; 'o'>'n'?Yes&→pop'n'(4)→"ztv"; 'o'>'v'?No→push →"ztvo"
 * i=11:'i'; push → "ztvoi"
 * i=12:' ' (none) done
 * After loop: result length = 6, resize to n-k = 2 → result="zt"
 */

/************************************************************ JAVA ************************************************/

// Approach: Use a greedy stack-based method to remove smaller preceding characters when a larger character is encountered, ensuring the remaining string of length n-k is lexicographically maximal.
// Time Complexity: O(n) where n = s.length(), since each character is pushed and popped at most once.
// Space Complexity: O(n) for the additional StringBuilder.
class Solution {
    public String maxSubseq(String s, int k) {
        int           n        = s.length();
        int           toRemove = k;                   // number of characters we still need to remove
        StringBuilder result   = new StringBuilder(); // acts like a stack to build the answer

        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            // while we can remove characters, and the current character c is greater
            // than the last in result, pop to make result lexicographically larger
            while (result.length() > 0 && toRemove > 0 && c > result.charAt(result.length() - 1)) {
                result.deleteCharAt(result.length() - 1);
                toRemove--;
            }
            result.append(c); // include current character
        }

        // if we haven't removed enough (e.g., string was non-decreasing), trim from the end
        result.setLength(n - k);
        return result.toString();
    }
}

/*
 *
 * Dry Run 1
 *
 * Input: s = "cadbzf", k = 2
 * n = 6, toRemove = 2, result = ""
 * i=0: c='c'; result="" → append 'c' → result="c"
 * i=1: c='a'; 'a'>'c'? No → append 'a' → result="ca"
 * i=2: c='d'; 'd'>'a' & toRemove>0 → remove 'a' (toRemove=1) → result="c"
 *                       'd'>'c' & toRemove>0 → remove 'c' (toRemove=0) → result=""
 *               → append 'd' → result="d"
 * i=3: c='b'; toRemove=0 → append 'b' → result="db"
 * i=4: c='z'; append 'z' → result="dbz"
 * i=5: c='f'; append 'f' → result="dbzf"
 * After loop: setLength to n-k = 4 → result="dbzf"
 *
 *
 * Dry Run 2
 *
 * Input: s = "zrptllivngoi", k = 11
 * n = 13, toRemove = 11, result = ""
 * i=0: 'z'; append → "z"
 * i=1: 'r'; 'r'>'z'? No → append → "zr"
 * i=2: 'p'; 'p'>'r'? No → append → "zrp"
 * i=3: 't'; 't'>'p'? Yes & toRemove>0 → remove 'p'(10) → "zr"; 't'>'r'? Yes & toRemove>0 → remove 'r'(9) → "z"; 't'>'z'? No → append 't' → "zt"
 * i=4: 'l'; toRemove=9 → 'l'>'t'? No → append → "ztl"
 * i=5: 'l'; append → "ztll"
 * i=6: 'i'; append → "ztlli"
 * i=7: 'v'; 'v'>'i'? Yes&→remove 'i'(8)→"ztll"; 'v'>'l'?Yes&→remove 'l'(7)→"ztl"; 'v'>'t'?Yes&→remove 't'(6)→"zt"; 'v'>'z'?No→append →"ztv"
 * i=8: 'n'; 'n'>'v'? No → append → "ztvn"
 * i=9: 'g'; append → "ztvng"
 * i=10:'o'; 'o'>'g'?Yes&→remove 'g'(5)→"ztvn"; 'o'>'n'?Yes&→remove 'n'(4)→"ztv"; 'o'>'v'?No→append →"ztvo"
 * i=11:'i'; append → "ztvoi"
 * i=12: end loop
 * After loop: length=6, setLength to n-k = 2 → result="zt"
 */
