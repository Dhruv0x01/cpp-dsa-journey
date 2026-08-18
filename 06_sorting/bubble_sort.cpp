/*
Bubble Sort — pushes the maximum to the last position by adjacent swaps.

Walk left to right, compare arr[i] with arr[i+1], swap if out of order.
One full walk drags the largest element to the end:

    13 46 24 52 20 9   ->   13 24 46 20 9 [52]

Now 52 is locked, so the next walk goes one step less far. Each walk locks
one more element at the back, so after n-1 walks the array is sorted.
*/

#include <bits/stdc++.h>
using namespace std;

void bubbleSort(int arr[], int n){
    for(int j=0; j<=n-2; j++){          // n-1 passes; j = how many are locked at the back
        bool swapped = false;           // must reset every pass

        for(int i=0; i<=n-2-j; i++){    // n-2 keeps i+1 in bounds, -j skips the locked tail
            if(arr[i] > arr[i+1]){
                swap(arr[i], arr[i+1]);
                swapped = true;
            }
        }

        // Zero swaps means every adjacent pair was already in order = sorted, so stop early.
        if(!swapped) break;
    }
}

// Time complexity -> O(n^2) for worst and avg case
// O(n) for best case
int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: " << endl;
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    bubbleSort(arr, n);

    cout << "After bubble sort: " << endl;
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }

    return 0;
}