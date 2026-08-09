// Recursion -> When a function calls itself until a specified condition is met

#include <bits/stdc++.h>
using namespace std;

// This leads to stack overflow -> when there is numerous function call waiting due to recursion, it runs out of memory 
/*
void f(){
    cout << 1 << endl;
    f();
}
*/

int cnt = 0;

// The condition that you use to stop the recursion is called base condition
void f(){
    if(cnt == 4) return; // base condition
    cout << cnt << endl;
    cnt++;
    f();
}
// If you are writing a return statement inside a function, the function gets terminated if that return statement get executed

int main(){
    f();
    return 0;
}




