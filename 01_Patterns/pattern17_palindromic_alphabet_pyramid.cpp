#include <iostream>
using namespace std;

void pattern(int n){
    for(int i=1; i<=n; i++){
        //Space
        for(int j=n; j>i; j--){
            cout << " ";
        }
        // First Character 
        char ch = 'A';
        for(int k=0; k<i; k++){
            cout << ch;
            ch++;
        }
        // Second Character 
        ch-=2;
        for(int z=1; z<i; z++){
            cout << ch;
            ch--;
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
// Pattern: Palindromic Alphabet Pyramid Pattern

    A
   ABA
  ABCBA
 ABCDCBA
ABCDEDCBA

*/