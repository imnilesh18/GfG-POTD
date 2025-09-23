# 🔄 Queue Reversal

<div align="center">

![GFG](https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-green?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-77.98%25-yellow?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)

</div>

---

> ⚠️ **Educational Use Only**:
> This repository and its content are intended solely for educational purposes. The solutions are provided for learning, practice, and reference only. The problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/queue-reversal/1).

---

## 📝 Problem Statement

Given a queue `q` containing integer elements, your task is to **reverse** the queue.

---

## 📖 Examples

Here are a couple of examples to illustrate the problem:

<div align="center">

<table width="100%">
    <tr>
        <th width="50%">Example 1</th>
        <th width="50%">Example 2</th>
    </tr>
    <tr>
        <td>
            <pre>
<strong>Input:</strong> q[] = [5, 10, 15, 20, 25]
<strong>Output:</strong> [25, 20, 15, 10, 5]
<strong>Explanation:</strong> After reversing, the
queue becomes 25 20 15 10 5.
            </pre>
        </td>
        <td>
            <pre>
<strong>Input:</strong> q[] = [1, 2, 3, 4, 5]
<strong>Output:</strong> [5, 4, 3, 2, 1]
<strong>Explanation:</strong> After reversing, the
queue becomes 5 4 3 2 1.
            </pre>
        </td>
    </tr>
</table>

</div>

<details>
<summary><strong>Example Breakdown (Input: q = [5, 10, 15])</strong></summary>

1.  **Initial Queue:**
    * `Front -> [5, 10, 15] <- Rear`
2.  **Goal:** Reverse the queue so it becomes:
    * `Front -> [15, 10, 5] <- Rear`
3.  **How?** We need a mechanism to extract elements in FIFO (First-In, First-Out) order and re-insert them in LIFO (Last-In, First-Out) order. A **Stack** is the perfect data structure for this.
4.  **Step 1: Dequeue from Queue and Push to Stack**
    * Dequeue `5`, Push `5` to stack. Stack: `[5]`
    * Dequeue `10`, Push `10` to stack. Stack: `[5, 10]`
    * Dequeue `15`, Push `15` to stack. Stack: `[5, 10, 15]` (Top is 15)
    * Queue is now empty.
5.  **Step 2: Pop from Stack and Enqueue to Queue**
    * Pop `15`, Enqueue `15`. Queue: `[15]`
    * Pop `10`, Enqueue `10`. Queue: `[15, 10]`
    * Pop `5`, Enqueue `5`. Queue: `[15, 10, 5]`
    * Stack is now empty.
6.  **Final Queue:**
    * `Front -> [15, 10, 5] <- Rear`. The queue is successfully reversed.

</details>

---

## ⛓️ Constraints

The constraints for this problem are:
* `1 ≤ q.size() ≤ 10^3`
* `0 ≤ q[i] ≤ 10^5`

---

## 💡 Solution Approaches

The most intuitive way to solve this is by using a **Stack**. A queue operates on a **FIFO** (First-In, First-Out) principle, while a stack operates on a **LIFO** (Last-In, First-Out) principle. By transferring elements from the queue to the stack and then back to the queue, we can naturally reverse their order.

### C++ Solution

```cpp
// Intuition: The core idea is to leverage the Last-In-First-Out (LIFO) property of a stack to reverse the First-In-First-Out (FIFO) order of a queue. By moving all elements from the queue to a stack, the first element of the queue becomes the last one to be pushed onto the stack. Then, moving them back to the queue retrieves them in reversed order.
// Approach:
// 1. Create an auxiliary stack.
// 2. Dequeue every element from the queue and push it onto the stack. This process continues until the queue is empty.
// 3. Once all elements are in the stack, pop each element from the stack and enqueue it back into the now-empty queue.
// 4. The queue will now contain the elements in reversed order.
// Time Complexity: O(N), where N is the number of elements in the queue. Each element is enqueued and dequeued once, and pushed and popped from the stack once.
// Space Complexity: O(N), as we use an auxiliary stack to store all N elements from the queue.
class Solution {
  public:
    void reverseQueue(queue<int> &q) {
        stack<int> st; // Create an auxiliary stack.
    
        // Transfer all elements from the queue to the stack.
        // The first element of the queue will be at the bottom of the stack.
        while (!q.empty()) {
            st.push(q.front()); // Get the front element of the queue and push to stack.
            q.pop();            // Remove the element from the queue.
        }
        
        // Transfer all elements back from the stack to the queue.
        // This reverses the order because the stack is LIFO.
        while (!st.empty()) {
            q.push(st.top());   // Get the top element of the stack and push to queue.
            st.pop();           // Remove the element from the stack.
        }
    }
};

/*
*
* Dry Run
*
* Input: q = [5, 10, 15, 20, 25]
*
* 1. Initialize an empty stack `st`.
*
* 2. First while loop (Queue to Stack):
* - q is [5, 10, 15, 20, 25]. Pop 5, push to st.  q: [10, 15, 20, 25], st: [5]
* - q is [10, 15, 20, 25]. Pop 10, push to st. q: [15, 20, 25],   st: [5, 10]
* - q is [15, 20, 25]. Pop 15, push to st.   q: [20, 25],       st: [5, 10, 15]
* - q is [20, 25]. Pop 20, push to st.       q: [25],           st: [5, 10, 15, 20]
* - q is [25]. Pop 25, push to st.           q: [],             st: [5, 10, 15, 20, 25]
* - q is empty, loop terminates.
*
* 3. Second while loop (Stack to Queue):
* - st is [5, 10, 15, 20, 25]. Pop 25, push to q. st: [5, 10, 15, 20], q: [25]
* - st is [5, 10, 15, 20]. Pop 20, push to q.    st: [5, 10, 15],      q: [25, 20]
* - st is [5, 10, 15]. Pop 15, push to q.       st: [5, 10],          q: [25, 20, 15]
* - st is [5, 10]. Pop 10, push to q.          st: [5],              q: [25, 20, 15, 10]
* - st is [5]. Pop 5, push to q.             st: [],               q: [25, 20, 15, 10, 5]
* - st is empty, loop terminates.
*
* Final Queue: [25, 20, 15, 10, 5]
*
*/
```

---

## 🔑 Key Insights

The problem highlights the fundamental difference between Queues (FIFO) and Stacks (LIFO). The key insight is that one can be used to reverse the behavior of the other. This is a classic data structure problem that demonstrates a practical application of stacks.

---

## 🚀 Further Exploration

-   **Reverse first K elements of a queue:** A variation where you only reverse the first `k` elements, leaving the rest in their original order.
-   **Reverse a stack using a queue:** The inverse of this problem, which can be solved with a similar logic using an auxiliary queue.
-   **Implement a queue using two stacks:** A more complex challenge that tests your understanding of both data structures.

---

## 📚 References

* [Original GeeksforGeeks Problem](https://www.geeksforgeeks.org/problems/queue-reversal/1)
* [GeeksforGeeks Article on Queue Reversal](https://www.geeksforgeeks.org/reversing-a-queue/)

---

## 👨‍💻 Author

* **Code and README by:** [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

![Queue](https://img.shields.io/badge/Queue-blue?style=for-the-badge)
![Stack](https://img.shields.io/badge/Stack-orange?style=for-the-badge)
![Data Structures](https://img.shields.io/badge/Data%20Structures-grey?style=for-the-badge)
![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-green?style=for-the-badge)

---

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

**Reminder**: The solutions in this repository are for educational purposes only. It is highly encouraged to attempt the problems on your own before referring to these solutions.