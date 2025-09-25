# 🔟 Generate Binary Numbers

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-blue.svg?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-67.48%25-yellow.svg?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-green.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red.svg?style=for-the-badge)

</div>

---

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. The solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/generate-binary-numbers-1587115620/1).

---

## 🎯 Problem Statement

Given a number `n`, the task is to generate all binary numbers with decimal values from `1` to `n`.

---

## 📖 Examples

Here are the sample test cases to illustrate the problem.

<details>
<summary><strong>Example 1</strong></summary>

```
Input: n = 4
Output: ["1", "10", "11", "100"]
Explanation: Binary numbers from 1 to 4 are 1, 10, 11, and 100.
```

</details>

<details>
<summary><strong>Example 2</strong></summary>

```
Input: n = 6
Output: ["1", "10", "11", "100", "101", "110"]
Explanation: Binary numbers from 1 to 6 are 1, 10, 11, 100, 101, and 110.
```

</details>

<details>
<summary><strong>📖 Example Breakdown (n = 4)</strong></summary>

Let's walk through the process using a queue:

1.  **Initialize:**

    - `result = []`
    - `queue = ["1"]` (Start with the binary representation of 1)
    - We need to generate 4 numbers.

2.  **Iteration 1 (n=4):**

    - Dequeue `"1"`.
    - Add it to `result`. `result` is now `["1"]`.
    - Generate its children by appending "0" and "1":
      - Enqueue `"10"`.
      - Enqueue `"11"`.
    - `queue` is now `["10", "11"]`.

3.  **Iteration 2 (n=3):**

    - Dequeue `"10"`.
    - Add it to `result`. `result` is now `["1", "10"]`.
    - Generate its children:
      - Enqueue `"100"`.
      - Enqueue `"101"`.
    - `queue` is now `["11", "100", "101"]`.

4.  **Iteration 3 (n=2):**

    - Dequeue `"11"`.
    - Add it to `result`. `result` is now `["1", "10", "11"]`.
    - Generate its children:
      - Enqueue `"110"`.
      - Enqueue `"111"`.
    - `queue` is now `["100", "101", "110", "111"]`.

5.  **Iteration 4 (n=1):**

    - Dequeue `"100"`.
    - Add it to `result`. `result` is now `["1", "10", "11", "100"]`.
    - The loop terminates as we have generated `n` numbers.

6.  **Final Result:** `["1", "10", "11", "100"]`. This level-by-level generation naturally produces the binary numbers in increasing order.

</details>

---

## ⛓️ Constraints

- `1 ≤ n ≤ 10^6`

---

## 💡 Solution Approaches

The problem can be efficiently solved using a **Queue** data structure, which leverages a Breadth-First Search (BFS) approach.

### Optimized Approach (Using a Queue)

The core idea is to generate binary numbers level by level. We start with "1". In each step, we dequeue a binary number, add it to our result list, and then enqueue two new numbers: the current number with a "0" appended and the current number with a "1" appended. This process naturally generates the numbers in the correct sequence from 1 to `n`.

#### C++ Solution

```cpp
// Intuition: The problem can be modeled as a level-order traversal (BFS) of an implicit binary tree. The root is "1". The left child of any node is formed by appending "0" and the right child by appending "1". A queue is perfect for BFS.
// Approach:
// 1. Create a queue of strings and initialize it by pushing "1".
// 2. Create a vector of strings `res` to store the results.
// 3. Loop `n` times:
//    a. Dequeue the front element, let's call it `s1`.
//    b. Add `s1` to the result vector `res`.
//    c. Create a copy of `s1`, let's call it `s2`.
//    d. Append "0" to `s1` and push it into the queue.
//    e. Append "1" to `s2` and push it into the queue.
// 4. Return the result vector.
// Time Complexity: O(n), because we loop `n` times, and each string operation inside the loop is amortized constant time relative to the scale of n.
// Space Complexity: O(n), as the queue can store up to O(n) binary numbers at a time.
class Solution {
  public:
    vector<string> generateBinary(int n){
        vector<string> res; // Vector to store the final binary strings.
        queue<string> q;    // Queue to manage the generation process (BFS).

        // Enqueue the first binary number, which is "1".
        q.push("1");

        // This loop simulates a BFS traversal. It runs n times to generate n binary numbers.
        while (n--) {

            // Dequeue the current binary number string.
            string s1 = q.front();
            q.pop();
            res.push_back(s1); // Add it to our result list.

            string s2 = s1; // Make a copy for appending "1".

            // Check if we still need to generate more numbers to avoid extra pushes.
            if(q.size() < n) {

                // Append "0" to s1 and enqueue it. This is the "left child".
                q.push(s1.append("0"));

                // Append "1" to s2 and enqueue it. This is the "right child".
                q.push(s2.append("1"));
            }
        }
        return res; // Return the collected binary numbers.
    }

    /*
    *
    * Dry Run (n = 4)
    *
    * Initial State:
    * res = []
    * q = ["1"]
    * n = 4
    *
    * Iteration 1 (n becomes 3):
    * s1 = q.front() -> "1", q.pop() -> q is empty
    * res.push_back("1") -> res = ["1"]
    * s2 = "1"
    * q.push(s1 + "0") -> q = ["10"]
    * q.push(s2 + "1") -> q = ["10", "11"]
    *
    * Iteration 2 (n becomes 2):
    * s1 = q.front() -> "10", q.pop() -> q = ["11"]
    * res.push_back("10") -> res = ["1", "10"]
    * s2 = "10"
    * q.push(s1 + "0") -> q = ["11", "100"]
    * q.push(s2 + "1") -> q = ["11", "100", "101"]
    *
    * Iteration 3 (n becomes 1):
    * s1 = q.front() -> "11", q.pop() -> q = ["100", "101"]
    * res.push_back("11") -> res = ["1", "10", "11"]
    * s2 = "11"
    * q.push(s1 + "0") -> q = ["100", "101", "110"]
    * q.push(s2 + "1") -> q = ["100", "101", "110", "111"]
    *
    * Iteration 4 (n becomes 0):
    * s1 = q.front() -> "100", q.pop() -> q = ["101", "110", "111"]
    * res.push_back("100") -> res = ["1", "10", "11", "100"]
    * Loop condition (n--) is now false. Loop terminates.
    *
    * Final Result: ["1", "10", "11", "100"]
    *
    */
};
```

#### Java Solution

```java
// Intuition: The problem can be modeled as a level-order traversal (BFS) of an implicit binary tree. The root is "1". The left child of any node is formed by appending "0" and the right child by appending "1". A queue is perfect for BFS.
// Approach:
// 1. Create a queue of strings and initialize it by adding "1".
// 2. Create a list of strings `res` to store the results.
// 3. Loop `n` times:
//    a. Dequeue the front element, let's call it `s1`.
//    b. Add `s1` to the result list `res`.
//    c. Enqueue two new strings: `s1 + "0"` and `s1 + "1"`.
// 4. Return the result list.
// Time Complexity: O(n), because we loop `n` times, and each string operation inside the loop is amortized constant time relative to the scale of n.
// Space Complexity: O(n), as the queue can store up to O(n) binary numbers at a time.
class Solution {
    public ArrayList<String> generateBinary(int n) {
        ArrayList<String> res = new ArrayList<>(); // List to store results.
        Queue<String> q = new LinkedList<>();     // Queue for BFS-style generation.

        // Add the first binary number.
        q.add("1");

        // Loop n times to generate n binary numbers.
        for (int i = 0; i < n; i++) {
            // Dequeue the current binary number string.
            String current = q.poll();
            res.add(current); // Add it to the result list.

            // Generate the next two numbers by appending "0" and "1".
            q.add(current + "0");
            q.add(current + "1");
        }

        return res; // Return the final list.
    }
    /*
    *
    * Dry Run (n = 4)
    *
    * Initial State:
    * res = []
    * q = ["1"]
    *
    * Loop 1 (i = 0):
    * current = q.poll() -> "1", q is empty
    * res.add("1") -> res = ["1"]
    * q.add("10") -> q = ["10"]
    * q.add("11") -> q = ["10", "11"]
    *
    * Loop 2 (i = 1):
    * current = q.poll() -> "10", q = ["11"]
    * res.add("10") -> res = ["1", "10"]
    * q.add("100") -> q = ["11", "100"]
    * q.add("101") -> q = ["11", "100", "101"]
    *
    * Loop 3 (i = 2):
    * current = q.poll() -> "11", q = ["100", "101"]
    * res.add("11") -> res = ["1", "10", "11"]
    * q.add("110") -> q = ["100", "101", "110"]
    * q.add("111") -> q = ["100", "101", "110", "111"]
    *
    * Loop 4 (i = 3):
    * current = q.poll() -> "100", q = ["101", "110", "111"]
    * res.add("100") -> res = ["1", "10", "11", "100"]
    * q.add("1000") -> q = ["101", "110", "111", "1000"]
    * q.add("1001") -> q = ["101", "110", "111", "1000", "1001"]
    *
    * Loop terminates after 4 iterations.
    * Final Result: ["1", "10", "11", "100"]
    *
    */
}
```

---

## 🔑 Key Insights

- **BFS for Ordered Generation:** Using a queue (which facilitates BFS) is the key. It ensures that we process numbers level by level (e.g., all 2-digit binary numbers before any 3-digit ones), which naturally generates them in ascending order of their decimal value.
- **Implicit Tree Structure:** The generation process can be visualized as traversing a binary tree that isn't explicitly stored in memory. The node `"s"` has children `"s0"` and `"s1"`. This mental model makes the queue-based approach intuitive.

---

## 🚀 Further Exploration

- **Generate N-ary Numbers:** How would you modify the solution to generate numbers in base-3 (ternary) or any base-k system?
- **Gray Codes:** Explore problems on generating Gray codes, which are binary numeral systems where two successive values differ in only one bit.
- [GeeksforGeeks: Print first n numbers with two given digits](https://www.geeksforgeeks.org/print-first-n-numbers-with-two-given-digits/)

---

## 🔗 References

- **Original Problem:** [GeeksforGeeks - Generate Binary Numbers](https://www.geeksforgeeks.org/problems/generate-binary-numbers-1587115620/1)
- **Data Structure:** [Queue in C++ STL](https://www.geeksforgeeks.org/queue-cpp-stl/)

---

## 👨‍💻 Author

- **Solutions By:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Queue](https://img.shields.io/badge/Queue-blue?style=for-the-badge)
![Strings](https://img.shields.io/badge/Strings-orange?style=for-the-badge)
![Data Structures](https://img.shields.io/badge/Data%20Structures-green?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. It is intended for educational purposes only.
