class Solution {
public:
int minJumps(vector<int> &arr){
int n = arr.size();

        if (arr[0] == 0)
            return -1;

        int maxReach = 0;
        int currReach = 0;
        int jump = 0;

        for (int i = 0; i < n; i++){
            maxReach = max(maxReach, i + arr[i]);
            if (maxReach >= n - 1){
                return jump + 1;
            }

            // Increment the Jump as we reached the
            // Current Reachable index
            if (i == currReach){

                // If Max reach is same as current index
                // then we can not jump further
                if (maxReach == i){
                    return -1;
                }

                // If maxReach > current index then increment
                // jump and update current reachable index
                else{
                    jump++;
                    currReach = maxReach;
                }
            }
        }

        return -1;
    }

};
