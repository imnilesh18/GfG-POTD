/*
 * GfG Link: https://www.geeksforgeeks.org/problems/power-of-k-in-n-where-k-may-be-non-prime4206/1
 *
 * Power of k in factorial of n
 *
 * Difficulty: Medium Accuracy: 51.2% Submissions: 14K+ Points: 4
 *
 * Given two positive integers n and k, determine the highest value of x such that kx divides n! (n factorial) completely (i.e., n % (kx) == 0).
 *
 * Examples :
 *
 * Input: n = 7, k = 2
 * Output: 4
 * Explanation: 7! = 5040, and 24 = 16 is the highest power of 2 that divides 5040.
 * Input: n = 10, k = 9
 * Output: 2
 * Explanation: 10! = 3628800, and 9² = 81 is the highest power of 9 that divides 3628800.
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 2 ≤ k ≤ 10^5
 */

/************************************************************ C++ ************************************************/

// Approach: Factorize k into primes, use Legendre’s formula to count each prime’s exponent in n!, then the answer is the minimum of (exponent in n!) / (exponent in k) across all primes.
// Time Complexity: O(√k + log_p n) per prime factor, overall roughly O(√k + π(k)·log n), which is efficient for k, n ≤ 10^5.
// Space Complexity: O(log k) for storing prime factors of k.
class Solution {
public:
    // Function to factorize 'num' into its prime factors and their counts
    vector<vector<int> > primeFactors(int num) {
        vector<vector<int> > factors;

        int count = 0;

        // Count factor 2
        while (num % 2 == 0) {
            num /= 2;
            count++;
        }
        if (count > 0) {
            factors.push_back({ 2, count });
        }

        // Check for odd prime factors starting from 3
        for (int i = 3; i* i <= num; i += 2) {
            count = 0;
            while (num % i == 0) {
                num /= i;
                count++;
            }
            if (count > 0) {
                factors.push_back({ i, count });
            }
        }

        // If remainder is >1, it's a prime
        if (num > 1) {
            factors.push_back({ num, 1 });
        }

        return factors;
    }
    
    // Use Legendre’s formula to count exponent of prime p in n!
    int legendre(int n, int p) {
        int count = 0;

        // Sum floor(n/p^k) for k ≥ 1 until p^k > n
        for (long long power = p; power <= n; power *= p) {
            count += n / power;
        }
        return count;
    }

    // Compute the maximum x such that k^x divides n!
    int maxKPower(int n, int k) {
        // Get prime factorization of k
        vector<vector<int> > factors = primeFactors(k);

        int result = INT_MAX;

        // For each prime factor (prime, expInK)
        for (auto& factor : factors) {
            int prime  = factor[0];
            int expInK = factor[1];

            // Count total exponent of 'prime' in n!
            int countInFact = legendre(n, prime);

            // Maximum x for this prime is floor(countInFact / expInK)
            result = min(result, countInFact / expInK);
        }

        return result;
    }
};

/*
 *
 * Dry Run
 *
 * Input: n = 10, k = 9
 * 1. primeFactors(9) → {{3, 2}}           // 9 = 3^2
 * 2. legendre(10, 3):
 *      power = 3 → count += 10/3 = 3
 *      power = 9 → count += 10/9 = 1
 *      power = 27 > 10 → stop; total = 4
 * 3. result = floor(4 / 2) = 2
 * Output: 2
 */

/************************************************************ JAVA ************************************************/

// Approach: Factorize k into primes, count each prime’s exponent in n! via Legendre’s formula, answer is min(countInFact/expInK) across primes.
// Time Complexity: O(√k + log_p n) per prime factor, overall roughly O(√k + π(k)·log n), efficient for n, k ≤ 10^5.
// Space Complexity: O(log k) for storing prime factors of k.
class Solution {
    public int maxKPower(int n, int k) {
        // Get prime factorization of k
        List<int[]> factors = primeFactors(k);
        int         result  = Integer.MAX_VALUE;

        // For each prime factor [prime, expInK]
        for (int[] factor : factors) {
            int prime  = factor[0];
            int expInK = factor[1];
            // Count total exponent of 'prime' in n!
            int countInFact = legendre(n, prime);
            // Maximum exponent x for this prime
            result = Math.min(result, countInFact / expInK);
        }
        return result;
    }

    // Factorize num into list of [prime, count]
    private List<int[]> primeFactors(int num) {
        List<int[]> factors = new ArrayList<>();
        int         count   = 0;

        // Count factor 2
        while (num % 2 == 0) {
            num /= 2;
            count++;
        }
        if (count > 0) {
            factors.add(new int[]{ 2, count });
        }
        // Check odd factors from 3 upward
        for (int i = 3; i* (long)i <= num; i += 2) {
            count = 0;
            while (num % i == 0) {
                num /= i;
                count++;
            }
            if (count > 0) {
                factors.add(new int[]{ i, count });
            }
        }
        // If remainder > 1, it's prime
        if (num > 1) {
            factors.add(new int[]{ num, 1 });
        }
        return factors;
    }

    // Legendre’s formula: count of p in n!
    private int legendre(int n, int p) {
        int count = 0;

        for (long power = p; power <= n; power *= p) {
            count += n / power;
        }
        return count;
    }
}

/*
 *
 * Dry Run
 *
 * Input: n = 10, k = 9
 * 1. primeFactors(9) → [[3, 2]]           // 9 = 3^2
 * 2. legendre(10, 3):
 *      power = 3 → count += 10/3 = 3
 *      power = 9 → count += 10/9 = 1
 *      power = 27 > 10 → stop; total = 4
 * 3. result = floor(4 / 2) = 2
 * Output: 2
 */
