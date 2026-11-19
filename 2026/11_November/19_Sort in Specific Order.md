# 🟧 Sort in Specific Order

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/sort-in-specific-order2422/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/sort-in-specific-order2422/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-52.55%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/sort-in-specific-order2422/1)
[![Points](https://img.shields.io/badge/Points-4-success?style=for-the-badge)](https://www.geeksforgeeks.org/problems/sort-in-specific-order2422/1)
[![Submissions](https://img.shields.io/badge/Submissions-61K%2B-informational?style=for-the-badge)](https://www.geeksforgeeks.org/problems/sort-in-specific-order2422/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

> **⚠️ Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📋 Problem Statement

Given an array `arr[]` of non-negative integers, sort the array in-place such that :
1. The **first part** of the array contains all **odd numbers** sorted in **descending order** .
2. The **remaining portion** of the array contains all **even numbers** sorted in **ascending order** .

> **Note:** Ensure your solution meets the expected constraints (`1 ≤ arr.size() ≤ 10^5` and `0 ≤ arr[i] ≤ 10^9`) and runs within `O(n log n)` time and `O(1)` auxiliary space .

---

## 🧪 Examples

### Example 1
```text
Input:  arr[] = [1, 2, 3, 5, 4, 7, 10]
Output: [7, 5, 3, 1, 2, 4, 10]
Explanation: 7, 5, 3, 1 are odd numbers in descending order and 2, 4, 10 are even numbers in ascending order.
```

### Example 2
```text
Input:  arr[] = [0, 4, 5, 3, 7, 2, 1]
Output: [7, 5, 3, 1, 0, 2, 4]
Explanation: 7, 5, 3, 1 are odd numbers in descending order and 0, 2, 4 are even numbers in ascending order.
```

<details>
<summary><b>📖 Example Breakdown (Walkthrough of Example 1)</b></summary>

Given `arr[] = [1, 2, 3, 5, 4, 7, 10]` :

1. **Identify Parity of Elements:**
   - **Odd numbers (`num & 1 == 1`):** `1, 3, 5, 7` 
   - **Even numbers (`num & 1 == 0`):** `2, 4, 10` 

2. **Apply Custom Ordering Rules:**
   - **Odd Partition (Descending):** `[1, 3, 5, 7]` $\rightarrow$ `[7, 5, 3, 1]` 
   - **Even Partition (Ascending):** `[2, 4, 10]` $\rightarrow$ `[2, 4, 10]` 

3. **Final Combined Array:**
   - Place the sorted odd partition first, followed by the sorted even partition:
   - `[7, 5, 3, 1, 2, 4, 10]` 

</details>

---

## 🔒 Constraints & Expected Complexities

> **Constraints:** 
> - $1 \le \text{arr.size()} \le 10^5$ 
> - $0 \le \text{arr}[i] \le 10^9$ 
>
> **Expected Complexities:** 
> - **Time Complexity:** $\mathcal{O}(n \log n)$ 
> - **Auxiliary Space:** $\mathcal{O}(1)$ 

---

## 💡 Solution Approaches

### 1️⃣ Approach 1: Separate, Sort, and Merge (Brute Force / Extra Space)

#### Intuition
The most straightforward way to solve this problem is to split the input array into two separate lists: one storing all odd numbers and the other storing all even numbers. Once separated, we can independently sort the odd list in descending order and the even list in ascending order, then overwrite the original array with both sorted lists.

#### C++ Implementation
```cpp
// Intuition: Separate odd and even numbers into two auxiliary vectors, sort each according to its required order, and merge them back.
// Approach: Traverse arr to collect odds and evens separately, sort odds with greater<int>(), sort evens in ascending order, and overwrite arr.
// Time Complexity: O(n log n), where n is the number of elements in arr, dominated by sorting the two partitions.
// Space Complexity: O(n) auxiliary space to store the odd and even elements in separate vectors.

class Solution {
  public:
    void sortIt(vector<int>& arr) {
        vector<int> odds, evens;

        // Partition elements into odd and even vectors
        for (int num : arr) {
            if (num & 1) {
                odds.push_back(num);
            } else {
                evens.push_back(num);
            }
        }

        // Sort odd numbers in descending order
        sort(odds.begin(), odds.end(), greater<int>());

        // Sort even numbers in ascending order
        sort(evens.begin(), evens.end());

        // Write sorted odds followed by sorted evens back into arr
        int idx = 0;
        for (int num : odds) {
            arr[idx++] = num;
        }
        for (int num : evens) {
            arr[idx++] = num;
        }
    }
};

/*
*
* Dry Run
*
* Input: arr = [1, 2, 3, 5, 4, 7, 10]
*
* Step 1: Partition into odds and evens
* odds = [1, 3, 5, 7]
* evens = [2, 4, 10]
*
* Step 2: Sort each partition independently
* odds sorted descending = [7, 5, 3, 1]
* evens sorted ascending = [2, 4, 10]
*
* Step 3: Overwrite original array
* arr becomes [7, 5, 3, 1, 2, 4, 10]
*
* Output: [7, 5, 3, 1, 2, 4, 10]
*
*/
```

---

### 2️⃣ Approach 2: In-Place Sorting with Custom Comparator (Optimal)

#### Intuition
Instead of allocating extra memory to separate odd and even elements, we can define a single **custom comparator** inside `std::sort` that encodes all three ordering rules simultaneously :
1. Any odd number strictly precedes any even number .
2. Between two odd numbers, the larger number comes first (`a > b`) .
3. Between two even numbers, the smaller number comes first (`a < b`) .

This allows `std::sort` to partition and sort the array completely **in-place** in $\mathcal{O}(1)$ auxiliary space .

#### C++ Implementation
```cpp
// Intuition: Partition odd and even numbers in-place using a custom comparator so odds appear first in descending order and evens follow in ascending order.
// Approach: Pass a lambda comparator to std::sort that checks parity via bitwise AND (& 1), places odd elements before even elements, sorts odds descending (a > b), and sorts evens ascending (a < b).
// Time Complexity: O(n log n), where n is the size of the array, due to std::sort comparisons.
// Space Complexity: O(1) auxiliary space (in-place sorting without extra data structures).

class Solution {
  public:
    void sortIt(vector<int>& arr) {
        // Sort in-place using a custom lambda comparator
        sort(arr.begin(), arr.end(), [](int a, int b) {
            bool isOddA = (a & 1); // Check if 'a' is odd using LSB
            bool isOddB = (b & 1); // Check if 'b' is odd using LSB
            
            // Odd numbers come before even numbers (true if 'a' is odd and 'b' is even)
            if (isOddA != isOddB) {
                return isOddA;
            }
            
            // Both odd: sort in descending order
            if (isOddA) {
                return a > b;
            }
            
            // Both even: sort in ascending order
            return a < b;
        });
    }
};

/*
*
* Dry Run
*
* Input: arr = [1, 2, 3, 5, 4, 7, 10]
*
* Step 1: Check element parities via (x & 1)
* Odd elements (x & 1 == 1): 1, 3, 5, 7
* Even elements (x & 1 == 0): 2, 4, 10
*
* Step 2: Apply custom comparator rules during std::sort
* When comparing odd and even (isOddA != isOddB): returns isOddA, placing all odds before evens
* When comparing two odds (isOddA == true): returns a > b, ordering odds as [7, 5, 3, 1]
* When comparing two evens (isOddA == false): returns a < b, ordering evens as [2, 4, 10]
*
* Step 3: Final in-place state of arr
* arr = [7, 5, 3, 1, 2, 4, 10]
*
* Output: [7, 5, 3, 1, 2, 4, 10]
*
*/
```

---

### 📊 Complexity Comparison

| Approach | Time Complexity | Auxiliary Space | In-Place? | Notes |
| :--- | :---: | :---: | :---: | :--- |
| **Separate, Sort & Merge** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(n)$ | ❌ No | Easy to implement, but requires extra vectors for partitioning |
| **Custom Comparator (`std::sort`)** | $\mathcal{O}(n \log n)$ | $\mathcal{O}(1)$ | ✅ Yes | Optimal solution; satisfies strict weak ordering and $\mathcal{O}(1)$ space  |

---

## 🔑 Key Insights

- **Bitwise Parity Check (`a & 1`):** Checking the least significant bit with `a & 1` is fast and avoids negative remainder edge cases (`-1`) if the problem were ever extended to negative integers .
- **Strict Weak Ordering:** The custom comparator defines a valid strict weak ordering—every element falls into one of two disjoint partitions (odd vs. even), and each partition has a strict total order (`>` for odds, `<` for evens) .
- **Alternative Two-Pointer + Sort Trick:** Another $\mathcal{O}(1)$ space technique is to partition odds to the left and evens to the right using two pointers (similar to Lomuto/Hoare partition), then sort `[0, oddCount)` in descending order and `[oddCount, n)` in ascending order. The custom comparator achieves the same result in a single `std::sort` call .

---

## 🚀 Further Exploration

- **Related GeeksforGeeks Problems:**
  - [Segregate Even and Odd numbers](https://www.geeksforgeeks.org/problems/segregate-even-and-odd-numbers4629/1)
  - [Sort an array according to the other (Relative Sorting)](https://www.geeksforgeeks.org/problems/relative-sorting4323/1)
  - [Sorting Elements of an Array by Frequency](https://www.geeksforgeeks.org/problems/sorting-elements-of-an-array-by-frequency-1587115621/1)
  - [Wave Array](https://www.geeksforgeeks.org/problems/wave-array-1587115621/1)
- **Follow-Up Questions:**
  - How would you preserve the **relative order** of odd and even numbers without sorting their values (stable partitioning in $\mathcal{O}(n)$ time)?
  - Does the custom comparator still work if `arr[]` contains **negative integers** (e.g., `-3, -2, -5`)? *(Yes, because `a & 1` evaluates to `1` for negative odd numbers in two's complement representation!)*

---

## 📚 References

- **GeeksforGeeks Problem:** [Sort in Specific Order](https://www.geeksforgeeks.org/problems/sort-in-specific-order2422/1) 
- **C++ Reference:** [`std::sort` & Custom Comparators](https://en.cppreference.com/w/cpp/algorithm/sort)

---

## 👨‍💻 Author

- **GitHub:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

**Topic Tags:** 

![Arrays](https://img.shields.io/badge/Topic-Arrays-blueviolet?style=flat-square)
![Sorting](https://img.shields.io/badge/Topic-Sorting-blueviolet?style=flat-square)
![Numbers](https://img.shields.io/badge/Topic-Numbers-blueviolet?style=flat-square)
![Bit Manipulation](https://img.shields.io/badge/Topic-Bit_Manipulation-blueviolet?style=flat-square)
![Custom Comparator](https://img.shields.io/badge/Topic-Custom_Comparator-blueviolet?style=flat-square)

**Company Tags:** 

![Zoho](https://img.shields.io/badge/Company-Zoho-0078D4?style=flat-square)
![Microsoft](https://img.shields.io/badge/Company-Microsoft-0078D4?style=flat-square)