# 📈 Find H-Index

<div align="center">

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/find-h-index--165609/1).

</div>

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-296200?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-53.4%25-green.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)

</div>

---

## Problem Statement

You are given an array `citations[]`, where each element `citations[i]` represents the number of citations received by the `i`th paper of a researcher. You have to calculate the researcher’s **H-index**.

The **H-index** is defined as the maximum value `H`, such that the researcher has published at least `H` papers, and all those papers have a citation value greater than or equal to `H`.

---

## Examples

Here are a few examples to illustrate the problem:

**Example 1:**
```
Input: citations[] = [3, 0, 5, 3, 0]
Output: 3
Explanation: There are at least 3 papers with citation counts of 3, 5, and 3, all having citations greater than or equal to 3.
```

<details>
<summary>📖 Example Breakdown</summary>
<div>

Let's walk through the first example: `citations[] = [3, 0, 5, 3, 0]`.

1.  **Total number of papers (N):** 5.
2.  The H-index can be at most 5. Let's check possible values for H from N down to 1.
    * **Can H be 5?** We need at least 5 papers with 5 or more citations. The array is `[3, 0, 5, 3, 0]`. Only one paper (`5`) meets this criterion. So, H cannot be 5.
    * **Can H be 4?** We need at least 4 papers with 4 or more citations. Only one paper (`5`) meets this. So, H cannot be 4.
    * **Can H be 3?** We need at least 3 papers with 3 or more citations. The papers with citations `[3, 5, 3]` meet this criterion. We have exactly 3 such papers. Since the condition (at least 3 papers >= 3 citations) is met, H can be 3.
3.  Since we are looking for the *maximum* such H, and we found that H=3 works, this is our answer.

</div>
</details>

**Example 2:**
```
Input: citations[] = [5, 1, 2, 4, 1]
Output: 2
Explanation: There are 3 papers (with citation counts of 5, 2, and 4) that have 2 or more citations. However, the H-Index cannot be 3 because there aren't 3 papers with 3 or more citations.
```

**Example 3:**
```
Input: citations[] = [0, 0]
Output: 0
Explanation: The H-index is 0 because there are no papers with at least 1 citation.
```

---

## Constraints

<div align="center">

`1 ≤ citations.size() ≤ 10^6`
`0 ≤ citations[i] ≤ 10^6`

</div>

---

## Solution Approaches

### 1. Brute-Force Approach

The brute-force approach involves testing every possible H-index value from `N` down to `0`. For each potential value `h`, we iterate through the entire `citations` array to count how many papers have `h` or more citations. If the count is greater than or equal to `h`, we've found the H-index because we are checking in descending order.

#### C++ (Brute-Force)
```cpp
// Intuition: The most straightforward way is to check every possible value for the H-Index.
// Approach: Iterate from the maximum possible H-Index (N) down to 1. For each value `h`,
//           count how many papers have at least `h` citations. The first `h` for which
//           this count is >= `h` is the H-Index.
// Time Complexity: O(N^2), where N is the number of papers. For each of the N possible h-values, we traverse the array (N times).
// Space Complexity: O(1), as no extra space is used besides a few variables.
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        for (int h = n; h > 0; --h) {
            int count = 0;
            for (int citation : citations) {
                if (citation >= h) {
                    count++;
                }
            }
            if (count >= h) {
                return h; // First h that satisfies the condition is the max
            }
        }
        return 0; // If no such h is found
    }
};
/*
*
* Dry Run
* Input: citations[] = [3, 0, 5, 3, 0]
* n = 5
*
* h = 5: count papers with citations >= 5 is 1. (1 < 5). Continue.
* h = 4: count papers with citations >= 4 is 1. (1 < 4). Continue.
* h = 3: count papers with citations >= 3 is 3. (3 >= 3). Condition met. Return 3.
*
*/
```

### 2. Optimized Approach (Binary Search)

After sorting the `citations` array, the problem has a clear monotonic property. If an H-index `h` is possible, any value smaller than `h` is also a possibility. This structure allows us to use binary search on the *number of papers* to find the optimal `H` value efficiently.

#### C++ (Optimized)
```cpp
// Intuition: After sorting the citations, if a paper at index `i` satisfies the H-index condition,
//            all papers to its right also will. This monotonic property allows us to use binary search.
//            The search space is the possible values of H-index, from 0 to N.
// Approach: First, sort the citations array in ascending order. Then, apply binary search.
//           For any `mid` index, the number of papers with at least `citations[mid]` citations is `n - mid`.
//           Let this count be `h`. If `citations[mid]` >= `h`, it means we have `h` papers with at least `h` citations,
//           which is a valid H-index. We store this `h` as a potential answer and try for a larger H-index
//           by searching in the left half (`high = mid - 1`). Otherwise, we need more citations, so we search
//           in the right half (`low = mid + 1`).
// Time Complexity: O(N log N) - The sorting step dominates the O(log N) binary search.
// Space Complexity: O(1) - The sorting is done in-place, and we only use a few variables for binary search.
class Solution {
public:
    // Function to find H-Index using Binary Search
    int hIndex(vector<int>& citations){
       int n = citations.size();    // Get the number of papers

       // Sort the citations array in ascending order
       sort(citations.begin(), citations.end());

       // Initialize binary search boundaries
       int low = 0, high = n - 1, hIndex = 0;

       // Perform binary search
       while (low <= high) {
           // Calculate the middle index
           int mid = low + (high - low) / 2;

           // h is the potential H-Index, determined by the number of papers
           // from mid to the end.
           int h = n - mid;

           // Check if the citation count at mid satisfies the H-Index condition
           if (citations[mid] >= h) {
               // If valid, this is a potential H-Index. Store it.
               hIndex = h;
               // Try for a better (larger) h-index in the left half
               high   = mid - 1;
           } else {
               // If not valid, we need higher citation counts, so search the right half
               low = mid + 1;
           }
       }

       return hIndex;    // Return the maximum H-Index found
    }
};
/*
*
* Dry Run
* Input: citations[] = [3, 0, 5, 3, 0]
* Sorted: citations[] = [0, 0, 3, 3, 5], n = 5
*
* Initial: low = 0, high = 4, hIndex = 0
*
* Iteration 1:
* mid = 0 + (4-0)/2 = 2
* h = 5 - 2 = 3
* citations[2] (which is 3) >= h (which is 3)? Yes.
* Condition met. This is a valid H-index.
* hIndex = 3.
* Search for a potentially larger H-index: high = mid - 1 = 1.
*
* Iteration 2:
* low = 0, high = 1
* mid = 0 + (1-0)/2 = 0
* h = 5 - 0 = 5
* citations[0] (which is 0) >= h (which is 5)? No.
* Condition not met. Need more citations.
* low = mid + 1 = 1.
*
* Iteration 3:
* low = 1, high = 1
* mid = 1 + (1-1)/2 = 1
* h = 5 - 1 = 4
* citations[1] (which is 0) >= h (which is 4)? No.
* Condition not met. Need more citations.
* low = mid + 1 = 2.
*
* Loop ends because low (2) > high (1).
* Return final hIndex = 3.
*
*/
```

#### Java (Optimized)
```java
// Intuition: After sorting the citations, if a paper at index `i` satisfies the H-index condition,
//            all papers to its right also will. This monotonic property allows us to use binary search.
//            The search space is the possible values of H-index, from 0 to N.
// Approach: First, sort the citations array in ascending order. Then, apply binary search.
//           For any `mid` index, the number of papers with at least `citations[mid]` citations is `n - mid`.
//           Let this count be `h`. If `citations[mid]` >= `h`, it means we have `h` papers with at least `h` citations,
//           which is a valid H-index. We store this `h` as a potential answer and try for a larger H-index
//           by searching in the left half (`high = mid - 1`). Otherwise, we need more citations, so we search
//           in the right half (`low = mid + 1`).
// Time Complexity: O(N log N) - The sorting step dominates the O(log N) binary search.
// Space Complexity: O(1) or O(log N) depending on the Java sort implementation, but constant auxiliary space otherwise.
class Solution {
    // Function to find the H-Index using Binary Search
    public int hIndex(int[] citations) {
        int n = citations.length; // Get the number of papers

        // Sort the citations array in ascending order
        Arrays.sort(citations);

        // Initialize binary search boundaries
        int low = 0, high = n - 1, hIndex = 0;

        // Perform binary search
        while (low <= high) {
            // Calculate the middle index
            int mid = low + (high - low) / 2;

            // h is the potential H-Index, determined by the number of papers
            // from mid to the end.
            int h = n - mid;

            // Check if the citation count at mid satisfies the H-Index condition
            if (citations[mid] >= h) {
                // If valid, this is a potential H-Index. Store it.
                hIndex = h;
                // Try for a better (larger) h-index in the left half
                high = mid - 1;
            } else {
                // If not valid, we need higher citation counts, so search the right half
                low = mid + 1;
            }
        }

        return hIndex; // Return the maximum H-Index found
    }
}
/*
*
* Dry Run
* Input: citations[] = [3, 0, 5, 3, 0]
* Sorted: citations[] = [0, 0, 3, 3, 5], n = 5
*
* Initial: low = 0, high = 4, hIndex = 0
*
* Iteration 1:
* mid = 0 + (4-0)/2 = 2
* h = 5 - 2 = 3
* citations[2] (which is 3) >= h (which is 3)? Yes.
* Condition met. This is a valid H-index.
* hIndex = 3.
* Search for a potentially larger H-index: high = mid - 1 = 1.
*
* Iteration 2:
* low = 0, high = 1
* mid = 0 + (1-0)/2 = 0
* h = 5 - 0 = 5
* citations[0] (which is 0) >= h (which is 5)? No.
* Condition not met. Need more citations.
* low = mid + 1 = 1.
*
* Iteration 3:
* low = 1, high = 1
* mid = 1 + (1-1)/2 = 1
* h = 5 - 1 = 4
* citations[1] (which is 0) >= h (which is 4)? No.
* Condition not met. Need more citations.
* low = mid + 1 = 2.
*
* Loop ends because low (2) > high (1).
* Return final hIndex = 3.
*
*/
```

---

## Key Insights

The core idea for the optimized solution is recognizing that the H-index condition creates a searchable, ordered space. Once the citations are sorted (`[c_1, c_2, ..., c_n]`), we can make a key observation:

- For any index `i`, the number of papers with at least `citations[i]` citations is `n - i`.
- We are looking for the largest `h` where `h` papers have at least `h` citations. This translates to finding the best index `i` that maximizes `h = n - i` while still satisfying the condition `citations[i] >= h`.
- This check (`citations[i] >= n - i`) can be performed in `O(1)` time, making it perfect for a binary search.

---

## Further Exploration

- **H-Index II (LeetCode):** A follow-up where the input `citations` array is already sorted. This simplifies the problem to just the binary search part.
- **Counting Sort Approach:** If the citation values are within a reasonable range (as they are here), you can use a counting sort-based approach to solve this in `O(N + C)` time, where `C` is the maximum citation value. This can be faster than `O(N log N)` if `C` is not excessively large.

---

## References

- **Original Problem:** [GeeksforGeeks | Find H-Index](https://www.geeksforgeeks.org/problems/find-h-index--165609/1)
- **Related Concept:** [Wikipedia | H-index](https://en.wikipedia.org/wiki/H-index)

---

## Author

**[imnilesh18](https://github.com/imnilesh18)**


---

## Tags

![Array](https://img.shields.io/badge/Array-20232A?style=for-the-badge&logo=todoist&logoColor=white)
![Binary Search](https://img.shields.io/badge/Binary_Search-0078D4?style=for-the-badge&logo=cplusplus&logoColor=white)
![Sorting](https://img.shields.io/badge/Sorting-F7B93E?style=for-the-badge&logo=python&logoColor=white)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-296200?style=for-the-badge&logo=geeksforgeeks&logoColor=white)

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder that this is for educational purposes. Always try to solve problems on your own first!**