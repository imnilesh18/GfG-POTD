/*
 * GfG Link: https://www.geeksforgeeks.org/problems/count-unique-vowel-strings/1
 *
 * Count Unique Vowel Strings
 *
 * Difficulty: Medium Accuracy: 28.81% Submissions: 73+ Points: 4
 *
 * You are given a lowercase string s, determine the total number of distinct strings that can be formed using the following rules:
 * Identify all unique vowels (a, e, i, o, u) present in the string.
 * For each distinct vowel, choose exactly one of its occurrences from s. If a vowel appears multiple times, each occurrence represents a unique selection choice.
 * Generate all possible permutations of the selected vowels. Each unique arrangement counts as a distinct string.
 * Return the total number of such distinct strings.
 *
 * Examples:
 *
 * Input: s = "aeiou"
 * Output: 120
 * Explanation: Each vowel appears once, so the number of different strings can form is 5! = 120.
 *
 * Input: s = "ae"
 * Output: 2
 * Explanation: Pick a and e, make all orders → "ae", "ea".
 *
 * Input: s = "aacidf"
 * Output: 4
 *
 * Explanation: Vowels in s are 'a' and 'i', Pick each 'a' once with a single 'i', make all orders → "ai", "ia", "ai", "ia".
 *
 * Constraints:
 * 1 ≤ s.size() ≤ 100
 */

/************************************************************ C++ ************************************************/

// Approach: The method involves three main steps.

// First, we count the frequency of each unique vowel ('a', 'e', 'i', 'o', 'u') in the input string.

// Second, we calculate the total number of ways to select one instance of each unique vowel found. This is the product of their frequencies.

// Third, we calculate the number of ways to arrange (permute) these selected vowels, which is the factorial of the count of unique vowels.

// The final result is the product of the number of selection ways and the number of permutation ways.

// Time Complexity: O(N), where N is the length of the string 's'. We iterate through the string once. The subsequent loops run at most 5 times (for the vowels), which is constant time.
// Space Complexity: O(K), where K is the number of unique vowels. In the worst case, K=5, so the space complexity is O(1) or constant, as the map stores at most 5 elements.
class Solution {
public:
    int vowelCount(string& s) {
        // A map to store the frequency of each vowel found in the string.
        // The key is the vowel (char), and the value is its count (int).
        map<char, int> vowel_freq;

        // Iterate through each character of the input string 's'.
        for (char ch : s) {
            // Check if the character is a lowercase vowel.
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                // If it's a vowel, increment its count in the map.
                // If the vowel is not yet in the map, it will be added with a count of 1.
                vowel_freq[ch]++;
            }
        }

        // Get the number of unique vowels present in the string.
        // This is equal to the number of entries in our frequency map.
        int k = vowel_freq.size();

        // If no vowels are present in the string (k=0), no vowel strings can be formed.
        // So, we return 0 as per the problem logic.
        if (k == 0) {
            return 0;
        }

        // Calculate the total number of ways to choose one of each unique vowel.
        // This is the product of their frequencies.
        // We use 'long long' to prevent potential integer overflow if frequencies are large.
        long long selection_ways = 1;
        for (auto const& pair : vowel_freq) {
            // For each unique vowel, multiply the running product by its frequency.
            // pair.second holds the frequency of the vowel.
            selection_ways *= pair.second;
        }

        // Calculate the number of permutations for the k selected vowels, which is k!
        // We use 'long long' here as well for safety, although k! for k<=5 fits in an int.
        long long permutations = 1;
        for (int i = 1; i <= k; ++i) {
            // Calculate factorial: k * (k-1) * ... * 1
            permutations *= i;
        }

        // The total number of distinct strings is the product of the number of ways
        // to select the vowels and the number of ways to permute them.
        return static_cast<int>(selection_ways * permutations);
    }
};

/*
 *
 * Dry Run
 *
 * Input: s = "aacidf"
 *
 * 1. Initialization:
 * - `vowel_freq` is an empty map: {}
 *
 * 2. Loop through the string "aacidf" to count vowel frequencies:
 * - ch = 'a': It's a vowel. `vowel_freq` becomes {'a': 1}.
 * - ch = 'a': It's a vowel. `vowel_freq` becomes {'a': 2}.
 * - ch = 'c': Not a vowel. Skip.
 * - ch = 'i': It's a vowel. `vowel_freq` becomes {'a': 2, 'i': 1}.
 * - ch = 'd': Not a vowel. Skip.
 * - ch = 'f': Not a vowel. Skip.
 * - Final `vowel_freq` = {'a': 2, 'i': 1}.
 *
 * 3. Count unique vowels:
 * - `k = vowel_freq.size()`
 * - `k = 2`.
 *
 * 4. Check if k is 0:
 * - `k` is 2, which is not 0. Proceed.
 *
 * 5. Calculate `selection_ways`:
 * - Initialize `selection_ways = 1`.
 * - Loop through `vowel_freq`:
 * - For pair {'a', 2}: `selection_ways = 1 * 2 = 2`.
 * - For pair {'i', 1}: `selection_ways = 2 * 1 = 2`.
 * - Final `selection_ways` = 2.
 * (This means we can form two sets of selected vowels: {first 'a', 'i'} and {second 'a', 'i'}).
 *
 * 6. Calculate `permutations`:
 * - Initialize `permutations = 1`.
 * - `k` is 2. Loop from i = 1 to 2.
 * - i = 1: `permutations = 1 * 1 = 1`.
 * - i = 2: `permutations = 1 * 2 = 2`.
 * - Final `permutations` = 2.
 * (This means for any set of 2 vowels, there are 2! = 2 ways to arrange them, e.g., "ai" and "ia").
 *
 * 7. Final Calculation:
 * - `return selection_ways * permutations`
 * - `return 2 * 2`
 * - `return 4`
 *
 * Output: 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: The method involves three main steps.

// First, we count the frequency of each unique vowel ('a', 'e', 'i', 'o', 'u') in the input string.

// Second, we calculate the total number of ways to select one instance of each unique vowel found. This is the product of their frequencies.

// Third, we calculate the number of ways to arrange (permute) these selected vowels, which is the factorial of the count of unique vowels.

// The final result is the product of the number of selection ways and the number of permutation ways.

// Time Complexity: O(N), where N is the length of the string 's'. We iterate through the string once. The subsequent loops run at most 5 times (for the vowels), which is constant time.
// Space Complexity: O(K), where K is the number of unique vowels. In the worst case, K=5, so the space complexity is O(1) or constant, as the map stores at most 5 elements.
class Solution {
    public int vowelCount(String s) {
        // A map to store the frequency of each vowel found in the string.
        // The key is the vowel (Character), and the value is its count (Integer).
        Map<Character, Integer> vowel_freq = new HashMap<>();

        // Iterate through each character of the input string 's'.
        for (char ch : s.toCharArray()) {
            // Check if the character is a lowercase vowel.
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                // If it's a vowel, increment its count in the map.
                // If the vowel is not yet in the map, it will be added with a count of 1.
                vowel_freq.put(ch, vowel_freq.getOrDefault(ch, 0) + 1);
            }
        }

        // Get the number of unique vowels present in the string.
        // This is equal to the number of entries in our frequency map.
        int k = vowel_freq.size();

        // If no vowels are present in the string (k=0), no vowel strings can be formed.
        // So, we return 0 as per the problem logic.
        if (k == 0) {
            return 0;
        }

        // Calculate the total number of ways to choose one of each unique vowel.
        // This is the product of their frequencies.
        // We use 'long' to prevent potential integer overflow if frequencies are large.
        long selection_ways = 1;
        for (int count : vowel_freq.values()) {
            // For each unique vowel, multiply the running product by its frequency.
            selection_ways *= count;
        }

        // Calculate the number of permutations for the k selected vowels, which is k!
        // We use 'long' here as well for safety, although k! for k<=5 fits in an int.
        long permutations = 1;
        for (int i = 1; i <= k; i++) {
            // Calculate factorial: k * (k-1) * ... * 1
            permutations *= i;
        }

        // The total number of distinct strings is the product of the number of ways
        // to select the vowels and the number of ways to permute them.
        return (int)(selection_ways * permutations);
    }
}

/*
 *
 * Dry Run
 *
 * Input: s = "aacidf"
 *
 * 1. Initialization:
 * - `vowel_freq` is an empty HashMap: {}
 *
 * 2. Loop through the string "aacidf" to count vowel frequencies:
 * - ch = 'a': It's a vowel. `vowel_freq` becomes {'a'=1}.
 * - ch = 'a': It's a vowel. `vowel_freq` becomes {'a'=2}.
 * - ch = 'c': Not a vowel. Skip.
 * - ch = 'i': It's a vowel. `vowel_freq` becomes {'a'=2, 'i'=1}.
 * - ch = 'd': Not a vowel. Skip.
 * - ch = 'f': Not a vowel. Skip.
 * - Final `vowel_freq` = {'a'=2, 'i'=1}.
 *
 * 3. Count unique vowels:
 * - `k = vowel_freq.size()`
 * - `k = 2`.
 *
 * 4. Check if k is 0:
 * - `k` is 2, which is not 0. Proceed.
 *
 * 5. Calculate `selection_ways`:
 * - Initialize `selection_ways = 1`.
 * - Loop through `vowel_freq.values()` which are [2, 1]:
 * - For count 2: `selection_ways = 1 * 2 = 2`.
 * - For count 1: `selection_ways = 2 * 1 = 2`.
 * - Final `selection_ways` = 2.
 * (This means we can form two sets of selected vowels: {first 'a', 'i'} and {second 'a', 'i'}).
 *
 * 6. Calculate `permutations`:
 * - Initialize `permutations = 1`.
 * - `k` is 2. Loop from i = 1 to 2.
 * - i = 1: `permutations = 1 * 1 = 1`.
 * - i = 2: `permutations = 1 * 2 = 2`.
 * - Final `permutations` = 2.
 * (This means for any set of 2 vowels, there are 2! = 2 ways to arrange them, e.g., "ai" and "ia").
 *
 * 7. Final Calculation:
 * - `return (int) (selection_ways * permutations)`
 * - `return (int) (2 * 2)`
 * - `return 4`
 *
 * Output: 4
 *
 */
