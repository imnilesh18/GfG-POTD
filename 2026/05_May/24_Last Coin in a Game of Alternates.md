# 🪙 Last Coin in a Game of Alternates

<div align="center">
  
[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/last-coin-in-a-game-of-alternates/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Basic-42A5F5?style=for-the-badge)](#)
[![Accuracy](https://img.shields.io/badge/Accuracy-68.75%25-brightgreen?style=for-the-badge)](#)
[![Points](https://img.shields.io/badge/Points-1-orange?style=for-the-badge)](#)
[![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)](#)

</div>

⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array integer `arr[]`, representing the values of coins arranged in a row. Two players play a game by picking coins alternately. 

At each turn, a player can pick a coin from either the beginning or the end of the array. Both players follow a **greedy strategy**, i.e., they always pick the coin with the maximum value among the two available ends. The game continues until only one coin remains.

Find the value of the **last remaining coin**.

---

## 💡 Examples

```text
Input: arr[] = [5, 3, 1, 6, 9]
Output: 1

```

1. **Turn 1:** Available ends are `5` and `9`. Pick `9`, remaining array: `[5, 3, 1, 6]`
2. **Turn 2:** Available ends are `5` and `6`. Pick `6`, remaining array: `[5, 3, 1]`
3. **Turn 3:** Available ends are `5` and `1`. Pick `5`, remaining array: `[3, 1]`
4. **Turn 4:** Available ends are `3` and `1`. Pick `3`, remaining array: `[1]`

Final Output: `1`

```text
Input: arr[] = [5, 9, 2, 5]
Output: 2
Explanation:
Players always pick the larger coin from the two ends.
Pick 5, remaining array: [9, 2, 5]
Pick 9, remaining array: [2, 5]
Pick 5, remaining array: [2]
Final Output: 2

```

```text
Input: arr[] = [11]
Output: 11
Explanation:
Only one coin is present in the array, so no moves are made.
Final Output: 11

```

---

## ⚠️ Constraints

* $1 \le arr.size() \le 10^5$
* $1 \le arr[i] \le 10^6$

---

## 🚀 Solution Approaches

### 1️⃣ Approach 1: Sorting & Removing Maximums (Brute-Force)

**Intuition:** Because players always pick the largest available coin from the ends, the absolute minimum element in the array is guaranteed to be the last one left. Sorting the array and dropping the maximum repeatedly achieves this by isolating that minimum value.

```cpp
// Intuition: Because players always pick the largest available coin from the ends, the absolute minimum element in the array is guaranteed to be the last one left. Sorting the array and dropping the maximum repeatedly achieves this by isolating that minimum value.
// Approach: Loop continuously as long as the array has more than one element. In each iteration, sort the array in ascending order to push the maximum element to the back. Use pop_back() to remove that maximum element. Once the loop breaks, return the only remaining element.
// Time Complexity: O(N^2 log N) because we are running an O(N log N) sorting algorithm inside a while loop that runs N-1 times.
// Space Complexity: O(1) auxiliary space since we modify the input array in-place without allocating extra data structures.

class Solution {
  public:
    int coin(vector<int>& arr) {
        int n = arr.size(); // store initial size
        
        while(arr.size() != 1) { // loop until only one coin remains
            sort(arr.begin(), arr.end()); // sort to move the largest coin to the end
            arr.pop_back(); // remove the largest coin
        }
        
        return arr[0]; // return the final remaining coin
        
    }
};

/*
*
* Dry Run
* Input: arr = [5, 9, 2, 5]
* * Initial array is [5, 9, 2, 5]
* Loop starts because size is 4
* Sort makes array [2, 5, 5, 9]
* pop_back removes 9, array becomes [2, 5, 5]
* Size is 3, loop continues
* Sort makes array [2, 5, 5]
* pop_back removes 5, array becomes [2, 5]
* Size is 2, loop continues
* Sort makes array [2, 5]
* pop_back removes 5, array becomes [2]
* Size is 1, loop terminates
* Returns arr[0] which is 2
*
*/

```

---

### 2️⃣ Approach 2: Two-Pointer Simulation (Optimized)

**Intuition:** Since players are constrained to picking from the ends of the remaining subarray, we can simulate the game perfectly by placing pointers at both ends. We just shrink the window inward from whichever side has the larger value.

```cpp
// Intuition: Since players are constrained to picking from the ends of the remaining subarray, we can simulate the game perfectly by placing pointers at both ends. We just shrink the window inward from whichever side has the larger value.
// Approach: Initialize a start pointer 'i' at the beginning and an end pointer 'j' at the last index. Loop as long as 'i' is strictly less than 'j'. Compare the elements at both pointers. If the start element is larger, increment 'i' to simulate picking it. Otherwise, decrement 'j' to simulate picking the end element. Stop when both pointers meet at the final coin.
// Time Complexity: O(N) because each step of the loop moves a pointer inward by one position, processing each element exactly once.
// Space Complexity: O(1) as we are only using two integer variables for the pointers.

class Solution {
  public:
    int coin(vector<int>& arr) {
        int n = arr.size(); // get total number of coins
        int i = 0; // start pointer at the beginning
        int j = n - 1; // end pointer at the last element
        
        while(i < j) { // continue until pointers point to the same coin
            if(arr[i] > arr[j]) { // start coin is larger
                i++; // move start pointer inward
            } else { // end coin is larger or equal
                j--; // move end pointer inward
            }
        }
        
        return arr[j]; // return the single isolated coin
        
    }
};

/*
*
* Dry Run
* Input: arr = [5, 3, 1, 6, 9]
*
* Start with i = 0, j = 4
* arr[0] is 5 and arr[4] is 9
* 5 is not greater than 9, so j decrements to 3
* Now i = 0, j = 3
* arr[0] is 5 and arr[3] is 6
* 5 is not greater than 6, so j decrements to 2
* Now i = 0, j = 2
* arr[0] is 5 and arr[2] is 1
* 5 is greater than 1, so i increments to 1
* Now i = 1, j = 2
* arr[1] is 3 and arr[2] is 1
* 3 is greater than 1, so i increments to 2
* Now i = 2, j = 2
* Loop terminates because i is no longer less than j
* Returns arr[2] which is 1
*
*/

```

---

## 🧠 Key Insights

* **Greedy End Selection:** The problem is purely deterministic. Because both players act greedily based on the *visible* ends, simulating this action directly via the two-pointer technique faithfully represents the state of the game at any turn without requiring complex Min-Max algorithms.
* **Optimization Jump:** The naive way of sorting and popping elements unnecessarily processes the data repeatedly $O(N^2 \log N)$, whereas keeping track of the boundaries with two pointers drops the complexity down to a simple linear traversal $O(N)$.

---

## 🔍 Further Exploration

* Try variants where players try to maximize their *own sum* instead of purely picking the larger endpoint (e.g., *Optimal Strategy for a Game*).
* Practice Two-Pointer algorithms on arrays where choices at the ends dictate shrinking windows (e.g., *Container With Most Water*).

---

## 🔗 References

* **GeeksforGeeks Problem:** [Last Coin in a Game of Alternates](https://www.geeksforgeeks.org/problems/last-coin-in-a-game-of-alternates/1)

---

## 🧑‍💻 Author

**Nilesh** [GitHub Profile](https://github.com/imnilesh18)

---

## 🏷️ Tags

`two-pointer-algorithm` `Arrays` `Greedy` `Data Structures` `Algorithms`