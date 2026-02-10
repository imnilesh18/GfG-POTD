# 🍌 Koko Eating Bananas

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/koko-eating-bananas/1)
[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-FFB800?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/koko-eating-bananas/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-50.27%25-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/koko-eating-bananas/1)
[![Points](https://img.shields.io/badge/Points-4-green?style=for-the-badge)](https://www.geeksforgeeks.org/problems/koko-eating-bananas/1)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

---

### ⚠️ Educational Use Only:
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the **GeeksforGeeks** problem.

---

## 📝 Problem Statement

Koko is given an array `arr[]`, where each element represents a pile of bananas. She has exactly `k` hours to eat all the bananas.

Each hour, Koko can choose one pile and eat up to `s` bananas from it.
* If the pile has **at least** `s` bananas, she eats exactly `s` bananas.
* If the pile has **fewer** than `s` bananas, she eats the entire pile in that hour.

Koko can only eat from one pile per hour.

Your task is to find the **minimum** value of `s` (bananas per hour) such that Koko can finish all the piles within `k` hours.

---

## 💾 Examples

### Example 1

```java
Input: arr[] = [5, 10, 3], k = 4
Output: 5
Explanation: If Koko eats at the rate of 5 bananas per hour:
- First pile of 5 bananas will be finished in 1 hour.
- Second pile of 10 bananas will be finished in 2 hours.
- Third pile of 3 bananas will be finished in 1 hour.
Therefore, Koko can finish all piles of bananas in 1 + 2 + 1 = 4 hours.

```

### Example 2

```java
Input: arr[] = [5, 10, 15, 20], k = 7
Output: 10
Explanation: If Koko eats at the rate of 10 bananas per hour, it will take 6 hours to finish all the piles (which is <= 7).

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

Let's consider `arr[] = [3, 6, 7, 11]` and `k = 8`.
We need to find the minimum eating speed `s`.

* **Try Speed s = 3:**
* 3 bananas: `ceil(3/3)` = 1 hour
* 6 bananas: `ceil(6/3)` = 2 hours
* 7 bananas: `ceil(7/3)` = 3 hours (3 + 3 + 1)
* 11 bananas: `ceil(11/3)` = 4 hours (3 + 3 + 3 + 2)
* Total Time = 1 + 2 + 3 + 4 = **10 hours**.
* Since 10 > 8, speed 3 is **too slow**.


* **Try Speed s = 4:**
* 3 bananas: `ceil(3/4)` = 1 hour
* 6 bananas: `ceil(6/4)` = 2 hours (4 + 2)
* 7 bananas: `ceil(7/4)` = 2 hours (4 + 3)
* 11 bananas: `ceil(11/4)` = 3 hours (4 + 4 + 3)
* Total Time = 1 + 2 + 2 + 3 = **8 hours**.
* Since 8 <= 8, this speed works! Can we go slower? We already tried 3 and it failed. So, **4** is the answer.



</details>

---

## 🚧 Constraints

* `1 ≤ arr.size() ≤ k ≤ 10^6`
* `1 ≤ arr[i] ≤ 10^6`

---

## 💡 Solution Approaches

### 🚀 Approach: Binary Search on Answer

**Intuition:**
The problem asks for the *minimum* speed `s`.

* If Koko eats 1 banana/hour (minimum possible speed), it will take the maximum amount of time.
* If Koko eats `max(arr)` bananas/hour (maximum useful speed), she will finish each pile in exactly 1 hour.
* If a speed `x` works, any speed greater than `x` also works (monotonic property).

This "monotonicity" (Yes/No property) allows us to use **Binary Search** instead of checking every possible speed from 1 to `max(arr)`.

**Algorithm:**

1. **Define Range:** The search space for speed `s` is `[1, max(arr)]`.
2. **Binary Search:**
* Calculate `mid` (current eating speed).
* Calculate `requiredHours` to eat all piles at speed `mid`.
* For each pile, time taken = `ceil(pile / mid)`.


3. **Check Condition:**
* If `requiredHours <= k`: This speed is valid. Try to find a smaller valid speed by moving to the left half (`high = mid - 1`). Store `mid` as a potential answer.
* If `requiredHours > k`: This speed is too slow. Move to the right half (`low = mid + 1`) to increase speed.



---

### C++ Solution

```cpp
// Intuition: We use Binary Search on the range of eating speeds [1, max(arr)].
// Approach: For a given speed 'mid', calculate the total hours required. If hours <= k, try a smaller speed (left half); otherwise, increase speed (right half).
// Time Complexity: O(N * log(M)), where N is the array size and M is the maximum element in the array.
// Space Complexity: O(1)

class Solution {
public:
    // Function to check if Koko can finish all bananas at speed 'mid' within 'k' hours
    bool finish(vector<int>& arr, int mid, int k) {
        long long hours = 0; // Use long long to prevent integer overflow

        for (int i = 0; i < arr.size(); i++) {
            // Calculate hours for current pile: ceil(arr[i] / mid)
            // Equivalent to (arr[i] + mid - 1) / mid using integer division
            hours += (arr[i] / mid); 
            if (arr[i] % mid != 0) {
                hours++;
            }
        }

        return hours <= k;  // Return true if total hours fits in k
    }
    
    int kokoEat(vector<int>& arr, int k) {
        int low    = 1;
        int high   = *max_element(arr.begin(), arr.end()); // Max bananas in a pile
        int result = high; // Default to max possible speed

        while (low <= high) {
            int mid = low + (high - low) / 2;  // Current speed to test

            if (finish(arr, mid, k)) {
                result = mid;        // Found a valid speed, try simpler/smaller
                high   = mid - 1;
            } else {
                low = mid + 1;       // Too slow, need faster speed
            }
        }

        return result;  // Minimum speed found
    }
};

/*
 * Dry Run
 * Input: arr[] = [3, 6, 7, 11], k = 8
 * Range: low = 1, high = 11
 *
 * 1. mid = 6
 * Hours = ceil(3/6) + ceil(6/6) + ceil(7/6) + ceil(11/6) 
 * = 1 + 1 + 2 + 2 = 6 hours.
 * 6 <= 8 (True). Store result = 6. New high = 5.
 *
 * 2. mid = 3
 * Hours = ceil(3/3) + ceil(6/3) + ceil(7/3) + ceil(11/3)
 * = 1 + 2 + 3 + 4 = 10 hours.
 * 10 <= 8 (False). New low = 4.
 *
 * 3. mid = 4
 * Hours = ceil(3/4) + ceil(6/4) + ceil(7/4) + ceil(11/4)
 * = 1 + 2 + 2 + 3 = 8 hours.
 * 8 <= 8 (True). Store result = 4. New high = 3.
 *
 * Loop ends (low > high). Return 4.
 */

```

---

### Java Solution

```java
// Intuition: Apply Binary Search on the answer space (eating speeds).
// Approach: Iterate through speeds from 1 to max(arr) using binary search. Use a helper function to validate if a specific speed allows finishing within k hours.
// Time Complexity: O(N * log(M)), where N is array length and M is the maximum pile size.
// Space Complexity: O(1)

class Solution {
    // Helper function to check if Koko can finish all bananas at speed 'mid' within 'k' hours
    private boolean canFinish(int[] arr, int mid, int k) {
        int hours = 0;

        for (int bananas : arr) {
            hours += bananas / mid;
            if (bananas % mid != 0) {
                hours++; // Add extra hour if there's a remainder
            }
        }

        return hours <= k;
    }

    public int kokoEat(int[] arr, int k) {
        int low  = 1;
        int high = Integer.MIN_VALUE;

        // Find the maximum pile size to set the upper bound
        for (int bananas : arr) {
            high = Math.max(high, bananas);
        }

        int result = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canFinish(arr, mid, k)) {
                result = mid;       // Valid speed, try to minimize it
                high   = mid - 1;
            } else {
                low = mid + 1;      // Invalid speed, increase it
            }
        }

        return result;
    }
}

/*
 * Dry Run
 * Input: arr[] = [3, 6, 7, 11], k = 8
 * Max Element = 11. Range [1, 11]
 *
 * 1. mid = 6 -> Time = 6 hrs (<= 8). Valid. Result = 6, High = 5.
 * 2. mid = 3 -> Time = 10 hrs (> 8). Invalid. Low = 4.
 * 3. mid = 4 -> Time = 8 hrs (<= 8). Valid. Result = 4, High = 3.
 *
 * Low (4) > High (3), Break. Return 4.
 */

```

---

## 🔑 Key Insights

1. **Binary Search on Answer:** This is a classic example of "Binary Search on Answer". Whenever the answer lies in a specific range (here, speed) and the condition (can finish in `k` hours) is monotonic (if speed `x` works, `x+1` definitely works), Binary Search is the most efficient approach.
2. **Range Definition:**
* **Lower Bound:** 1 (Minimum assumption).
* **Upper Bound:** The maximum element in the array. Eating faster than the largest pile size doesn't reduce the hours for that pile below 1, so going higher isn't necessary.


3. **Calculation of Hours:**
* The time to eat a pile of size `P` at speed `S` is `ceil(P / S)`.
* In integer arithmetic, this is commonly written as `(P + S - 1) / S` or `P / S + (P % S != 0)`.



---

## 🔍 Further Exploration

Similar problems on GeeksforGeeks and LeetCode to practice Binary Search on Answer:

1. **Capacity To Ship Packages Within D Days**
2. **Minimize Max Distance to Gas Station**
3. **Split Array Largest Sum**
4. **Minimum Number of Days to Make m Bouquets**

---

## 🔗 References

* [GFG Problem Link](https://www.geeksforgeeks.org/problems/koko-eating-bananas/1)
* [Binary Search Visualization](https://www.cs.usfca.edu/~galles/visualization/Search.html)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

</div>

> **Note:** This repository consists of coding problem solutions and is intended for educational purposes.