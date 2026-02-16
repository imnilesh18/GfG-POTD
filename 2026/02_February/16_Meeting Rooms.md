# 🗓️ Meeting Rooms

<div align="center">

[![Status](https://img.shields.io/badge/Status-Active-success?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/attend-all-meetings/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/attend-all-meetings/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-65.12%25-blue?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/attend-all-meetings/1)
[![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/attend-all-meetings/1)
[![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge&logo=github&logoColor=white)](LICENSE)

</div>

---

### ⚠️ Educational Use Only
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Given a 2D array `arr[][]`, where `arr[i][0]` is the **starting time** of the $i^{th}$ meeting and `arr[i][1]` is the **ending time** of the $i^{th}$ meeting, the task is to check if it is possible for a person to attend all the meetings such that he can attend only one meeting at a particular time.

**Note:** A person can attend a meeting if its starting time is greater than or equal to the previous meeting's ending time.

---

## 📊 Examples

### Example 1
```bash
Input: arr[][] = [[1, 4], [10, 15], [7, 10]]
Output: true
Explanation: Since all the meetings are held at different times, it is possible to attend all the meetings.

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

1. **Meetings**: `[1, 4]`, `[10, 15]`, `[7, 10]`
2. **Sorted Order**:
* Meeting 1: `1` to `4`
* Meeting 2: `7` to `10`
* Meeting 3: `10` to `15`


3. **Check Overlaps**:
* Meeting 1 ends at `4`, Meeting 2 starts at `7`. `4 <= 7` (OK)
* Meeting 2 ends at `10`, Meeting 3 starts at `10`. `10 <= 10` (OK)


4. **Result**: `true`

</details>

### Example 2

```bash
Input: arr[][] = [[2, 4], [9, 12], [6, 10]]
Output: false
Explanation: Since the second and third meeting overlap, a person cannot attend all the meetings.

```

---

## 🛑 Constraints

* $1 \leq arr.size() \leq 10^5$
* $0 \leq arr[i] \leq 2 \times 10^6$

---

## 💡 Solution Approach

### 1️⃣ Sorting & Linear Scan (Optimized)

#### Intuition

To determine if we can attend all meetings, we simply need to ensure that no two meetings overlap. If we visualize meetings on a timeline, an overlap occurs if a meeting starts before the previous one has finished. By sorting the meetings based on their start times, we align them chronologically. Then, we only need to compare the ending time of the current meeting with the starting time of the *immediate next* meeting.

#### Approach

1. **Sort**: Sort the array of meetings based on their start times (the first element of the inner vectors).
2. **Iterate**: Loop through the sorted meetings from the first up to the second-to-last one.
3. **Check Overlap**: For each meeting `i`, check if `arr[i][end_time] > arr[i+1][start_time]`.
4. **Result**: If the condition is true, an overlap exists, return `false`. If the loop completes without finding overlaps, return `true`.

#### Implementation

```cpp
// Intuition: To detect overlaps efficiently, we align meetings chronologically. If sorted by start time, any overlapping meeting implies it starts before the previous one ends.
// Approach: Sort the meetings by start time. Iterate through the sorted list and check if the current meeting ends strictly after the next meeting begins.
// Time Complexity: O(N log N) due to sorting, where N is the number of meetings. The subsequent linear scan takes O(N).
// Space Complexity: O(1) auxiliary space (excluding internal stack space used by the sorting algorithm).

class Solution {
  public:
    bool canAttend(vector<vector<int>> &arr) {
        int n = arr.size();
        
        // Sort the meetings by their start times to process them in chronological order
        sort(arr.begin(), arr.end());
        
        for(int i = 0; i < n - 1; i++) {
           
            // Compare the current meeting's end time with the 
            // next meeting's start time to check for overlap
            // If current meeting ends strictly after next starts, we have a conflict
            if(arr[i][1] > arr[i + 1][0])
              return false;
        }
        return true;
    }
};

/*
*
* Dry Run
* Input: arr = [[1, 4], [10, 15], [7, 10]]
* n = 3
*
* Step 1: Sort arr by start times
* Sorted arr: [[1, 4], [7, 10], [10, 15]]
*
* Step 2: Loop i = 0 to n - 2 (i < 2)
*
* Iteration 1 (i = 0):
* Current meeting: [1, 4], Next meeting: [7, 10]
* End time of current (4) vs Start time of next (7)
* Check: 4 > 7? False. No overlap.
*
* Iteration 2 (i = 1):
* Current meeting: [7, 10], Next meeting: [10, 15]
* End time of current (10) vs Start time of next (10)
* Check: 10 > 10? False. (A meeting ending at 10 allows another starting at 10)
*
* Loop ends.
* Return true.
*
* ------------------------------------------------
*
* Dry Run Case 2
* Input: arr = [[2, 4], [9, 12], [6, 10]]
* Sorted: [[2, 4], [6, 10], [9, 12]]
*
* i = 0: [2, 4] vs [6, 10]. 4 > 6 is False.
* i = 1: [6, 10] vs [9, 12]. 10 > 9 is True.
* Overlap detected! Return false.
*/

```

---

## 🔑 Key Insights

* **Sorting is Key**: The problem reduces to finding any intersection in a set of intervals. Without sorting, we would need to check every pair against every other pair, leading to . Sorting allows us to check for conflicts in .
* **Edge Case**: Be careful with the equality condition. The problem states a person *can* attend a meeting if it starts exactly when the previous one ends (`>=`). Therefore, conflict exists only if `end_time > start_time`.

---

## 🚀 Further Exploration

* **Meeting Rooms II**: Find the minimum number of conference rooms required (Medium).
* **Merge Intervals**: Merge all overlapping intervals (Medium).
* **Non-overlapping Intervals**: Find the minimum number of intervals to remove to make the rest non-overlapping (Medium).

---

## 🔗 References

* [GFG Problem Link](https://www.geeksforgeeks.org/problems/attend-all-meetings/1)
* [C++ std::sort Documentation](https://en.cppreference.com/w/cpp/algorithm/sort)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)
