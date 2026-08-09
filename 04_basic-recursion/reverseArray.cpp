#include <bits/stdc++.h>
using namespace std;

// Reverse an array using recursion
// Way 1: Using two parameter
// i goes from 0 to size-1
// r goes from size-1 to 0
// Moment they are equal (in case of odd) or i becomes bigger than r, array is reversed as we are swapping elements 
void swap(int arr[], int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Here i and r both changes
void reverseArray(int arr[], int r, int i=0){
    if(i >= r){ // More than equal so it works for even too
        cout << "Reversed successfully!" << endl;
        return;
    }
    swap(arr, i, r);
    reverseArray(arr, r-1, i+1);
}

// Way 2: Doing it using single pointer
// i will swap with size-1-i
// base condition -> stop when i>= size/2 -> stop moment i crosses middle
// Here only i changes goes from 0 to ahead
// Size stays constant
void reverseArrayA(int arr[], int size, int i=0){
    if(i >= size/2) return;

    swap(arr, i, size-i-1);

    reverseArrayA(arr, size, i+1);
}


int main(){
    int size;
    cout << "Enter size: ";
    cin >> size;

    int arr[size];

    cout << "Enter elements:" << endl;
    for(int i=0; i<size; i++){
        cin >> arr[i];
    }

    //reverseArray(arr, size-1);
    reverseArrayA(arr, size); // Sending size which stays constant

    for(int i=0; i<size; i++){
        cout << arr[i] << " ";
    }

    return 0;
}