#include <bits/stdc++.h>
using namespace std;

// Hashing -> One of the most imp topics in ds algo

// To tell how many times a number appears in an array

// Brute approach 
// Linear iteration -> it goes to each element and check
// Time complexity to check 1 number -> O(n)
// If you have to check q numbers -> O(q*n)
int countNumber(int arr[], int size, int target){
    int cnt = 0;

    for(int i=0; i<size; i++){
        if(arr[i] == target) cnt++;
    }

    return cnt;
}

// This is where hashing comes in
// Hashing -> Prestoring/fetching
// Let's say q states that number will be at max 12
// Hashing will create a hash/frequency array
// An array of size 13, filled with element 0 index goes from 0 to 12
// We will do some pre calculation -> all before user ask what number he want to know the count of btw
// It will traverse the array -> lets say it find number 1 -> it tells it hash array that can you remember i have one 1 -> hash array index 1 now has element 1 (previously it was 0)
// Then let's say while traversing array it finds number 4 -> it will tell its hash array that remember i have one 4 -> hash array index 4 now has element 1(previously it was 0)
// Traversing through array number 1 appears again -> gonna tell my hash array to increment the element at index 1 
// Now when im asked how many times 1 appears -> ill just print the element at index 1 of my hash array, i wont need to loop through an entire array to tell this

int main(){
// Let's say we will first input size of the array
// Element of the array
// How any numbers you want to know the count of
// Enter each number you want to know the count of
    int size;
    cout << "Enter size: ";
    cin >> size; // size of the array

    int arr[size];

    cout << "Enter elements: " << endl;
    for(int i=0; i<size; i++){
        cin >> arr[i]; // Inputing elements of array
    }

    // Depending on what is the maximum number that can be in the array -> we declare that+1 to be the size of our hash array
    // precomputation
    int hash[13] = {0}; // We assumed the numbers in array could only be till 12
    for(int i=0; i<size; i++){
        hash[arr[i]]++;
    }
    // Now we have the hash array prepared
    // If we are declaring array inside the main funtion -> we can only declare upto 10^6 arr[10^6] integer
    // But globally we can declare upto arr[10^7] integers 

    // For boolean array -> inside main we can declare upto arr[10^7]
    // Globally we can go till arr[10^8] boolean

    // If you declare size more than what it allows -> it will through segmentation error

    // If you declare globally everything is initialized at 0, so no need to put = {0}

    // Continue from 21 min





    cout << "Enter number of elements you want to know the count of: ";
    int q; 
    cin >> q; // How many elements you want to know the number of count of
    while(q--){
        int number;
        cin >> number; // The element you want to know the number of count of

        // fetch
        cout << hash[number] << endl;

    }

    

    //cout << countNumber(arr, size, target);

    return 0;
}