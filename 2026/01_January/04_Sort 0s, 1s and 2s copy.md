# 🚥 Sort 0s, 1s and 2s

<div align="center">
    <a href="https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s4231/1">
        <img src="https://img.shields.io/badge/GeeksforGeeks-Sort%200s%2C%201s%20and%202s-2980b9?logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks Problem Link" />
    </a>
    <img src="https://img.shields.io/badge/Difficulty-Medium-orange?logo=scale" alt="Difficulty Medium" />
    <img src="https://img.shields.io/badge/Accuracy-50.58%25-green" alt="Accuracy 50.58%" />
    <img src="https://img.shields.io/badge/Points-4-blue" alt="Points 4" />
    <img src="https://img.shields.io/badge/License-MIT-yellow" alt="MIT License" />
</div>

<br />

<div align="center">
  <h3>⚠️ Educational Use Only</h3>
  <p>This repository and its content are intended solely for educational purposes.</p>
  <p>Solutions are provided for learning, practice, and reference only.</p>
  <p>Problem statement and test cases are based on the <a href="https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s4231/1">GeeksforGeeks problem</a>.</p>
</div>

---

## 📝 Problem Statement

Given an array `arr[]` containing only **0s**, **1s**, and **2s**. Sort the array in ascending order.

**Note:** You need to solve this problem without utilizing the built-in sort function.

**Follow up:** Could you come up with a one-pass algorithm using only constant extra space?

---

## 🧪 Examples

**Example 1:**

```javascript
Input: arr[] = [0, 1, 2, 0, 1, 2]
Output: [0, 0, 1, 1, 2, 2]
Explanation: 0s, 1s and 2s are segregated into ascending order.
```

**Example 2:**

```javascript
Input: arr[] = [0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1]
Output: [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2]
Explanation: 0s, 1s and 2s are segregated into ascending order.
```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's take `arr = [0, 1, 2, 0, 1, 2]`

1.  **Objective:** Move all `0`s to the front, `2`s to the back, leaving `1`s in the middle.
2.  **Initial State:** `[0, 1, 2, 0, 1, 2]`
3.  **Process:**
    * Found `0`, place at start.
    * Found `2`, place at end.
    * `1`s naturally settle in between.
4.  **Result:** `[0, 0, 1, 1, 2, 2]`

</details>

---

## 🚧 Constraints

* $1 \le arr.size() \le 10^6$
* $0 \le arr[i] \le 2$

---

## 💡 Solution Approaches

We will explore three approaches:
1.  **Built-in Sort:** The naive $O(N \log N)$ approach.
2.  **Counting Sort:** A two-pass $O(N)$ approach counting frequencies.
3.  **Dutch National Flag Algorithm:** An optimal one-pass $O(N)$ approach using 3 pointers.

### Approach 1: Built-in Sort

#### 🔹 Intuition
The simplest way to solve any sorting problem is to use the language's standard library sort function.

#### 💻 Code (C++)

```cpp
// Intuition: Leverage the highly optimized standard library sorting algorithm.
// Approach: Use std::sort to arrange elements in non-decreasing order.
// Time Complexity: O(N * log(N)) due to sorting mechanics.
// Space Complexity: O(1) or O(log N) depending on the internal implementation of sort.

//Approach-1 : Sorting
//T.C : O(n*log(n))
//S.C : O(1)
class Solution {
  public:
    void sort012(vector<int>& arr) {
        // Simple built-in sort
        sort(begin(arr), end(arr));
    }
};

/*
* Dry Run
* Input: [2, 0, 1]
* 1. sort() function called.
* 2. Internal algo rearranges elements.
* 3. Result: [0, 1, 2]
*/
```

---

### Approach 2: Counting Sort

#### 🔹 Intuition
Since we know the array only contains three distinct numbers (0, 1, 2), we can simply count how many times each number appears and then overwrite the array based on these counts.

#### 💻 Code (C++)

```cpp
// Intuition: Since values are restricted to 0, 1, 2, we can count frequencies and reconstruct the array.
// Approach: Iterate once to count 0s, 1s, 2s. Iterate again to fill the array sequentially.
// Time Complexity: O(2N) -> O(N), as we traverse the array twice.
// Space Complexity: O(1), using fixed number of counter variables.

//Approach-2 (Using counting)
//T.C : O(n+n)
//S.C : O(1)
class Solution {
  public:
    void sort012(vector<int>& arr) {
        int n = arr.size();
        
        int count_0 = 0;
        int count_1 = 0;
        int count_2 = 0;
        
        // Pass 1: Count frequencies
        for(int &num : arr) {
            if(num == 0)
                count_0++;
            else if(num == 1)
                count_1++;
            else
                count_2++;
        }
        
        // Pass 2: Overwrite array based on counts
        for(int i = 0; i<n; i++) {
            if(count_0 > 0) {
                arr[i] = 0;
                count_0--;
            } else if(count_1 > 0) {
                arr[i] = 1;
                count_1--;
            } else if(count_2 > 0) {
                arr[i] = 2;
                count_2--;
            }
        }
    }
};

/*
* Dry Run
* Input: [0, 2, 1, 2, 0]
* Pass 1: count_0 = 2, count_1 = 1, count_2 = 2
* Pass 2:
* i=0: count_0 > 0 -> arr[0]=0, count_0=1
* i=1: count_0 > 0 -> arr[1]=0, count_0=0
* i=2: count_1 > 0 -> arr[2]=1, count_1=0
* i=3: count_2 > 0 -> arr[3]=2, count_2=1
* i=4: count_2 > 0 -> arr[4]=2, count_2=0
* Result: [0, 0, 1, 2, 2]
*/
```

---

### Approach 3: Dutch National Flag Algorithm (Optimal)

#### 🔹 Intuition
We divide the array into three regions: `0`s on the left, `2`s on the right, and `1`s in the middle. We maintain three pointers: `i` (low) for the boundary of 0s, `k` (high) for the boundary of 2s, and `j` (mid) to traverse the array.

#### 💻 Code (C++)

```cpp
// Intuition: Maintain 3 pointers: i (low) for 0s region, j (mid) for current element, k (high) for 2s region.
// Approach: Move j. If 0, swap with i. If 2, swap with k. If 1, just move j.
// Time Complexity: O(N) - One pass solution.
// Space Complexity: O(1) - Constant extra space.

//Approach-3 (Follow up) : O(n)
//T.C : O(n)
//S.C : O(1)
class Solution {
  public:
    void sort012(vector<int>& arr) {
        int n = arr.size();
        
        int i = 0;   // denotes boundary for 0
        int j = 0;   // current element iterator (denotes 1)
        int k = n-1; // denotes boundary for 2
        
        while ( j <= k) {
            if(arr[j] == 1) {
                // If 1, it's in correct middle region, just move forward
                j++;
            } else if(arr[j] == 2) {
                // If 2, swap to the right boundary (k) and shrink right region
                swap(arr[j], arr[k]);
                k--;
                // Don't increment j, we need to check the swapped element
            } else { // arr[j] == 0
                // If 0, swap to left boundary (i), expand left region, move forward
                swap(arr[j], arr[i]);
                i++;
                j++;
            }
        }
    }
};

/*
* Dry Run
* Input: [2, 0, 1]
* Init: i=0, j=0, k=2
*
* Iteration 1 (j=0, arr[j]=2):
* Swap arr[0] and arr[2] -> [1, 0, 2]
* k becomes 1. j stays 0.
*
* Iteration 2 (j=0, arr[j]=1):
* arr[j] is 1, just j++
* j becomes 1.
*
* Iteration 3 (j=1, arr[j]=0):
* Swap arr[1] and arr[0] -> [0, 1, 2]
* i becomes 1, j becomes 2.
*
* Loop ends (j > k).
* Result: [0, 1, 2]
*/
```

---

## 🗝️ Key Insights

* **Problem Pattern:** This is a classic variation of the **Dutch National Flag problem** proposed by Edsger Dijkstra.
* **Counting vs Pointers:** While Counting Sort is easy to implement and $O(N)$, it requires two passes over the array. The 3-pointer approach does it in a single pass.
* **Pointer Logic:**
    * `0` to `i-1`: All Zeros
    * `i` to `j-1`: All Ones
    * `k+1` to `n-1`: All Twos
    * `j` to `k`: Unsorted/Unknown region.

---

## 🚀 Further Exploration

* **Sort Colors:** The exact same problem on [LeetCode #75](https://leetcode.com/problems/sort-colors/).
* **Move Zeroes:** Segregating 0s and non-0s.
* **Wiggle Sort:** Sorting with specific relative order requirements.

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/sort-an-array-of-0s-1s-and-2s4231/1)
* [Dutch National Flag Algorithm Wiki](https://en.wikipedia.org/wiki/Dutch_national_flag_problem)

---

## 👨‍💻 Author

**Nilesh** [GitHub Profile](https://github.com/imnilesh18)

---

## 🔖 Tags

`arrays` `sorting` `two-pointers` `dutch-national-flag` `cpp` `medium`

---

## 📜 License

<div align="center">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License">
  <p>This project is licensed under the MIT License.</p>
  <p><b>⚠️ Educational Use Only:</b> This repository contains solutions for educational purposes.</p>
</div>