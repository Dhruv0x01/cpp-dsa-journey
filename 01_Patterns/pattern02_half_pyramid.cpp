#include <iostream>
using namespace std;

void print2(int n){
    for(int i = 1; i<n+1; i++){
        for(int j=0; j<i; j++){
            cout << "*";
        }
        cout << endl;
    }

}

int main(){
    int n;
    cin >> n;
    print2(n);
    return 0;
}

// Pattern 02: Half Pyramid
// *
// **
// ***
// ****
// *****


/*
First row pe 1 star
2nd row pe 2 star
3rd row pe 3 star
4th row pe 4 star
and so on

isse we connected columns to rows
*/