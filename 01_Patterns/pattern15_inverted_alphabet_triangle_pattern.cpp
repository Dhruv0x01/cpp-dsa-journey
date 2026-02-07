#include <iostream>
using namespace std;

void pattern(int n, char ch){
    for(int i=1; i<=n; i++){
        for(int j=n; j>=i; j--){
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
    char ch = 'A';
    pattern(n, ch);
    return 0;
}

/*
// Pattern: Inverted Alphabet Triangle Pattern

ABCDE
ABCD
ABC
AB
A

*/