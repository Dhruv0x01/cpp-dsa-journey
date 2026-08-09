// Basic Recursion Problems
#include <bits/stdc++.h>
using namespace std;

// Print name N times
/*
void name(int i, int N){
    if(i>N) return;
    cout << "Dhruv" << endl;
    name(i+1, N);
}
*/

// Print linearly from 1 to N
/*
void printNum(int i, int N){
    if(i>N) return;
    cout << i << endl;
    printNum(i+1, N);
    
}
*/


// Print from N to 1
/*
void printRevNum(int i){
    if(i<1) return;
    cout << i << endl;
    printRevNum(i-1);
}
*/

// Print 1 to N by backtracking
// Dont use f(i+1, N)
// Just use f(i-1)
/*
void printNum(int i, int N){
    if(i<1) return;
    printNum(i-1, N);
    cout << i << endl; 
    // Since we kept the print line after the function call, it will run when we start returning back when i becomes 0 we return to last recursion where i=1, there the printNum ran so the cout get executed
    // after that it came back again to before it where i=2, the printNum get executed so now cout works, prints 2, and so on..
}
// What we did was we made it mandatory that the last print ran first, that was when i = 1
*/

// Print N to 1 by backtracking
void printRevNum(int i, int N){
    if(i>N) return;
    printRevNum(i+1, N);
    cout << i << endl;
}

int main(){
    //name(1, 6);
    //printNum(10, 10);
    printRevNum(1, 10);



    return 0;
}