#include <bits/stdc++.h>
using namespace std;

// Note: If the function type is void, then no need for return Function() at last
// If return type is non-void, you need to type return sumNum();

// Summation of first N numbers using recursion
// Way 1: Through parameter(parameterised way)
// we will carry a sum parameter inside function -> we will go from N to 1
void sumNumP(int i, int sum=0){
    if(i<1) {
        cout << sum << endl;
        return;
    }
    sumNumP(i-1, sum+i);
}

// Way 2: Functional way(where function itself returns the answer)
// You want the function to return the answer 
// It will accept N and return sum upto N
int sumNumF(int i){
    if(i==0) return 0;

    return i+sumNumF(i-1);
}

// Factorial of n
// Way 1: Parameterized
void factP(int i, int fact = 1){
    if(i==1){
        cout << fact << endl;
        return;
    }
    factP(i-1, fact*i);
}

// Way 2: Functional return
int factN(int i){
    if(i==0)return 1;
    return i*factN(i-1);
}

int main(){
    //sumNumP(6);
    //cout << sumNumF(3);
    //factP(5);
    cout << factN(5);
    return 0;
}