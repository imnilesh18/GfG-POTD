/*
 * GfG Link: https://www.geeksforgeeks.org/problems/nine-divisors3751/1
 *
 * Nine Divisors
 *
 * Difficulty: Medium Accuracy: 35.58 % Submissions : 27K + Points : 4
 *
 * Given a positive integer n, you need to count the numbers less than or equal to n having exactly 9 divisors.
 *
 * Examples:
 *
 * Input: n = 100
 *         Output : 2
 * Explanation: Numbers which have exactly 9 divisors are 36 and 100.
 *
 * Input:     n = 200
 *             Output : 3
 * Explanation:   Numbers which have exactly 9 divisors are 36, 100, 196.
 *
 * Constraints:
 * 1 ≤ n ≤ 10 ^ 9
 */

/************************************************************ C++ ************************************************/

// Approach: A number with exactly 9 divisors can either be of form p^8 (one prime raised to 8) or p^2 * q^2 (product of two distinct primes each raised to power 2).
// Time Complexity: O(sqrt(n) * log(log n)) due to Sieve of Eratosthenes up to sqrt(n).
// Space Complexity: O(sqrt(n)) to store smallest prime factors in sieve.
class Solution {
public:
    int countNumbers(int n) {
        int count = 0;
        int limit = sqrt(n);

        // Create a sieve to store smallest prime factor for numbers up to limit
        vector<int> prime(limit + 1);

        for (int i = 1; i <= limit; i++) {
            prime[i] = i;
        }

        // Sieve of Eratosthenes to populate smallest prime factors
        for (int i = 2; i* i <= limit; i++) {
            if (prime[i] == i) {
                for (int j = i * i; j <= limit; j += i) {
                    if (prime[j] == j) {
                        prime[j] = i;
                    }
                }
            }
        }

        // Loop through each number up to limit to check valid patterns
        for (int i = 2; i <= limit; i++) {
            int p = prime[i];
            int q = prime[i / p];

            // Case 1: i = p * q and both p, q are distinct primes → number = (p^2)*(q^2)
            if (p * q == i && p != q && q != 1) {
                if (1LL * p * p * q * q <= n) {
                    count++;
                }
            }
            // Case 2: i is prime and i^8 <= n → number = p^8
            else if (prime[i] == i && pow(i, 8) <= n) {
                count++;
            }
        }

        return count;
    }
};

/*
 *
 * Dry Run
 * Input: n = 100
 * Step 1: limit = sqrt(100) = 10
 * Step 2: Create sieve for smallest prime factor up to 10
 *         prime[] = {0,1,2,3,2,5,2,7,2,3,2}
 * Step 3: Loop i from 2 to 10
 *
 * For i = 6: prime[6] = 2, prime[6/2=3] = 3 → p*q = 2*3 = 6 == i → check (2^2)*(3^2)=36 ≤ 100 → count++
 * For i = 10: prime[10] = 2, prime[10/2=5] = 5 → p*q = 2*5 = 10 == i → (2^2)*(5^2)=100 ≤ 100 → count++
 * For i = 7: prime[7] = 7, 7^8 = 5764801 > 100 → skip
 *
 * Total valid numbers = 2 (36 and 100)
 * Output: 2
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: A number with exactly 9 divisors can either be of form p^8 (one prime raised to 8) or p^2 * q^2 (product of two distinct primes each raised to power 2).
// Time Complexity: O(sqrt(n) * log(log n)) due to Sieve of Eratosthenes up to sqrt(n).
// Space Complexity: O(sqrt(n)) to store smallest prime factors in sieve.
class Solution {
    public static int countNumbers(int n) {
        int count = 0;
        int limit = (int)Math.sqrt(n);

        // Create a sieve to store smallest prime factor for numbers up to limit
        int[] prime = new int[limit + 1];

        for (int i = 1; i <= limit; i++) {
            prime[i] = i;
        }

        // Sieve of Eratosthenes to populate smallest prime factors
        for (int i = 2; i* i <= limit; i++) {
            if (prime[i] == i) {
                for (int j = i * i; j <= limit; j += i) {
                    if (prime[j] == j) {
                        prime[j] = i;
                    }
                }
            }
        }

        // Loop through each number up to limit to check valid patterns
        for (int i = 2; i <= limit; i++) {
            int p = prime[i];
            int q = prime[i / p];

            // Case 1: i = p * q and both p, q are distinct primes → number = (p^2)*(q^2)
            if (p * q == i && p != q && q != 1) {
                long num = 1L * p * p * q * q;
                if (num <= n) {
                    count++;
                }
            }
            // Case 2: i is prime and i^8 <= n → number = p^8
            else if (prime[i] == i && Math.pow(i, 8) <= n) {
                count++;
            }
        }

        return count;
    }
}

/*
 *
 * Dry Run
 * Input: n = 100
 * Step 1: limit = sqrt(100) = 10
 * Step 2: Create sieve for smallest prime factor up to 10
 *         prime[] = {0,1,2,3,2,5,2,7,2,3,2}
 * Step 3: Loop i from 2 to 10
 *
 * For i = 6: prime[6] = 2, prime[6/2=3] = 3 → p*q = 2*3 = 6 == i → check (2^2)*(3^2)=36 ≤ 100 → count++
 * For i = 10: prime[10] = 2, prime[10/2=5] = 5 → p*q = 2*5 = 10 == i → (2^2)*(5^2)=100 ≤ 100 → count++
 * For i = 7: prime[7] = 7, 7^8 = 5764801 > 100 → skip
 *
 * Total valid numbers = 2 (36 and 100)
 * Output: 2
 *
 */
