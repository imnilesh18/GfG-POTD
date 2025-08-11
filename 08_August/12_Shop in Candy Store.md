# 🍭 Shop in Candy Store

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](httpshttps://www.geeksforgeeks.org/problems/shop-in-candy-store1145/1).

<div align="center">

[![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)](https://www.geeksforgeeks.org/problems/shop-in-candy-store1145/1)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-45.43%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)

</div>

<div align="center">
  <img src="https://media.geeksforgeeks.org/wp-content/uploads/20250722162220605938/Minimum-and-Maximum-Candy-Cost-3.webp" alt="Shop in Candy Store Illustration" width="550"/>
</div>

---

## 📜 Problem Statement

In a candy store, there are different types of candies available and `prices[i]` represents the price of the *i*th type of candy. You are now provided with an attractive offer.

For every candy you buy from the store, you can get up to **k** other different candies for free.

Your task is to find the **minimum** and **maximum** amount of money you need to spend to buy all the candies.

**Note**: In both cases (for minimum and maximum cost), you must take the maximum number of free candies possible during each purchase.

---

## 📖 Examples

### Example 1

```
Input:
prices[] = [3, 2, 1, 4]
k = 2

Output:
[3, 7]
```

<details>
<summary><strong>📝 Example Breakdown</strong></summary>

> **Sorted Prices:** `[1, 2, 3, 4]`
>
> **Minimum Cost Strategy:**
>
> 1.  **Buy the cheapest candy**: Buy the candy costing `1`.
> 2.  **Get free candies**: Get `k=2` of the most expensive candies for free. These are the ones costing `4` and `3`.
> 3.  **Remaining candy**: The only candy left to buy is the one costing `2`.
> 4.  **Total Minimum Cost**: `1 + 2 = 3`.
>
> **Maximum Cost Strategy:**
>
> 1.  **Buy the most expensive candy**: Buy the candy costing `4`.
> 2.  **Get free candies**: Get `k=2` of the cheapest candies for free. These are the ones costing `1` and `2`.
> 3.  **Remaining candy**: The only candy left to buy is the one costing `3`.
> 4.  **Total Maximum Cost**: `4 + 3 = 7`.

</details>

### Example 2

```
Input:
prices[] = [3, 2, 1, 4, 5]
k = 4

Output:
[1, 5]
```

> **Explanation:**
>
> - **Minimum Cost:** Buy the candy with cost `1`. You can get up to `k=4` other candies for free, so you get all remaining four candies for free. Total cost: `1`.
> - **Maximum Cost:** Buy the candy with cost `5`. You can get up to `k=4` other candies for free, so you get all remaining four candies for free. Total cost: `5`.

---

## ⛓️ Constraints

> ```
> 1 ≤ prices.size() ≤ 10^5
> 0 ≤ k ≤ prices.size()
> 1 ≤ prices[i] ≤ 10^4
> ```

---

## 💡 Solution Approach: Greedy with Sorting

The core idea is to use a **greedy strategy**. To find the minimum cost, we should always buy the cheapest available candies and use the offer to get the most expensive ones for free. Conversely, for the maximum cost, we should buy the most expensive candies and get the cheapest ones for free. Sorting the array first makes this greedy selection straightforward and efficient.

---

## 💻 Code Implementations

### C++ Solution

```cpp
// Intuition: To minimize cost, buy the cheapest candies and get the most expensive for free.
// To maximize cost, buy the most expensive candies and get the cheapest for free.
// Approach:
// 1. Sort the prices array in non-decreasing order.
// 2. For minimum cost:
//    - Initialize a pointer `i` to 0 and `n` to the total number of candies.
//    - Iterate while `i < n`. In each step, buy the candy at `prices[i]`, add it to `minCost`.
//    - Then, get `k` free candies from the expensive end by decrementing `n` by `k`.
// 3. For maximum cost:
//    - Initialize a pointer `i` to `prices.size() - 1` and `j` to `0`.
//    - Iterate while `j <= i`. In each step, buy the candy at `prices[i]`, add it to `maxCost`.
//    - Then, get `k` free candies from the cheap end by incrementing `j` by `k`.
// Time Complexity: O(N log N), dominated by the sorting algorithm.
// Space Complexity: O(1), as sorting is done in-place and we use a constant amount of extra space.
class Solution {
  public:
    vector<int> minMaxCandy(vector<int>& prices, int k) {
        // Sort the array to easily access cheapest and most expensive candies
        sort(prices.begin(), prices.end());

        // --- Calculate Minimum Cost ---
        // We buy the cheapest candies and get the most expensive for free.
        int minCost = 0;
        int n = prices.size();
        for (int i = 0; i < n; i++) {
            minCost += prices[i]; // Buy the cheapest available candy
            n -= k;               // Get k most expensive candies for free
        }

        // --- Calculate Maximum Cost ---
        // We buy the most expensive candies and get the cheapest for free.
        int maxCost = 0;
        int index = -1;
        for (int i = prices.size() - 1; i > index; i--) {
            maxCost += prices[i]; // Buy the most expensive available candy
            index += k;           // Get k cheapest candies for free
        }

        return {minCost, maxCost}; // Return both costs
    }
};

/*
*
* Dry Run
*
* Input: prices[] = [3, 2, 1, 4], k = 2
*
* 1. Sort prices: [1, 2, 3, 4]
*
* 2. Calculate minCost:
* - i = 0, n = 4.  (0 < 4 is true)
* - minCost = 0 + prices[0] = 1.
* - n = 4 - 2 = 2.
* - i = 1, n = 2.  (1 < 2 is true)
* - minCost = 1 + prices[1] = 1 + 2 = 3.
* - n = 2 - 2 = 0.
* - i = 2, n = 0.  (2 < 0 is false). Loop terminates.
* - Final minCost = 3.
*
* 3. Calculate maxCost:
* - i = 3, index = -1. (3 > -1 is true)
* - maxCost = 0 + prices[3] = 4.
* - index = -1 + 2 = 1.
* - i = 2, index = 1.  (2 > 1 is true)
* - maxCost = 4 + prices[2] = 4 + 3 = 7.
* - index = 1 + 2 = 3.
* - i = 1, index = 3.  (1 > 3 is false). Loop terminates.
* - Final maxCost = 7.
*
* Output: {3, 7}
*
*/
```

### Java Solution

```java
// Intuition: To minimize cost, buy the cheapest candies and get the most expensive for free.
// To maximize cost, buy the most expensive candies and get the cheapest for free.
// Approach:
// 1. Sort the prices array in non-decreasing order.
// 2. For minimum cost:
//    - Initialize a pointer `i` to 0 and `n` to the total number of candies.
//    - Iterate while `i < n`. In each step, buy the candy at `prices[i]`, add it to `minCost`.
//    - Then, get `k` free candies from the expensive end by decrementing `n` by `k`.
// 3. For maximum cost:
//    - Initialize a pointer `i` to `prices.length - 1` and `j` to `0`.
//    - Iterate while `j <= i`. In each step, buy the candy at `prices[i]`, add it to `maxCost`.
//    - Then, get `k` free candies from the cheap end by incrementing `j` by `k`.
// Time Complexity: O(N log N), dominated by the sorting algorithm.
// Space Complexity: O(1), as sorting is done in-place and we use a constant amount of extra space.
class Solution {
    public ArrayList<Integer> minMaxCandy(int[] prices, int k) {
        // Sort the array to easily access cheapest and most expensive candies
        Arrays.sort(prices);

        // --- Calculate Minimum Cost ---
        // We buy the cheapest candies and get the most expensive for free.
        int minCost = 0;
        int n = prices.length;
        for (int i = 0; i < n; i++) {
            minCost += prices[i]; // Buy the cheapest available candy
            n -= k;               // Get k most expensive candies for free
        }

        // --- Calculate Maximum Cost ---
        // We buy the most expensive candies and get the cheapest for free.
        int maxCost = 0;
        int index = -1;
        for (int i = prices.length - 1; i > index; i--) {
            maxCost += prices[i]; // Buy the most expensive available candy
            index += k;           // Get k cheapest candies for free
        }

        // Prepare the result list
        ArrayList<Integer> result = new ArrayList<>();
        result.add(minCost);
        result.add(maxCost);

        return result; // Return both costs
    }
}

/*
*
* Dry Run
*
* Input: prices[] = {3, 2, 1, 4}, k = 2
*
* 1. Sort prices: {1, 2, 3, 4}
*
* 2. Calculate minCost:
* - i = 0, n = 4.  (0 < 4 is true)
* - minCost = 0 + prices[0] = 1.
* - n = 4 - 2 = 2.
* - i = 1, n = 2.  (1 < 2 is true)
* - minCost = 1 + prices[1] = 1 + 2 = 3.
* - n = 2 - 2 = 0.
* - i = 2, n = 0.  (2 < 0 is false). Loop terminates.
* - Final minCost = 3.
*
* 3. Calculate maxCost:
* - i = 3, index = -1. (3 > -1 is true)
* - maxCost = 0 + prices[3] = 4.
* - index = -1 + 2 = 1.
* - i = 2, index = 1.  (2 > 1 is true)
* - maxCost = 4 + prices[2] = 4 + 3 = 7.
* - index = 1 + 2 = 3.
* - i = 1, index = 3.  (1 > 3 is false). Loop terminates.
* - Final maxCost = 7.
*
* Output: [3, 7]
*
*/
```

---

## 🎯 Key Insights

- **Greedy is Optimal**: The problem structure allows for a greedy approach. The optimal strategy for both minimum and maximum cost doesn't require looking ahead or complex decision-making.
- **Sorting is Key**: Sorting the prices is the fundamental step that enables the greedy selection of the "cheapest" or "most expensive" candies.
- **Two-Pointer Simulation**: For both min and max cost calculations, the loops with their respective pointers/indices cleverly simulate the process of buying one candy and getting `k` others for free from the opposite end of the price spectrum.

---

## 🔎 Further Exploration

This problem is a great introduction to greedy algorithms. To sharpen your skills, try these related problems:

- [N meetings in one room](https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1)
- [Job Sequencing Problem](https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1)
- [Fractional Knapsack](https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1)

---

## 📚 References

- **Original Problem:** [Shop in Candy Store on GeeksforGeeks](https://www.geeksforgeeks.org/problems/shop-in-candy-store1145/1)
- **Learn More:** [Greedy Algorithms on GeeksforGeeks](https://www.geeksforgeeks.org/greedy-algorithms/)

---

## 👨‍💻 Author

- [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

<div>

![Greedy](https://img.shields.io/badge/Greedy-Algorithm-orange?style=for-the-badge)
![Sorting](https://img.shields.io/badge/Sorting-blue?style=for-the-badge)
![Array](https://img.shields.io/badge/Array-yellowgreen?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge)

</div>

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**A gentle reminder that this repository is for educational purposes. It's a great resource for learning and understanding different approaches to problem-solving. Happy coding!**