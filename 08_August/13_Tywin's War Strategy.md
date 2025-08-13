# 🛡️ Tywin's War Strategy

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/tywins-war-strategy0527/1).

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-50.0%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)

</div>

---

## 🎯 Problem Statement

You are given an array `arr[]` of size `n`, where `arr[i]` represents the number of soldiers in the `i-th` troop. You are also given an integer `k`. A troop is considered **"lucky"** if its number of soldiers is a multiple of `k`.

Your task is to find the **minimum** total number of soldiers to add across all troops so that at least `⌈n / 2⌉` troops become lucky.

---

## 📖 Examples

### Example 1
**Input:**
```
arr = [5, 6, 3, 2, 1]
k = 2
```
**Output:**
```
1
```
<details>
<summary><strong>📖 Example Breakdown</strong></summary>

-   **Goal:** We need at least `⌈5 / 2⌉ = 3` lucky troops.
-   **Initial State:** The troop with `6` soldiers is lucky (multiple of 2). We have `1` lucky troop.
-   **Requirement:** We need `3 - 1 = 2` more lucky troops.
-   **Costs to make troops lucky:**
    -   Troop `5`: Needs `2 - (5 % 2) = 1` soldier to become `6`.
    -   Troop `3`: Needs `2 - (3 % 2) = 1` soldier to become `4`.
    -   Troop `2`: Is already lucky (multiple of 2). Wait, the initial state had `6` and `2`, so 2 lucky troops. We only need one more.
    -   Troop `1`: Needs `2 - (1 % 2) = 1` soldier to become `2`.
-   **Analysis Correction**:
    -   Initially lucky troops: `6` and `2` (2 troops).
    -   We need `3` lucky troops, so we need `1` more.
    -   The costs to make the remaining troops lucky are:
        -   `5` -> cost `1`
        -   `3` -> cost `1`
        -   `1` -> cost `1`
-   **Optimal Choice:** To minimize the cost, we pick the cheapest option. All options cost `1`. We only need one more lucky troop. So we pick any one of them.
-   **Action:** Add `1` soldier to the troop with `1` soldier. The array becomes `[5, 6, 3, 2, 2]`.
-   **Result:** The lucky troops are now `6`, `2`, and `2` (3 troops), which meets the goal. The total soldiers added is `1`.

</details>

### Example 2
**Input:**
```
arr = [3, 5, 6, 7, 9, 10]
k = 4
```
**Output:**
```
4
```
**Explanation:** We need at least `⌈6 / 2⌉ = 3` lucky troops. No troop is currently divisible by 4.
- Add `1` soldier for troop `3` → `4`.
- Add `2` soldiers for troop `6` → `8`.
- Add `1` soldier for troop `7` → `8`.
New array: `[4, 5, 8, 8, 9, 10]` with 3 lucky troops (`4`, `8`, `8`).
Total soldiers added = `1 + 2 + 1 = 4`.

---

## ⛓️ Constraints

-   `1 ≤ arr.size() ≤ 10^5`
-   `1 ≤ k ≤ 10^5`
-   `1 ≤ arr[i] ≤ 10^5`

---

## 💡 Solution Approaches

### Optimized Greedy Approach

The core idea is to be greedy. To minimize the total soldiers added, we should always choose to modify the troops that require the fewest soldiers to become "lucky."

We can calculate the "cost" (soldiers to add) for each troop to become a multiple of `k`. By using a **min-priority queue**, we can efficiently find and sum the smallest costs needed to meet the `⌈n / 2⌉` requirement.

#### C++ Solution
```cpp
// Intuition: To minimize the total soldiers added, we should prioritize making troops lucky that require the fewest additional soldiers. This suggests a greedy approach.
// Approach:
// 1. Calculate the target number of lucky troops needed: ceil(n/2).
// 2. Iterate through the array. Count troops that are already lucky.
// 3. For troops that are not lucky, calculate the cost (soldiers to add) to make them lucky: `k - (num % k)`.
// 4. Store these costs in a min-priority queue to always have the smallest costs available.
// 5. If the initial count of lucky troops is sufficient, return 0.
// 6. Otherwise, determine how many more troops we need to make lucky (`req = need - lucky`).
// 7. Greedily extract the `req` smallest costs from the priority queue and sum them up. This sum is the minimal total soldiers.
// Time Complexity: O(N log N), where N is the size of the array. The loop is O(N), and each push/pop operation on the priority queue is O(log N).
// Space Complexity: O(N) in the worst case, if no troops are initially lucky, the priority queue will store N costs.

class Solution {
  public:
    int minSoldiers(vector<int>& arr, int k) {
        int n = arr.size();
        int need = (n + 1) / 2; // Calculate required lucky troops (ceil division)
        int lucky = 0;

        // Min-heap for storing costs to make a troop lucky
        priority_queue<int, vector<int>, greater<int>> pq;

        // Iterate through each troop
        for (int num : arr) {
            if (num % k == 0) {
                // Troop is already lucky
                ++lucky;
            } else {
                // Calculate cost and push to min-heap
                pq.push(k - (num % k));
            }
        }

        // If already enough lucky troops, cost is 0
        if (lucky >= need) return 0;

        int total = 0;
        int req = need - lucky; // Number of additional lucky troops required

        // Take smallest `req` costs from the heap
        for (int i = 0; i < req && !pq.empty(); ++i) {
            total += pq.top(); // Add the cheapest cost
            pq.pop();
        }

        return total;
    }
};

/*
 *
 * Dry Run
 * Input: arr = [5, 6, 3, 2, 1], k = 2
 *
 * n = 5
 * need = (5 + 1) / 2 = 3
 * lucky = 0
 * pq = min-priority-queue
 *
 * Loop:
 * num = 5: 5 % 2 != 0. Cost = 2 - (5 % 2) = 1. pq.push(1). pq = {1}
 * num = 6: 6 % 2 == 0. lucky = 1.
 * num = 3: 3 % 2 != 0. Cost = 2 - (3 % 2) = 1. pq.push(1). pq = {1, 1}
 * num = 2: 2 % 2 == 0. lucky = 2.
 * num = 1: 1 % 2 != 0. Cost = 2 - (1 % 2) = 1. pq.push(1). pq = {1, 1, 1}
 *
 * After loop: lucky = 2, pq = {1, 1, 1}
 *
 * Check: lucky (2) < need (3). Condition is true.
 * req = need - lucky = 3 - 2 = 1. We need 1 more lucky troop.
 * total = 0.
 *
 * Loop for summing costs (i=0 to req-1=0):
 * i = 0: total += pq.top() (which is 1). total = 1. pq.pop().
 *
 * Return total = 1.
 *
 */
```

#### Java Solution
```java
// Intuition: The problem asks for the minimum total soldiers, which is a classic optimization problem. A greedy strategy works best: always pick the "cheapest" troop to upgrade.
// Approach:
// 1. Determine the target number of lucky troops, `need = ceil(n/2)`.
// 2. Traverse the input array `arr`.
// 3. If a troop `num` is already a multiple of `k`, increment the `lucky` counter.
// 4. If not, calculate the soldiers needed (`k - (num % k)`) and add this cost to a min-heap (PriorityQueue).
// 5. If we already have enough `lucky` troops, the answer is 0.
// 6. Otherwise, we need `req = need - lucky` more lucky troops.
// 7. Poll the `req` smallest costs from the min-heap and add them to a `total`.
// 8. Return the `total`.
// Time Complexity: O(N log N). Iterating through N elements and performing heap operations (O(log N)) for each.
// Space Complexity: O(N), for the PriorityQueue which can hold up to N elements.

class Solution {
    public int minSoldiers(int[] arr, int k) {
        int n = arr.length;
        int need = (n + 1) / 2; // Required number of lucky troops (ceiling)
        int lucky = 0;

        // Min-heap for storing costs to make a troop lucky
        PriorityQueue<Integer> pq = new PriorityQueue<>();

        // Process each troop's soldier count
        for (int num : arr) {
            if (num % k == 0) {
                // This troop is already lucky
                ++lucky;
            } else {
                // Calculate the cost to make it lucky and add to the min-heap
                pq.add(k - (num % k));
            }
        }

        // If we already have enough lucky troops, no cost is incurred
        if (lucky >= need) return 0;

        int total = 0;
        int req = need - lucky; // How many more troops we must make lucky

        // Take the smallest `req` costs from the heap
        for (int i = 0; i < req && !pq.isEmpty(); ++i) {
            total += pq.poll(); // Add the smallest available cost
        }

        return total;
    }
}

/*
 *
 * Dry Run
 * Input: arr = [3, 5, 6, 7, 9, 10], k = 4
 *
 * n = 6
 * need = (6 + 1) / 2 = 3
 * lucky = 0
 * pq = new PriorityQueue<>()
 *
 * Loop:
 * num = 3: 3 % 4 != 0. Cost = 4 - 3 = 1. pq.add(1). pq = {1}
 * num = 5: 5 % 4 != 0. Cost = 4 - 1 = 3. pq.add(3). pq = {1, 3}
 * num = 6: 6 % 4 != 0. Cost = 4 - 2 = 2. pq.add(2). pq = {1, 2, 3}
 * num = 7: 7 % 4 != 0. Cost = 4 - 3 = 1. pq.add(1). pq = {1, 1, 2, 3}
 * num = 9: 9 % 4 != 0. Cost = 4 - 1 = 3. pq.add(3). pq = {1, 1, 2, 3, 3}
 * num = 10: 10 % 4 != 0. Cost = 4 - 2 = 2. pq.add(2). pq = {1, 1, 2, 2, 3, 3}
 *
 * After loop: lucky = 0, pq is sorted {1, 1, 2, 2, 3, 3}
 *
 * Check: lucky (0) < need (3).
 * req = need - lucky = 3 - 0 = 3. We need 3 lucky troops.
 * total = 0.
 *
 * Loop for summing costs (i=0 to req-1=2):
 * i = 0: total += pq.poll() (1). total = 1.
 * i = 1: total += pq.poll() (1). total = 2.
 * i = 2: total += pq.poll() (2). total = 4.
 *
 * Return total = 4.
 *
 */
```

---

## 🔑 Key Insights

-   **Greedy Choice:** The problem's structure allows for a greedy approach. By always picking the smallest "cost" (minimum soldiers to add), we ensure the overall sum is minimized. A proof by exchange would show that picking a more expensive option would never lead to a better result.
-   **Data Structure:** A min-priority queue (or min-heap) is the perfect data structure for this greedy strategy. It allows `O(log N)` insertion and `O(log N)` retrieval of the minimum element, which is far more efficient than sorting the costs repeatedly.

---

## 🚀 Further Exploration

-   [Minimum Cost of ropes](https://www.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1): Another classic problem solved efficiently with a priority queue.
-   [Fractional Knapsack](https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1): A famous greedy algorithm problem that helps solidify the greedy choice property.
-   Explore other problems involving modulo arithmetic and optimization on arrays.

---

## 📚 References

-   **Original Problem:** [GeeksforGeeks | Tywin's War Strategy](https://www.geeksforgeeks.org/problems/tywins-war-strategy0527/1)
-   **Priority Queue (C++):** [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue)
-   **Priority Queue (Java):** [java.util.PriorityQueue](https://docs.oracle.com/javase/8/docs/api/java/util/PriorityQueue.html)

---

## 👨‍💻 Author

-   **Solutions & README By:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Array](https://img.shields.io/badge/Array-blue?style=for-the-badge)
![Greedy](https://img.shields.io/badge/Greedy-green?style=for-the-badge)
![Sorting](https://img.shields.io/badge/Sorting-purple?style=for-the-badge)
![Priority Queue](https://img.shields.io/badge/Priority_Queue-orange?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License.

<div align="center">
    <p><strong>Remember, this is for educational purposes. Always try to solve problems on your own first!</strong></p>
</div>