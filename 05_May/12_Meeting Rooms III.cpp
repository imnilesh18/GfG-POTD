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

// Approach: Use two priority queues — one min-heap for available rooms and one for occupied rooms (by end time). Meetings are sorted by start time. We allocate the smallest room available or delay if none are free.
// Time Complexity: O(m log n + m log m) where m = number of meetings, n = number of rooms. Sorting meetings takes O(m log m), and we do O(log n) operations for each meeting.
// Space Complexity: O(n + m) for room tracking, counts, and priority queues.
class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Min-heap to store occupied rooms with their end time {endTime, room}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> occupied;

        // Min-heap to store available room numbers
        priority_queue<int, vector<int>, greater<int>> available;

        // Vector to count how many meetings each room hosts
        vector<int> cnt(n, 0);

        // Initially all rooms are available
        for (int i = 0; i < n; i++) {
            available.push(i);
        }

        // Sort meetings based on start time
        sort(meetings.begin(), meetings.end());

        for (auto& m : meetings) {
            int start = m[0];
            int end   = m[1];

            // Free up rooms that have completed their meetings before the current start time
            while (!occupied.empty() && occupied.top().first <= start) {
                available.push(occupied.top().second);
                occupied.pop();
            }

            if (!available.empty()) {
                // If there's an available room, assign it
                int room = available.top();
                available.pop();
                occupied.push({ end, room }); // Assign the room until current meeting's end
                cnt[room]++;                  // Increment meeting count for the room
            } else {
                // No room available, delay the meeting until earliest room becomes free
                int endTime = occupied.top().first;
                int room    = occupied.top().second;
                occupied.pop();
                occupied.push({ endTime + (end - start), room }); // Delay but retain original duration
                cnt[room]++;                                      // Increment meeting count for the room
            }
        }

        int maxCnt = 0;
        int result = 0;

        // Find the room with the maximum number of meetings
        for (int i = 0; i < n; i++) {
            if (cnt[i] > maxCnt) {
                maxCnt = cnt[i];
                result = i;
            }
        }

        return result;
    }
};

/*
 *
 * Dry Run
 * Input: n = 2, meetings = [[0,6],[2,3],[3,7],[4,8],[6,8]]
 * Step-by-step explanation:
 *
 * Initial:
 * - Available rooms: [0, 1] (min-heap)
 * - Occupied rooms: [] (min-heap of {endTime, room})
 * - Meeting counts: [0, 0]
 *
 * Step 1: Meeting [0, 6]
 * - Start time = 0
 * - Available rooms: [0, 1] → pick room 0
 * - End time = 6 → push (6, 0) to occupied
 * - Counts: [1, 0]
 *
 * Step 2: Meeting [2, 3]
 * - Start time = 2
 * - Check if any rooms are free before 2 → (6, 0) not yet done
 * - Available rooms: [1] → pick room 1
 * - End time = 3 → push (3, 1) to occupied
 * - Counts: [1, 1]
 *
 * Step 3: Meeting [3, 7]
 * - Start time = 3
 * - Check if any rooms are free before 3 → (3, 1) frees now → push room 1 to available
 * - Available: [1] → pick room 1
 * - End time = 7 → push (7, 1) to occupied
 * - Counts: [1, 2]
 *
 * Step 4: Meeting [4, 8]
 * - Start time = 4
 * - Check if any rooms are free before 4 → (6, 0), (7, 1) → none frees
 * - Available: [] → delay meeting until earliest end time (6)
 * - Duration = 4 (8 - 4)
 * - New start = 6, new end = 10
 * - Reuse room 0 → pop (6, 0), push (10, 0)
 * - Counts: [2, 2]
 *
 * Step 5: Meeting [6, 8]
 * - Start time = 6
 * - Check if any rooms are free before 6 → (7, 1), (10, 0) → none free
 * - Available: [] → delay meeting until earliest end time (7)
 * - Duration = 2 (8 - 6)
 * - New start = 7, new end = 9
 * - Reuse room 1 → pop (7, 1), push (9, 1)
 * - Counts: [2, 3]
 *
 * Final:
 * - Meeting counts: [2, 3]
 * - Room 1 handled the most meetings → return 1
 *
 */

/************************************************************ JAVA ************************************************/

// Approach: Use two priority queues — one min-heap for available rooms and one for occupied rooms (by end time). Meetings are sorted by start time. We allocate the smallest room available or delay if none are free.
// Time Complexity: O(m log n + m log m) where m = number of meetings, n = number of rooms. Sorting meetings takes O(m log m), and we do O(log n) operations for each meeting.
// Space Complexity: O(n + m) for room tracking, counts, and priority queues.
class Solution {
    public int mostBooked(int n, int[][] meetings) {
        // Min-heap to store occupied rooms by endTime; if tie, smaller room number first
        PriorityQueue<long[]> occupied = new PriorityQueue<>(
            (a, b)->a[0] != b[0] ? Long.compare(a[0], b[0]) : Integer.compare((int)a[1], (int)b[1])
            );

        // Min-heap for available room numbers
        PriorityQueue<Integer> available = new PriorityQueue<>((a, b)->a - b);

        int[] cnt = new int[n]; // Meeting count per room

        // All rooms initially available
        for (int i = 0; i < n; i++) {
            available.offer(i);
        }

        // Sort meetings by start time
        Arrays.sort(meetings, (a, b)->a[0] - b[0]);

        for (int[] m : meetings) {
            int start = m[0], end = m[1];

            // Free up rooms that are done before current meeting starts
            while (!occupied.isEmpty() && occupied.peek()[0] <= start) {
                available.offer((int)occupied.poll()[1]);
            }

            if (!available.isEmpty()) {
                // Assign meeting to earliest available room
                int room = available.poll();
                occupied.offer(new long[]{ end, room });
                cnt[room]++;
            } else {
                // Delay meeting to when earliest room is available
                long[] top = occupied.poll();
                long newEnd = top[0] + (end - start);
                int  room   = (int)top[1];
                occupied.offer(new long[]{ newEnd, room });
                cnt[room]++;
            }
        }

        // Find the room with the most meetings (smallest index if tie)
        int max = 0, result = 0;
        for (int i = 0; i < n; i++) {
            if (cnt[i] > max) {
                max    = cnt[i];
                result = i;
            }
        }

        return result;
    }
}

/*
 *
 * Dry Run
 * Input: n = 2, meetings = [[0,6],[2,3],[3,7],[4,8],[6,8]]
 * Step-by-step explanation:
 *
 * Initial:
 * - Available rooms: [0, 1] (min-heap)
 * - Occupied rooms: [] (min-heap of {endTime, room})
 * - Meeting counts: [0, 0]
 *
 * Step 1: Meeting [0, 6]
 * - Start time = 0
 * - Available rooms: [0, 1] → pick room 0
 * - End time = 6 → push (6, 0) to occupied
 * - Counts: [1, 0]
 *
 * Step 2: Meeting [2, 3]
 * - Start time = 2
 * - Check if any rooms are free before 2 → (6, 0) not yet done
 * - Available rooms: [1] → pick room 1
 * - End time = 3 → push (3, 1) to occupied
 * - Counts: [1, 1]
 *
 * Step 3: Meeting [3, 7]
 * - Start time = 3
 * - Check if any rooms are free before 3 → (3, 1) frees now → push room 1 to available
 * - Available: [1] → pick room 1
 * - End time = 7 → push (7, 1) to occupied
 * - Counts: [1, 2]
 *
 * Step 4: Meeting [4, 8]
 * - Start time = 4
 * - Check if any rooms are free before 4 → (6, 0), (7, 1) → none frees
 * - Available: [] → delay meeting until earliest end time (6)
 * - Duration = 4 (8 - 4)
 * - New start = 6, new end = 10
 * - Reuse room 0 → pop (6, 0), push (10, 0)
 * - Counts: [2, 2]
 *
 * Step 5: Meeting [6, 8]
 * - Start time = 6
 * - Check if any rooms are free before 6 → (7, 1), (10, 0) → none free
 * - Available: [] → delay meeting until earliest end time (7)
 * - Duration = 2 (8 - 6)
 * - New start = 7, new end = 9
 * - Reuse room 1 → pop (7, 1), push (9, 1)
 * - Counts: [2, 3]
 *
 * Final:
 * - Meeting counts: [2, 3]
 * - Room 1 handled the most meetings → return 1
 *
 */
