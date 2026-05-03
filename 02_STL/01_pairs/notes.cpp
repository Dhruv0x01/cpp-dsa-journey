#include <bits/stdc++.h> 
using namespace std;

// Pairs
void explainPair(){
    pair<int, int> p = {1, 3}; // Defining and assigning pairs, variable p contains {1, 3}
    cout << p.first << " " << p.second << endl;   // Access first and second element by variable.first and variable.second
    // Output: 1 3

    // Nested property of pair
    // Since it's a pair, it stored two numbers. To store three, what if {new number, {old pair}} 
    // Let's do this
    // Make sure to update the data type as this time the second thing is a pair of integers and not just an integer

    pair<int, pair<int, int>> l = {5, {1, 3}};
    cout << l.first << " " << l.second.first << " " << l.second.second << endl;
    // Output: 5 1 3

    // To print the individual inside another pair, l.second.first and l.second.first
    // You can't print the pair inside like l.second btw 

    // Declaring pair array 
    // We will declare an array whose each element consist of a pair
    pair<int, int> arr[] = {{1, 2}, {3, 4}, {5, 6}};
    cout << arr[0].first << " " << arr[2].second << " " << arr[1].first;
    // Output: 1 6 3

    // Again you can't print arr[0] on its own, you need to specify .first or .second
}


int main(){
    explainPair();

    return 0;
}







