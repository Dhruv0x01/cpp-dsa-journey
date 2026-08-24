#include <bits/stdc++.h>
using namespace std;

// Places arr[low] at its final sorted position, returns that index.
// After this: everything left of it is <=, everything right is >.
int partitionIndex(int arr[], int low, int high){
    int pivot = arr[low];
    int i = low, j = high;

    while(i < j){
        while(arr[i] <= pivot && i <= high-1) i++;   // scan right for an element > pivot
        while(arr[j] >  pivot && j >= low+1)  j--;   // scan left  for an element <= pivot
        if(i < j) swap(arr[i], arr[j]);              // both found, not crossed -> swap
    }

    swap(arr[low], arr[j]);   // j has crossed past i, so arr[j] <= pivot -> pivot's home
    return j;
}

void quickSort(int arr[], int low, int high){
    if(low >= high) return;                          // 0 or 1 element = already sorted
    int p = partitionIndex(arr, low, high);
    quickSort(arr, low,   p-1);                      // pivot itself is done, exclude it
    quickSort(arr, p+1,   high);
}

int main(){
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    quickSort(arr.data(), 0, n-1);

    for(int x : arr) cout << x << " ";

    return 0;
}