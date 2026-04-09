# 🟢 Intersection of Two Sorted Arrays

<div align="center">
  <a href="https://www.geeksforgeeks.org/problems/intersection-of-two-sorted-arrays-with-duplicate-elements/1">
    <img src="https://img.shields.io/badge/GeeksforGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white" alt="GeeksforGeeks" />
  </a>
  <img src="https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge" alt="Difficulty" />
  <img src="https://img.shields.io/badge/Accuracy-47.82%25-blue?style=for-the-badge" alt="Accuracy" />
  <img src="https://img.shields.io/badge/Points-2-orange?style=for-the-badge" alt="Points" />
  <img src="https://img.shields.io/badge/License-MIT-red?style=for-the-badge" alt="License" />
</div>

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes. 
> Solutions are provided for learning, practice, and reference only. 
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given two **sorted** arrays `a[]` and `b[]`, where each array may contain duplicate elements, return the elements in the **intersection** of the two arrays in **sorted** order.

> **Note:** Intersection of two arrays can be defined as the set containing distinct common elements that are present in both of the arrays.

---

## ⚙️ Constraints

> - `1 ≤ a.size(), b.size() ≤ 10^5`
> - `-10^9 ≤ a[i], b[i] ≤ 10^9`

---

## 💡 Examples

**Input:** `a[] = [1, 1, 2, 2, 2, 4]`, `b[] = [2, 2, 4, 4]`
**Output:** `[2, 4]`
**Explanation:** Distinct common elements in both the arrays are: 2 and 4.

**Input:** `a[] = [1, 2]`, `b[] = [3, 4]`
**Output:** `[]`
**Explanation:** No common elements.

<details>
<summary><b>📖 Example Breakdown</b></summary>

**Input:** `a[] = [1, 2, 3]`, `b[] = [1, 2, 3]`

1. We evaluate the first element of both arrays: `a[0] = 1`, `b[0] = 1`. Since they are equal, `1` is added to our result and we skip past any duplicates of `1`.
2. Move to `a[1] = 2` and `b[1] = 2`. They are equal, add `2` to result.
3. Move to `a[2] = 3` and `b[2] = 3`. They are equal, add `3` to result.
4. Arrays are exhausted. 
**Final Output:** `[1, 2, 3]`
</details>

---

## 💻 Solution Approaches

### 1️⃣ Naive Approach (Nested Loops)
**Intuition:** The most basic way is to check each element of the first array against the second array. We can use the sorted property to skip duplicates in the first array to ensure distinct elements in the final answer.

```cpp
// Intuition: The simplest way is to check each element of the first array against all elements of the second array, while ensuring we skip duplicates to maintain distinct elements in our result.
// Approach: Traverse the first array `a`, skipping consecutive duplicates. For each distinct element, traverse the second array `b` to find a match. If a match is found, add it to the result and break the inner loop.
// Time Complexity: O(n * m), where n and m are the sizes of arrays `a` and `b`. In the worst case, for each element in `a`, we iterate through all elements in `b`.
// Space Complexity: O(1) auxiliary space, as we only use a result vector to store the final intersection.

class Solution {
  public:
    // Function to find the intersection of two arrays
    // It returns a vector containing the common elements
    vector<int> intersection(vector<int>& a, vector<int>& b) {
        vector<int> res; 
        int m = a.size(); 
        int n = b.size(); 
        
        for(int i = 0; i < m; i++) {
          
            // Note that duplicates must be 
            // consecutive in a sorted array
            // Skip consecutive duplicates in a[]
            if(i > 0 && a[i - 1] == a[i])
                continue;
            
            // Since we are only searchin distint
            // elements of a[] in b[] and we break as 
            // soon we find a match, we get only
            // distinct elements in result
            for(int j = 0; j < n; j++) {
                // Match found, add to result and break
                if(a[i] == b[j]) {
                    res.push_back(a[i]);
                    break; 
                }
            }
        }
        return res;
    }
};

/*
*
* Dry Run
* Input: a = [1, 2, 2, 3], b = [2, 2, 4]
* Step 1: i = 0, a[0] = 1. Inner loop checks b. No 1 found.
* Step 2: i = 1, a[1] = 2. Inner loop checks b. b[0] = 2. Match found! res = [2]. Break inner loop.
* Step 3: i = 2, a[2] = 2. a[1] == a[2], so skip duplicate.
* Step 4: i = 3, a[3] = 3. Inner loop checks b. No 3 found.
* Output: [2]
*
*/
````

### 2️⃣ Better Approach (Using HashSet)

**Intuition:** We can optimize the look-up time by storing the elements of the first array in a HashSet, which allows us to find common elements efficiently.

```cpp
// Intuition: We can quickly check for common elements by storing the elements of the first array in a Hash Set, which allows O(1) average time complexity for lookups.
// Approach: Insert all elements of array `a` into an unordered_set. Iterate through array `b`. If an element is found in the set, add it to the result and remove it from the set to avoid duplicates.
// Time Complexity: O(n + m), where n and m are the sizes of arrays `a` and `b`. Inserting elements takes O(n) and looking them up takes O(m) time.
// Space Complexity: O(n), as we store the unique elements of array `a` in an unordered_set.

class Solution {
  public:
    vector<int> intersection(vector<int>& a, vector<int>& b) {
        // Store all elements of 'a' in a set to remove duplicates and allow O(1) lookups
        unordered_set<int> st(a.begin(), a.end());
        vector<int> res;
        
        // Iterate through 'b' to find common elements
        for(int num : b) {
            // If element from 'b' is present in the set
            if(st.count(num)) {
                res.push_back(num); // Add to the result
                st.erase(num);      // Erase from set to prevent duplicate entries in result
            }
        }
        
        // Since 'b' is processed in its sorted order, 'res' naturally stays sorted
        return res;
    }
};

/*
*
* Dry Run
* Input: a = [1, 1, 2], b = [2, 3]
* Set Initialization: st = {1, 2}
* Loop b: 
* - num = 2: st.count(2) is true -> res = [2] -> st.erase(2) -> st = {1}
* - num = 3: st.count(3) is false
* Output: [2]
*
*/
```

### 3️⃣ Expected Optimized Approach (Merge Step / Two Pointers)

**Intuition:** Since both arrays are already sorted, we can process them sequentially using two pointers. This perfectly mimics the merge process of the Merge Sort algorithm and gives us optimal time and space.

```cpp
// Intuition: Since both arrays are already sorted, we can use two pointers traversing both arrays simultaneously. This mimics the merge step of Merge Sort and avoids redundant comparisons.
// Approach: Maintain two pointers `i` and `j` for arrays `a` and `b`. Skip any duplicate elements in `a`. Compare `a[i]` and `b[j]`. If `a[i] < b[j]`, increment `i`. If `a[i] > b[j]`, increment `j`. If they are equal, add to the result and increment both.
// Time Complexity: O(n + m), where n and m are the sizes of the arrays. We traverse each array at most once.
// Space Complexity: O(1) auxiliary space, as no extra space is used except the result vector.

class Solution {
  public:
    vector<int> intersection(vector<int>& a,  vector<int>& b) {
        vector<int> res; 
        int m = a.size();
        int n = b.size();
      
        int i = 0, j = 0;    
        
        // Traverse both arrays simultaneously using two pointers
        while(i < m && j < n) {
          
            // Skip duplicate elements in the first array
            if(i > 0 && a[i - 1] == a[i]) {
                i++;
                continue;
            }
          
            // Skip the smaller element to catch up
            if(a[i] < b[j]) {
                i++;
            }
            else if(a[i] > b[j]) {
                j++;
            }
            // If equal, add to result and move both pointers
            else {
                res.push_back(a[i]);
                i++;
                j++;
            }
        }
        return res; 
    }
};

/*
*
* Dry Run
* Input: a = [1, 1, 2, 4], b = [2, 2, 4]
* Initial: i = 0, j = 0
* Step 1: a[0](1) < b[0](2) -> i++ (i=1)
* Step 2: a[1] == a[0], duplicate skipped -> i++ (i=2)
* Step 3: a[2](2) == b[0](2) -> res = [2], i++ (i=3), j++ (j=1)
* Step 4: a[3](4) > b[1](2) -> j++ (j=2)
* Step 5: a[3](4) == b[2](4) -> res = [2, 4], i++ (i=4), j++ (j=3)
* Loop ends.
* Output: [2, 4]
*
*/
```

-----

## 🎯 Key Insights

  - **Sorted Property Advantage:** Because the inputs are sorted, we don't need a heavy nested loop or extra memory (like HashMaps/Sets) for mapping. Using the two-pointer technique scales seamlessly in `O(n+m)` time.
  - **Handling Duplicates:** Managing duplicates inline by checking `if(i > 0 && a[i-1] == a[i])` allows us to bypass redundant checks without mutating the array or utilizing additional space.

-----

## 🔍 Further Exploration

  - **Union of Two Sorted Arrays:** Try solving the union problem using a similar two-pointer technique.
  - **Intersection of Two Unsorted Arrays:** How would you modify the HashSet approach if the given arrays were *not* sorted?

-----

## 🔗 References

  - **Original Problem:** [Intersection of Two Sorted Arrays - GeeksforGeeks](https://www.geeksforgeeks.org/problems/intersection-of-two-sorted-arrays-with-duplicate-elements/1)

-----

## 👤 Author

**GitHub:** [imnilesh18](https://github.com/imnilesh18)

-----

## 🏷️ Tags

`Array` `Two Pointers` `HashSet` `GeeksforGeeks` `Data Structures`