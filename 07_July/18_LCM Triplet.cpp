/*
 * GfG Link: https://www.geeksforgeeks.org/problems/lcm-triplet1501/1
 *
 * LCM Triplet
 *
 * Difficulty: Medium Accuracy: 50.13% Submissions: 19K+ Points: 4
 *
 * Given a number n. Find the maximum possible LCM that can be obtained by selecting three numbers less than or equal to n.
 * Note : LCM stands for Lowest Common Multiple.
 *
 * Examples:
 *
 * Input: n = 9
 * Output: 504
 * Explanation: 504 is the maximum LCM that can be attained by any triplet of numbers less than or equal 9. The triplet which has this LCM is {7, 8, 9}.
 *
 * Input: n = 7
 * Output: 210
 * Explanation: 210 is the maximum LCM that can be attained by any triplet of numbers less than or equal 7. The triplet which has this LCM is {5, 6, 7}.
 *
 * Constraints:
 * 1 ≤ n ≤ 10^3
 */

/************************************************************ C++ ************************************************/

// Approach 1: Brute‑force try every triplet (i, j, k) ≤ n, compute their LCM via GCD, and keep the maximum.
// Time Complexity: O(n^3 · log n) — three nested loops over n, each LCM uses GCD which is O(log n).
// Space Complexity: O(1) — only a few integer variables are used.
class Solution {
public:
    // Compute GCD of a and b using the Euclidean algorithm.
    // gcd(a, b) = gcd(b % a, a) until a == 0.
    int gcd(int a, int b) {
        if (a == 0) {
            return b;                  // Base case: gcd(0, b) = b
        }
        return gcd(b % a, a);          // Recursive step
    }

    // Compute LCM of a and b via the formula lcm(a, b) = (a / gcd(a,b)) * b.
    int lcm(int a, int b) {
        int g = gcd(a, b);             // find common divisor

        return (a / g) * b;            // avoid overflow: divide first
    }

    int lcmTriplets(int n) {
        int maxLCM = 1;                // will hold the max found so far

        // Try all i, j, k with 1 ≤ i ≤ j ≤ k ≤ n
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= n; ++j) {
                for (int k = j; k <= n; ++k) {
                    // Compute LCM(i, j, k) = lcm(lcm(i,j), k)
                    int l1  = lcm(i, j);
                    int cur = lcm(l1, k);
                    // Update maximum if this triplet gives a larger LCM
                    if (cur > maxLCM) {
                        maxLCM = cur;
                    }
                }
            }
        }
        return maxLCM;
    }
};

/*
 *
 * Dry Run for n = 9:
 * 1) Initialize maxLCM = 1.
 * 2) Outer loop i=1..9
 *    - i=1: j=1..9, k=j..9 → all LCMs ≤ 504, but maxLCM updates gradually.
 *    ...
 *    - i=7: j=7..9
 *        • j=7: k=7 → lcm(7,7)=7 → lcm(7,7)=7 → maxLCM=7
 *               k=8 → lcm(7,8)=56 → lcm(56,8)=56 → maxLCM=56
 *               k=9 → lcm(7,8)=56 → lcm(56,9)=504 → maxLCM=504 ★
 *        • j=8: k=8→ lcm(7,8)=56→lcm(56,8)=56 (no change)
 *               k=9→ lcm(8,8)=8→lcm(8,9)=72 (no change)
 *        • j=9: k=9→ lcm(7,9)=63→lcm(63,9)=63 (no change)
 *    - i=8,9: no triplet exceeds 504.
 * 3) Final maxLCM = 504.
 *
 */

// Approach 2: Pattern‑based pick of three large coprime (or low‑overlap) numbers:
//   • if n is odd → choose (n, n-1, n-2)
//   • else if n%2==0 and gcd(n,n-3)==1 → choose (n, n-1, n-3)
//   • else → choose (n-1, n-2, n-3)
// Time Complexity: O(log n) for one gcd check → O(1) effectively.
// Space Complexity: O(1).
class Solution {
public:
    // Compute GCD by Euclid.
    int gcd(int a, int b) {
        return a == 0 ? b : gcd(b % a, a);
    }

    int lcmTriplets(int n) {
        if (n < 3) {
            // fewer than 3 numbers → return n itself
            return n;
        }

        if (n % 2 == 1) {
            // odd n → consecutive numbers cover both parities
            return n * (n - 1) * (n - 2);
        }

        // even n → skip one of the evens if possible
        if (gcd(n, n - 3) == 1) {
            // n and n-3 coprime → good spread
            return n * (n - 1) * (n - 3);
        }

        // otherwise drop n entirely → three consecutive odd/even mix
        return (n - 1) * (n - 2) * (n - 3);
    }
};

/*
 *
 * Dry Run for n = 9:
 * 1) Check n < 3? 9<3 → false.
 * 2) Check n%2==1? 9%2=1 → true.
 *    → compute 9 * 8 * 7 = 504.
 * 3) Return 504.
 *
 */

// Approach 3: Simplified pattern‑based conditional:
//   • if n odd → n*(n-1)*(n-2)
//   • else if n%3!=0 → n*(n-1)*(n-3)
//   • else → (n-1)*(n-2)*(n-3)
// Time Complexity: O(1).
// Space Complexity: O(1).
class Solution {
public:
    int lcmTriplets(int n) {
        if (n < 3) {
            // cannot form three numbers
            return n;
        } else if (n % 2 == 1) {
            // odd n: best three consecutive
            return n * (n - 1) * (n - 2);
        } else if (n % 3 != 0) {
            // even but not divisible by 3: skip n-2
            return n * (n - 1) * (n - 3);
        } else {
            // divisible by 2 and 3 → pick previous three
            return (n - 1) * (n - 2) * (n - 3);
        }
    }
};

/*
 *
 * Dry Run for n = 9:
 * 1) n<3? false.
 * 2) n%2==1? 9%2=1 → true → compute 9*8*7 = 504.
 * 3) Return 504.
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Brute‑force try every triplet (i, j, k) ≤ n, compute their LCM via GCD, and keep the maximum.
// Time Complexity: O(n^3 · log n) — three nested loops over n, each LCM uses GCD which is O(log n).
// Space Complexity: O(1) — only a few integer variables are used.
class Solution {
    // Compute GCD of a and b using the Euclidean algorithm.
    private int gcd(int a, int b) {
        if (a == 0) {
            return b;                  // Base case: gcd(0, b) = b
        }
        return gcd(b % a, a);          // Recursive step
    }

    // Compute LCM of a and b via the formula lcm(a, b) = (a / gcd(a,b)) * b.
    private int lcm(int a, int b) {
        int g = gcd(a, b);             // find common divisor

        return (a / g) * b;            // avoid overflow: divide first
    }

    public int lcmTriplets(int n) {
        int maxLCM = 1;                // will hold the max found so far

        // Try all i, j, k with 1 ≤ i ≤ j ≤ k ≤ n
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                for (int k = j; k <= n; k++) {
                    // Compute LCM(i, j, k) = lcm(lcm(i,j), k)
                    int l1  = lcm(i, j);
                    int cur = lcm(l1, k);
                    // Update maximum if this triplet gives a larger LCM
                    if (cur > maxLCM) {
                        maxLCM = cur;
                    }
                }
            }
        }
        return maxLCM;
    }
}

/*
 *
 * Dry Run for n = 9:
 * 1) maxLCM = 1.
 * 2) i=1..9:
 *    ...
 *    i=7:
 *      j=7: k=7→lcm(7,7)=7→lcm(7,7)=7→maxLCM→7
 *             k=8→lcm(7,8)=56→lcm(56,8)=56→maxLCM→56
 *             k=9→lcm(7,8)=56→lcm(56,9)=504→maxLCM→504 ★
 *      j=8: k=8→lcm(7,8)=56→lcm(56,8)=56
 *             k=9→lcm(8,8)=8→lcm(8,9)=72
 *      j=9: k=9→lcm(7,9)=63→lcm(63,9)=63
 *    i=8,9: no larger LCM.
 * 3) Return 504.
 *
 */

// Approach 2: Pattern‑based pick of three large coprime (or low‑overlap) numbers:
//   • if n is odd → choose (n, n-1, n-2)
//   • else if n%2==0 and gcd(n,n-3)==1 → choose (n, n-1, n-3)
//   • else → choose (n-1, n-2, n-3)
// Time Complexity: O(log n) for one gcd check → O(1) effectively.
// Space Complexity: O(1).
class Solution {
    // Euclidean GCD
    private int gcd(int a, int b) {
        return a == 0 ? b : gcd(b % a, a);
    }

    public int lcmTriplets(int n) {
        if (n < 3) {
            return n;            // fewer than three → return n
        }

        if (n % 2 != 0) {
            // odd n
            return n * (n - 1) * (n - 2);
        }

        // even n
        if (gcd(n, n - 3) == 1) {
            return n * (n - 1) * (n - 3);
        }
        
        return (n - 1) * (n - 2) * (n - 3);
    }
}

/*
 *
 * Dry Run for n = 9:
 * - n<3? No.
 * - n%2!=0? 9%2=1 → yes.
 *   compute 9×8×7 = 504.
 * - Return 504.
 *
 */

// Approach 3: Simplified pattern‑based conditional:
//   • if n odd → n*(n-1)*(n-2)
//   • else if n%3!=0 → n*(n-1)*(n-3)
//   • else → (n-1)*(n-2)*(n-3)
// Time Complexity: O(1).
// Space Complexity: O(1).
class Solution {
    public int lcmTriplets(int n) {
        if (n < 3) {
            return n;            // cannot form three numbers
        } else if (n % 2 != 0) {
            // odd n: best three consecutive
            return n * (n - 1) * (n - 2);
        } else if (n % 3 != 0) {
            // even but not divisible by 3: skip n-2
            return n * (n - 1) * (n - 3);
        } else {
            // divisible by 2 and 3 → pick previous three
            return (n - 1) * (n - 2) * (n - 3);
        }
    }
}

/*
 *
 * Dry Run for n = 9:
 * a) Check n<3? No.
 * b) Check n%2!=0? 9%2=1 → yes → product = 9*8*7 = 504.
 * c) Return 504.
 *
 */
