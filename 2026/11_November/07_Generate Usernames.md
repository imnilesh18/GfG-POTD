# 🏷️ Generate Usernames

![GeeksForGeeks](https://img.shields.io/badge/GeeksForGeeks-298D46?style=for-the-badge&logo=geeksforgeeks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Easy-brightgreen?style=for-the-badge)
![Accuracy](https://img.shields.io/badge/Accuracy-68.82%25-blue?style=for-the-badge)
![Points](https://img.shields.io/badge/Points-2-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-red?style=for-the-badge)

> ⚠️ **Educational Use Only:**
> This repository and its content are intended solely for educational purposes.
> Solutions are provided for learning, practice, and reference only.
> Problem statement and test cases are based on the GeeksforGeeks problem.

---

## 📝 Problem Statement

Given an array of strings `arr[]`. The array represents the first names of users. Your task is to generate a unique username for each entry in the order it appears.

* Initially, consider all usernames present in the input array as **reserved**.
* If a username has not already been assigned to any previous user, keep it **unchanged**.
* Otherwise, append the **smallest positive integer suffix** that produces a username that has not been reserved or assigned to any previous user.

Return the array of generated usernames.

---

## 💡 Examples

### Example 1
```text
Input: arr[] = ["aba", "ab", "aba", "aba", "ab"]
Output: ["aba", "ab", "aba1", "aba2", "ab1"]

```

### Example 2

```text
Input: arr[] = ["a", "a", "a1", "a"]
Output: ["a", "a2", "a1", "a3"]

```

1. Initially, `"a"` and `"a1"` are reserved in the global pool.
2. **First `"a"**`: Retains its name since it's the first occurrence. Output: `["a"]`.
3. **Second `"a"**`: `"a1"` is already reserved. The smallest available username is `"a2"`. Output: `["a", "a2"]`.
4. **First `"a1"**`: Retains its name since it's the first time we are processing `"a1"` as a base string. Output: `["a", "a2", "a1"]`.
5. **Third `"a"**`: `"a1"` and `"a2"` are already used. The next available is `"a3"`. Output: `["a", "a2", "a1", "a3"]`.

### Example 3

```text
Input: arr[] = ["aba1", "aba", "aba"]
Output: ["aba1", "aba", "aba2"]

```

---

## ⚙️ Constraints

* `1 ≤ |arr| ≤ 10^3`
* `1 ≤ |arr[i]| ≤ 10^2`
* `arr` consists of English alphabets and digits.

---

## 💻 Solution Approach

### C++ Optimized Implementation

```cpp
// Intuition: We need to assign unique usernames based on the input array. Since all initial names in the array are considered reserved, we track them in a set. First occurrences retain their names, while subsequent occurrences get the smallest available integer suffix.
// Approach: 
// 1. Insert all elements of the input array into a hash set to mark them as initially reserved.
// 2. Iterate over the input array and maintain a frequency map for the assigned base names.
// 3. If a name is encountered for the first time, keep it as is and increment its frequency.
// 4. If a name repeats, find the next available integer suffix using a second map to track the current suffix counter for that base name.
// 5. Add the newly generated username to the reserved set and append it to the result array.
// Time Complexity: O(N * M) where N is the size of the array and M is the maximum string length. Checking set membership and string concatenation takes O(M) time on average.
// Space Complexity: O(N * M) to store the hash set, hash maps, and the resulting vector of strings.

class Solution {
  public:
    vector<string> generateUsernames(vector<string> arr) {
        // mark all initial names as reserved globally
        unordered_set<string> used(arr.begin(), arr.end());

        unordered_map<string, int> assigned_count;
        unordered_map<string, int> next_suffix;
        vector<string> ans;

        for (string& s : arr) {
            // first occurrence retains its original name
            if (assigned_count[s] == 0) {
                ans.push_back(s);
                assigned_count[s] = 1;
            } 
            // subsequent occurrences require a numeric suffix
            else {
                int k = next_suffix.count(s) ? next_suffix[s] : 1;

                // increment suffix until an unreserved name is found
                while (used.count(s + to_string(k))) {
                    k++;
                }

                string new_name = s + to_string(k);
                ans.push_back(new_name);

                // reserve the newly generated name
                used.insert(new_name);

                // update suffix counter for future lookups
                next_suffix[s] = k + 1;
            }
        }

        return ans;
    }
};

/*
Dry Run

Input: arr = ["a", "a", "a1", "a"]

Initial State:
used = {"a", "a1"}
ans = []

Processing "a" (index 0):
First time seeing "a" as base string
Add "a" to ans
ans = ["a"]

Processing "a" (index 1):
Repeated occurrence of "a"
Check suffix 1: "a1" is in used
Check suffix 2: "a2" is not in used
Add "a2" to ans and insert into used
ans = ["a", "a2"]
used = {"a", "a1", "a2"}

Processing "a1" (index 2):
First time seeing "a1" as base string
Add "a1" to ans
ans = ["a", "a2", "a1"]

Processing "a" (index 3):
Repeated occurrence of "a"
Resume checking suffixes for "a" from 3
Check suffix 3: "a3" is not in used
Add "a3" to ans and insert into used
ans = ["a", "a2", "a1", "a3"]

Output: ["a", "a2", "a1", "a3"]
*/

```

---

## 🧠 Key Insights

* **Pre-population is Crucial:** By tossing the original array into an `unordered_set` right at the start, we immediately solve the edge case where a generated username might accidentally collide with a string that appears much later in the input list.
* **State Tracking:** Using a dedicated `next_suffix` map ensures we don't start counting from `1` every time a highly-repeated name appears. If `"aba"` appears 50 times, we resume checking from the last known good suffix rather than continuously looping from `1`, maintaining amortized efficiency.

---

## 🔍 Further Exploration

* **Design Hit Counter**
* **Design a File System**
* **Design In-Memory File System**

---

## 🔗 References

* **GeeksforGeeks Problem:** [Generate Usernames](https://www.geeksforgeeks.org/problems/new-registration-system--150419/1)

---

## 👨‍💻 Author

**[imnilesh18](https://github.com/imnilesh18)**

---

## 🏷️ Tags

* `Strings`
* `Hash Set`
* `Hash Map`
* `GeeksforGeeks`