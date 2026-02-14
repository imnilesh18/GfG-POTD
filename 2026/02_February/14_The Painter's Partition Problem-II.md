# 🖌️ The Painter's Partition Problem-II

![Difficulty: Hard](https://img.shields.io/badge/Difficulty-Hard-orange?logo=geeksforgeeks&logoColor=white)
![Accuracy: 27.52%](https://img.shields.io/badge/Accuracy-27.52%25-blue)
![Points: 8](https://img.shields.io/badge/Points-8-yellow)
![License: MIT](https://img.shields.io/badge/License-MIT-green)

> [!IMPORTANT]
> **⚠️ Educational Use Only**
>
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/the-painters-partition-problem1535/1).

---

## 📝 Problem Statement

Given an array `arr[]` where each element denotes the length of a board, and an integer `k` representing the number of **painters** available. Each painter takes **1 unit of time** to paint **1 unit length** of a board.

Determine the **minimum** amount of time required to paint all the boards, under the constraint that each painter can paint only a **contiguous** sequence of boards (no skipping or splitting allowed).

### ⚙️ Constraints

- $1 \leq \text{arr.size()} \leq 10^5$
- $1 \leq \text{arr}[i] \leq 10^4$
- $1 \leq k \leq 10^5$

---

## 🔍 Examples

### Case 1
```text
Input: arr[] = [5, 10, 30, 20, 15], k = 3
Output: 35

```

<details>
<summary>📖 <strong>Example Breakdown</strong></summary>

The optimal allocation of boards among 3 painters is:

* **Painter 1**: `[5, 10]`  time = 
* **Painter 2**: `[30]`  time = 
* **Painter 3**: `[20, 15]`  time = 

The job is done when the last painter finishes.
**Total time** = .

</details>

### Case 2

```text
Input: arr[] = [10, 20, 30, 40], k = 2
Output: 60
Explanation: 
Painter 1 takes [10, 20, 30] (time 60).
Painter 2 takes [40] (time 40).
Max time is 60.

```

### Case 3

```text
Input: arr[] = [100, 200, 300, 400], k = 1
Output: 1000
Explanation: Only one painter takes all boards. Sum = 1000.

```

---

## 💡 Solution Approach

### Binary Search on Answer

The problem asks for a minimum value (maximum time allowed per painter) that satisfies a condition. This structure suggests a **Binary Search on Answer** approach.

1. **Search Space**:
* **Low**: The largest single board (a painter must paint at least the largest board).
* **High**: The sum of all boards (one painter paints everything).


2. **Binary Search**: Pick a `mid` value representing a potential "max time limit".
3. **Feasibility Check (`isPossible`)**:
* Iterate through the boards and assign them greedily to a painter.
* If adding a board exceeds `mid`, assign it to a new painter.
* If the number of painters needed , then `mid` is feasible.


4. **Optimization**:
* If feasible, try a smaller time (`high = mid - 1`).
* If not, increase the time limit (`low = mid + 1`).



```cpp
// Intuition: The problem asks for the minimum time to complete a job where the workload is distributed. The answer lies within a range [max(board_length), sum(total_length)]. Since the feasibility function is monotonic (if x time is enough, x+1 is also enough), we can use Binary Search on the Answer.
// Approach:
// 1. Determine the search space: low = max element in arr, high = sum of all elements.
// 2. Perform Binary Search: Calculate mid as a potential maximum time allowed for a painter.
// 3. Use a greedy helper function 'isPossible' to check if painting is possible with 'k' painters within 'mid' time.
// 4. If possible, try to minimize time by moving left (high = mid - 1).
// 5. If not possible, we need more time per painter, so move right (low = mid + 1).
// Time Complexity: O(N * log(sum(arr))) where N is the number of boards. The search space is the sum of array elements.
// Space Complexity: O(1) as we use constant extra space.

class Solution {
  public:
    // checks whether all boards can be painted within 'maxTime'
    // by dividing the work among at most k painters
    bool isPossible(int maxTime,  vector<int>& arr, int k) {
        int painters = 1;    
        int currSum = 0;      
    
        for (int length : arr) {
            // if a board is longer than maxTime,
            // it's impossible to assign
            if (length > maxTime)
                return false;
    
            // if assigning this board exceeds maxTime, 
            // give it to a new painter
            if (currSum + length > maxTime) {
                painters++;        
                currSum = length;  
            } 
            // otherwise, continue adding to the current 
            // painter's workload
            else {
                currSum += length;
            }
        }
    
        // return true if total painters used is
        // within the allowed k
        return painters <= k;
    }
    
    // returns the minimum possible time to paint all 
    // boards using exactly k painters
    int minTime(vector<int>& arr, int k) {
        
        // lower limit is the largest board 
        // (can't split boards)
        int low = *max_element(arr.begin(), arr.end());
    
        // upper limit is the sum of all board lengths 
        // (one painter does all)
        int high = accumulate(arr.begin(), arr.end(), 0);
    
        int result = high;
    
        while (low <= high) {
            int mid = (low + high) / 2;
    
            // if this time allows us to paint
            // with k painters or fewer
            if (isPossible(mid, arr, k)) {
                result = mid;      
                high = mid - 1;    
            } 
            
            // if not possible, we need to allow 
            // more time
            else {
                low = mid + 1;
            }
        }
    
        return result;
    }

};

/*
*
* Dry Run
* Input: arr[] = [10, 20, 30, 40], k = 2
*
* Initial Bounds:
* low = 40 (max element), high = 100 (sum)
* result = 100
*
* Iteration 1:
* mid = (40 + 100) / 2 = 70
* isPossible(70, arr, 2):
* Painter 1: 10 + 20 + 30 = 60 (next 40 would make 100 > 70) -> Count = 1
* Painter 2: 40 -> Count = 2
* 2 <= 2 is True. Possible.
* result = 70
* high = 69
*
* Iteration 2:
* mid = (40 + 69) / 2 = 54
* isPossible(54, arr, 2):
* Painter 1: 10 + 20 = 30 (next 30 would make 60 > 54) -> Count = 1
* Painter 2: 30 (next 40 would make 70 > 54) -> Count = 2
* Painter 3: 40 -> Count = 3
* 3 <= 2 is False. Not Possible.
* low = 55
*
* Iteration 3:
* mid = (55 + 69) / 2 = 62
* isPossible(62, arr, 2):
* Painter 1: 10 + 20 + 30 = 60. Count = 1
* Painter 2: 40. Count = 2.
* True. Possible.
* result = 62
* high = 61
*
* Iteration 4:
* mid = (55 + 61) / 2 = 58
* isPossible(58, arr, 2):
* P1: 30 (10+20). P2: 30. P3: 40. Count = 3. False.
* low = 59
*
* Iteration 5:
* mid = (59 + 61) / 2 = 60
* isPossible(60, arr, 2):
* P1: 60 (10+20+30). P2: 40. Count = 2. True.
* result = 60
* high = 59
*
* Loop Ends (low 59 > high 59 is false? No, low 59 <= high 59 is true).
* Next Iteration: mid = 59. isPossible(59) -> False. low becomes 60.
* Loop Ends.
* Return result = 60.
*/

```

---

## 🗝️ Key Insights

1. **Monotonicity**: The problem exhibits a monotonic property. If it is possible to complete the job in time , it is definitely possible to complete it in any time . If it's impossible in time , it's impossible for any time . This property is key for **Binary Search**.
2. **Greedy Allocation**: To check if a specific time limit `mid` is feasible, we simply iterate through the array and assign boards to the current painter until their time limit is reached, then move to the next painter. This greedy strategy ensures we use the minimum number of painters for a given time constraint.
3. **Search Space**: The answer is bounded by the largest single board (lower bound) and the total sum of lengths (upper bound).

---

## 🔗 Further Exploration

Similar "Binary Search on Answer" problems:

* **Allocate Minimum Number of Pages**: Almost identical logic.
* **Aggressive Cows**: Maximizing the minimum distance.
* **Capacity To Ship Packages Within D Days**: Same partition logic.

---

## 📚 References

* [The Painter's Partition Problem-II on GeeksforGeeks](https://www.geeksforgeeks.org/problems/the-painters-partition-problem1535/1)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)
