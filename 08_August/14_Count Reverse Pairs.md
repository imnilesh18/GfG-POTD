# 🤯 Count Reverse Pairs

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-green?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/count-reverse-pairs/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-50.0%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/count-reverse-pairs/1).

---

## 🎯 Problem Statement

You are given an array `arr[]` of positive integers. Your task is to find the count of **reverse pairs**.

A pair of indices `(i, j)` is said to be a **reverse pair** if both the following conditions are met:

1.  `0 ≤ i < j < arr.size()`
2.  `arr[i] > 2 * arr[j]`

---

## 📖 Examples

### Example 1:

**Input:**

```
arr[] = [3, 2, 4, 5, 1, 20]
```

**Output:**

```
3
```

<details>
<summary>📖 Example Breakdown</summary>

The reverse pairs are:

- **(0, 4):** `arr[0] = 3`, `arr[4] = 1`. The condition `3 > 2 * 1` is **true**.
- **(2, 4):** `arr[2] = 4`, `arr[4] = 1`. The condition `4 > 2 * 1` is **true**.
- **(3, 4):** `arr[3] = 5`, `arr[4] = 1`. The condition `5 > 2 * 1` is **true**.

Total count = **3**.

</details>

### Example 2:

**Input:**

```
arr[] = [5, 4, 3, 2, 2]
```

**Output:**

```
2
```

**Explanation:**
The reverse pairs are:

- **(0, 3):** `arr[0] = 5`, `arr[3] = 2`. The condition `5 > 2 * 2` (i.e., 5 > 4) is **true**.
- **(0, 4):** `arr[0] = 5`, `arr[4] = 2`. The condition `5 > 2 * 2` (i.e., 5 > 4) is **true**.

Total count = **2**.

---

## ⚙️ Constraints

- `1 ≤ arr.size() ≤ 5*10^4`
- `1 ≤ arr[i] ≤ 10^9`

---

## 💡 Solution Approaches

### Optimized Approach: Merge Sort

The problem can be efficiently solved using a modification of the Merge Sort algorithm. A brute-force check of all pairs `(i, j)` would be `O(N^2)`, which is too slow for the given constraints. The Divide and Conquer strategy is ideal here.

The core idea is that while merging two sorted halves of the array, we can efficiently count the reverse pairs that span across the two halves.

#### C++ Solution

```cpp
// Intuition: The problem requires counting pairs (i, j) with i < j and arr[i] > 2 * arr[j].
// A brute-force O(N^2) approach is too slow. This structure is similar to counting inversions,
// suggesting a Divide and Conquer approach like Merge Sort, which works in O(N log N).
// The key is to count the "cross" reverse pairs while merging two sorted subarrays.

// Approach:
// 1. Use a recursive Merge Sort algorithm to divide the array.
// 2. In the merging step, for two sorted halves (left and right), count the reverse pairs.
// 3. For each element `a` in the left half, find the number of elements `b` in the right half
//    such that `a > 2 * b`. Since both halves are sorted, this can be done efficiently in linear time.
// 4. Sum up the counts from the left subarray, the right subarray, and the cross pairs found during merging.
// 5. Finally, perform the standard merge operation to sort the array segment for subsequent recursive calls.

// Time Complexity: O(N log N), where N is the size of the array. The merge sort algorithm inherently
// takes O(N log N), and the counting process inside the merge function is O(N).
// Space Complexity: O(N) due to the temporary vector used for merging the subarrays.

class Solution {
  public:
    // Function to count reverse pairs and merge the two sorted halves
    int merging(vector<int>& arr, int low, int mid, int high) {
        int count = 0;
        int j = mid + 1; // Pointer for the right half

        // Count pairs where arr[i] > 2 * arr[j]
        // For each element in the left half...
        for (int i = low; i <= mid; i++) {
            // ...find how many elements in the right half satisfy the condition
            while (j <= high && arr[i] > 2LL * arr[j]) {
                j++;
            }
            // All elements from (mid+1) to (j-1) in the right half form a pair with arr[i]
            count += (j - (mid + 1));
        }

        // Standard merge step to sort the array
        vector<int> temp;
        int left = low;      // Pointer for the left half
        int right = mid + 1; // Pointer for the right half

        // Merge the two halves into a temporary vector
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left++]);
            } else {
                temp.push_back(arr[right++]);
            }
        }

        // Copy any remaining elements from the left half
        while (left <= mid) {
            temp.push_back(arr[left++]);
        }

        // Copy any remaining elements from the right half
        while (right <= high) {
            temp.push_back(arr[right++]);
        }

        // Copy the sorted elements back to the original array
        for (int i = low; i <= high; i++) {
            arr[i] = temp[i - low];
        }

        return count; // Return the count of cross-pairs
    }

    // Recursive function to perform merge sort and count pairs
    int mergeSort(vector<int>& arr, int low, int high) {
        // Base case: if the array has 0 or 1 element, no pairs can be formed
        if (low >= high) {
            return 0;
        }

        int mid = low + (high - low) / 2; // Calculate the middle index
        int count = 0;

        // Recursively count pairs in the left and right halves
        count += mergeSort(arr, low, mid);
        count += mergeSort(arr, mid + 1, high);

        // Count pairs that span across the two halves
        count += merging(arr, low, mid, high);

        return count;
    }

    // Main function to initiate the counting of reverse pairs
    int countRevPairs(vector<int>& arr) {
        if (arr.empty()) return 0;
        return mergeSort(arr, 0, arr.size() - 1);
    }
};

/*
*
* Dry Run
*
* Input: arr[] = [3, 2, 4, 5, 1, 20]
*
* 1. mergeSort([3, 2, 4, 5, 1, 20], 0, 5)
* - mid = 2.
* - Calls mergeSort([3, 2, 4], 0, 2)
* - mid = 1.
* - Calls mergeSort([3, 2], 0, 1) -> ... -> merging([2, 3], ...) returns 0 pairs.
* - Calls mergeSort([4], 2, 2) -> returns 0.
* - Calls merging([2, 3], [4]). `j` starts at index 2.
* - i=0 (val=2): 2 > 2*4 is false.
* - i=1 (val=3): 3 > 2*4 is false.
* - Cross pairs = 0.
* - Array becomes [2, 3, 4]. Left half count = 0.
* - Calls mergeSort([5, 1, 20], 3, 5)
* - ... similar process ...
* - Array becomes [1, 5, 20]. Right half count = 0.
*
* 2. merging([2, 3, 4], [1, 5, 20])
* - low=0, mid=2, high=5
* - Left half: [2, 3, 4], Right half: [1, 5, 20]
* - Count pairs:
* - i = 0 (val = 2): Check against right half. `j` is at index 3 (val=1). 2 > 2*1 is false.
* - i = 1 (val = 3): Check against right half. `j` is at index 3 (val=1). 3 > 2*1 is true. Move `j` to 4. Pairs found = 1 ( (3,1) ).
* - i = 2 (val = 4): Check against right half. `j` is at index 4 (val=5). 4 > 2*1 is true. Move `j` to 4. Pairs found = 1 + 1 = 2 ( (4,1) ).
* - i = 2 (val = 5): Check against right half. `j` is at index 4 (val=5). 5 > 2*1 is true. Move `j` to 4. Pairs found = 2 + 1 = 3 ( (5,1) ).
*
* - This seems slightly off. Let's re-trace the count logic.
* - Let left=[3,2,4], right=[5,1,20]. After sorting: left=[2,3,4], right=[1,5,20].
* - Now, merge and count:
* - i = 0 (val = 2): Check vs [1, 5, 20]. j=3. 2 > 2*arr[3](1) is false. count += 0.
* - i = 1 (val = 3): Check vs [1, 5, 20]. j=3. 3 > 2*arr[3](1) is true. j++. now j=4. count += (4-(2+1)) = 1. The pair is (3,1).
* - i = 2 (val = 4): Check vs [1, 5, 20]. j=4. 4 > 2*arr[3](1) is true. Wait, `j` doesn't reset.
*
* Correct Dry Run of counting in `merging`:
* Left sorted: [2, 3, 4], Right sorted: [1, 5, 20]
* `j` starts at `mid + 1` = 3. `count = 0`.
*
* i = 0 (val=2): `while(j<=5 && 2 > 2LL * arr[j])`.
* - j=3 (val=1): 2 > 2 is false. Loop doesn't run. `count += (3 - (2+1)) = 0`.
*
* i = 1 (val=3): `while(j<=5 && 3 > 2LL * arr[j])`.
* - j=3 (val=1): 3 > 2 is true. j becomes 4.
* - j=4 (val=5): 3 > 10 is false. Loop stops.
* - `count += (4 - (2+1)) = 1`.
*
* i = 2 (val=4): `while(j<=5 && 4 > 2LL * arr[j])`. `j` is already 4.
* - j=4 (val=5): 4 > 10 is false. Loop doesn't run.
* - `count += (4 - (2+1)) = 1`. This seems wrong.
*
* Let's trace the original array [3,2,4] and [5,1,20].
* Original pairs found in subproblems: (3,2) -> no, (5,1) -> yes. Let's assume subproblems return 0.
* Now `merging([3,2,4,5,1,20], 0, 2, 5)`. Left sorted: [2,3,4]. Right sorted: [1,5,20].
* Let's trace the example pairs: (3,1), (4,1), (5,1).
* The algorithm must be finding these pairs across the mid-point. Let's see how.
* The original array `arr` is modified in-place.
* The count for `(0,4)` where `arr[0]=3, arr[4]=1` is what we need to find.
* My trace was flawed. The pairs are from the *original indices*.
* Let's take `arr = [3, 2, 4, 5, 1, 20]`
* `mergeSort` on `[3, 2, 4]` and `[5, 1, 20]`
* Left becomes `[2, 3, 4]` (0 pairs). Right becomes `[1, 5, 20]` (1 pair: (5,1)).
* Now `merging`: left part is `[2,3,4]`, right is `[1,5,20]`. `j=3`.
* i=0 (val=2): vs `[1,5,20]`. 2 > 2*1 is false.
* i=1 (val=3): vs `[1,5,20]`. 3 > 2*1 is true. `j` becomes 4. `count += 1`.
* i=2 (val=4): vs `[1,5,20]`. 4 > 2*1 is true. `j` is already 4.
* This logic seems to miss pairs. Let's re-read the code. Ah, the `for` loop `i` is for the left part, `j` for the right.
*
* Corrected trace of `merging` with `left=[2,3,4]`, `right=[1,5,20]`
* `j = 3`
* `i = 0` (val=2): `while(j<=5 && 2 > 2*arr[j])`. `j=3`(val=1), `2 > 2` is false. `count += (3 - 3) = 0`.
* `i = 1` (val=3): `while(j<=5 && 3 > 2*arr[j])`. `j=3`(val=1), `3 > 2` is true. `j` becomes 4. `j=4`(val=5), `3 > 10` is false. `count += (4 - 3) = 1`. (This pair corresponds to original (3,1))
* `i = 2` (val=4): `while(j<=5 && 4 > 2*arr[j])`. `j` is now 4. `j=4`(val=5), `4 > 10` is false. `count += (4 - 3) = 1`. (This pair corresponds to original (4,1)).
* The total count is 0(left) + 1(right for 5,1) + 1+1 (cross) = 3. Wait, there is no (5,1) in the right half. 5 > 2*1 is true. Yes, but `i<j`.
* Let's restart the dry run simply.
* Initial Call: `countRevPairs([3, 2, 4, 5, 1, 20])`
* `mergeSort(arr, 0, 5)` -> `mid=2`
* `mergeSort(arr, 0, 2)` for `[3, 2, 4]` -> sorts to `[2, 3, 4]`, returns 0 pairs.
* `mergeSort(arr, 3, 5)` for `[5, 1, 20]` -> sorts to `[1, 5, 20]`, returns 1 pair (5,1).
* `merging(arr, 0, 2, 5)`. Current `arr`: `[2, 3, 4, 1, 5, 20]`.
* Count step:
* `j=3`.
* `i=0 (val=2)`: vs `[1, 5, 20]`. `2 > 2*1` is false. `count += 0`.
* `i=1 (val=3)`: vs `[1, 5, 20]`. `3 > 2*1` is true. `j` becomes 4. `count += (4-3) = 1`. This finds a pair.
* `i=2 (val=4)`: vs `[1, 5, 20]`. `j` is 4. `4 > 2*1` is true. The inner loop was on `arr[j]` which is 1. My trace was wrong.
* Let's fix the trace:
* `merging([2, 3, 4, 1, 5, 20], 0, 2, 5)`
* `j = 3`.
* `i = 0` (arr[0]=2): `while (j <= 5 && 2 > 2LL*arr[j])`. `j=3`(arr[3]=1), `2>2` is false. count += (3-3)=0.
* `i = 1` (arr[1]=3): `while (j <= 5 && 3 > 2LL*arr[j])`. `j=3`(arr[3]=1), `3>2` is true. `j` becomes 4. `j=4`(arr[4]=5), `3>10` is false. `count += (4-3)=1`. (Pair: (3,1))
* `i = 2` (arr[2]=4): `while (j <= 5 && 4 > 2LL*arr[j])`. `j` is now 4. `j=4`(arr[4]=5), `4>10` is false. `count += (4-3)=1`. (Pair: (4,1))
* Total from merging: 1 + 1 = 2.
* Total count: 0(left) + 1(right) + 2(cross) = 3. This is correct.
* Final Array after merge: `[1, 2, 3, 4, 5, 20]`.
* Output: 3. Correct.
*/
```

#### Java Solution

```java
// Intuition: A brute-force O(N^2) check for all pairs (i, j) is inefficient. The problem's
// structure, arr[i] > 2 * arr[j], is a variation of the classic "Count Inversions" problem.
// This hints that a Divide and Conquer strategy, specifically Merge Sort, is the optimal approach.

// Approach:
// 1. We'll use a recursive Merge Sort to break the array down into single elements.
// 2. The core logic resides in the `merging` function, which is called after the recursive calls return.
// 3. Before merging two sorted halves (left and right), we count the reverse pairs that span across them.
// 4. For each element `arr[i]` in the sorted left half, we find how many elements `arr[j]` in the
//    sorted right half satisfy `arr[i] > 2 * arr[j]`.
// 5. This counting is done efficiently (linear time) using two pointers because both halves are already sorted.
// 6. After counting, we perform a standard merge operation to sort the combined segment.
// 7. The total count is the sum of pairs from the left half, right half, and the cross-pairs.

// Time Complexity: O(N log N). The algorithm is dominated by the Merge Sort structure.
// Each level of recursion involves a linear O(N) scan for counting and merging.
// Space Complexity: O(N) for the temporary `ArrayList` used during the merge step.

class Solution {
    // Function to count reverse pairs and merge two sorted subarrays
    static int merging(int[] arr, int low, int mid, int high) {
        int count = 0;
        int j = mid + 1; // Pointer for the right subarray

        // Count pairs satisfying the condition arr[i] > 2 * arr[j]
        for (int i = low; i <= mid; i++) {
            // Move pointer j while the condition holds
            while (j <= high && arr[i] > 2L * arr[j]) {
                j++;
            }
            // All elements from (mid+1) to (j-1) in the right half form pairs with arr[i]
            count += (j - (mid + 1));
        }

        // Standard merge sort procedure to sort the array segment
        List<Integer> temp = new ArrayList<>();
        int left = low;      // Pointer for the left subarray
        int right = mid + 1; // Pointer for the right subarray

        // Merge the two halves into the temporary list
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.add(arr[left++]);
            } else {
                temp.add(arr[right++]);
            }
        }

        // Add any remaining elements from the left half
        while (left <= mid) {
            temp.add(arr[left++]);
        }

        // Add any remaining elements from the right half
        while (right <= high) {
            temp.add(arr[right++]);
        }

        // Copy the sorted elements from temp back to the original array
        for (int i = low; i <= high; i++) {
            arr[i] = temp.get(i - low);
        }

        return count; // Return the count of pairs found in this merge step
    }

    // Function to perform merge sort recursively
    static int mergeSort(int[] arr, int low, int high) {
        // Base case: if the array has one or zero elements, no pairs exist
        if (low >= high) {
            return 0;
        }

        int mid = low + (high - low) / 2; // Find the middle point
        int count = 0;

        // Recursively count pairs in the left half
        count += mergeSort(arr, low, mid);
        // Recursively count pairs in the right half
        count += mergeSort(arr, mid + 1, high);
        // Count pairs that span across the two halves
        count += merging(arr, low, mid, high);

        return count;
    }

    // Main function to start the process
    static int countRevPairs(int[] arr) {
        if (arr == null || arr.length == 0) return 0;
        return mergeSort(arr, 0, arr.length - 1);
    }
}
/*
*
* Dry Run
*
* Input: arr = [5, 4, 3, 2, 2]
*
* 1. countRevPairs calls mergeSort(arr, 0, 4)
* 2. mergeSort(arr, 0, 4) -> mid = 2.
* - Calls mergeSort(arr, 0, 2) for [5, 4, 3].
* - Calls mergeSort for [5, 4] -> sorts to [4, 5], 0 pairs.
* - Calls mergeSort for [3] -> returns 0.
* - Calls merging([4, 5], [3]) -> sorts to [3, 4, 5].
* - Count cross-pairs: i=0(val=4)>2*3 is false. i=1(val=5)>2*3 is false. Count=0.
* - Left half returns 0 pairs. Array is now [3, 4, 5, 2, 2].
* - Calls mergeSort(arr, 3, 4) for [2, 2].
* - Returns 0 pairs. Array remains [3, 4, 5, 2, 2].
* - Calls merging(arr, 0, 2, 4).
* - Left sorted part is [3, 4, 5]. Right sorted part is [2, 2].
* - Count cross-pairs: j starts at 3.
* - i = 0 (val = 3): 3 > 2*arr[3](2) is false. count += 0.
* - i = 1 (val = 4): 4 > 2*arr[3](2) is false. count += 0.
* - i = 2 (val = 5): 5 > 2*arr[3](2) is true. j++.
* 5 > 2*arr[4](2) is true. j++. j is now 5.
* count += (5 - (2+1)) = 2.
* - Merging returns 2.
* 3. Total count = 0 (left) + 0 (right) + 2 (cross) = 2.
*
* Output: 2. This matches the example.
*
*/
```

---

## 🧠 Key Insights

The brilliance of the Merge Sort approach lies in its "Divide and Conquer" nature.

- **Sorted Subarrays:** By ensuring that the left (`low` to `mid`) and right (`mid+1` to `high`) subarrays are sorted before we count the cross-pairs, we introduce a powerful property.
- **Linear Time Counting:** For an element `arr[i]` in the left subarray, if we find that `arr[i] > 2 * arr[j]`, then because the right subarray is sorted, we know that `arr[i]` will also be greater than `2 * arr[k]` for all `k < j`. This allows us to use a single pass (or two pointers) to count these pairs in `O(N)` time for each merge step, instead of a nested `O(N^2)` loop.
- **Comprehensive Count:** The total number of reverse pairs is the sum of pairs entirely within the left subarray, pairs entirely within the right subarray, and pairs that cross the midpoint. The recursion naturally handles the first two, and our custom `merging` function handles the third.

---

## 🚀 Further Exploration

If you found this problem interesting, you should also try these related problems on GeeksforGeeks:

- [**Count Inversions**](https://www.geeksforgeeks.org/problems/inversion-of-array/0): The classic problem that introduces this Merge Sort-based counting technique.
- [**Maximum sum of elements not part of LIS**](https://www.geeksforgeeks.org/problems/maximum-sum-of-elements-not-part-of-lis/1): Another DP problem that requires careful subsequence analysis.

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks | Count Reverse Pairs](https://www.geeksforgeeks.org/problems/count-reverse-pairs/1)
- **Merge Sort Algorithm:** A fundamental sorting algorithm that is the basis for this solution.

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<p>
  <a href="#">
    <img src="https://img.shields.io/badge/Array-2ea44f?style=for-the-badge" alt="Array">
  </a>
  <a href="#">
    <img src="https://img.shields.io/badge/Divide%20and%20Conquer-a2468f?style=for-the-badge" alt="Divide and Conquer">
  </a>
  <a href="#">
    <img src="https://img.shields.io/badge/Merge%20Sort-563d7c?style=for-the-badge" alt="Merge Sort">
  </a>
  <a href="https://www.geeksforgeeks.org/">
    <img src="https://img.shields.io/badge/GeeksforGeeks-0f9d58?style=for-the-badge" alt="GeeksforGeeks">
  </a>
  <a href="#">
    <img src="https://img.shields.io/badge/Hard-ff4747?style=for-the-badge" alt="Hard">
  </a>
</p>

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](https://opensource.org/licenses/MIT) file for details.

This repository is for educational purposes only. The problem statement and code solutions are inspired by and based on the GeeksforGeeks platform.
