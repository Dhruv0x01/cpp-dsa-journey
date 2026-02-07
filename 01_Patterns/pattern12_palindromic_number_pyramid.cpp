#include <iostream>
using namespace std;

void pattern(int n){
    for(int i=1; i<=n; i++){
        //Number
        for(int j=1; j<=i; j++){
            cout << j;
        }
        // Space
        for(int k=n; k>i; k--){
            cout << "  ";
        }
        // Number
        for(int j=i; j>=1; j--){
            cout << j;
        }
        cout << endl;
    }
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    pattern(n);
    return 0;
}

/*
// Pattern: Palindromic Number Pyramid Pattern
1        1
12      21
123    321
1234  4321
1234554321


*/