#include <bits/stdc++.h>
using namespace std;

int count(int n){
    int count=0;
    while(n!=0){
        count++;
        n = n/10;
    }
    return count;
    /*
    int count = (int)(log10(n) + 1);
    return count;
    */
}
// Time complexity is log10(n)
    // As we are dividing by 10
    // If number of iterations is based on division, the log(n) will come in time complexity

    // Whenever there is division, if the division is happening by 2 -> time complexity is log2(n) [base is 2]
    // """""""                                                  by 10 -> time complexity is log10(n) [base is 10]


int reverseNumber(int n){
    int revNum, digit;
    while(n!=0){
        digit = n%10;
        revNum = (revNum*10) + digit;
        n /= 10;
    }
    return revNum;
}


int main(){
    int n;
    cout << "Enter number: ";
    cin >> n;

    //cout << count(n); 
    cout << reverseNumber(n);
    


    return 0;
}