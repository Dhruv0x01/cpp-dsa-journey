#include <iostream>
using namespace std;

void pattern(int n){
    //Top part
    for(int i=1; i<=n; i++){
        
        // Left star
        for(int j=n; j>=i; j--){
            cout << "*";
        }
        // Space
        for(int k=1; k<i; k++){
            cout << "  ";
        }
        // Right star
        for(int j=n; j>=i; j--){
            cout << "*";
        }
        cout << endl;
    }

    //Bottom part
    for(int i=1; i<=n; i++){
        
        //Left star
        for(int j=0; j<i; j++){
            cout << "*";
        }
        //Space
        for(int k=i; k<n; k++){
            cout << "  ";
        }
        //Right star
        for(int z=0; z<i; z++){
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
// Pattern: Hourglass Star Pattern
**********
****  ****
***    ***
**      **
*        *
*        *
**      **
***    ***
****  ****
**********

*/