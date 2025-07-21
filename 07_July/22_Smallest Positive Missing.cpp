/*
 * GfG Link: https://www.geeksforgeeks.org/problems/smallest-positive-missing-number-1587115621/1
 *
 * Smallest Positive Missing
 *
 * Difficulty: Medium Accuracy: 25.13% Submissions: 432K+ Points: 4
 *
 * You are given an integer array arr[]. Your task is to find the smallest positive number missing from the array.
 * Note: Positive number starts from 1. The array can have negative integers too.
 *
 * Examples:
 *
 * Input: arr[] = [2, -3, 4, 1, 1, 7]
 * Output: 3
 * Explanation: Smallest positive missing number is 3.
 *
 * Input: arr[] = [5, 3, 2, 5, 1]
 * Output: 4
 * Explanation: Smallest positive missing number is 4.
 *
 * Input: arr[] = [-8, 0, -1, -4, -3]
 * Output: 1
 * Explanation: Smallest positive missing number is 1.
 *
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * -10^6 ≤ arr[i] ≤ 10^6
 */

/************************************************************ C++ ************************************************/

// Approach 1: Sort the vector first. Then, iterate through the sorted vector with a counter 'num' starting from 1. Skip any non-positive numbers and duplicates. The first element that doesn't match the counter 'num' indicates that 'num' is the smallest missing positive number.
// Time Complexity: O(N log N), because the sorting step (std::sort) is the most expensive operation. The subsequent linear scan is O(N).
// Space Complexity: O(log N), which is the typical space complexity for the Introsort algorithm used in std::sort.class Solution {
class Solution {
public:
    int missingNumber(std::vector<int>& arr) {
        // Get the size of the vector.
        int n = arr.size();

        // Sort the vector in non-decreasing order. This is the dominant operation.
        sort(arr.begin(), arr.end());

        // 'num' will track the smallest positive integer we expect to find.
        // We start by looking for 1.
        int num = 1;

        // Iterate through the sorted vector.
        for (int i = 0; i < n; i++) {
            // Ignore any numbers that are not positive.
            if (arr[i] <= 0) {
                continue;
            }

            // If the current number is the same as the previous one, it's a duplicate.
            // We've already processed this number, so we skip it.
            if (i > 0 && arr[i] == arr[i - 1]) {
                continue;
            }

            // If the current positive number from the vector does not match the
            // positive number we are looking for, it means 'num' is missing.
            if (arr[i] != num) {
                return num;
            }

            // If arr[i] matches num, it means we have found 'num'.
            // We increment 'num' to look for the next consecutive positive integer.
            num++;
        }

        // If the loop completes, it means all positive numbers in the vector were
        // consecutive starting from 1. The smallest missing one is the next number.
        return num;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = {2, -3, 4, 1, 1, 7}
 *
 * 1. Initialization:
 * - Sort arr: arr becomes {-3, 1, 1, 2, 4, 7}
 * - n = 6
 * - num = 1
 *
 * 2. Loop from i = 0 to 5
 *
 * - i = 0: arr[0] is -3. arr[i] <= 0 is true. Continue.
 *
 * - i = 1: arr[1] is 1.
 * - arr[i] <= 0 is false.
 * - Duplicate check is false (i=1).
 * - Check: (arr[1] != num) -> (1 != 1) -> False.
 * - They match, so increment num. num is now 2.
 *
 * - i = 2: arr[2] is 1.
 * - arr[i] <= 0 is false.
 * - Duplicate check: (arr[2] == arr[1]) -> (1 == 1) -> True. Continue.
 *
 * - i = 3: arr[3] is 2.
 * - arr[i] <= 0 is false.
 * - Duplicate check is false.
 * - Check: (arr[3] != num) -> (2 != 2) -> False.
 * - They match, so increment num. num is now 3.
 *
 * - i = 4: arr[4] is 4.
 * - arr[i] <= 0 is false.
 * - Duplicate check is false.
 * - Check: (arr[4] != num) -> (4 != 3) -> True. Condition met.
 *
 * 3. Return Value:
 * - The condition is met, so we return the current value of `num`.
 * - return 3
 *
 * Final Output: 3
 *
 */

// Approach 2: Use a hash set to store unique array elements for O(1) lookups. Iterate from i = 1 to n+1, maintaining two XOR sums: one for the ideal sequence (1 to i) and one for the numbers present in the set (up to i). The first time these XOR sums diverge, the missing number is their XOR result.
// Time Complexity: O(N), as we iterate through the array once to build the set and then loop up to N+1 times.
// Space Complexity: O(K), where K is the number of unique positive elements, for storing them in the hash set. In the worst case, this is O(N).
class Solution {
public:
    int missingNumber(std::vector<int>& arr) {
        // Use a hash set for O(1) average time complexity for lookups.
        // This also implicitly handles duplicate values from the input array.
        unordered_set<int> st(arr.begin(), arr.end());

        // Get the size of the input array. The missing number must be within [1, n+1].
        int n = arr.size();

        // This will hold the XOR sum of the ideal sequence of numbers: 1, 2, 3, ..., i.
        int xor_ideal = 0;

        // This will hold the XOR sum of the numbers that are actually present in the input array, up to i.
        int xor_present = 0;

        // The smallest missing positive number must be in the range [1, n + 1].
        // For example, if arr = [1, 2, 3], n=3, the missing number is 4 (n+1).
        for (int i = 1; i <= n + 1; ++i) {
            // Continuously update the XOR sum for the ideal sequence.
            // After iteration i, xor_ideal = 1 ^ 2 ^ ... ^ i.
            xor_ideal ^= i;

            // Check if the current number 'i' exists in our set of unique input numbers.
            if (st.count(i)) {
                // If it exists, update the XOR sum of present numbers.
                xor_present ^= i;
            }

            // If the XOR sum of the ideal sequence is different from the XOR sum of the
            // numbers we've actually found, it means we've just passed the first missing number.
            if (xor_ideal != xor_present) {
                // The missing number is the XOR of these two sums.
                // This works because (1^2^...^k) ^ (1^2^...^(k-1)) = k.
                // Here, 'k' is the missing number.
                return xor_ideal ^ xor_present;
            }
        }

        // This line is technically unreachable given the problem constraints,
        // as a missing number in the range [1, n+1] is guaranteed.
        // It's included to handle all control paths for the compiler.
        return 1;
    }
};

/*
 *
 * Dry Run
 *
 * Input: arr[] = [2, -3, 4, 1, 1, 7]
 *
 * 1. Initialization:
 * - st (unordered_set) = {1, 2, 4, 7, -3}  // Duplicates are removed
 * - n = 6
 * - xor_ideal = 0
 * - xor_present = 0
 *
 * 2. Loop from i = 1 to n + 1 (i.e., 1 to 7)
 *
 * - i = 1:
 * - xor_ideal = 0 ^ 1 = 1
 * - st.count(1) is true.
 * - xor_present = 0 ^ 1 = 1
 * - Check: (xor_ideal == xor_present) -> (1 == 1) -> True. Continue.
 *
 * - i = 2:
 * - xor_ideal = 1 ^ 2 = 3
 * - st.count(2) is true.
 * - xor_present = 1 ^ 2 = 3
 * - Check: (xor_ideal == xor_present) -> (3 == 3) -> True. Continue.
 *
 * - i = 3:
 * - xor_ideal = 3 ^ 3 = 0
 * - st.count(3) is false.
 * - xor_present remains 3.
 * - Check: (xor_ideal != xor_present) -> (0 != 3) -> True. Condition met.
 *
 * 3. Return Value:
 * - The condition is met, so we return `xor_ideal ^ xor_present`.
 * - return 0 ^ 3 = 3
 *
 * Final Output: 3
 *
 */

/************************************************************ JAVA ************************************************/

// Approach 1: Sort the array first. Then, iterate through the sorted array with a counter 'num' starting from 1. Skip any non-positive numbers and duplicates. The first element that doesn't match the counter 'num' indicates that 'num' is the smallest missing positive number.
// Time Complexity: O(N log N), because the sorting step (Arrays.sort) is the most expensive operation. The subsequent linear scan is O(N).
// Space Complexity: O(log N) to O(N), which is the space complexity for the sorting algorithm used in Java's Arrays.sort.
class Solution {
    // Function to find the smallest positive number missing from the array.
    public int missingNumber(int[] arr) {
        // Get the size of the array.
        int n = arr.length;

        // Sort the array in non-decreasing order. This is the dominant operation.
        Arrays.sort(arr);

        // 'num' will track the smallest positive integer we expect to find.
        // We start by looking for 1.
        int num = 1;

        // Iterate through the sorted array.
        for (int i = 0; i < n; i++) {
            // Ignore any numbers that are not positive.
            if (arr[i] <= 0) {
                continue;
            }

            // If the current number is the same as the previous one, it's a duplicate.
            // We've already processed this number, so we skip it.
            if (i > 0 && arr[i] == arr[i - 1]) {
                continue;
            }

            // If the current positive number from the array does not match the
            // positive number we are looking for, it means 'num' is missing.
            if (arr[i] != num) {
                return num;
            }

            // If arr[i] matches num, it means we have found 'num'.
            // We increment 'num' to look for the next consecutive positive integer.
            num++;
        }

        // If the loop completes, it means all positive numbers in the array were
        // consecutive starting from 1. The smallest missing one is the next number.
        return num;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = {2, -3, 4, 1, 1, 7}
 *
 * 1. Initialization:
 * - Sort arr: arr becomes {-3, 1, 1, 2, 4, 7}
 * - n = 6
 * - num = 1
 *
 * 2. Loop from i = 0 to 5
 *
 * - i = 0: arr[0] is -3. arr[i] <= 0 is true. Continue.
 *
 * - i = 1: arr[1] is 1.
 * - arr[i] <= 0 is false.
 * - Duplicate check is false (i=1).
 * - Check: (arr[1] != num) -> (1 != 1) -> False.
 * - They match, so increment num. num is now 2.
 *
 * - i = 2: arr[2] is 1.
 * - arr[i] <= 0 is false.
 * - Duplicate check: (arr[2] == arr[1]) -> (1 == 1) -> True. Continue.
 *
 * - i = 3: arr[3] is 2.
 * - arr[i] <= 0 is false.
 * - Duplicate check is false.
 * - Check: (arr[3] != num) -> (2 != 2) -> False.
 * - They match, so increment num. num is now 3.
 *
 * - i = 4: arr[4] is 4.
 * - arr[i] <= 0 is false.
 * - Duplicate check is false.
 * - Check: (arr[4] != num) -> (4 != 3) -> True. Condition met.
 *
 * 3. Return Value:
 * - The condition is met, so we return the current value of `num`.
 * - return 3
 *
 * Final Output: 3
 *
 */

// Approach 2: Use a HashSet to store unique array elements for O(1) lookups. Iterate from i = 1 to n+1, maintaining two XOR sums: one for the ideal sequence (1 to i) and one for the numbers present in the set (up to i). The first time these XOR sums diverge, the missing number is their XOR result.
// Time Complexity: O(N), as we iterate through the array once to build the set and then loop up to N+1 times.
// Space Complexity: O(K), where K is the number of unique positive elements, for storing them in the HashSet. In the worst case, this is O(N).
class Solution {
    public int missingNumber(int[] arr) {
        // Use a HashSet for O(1) average time complexity for lookups.
        // This also implicitly handles duplicate values from the input array.
        Set<Integer> st = new HashSet<>();

        for (int num : arr) {
            st.add(num);
        }

        // Get the size of the input array. The missing number must be within [1, n+1].
        int n = arr.length;

        // This will hold the XOR sum of the ideal sequence of numbers: 1, 2, 3, ..., i.
        int xor_ideal = 0;

        // This will hold the XOR sum of the numbers that are actually present in the input array, up to i.
        int xor_present = 0;

        // The smallest missing positive number must be in the range [1, n + 1].
        // For example, if arr = [1, 2, 3], n=3, the missing number is 4 (n+1).
        for (int i = 1; i <= n + 1; ++i) {
            // Continuously update the XOR sum for the ideal sequence.
            // After iteration i, xor_ideal = 1 ^ 2 ^ ... ^ i.
            xor_ideal ^= i;

            // Check if the current number 'i' exists in our set of unique input numbers.
            if (st.contains(i)) {
                // If it exists, update the XOR sum of present numbers.
                xor_present ^= i;
            }

            // If the XOR sum of the ideal sequence is different from the XOR sum of the
            // numbers we've actually found, it means we've just passed the first missing number.
            if (xor_ideal != xor_present) {
                // The missing number is the XOR of these two sums.
                // This works because (1^2^...^k) ^ (1^2^...^(k-1)) = k.
                // Here, 'k' is the missing number.
                return xor_ideal ^ xor_present;
            }
        }

        // This line is technically unreachable given the problem constraints,
        // as a missing number in the range [1, n+1] is guaranteed.
        // It's included to handle all control paths for the compiler.
        return 1;
    }
}

/*
 *
 * Dry Run
 *
 * Input: arr[] = {2, -3, 4, 1, 1, 7}
 *
 * 1. Initialization:
 * - st (HashSet) = {1, 2, 4, 7, -3}  // Duplicates are removed
 * - n = 6
 * - xor_ideal = 0
 * - xor_present = 0
 *
 * 2. Loop from i = 1 to n + 1 (i.e., 1 to 7)
 *
 * - i = 1:
 * - xor_ideal = 0 ^ 1 = 1
 * - st.contains(1) is true.
 * - xor_present = 0 ^ 1 = 1
 * - Check: (xor_ideal == xor_present) -> (1 == 1) -> True. Continue.
 *
 * - i = 2:
 * - xor_ideal = 1 ^ 2 = 3
 * - st.contains(2) is true.
 * - xor_present = 1 ^ 2 = 3
 * - Check: (xor_ideal == xor_present) -> (3 == 3) -> True. Continue.
 *
 * - i = 3:
 * - xor_ideal = 3 ^ 3 = 0
 * - st.contains(3) is false.
 * - xor_present remains 3.
 * - Check: (xor_ideal != xor_present) -> (0 != 3) -> True. Condition met.
 *
 * 3. Return Value:
 * - The condition is met, so we return `xor_ideal ^ xor_present`.
 * - return 0 ^ 3 = 3
 *
 * Final Output: 3
 *
 */
