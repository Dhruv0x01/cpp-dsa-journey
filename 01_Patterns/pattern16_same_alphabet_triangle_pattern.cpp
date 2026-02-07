#include <iostream>
using namespace std;

void pattern(int n, char ch){
    for(int i=1; i<=n; i++){
        for(int j=0; j<i; j++){
            cout << ch;
        }
        ch++;
        cout << endl;
    }
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    char ch = 'A';
    pattern(n, ch);
    return 0;
}

/*
// Pattern: Same Alphabet Triangle Pattern

A
BB
CCC
DDDD
EEEEE

*/