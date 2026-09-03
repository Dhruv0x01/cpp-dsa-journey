#include <bits/stdc++.h>
using namespace std;

// Brute Force
// TC = O(N^2)
// SC = O(1)
/*
int longestSubarray(vector<int>& arr, int K){
    int result = 0;
    int n = arr.size();
    for(int i=0; i<n; i++){
        int sum = 0;
        for(int j=i; j<n; j++){
            sum += arr[j];
            if(sum == K){
                result = max(result, j-i+1);
            }
        }
    }
    return result;
}
*/

/*
// Better solution
// (Optimal also if array contains negatives, zeroes and positives)
int longestSubarray(vector<int>& arr, long long k){
    int n = arr.size();

    // prefixSum as key and it's index as value
    map<long long, int>sumMap;

    long long prefixSum = 0;
    int maxLen = 0;

    for(int i=0; i<n; i++){
        prefixSum += arr[i];

        // Here entire prefix sums to K
        // it's length would be start to current index
        // 0 to i would be area that sums to k
        // Length = i-0+1
        if(prefixSum == k){
            maxLen = max(maxLen, i+1);
        }

        // We are searching for x-k in any of the prior prefixSum [x means current prefixSum]
        // Because if we find then +1 from that index to current index sums to k
        // Our key is prefixSum and value is index
        // sumMap[rem] gave index where we got the prefix sum = x-k
        // Hence our k sum will be between sumMap[rem]+1 to currentIndex
        // length = currentIndex - (sumMap[rem]+1) + 1
        long long rem = prefixSum - k;
        if(sumMap.find(rem) != sumMap.end()){
            int len = i-(sumMap[rem]+1)+1;
            maxLen = max(len, maxLen); // Only putting the bigger length 
        }

        // Hashing current prefixSum as key and it's index as value
        if(sumMap.find(prefixSum) == sumMap.end()){
            sumMap[prefixSum] = i;
        }
        // We are only hashing if the prefix sum doesn't exist already
        // Because if it exist already and getting updated again means we encountered 0 element which doesn't change the prefix sum
        // and for length to be longest we must get left most prefixSum
        // [4, 0, 0, 0, 0, 2, 1, 10, 12] and k=3

        // Index 0 iteration
        // -> prefixSum = 4 index = 0
        // hash = [4:0]

        // Index 1 iteration
        // prefixSum = 4, index = 1
        // hash = [4:1]

        // so on to [4: 4]

        // Index 5 iteration
        // prefixSum = 6, index = 5
        // 6-3 = 3 and 3 doesn't exist in map
        // map = [4:4, 6:5]

        // Index 6 iteration
        // prefixSum = 7, index = 6
        // 7-3 = 4, yes 4 exist in map but since index kept on changing even when prefixSum didn't change due to 0
        // We now have the rightmost summation 4 and length is'nt longest this way
        // So for longest we need leftmost 4
        // so if we already have a prefixSum in the hashMap then it's index(value) won't be updated

        
    }
    return maxLen;
}
*/

// Optimal Solution
// 2 pointer and Greedy approach
// Only when array has zeroes and positives only
int longestSubarray(vector<int>& arr, long long k){
    int n = arr.size();
    int maxLen = 0, left = 0, right = 0;
    long long sum = arr[0];

    while(right < n){
        
        while(sum > k && left<=right){
            sum -= arr[left];
            left++;
        }

        if(sum == k){
            maxLen = max(maxLen, right-left+1);
        }

        right++;
        if(right<n){
            sum += arr[right];
        }

    }

    return maxLen;
}


int main(){
    int size;
    cout << "Enter size: ";
    cin >> size;

    vector<int>arr;

    int x;
    cout << "Enter array elements:" << endl;
    for(int i=0; i<size; i++){
        cin >> x;
        arr.push_back(x);
    }

    long long k;

    cout << "Enter value of k: ";
    cin >> k;

    int result = longestSubarray(arr, k);

    cout << result << endl;

    return 0;
}