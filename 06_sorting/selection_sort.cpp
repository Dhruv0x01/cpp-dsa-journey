#include <bits/stdc++.h>
using namespace std;

// Swap element between 0 and minElementIndex [Search min element between 0 and n-1]
// Swap element between 1 and minElementIndex [Search min element between 1 and n-1]
// Swap element between 2 and minElementIndex [Search min element between 2 and n-1]
// ----
// Swap element between n-2 and minElementIndex [Search min element between n-2 and n-1]


// O(n^2) is the best, avg, worst case time complexity for selectionSort
void selectionSort(int arr[], int n){
    for(int i=0; i<=n-2; i++){
        int minInd = i;
        for(int j=i+1; j<n; j++){
            if(arr[j] < arr[minInd]){
                minInd = j;
            }
        }
        swap(arr[i], arr[minInd]);
    }
}

int main(){
    int n;
    cout << "Enter size: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: " << endl;
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    selectionSort(arr, n);

    cout << "Sorted Array: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }

    return 0;
}