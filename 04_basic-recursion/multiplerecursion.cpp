// Multiple Recursion Calls
// Here we will call functions multiple times within the function

// Fibonacci Numbers
// 0 1 1 2 3 5 8 13

// You will be given N, need to give N'th fibonacci number
// 0 is 0th fibonacci number
// 1 is 1st """"""
// so on
// f(3) = f(2) + f(1) + f(0)

// If there are multiple recursion calls:-
// line 4: f();
// line 5: f();
// line 6: f();

// So line 4 will execute and when it returns then line 5 and then line 6
// Line by line it will work
// Time complexity is roughly 2^n
// Exponential in nature 
// For 1 number:- we are calling 2
// so on

#include <bits/stdc++.h>
using namespace std;

int fibonacci(int n){
    if(n<=1) return n;

    int last = fibonacci(n-1);
    int secondLast = fibonacci(n-2);

    return last+secondLast;
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    cout << fibonacci(n);
    return 0;
}
