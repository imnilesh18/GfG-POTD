# 🟧 Insert Interval

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge&logo=geeksforgeeks)](https://www.geeksforgeeks.org/problems/insert-interval-1666733333/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-50.61%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/insert-interval-1666733333/1).

---

## 📄 Problem Statement

Geek has an array of non-overlapping intervals `intervals[][]` where `intervals[i] = [starti, endi]` represent the start and the end of the _ith_ event and `intervals` is sorted in **ascending** order by `starti`. He wants to add a new interval `newInterval[] = [newStart, newEnd]` where `newStart` and `newEnd` represent the start and end of this interval.

Help Geek to **insert** `newInterval` into `intervals` such that `intervals` is still sorted in ascending order by `starti` and `intervals` still does not have any overlapping intervals (merge overlapping intervals if necessary).

---

## 🧪 Examples

### Example 1

```
Input: intervals[][] = [[1, 3], [4, 5], [6, 7], [8, 10]], newInterval[] = [5, 6]
Output: [[1, 3], [4, 7], [8, 10]]
Explanation: The newInterval [5, 6] overlaps with [4, 5] and [6, 7]. So, they are merged into one interval [4, 7].
```

<details>
<summary>📖 Example Breakdown</summary>

1.  **Initial State**: `intervals = [[1, 3], [4, 5], [6, 7], [8, 10]]`, `newInterval = [5, 6]`.
2.  **Iterate and Add Non-Overlapping**:
    - `[1, 3]` ends before `[5, 6]` starts. Add `[1, 3]` to the result.
    - Result: `[[1, 3]]`
3.  **Merge Overlapping Intervals**:
    - The next interval `[4, 5]` overlaps with `newInterval = [5, 6]` because `4 <= 6`.
    - Merge them: `newStart = min(5, 4) = 4`, `newEnd = max(6, 5) = 6`. The merged interval is now `[4, 6]`.
    - The next interval `[6, 7]` overlaps with the _updated_ `newInterval = [4, 6]` because `6 <= 6`.
    - Merge them: `newStart = min(4, 6) = 4`, `newEnd = max(6, 7) = 7`. The merged interval is now `[4, 7]`.
4.  **Add Merged Interval**:
    - The loop for merging ends. Add the final merged interval `[4, 7]` to the result.
    - Result: `[[1, 3], [4, 7]]`
5.  **Add Remaining Intervals**:
    - The next interval `[8, 10]` starts after `[4, 7]` ends. Add it to the result.
    - Result: `[[1, 3], [4, 7], [8, 10]]`
6.  **Final Output**: `[[1, 3], [4, 7], [8, 10]]`.

</details>

### Example 2

```
Input: intervals[][] = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], newInterval[] = [4, 9]
Output: [[1, 2], [3, 10], [12, 16]]
Explanation: The new interval [4, 9] overlaps with [3, 5], [6, 7] and [8, 10]. So, they are merged into one interval [3, 10].
```

---

## 📏 Constraints

> `1 ≤ intervals.size() ≤ 10^5` > `0 ≤ starti ≤ endi ≤ 10^9` > `0 ≤ newStart ≤ newEnd ≤ 10^9`

---

## 💡 Solution Approaches

### Optimized Approach

The core idea is to iterate through the intervals and divide the problem into three phases:

1.  **Phase 1: Non-Overlapping (Before)**: Add all intervals that end before the `newInterval` starts. These intervals are guaranteed to be part of the final result and appear first.
2.  **Phase 2: Overlapping/Merging**: Once we find an interval that overlaps with `newInterval`, we enter the merging phase. We greedily merge all subsequent overlapping intervals with our `newInterval` by updating its start and end times. The new start becomes the minimum of the current starts, and the new end becomes the maximum of the current ends.
3.  **Phase 3: Non-Overlapping (After)**: After merging all possible intervals, the updated `newInterval` is added to the result. Then, all remaining intervals are added, as they are guaranteed to start after the merged interval ends.

---

### C++ Code

```cpp
// Intuition: The problem can be broken down into three parts: adding intervals before the new one,
// merging the new interval with any that overlap, and finally adding the intervals that come after.
// Approach:
// 1. Initialize an empty result vector.
// 2. Iterate through the original intervals. Add all intervals that end before the `newInterval` starts directly to the result.
// 3. Once an overlapping interval is found (i.e., `interval.start <= newInterval.end`), start merging.
//    Update `newInterval` by taking the minimum of start times and the maximum of end times.
// 4. Continue this merge process for all subsequent overlapping intervals.
// 5. After the merging phase, add the updated `newInterval` to the result.
// 6. Add all remaining intervals from the original list to the result.
// 7. Return the result vector.
// Time Complexity: O(N), where N is the number of intervals, as we iterate through the list once.
// Space Complexity: O(N) in the worst case, for storing the result vector.
class Solution {
  public:
    vector<vector<int>> insertInterval(vector<vector<int>> &intervals,
                                           vector<int> &newInterval) {
        vector<vector<int>> res; // Stores the final merged intervals
        int i = 0;
        int n = intervals.size();

        // Phase 1: Add all intervals that come before the new interval
        // These intervals do not overlap and can be added directly.
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.push_back(intervals[i]);
            i++;
        }

        // Phase 2: Merge all overlapping intervals with the new interval
        // An interval overlaps if its start is less than or equal to the new interval's end.
        while (i < n && intervals[i][0] <= newInterval[1]) {
            // Update the new interval to be the union of the current and new intervals
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        res.push_back(newInterval); // Add the merged interval

        // Phase 3: Add all the remaining intervals
        // These intervals start after the merged interval ends.
        while (i < n) {
            res.push_back(intervals[i]);
            i++;
        }

        return res;
    }
};

/*
*
* Dry Run
*
* Input: intervals = [[1, 3], [4, 5], [6, 7], [8, 10]], newInterval = [5, 6]
*
* 1. Initialize res = [], i = 0, n = 4.
*
* Phase 1 (Non-overlapping):
* - i = 0: intervals[0][1] (3) < newInterval[0] (5). This is true.
* - res.push_back([1, 3]). res = [[1, 3]]. i becomes 1.
* - i = 1: intervals[1][1] (5) < newInterval[0] (5). This is false. Loop ends.
*
* Phase 2 (Merging):
* - i = 1: intervals[1][0] (4) <= newInterval[1] (6). This is true.
* - newInterval[0] = min(5, 4) = 4.
* - newInterval[1] = max(6, 5) = 6.
* - newInterval is now [4, 6]. i becomes 2.
* - i = 2: intervals[2][0] (6) <= newInterval[1] (6). This is true.
* - newInterval[0] = min(4, 6) = 4.
* - newInterval[1] = max(6, 7) = 7.
* - newInterval is now [4, 7]. i becomes 3.
* - i = 3: intervals[3][0] (8) <= newInterval[1] (7). This is false. Loop ends.
*
* - res.push_back(newInterval). res = [[1, 3], [4, 7]].
*
* Phase 3 (Remaining):
* - i = 3: i < n is true.
* - res.push_back(intervals[3]), which is [8, 10]. res = [[1, 3], [4, 7], [8, 10]]. i becomes 4.
* - i = 4: i < n is false. Loop ends.
*
* Final Result: [[1, 3], [4, 7], [8, 10]]
*
*/
```

---

### Java Code

```java
// Intuition: The problem can be solved by iterating through the intervals and handling three distinct cases:
// intervals before the new one, intervals overlapping with the new one, and intervals after.
// Approach:
// 1. Create a new ArrayList to store the result.
// 2. Iterate while the current interval's end is less than the new interval's start. Add these intervals to the result.
// 3. Iterate while the current interval's start is less than or equal to the new interval's end. This is the merge phase.
//    Update the new interval's bounds by taking the minimum of starts and maximum of ends.
// 4. After the merge loop, add the final merged `newInterval`.
// 5. Add all remaining intervals to the result.
// 6. Return the result list.
// Time Complexity: O(N), because we traverse the list of intervals only once.
// Space Complexity: O(N), as the result list can contain up to N+1 intervals.
class Solution {
    public ArrayList<int[]> insertInterval(int[][] intervals, int[] newInterval) {
        ArrayList<int[]> res = new ArrayList<>(); // To store the result
        int i = 0;
        int n = intervals.length;

        // Phase 1: Add all intervals that appear before the new interval
        while (i < n && intervals[i][1] < newInterval[0]) {
            res.add(intervals[i]);
            i++;
        }

        // Phase 2: Merge all intervals that overlap with the new interval
        while (i < n && intervals[i][0] <= newInterval[1]) {
            // Expand the new interval to encompass the current one
            newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
            newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
            i++;
        }
        res.add(newInterval); // Add the newly merged interval

        // Phase 3: Add all remaining intervals that come after
        while (i < n) {
            res.add(intervals[i]);
            i++;
        }

        return res;
    }
}

/*
*
* Dry Run
*
* Input: intervals = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], newInterval = [4, 9]
*
* 1. Initialize res = [], i = 0, n = 5.
*
* Phase 1 (Non-overlapping):
* - i = 0: intervals[0][1] (2) < newInterval[0] (4). True.
* - res.add([1, 2]). res = [[1, 2]]. i becomes 1.
* - i = 1: intervals[1][1] (5) < newInterval[0] (4). False. Loop ends.
*
* Phase 2 (Merging):
* - i = 1: intervals[1][0] (3) <= newInterval[1] (9). True.
* - newInterval[0] = min(4, 3) = 3.
* - newInterval[1] = max(9, 5) = 9.
* - newInterval is now [3, 9]. i becomes 2.
* - i = 2: intervals[2][0] (6) <= newInterval[1] (9). True.
* - newInterval[0] = min(3, 6) = 3.
* - newInterval[1] = max(9, 7) = 9.
* - newInterval is still [3, 9]. i becomes 3.
* - i = 3: intervals[3][0] (8) <= newInterval[1] (9). True.
* - newInterval[0] = min(3, 8) = 3.
* - newInterval[1] = max(9, 10) = 10.
* - newInterval is now [3, 10]. i becomes 4.
* - i = 4: intervals[4][0] (12) <= newInterval[1] (10). False. Loop ends.
*
* - res.add(newInterval). res = [[1, 2], [3, 10]].
*
* Phase 3 (Remaining):
* - i = 4: i < n is true.
* - res.add(intervals[4]), which is [12, 16]. res = [[1, 2], [3, 10], [12, 16]]. i becomes 5.
* - i = 5: i < n is false. Loop ends.
*
* Final Result: [[1, 2], [3, 10], [12, 16]]
*
*/
```

---

## 🔑 Key Insights

- **Greedy Approach**: The problem has an optimal substructure and greedy-choice property. By processing intervals sequentially, we can make the locally optimal choice at each step (either add, merge, or stop) which leads to a globally optimal solution.
- **Sorted Input**: The fact that the initial `intervals` array is sorted by `starti` is crucial. This property allows us to process intervals in a single pass without needing to look back, ensuring an efficient O(N) solution. If the array were unsorted, we would first need to sort it, adding an O(N log N) step.
- **Three-Phase Logic**: Separating the logic into three distinct phases simplifies the code and reasoning. It cleanly handles the intervals that are completely separate from the `newInterval` and isolates the core merging logic.

---

## 🚀 Further Exploration

- [Merge Intervals](https://leetcode.com/problems/merge-intervals/description/)
- [Non-overlapping Intervals](https://www.geeksforgeeks.org/problems/non-overlapping-intervals/1)
- [Meeting Rooms II](https://www.geeksforgeeks.org/problems/attend-all-meetings-ii/1) (A variation involving finding the minimum number of rooms required)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks | Insert Interval](https://www.geeksforgeeks.org/problems/insert-interval-1666733333/1)
- **Article:** [Insert in Sorted and Non-overlapping Interval Array](https://www.geeksforgeeks.org/dsa/insert-in-sorted-and-non-overlapping-interval-array/)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## #️⃣ Tags

`array` `intervals` `merging` `greedy` `geeksforgeeks` `medium-difficulty`

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A Note on Academic Integrity:** This repository is for educational purposes. Copying and pasting code without understanding it is not a substitute for learning. Always try to solve problems on your own first!
