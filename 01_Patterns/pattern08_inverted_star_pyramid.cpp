#include <iostream>
using namespace std;

void pattern(int n){
    for(int i=n; i>0; i--){
        //space
        for(int j=0; j<n-i; j++){
            cout << " ";
        }
        //stars
        for(int k=2*i-1; k>0; k--){
            cout << "*";
        }
        //space
        for(int j=0; j<n-i; j++){
            cout << " ";
        }
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;
    pattern(n);

    return 0;
}

/*
Pattern: Inverted Pyramid Star Pattern
*********
 *******
  *****
   ***
    *
*/