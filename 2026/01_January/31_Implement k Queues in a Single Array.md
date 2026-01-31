# 📚 Implement k Queues in a Single Array

<div align="center">

![GeeksforGeeks](https://img.shields.io/badge/GeeksforGeeks-298D35?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Hard-red?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Accuracy](https://img.shields.io/badge/Accuracy-74.25%25-green?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-8-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

</div>

---

### ⚠️ Educational Use Only
> **This repository and its content are intended solely for educational purposes.** > Solutions are provided for learning, practice, and reference only.  
> Problem statement and test cases are based on the [GeeksforGeeks problem](https://www.geeksforgeeks.org/problems/implement-k-queues-in-a-single-array/1).

---

## 📝 Problem Statement

You are given two integers `n` and `k`. Your task is to implement a class `kQueues` that uses a single array of size `n` to simulate `k` independent queues.

The class should support the following operations:
* `enqueue(x, i)`: Adds the element `x` into the `i`-th queue.
* `dequeue(i)`: Removes the front element from the `i`-th queue and returns it. Returns `-1` if the queue is empty.
* `isEmpty(i)`: Returns `true` if `i`-th queue is empty, else return `false`.
* `isFull()`: Returns `true` if the array is completely full and no more elements can be inserted, otherwise `false`.

There will be a sequence of `q` queries represented as:
1.  `1 x i`: Call `enqueue(x, i)`
2.  `2 i`: Call `dequeue(i)`
3.  `3 i`: Call `isEmpty(i)`
4.  `4`: Call `isFull()`

The driver code will process the queries, call the corresponding functions, and print the results of dequeue, isEmpty, and isFull operations.

---

## 💡 Examples

### Example 1

```bash
Input: 
n = 4, k = 2, q = 8
queries = [[1, 5, 0], [1, 3, 0], [1, 1, 1], [2, 0], [1, 4, 1], [1, 1, 0], [3, 1], [4]]

Output: 
[5, false, true]

Explanation: 
enqueue(5, 0) → queue0 = [5]
enqueue(3, 0) → queue0 = [5, 3]
enqueue(1, 1) → queue1 = [1]
dequeue(0)    → returns 5, queue0 = [3]
enqueue(4, 1) → queue1 = [1, 4]
enqueue(1, 0) → queue0 = [3, 1]
isEmpty(1)    → false
isFull()      → true

```

<details>
<summary><b>📖 Example Breakdown</b></summary>

1. **Init**: Array size 4, 2 Queues. All slots free.
2. **enqueue(5, 0)**: Uses index 0. `Q0: [5]`.
3. **enqueue(3, 0)**: Uses index 1. `Q0: [5, 3]`.
4. **enqueue(1, 1)**: Uses index 2. `Q1: [1]`.
5. **dequeue(0)**: Removes head of Q0 (which is 5 at index 0). Index 0 becomes free. `Q0: [3]`.
6. **enqueue(4, 1)**: Uses index 0 (recycled). `Q1: [1, 4]`.
7. **enqueue(1, 0)**: Uses index 3. `Q0: [3, 1]`.
8. **isEmpty(1)**: Q1 is not empty. Returns `false`.
9. **isFull()**: All indices (0, 1, 2, 3) are used. Returns `true`.

</details>

### Example 2

```bash
Input: 
n = 6, k = 3, q = 4
queries = [[1, 3, 2], [2, 0], [1, 2, 1], [3, 2]]

Output: 
[-1, false]

Explanation: 
enqueue(3, 2) → queue2 = [3]
dequeue(0)    → queue0 is empty, returns -1
enqueue(2, 1) → queue1 = [2]
isEmpty(2)    → false

```

---

## 🛑 Constraints

* 
* 
* 

---

## 🛠️ Solution Approach

### Optimized "Free List" Approach

The most efficient way to solve this is to treat the single array like a pool of memory nodes in a Linked List. We maintain arrays to track:

1. **Front**: The start index of each queue.
2. **Rear**: The end index of each queue.
3. **Next**: The next index for an element (pointers) OR the next available free slot.
4. **Free**: A pointer to the beginning of the "free" slots list.

This allows  allocation and deallocation of slots regardless of which queue needs them.

```cpp
// Intuition: Efficiently share a single array among k queues using a free list to manage available slots, mimicking a linked list structure within arrays.
// Approach: 
// 1. Maintain 'front' and 'rear' arrays to track the head and tail indices of each of the k queues.
// 2. Use a 'next' array to store the next element index in a queue AND to link free slots together.
// 3. Maintain a 'freeIndex' that points to the head of the available free slots list.
// 4. Enqueue: Take slot from free list, add to queue rear. Dequeue: Remove from queue front, add slot back to free list.
// Time Complexity: O(1) for all operations (enqueue, dequeue, isEmpty, isFull) as they entail constant index updates.
// Space Complexity: O(N) where N is the array size, for storing the auxiliary 'front', 'rear', and 'next' arrays.

class kQueues {
private:
    vector<int> arr;       // Stores the actual data elements
    int n, k;              // n: size of array, k: number of queues
    vector<int> front;     // Stores index of front element for each queue
    vector<int> rear;      // Stores index of rear element for each queue
    vector<int> next;      // Stores next index in queue or next free slot
    int freeIndex;         // Index of the first free slot in the array

public:
    kQueues(int n, int k) {
        this->n = n;
        this->k = k;
        arr.resize(n);
        front.assign(k, -1); // Initialize all queue fronts to -1 (empty)
        rear.assign(k, -1);  // Initialize all queue rears to -1 (empty)
        next.resize(n);
        
        // Initialize all spaces as free and link them together
        freeIndex = 0;
        for (int i = 0; i < n - 1; i++)
            next[i] = i + 1; // Point to the next available slot
            
        next[n - 1] = -1; // End of free list
    }
    
    // Checks if queue qn is empty
    bool isEmpty(int qn) {
        return (front[qn] == -1);
    }
    
    // Checks if the entire array space is exhausted
    bool isFull() {
        return (freeIndex == -1);
    }
    
    // Adds element x to queue qn
    bool enqueue(int x, int qn) {
        if (isFull()) return false; // No free slots available
            
        int i = freeIndex;     // Get index of the first free slot
        freeIndex = next[i];   // Update freeIndex to the next available slot
        
        if (isEmpty(qn)) {
            front[qn] = i;     // If queue was empty, this is the first element
        } else {
            next[rear[qn]] = i; // Link the previous rear to this new node
        }
        
        next[i] = -1;          // This new node is now the end of the queue
        rear[qn] = i;          // Update rear of queue qn to current index
        arr[i] = x;            // Store the value
        
        return true;
    }
    
    // Removes element from queue qn
    int dequeue(int qn) {
        if (isEmpty(qn)) return -1; // Queue is empty
            
        int i = front[qn];       // Index of the element to be removed
        front[qn] = next[i];     // Move front to the next element in this queue
        
        // If queue becomes empty after removal
        if (front[qn] == -1) {
            rear[qn] = -1;       
        }
        
        // Add the freed index 'i' back to the beginning of free list
        next[i] = freeIndex;
        freeIndex = i;
        
        return arr[i];
    }
};

/*
*
* Dry Run
* Input: n=3, k=1. (Simple case for clarity)
* Init: free=0, next=[1,2,-1], front=[-1], rear=[-1]
*
* 1. enqueue(10, 0):
* - Get free slot i=0. New free=next[0]=1.
* - Queue 0 empty -> front[0]=0.
* - next[0]=-1. rear[0]=0. arr[0]=10.
* - State: arr=[10,?,?], front=[0], rear=[0], next=[-1,2,-1], free=1
*
* 2. enqueue(20, 0):
* - Get free slot i=1. New free=next[1]=2.
* - Queue 0 not empty -> next[rear[0]] = next[0] = 1.
* - next[1]=-1. rear[0]=1. arr[1]=20.
* - State: arr=[10,20,?], front=[0], rear=[1], next=[1,-1,-1], free=2
*
* 3. dequeue(0):
* - Item at front[0] is index 0. Val=10.
* - New front[0] = next[0] = 1.
* - Recycle index 0: next[0]=free(2) -> next[0]=2. free=0.
* - Returns 10.
* - State: front=[1], rear=[1], next=[2,-1,-1], free=0
*/

```

---

## 🗝️ Key Insights

1. **Free List Management**: The core trick is maintaining a linked list of "free" indices using the `next` array. When we `dequeue`, we push the freed index back to the head of the free list. When we `enqueue`, we pop from the head.
2. **Dynamic Allocation**: Instead of partitioning the array into fixed segments (which wastes space if one queue is empty and another is full), this approach allows any queue to use any available slot in the array.
3. **Linked List Simulation**: The `next` array effectively serves as the "next pointer" for both the actual queues and the free list chain.

---

## 🚀 Further Exploration

* **Circular Queues**: How would you implement k Circular Queues?
* **k Stacks**: Try implementing k Stacks in a single array (Logic is similar but simpler, essentially managing k linked lists LIFO style).
* **Thread Safety**: How to make this class thread-safe?

---

## 🔗 References

* [GeeksforGeeks Problem Link](https://www.geeksforgeeks.org/problems/implement-k-queues-in-a-single-array/1)

---

## 🧑‍💻 Author

[imnilesh18](https://github.com/imnilesh18)

---

## 🏷️ Tags

---

## 📜 License

<div align="center">

</div>

> **Disclaimer**: This code is for educational purposes. Please use it responsibly and do not submit it as your own in contests.
