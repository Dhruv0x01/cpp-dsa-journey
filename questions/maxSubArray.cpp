#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> maxSubArray(vector<int>&nums){
    int result = INT_MIN;
    int i=0, sum = 0, n = nums.size();
    int start=0;
    int ansStart = -1, ansEnd = -1;
    

    while(i<n){
        if(sum == 0) start = i;

        sum += nums[i];

        if(sum > result){
            result = sum;
            ansStart = start;
            ansEnd = i;
        }

        if(sum < 0){
            sum = 0;
        }
        i++;
    }
    return {result, ansStart, ansEnd};
}

int main(){
    vector<int> nums = {-2, -3, 4, -1, -2, 1, 5, -3};

    auto [result, ansStart, ansEnd] = maxSubArray(nums);

    for(int i=ansStart; i<=ansEnd; i++){
        cout << nums[i] << " ";
    }

    return 0;

}