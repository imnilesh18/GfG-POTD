<div align="center">

# 🎫 Max Amount by Selling K Tickets

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty Medium](https://img.shields.io/badge/Difficulty-Medium-yellow?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-49.96%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-blue?style=for-the-badge)
![License MIT](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

<br>

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

</div>

---

## 📝 Problem Statement

Given an integer array `arr[]`, where `arr[i]` denotes the number of tickets available with the `i-th` ticket seller. 
The price of each ticket is equal to the number of tickets remaining with that seller at the time of sale. 
A seller can sell at most one ticket at a time, and after each sale, the price of the next ticket from that seller decreases by `1`.
All sellers are allowed to sell at most `k` tickets in total.

Find the **maximum amount** that can be earned by selling `k` tickets. Return the answer modulo $10^9+7$.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = [4, 3, 6, 2, 4], k = 3
Output: 15
Explanation: 
One optimal sequence is to sell two tickets from the seller with 6 tickets (the price of first would be 6 and second 5) 
and one ticket from a seller with 4 tickets. This gives a total earning of 6 + 5 + 4 = 15.
```

### Example 2
```text
Input: arr[] = [5, 3, 5, 2, 4, 4], k = 2
Output: 10
Explanation: 
One optimal sequence is to sell one ticket each from the two sellers with 5 tickets, earning 5 + 5 = 10.
```

<details>
<summary><b>📖 Example Breakdown (Example 1)</b></summary>
<br>

1. **Initial states:** Ticket counts per seller are `[4, 3, 6, 2, 4]`.
2. **Sale 1:** The highest priced ticket available is `6`. 
   - Sell it. Amount earned = `6`.
   - Seller's tickets update to `5`.
3. **Sale 2:** The highest priced ticket available is now `5`.
   - Sell it. Amount earned = `6 + 5 = 11`.
   - Seller's tickets update to `4`.
4. **Sale 3:** The highest priced tickets available are `4` (from multiple sellers).
   - Sell any one of them. Amount earned = `11 + 4 = 15`.
   - Seller's tickets update to `3`.
5. We have sold `k = 3` tickets. Maximum total earning is **15**.
</details>

---

## ⚙️ Constraints

> - $1 \le \text{arr.size()} \le 10^5$
> - $1 \le \text{arr}[i], k \le 10^6$

---

## 🚀 Solution Approaches

### Max-Heap (Priority Queue) Approach
The problem requires us to always select the highest available ticket price dynamically. A **Priority Queue (Max-Heap)** is perfectly suited for this. By pushing all ticket counts into a max-heap, we can effortlessly extract the maximum value in $O(\log n)$ time, add it to our total, and then push the decremented value back if it's strictly greater than $0$. Repeating this process $k$ times guarantees the maximum profit.

```cpp
// Intuition: To maximize profit, always sell the most expensive available ticket. A max-heap keeps track of the highest ticket prices dynamically.
// Approach: Insert all ticket counts into a max-heap. Extract the max element, add it to total amount, decrement it, and push it back if it's > 0. Repeat k times.
// Time Complexity: O(n + k log n) where n is array size and k is number of tickets. Building heap takes O(n), each of k pops/pushes takes O(log n).
// Space Complexity: O(n) to store elements in the priority queue.

class Solution {
  public:
    int maxAmount(vector<int>& arr, int k) {
        // Modulo constant for large answer tracking
        int mod = 1e9 + 7;
        
        // Max-heap to store available tickets per seller
        priority_queue<int> pq(arr.begin(), arr.end());
        long long max_earned = 0;
        
        // Greedily pick the highest priced ticket k times
        while (k > 0 && !pq.empty()) {
            // Get highest available ticket price
            int max_price = pq.top();
            pq.pop();
            
            // Add current highest price to total earnings
            max_earned = (max_earned + max_price) % mod;
            
            // If seller still has tickets, push updated count back
            if (max_price - 1 > 0) {
                pq.push(max_price - 1);
            }
            
            k--; // One ticket successfully sold
        }
        
        return max_earned;
    }
};

/*
*
* Dry Run
* Input: arr[] = [4, 3, 6, 2, 4], k = 3
* Initialize max-heap: [6, 4, 4, 3, 2], max_earned = 0
* * Iteration 1:
* max_price = 6, pop 6
* max_earned = 0 + 6 = 6
* Push 5 into heap -> [5, 4, 4, 3, 2]
* k = 2
* * Iteration 2:
* max_price = 5, pop 5
* max_earned = 6 + 5 = 11
* Push 4 into heap -> [4, 4, 4, 3, 2]
* k = 1
* * Iteration 3:
* max_price = 4, pop 4
* max_earned = 11 + 4 = 15
* Push 3 into heap -> [4, 4, 3, 3, 2]
* k = 0
* * Loop ends since k == 0
* Return max_earned = 15
*/
```

---

## 🧠 Key Insights
- **Greedy Strategy:** At any given step, picking the absolute highest value maximizes our immediate earning without negatively impacting our future options (since picking the highest naturally decrements it to the next highest possible value).
- **Heap Efficiency:** Instead of sorting repeatedly or keeping track of an array linearly, building a `priority_queue` in C++ runs in linear $O(n)$ time, and updating it takes logarithmic $O(\log n)$ time.

---

## 🔍 Further Exploration
- Try optimizing it to strictly $O(n \log n)$ by using **Binary Search on the Answer**. Find a threshold price such that the sum of all tickets sold above this price equals $k$. 
- **Similar GFG Problems:** Minimum Cost of Ropes, Maximize array sum after K negations.

---

## 🔗 References
- **Original Problem:** [Max Amount by Selling K Tickets on GeeksforGeeks](https://www.geeksforgeeks.org/problems/ticket-sellers3241/1)
- **C++ Priority Queue Docs:** [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue)

---

## 🧑‍💻 Author
Made with ❤️ by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags
![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white) 
![Data Structures](https://img.shields.io/badge/Data%20Structures-1E293B?style=for-the-badge) 
![Priority Queue](https://img.shields.io/badge/Priority%20Queue-FF6F00?style=for-the-badge) 
![Greedy](https://img.shields.io/badge/Greedy-000000?style=for-the-badge) 
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge)