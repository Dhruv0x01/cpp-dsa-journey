#include <iostream>
using namespace std;

void star1(int n){
    for(int i=1; i<=n; i++){
            for(int k=1; k<=n-i; k++){   //For initial space
                cout << " ";
            }
            for(int l=1; l<=2*i-1; l++){ //For stars
                cout << "*";
            }
            for(int k=1; k<=n-i; k++){   //For after space
                cout << " ";
            }
        cout << endl;
    }
}

void star2(int n){
    for(int i=1; i<=n; i++){
        for(int j=n-i; j>0; j--){
            cout << " ";
        }
        for(int k=0; k<2*i-1; k++){
            cout <<"*";
        }
        for(int j=n-i; j>0; j--){
            cout << " ";
        }
        cout << endl;
    }
}


int main(){
    int n;
    cin >> n;
    star1(n);
//  star2(n);

    return 0;
}

/*
Pattern: Full Star Pyramid
    *    
   ***   
  *****  
 ******* 
*********
*/