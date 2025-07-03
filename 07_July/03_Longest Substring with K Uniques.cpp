/*
 * GfG Link: https://www.geeksforgeeks.org/problems/longest-k-unique-characters-substring0853/1
 *
 * Longest Substring with K Uniques
 *
 * Difficulty: Medium Accuracy: 34.65% Submissions: 200K+ Points: 4
 *
 * You are given a string s consisting only lowercase alphabets and an integer k. Your task is to find the length of the longest substring that contains exactly k distinct characters.
 *
 * Note : If no such substring exists, return -1.
 *
 * Examples:
 *
 * Input: s = "aabacbebebe", k = 3
 * Output: 7
 * Explanation: The longest substring with exactly 3 distinct characters is "cbebebe", which includes 'c', 'b', and 'e'.
 *
 * Input: s = "aaaa", k = 2
 * Output: -1
 * Explanation: There's no substring with 2 distinct characters.
 *
 * Input: s = "aabaaab", k = 2
 * Output: 7
 * Explanation: The entire string "aabaaab" has exactly 2 unique characters 'a' and 'b', making it the longest valid substring.
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 10^5
 * 1 ≤ k ≤ 26
 */

/************************************************************ C++ ************************************************/

// Approach: Use sliding window with two pointers and a frequency map to maintain exactly k distinct characters in the window; expand right pointer, shrink left when distinct count exceeds k, and update max length when count == k.
// Time Complexity: O(n), where n = s.length(), since each character is processed at most twice (once by j and once by i).
// Space Complexity: O(1) (bounded by alphabet size 26), for the unordered_map storing character frequencies.
class Solution {
public:
    int longestKSubstr(string& s, int k) {
        int n = s.length();
        unordered_map<char, int> mp; // map to store frequency of chars in current window

        int i = 0;                   // left pointer of window
        int j = 0;                   // right pointer of window

        int result = -1;             // store max length found

        while (j < n) {
            mp[s[j]]++;   // include s[j] in window

            // if more than k distinct, shrink from left
            if (mp.size() > k) {
                mp[s[i]]--;          // decrement freq of s[i]
                if (mp[s[i]] == 0) { // if freq becomes 0, remove from map
                    mp.erase(s[i]);
                }
                i++;               // move left pointer
            }

            // if exactly k distinct, update result
            if (mp.size() == k) {
                result = max(result, j - i + 1);
            }
            j++;  // expand right pointer
        }
        return result;
    }
};

/*
 *
 * Dry Run on Input: s = "aabacbebebe", k = 3
 *
 * i=0, j=0: window="a", mp={a:1}         => size=1 < 3, result stays -1
 * i=0, j=1: window="aa", mp={a:2}        => size=1 < 3, result stays -1
 * i=0, j=2: window="aab", mp={a:2,b:1}   => size=2 < 3, result stays -1
 * i=0, j=3: window="aaba", mp={a:3,b:1}  => size=2 < 3, result stays -1
 * i=0, j=4: window="aabac", mp={a:3,b:1,c:1} => size=3 == 3, result = 5
 * i=0, j=5: window="aabacb", mp={a:3,b:2,c:1} => size=3 == 3, result = 6
 * i=0, j=6: window="aabacbe", mp={a:3,b:2,c:1,e:1} => size=4 > 3
 *   shrink: remove s[0]='a' -> mp={a:2,b:2,c:1,e:1}, i=1 => size=4 >3
 *   shrink: remove s[1]='a' -> mp={a:1,b:2,c:1,e:1}, i=2 => size=4 >3
 *   shrink: remove s[2]='b' -> mp={a:1,b:1,c:1,e:1}, i=3 => size=4 >3
 *   shrink: remove s[3]='a' -> mp={a:0->erase,b:1,c:1,e:1}, i=4 => size=3
 * window="cb e", now size==3, result stays 6
 * i=4, j=6 window="cb e": length= j-i+1 = 6-4+1=3, result=6
 * i=4, j=7: include 'b' -> mp={c:1,e:1,b:2}, size=3, result = max(6,7-4+1=4)=6
 * i=4, j=8: include 'e' -> mp={c:1,e:2,b:2}, size=3, result = max(6,8-4+1=5)=6
 * i=4, j=9: include 'b' -> mp={c:1,e:2,b:3}, size=3, result = max(6,9-4+1=6)=6
 * i=4, j=10: include 'e' -> mp={c:1,e:3,b:3}, size=3, result = max(6,10-4+1=7)=7
 *
 * Final result = 7 (substring "cbebebe")
 */

/************************************************************ JAVA ************************************************/

// Approach: Use sliding window with two pointers and a frequency map to maintain exactly k distinct characters in the window; expand right pointer, shrink left when distinct count exceeds k, and update max length when count == k.
// Time Complexity: O(n), where n = s.length(), since each character is processed at most twice (once by j and once by i).
// Space Complexity: O(1) (bounded by alphabet size 26), for the HashMap storing character frequencies.
class Solution {
    public int longestKSubstr(String s, int k) {
        int n = s.length();
        Map<Character, Integer> mp = new HashMap<>(); // map to store frequency of chars in current window

        int i = 0;                                    // left pointer of window
        int j = 0;                                    // right pointer of window

        int result = -1;                              // store max length found

        while (j < n) {
            // include s.charAt(j) in window
            char cj = s.charAt(j);
            mp.put(cj, mp.getOrDefault(cj, 0) + 1);

            // if more than k distinct, shrink from left
            if (mp.size() > k) {
                char ci = s.charAt(i);
                mp.put(ci, mp.get(ci) - 1);         // decrement freq of s.charAt(i)
                if (mp.get(ci) == 0) {              // if freq becomes 0, remove from map
                    mp.remove(ci);
                }
                i++;                                // move left pointer
            }

            // if exactly k distinct, update result
            if (mp.size() == k) {
                result = Math.max(result, j - i + 1);
            }
            j++; // expand right pointer
        }

        return result;
    }
}

/*
 *
 * Dry Run on Input: s = "aabacbebebe", k = 3
 *
 * i=0, j=0: window="a", mp={a=1}             => size=1 < 3, result stays -1
 * i=0, j=1: window="aa", mp={a=2}            => size=1 < 3, result stays -1
 * i=0, j=2: window="aab", mp={a=2,b=1}       => size=2 < 3, result stays -1
 * i=0, j=3: window="aaba", mp={a=3,b=1}      => size=2 < 3, result stays -1
 * i=0, j=4: window="aabac", mp={a=3,b=1,c=1} => size=3 == 3, result = 5
 * i=0, j=5: window="aabacb", mp={a=3,b=2,c=1}=> size=3 == 3, result = 6
 * i=0, j=6: window="aabacbe", mp={a=3,b=2,c=1,e=1} => size=4 > 3
 *   shrink: remove s[0]='a' -> mp={a=2,b=2,c=1,e=1}, i=1 => size=4 > 3
 * i=1, j=6 window="abacbe"
 *   (only one shrink per iteration as per code)
 * if size still > k, window will shrink further in subsequent j-iterations
 *   after this iteration size=4 so result not updated
 * i=1, j=7: include 'b' -> mp={a=2,b=3,c=1,e=1}, size=4 > 3
 *   shrink: remove s[1]='a' -> mp={a=1,b=3,c=1,e=1}, i=2 => size=4 > 3
 * i=2, j=7 window="bacbeb"
 * i=2, j=8: include 'e' -> mp={a=1,b=3,c=1,e=2}, size=4 > 3
 *   shrink: remove s[2]='b' -> mp={a=1,b=2,c=1,e=2}, i=3 => size=4 > 3
 * i=3, j=8 window="acbebe"
 * i=3, j=9: include 'b' -> mp={a=1,b=3,c=1,e=2}, size=4 > 3
 *   shrink: remove s[3]='a' -> mp={b=3,c=1,e=2}, i=4 => size=3
 * window="cbebeb", now size==3, result = max(6,9-4+1=6)=6
 * i=4, j=10: include 'e' -> mp={b=3,c=1,e=3}, size=3, result = max(6,10-4+1=7)=7
 *
 * Final result = 7 (substring "cbebebe")
 */
