#include <bits/stdc++.h>
using namespace std;

// Left rotate an element by d places
// [1, 2, 3, 4, 5, 6, 7] d=2
// [3, 4, 5, 6, 7, 1, 2] -> result

// Brute Approach
// Storing starting element in temp array
// Modifying existing nums 
// Adding stored elements from temp array to nums

// TC = O(d + (N-d) + d) = O(d + N) = O(2N) at most 
// SC = O(N)
/*
void leftRotate(vector<int>&nums, int d){
    vector<int>temp;

    int n = nums.size();
    d = d%n;

    // Storing starting elements in new temp
    for(int i=0; i<d; i++){
        temp.push_back(nums[i]);
    }

    // Modifying nums
    for(int i=0; i<n-d; i++){
        nums[i] = nums[i+d];
    }

    int l = d;
    // Adding remaining
    for(int i=0; i<d; i++){
        nums[n-l] = temp[i];
        l--;
    }
    
}
*/

void leftRotate(vector<int>&nums, int d){
    int n = nums.size();
    d = d%n;

    // Reverse first d elements
    reverse(nums.begin(), nums.begin()+d);
    // Reverse Next set of elements
    reverse(nums.begin()+d, nums.end());

    // We now have entire result array as reversed
    // Reverse entire array
    reverse(nums.begin(), nums.end());
}


int main(){
    vector<int>nums;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter array elements: \n";

    int a;

    for(int i=0; i<n; i++){
        cin >> a;
        nums.push_back(a);
    }

    int d;
    cout << "Enter d: ";
    cin >> d;

    leftRotate(nums, d);

    for(auto it:nums){
        cout << it << " ";
    }

    return 0;
}