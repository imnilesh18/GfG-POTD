# 📚 Allocate Minimum Pages

<div align="center">

⚠️ **Educational Use Only**:
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1).

</div>

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-35.51%25-orange.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

---

## 📄 Problem Statement

Given an array `arr[]` of integers, where each element `arr[i]` represents the number of pages in the i-th book. You also have an integer `k` representing the number of students. The task is to allocate books to each student such that:

1.  Each student receives at least one book.
2.  Each student is assigned a **contiguous** sequence of books.
3.  No book is assigned to more than one student.

The objective is to **minimize the maximum number of pages** assigned to any student. In other words, out of all possible allocations, find the arrangement where the student who receives the most pages still has the smallest possible maximum.

**Note**: If it is not possible to allocate books to all students, return `-1`.

---

## 📖 Examples

### Example 1:

```
Input:
arr[] = [12, 34, 67, 90]
k = 2

Output: 113

Explanation:
Allocation can be done in the following ways:
=> [12] and [34, 67, 90] -> Maximum Pages = 191
=> [12, 34] and [67, 90] -> Maximum Pages = 157
=> [12, 34, 67] and [90] -> Maximum Pages = 113

The third combination has the minimum possible maximum pages, which is 113.
```

<details>
<summary>📖 Example 1 Breakdown</summary>

Let's walk through `arr[] = [12, 34, 67, 90]` and `k = 2`.

- **Goal**: We want to split the array into 2 contiguous parts and find the split where the largest sum of any part is minimized.
- **Possible Splits:**
  1.  `(12)` and `(34, 67, 90)`
      - Sums: `12` and `191`
      - Max sum for this split: `191`
  2.  `(12, 34)` and `(67, 90)`
      - Sums: `46` and `157`
      - Max sum for this split: `157`
  3.  `(12, 34, 67)` and `(90)`
      - Sums: `113` and `90`
      - Max sum for this split: `113`
- **Comparing Maximums**: The maximums we found are `191`, `157`, and `113`.
- **Result**: The minimum of these maximums is **113**.

</details>

### Example 2:

```
Input:
arr[] = [15, 17, 20]
k = 5

Output: -1

Explanation:
Since there are more students (5) than total books (3), it's impossible to allocate at least one book to each student.
```

---

## ⛓️ Constraints

> `1 ≤ arr.size() ≤ 10^6` > `1 ≤ arr[i], k ≤ 10^3`

---

## 💡 Solution Approaches

The problem asks to minimize a maximum value, which is a classic signal for **Binary Search on the Answer**.

### Intuition

The answer (the minimum possible maximum pages for any student) must lie within a specific range.

- The **minimum** possible value (`low`) is the largest number of pages in a single book (since that book must be assigned to someone).
- The **maximum** possible value (`high`) is the sum of all pages in all books (the case where one student gets all books).

We can binary search within this `[low, high]` range. For any `mid` value (a potential answer), we need a way to check if it's possible to allocate books to `k` students such that no student gets more than `mid` pages.

If it's possible with `mid` pages, it means we might be able to do even better, so we try a smaller value by setting `high = mid - 1`. If it's not possible, `mid` is too small, and we need to allow more pages, so we set `low = mid + 1`.

### Optimized Approach: Binary Search

A helper function, `check()`, greedily determines if an allocation is possible for a given page limit. It iterates through the books, summing up pages for the current student. Once the sum exceeds the limit, it assigns the current book to a new student and increments the student count. If the total students required are less than or equal to `k`, the limit is feasible.

#### C++ Solution

```cpp
// Intuition: The problem asks for the minimum of a maximum value, which suggests binary search on the answer. The search space for the answer (maximum pages per student) ranges from the max pages of a single book to the sum of all pages.
// Approach:
// 1. Define a search space `[lo, hi]`, where `lo` is the maximum element in `arr` and `hi` is the sum of all elements.
// 2. Perform binary search on this range. For each `mid`, check if it's a feasible maximum page limit for `k` students using a helper function `check()`.
// 3. The `check()` function greedily allocates books to students. It keeps adding pages to the current student until it exceeds `mid`. Then, it moves to the next student.
// 4. If `check(mid)` returns true (meaning an allocation is possible with `mid` as the limit), it means `mid` could be our answer, so we try for a smaller value: `res = mid`, `hi = mid - 1`.
// 5. If `check(mid)` is false, the limit is too small, so we must increase it: `lo = mid + 1`.
// 6. The final `res` will hold the minimum possible maximum.
// Time Complexity: O(N * log(Sum - Max)), where N is the number of books, Sum is the total pages, and Max is the max pages in a book. The binary search runs in O(log(Sum - Max)) and the `check` function takes O(N).
// Space Complexity: O(1), as we are not using any extra space.
class Solution {
  public:
    // function to check if books can be allocated to
    // all k students without exceeding 'pageLimit'
    bool check(vector<int> &arr, int k, int pageLimit) {

        // starting from the first student
        int cnt = 1;
        int pageSum = 0;
        for(int i = 0; i < arr.size(); i++) {

            // if adding the current book exceeds the page
            // limit, assign the book to the next student
            if(pageSum + arr[i] > pageLimit) {
                cnt++; // increment student count
                pageSum = arr[i]; // start new sum for the new student
            }
            else {
                // otherwise, add pages to the current student
                pageSum += arr[i];
            }
        }

        // if the number of students required is within the limit k, it's a valid allocation
        return (cnt <= k);
    }

    int findPages(vector<int> &arr, int k) {

        // if number of students are more than total books, allocation is not possible
        if(k > arr.size())
            return -1;

        // search space for Binary Search
        // 'lo' is the minimum possible answer (max pages in a single book)
        int lo = *max_element(arr.begin(), arr.end());
        // 'hi' is the maximum possible answer (sum of all pages)
        int hi = accumulate(arr.begin(), arr.end(), 0);
        int res = -1;

        // standard binary search loop
        while(lo <= hi) {
            int mid = lo + (hi - lo)/2;

            // check if 'mid' is a feasible page limit
            if(check(arr, k, mid)){
                res = mid;      // store potential answer
                hi = mid - 1;   // try for a smaller maximum
            }
            else {
                lo = mid + 1;   // 'mid' is too small, increase the limit
            }
        }

        return res;
    }
};
/*
*
* Dry Run
* arr = [12, 34, 67, 90], k = 2
*
* 1. Initial Search Space:
* lo = max(12, 34, 67, 90) = 90
* hi = 12 + 34 + 67 + 90 = 203
*
* 2. Iteration 1:
* mid = 90 + (203 - 90) / 2 = 146
* check(arr, 2, 146):
* - Student 1: 12 + 34 + 67 = 113 (<= 146)
* - (113 + 90 > 146) -> new student
* - Student 2: 90 (<= 146)
* - Total students = 2. It is possible (cnt <= k).
* Result: check is true. res = 146, hi = 145.
*
* 3. Iteration 2:
* lo = 90, hi = 145
* mid = 90 + (145 - 90) / 2 = 117
* check(arr, 2, 117):
* - Student 1: 12 + 34 + 67 = 113 (<= 117)
* - (113 + 90 > 117) -> new student
* - Student 2: 90 (<= 117)
* - Total students = 2. It is possible (cnt <= k).
* Result: check is true. res = 117, hi = 116.
*
* 4. Iteration 3:
* lo = 90, hi = 116
* mid = 90 + (116 - 90) / 2 = 103
* check(arr, 2, 103):
* - Student 1: 12 + 34 = 46 (<= 103)
* - (46 + 67 > 103) -> new student
* - Student 2: 67 (<= 103)
* - (67 + 90 > 103) -> new student
* - Student 3: 90 (<= 103)
* - Total students = 3. Not possible (cnt > k).
* Result: check is false. lo = 104.
*
* 5. Iteration 4:
* lo = 104, hi = 116
* mid = 104 + (116 - 104) / 2 = 110
* check(arr, 2, 110):
* - Similar to mid=103, this will also require 3 students.
* Result: check is false. lo = 111.
*
* 6. Iteration 5:
* lo = 111, hi = 116
* mid = 111 + (116 - 111) / 2 = 113
* check(arr, 2, 113):
* - Student 1: 12 + 34 + 67 = 113 (<= 113)
* - (113 + 90 > 113) -> new student
* - Student 2: 90 (<= 113)
* - Total students = 2. It is possible.
* Result: check is true. res = 113, hi = 112.
*
* 7. Iteration 6:
* lo = 111, hi = 112
* mid = 111 + (112 - 111) / 2 = 111
* check(arr, 2, 111): Not possible (requires 3 students).
* Result: check is false. lo = 112.
*
* 8. Iteration 7:
* lo = 112, hi = 112
* mid = 112. check(arr, 2, 112): Not possible.
* Result: check is false. lo = 113.
*
* Now lo (113) > hi (112), loop terminates.
* Final Answer: res = 113.
*
*/
```

#### Java Solution

```java
// Intuition: The problem requires finding the minimum possible value for the maximum number of pages assigned to a student. This structure suggests a binary search approach on the potential answers for this minimum-maximum value.
// Approach:
// 1. Establish a search range for the answer. The lower bound `lo` is the maximum pages in any single book, and the upper bound `hi` is the sum of all pages.
// 2. Apply binary search. For each `mid` value, use a helper function `check()` to verify if it's possible to distribute books among `k` students without any student exceeding the `mid` page limit.
// 3. The `check()` function greedily assigns books to the current student until the page count surpasses `mid`, at which point it moves to the next student.
// 4. If `check(mid)` is true, it means `mid` is a valid potential answer. We then try to find an even smaller value by setting `res = mid` and `hi = mid - 1`.
// 5. If `check(mid)` is false, `mid` is too restrictive, and we must allow more pages by setting `lo = mid + 1`.
// 6. The loop continues until `lo` crosses `hi`, and `res` will hold the minimal maximum value found.
// Time Complexity: O(N * log(Sum - Max)), where N is the number of books. The binary search takes O(log(Sum - Max)) iterations, and each call to `check` is O(N).
// Space Complexity: O(1), as no auxiliary data structures are used.
class Solution {
    // function to check if books can be allocated to
    // all k students without exceeding 'pageLimit'
    static boolean check(int[] arr, int k, int pageLimit) {

        // starting from the first student
        int cnt = 1;
        int pageSum = 0;
        for(int i = 0; i < arr.length; i++) {

            // if adding the current book exceeds the page
            // limit, assign the book to the next student
            if(pageSum + arr[i] > pageLimit) {
                cnt++; // move to the next student
                pageSum = arr[i]; // assign current book to this new student
            }
            else {
                // accumulate pages for the current student
                pageSum += arr[i];
            }
        }

        // if the number of students needed is not more than k, this pageLimit is possible
        return (cnt <= k);
    }

    static int findPages(int[] arr, int k) {

        // if number of students are more than total books
        // then allocation is not possible
        if(k > arr.length)
            return -1;

        // search space for Binary Search
        // 'lo' is the minimum possible answer (a single book with max pages)
        int lo = Arrays.stream(arr).max().getAsInt();
        // 'hi' is the maximum possible answer (one student takes all books)
        int hi = Arrays.stream(arr).sum();
        int res = -1;

        // binary search loop
        while(lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            // if 'mid' is a valid maximum limit
            if(check(arr, k, mid)){
                res = mid;      // this is a potential answer
                hi = mid - 1;   // try to find an even smaller limit
            }
            else {
                lo = mid + 1;   // limit is too small, need to increase it
            }
        }

        return res;
    }
}

/*
*
* Dry Run
* arr = [12, 34, 67, 90], k = 2
*
* 1. Initial Search Space:
* lo = 90 (max element)
* hi = 203 (sum of elements)
*
* 2. Iteration 1:
* mid = 90 + (203 - 90) / 2 = 146
* check(146):
* - Student 1: 12 + 34 + 67 = 113. Next book (90) makes sum > 146.
* - Student 2: 90.
* - Count = 2. check(146) is true.
* Result: res = 146, hi = 145.
*
* 3. Iteration 2:
* mid = 90 + (145 - 90) / 2 = 117
* check(117):
* - Student 1: 12 + 34 + 67 = 113. Next book (90) makes sum > 117.
* - Student 2: 90.
* - Count = 2. check(117) is true.
* Result: res = 117, hi = 116.
*
* 4. Iteration 3:
* mid = 90 + (116 - 90) / 2 = 103
* check(103):
* - Student 1: 12 + 34 = 46. Next book (67) makes sum > 103.
* - Student 2: 67. Next book (90) makes sum > 103.
* - Student 3: 90.
* - Count = 3. check(103) is false.
* Result: lo = 104.
*
* ... (The search continues, narrowing down the range) ...
*
* 5. Final relevant iteration:
* lo = 113, hi = 113
* mid = 113
* check(113):
* - Student 1: 12 + 34 + 67 = 113. Next book (90) makes sum > 113.
* - Student 2: 90.
* - Count = 2. check(113) is true.
* Result: res = 113, hi = 112.
*
* Loop terminates as lo (113) > hi (112).
* Return res = 113.
*
*/
```

---

## 🚀 Key Insights

- **Monotonicity**: The core principle that enables binary search here is the monotonic nature of the `check(pageLimit)` function. If we can successfully allocate books with a maximum limit of `X` pages, we can **definitely** also do it with any limit `Y > X`. Conversely, if we cannot make an allocation with limit `X`, we **definitely** cannot do it with any limit `Z < X`. This property ensures that our binary search correctly narrows down the search space to find the optimal minimum-maximum value.
- **Greedy Check**: The `check` function works because the books must be allocated contiguously. For a given page limit, the most optimal strategy to minimize the number of students is to be greedy: assign as many books as possible to the current student before moving to the next one.

---

## 🔭 Further Exploration

This problem is a classic example of "Binary Search on the Answer". Here are some related problems that use the same powerful technique:

- [Aggressive Cows](https://www.geeksforgeeks.org/problems/aggressive-cows/0)
- [Split Array Largest Sum](https://www.geeksforgeeks.org/problems/split-array-largest-sum--141634/1)
- [Koko Eating Bananas](https://www.geeksforgeeks.org/problems/koko-eating-bananas/1)
- [Smallest Divisor](https://www.geeksforgeeks.org/problems/smallest-divisor/1)

---

## 🔗 References

- **Original Problem**: [GeeksforGeeks | Allocate Minimum Number of Pages](https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1)
- **Binary Search on Answer**: [GeeksforGeeks Article](https://www.geeksforgeeks.org/binary-search-on-answer-the-ultimate-guide/)

---

## ✍️ Author

- [imnilesh18](https://github.com/imnilesh18)

---

## #️⃣ Tags

![Binary Search](https://img.shields.io/badge/Binary_Search-007ACC?style=for-the-badge&logo=cplusplus&logoColor=white)
![Arrays](https://img.shields.io/badge/Arrays-5C6BC0?style=for-the-badge)
![Greedy](https://img.shields.io/badge/Greedy-4CAF50?style=for-the-badge)
![Algorithms](https://img.shields.io/badge/Algorithms-FF9800?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**A gentle reminder**: The solutions and explanations in this repository are for educational purposes. They are meant to help you understand the problem-solving process and are not intended for direct submission to online judges. Always try to solve problems on your own first!
