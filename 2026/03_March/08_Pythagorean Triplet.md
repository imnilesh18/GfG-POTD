# 🟧 Pythagorean Triplet

<div align="center">

![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy: 24.77%](https://img.shields.io/badge/Accuracy-24.77%25-blue?style=for-the-badge)
![Points: 4](https://img.shields.io/badge/Points-4-success?style=for-the-badge)

</div>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📜 Problem Statement

Given an array `arr[]`, return `true` if there is a triplet `(a, b, c)` from the array (where `a`, `b`, and `c` are on different indexes) that satisfies **`a² + b² = c²`**, otherwise return `false`.

---

## 💡 Examples

```text
Input: arr[] = [3, 2, 4, 6, 5]
Output: true
Explanation: a=3, b=4, and c=5 forms a pythagorean triplet (9 + 16 = 25).
```

```text
Input: arr[] = [3, 8, 5]
Output: false
Explanation: No such triplet possible.
```

```text
Input: arr[] = [1, 1, 1]
Output: false
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

**Input:** `arr[] = [3, 2, 4, 6, 5]`

1. First, we look at the elements of the array: `3, 2, 4, 6, 5`
2. If we pick `a = 3` from index 0 and `b = 4` from index 2:
   - `a² = 3 * 3 = 9`
   - `b² = 4 * 4 = 16`
   - `a² + b² = 9 + 16 = 25`
3. Now, we search the array to see if there is any `c` whose square is `25`:
   - At index 4, `c = 5` is present.
   - `c² = 5 * 5 = 25`
4. Since the condition `9 + 16 = 25` (`a² + b² = c²`) is completely satisfied, and all three elements are at different indices, we return `true`.

</details>

---

## ⚙️ Constraints

> - `1 <= arr.size() <= 10^5`
> - `1 <= arr[i] <= 10^3`

---

## 🚀 Solution Approaches

Here we will discuss four different approaches, ranging from the most basic (Brute Force) to the most optimal.

### 1️⃣ Approach 1: Brute Force
In this approach, we use three nested loops and check all possible combinations to see if any form a valid Pythagorean triplet.

<details>
<summary><b>View C++ and Java Code (Brute Force)</b></summary>

#### C++
```cpp
// Intuition: We can check all possible triplets in the array using three nested loops to see if any satisfy the condition.
// Approach: Run three loops for pointers i, j, and k. For each triplet, calculate their squares and verify if a^2 + b^2 == c^2.
// Time Complexity: O(n^3) - Three nested loops traversing the array to check all combinations.
// Space Complexity: O(1) - No extra space is used.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            int a = arr[i];         // First element
            for (int j = i + 1; j < n; j++) {
                int b = arr[j];     // Second element
                for (int k = j + 1; k < n; k++) {
                    int c = arr[k]; // Third element

                    int a2 = a * a; // Square of a
                    int b2 = b * b; // Square of b
                    int c2 = c * c; // Square of c

                    // Check if any combination satisfies the Pythagorean triplet condition
                    if (a2 + b2 == c2 || b2 + c2 == a2 || a2 + c2 == b2) {
                        return true;
                    }
                }
            }
        }
        return false; // If no triplet found
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Triplets tried (a, b, c):
 *(3, 1, 4) => 9 + 1 != 16
 *(3, 1, 6) => 9 + 1 != 36
 *(3, 1, 5) => 9 + 1 != 25
 *(3, 4, 6) => 9 + 16 != 36
 *(3, 4, 5) => 9 + 16 == 25 => Found! Return true
 *
 */
```

#### Java
```java
// Intuition: We can check all possible triplets in the array using three nested loops to see if any satisfy the condition.
// Approach: Run three loops for pointers i, j, and k. For each triplet, calculate their squares and verify if a^2 + b^2 == c^2.
// Time Complexity: O(n^3) - Three nested loops traversing the array to check all combinations.
// Space Complexity: O(1) - No extra space is used.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            int a = arr[i];         // First element
            for (int j = i + 1; j < n; j++) {
                int b = arr[j];     // Second element
                for (int k = j + 1; k < n; k++) {
                    int c = arr[k]; // Third element

                    int a2 = a * a; // Square of a
                    int b2 = b * b; // Square of b
                    int c2 = c * c; // Square of c

                    // Check if any combination satisfies the Pythagorean triplet condition
                    if (a2 + b2 == c2 || b2 + c2 == a2 || a2 + c2 == b2) {
                        return true;
                    }
                }
            }
        }
        return false; // If no triplet found
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Triplets tried (a, b, c):
 *(3, 1, 4) => 9 + 1 != 16
 *(3, 1, 6) => 9 + 1 != 36
 *(3, 1, 5) => 9 + 1 != 25
 *(3, 4, 6) => 9 + 16 != 36
 *(3, 4, 5) => 9 + 16 == 25 => Found! Return true
 *
 */
```
</details>

---

### 2️⃣ Approach 2: Sorting and Two Pointers
This method reduces the problem to a variation of the "Two Sum" problem. We first square all the elements and then sort the array.

<details>
<summary><b>View C++ and Java Code (Two Pointers)</b></summary>

#### C++
```cpp
// Intuition: By squaring all elements and sorting them, the problem becomes similar to the classic "Two Sum" problem.
// Approach: Square each element, sort the array, fix the largest element (hypotenuse) from right to left, and use two pointers (left and right) to find if a valid sum exists.
// Time Complexity: O(n^2) - One loop iterating over elements and an inner two-pointer traversal.
// Space Complexity: O(1) - No extra space used apart from modifying the array in-place.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n; i++) {
            arr[i] = arr[i] * arr[i]; // Square each element
        }

        sort(begin(arr), end(arr));  // Sort the squared array

        // Fix one element (as hypotenuse) and use two pointers to find other two
        for (int i = n - 1; i >= 2; i--) {
            int target = arr[i]; // Hypotenuse

            int l = 0;
            int r = i - 1;

            while (l < r) {
                int sum = arr[l] + arr[r]; // Sum of two smaller squares

                if (sum == target) {
                    return true; // Found a valid triplet
                }

                (sum < target) ? l++ : r--; // Move pointers accordingly
            }
        }

        return false; // No triplet found
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * After squaring: [9, 1, 16, 36, 25]
 * After sorting: [1, 9, 16, 25, 36]
 * Fix 36 as hypotenuse
 * Check 1 + 25 = 26, move left pointer
 * Check 9 + 25 = 34, move left pointer
 * Check 16 + 25 = 41, move right pointer
 * Now fix 25 as hypotenuse
 * Check 1 + 16 = 17, move left pointer
 * Check 9 + 16 = 25 => Found! Return true
 *
 */
```

#### Java
```java
// Intuition: By squaring all elements and sorting them, the problem becomes similar to the classic "Two Sum" problem.
// Approach: Square each element, sort the array, fix the largest element (hypotenuse) from right to left, and use two pointers (left and right) to find if a valid sum exists.
// Time Complexity: O(n^2) - One loop iterating over elements and an inner two-pointer traversal.
// Space Complexity: O(1) - No extra space used apart from modifying the array in-place.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        for (int i = 0; i < n; i++) {
            arr[i] = arr[i] * arr[i]; // Square each element
        }

        Arrays.sort(arr); // Sort the squared array

        // Fix one element (as hypotenuse) and use two pointers
        for (int i = n - 1; i >= 2; i--) {
            int target = arr[i]; // Hypotenuse

            int l = 0;
            int r = i - 1;

            while (l < r) {
                int sum = arr[l] + arr[r]; // Sum of two smaller squares

                if (sum == target) {
                    return true; // Found a valid triplet
                }

                if (sum < target) {
                    l++; // Increase left pointer
                } else {
                    r--; // Decrease right pointer
                }
            }
        }

        return false; // No triplet found
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * After squaring: [9, 1, 16, 36, 25]
 * After sorting: [1, 9, 16, 25, 36]
 * Fix 36 as hypotenuse
 * Check 1 + 25 = 26, move left pointer
 * Check 9 + 25 = 34, move left pointer
 * Check 16 + 25 = 41, move right pointer
 * Now fix 25 as hypotenuse
 * Check 1 + 16 = 17, move left pointer
 * Check 9 + 16 = 25 => Found! Return true
 *
 */
```
</details>

---

### 3️⃣ Approach 3: Using Hash Set
We can use the mathematical formula `c = sqrt(a² + b²)` and leverage a HashSet for quick O(1) lookups to check if the exact `c` exists in the array.

<details>
<summary><b>View C++ and Java Code (Hash Set)</b></summary>

#### C++
```cpp
// Intuition: We can leverage the formula c = sqrt(a^2 + b^2) and check if c exists in O(1) time using a HashSet.
// Approach: Insert all array elements into a Set. Iterate through all possible pairs (a, b), calculate the hypotenuse 'c', and check if it is a perfect integer present in the set.
// Time Complexity: O(n^2) - We iterate through every unique pair in the array.
// Space Complexity: O(n) - We use a HashSet to store all the elements.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        // Insert all elements into a set for O(1) lookup
        unordered_set<int> st(arr.begin(), arr.end());

        // Check every pair (a, b) to see if there's a c such that c^2 = a^2 + b^2
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int a = arr[i];
                int b = arr[j];

                // Calculate potential value of c using Pythagoras theorem
                int c = sqrt(a * a + b * b);

                // If c is an integer and exists in the set, return true
                if (c * c == a * a + b * b && st.count(c)) {
                    return true;
                }
            }
        }

        // No valid Pythagorean triplet found
        return false;
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Set: {1, 3, 4, 5, 6}
 * Check pair (3, 1) → c = sqrt(10) → not integer
 * Check pair (3, 4) → c = sqrt(25) = 5 → 5 in set → Found! Return true
 *
 */
```

#### Java
```java
// Intuition: We can leverage the formula c = sqrt(a^2 + b^2) and check if c exists in O(1) time using a HashSet.
// Approach: Insert all array elements into a Set. Iterate through all possible pairs (a, b), calculate the hypotenuse 'c', and check if it is a perfect integer present in the set.
// Time Complexity: O(n^2) - We iterate through every unique pair in the array.
// Space Complexity: O(n) - We use a HashSet to store all the elements.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        // Insert all elements into a set for O(1) lookup
        Set<Integer> set = new HashSet<>();

        for (int num : arr) {
            set.add(num);
        }

        // Check every pair (a, b)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int a = arr[i];
                int b = arr[j];

                // Calculate potential c
                int c = (int)Math.sqrt(a * a + b * b);

                // If c is integer and exists in set, return true
                if (c * c == a * a + b * b && set.contains(c)) {
                    return true;
                }
            }
        }

        // No valid triplet found
        return false;
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * Set: {1, 3, 4, 5, 6}
 * Check pair (3, 1) → c = sqrt(10) → not integer
 * Check pair (3, 4) → c = sqrt(25) = 5 → 5 in set → Found! Return true
 *
 */
```
</details>

---

### 4️⃣ Approach 4: Optimized Boolean Array - 🏆 *Best Solution*
Since the maximum possible value in the array is very small (`1000`), we can use a frequency/boolean presence array (`visited array`). This allows us to solve the problem optimally in `O(maxEl²)`, avoiding TLE for large input sizes.

#### C++
```cpp
// Intuition: The maximum value constraint is very small (1000). We can leverage this to create a boolean presence array for extremely fast O(1) checks.
// Approach: Find the maximum element. Create a boolean 'visited' array of size maxEl + 1. Iterate through all possible values of (a, b) from 1 to maxEl and check for combinations.
// Time Complexity: O(maxEl^2) - We iterate over all pairs (a, b) from 1 to maxElement. Since maxEl <= 1000, operations stay well within bounds.
// Space Complexity: O(maxEl) - Auxiliary space required for the visited boolean array.
class Solution {
public:
    bool pythagoreanTriplet(vector<int>& arr) {
        int n = arr.size();

        // Step 1: Find the maximum element in the array
        int maxEl = 0;

        for (int i = 0; i < n; i++) {
            maxEl = max(maxEl, arr[i]);
        }
        // Alternate (cleaner) way: int maxEl = *max_element(arr.begin(), arr.end());

        // Step 2: Create a boolean array to mark presence of each number
        vector<bool> visited(maxEl + 1, false);
        for (int i = 0; i < n; i++) {
            visited[arr[i]] = true;
        }

        // Step 3: Try all possible combinations of a and b
        for (int a = 1; a <= maxEl; a++) {
            // Skip if 'a' is not present in original array
            if (!visited[a]) {
                continue;
            }

            for (int b = 1; b <= maxEl; b++) {
                // Skip if 'b' is not present
                if (!visited[b]) {
                    continue;
                }

                // Calculate c using Pythagoras theorem
                int c = sqrt(a * a + b * b);

                // Skip if c^2 is not a perfect square or c is out of bounds
                if (c * c != a * a + b * b || c > maxEl) {
                    continue;
                }

                // If c exists in the array, we found a Pythagorean triplet
                if (visited[c]) {
                    return true;
                }
            }
        }

        // No triplet found
        return false;
    }
};

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * maxEl = 6
 * visited[] = [false, true, false, true, true, true, true]
 * Try a = 3, b = 4 => c = sqrt(9 + 16) = sqrt(25) = 5 => 5 is present → Found! Return true
 *
 */
```

#### Java
```java
// Intuition: The maximum value constraint is very small (1000). We can leverage this to create a boolean presence array for extremely fast O(1) checks.
// Approach: Find the maximum element. Create a boolean 'visited' array of size maxEl + 1. Iterate through all possible values of (a, b) from 1 to maxEl and check for combinations.
// Time Complexity: O(maxEl^2) - We iterate over all pairs (a, b) from 1 to maxElement. Since maxEl <= 1000, operations stay well within bounds.
// Space Complexity: O(maxEl) - Auxiliary space required for the visited boolean array.
class Solution {
    boolean pythagoreanTriplet(int[] arr) {
        int n = arr.length;

        // Step 1: Find maximum element in array
        int maxEl = 0;

        for (int i = 0; i < n; i++) {
            maxEl = Math.max(maxEl, arr[i]);
        }

        // Step 2: Create a boolean array for presence check
        boolean[] visited = new boolean[maxEl + 1];
        for (int i = 0; i < n; i++) {
            visited[arr[i]] = true;
        }

        // Step 3: Try all combinations of a and b
        for (int a = 1; a <= maxEl; a++) {
            if (!visited[a]) {
                continue;
            }

            for (int b = 1; b <= maxEl; b++) {
                if (!visited[b]) {
                    continue;
                }

                int c = (int)Math.sqrt(a * a + b * b);

                if (c * c != a * a + b * b || c > maxEl) {
                    continue;
                }

                if (visited[c]) {
                    return true;
                }
            }
        }

        return false; // No triplet found
    }
}

/*
 *
 * Dry Run
 * Input: [3, 1, 4, 6, 5]
 * maxEl = 6
 * visited[] = [false, true, false, true, true, true, true]
 * Try a = 3, b = 4 => c = sqrt(25) = 5 → 5 is present → Found! Return true
 *
 */
```

---

## 🧠 Key Insights

- **Two Pointers Method:** This is a great way to solve the problem in `O(n²)`, but for large inputs like `n = 10^5`, it can cause **Time Limit Exceeded (TLE)**.
- **Optimized Frequency Array (Boolean Array):** The most optimal approach takes advantage of the maximum limit of array elements (`1000`). Since the loops only run up to `maxEl`, its runtime becomes `O(maxEl²)`, which is bounded by `10^6` operations in the worst case, making the code run instantly!

---

## 🔍 Further Exploration

Try solving other similar problems:
- 3Sum Problem (LeetCode & GFG)
- 4Sum Problem
- Two Sum Problem (Famous Two-Pointer or HashMap problem)

---

## 🔗 References

- **GeeksforGeeks Problem Link:** [Pythagorean Triplet](https://www.geeksforgeeks.org/problems/pythagorean-triplet3018/1)

---

## 👨‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

- `Arrays`
- `Two Pointers`
- `Hashing`
- `Math`
- `GeeksForGeeks`
- `Data Structures`