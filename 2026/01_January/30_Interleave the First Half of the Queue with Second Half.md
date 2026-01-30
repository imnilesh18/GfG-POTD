# 🟧 Interleave the First Half of the Queue with Second Half

![GFG](https://img.shields.io/badge/GeeksforGeeks-Interleave%20the%20First%20Half%20of%20the%20Queue-brightgreen?style=for-the-badge&logo=geeksforgeeks)
![Difficulty](https://img.shields.io/badge/Difficulty-Medium-orange?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-62.41%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-4-yellow?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=for-the-badge)

⚠️ **Educational Use Only:**
This repository and its content are intended solely for educational purposes. Solutions are provided for learning, practice, and reference only. Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given a queue `q[]` of **even** size. Your task is to rearrange the queue by interleaving its **first half** with the **second half**.

Interleaving is the process of mixing two sequences by alternating their elements while preserving their relative order. In other words, Interleaving means place the first element from the first half and then first element from the 2nd half and again second element from the first half and then second element from the 2nd half and so on...

---

## 🚀 Examples

### Example 1:
```text
Input: q[] = [2, 4, 3, 1]
Output: [2, 3, 4, 1]
Explanation: 
First half: [2, 4], Second half: [3, 1]
Interleaved: 2 (from 1st half) -> 3 (from 2nd half) -> 4 (from 1st half) -> 1 (from 2nd half)
```

### Example 2:
```text
Input: q[] = [3, 5]
Output: [3, 5]
Explanation: 
First half: [3], Second half: [5]
Interleaved: 3 -> 5
```

<details>
<summary>📖 Example Breakdown (Dry Run Walkthrough)</summary>

**Input Queue:** `[1, 2, 3, 4]` (Size 4, Half Size 2)

1.  **Move first half to stack:** Queue: `[3, 4]`, Stack: `[1, 2]` (top: 2)
2.  **Stack back to queue:** Queue: `[3, 4, 2, 1]`
3.  **Rotate first half (old second half):** Queue: `[2, 1, 3, 4]`
4.  **Move current first half back to stack:** Queue: `[3, 4]`, Stack: `[2, 1]` (top: 1)
5.  **Interleave:** -   Pop 1 from stack, push to queue. Dequeue 3, push to queue.
    -   Pop 2 from stack, push to queue. Dequeue 4, push to queue.
**Final Queue:** `[1, 3, 2, 4]`
</details>

---

## ⚙️ Constraints

- `1 ≤ queue.size() ≤ 10^3`
- `1 ≤ queue[i] ≤ 10^5`
- `queue.size()` is always **even**.

---

## 💡 Solution Approaches

### 1. Using Stack (Optimized)
**Intuition:** Since we need to pick elements from the first half and alternate them with the second half, a stack helps in reversing the first half twice to restore its original order while maintaining access to the elements.

```cpp
// Intuition: Use a stack as temporary storage to rearrange the first half of the queue so it can be interleaved with the second half element-by-element.
// Approach: 1. Push first half to stack. 2. Enqueue stack back to queue. 3. Rotate queue to bring second half to the front. 4. Push first half to stack again. 5. Pop from stack and dequeue from queue alternately.
// Time Complexity: O(n) - We perform a constant number of passes over the elements.
// Space Complexity: O(n) - A stack is used to store half of the queue elements.

class Solution {
  public:
    void rearrangeQueue(queue<int>& q){
        stack<int> s;
        int halfSize = q.size() / 2;
    
        // Move first half elements from queue into the stack
        for (int i = 0; i < halfSize; i++) {
            s.push(q.front());
            q.pop();
        }
    
        // Enqueue back the stack elements (reverses their order in queue)
        while (!s.empty()) {
            q.push(s.top());
            s.pop();
        }
    
        // Move the current front elements (the original second half) to the back
        for (int i = 0; i < halfSize; i++) {
            q.push(q.front());
            q.pop();
        }
    
        // Push the new first half (original first half in original order) into the stack
        for (int i = 0; i < halfSize; i++) {
            s.push(q.front());
            q.pop();
        }
    
        // Interleave by alternating stack pops and queue dequeues
        while (!s.empty()) {
            q.push(s.top()); // Add element from first half
            s.pop();
            q.push(q.front()); // Add element from second half
            q.pop();
        }
    }
};

/*
* Dry Run:
* Initial Queue: [10, 20, 30, 40]
* halfSize = 2
* 1. Stack first half: q=[30, 40], s=[10, 20]
* 2. Enqueue stack: q=[30, 40, 20, 10], s=[]
* 3. Rotate queue: q=[20, 10, 30, 40]
* 4. Stack front half: q=[30, 40], s=[20, 10] (top: 10)
* 5. Interleave:
* - Pop 10, Push: q=[30, 40, 10]. Front 30, Push: q=[40, 10, 30]
* - Pop 20, Push: q=[10, 30, 20]. Front 40, Push: q=[10, 30, 20, 40]
* Result: [10, 30, 20, 40]
*/
```

---

## 🔑 Key Insights

- **Stack Property:** Using a stack twice effectively reverses the sequence of the first half twice, returning it to its original order while allowing us to interleave.
- **Queue Rotation:** Moving elements from the front to the back of the queue is a clean way to "skip" or "reorder" segments without extra linear space besides the stack.

---

## 🔍 Further Exploration

- [Reverse First K elements of Queue](https://www.geeksforgeeks.org/problems/reverse-first-k-elements-of-queue/1)
- [Implement Stack using Queues](https://www.geeksforgeeks.org/problems/stack-using-two-queues/1)

---

## 🔗 References

- **Problem Link:** [Interleave the First Half of the Queue with Second Half](https://www.geeksforgeeks.org/problems/interleave-the-first-half-of-the-queue-with-second-half/1)

---

## 👤 Author

Developed with ❤️ by [imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

`queue` `stack` `interleaving` `data-structures` `geeksforgeeks` `cpp`

---

## 📜 License

This project is licensed under the **MIT License**.
*This content is strictly for educational purposes.*