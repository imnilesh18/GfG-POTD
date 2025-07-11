/*
 * GfG Link: https://www.geeksforgeeks.org/problems/meeting-rooms-iii/1
 *
 * Meeting Rooms III
 *
 * Difficulty: Hard Accuracy: 64.19% Submissions: 1K+ Points: 8
 *
 * You are given an integer n representing the number of rooms numbered from 0 to n - 1. Additionally, you are given a 2D integer array meetings[][] where meetings[i] = [starti, endi] indicates that a meeting is scheduled during the half-closed time interval [starti, endi). All starti values are unique.
 *
 * Meeting Allocation Rules:
 * When a meeting starts, assign it to the available room with the smallest number.
 * If no rooms are free, delay the meeting until the earliest room becomes available. The delayed meeting retains its original duration.
 * When a room becomes free, assign it to the delayed meeting with the earliest original start time.
 * Determine the room number that hosts the most meetings. If multiple rooms have the same highest number of meetings, return the smallest room number among them.
 *
 * Examples:
 *
 * Input: n = 2, meetings[][] = [[0, 6], [2, 3], [3, 7], [4, 8], [6, 8]]
 * Output: 1
 * Explanation: Time 0: Both rooms available. [0,6] starts in room 0.
 * Time 2: Room 0 busy until 6. Room 1 available. [2,3] starts in room 1.
 * Time 3: Room 1 frees up. [3,7] starts in room 1.
 * Time 4: Both rooms busy. [4,8] is delayed.
 * Time 6: Room 0 frees up. Delayed [4,8] starts in room 0 [6,10).
 * Time 6: [6,8] arrives but both rooms busy. It’s delayed.
 * Time 7: Room 1 frees up. Delayed [6,8] starts in room 1 [7,9).
 * Meeting counts: [2, 3]
 *
 * Input: n = 4, meetings[][] = [[0, 8], [1, 4], [3, 4], [2, 3]
 * Output: 2
 * Explanation: Time 0: All rooms available. [0,8] starts in room 0.
 * Time 1: Room 0 busy until 8. Rooms 1, 2, 3 available. [1,4] starts in room 1.
 * Time 2: Rooms 0 and 1 busy. Rooms 2, 3 available. [2,3] starts in room 2.
 * Time 3: Room 2 frees up. [3,4] starts in room 2.
 * Meeting counts: [1, 1, 2, 0]
 *
 * Constraints:
 * 1 ≤ n ≤ 10^4
 * 1 ≤ meetings.size() ≤ 10^4
 * meetings[i].size() == 2
 * 0 ≤ starti < endi ≤ 10^4
 */

/************************************************************ C++ ************************************************/

// Approach: Use two priority queues — one min-heap for available rooms and one for occupied rooms (by end time).
// Meetings are sorted by start time. We allocate the smallest room available or delay if none are free.
// Use 64-bit arithmetic for end-times to avoid overflow when delaying meetings.
// Time Complexity: O(m log n + m log m) where m = number of meetings, n = number of rooms.
//    – Sorting meetings: O(m log m)
//    – Heap operations: O(m log n)
// Space Complexity: O(n + m) for room tracking, counts, and priority queues.
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Min-heap to store occupied rooms with their end time {endTime, room}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> occupied;
        // Min-heap to store available room numbers
        priority_queue<int, vector<int>, greater<>> available;
        // Vector to count how many meetings each room hosts
        vector<int> cnt(n, 0);

        // Initially all rooms are available
        for (int i = 0; i < n; i++) {
            available.push(i);
        }

        // Sort meetings based on start time
        sort(meetings.begin(), meetings.end());

        for (auto& m : meetings) {
            long long start = m[0];
            long long end   = m[1];

            // Free up rooms that have completed their meetings before the current start time
            while (!occupied.empty() && occupied.top().first <= start) {
                available.push(occupied.top().second);
                occupied.pop();
            }

            if (!available.empty()) {
                // If there's an available room, assign it
                int room = available.top();
                available.pop();
                occupied.emplace(end, room);  // Assign the room until current meeting's end
                cnt[room]++;                  // Increment meeting count for the room
            } else {
                // No room available, delay the meeting until earliest room becomes free
                pair<long long, int> top         = occupied.top();
                long long            earliestEnd = top.first;
                int room = top.second;
                occupied.pop();

                long long newEnd = earliestEnd + (end - start);
                occupied.emplace(newEnd, room);  // Delay but retain original duration
                cnt[room]++;                     // Increment meeting count for the room
            }
        }

        // Find the room with the maximum number of meetings (smallest index on tie)
        int result = 0;
        for (int i = 1; i < n; i++) {
            if (cnt[i] > cnt[result]) {
                result = i;
            }
        }

        return result;
    }
};

/*
 * Dry Run
 * Input: n = 2, meetings = [[0,6],[2,3],[3,7],[4,8],[6,8]]
 *
 * Initial:
 * - Available rooms: [0, 1] (min-heap)
 * - Occupied rooms: [] (min-heap of {endTime, room})
 * - Meeting counts: [0, 0]
 *
 * Step 1: Meeting [0, 6]
 * - Start time = 0
 * - Available: [0,1] → pick room 0
 * - Assign until end=6 → occupied.push({6,0})
 * - Counts: [1, 0]
 *
 * Step 2: Meeting [2, 3]
 * - Start time = 2
 * - occupied.top().first=6 > 2 → no rooms freed
 * - Available: [1] → pick room 1
 * - Assign until end=3 → occupied.push({3,1})
 * - Counts: [1, 1]
 *
 * Step 3: Meeting [3, 7]
 * - Start time = 3
 * - occupied.top().first=3 ≤ 3 → free room 1 (pop {3,1}, available.push(1))
 * - Available: [1] → pick room 1
 * - Assign until end=7 → occupied.push({7,1})
 * - Counts: [1, 2]
 *
 * Step 4: Meeting [4, 8]
 * - Start time = 4
 * - occupied.top().first=6 > 4 → no rooms freed
 * - Available: [] → delay meeting
 *   * Pop earliest {6,0}
 *   * Duration = 8 - 4 = 4
 *   * newEnd = 6 + 4 = 10
 *   * occupied.push({10,0})
 *   * Counts: [2, 2]
 *
 * Step 5: Meeting [6, 8]
 * - Start time = 6
 * - occupied.top().first=7 > 6 → no rooms freed
 * - Available: [] → delay meeting
 *   * Pop earliest {7,1}
 *   * Duration = 8 - 6 = 2
 *   * newEnd = 7 + 2 = 9
 *   * occupied.push({9,1})
 *   * Counts: [2, 3]
 *
 * Final:
 * - Meeting counts: [2, 3]
 * - Room 1 handled the most meetings → return 1
 */

/************************************************************ JAVA ************************************************/

// Approach: Use two priority queues — one min-heap for available rooms and one for occupied rooms (by end time).
// Meetings are sorted by start time. We allocate the smallest room available or delay if none are free.
// Use 64-bit long for end‑times to avoid overflow when delaying meetings.
// Time Complexity: O(m log n + m log m) where m = number of meetings, n = number of rooms.
//    – Sorting meetings: O(m log m)
//    – Heap operations: O(m log n)
// Space Complexity: O(n + m) for room tracking, counts, and priority queues.
class Solution {
    public int mostBooked(int n, int[][] meetings) {
        // Min-heap to store occupied rooms as [endTime, room]
        PriorityQueue<long[]> occupied = new PriorityQueue<>(
            (a, b)->a[0] != b[0] ? Long.compare(a[0], b[0]) : Long.compare(a[1], b[1])
            );
        // Min-heap to store available room numbers
        PriorityQueue<Integer> available = new PriorityQueue<>();
        // Array to count how many meetings each room hosts
        int[] cnt = new int[n];

        // Initially all rooms are available
        for (int i = 0; i < n; i++) {
            available.offer(i);
        }

        // Sort meetings based on start time
        Arrays.sort(meetings, (a, b)->Integer.compare(a[0], b[0]));

        for (int[] m : meetings) {
            long start = m[0];
            long end   = m[1];

            // Free up rooms that have completed their meetings before current start
            while (!occupied.isEmpty() && occupied.peek()[0] <= start) {
                available.offer((int)occupied.poll()[1]);
            }

            if (!available.isEmpty()) {
                // If there's an available room, assign it
                int room = available.poll();
                occupied.offer(new long[]{ end, room });
                cnt[room]++;  // Increment meeting count for the room
            } else {
                // No room available, delay the meeting until earliest room becomes free
                long[] top = occupied.poll();
                long earliestEnd = top[0];
                int  room        = (int)top[1];
                long newEnd      = earliestEnd + (end - start);
                occupied.offer(new long[]{ newEnd, room });
                cnt[room]++;   // Increment meeting count for the room
            }
        }

        // Find the room with the maximum number of meetings (smallest index on tie)
        int result = 0;
        for (int i = 1; i < n; i++) {
            if (cnt[i] > cnt[result]) {
                result = i;
            }
        }
        return result;
    }
}

/*
 * Dry Run
 * Input: n = 2, meetings = [[0,6],[2,3],[3,7],[4,8],[6,8]]
 *
 * Initial:
 * - Available rooms: [0, 1] (min-heap)
 * - Occupied rooms: [] (min-heap of [endTime, room])
 * - Meeting counts: [0, 0]
 *
 * Step 1: Meeting [0, 6]
 * - start = 0
 * - occupied empty → no rooms freed
 * - available = [0,1] → poll room 0
 * - occupied.offer([6,0])
 * - counts = [1, 0]
 *
 * Step 2: Meeting [2, 3]
 * - start = 2
 * - occupied.peek()[0]=6 > 2 → no rooms freed
 * - available = [1] → poll room 1
 * - occupied.offer([3,1])
 * - counts = [1, 1]
 *
 * Step 3: Meeting [3, 7]
 * - start = 3
 * - occupied.peek()[0]=3 ≤ 3 → free room 1 (poll [3,1], available.offer(1))
 * - available = [1] → poll room 1
 * - occupied.offer([7,1])
 * - counts = [1, 2]
 *
 * Step 4: Meeting [4, 8]
 * - start = 4
 * - occupied.peek()[0]=6 > 4 → no rooms freed
 * - available empty → delay meeting
 *   * poll earliest [6,0]
 *   * duration = 8 - 4 = 4
 *   * newEnd = 6 + 4 = 10
 *   * occupied.offer([10,0])
 *   * counts = [2, 2]
 *
 * Step 5: Meeting [6, 8]
 * - start = 6
 * - occupied.peek()[0]=7 > 6 → no rooms freed
 * - available empty → delay meeting
 *   * poll earliest [7,1]
 *   * duration = 8 - 6 = 2
 *   * newEnd = 7 + 2 = 9
 *   * occupied.offer([9,1])
 *   * counts = [2, 3]
 *
 * Final:
 * - Meeting counts: [2, 3]
 * - Room 1 handled the most meetings → return 1
 */
