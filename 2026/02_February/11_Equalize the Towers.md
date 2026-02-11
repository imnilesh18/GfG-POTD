# ⚖️ Equalize the Towers

<div align="center">

![GfG](https://img.shields.io/badge/GfG-Medium-orange?style=for-the-badge&logo=geeksforgeeks)
![Accuracy](https://img.shields.io/badge/Accuracy-52.18%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)

</div>

<p align="center">
  <b>⚠️ Educational Use Only:</b> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.
</p>

---

## 📝 Problem Statement

You are given an array `heights[]` representing the heights of towers and another array `cost[]` where each element represents the cost of modifying the height of respective tower.

The goal is to make all towers of same height by either adding or removing blocks from each tower.
Modifying the height of tower 'i' by 1 unit (add or remove) costs `cost[i]`.

Return the **minimum** cost to equalize the heights of all the towers.

---

## 💾 Examples

<details>
<summary><b>📖 Example Breakdown</b></summary>

**Input:** `heights[] = [1, 2, 3]`, `cost[] = [10, 100, 1000]`

Let's calculate the cost for different target heights:

1.  **Target Height = 1:**
    * Tower 1 (1 -> 1): 0 cost
    * Tower 2 (2 -> 1): `|2-1| * 100 = 100`
    * Tower 3 (3 -> 1): `|3-1| * 1000 = 2000`
    * Total: `2100`

2.  **Target Height = 2:**
    * Tower 1 (1 -> 2): `|1-2| * 10 = 10`
    * Tower 2 (2 -> 2): 0 cost
    * Tower 3 (3 -> 2): `|3-2| * 1000 = 1000`
    * Total: `1010`

3.  **Target Height = 3:**
    * Tower 1 (1 -> 3): `|1-3| * 10 = 20`
    * Tower 2 (2 -> 3): `|2-3| * 100 = 100`
    * Tower 3 (3 -> 3): 0 cost
    * Total: `120` ✅ (Minimum)

**Output:** `120`
</details>

```cpp
Input: heights[] = [1, 2, 3], cost[] = [10, 100, 1000]
Output: 120

```

```cpp
Input: heights[] = [7, 1, 5], cost[] = [1, 1, 1]
Output: 6
Explanation: The minimum cost to equalize the towers is 6, achieved by setting all towers to height 5.

```

---

## 🚧 Constraints

* `1 ≤ heights.size() = cost.size() ≤ 10^5`
* `1 ≤ heights[i] ≤ 10^4`
* `1 ≤ cost[i] ≤ 10^3`

---

## 🛠️ Solution Approaches

### 1️⃣ Brute Force Approach (Naive)

**Intuition:**
The simplest way is to consider every single tower's height present in the array as the 'target height'. We calculate the total cost for each potential height and take the minimum cost as our answer.

**Algorithm:**

1. Iterate through each element of the `heights` array.
2. Consider the current element as the `target`.
3. In a nested loop, calculate the total cost to change all towers to this `target` height.
4. Update the minimum cost.

```cpp
// Intuition: Try making every tower equal to the height of each existing tower one by one and find the min cost.
// Approach: Nested loops to calculate cost for every candidate height.
// Time Complexity: O(N^2) because of nested loops over the array of size N.
// Space Complexity: O(1) as we use only constant extra space.

class Solution {
public:
    int minCost(vector<int>& heights, vector<int>& cost) {
        int n = heights.size();

        long long result = LLONG_MAX;  // will hold the minimum cost found

        // Try each tower's height as the target height
        for (int i = 0; i < n; i++) {
            long long total = 0;  // cost to make all towers height = heights[i]

            // Calculate cost to equalize every tower to heights[i]
            for (int j = 0; j < n; j++) {
                total += abs(heights[j] - heights[i]) * cost[j];
            }

            result = min(result, total);  // update minimum cost if this is lower
        }

        return (int)result;  // cast back to int for GfG signature
    }
};

/*
 * Dry Run on heights = [1,2,3], cost = [10,100,1000]
 *
 * i = 0, target = heights[0] = 1
 * total = |1-1|*10 + |2-1|*100 + |3-1|*1000
 * = 0 + 100 + 2000 = 2100
 * result = min(LLONG_MAX,2100) = 2100
 *
 * i = 1, target = heights[1] = 2
 * total = |1-2|*10 + |2-2|*100 + |3-2|*1000
 * = 10 + 0 + 1000 = 1010
 * result = min(2100,1010) = 1010
 *
 * i = 2, target = heights[2] = 3
 * total = |1-3|*10 + |2-3|*100 + |3-3|*1000
 * = 20 + 100 + 0 = 120
 * result = min(1010,120) = 120
 *
 * Final result returned = 120
 */

```

```java
// Intuition: Check every height present in the array as a potential target height.
// Approach: Calculate the total cost for converting all towers to each height present in the array.
// Time Complexity: O(N^2) due to nested iteration.
// Space Complexity: O(1) constant extra space.

class Solution {
    public int minCost(int[] heights, int[] cost) {
        int n = heights.length;

        long result = Long.MAX_VALUE;  // will hold the minimum cost found

        // Try each tower's height as the target height
        for (int i = 0; i < n; i++) {
            long total = 0;  // cost to make all towers height = heights[i]

            // Calculate cost to equalize every tower to heights[i]
            for (int j = 0; j < n; j++) {
                total += Math.abs(heights[j] - heights[i]) * (long) cost[j];
            }

            result = Math.min(result, total);  // update minimum cost if this is lower
        }

        return (int) result;  // cast back to int as expected
    }
}

/*
 * Dry Run on heights = [1,2,3], cost = [10,100,1000]
 * i = 0, target = heights[0] = 1, total = 2100
 * i = 1, target = heights[1] = 2, total = 1010
 * i = 2, target = heights[2] = 3, total = 120
 * result = 120
 */

```

---

### 2️⃣ Optimized Approach (Binary Search on Answer)

**Intuition:**
If we plot a graph between 'target height' and 'total cost', we will find that it forms a **Convex Function** (U-shaped curve). This means the cost decreases first, reaches a minimum point, and then increases. We can efficiently find this minimum point (valley) using **Binary Search**.

**Algorithm:**

1. Define Search Space: `low = min(heights)` and `high = max(heights)`.
2. Calculate `mid` and compute `cost(mid)` and `cost(mid + 1)`.
3. If `cost(mid) < cost(mid + 1)`, it means the slope is increasing, so the minimum is at `mid` or to its left (`high = mid - 1`).
4. Otherwise, the slope is still decreasing, so the minimum is to the right (`low = mid + 1`).
5. Finally, calculate the final cost using the obtained `targetH`.

```cpp
// Intuition: The cost function is convex. We can use Binary Search to find the minimum point (valley).
// Approach: Binary Search on heights range. Compare cost(mid) and cost(mid+1) to decide direction.
// Time Complexity: O(N * log(maxH - minH)) where maxH is max height. Binary search runs log(Range) times, cost calc is O(N).
// Space Complexity: O(1) constant extra space.

class Solution {
public:

    // Helper function to compare cost at mid vs mid + 1
    bool check(vector<int>& heights, vector<int>& cost, int mid) {
        long long costMid    = 0;
        long long costMidP1 = 0;

        for (int i = 0; i < heights.size(); i++) {
            costMid    += (long long)abs(heights[i] - mid) * cost[i];
            costMidP1 += (long long)abs(heights[i] - (mid + 1)) * cost[i];
        }

        return costMid < costMidP1;  // true if mid gives smaller cost than mid+1 (move left/stay)
    }
    int minCost(vector<int>& heights, vector<int>& cost) {
        // Define search boundaries for binary search
        int low  = *min_element(heights.begin(), heights.end());
        int high = *max_element(heights.begin(), heights.end());

        int targetH = 0;  // best height found

        while (low <= high) {
            int mid = (low + high) / 2;

            // Move toward the side with lower cost
            if (check(heights, cost, mid)) {
                targetH = mid;
                high    = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // Calculate final cost using chosen target height
        long long result = 0;
        for (int i = 0; i < heights.size(); i++) {
            result += (long long)abs(heights[i] - targetH) * cost[i];
        }

        return (int)result;
    }
};

/*
 *
 * Dry Run
 * heights = [1,2,3], cost = [10,100,1000]
 *
 * low = 1, high = 3
 * mid = 2
 * costMid = |1-2|*10 + |2-2|*100 + |3-2|*1000 = 1010
 * costMidP1 = |1-3|*10 + |2-3|*100 + |3-3|*1000 = 120
 * costMid < costMidP1 (1010 < 120) -> false
 * low = mid + 1 = 3
 *
 * next iter: low=3, high=3, mid=3
 * check(3): costMid(120) < costMidP1(1230 for h=4) -> true
 * targetH = 3, high = 2
 *
 * loop ends (low > high)
 * Final targetH = 3
 * Final result calc with h=3 -> 120
 *
 */

```

```java
// Intuition: Use Binary Search to find the minimum of the convex cost function efficiently.
// Approach: Check slope at mid by comparing cost(mid) and cost(mid+1) to adjust search range.
// Time Complexity: O(N * log(maxH - minH)). Efficient for large N.
// Space Complexity: O(1).

class Solution {
    // Helper function to compare cost at mid vs mid + 1
    public boolean check(int[] heights, int[] cost, int mid) {
        long costMid    = 0;
        long costMidP1 = 0;

        for (int i = 0; i < heights.length; i++) {
            costMid    += (long)Math.abs(heights[i] - mid) * cost[i];
            costMidP1 += (long)Math.abs(heights[i] - (mid + 1)) * cost[i];
        }

        return costMid < costMidP1;  // true if mid gives smaller cost than mid+1 (move left)
    }
    public int minCost(int[] heights, int[] cost) {
        // Define search boundaries for binary search
        int low  = Arrays.stream(heights).min().getAsInt();
        int high = Arrays.stream(heights).max().getAsInt();

        int targetH = 0;  // best height found

        while (low <= high) {
            int mid = (low + high) / 2;

            // Move toward the side with lower cost
            if (check(heights, cost, mid)) {
                targetH = mid;
                high    = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // Calculate final cost using chosen target height
        long result = 0;
        for (int i = 0; i < heights.length; i++) {
            result += (long)Math.abs(heights[i] - targetH) * cost[i];
        }

        return (int)result;
    }
}

/*
 * Dry Run
 * low = 1, high = 3, mid = 2
 * cost(2) = 1010, cost(3) = 120
 * cost(2) < cost(3) is false.
 * low becomes 3.
 * Finally converges to height 3 with cost 120.
 */

```

---

## 💡 Key Insights

1. **Convex Cost Function:** If we plot `cost` against `target height`, the curve is always convex (U-shape). This is why we can use **Binary Search** or **Ternary Search** to find a local minimum.
2. **Range:** The answer will always lie between the minimum (`min`) and maximum (`max`) height of the input array.
3. **Comparison Strategy:** Comparing `f(mid)` and `f(mid+1)` is essentially checking the slope (derivative). If `f(mid+1)` is smaller, we are going down the slope (to the right), otherwise we are going up or are at the bottom (to the left).

---

## 🔍 Further Exploration

* **Ternary Search:** How can Ternary Search be used to solve this problem?
* **Median Logic:** If all costs were `1`, what would be the optimal height? (Hint: Median).
* **Weighted Median:** This problem is a form of finding the Weighted Median.

---

## 🔗 References

* [Original Problem on GeeksforGeeks](https://www.geeksforgeeks.org/problems/equalize-the-towers2804/1)
* [Binary Search on Answer](https://www.geeksforgeeks.org/binary-search/)

---

## 👤 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

</div>

<p align="center">
<b>⚠️ Educational Disclaimer:</b> This material is for educational purposes only. It is advised to understand the underlying concepts before copying the code.
</p>