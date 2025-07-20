/*
 * GfG Link: https://www.geeksforgeeks.org/problems/count-the-coprimes/1
 *
 * Count the Coprimes
 *
 * Difficulty: Hard Accuracy: 39.96% Submissions: 846+ Points: 8
 *
 * You are given an array arr[] of positive integers. Your task is to count the number of pairs (i, j) such that:
 *
 * 0 ≤ i < j ≤ n-1
 * gcd(arr[i], arr[j]) = 1
 * In other words, count the number of unordered pairs of indices (i, j) where the elements at those positions are co-prime.
 *
 * Examples:
 *
 * Input: arr[] = [1, 2, 3]
 * Output: 3
 * Explanation: (0,1), (0,2), (1,2) are the pair of indices where gcd(arr[i], arr[j]) = 1
 *
 * Input: arr[] = [4, 8, 3, 9]
 * Output: 4
 * Explanation: (0,2), (0,3), (1,2), (1,3) are the pair of indices where gcd(arr[i], arr[j]) = 1
 *
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^4
 * 1 ≤ arr[i] ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use the Principle of Inclusion-Exclusion with Mobius Inversion. The number of coprime pairs is given by the formula: sum_{d=1 to M} mu(d) * C(count[d], 2), where M is the max element, mu is the Mobius function, and count[d] is the number of elements in the array divisible by d. The steps are: 1. Precompute frequencies of each number. 2. Precompute count[d] for each d (sum of frequencies of its multiples). 3. Precompute the Mobius function mu(d) using a sieve. 4. Apply the formula to calculate the total count of coprime pairs.
// Time Complexity: O(n + M*log(M)), where n is arr.length and M is max(arr[i]). O(n) for frequencies, O(M*logM) for multiples count, O(M) for Mobius sieve, and O(M) for the final sum.
// Space Complexity: O(M), where M is max(arr[i]), for storing frequencies, counts, and Mobius values.
class Solution {
public:
    int cntCoprime(std::vector<int>& arr) {
        // Define the maximum possible value from constraints + 1.
        int MAX_VAL = 10001;

        // mu array for Mobius function values.
        vector<int> mu(MAX_VAL);
        // lp array to store the least prime factor for the sieve.
        vector<int> lp(MAX_VAL, 0);
        // vector to store prime numbers found by the sieve.
        vector<int> primes;

        // --- Step 1: Precompute Mobius function (mu) using a linear sieve ---
        mu[1] = 1; // Base case: mu(1) is 1.
        for (int i = 2; i < MAX_VAL; ++i) {
            // If lp[i] is 0, it means i is a prime number.
            if (lp[i] == 0) {
                lp[i] = i;           // The least prime factor of a prime is itself.
                mu[i] = -1;          // For a prime p, mu(p) = -1.
                primes.push_back(i); // Add i to the list of primes.
            }
            // Iterate through primes to mark their multiples.
            for (int p : primes) {
                // Stop if the current prime is too large or i*p exceeds the limit.
                if (p > lp[i] || (long long)i * p >= MAX_VAL) {
                    break;
                }
                lp[i * p] = p; // p is the least prime factor of i*p.
                // If p is also the least prime factor of i, then i*p has a squared prime factor.
                if (p == lp[i]) {
                    mu[i * p] = 0; // mu is 0 if there's a squared prime factor.
                    break;         // Crucial break for linear time performance.
                } else {
                    // If p is not the least prime factor of i, toggle the sign based on mu[i].
                    mu[i * p] = -mu[i];
                }
            }
        }

        // --- Step 2: Calculate frequencies of each number in the input array ---
        vector<int> freq(MAX_VAL, 0); // Stores frequency of each number.
        for (int x : arr) {
            freq[x]++;                // Increment frequency for the number x.
        }

        // --- Step 3: Calculate the count of numbers divisible by each d ---
        // count[d] stores how many numbers in arr are multiples of d.
        vector<long long> count(MAX_VAL, 0);
        for (int d = 1; d < MAX_VAL; ++d) {
            // Iterate through all multiples of d up to MAX_VAL.
            for (int m = d; m < MAX_VAL; m += d) {
                count[d] += freq[m]; // Add the frequency of the multiple m.
            }
        }

        // --- Step 4: Apply the Inclusion-Exclusion principle using the Mobius function ---
        // The number of coprime pairs is sum(mu[d] * C(count[d], 2)) for d from 1 to MAX_VAL.
        long long ans = 0;
        for (int d = 1; d < MAX_VAL; ++d) {
            // If mu[d] is 0, this term contributes nothing to the sum.
            if (mu[d] == 0) {
                continue;
            }

            // Calculate C(count[d], 2), which is count[d] * (count[d] - 1) / 2.
            // This represents the number of pairs where both elements are multiples of d.
            long long pairs_with_gcd_multiple_of_d = (count[d] * (count[d] - 1)) / 2;

            // Add or subtract from the total based on the sign of mu[d].
            ans += mu[d] * pairs_with_gcd_multiple_of_d;
        }

        return (int)ans;
    }
};

/* *
 * Dry Run for Input: arr[] = [4, 8, 3, 9]
 *
 * M is set to 10001 based on constraints.
 *
 * 1. Mobius Sieve (precomputation of mu array):
 * This step precomputes mu[d] for all d up to 10000.
 * Key values for this example:
 * - mu[1] = 1
 * - mu[2] = -1 (prime)
 * - mu[3] = -1 (prime)
 * - mu[4] = 0  (4 = 2^2, has a squared prime factor)
 * - mu[5] = -1 (prime)
 * - mu[6] = 1  (6 = 2*3, two distinct prime factors)
 * - mu[7] = -1 (prime)
 * - mu[8] = 0  (8 = 2^3)
 * - mu[9] = 0  (9 = 3^2)
 * ... and so on for other numbers.
 *
 * 2. Frequency Calculation (freq array):
 * - freq[3] = 1
 * - freq[4] = 1
 * - freq[8] = 1
 * - freq[9] = 1
 * (All other relevant frequencies are 0)
 *
 * 3. Multiples Count (count array):
 * count[d] = sum of frequencies of numbers in arr that are multiples of d.
 * - count[1] = freq[3] + freq[4] + freq[8] + freq[9] = 4
 * - count[2] = freq[4] + freq[8] = 2
 * - count[3] = freq[3] + freq[9] = 2
 * - count[4] = freq[4] + freq[8] = 2
 * - count[5] = 0
 * - count[6] = 0
 * - count[7] = 0
 * - count[8] = freq[8] = 1
 * - count[9] = freq[9] = 1
 * (For any d where count[d] <= 1, the number of pairs C(count[d], 2) is 0, so those terms won't affect the sum).
 *
 * 4. Final Calculation (Applying Inclusion-Exclusion formula):
 * ans = sum(mu[d] * C(count[d], 2))
 * Initialize ans = 0.
 *
 * - d = 1:
 * mu[1] = 1, count[1] = 4
 * pairs = C(4, 2) = (4 * 3) / 2 = 6
 * ans += 1 * 6  =>  ans = 6
 *
 * - d = 2:
 * mu[2] = -1, count[2] = 2
 * pairs = C(2, 2) = (2 * 1) / 2 = 1
 * ans += (-1) * 1  =>  ans = 6 - 1 = 5
 *
 * - d = 3:
 * mu[3] = -1, count[3] = 2
 * pairs = C(2, 2) = 1
 * ans += (-1) * 1  =>  ans = 5 - 1 = 4
 *
 * - d = 4:
 * mu[4] = 0, count[4] = 2
 * pairs = C(2, 2) = 1
 * ans += 0 * 1  =>  ans = 4 + 0 = 4
 *
 * - For all other 'd', either mu[d] is 0 or count[d] < 2, making the term 0.
 *
 * Final Answer: 4
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use the Principle of Inclusion-Exclusion with Mobius Inversion. The number of coprime pairs is given by the formula: sum_{d=1 to M} mu(d) * C(count[d], 2), where M is the max element, mu is the Mobius function, and count[d] is the number of elements in the array divisible by d. The steps are: 1. Precompute frequencies of each number. 2. Precompute count[d] for each d (sum of frequencies of its multiples). 3. Precompute the Mobius function mu(d) using a sieve. 4. Apply the formula to calculate the total count of coprime pairs.
// Time Complexity: O(n + M*log(M)), where n is arr.length and M is max(arr[i]). O(n) for frequencies, O(M*logM) for multiples count, O(M) for Mobius sieve, and O(M) for the final sum.
// Space Complexity: O(M), where M is max(arr[i]), for storing frequencies, counts, and Mobius values.
class Solution {
    int cntCoprime(int[] arr) {
        // Define the maximum possible value from constraints + 1.
        final int MAX_VAL = 10001;

        // mu array for Mobius function values.
        int[] mu = new int[MAX_VAL];
        // lp array to store the least prime factor for the sieve.
        int[] lp = new int[MAX_VAL];
        // ArrayList to store prime numbers found by the sieve.
        ArrayList<Integer> primes = new ArrayList<>();

        // --- Step 1: Precompute Mobius function (mu) using a linear sieve ---
        mu[1] = 1; // Base case: mu(1) is 1.
        for (int i = 2; i < MAX_VAL; ++i) {
            // If lp[i] is 0, it means i is a prime number.
            if (lp[i] == 0) {
                lp[i] = i;     // The least prime factor of a prime is itself.
                mu[i] = -1;    // For a prime p, mu(p) = -1.
                primes.add(i); // Add i to the list of primes.
            }
            // Iterate through primes to mark their multiples.
            for (int p : primes) {
                // Stop if the current prime is too large or i*p exceeds the limit.
                if (p > lp[i] || (long)i * p >= MAX_VAL) {
                    break;
                }
                lp[i * p] = p; // p is the least prime factor of i*p.
                // If p is also the least prime factor of i, then i*p has a squared prime factor.
                if (p == lp[i]) {
                    mu[i * p] = 0; // mu is 0 if there's a squared prime factor.
                    break;         // Crucial break for linear time performance.
                } else {
                    // If p is not the least prime factor of i, toggle the sign based on mu[i].
                    mu[i * p] = -mu[i];
                }
            }
        }

        // --- Step 2: Calculate frequencies of each number in the input array ---
        int[] freq = new int[MAX_VAL]; // Stores frequency of each number.
        for (int x : arr) {
            freq[x]++;                 // Increment frequency for the number x.
        }

        // --- Step 3: Calculate the count of numbers divisible by each d ---
        // count[d] stores how many numbers in arr are multiples of d.
        long[] count = new long[MAX_VAL];
        for (int d = 1; d < MAX_VAL; ++d) {
            // Iterate through all multiples of d up to MAX_VAL.
            for (int m = d; m < MAX_VAL; m += d) {
                count[d] += freq[m]; // Add the frequency of the multiple m.
            }
        }

        // --- Step 4: Apply the Inclusion-Exclusion principle using the Mobius function ---
        // The number of coprime pairs is sum(mu[d] * C(count[d], 2)) for d from 1 to MAX_VAL.
        long ans = 0;
        for (int d = 1; d < MAX_VAL; ++d) {
            // If mu[d] is 0, this term contributes nothing to the sum.
            if (mu[d] == 0) {
                continue;
            }

            // Calculate C(count[d], 2), which is count[d] * (count[d] - 1) / 2.
            // This represents the number of pairs where both elements are multiples of d.
            long pairs_with_gcd_multiple_of_d = (count[d] * (count[d] - 1)) / 2;

            // Add or subtract from the total based on the sign of mu[d].
            ans += mu[d] * pairs_with_gcd_multiple_of_d;
        }

        return (int)ans;  // Cast the final answer to int as required by the function signature.
    }
}

/* *
 * Dry Run for Input: arr[] = [4, 8, 3, 9]
 *
 * M is set to 10001 based on constraints.
 *
 * 1. Mobius Sieve (precomputation of mu array):
 * This step precomputes mu[d] for all d up to 10000.
 * Key values for this example:
 * - mu[1] = 1
 * - mu[2] = -1 (prime)
 * - mu[3] = -1 (prime)
 * - mu[4] = 0  (4 = 2^2, has a squared prime factor)
 * - mu[5] = -1 (prime)
 * - mu[6] = 1  (6 = 2*3, two distinct prime factors)
 * - mu[7] = -1 (prime)
 * - mu[8] = 0  (8 = 2^3)
 * - mu[9] = 0  (9 = 3^2)
 * ... and so on for other numbers.
 *
 * 2. Frequency Calculation (freq array):
 * - freq[3] = 1
 * - freq[4] = 1
 * - freq[8] = 1
 * - freq[9] = 1
 * (All other relevant frequencies are 0)
 *
 * 3. Multiples Count (count array):
 * count[d] = sum of frequencies of numbers in arr that are multiples of d.
 * - count[1] = freq[3] + freq[4] + freq[8] + freq[9] = 4
 * - count[2] = freq[4] + freq[8] = 2
 * - count[3] = freq[3] + freq[9] = 2
 * - count[4] = freq[4] + freq[8] = 2
 * - count[5] = 0
 * - count[6] = 0
 * - count[7] = 0
 * - count[8] = freq[8] = 1
 * - count[9] = freq[9] = 1
 * (For any d where count[d] <= 1, the number of pairs C(count[d], 2) is 0, so those terms won't affect the sum).
 *
 * 4. Final Calculation (Applying Inclusion-Exclusion formula):
 * ans = sum(mu[d] * C(count[d], 2))
 * Initialize ans = 0.
 *
 * - d = 1:
 * mu[1] = 1, count[1] = 4
 * pairs = C(4, 2) = (4 * 3) / 2 = 6
 * ans += 1 * 6  =>  ans = 6
 *
 * - d = 2:
 * mu[2] = -1, count[2] = 2
 * pairs = C(2, 2) = (2 * 1) / 2 = 1
 * ans += (-1) * 1  =>  ans = 6 - 1 = 5
 *
 * - d = 3:
 * mu[3] = -1, count[3] = 2
 * pairs = C(2, 2) = 1
 * ans += (-1) * 1  =>  ans = 5 - 1 = 4
 *
 * - d = 4:
 * mu[4] = 0, count[4] = 2
 * pairs = C(2, 2) = 1
 * ans += 0 * 1  =>  ans = 4 + 0 = 4
 *
 * - For all other 'd', either mu[d] is 0 or count[d] < 2, making the term 0.
 *
 * Final Answer: 4
 *
 */
