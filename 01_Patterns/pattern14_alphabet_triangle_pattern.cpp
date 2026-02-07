// Characters are stores as ASCII values
// char ch = 'A'; then ch++ will be 'B'

#include <iostream>
using namespace std;

void pattern(int n){
    char ch = 'A';
    for(int i=1; i<=n; i++){
        for(int j=0; j<i; j++){
            cout << ch;
            ch++;
        }
        ch = 'A';
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
// Pattern: Alphabet Triangle Pattern

A
AB
ABC
ABCD
ABCDE


*/
