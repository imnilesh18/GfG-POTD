/*
 * Prime List
 *
 * Difficulty: Medium Accuracy: 53.68% Submissions: 36K+ Points: 4
 *
 * You are given the head of a linked list. You have to replace all the values of the nodes with the nearest prime number. If more than one prime number exists at an equal distance, choose the smallest one. Return the head of the modified linked list.
 *
 * Examples :
 *
 * Input: head = 2 → 6 → 10
 * Output: 2 → 5 → 11
 * Explanation: The nearest prime of 2 is 2 itself. The nearest primes of 6 are 5 and 7, since 5 is smaller so, 5 will be chosen. The nearest prime of 10 is 11.
 *
 * Input: head = 1 → 15 → 20
 * Output: 2 → 13 → 19
 * Explanation: The nearest prime of 1 is 2. The nearest primes of 15 are 13 and 17, since 13 is smaller so, 13 will be chosen. The nearest prime of 20 is 19.
 * Constraints:
 * 1 <= no. of Nodes <= 10^4
 * 1 <= node.val <= 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use Sieve of Eratosthenes to precompute primes up to 2 * max node value, then for each node, find the nearest prime by searching in both directions.
// Time Complexity: O(N * sqrt(M) + M), where N is number of nodes and M is max node value (for sieve and lookup).
// Space Complexity: O(M), where M is space used for the prime sieve array.
class Solution {
public:
    // Function to generate all prime numbers up to n using Sieve of Eratosthenes
    vector<int> findPrimes(int n) {
        vector<int> primes(n + 1, 1); // initialize all as prime (1)

        primes[0] = 0;                // 0 is not a prime
        primes[1] = 0;                // 1 is not a prime

        // Sieve of Eratosthenes logic to mark non-primes
        for (int i = 2; i* i <= n; i++) {
            if (primes[i]) {
                for (int j = i * i; j <= n; j += i) {
                    primes[j] = 0;   // mark as non-prime
                }
            }
        }
        return primes;   // return the prime map
    }
    // Main function to replace each node's value with the nearest prime
    Node* primeList(Node* head) {
        int   max_num = 0;
        Node* temp    = head;

        // Step 1: Find the maximum value in the linked list
        while (temp != NULL) {
            max_num = max(max_num, temp->val);
            temp    = temp->next;
        }

        // Step 2: Generate primes up to 2 * max_num for safety
        vector<int> primes = findPrimes(2 * max_num);

        temp = head;
        // Step 3: Traverse the list and update each node's value
        while (temp != NULL) {
            int num = temp->val;

            if (num == 1) {
                temp->val = 2;   // nearest prime to 1 is 2
            } else {
                int num1 = num, num2 = num;
                // Search for the closest prime less than or equal to num
                while (!primes[num1]) {
                    num1--;
                }
                // Search for the closest prime greater than or equal to num
                while (!primes[num2]) {
                    num2++;
                }

                // Choose the closer prime, or the smaller one in case of tie
                if (num - num1 > num2 - num) {
                    temp->val = num2;
                } else {
                    temp->val = num1;
                }
            }

            temp = temp->next;   // move to next node
        }

        return head;   // return updated list head
    }
};

/*
 *
 * Dry Run
 *
 * Input: 1 → 15 → 20
 *
 * Step 1: max_num = 20
 * Step 2: Generate primes up to 40 using Sieve.
 * Step 3:
 *   Node 1: val = 1 → nearest prime = 2 → update to 2
 *   Node 2: val = 15 → nearest primes = 13 and 17 → 13 is smaller → update to 13
 *   Node 3: val = 20 → nearest primes = 19 and 23 → 19 is closer → update to 19
 *
 * Final Output: 2 → 13 → 19
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use Sieve of Eratosthenes to precompute prime numbers up to 2 * max node value. Then, for each node, find the nearest prime by checking both downward and upward from the node's value.
// Time Complexity: O(N + M log(log M)), where N = number of nodes, M = max node value. Finding max and updating values is O(N); Sieve is O(M log(log M)).
// Space Complexity: O(M), for the boolean prime array.
class Solution {
    // Sieve function to precompute primes up to n
    private boolean[] findPrimes(int n) {
        boolean[] isPrime = new boolean[n + 1];
        Arrays.fill(isPrime, true);
        isPrime[0] = false;
        isPrime[1] = false;

        // Sieve logic
        for (int i = 2; i* i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        return isPrime;
    }
    Node primeList(Node head) {
        int  maxVal = 0;
        Node temp   = head;

        // Step 1: Find the maximum value in the list
        while (temp != null) {
            maxVal = Math.max(maxVal, temp.val);
            temp   = temp.next;
        }

        // Step 2: Generate prime numbers up to 2 * maxVal
        boolean[] primes = findPrimes(2 * maxVal);

        temp = head;
        // Step 3: Traverse and update node values
        while (temp != null) {
            int num = temp.val;

            if (num == 1) {
                temp.val = 2; // nearest prime to 1 is 2
            } else {
                int left  = num;
                int right = num;

                // find nearest lower/equal prime
                while (left > 1 && !primes[left]) {
                    left--;
                }

                // find nearest higher/equal prime
                while (right < primes.length && !primes[right]) {
                    right++;
                }

                // choose closer prime or smaller one if tie
                if ((num - left) > (right - num)) {
                    temp.val = right;
                } else {
                    temp.val = left;
                }
            }

            temp = temp.next; // move to next node
        }

        return head; // return modified list
    }
}

/*
 *
 * Dry Run
 *
 * Input: 1 → 15 → 20
 *
 * Step 1: maxVal = 20
 * Step 2: Generate primes up to 40
 * Step 3:
 *   Node 1: val = 1 → nearest prime = 2 → update to 2
 *   Node 2: val = 15 → nearest primes = 13, 17 → pick 13 (smaller)
 *   Node 3: val = 20 → nearest primes = 19, 23 → pick 19 (closer)
 *
 * Output: 2 → 13 → 19
 *
 */
