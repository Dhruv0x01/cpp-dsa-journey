#include <iostream>
using namespace std;

void star(int n){
    //Upper half
    for(int i=1; i<=n/2; i++){
        //space
        for(int j=n/2-i; j>0; j--){
            cout << " ";
        }
        //star
        for(int k=0; k<2*i-1; k++){
            cout << "*";
        }
        //space
        for(int j=n/2-i; j>0; j--){
            cout << " ";
        }
        cout << endl;
    }
    //Lower half
    for(int i=n/2; i>0; i--){
        //space
        for(int j=0; j<n/2-i; j++){
            cout << " ";
        }
        //star
        for(int k=0; k<2*i-1; k++){
            cout << "*";
        }
        //space
        for(int j=0; j<n/2-i; j++){
            cout << " ";
        }
        cout << endl;
    }
}

int get_even(){
    int n;
    cout << "Enter an even number: ";
    cin >> n;

    if(n%2 == 0){
        return n;
    }else{
        cout << "Not even. Try again" << endl;
        return get_even();
    }
}

int main(){
    int n = get_even();
    star(n);
    return 0;
}

/*
Pattern: Diamond Star Pattern
    *    
   ***
  *****
 *******
*********
*********
 *******
  *****
   ***
    *
*/