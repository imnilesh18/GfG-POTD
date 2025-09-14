# ⛽ Gas Station (Circular Tour)

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-Problem-green?logo=geeksforgeeks&style=for-the-badge)](https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1)
[![Difficulty](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)](https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1)
[![Accuracy](https://img.shields.io/badge/Accuracy-34.79%25-orange?style=for-the-badge)](https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1)
[![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)](https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes.
Solutions are provided for learning, practice, and reference only.
Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1).

## 1. Problem Statement

There are `n` gas stations along a **circular tour**. You are given two integer arrays `gas[]` and `cost[]`, where `gas[i]` is the amount of gas available at station `i` and `cost[i]` is the gas needed to travel from station `i` to station `(i+1)`. You have a car with an unlimited gas tank and start with an empty tank at some station. Your task is to return the **index** of the starting station if it is possible to travel once around the circular route in a clockwise direction without running out of gas at any station; otherwise, return `-1`.

**Note:** If a solution exists, it is guaranteed to be unique.

---

## 2. Examples

### Example 1

```
Input:
gas[] = [4, 5, 7, 4]
cost[] = [6, 6, 3, 5]

Output: 2
```

<details>
<summary><strong>📖 Example Breakdown</strong></summary>
<br>
Let's start at gas station at index 2.
<ol>
    <li>Fill up with 7 units of gas. Your tank = 0 + 7 = 7.</li>
    <li>Travel to station 3. Gas needed = 3. Gas remaining = 7 - 3 = 4.</li>
    <li>At station 3, fill up with 4 units. Tank = 4 + 4 = 8.</li>
    <li>Travel to station 0. Gas needed = 5. Gas remaining = 8 - 5 = 3.</li>
    <li>At station 0, fill up with 4 units. Tank = 3 + 4 = 7.</li>
    <li>Travel to station 1. Gas needed = 6. Gas remaining = 7 - 6 = 1.</li>
    <li>At station 1, fill up with 5 units. Tank = 1 + 5 = 6.</li>
    <li>Travel back to station 2. Gas needed = 6. Gas remaining = 6 - 6 = 0.</li>
</ol>
Since we successfully returned to station 2, the answer is 2.
</details>

### Example 2

```
Input:
gas[] = [3, 9]
cost[] = [7, 6]

Output: -1

Explanation:
There is no gas station to start with such that you can complete the tour.
- Start at 0: Tank = 3. Cost to 1 = 7. Fails (3 < 7).
- Start at 1: Tank = 9. Cost to 0 = 6. Tank = 9-6+3 = 6. Cost to 1 = 7. Fails (6 < 7).
```

---

## 3. Constraints

<div style="background-color: #333; color: #fff; padding: 1rem; border-radius: 8px;">

- `1 ≤ n ≤ 10^6`
- `1 ≤ gas[i], cost[i] ≤ 10^3`

</div>

---

## 4. Solution Approaches

### 🔹 Optimized Greedy Approach

The problem can be solved efficiently using a greedy approach in a single pass (after one preliminary pass to check for possibility).

```cpp

// Intuition: The core idea is to first check if a solution is even possible by comparing total gas available versus total cost required. If totalGas < totalCost, no solution exists.
// Approach: If a solution does exist, we can find it in a single pass. We maintain a running 'currentFuelBalance' (gas[i] - cost[i]). If this balance ever drops below zero, it means we cannot reach station 'i+1' from the current 'startingStationIndex'. More importantly, we also can't start from ANY station between the old start and 'i', because they would all result in an even lower balance by the time they reached 'i'. Therefore, if our balance goes negative at 'i', the only possible new starting candidate is 'i+1'. We reset the balance to 0 and continue. Since a unique solution is guaranteed to exist (if totalGas >= totalCost), this single pass will find it.
// Time Complexity: O(n), as we iterate through the 'gas' and 'cost' arrays twice (once for the total sum check, and once for the main simulation). This simplifies to O(n).
// Space Complexity: O(1), as we only use only a constant amount of extra variables to store totals and the current state.
class Solution {
public:
    int startStation(std::vector<int>& gas, std::vector<int>& cost) {
        int n = gas.size();

        // Calculate total gas available and total cost required for the circuit.
        // We use long long to prevent potential integer overflow during summation, although with given constraints int is fine.
        long long totalGasAvailable = 0;
        long long totalCostRequired = 0;
        for(int g : gas) totalGasAvailable += g;
        for(int c : cost) totalCostRequired += c;

        // If overall available gas is less than the cost, the journey is impossible.
        if (totalGasAvailable < totalCostRequired) {
            return -1;
        }

        int startingStationIndex = 0;   // Candidate index for starting the journey.
        int currentFuelBalance   = 0;   // Current fuel balance during the journey.

        for (int i = 0; i < n; i++) {
            // Calculate the net gain/loss at this station
            int netFuel = gas[i] - cost[i];

            // Update the current fuel balance by adding the net fuel at station i.
            currentFuelBalance += netFuel;

            // If the balance becomes negative, it means we ran out of gas trying to reach i+1
            // from the current 'startingStationIndex'.
            if (currentFuelBalance < 0) {
                // This means 'startingStationIndex' (and any station between it and i) is invalid.
                // Our new *potential* start must be the *next* station (i + 1).
                startingStationIndex = i + 1;
                // We reset the fuel balance, as we are "starting over" from this new candidate.
                currentFuelBalance   = 0;
            }
        }

        // Because we already confirmed a solution exists (totalGas >= totalCost),
        // the 'startingStationIndex' we are left with is guaranteed to be the correct one.
        return startingStationIndex;
    }
};

/*
 * Dry Run Visualization:
 *
 * Input:
 * gas  = [4,  5,  7,  4]
 * cost = [6,  6,  3,  5]
 *
 * *---------------------------------------------------------------*
 * * Step 1: Compute Totals                                        *
 * *---------------------------------------------------------------*
 * * totalGasAvailable = 4 + 5 + 7 + 4 = 20                      *
 * * totalCostRequired = 6 + 6 + 3 + 5 = 20                      *
 * * Since 20 >= 20, a solution exists. Proceed.                 *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 2: Initialize Variables                                  *
 * *---------------------------------------------------------------*
 * * startingStationIndex = 0                                    *
 * * currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 3: Iterate Over Each Station                             *
 * *---------------------------------------------------------------*
 *
 * * Iteration 1: i = 0                                            *
 * *---------------------------------------------------------------*
 * * [ Index:  0    1    2    3 ]                                  *
 * * [  gas:  [4,   5,   7,   4] ]                                  *
 * * [ cost:  [6,   6,   3,   5] ]                                  *
 * * ^                                                    *
 * * |                                                    *
 * * i = 0                                                 *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * * currentFuelBalance += gas[0] - cost[0]                      *
 * * = 0 + (4 - 6) = -2                       *
 * * Since currentFuelBalance (-2) < 0, reset the candidate:       *
 * * startingStationIndex = 0 + 1 = 1                            *
 * * currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * * Iteration 2: i = 1                                            *
 * *---------------------------------------------------------------*
 * * [ Index:  0    1    2    3 ]                                  *
 * * [  gas:  [4,   5,   7,   4] ]                                  *
 * * [ cost:  [6,   6,   3,   5] ]                                  *
 * * ^                                               *
 * * |                                               *
 * * i = 1                                            *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * * currentFuelBalance += gas[1] - cost[1]                      *
 * * = 0 + (5 - 6) = -1                       *
 * * Since currentFuelBalance (-1) < 0, reset the candidate:       *
 * * startingStationIndex = 1 + 1 = 2                            *
 * * currentFuelBalance   = 0                                    *
 * *---------------------------------------------------------------*
 *
 * * Iteration 3: i = 2                                            *
 * *---------------------------------------------------------------*
 * * [ Index:  0    1    2    3 ]                                  *
 * * [  gas:  [4,   5,   7,   4] ]                                  *
 * * [ cost:  [6,   6,   3,   5] ]                                  *
 * * ^                                          *
 * * |                                          *
 * * i = 2                                       *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * * currentFuelBalance += gas[2] - cost[2]                      *
 * * = 0 + (7 - 3) = 4                        *
 * * Since currentFuelBalance (4) >= 0, no reset needed.           *
 * * startingStationIndex remains 2                               *
 * *---------------------------------------------------------------*
 *
 * * Iteration 4: i = 3                                            *
 * *---------------------------------------------------------------*
 * * [ Index:  0    1    2    3 ]                                  *
 * * [  gas:  [4,   5,   7,   4] ]                                  *
 * * [ cost:  [6,   6,   3,   5] ]                                  *
 * * ^                                     *
 * * |                                     *
 * * i = 3                                  *
 * *---------------------------------------------------------------*
 * * Calculation:                                                  *
 * * currentFuelBalance += gas[3] - cost[3]                      *
 * * = 4 + (4 - 5) = 3                        *
 * * currentFuelBalance remains positive (3), no reset.            *
 * * startingStationIndex remains 2                               *
 * *---------------------------------------------------------------*
 *
 * *---------------------------------------------------------------*
 * * Step 4: End of Iteration                                      *
 * *---------------------------------------------------------------*
 * * Final Candidate: startingStationIndex = 2                     *
 * * Return: 2                                                     *
 * *---------------------------------------------------------------*
 */
```

---

## 5. Key Insights

The problem has two key greedy insights:

1.  **Possibility Check**: A circular tour is only possible if the total amount of gas available in the entire circuit is greater than or equal to the total cost to travel the entire circuit. If `sum(gas) < sum(cost)`, no starting point can ever succeed, so we return -1 immediately.
2.  **Start Point Selection (Kadane's-like logic)**: If a solution _does_ exist (from step 1), we can find it in one pass.
    - Assume a starting point `start = 0`. Maintain a running `tank` (or `currentFuelBalance`).
    - Iterate from `i = 0` to `n-1`. For each station, add `gas[i] - cost[i]` to the `tank`.
    - If at _any_ point `i` the `tank` becomes negative, it means two things:
      - Our assumed `start` is invalid.
      - **Crucially**, _any_ station between `start` and `i` (inclusive) is also an invalid starting point. Why? Because starting at any of those points would mean we arrive at station `i` with an even _lower_ (or at best, equal) tank balance than we did when starting from `start`, and we would still fail.
    - Therefore, if our `tank` goes negative at index `i`, the only possible valid starting point must be _after_ `i`. So, we set `start = i + 1` and reset our `tank = 0`.
    - Since the problem guarantees a unique solution exists (if one exists at all), the `start` index we are left with after the loop finishes must be the correct one.

---

## 6. Further Exploration

- **Related Problem**: [Maximum Subarray Sum (Kadane's Algorithm)](https://www.geeksforgeeks.org/problems/kadanes-algorithm-1587115620/1)
  - The logic of maintaining a running sum and resetting it to zero when it falls below a threshold is the core idea behind Kadane's Algorithm, which is very similar to the "Start Point Selection" logic used here.

---

## 7. References

- **Original Problem**: [https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1](https://www.geeksforgeeks.org/problems/circular-tour-1587115620/1)
- **Related LeetCode Problem**: [134. Gas Station](https://leetcode.com/problems/gas-station/)

---

## 8. Author

- **GitHub**: [imnilesh18](https://github.com/imnilesh18)

---

## 9. Tags

- `greedy`
- `array`
- `circular-tour`
- `kadanes-algorithm`
- `geeksforgeeks`
- `cpp`

---

## 10. License

[![License](https://img.shields.io/badge/License-MIT-green.svg?style=flat)](https://opensource.org/licenses/MIT)

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file (if available) or the badge link for details.

**Educational Use Disclaimer**: All content, including problem statements, solutions, and examples, is provided for educational purposes only. This repository is not affiliated with GeeksforGeeks or any other official coding platform. All problem rights and content belong to their respective owners.
