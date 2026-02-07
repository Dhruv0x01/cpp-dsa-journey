#include <iostream>
using namespace std;

void pattern(int n){
    //Top part
    for(int i=1; i<=n; i++){
        //Left star
        for(int j=0; j<i; j++){
            cout << "*";
        }
        //Space
        for(int space=i; space<n; space++){
            cout << "  ";
        }
        //Right star
        for(int j=0; j<i; j++){
            cout << "*";
        }
        cout << endl;
    }
    //Bottom part
    for(int i=2; i<=n; i++){
        // Left star
        for(int j=n; j>=i; j--){
            cout << "*";
        }
        // Space
        for(int space=1; space<i; space++){
            cout << "  ";
        }
        // Right star
        for(int j=n; j>=i; j--){
            cout << "*";
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
// Pattern: Butterfly Star Pattern
*        *
**      **
***    ***
****  ****
**********
****  ****
***    ***
**      **
*        *

*/