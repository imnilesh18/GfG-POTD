/*
 * GfG Link: https://www.geeksforgeeks.org/problems/game-with-string4100/1
 *
 * Game with String
 *
 * Difficulty: Medium Accuracy: 53.96% Submissions: 59K+ Points: 4 Average Time: 15m
 *
 * Given a string s consisting of lowercase alphabets and an integer k, your task is to find the minimum possible value of the string after removing exactly k characters.
 *
 * The value of the string is defined as the sum of the squares of the frequencies of each distinct character present in the string.
 *
 * Examples :
 *
 * Input: s = "abbccc", k = 2
 * Output: 6
 * Explaination: We remove two 'c' to get the value as 12 + 22 + 12 = 6 or We remove one 'b' and one 'c' to get the value 12 + 12 + 22 = 6.
 *
 * Input: s = "aaab", k = 2
 * Output: 2
 * Explaination: We remove two 'a'. Now we get the value as 12 + 12 = 2.
 *
 * Constraints:
 * 0 ≤ k ≤ s.length() ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach 1: Count frequency of each character, use greedy strategy to always reduce the character with highest frequency (to minimize square sum).
// Time Complexity: O(k * log 26 + 26) ≈ O(k) as 26 is constant. Sorting 26-length freq array k times.
// Space Complexity: O(1) since frequency array is fixed size of 26.
class Solution {
public:
    int minValue(string& s, int k) {
        vector<int> freq(26, 0); // Frequency array for 26 lowercase letters

        // Count frequencies
        for (char ch : s) {
            freq[ch - 'a']++;
        }

        // Remove k characters greedily from the highest frequency char
        while (k--) {
            sort(freq.begin(), freq.end()); // Sort to bring max freq to end
            if (freq[25] == 0) {            // If all characters are removed
                break;
            }
            freq[25]--; // Remove one occurrence from highest freq char
        }

        int result = 0;
        for (int val : freq) {
            result += val * val; // Sum of squares of remaining frequencies
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "abbccc", k = 2
 * Initial frequencies: a:1, b:2, c:3 → freq = [1, 2, 3]
 *
 * Iteration 1:
 *   Sorted freq: [0, ..., 1, 2, 3] → max is 3 → reduce to 2
 *   freq becomes: [1, 2, 2]
 *
 * Iteration 2:
 *   Sorted freq: [0, ..., 1, 2, 2] → max is 2 → reduce to 1
 *   freq becomes: [1, 2, 1]
 *
 * Final freq: a:1, b:2, c:1
 * Value = 1^2 + 2^2 + 1^2 = 1 + 4 + 1 = 6
 * Output: 6
 *
 */

// Approach 2: Use a max heap (priority queue) to always pick and reduce the character with the highest frequency first (greedy).
// Time Complexity: O(n + k*log 26) ≈ O(n + k) since heap size is constant (max 26).
// Space Complexity: O(26) = O(1) since only 26 lowercase letters.
class Solution {
public:
    int minValue(string& s, int k) {
        vector<int> freq(26, 0); // Frequency array for 26 lowercase letters

        // Count frequencies
        for (char ch : s) {
            freq[ch - 'a']++;
        }

        priority_queue<int> pq; // Max heap to always reduce highest freq

        // Push all non-zero frequencies to heap
        for (int f : freq) {
            if (f > 0) {
                pq.push(f);
            }
        }

        // Remove k characters from the highest freq char
        while (k-- && !pq.empty()) {
            int top = pq.top();
            pq.pop();
            if (top > 1) {
                pq.push(top - 1); // Push back after reducing
            }
        }

        int result = 0;
        while (!pq.empty()) {
            int val = pq.top();
            pq.pop();
            result += val * val; // Sum of squares of remaining frequencies
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "abbccc", k = 2
 * Initial frequencies: a:1, b:2, c:3 → freq = [1, 2, 3]
 * Push all to max heap → pq = [3, 2, 1]
 *
 * Iteration 1:
 *   Top = 3 → reduce to 2 → pq = [2, 2, 1]
 *
 * Iteration 2:
 *   Top = 2 → reduce to 1 → pq = [2, 1, 1]
 *
 * Final freq in heap: a:1, b:2, c:1
 * Value = 1^2 + 2^2 + 1^2 = 1 + 4 + 1 = 6
 * Output: 6
 *
 */

// Approach 3: Use a bucket array to count how many characters have the same frequency,
// then reduce highest frequencies first (greedy) using frequency buckets.
// Time Complexity: O(n + k + maxi) where maxi is the maximum frequency in s.
// Space Complexity: O(1) since arrays used are bounded (constant size 26 and max frequency ≤ n).
class Solution {
public:
    int minValue(string& s, int k) {
        // Step 1: Count frequency of each character and get maximum frequency
        vector<int> alphaFreq(26, 0);
        int         maxi = 0;

        for (char ch : s) {
            alphaFreq[ch - 'a']++;
            maxi = max(maxi, alphaFreq[ch - 'a']);
        }

        // Step 2: Build a bucket array where index = frequency and value = count of chars with that freq
        vector<int> freq(maxi + 1, 0);
        for (int i = 0; i < 26; i++) {
            if (alphaFreq[i] > 0) {
                freq[alphaFreq[i]]++;
            }
        }

        int maxFreq = maxi;

        // Step 3: Reduce highest frequencies greedily
        while (k > 0 && maxFreq > 0) {
            int countAtMax = freq[maxFreq];

            if (countAtMax <= k) {
                k -= countAtMax;
                freq[maxFreq - 1] += countAtMax;
                freq[maxFreq]      = 0;
                maxFreq--;
            } else {
                freq[maxFreq]     -= k;
                freq[maxFreq - 1] += k;
                k = 0;
            }
        }

        // Step 4: Calculate sum of squares of remaining frequencies
        int result = 0;
        for (int i = 1; i <= maxi; i++) {
            result += i * i * freq[i];
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "abbccc", k = 2
 *
 * Step 1: Count frequencies → alphaFreq = [1(a), 2(b), 3(c)]
 *         max frequency (maxi) = 3
 *
 * Step 2: Build bucket freq:
 *         freq = [0, 1, 1, 1] // freq[1] = 1(a), freq[2] = 1(b), freq[3] = 1(c)
 *
 * Step 3:
 *   k = 2, maxFreq = 3, freq[3] = 1
 *   → Remove 1 char with freq 3 → freq[2] += 1, freq[3] = 0, k = 1
 *
 *   k = 1, maxFreq = 2, freq[2] = 2
 *   → Remove 1 char with freq 2 → freq[1] += 1, freq[2] = 1, k = 0
 *
 * Final freq = [0, 2, 1] → freq[1] = 2, freq[2] = 1
 *
 * Step 4:
 *   result = 1^2 * 2 + 2^2 * 1 = 1*2 + 4 = 6
 *
 * Output: 6
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Count frequency of each character, use greedy strategy to always reduce the character with highest frequency (to minimize square sum).
// Time Complexity: O(k * log 26 + 26) ≈ O(k) as 26 is constant. Sorting 26-length freq array k times.
// Space Complexity: O(1) since frequency array is fixed size of 26.
class Solution {
    public int minValue(String s, int k) {
        int[] freq = new int[26]; // Frequency array for 26 lowercase letters

        // Count frequencies
        for (char ch : s.toCharArray()) {
            freq[ch - 'a']++;
        }

        // Remove k characters greedily from the highest frequency char
        while (k-- > 0) {
            Arrays.sort(freq);   // Sort to bring max freq to end
            if (freq[25] == 0) { // If all characters are removed
                break;
            }
            freq[25]--; // Remove one occurrence from highest freq char
        }

        int result = 0;
        for (int val : freq) {
            result += val * val; // Sum of squares of remaining frequencies
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "abbccc", k = 2
 * Initial frequencies: a:1, b:2, c:3 → freq = [1, 2, 3]
 *
 * Iteration 1:
 *   Sorted freq: [0, ..., 1, 2, 3] → max is 3 → reduce to 2
 *   freq becomes: [1, 2, 2]
 *
 * Iteration 2:
 *   Sorted freq: [0, ..., 1, 2, 2] → max is 2 → reduce to 1
 *   freq becomes: [1, 2, 1]
 *
 * Final freq: a:1, b:2, c:1
 * Value = 1^2 + 2^2 + 1^2 = 1 + 4 + 1 = 6
 * Output: 6
 *
 */

// Approach 2: Use a max heap (priority queue) to always pick and reduce the character with the highest frequency first (greedy).
// Time Complexity: O(n + k*log 26) ≈ O(n + k) since heap size is constant (max 26).
// Space Complexity: O(26) = O(1) since only 26 lowercase letters.
class Solution {
    public int minValue(String s, int k) {
        int[] freq = new int[26]; // Frequency array for 26 lowercase letters

        // Count frequencies
        for (char ch : s.toCharArray()) {
            freq[ch - 'a']++;
        }

        // Max heap using PriorityQueue with reverse order
        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());

        // Push all non-zero frequencies to heap
        for (int f : freq) {
            if (f > 0) {
                pq.offer(f);
            }
        }

        // Remove k characters from the highest freq char
        while (k-- > 0 && !pq.isEmpty()) {
            int top = pq.poll();
            if (top > 1) {
                pq.offer(top - 1); // Push back after reducing
            }
        }

        int result = 0;
        while (!pq.isEmpty()) {
            int val = pq.poll();
            result += val * val; // Sum of squares of remaining frequencies
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "abbccc", k = 2
 * Initial frequencies: a:1, b:2, c:3 → freq = [1, 2, 3]
 * Push all to max heap → pq = [3, 2, 1]
 *
 * Iteration 1:
 *   Top = 3 → reduce to 2 → pq = [2, 2, 1]
 *
 * Iteration 2:
 *   Top = 2 → reduce to 1 → pq = [2, 1, 1]
 *
 * Final freq in heap: a:1, b:2, c:1
 * Value = 1^2 + 2^2 + 1^2 = 1 + 4 + 1 = 6
 * Output: 6
 *
 */

// Approach 3: Use a bucket array to count how many characters have the same frequency,
// then reduce highest frequencies first (greedy) using frequency buckets.
// Time Complexity: O(n + k + maxi) where maxi is the maximum frequency in s.
// Space Complexity: O(1) since arrays used are bounded (constant size 26 and max frequency ≤ n).
class Solution {
    public int minValue(String s, int k) {
        // Step 1: Count frequency of each character and get maximum frequency
        int[] alphaFreq = new int[26];
        int maxi = 0;

        for (char ch : s.toCharArray()) {
            alphaFreq[ch - 'a']++;
            maxi = Math.max(maxi, alphaFreq[ch - 'a']);
        }

        // Step 2: Build a bucket array where index = frequency and value = count of chars with that freq
        int[] freq = new int[maxi + 1];
        for (int i = 0; i < 26; i++) {
            if (alphaFreq[i] > 0) {
                freq[alphaFreq[i]]++;
            }
        }

        int maxFreq = maxi;

        // Step 3: Reduce highest frequencies greedily
        while (k > 0 && maxFreq > 0) {
            int countAtMax = freq[maxFreq];

            if (countAtMax <= k) {
                k -= countAtMax;
                freq[maxFreq - 1] += countAtMax;
                freq[maxFreq]      = 0;
                maxFreq--;
            } else {
                freq[maxFreq]     -= k;
                freq[maxFreq - 1] += k;
                k = 0;
            }
        }

        // Step 4: Calculate sum of squares of remaining frequencies
        int result = 0;
        for (int i = 1; i <= maxi; i++) {
            result += i * i * freq[i];
        }

        return result;
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "abbccc", k = 2
 *
 * Step 1: Count frequencies → alphaFreq = [1(a), 2(b), 3(c)]
 *         max frequency (maxi) = 3
 *
 * Step 2: Build bucket freq:
 *         freq = [0, 1, 1, 1] // freq[1] = 1(a), freq[2] = 1(b), freq[3] = 1(c)
 *
 * Step 3:
 *   k = 2, maxFreq = 3, freq[3] = 1
 *   → Remove 1 char with freq 3 → freq[2] += 1, freq[3] = 0, k = 1
 *
 *   k = 1, maxFreq = 2, freq[2] = 2
 *   → Remove 1 char with freq 2 → freq[1] += 1, freq[2] = 1, k = 0
 *
 * Final freq = [0, 2, 1] → freq[1] = 2, freq[2] = 1
 *
 * Step 4:
 *   result = 1^2 * 2 + 2^2 * 1 = 1*2 + 4 = 6
 *
 * Output: 6
 *
 */
