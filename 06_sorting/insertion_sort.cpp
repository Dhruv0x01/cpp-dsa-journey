/*
Insertion sort

Always takes an element and places it in its correct position

14, 9, 15, 12, 6, 8, 13

It starts with looking at first element in the array
It sees 14 -> It says element 14 in a size 1 array is in correct order

Now it sees 14, 9
It says in an array of size 2 -> element 9 should be first and element 14 second

9, 14, 15, 12, 6, 8, 13


Now it sees 9, 14, 15
It says in an array of size 3 -> they are in correct order

Now -> 9, 14, 15, 12 -> Check if 12 is at the correct pos? No
you compare 12 with its left element -> Should it swap? Yes then do
9, 14, 12, 15
Now again compare 12 with its left element -> Should it swap? Yes then do
9, 12, 14, 15
Compare 12 with left -> Should it swap? No then leave

9, 12, 14, 15, 6, 8, 13

Now it sees 9, 12, 14, 15, 6
Is 6 at right pos?
Can 6 swap with element left to it? yes then do
9, 12, 14, 6, 15
6 with 14? yes
9, 12, 6, 14, 15
6 with 12? yes
9, 6, 12, 14, 15
6 with 9? yes
6, 9, 12, 14, 15

Now sees 6, 9, 12, 14, 15, 8

Do for 8
6, 9, 12, 14, 8, 15
6, 9, 12, 8, 14, 15
6, 9, 8, 12, 14, 15
6, 8, 9, 12, 14, 15

now it sees 
6, 8, 9, 12, 14, 15, 13

Do for 13

6, 8, 9, 12, 13, 14, 15
Done
*/

#include <bits/stdc++.h>
using namespace std;

void insertionSort(int arr[], int n){
    for(int i=1; i<=n-1; i++){
        for(int j=i; j>0; j--){
            if(arr[j] < arr[j-1]){
                swap(arr[j], arr[j-1]);
            }else{
                break;
            }
        }
    }
    
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: " << endl;

    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    insertionSort(arr, n);

    cout << "After insertion sort: " << endl;

    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }

    return 0;
}