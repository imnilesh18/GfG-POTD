# 🕒 Difference Check

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/difference-check/1).

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-57.44%25-green.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg?style=for-the-badge)

</div>

---

## 📝 Problem Statement

Given an array `arr[]` of time strings in 24-hour clock format **"HH:MM:SS"**, return the **minimum difference** in **seconds** between any two time strings in the `arr[]`.

The clock wraps around at midnight, so the time difference between `"23:59:59"` and `"00:00:00"` is **1** second.

---

## 📋 Examples

### Example 1

```
Input: arr[] = ["12:30:15", "12:30:45"]
Output: 30
Explanation: The minimum time difference is 30 seconds.
```

### Example 2

```
Input: arr[] = ["00:00:01", "23:59:59", "00:00:05"]
Output: 2
Explanation: The time difference is minimum between "00:00:01" and "23:59:59".
```

<details>
<summary>📖 Example 2 Breakdown</summary>

1.  **Convert times to seconds:**
    - `"00:00:01"` -> `1` second
    - `"23:59:59"` -> `86399` seconds
    - `"00:00:05"` -> `5` seconds
2.  **Calculate differences:**
    - Difference between `5` and `1` is `5 - 1 = 4` seconds.
3.  **Calculate wrap-around difference:**
    - The difference between the earliest time (`00:00:01`) and the latest time (`23:59:59`) across midnight.
    - This is calculated as `(total seconds in a day - latest) + earliest`.
    - `(86400 - 86399) + 1 = 1 + 1 = 2` seconds.
4.  **Find the minimum:**
    - The minimum of all calculated differences (`4` and `2`) is `2`.

</details>

---

## ⚙️ Constraints

> `2 ≤ arr.size() ≤ 10^5` > `arr[i]` is in `"HH:MM:SS"` format.

---

## 💡 Solution Approaches

### Optimized Approach (Using Boolean Array)

The core idea is to convert all time strings into their corresponding total seconds from the start of the day (`00:00:00`). We can then use a boolean array of size `86400` (total seconds in a day) to mark which seconds are present in the input array. By iterating through this boolean array, we can find the minimum difference between adjacent "marked" seconds. The final step is to consider the wrap-around difference between the first and last time of the day.

---

### C++ Solution

```cpp
// Intuition: The problem asks for the minimum time difference. Since the times can wrap around midnight, a linear scan won't work directly.
// We can convert all time points to a single unit (seconds) and place them on a timeline of a single day. The minimum difference will be the smallest gap between any two adjacent time points on this timeline.
//
// Approach:
// 1. Create a boolean array `seen` of size 86400 (for every second in a 24-hour day).
// 2. Iterate through the input `arr`. Convert each "HH:MM:SS" string to total seconds.
// 3. Mark the corresponding index in the `seen` array as `true`. If a time is already seen, it's a duplicate, and the difference is 0, so we can return immediately.
// 4. Iterate through the `seen` array to find the minimum difference between consecutive `true` values.
// 5. Keep track of the `first` and `last` seen seconds to calculate the wrap-around difference (e.g., between 23:59 and 00:01).
// 6. The final answer is the minimum of all adjacent differences and the wrap-around difference.
//
// Time Complexity: O(N + S), where N is the number of time strings and S is the total seconds in a day (86400). Since S is a constant, this is effectively O(N) because if N > S, we are guaranteed a duplicate time and return early.
// Space Complexity: O(S), for the `seen` boolean array. Since S is a constant, this is O(1) space.

class Solution {
 public:
    // Helper function to convert "HH:MM:SS" to total seconds
    int toSeconds(string &time) {
        int h = stoi(time.substr(0, 2));
        int m = stoi(time.substr(3, 2));
        int s = stoi(time.substr(6, 2));
        return h * 3600 + m * 60 + s;
    }

    int minDifference(vector<string> &arr) {
        // Total seconds in a day
        int totalSec = 24 * 3600;

        // Boolean array to mark seen seconds, size = 86400
        vector<bool> seen(totalSec, false);

        int n = arr.size();

        // Mark all seconds in the seen array, return 0 on duplicate
        for (int i = 0; i < n; i++) {
            int sec = toSeconds(arr[i]);
            // If we've seen this time before, the difference is 0
            if (seen[sec] == true) {
                return 0;
            }
            seen[sec] = true;
        }

        // Variables to track first, last, and previous times
        int first = -1;
        int last = -1;
        int prev = -1;
        int minDiff = INT_MAX;

        // Find the minimum difference between adjacent times
        for (int i = 0; i < totalSec; i++) {
            // Skip seconds that were not in the input array
            if (!seen[i]) {
                continue;
            }
            // If we have a previous time, calculate the difference
            if (prev != -1) {
                minDiff = min(minDiff, i - prev);
            } else {
                // This is the first time we've encountered
                first = i;
            }
            // Update prev and last to the current time
            prev = i;
            last = i;
        }

        // Calculate the wrap-around difference (e.g., between 23:59 and 00:01)
        int wrap = first + totalSec - last;
        minDiff = min(minDiff, wrap);

        return minDiff;
    }
};

/*
*
* Dry Run
*
* Input: arr[] = ["00:00:01", "23:59:59", "00:00:05"]
*
* 1. `toSeconds("00:00:01")` -> 1. `seen[1]` = true.
* 2. `toSeconds("23:59:59")` -> 86399. `seen[86399]` = true.
* 3. `toSeconds("00:00:05")` -> 5. `seen[5]` = true.
*
* 4. Initialize `minDiff = INT_MAX`, `first = -1`, `last = -1`, `prev = -1`.
*
* 5. Loop through `seen` array:
* - i = 1: `seen[1]` is true. `prev` is -1. Set `first = 1`, `prev = 1`, `last = 1`.
* - i = 5: `seen[5]` is true. `prev` is 1. `minDiff = min(INT_MAX, 5 - 1) = 4`. `prev = 5`, `last = 5`.
* - i = 86399: `seen[86399]` is true. `prev` is 5. `minDiff = min(4, 86399 - 5) = 4`. `prev = 86399`, `last = 86399`.
*
* 6. Calculate wrap-around difference:
* - `wrap = first + totalSec - last`
* - `wrap = 1 + 86400 - 86399 = 2`.
*
* 7. Final `minDiff = min(minDiff, wrap) = min(4, 2) = 2`.
*
* Output: 2
*
*/
```

---

### Java Solution

```java
// Intuition: The problem asks for the minimum time difference. Since the times can wrap around midnight, a linear scan won't work directly.
// We can convert all time points to a single unit (seconds) and place them on a timeline of a single day. The minimum difference will be the smallest gap between any two adjacent time points on this timeline.
//
// Approach:
// 1. Create a boolean array `seen` of size 86400 (for every second in a 24-hour day).
// 2. Iterate through the input `arr`. Convert each "HH:MM:SS" string to total seconds.
// 3. Mark the corresponding index in the `seen` array as `true`. If a time is already seen, it's a duplicate, and the difference is 0, so we can return immediately.
// 4. Iterate through the `seen` array to find the minimum difference between consecutive `true` values.
// 5. Keep track of the `first` and `last` seen seconds to calculate the wrap-around difference (e.g., between 23:59 and 00:01).
// 6. The final answer is the minimum of all adjacent differences and the wrap-around difference.
//
// Time Complexity: O(N + S), where N is the number of time strings and S is the total seconds in a day (86400). Since S is a constant, this is effectively O(N) because if N > S, we are guaranteed a duplicate time and return early.
// Space Complexity: O(S), for the `seen` boolean array. Since S is a constant, this is O(1) space.

class Solution {
    // Helper function to convert "HH:MM:SS" to total seconds
    private static int toSeconds(String time) {
        int h = Integer.parseInt(time.substring(0, 2));
        int m = Integer.parseInt(time.substring(3, 5));
        int s = Integer.parseInt(time.substring(6, 8));
        return h * 3600 + m * 60 + s;
    }

    public static int minDifference(String[] arr) {
        // Total seconds in a day
        int totalSec = 24 * 3600;

        // Boolean array to mark seen seconds, size = 86400
        boolean[] seen = new boolean[totalSec];

        int n = arr.length;

        // Mark all seconds in the seen array, return 0 on duplicate
        for (int i = 0; i < n; i++) {
            int sec = toSeconds(arr[i]);
            // If we've seen this time before, the difference is 0
            if (seen[sec]) {
                return 0;
            }
            seen[sec] = true;
        }

        // Variables to track first, last, and previous times
        int first = -1;
        int last = -1;
        int prev = -1;
        int minDiff = Integer.MAX_VALUE;

        // Find the minimum difference between adjacent times
        for (int i = 0; i < totalSec; i++) {
            // Skip seconds that were not in the input array
            if (!seen[i]) {
                continue;
            }
            // If we have a previous time, calculate the difference
            if (prev != -1) {
                minDiff = Math.min(minDiff, i - prev);
            } else {
                // This is the first time we've encountered
                first = i;
            }
            // Update prev and last to the current time
            prev = i;
            last = i;
        }

        // Calculate the wrap-around difference (e.g., between 23:59 and 00:01)
        int wrap = first + totalSec - last;
        minDiff = Math.min(minDiff, wrap);

        return minDiff;
    }
}

/*
*
* Dry Run
*
* Input: arr[] = ["00:00:01", "23:59:59", "00:00:05"]
*
* 1. `toSeconds("00:00:01")` -> 1. `seen[1]` = true.
* 2. `toSeconds("23:59:59")` -> 86399. `seen[86399]` = true.
* 3. `toSeconds("00:00:05")` -> 5. `seen[5]` = true.
*
* 4. Initialize `minDiff = Integer.MAX_VALUE`, `first = -1`, `last = -1`, `prev = -1`.
*
* 5. Loop through `seen` array:
* - i = 1: `seen[1]` is true. `prev` is -1. Set `first = 1`, `prev = 1`, `last = 1`.
* - i = 5: `seen[5]` is true. `prev` is 1. `minDiff = min(MAX_VALUE, 5 - 1) = 4`. `prev = 5`, `last = 5`.
* - i = 86399: `seen[86399]` is true. `prev` is 5. `minDiff = min(4, 86399 - 5) = 4`. `prev = 86399`, `last = 86399`.
*
* 6. Calculate wrap-around difference:
* - `wrap = first + totalSec - last`
* - `wrap = 1 + 86400 - 86399 = 2`.
*
* 7. Final `minDiff = Math.min(minDiff, wrap) = Math.min(4, 2) = 2`.
*
* Output: 2
*
*/
```

---

## 🔑 Key Insights

- **Pigeonhole Principle**: The core of the optimized solution relies on this principle. There are `24 * 60 * 60 = 86400` unique seconds in a day. If the input array `arr` has more than 86400 elements, there must be at least one duplicate time, making the minimum difference `0`.
- **Constant Time/Space**: By converting times to seconds and using a fixed-size boolean array (`seen`), we transform the problem from comparing every pair of times (`O(N^2)`) or sorting (`O(N log N)`) to a linear scan. Since the size of the `seen` array is constant, the space complexity is `O(1)`, and the time complexity is dominated by the initial pass through the input `arr`, making it `O(N)`.
- **Wrap-Around Logic**: The most crucial part is handling the time difference across midnight. The difference between the last time of one day and the first time of the next is simply `(first_time + seconds_in_day) - last_time`.

---

## 🚀 Further Exploration

- [Minimum Time Difference (LeetCode)](https://leetcode.com/problems/minimum-time-difference/)
- [Clock angle problem](https://www.geeksforgeeks.org/calculate-angle-hour-hand-minute-hand/)
- [Find all triplets with zero sum](https://www.geeksforgeeks.org/problems/find-all-triplets-with-zero-sum/1)

---

## 📚 References

- **Original Problem:** [GeeksforGeeks | Difference Check](https://www.geeksforgeeks.org/problems/difference-check/1)

---

## 👨‍💻 Author

- [imniles18](https://github.com/imnilesh18)

---

## #️⃣ Tags

`array` `string` `hashing` `geeksforgeeks` `time-conversion`

---

## 📄 License

This project is licensed under the MIT License.

> **MIT License**
>
> Copyright (c) 2024
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> **Educational Use Reminder**: This repository is for educational purposes only. It is not intended for production use.
