#include <iostream>
using namespace std;

// Method 1: By merging two parts
void star(int n){
    //Upper part
    for(int i=0; i<=(2*n-1)/2; i++){
        for(int j=0; j<=i; j++){
            cout << "*";
        }
        for(int k=0; k<n-i-1; k++){
            cout << " ";
        }
        cout << endl;
    }
    // bottom part
    for(int a=1; a<n; a++){
        for(int b=0; b<n-a; b++){
            cout << "*";
        }
        for(int c=0; c<a; c++){
            cout << " ";
        }
        cout << endl;
    }
}

// Method 2
void star2(int n){
    for(int i=1; i<=2*n-1; i++){
        int stars = i;
        if(i<=n){
        for(int j = 1; j<=stars; j++){
        cout << "*";
        }
    }else{
        for(int k=n; k>i-n; k--){
            cout << "*";
        }
    }
       cout << endl; 
    }
}



int main(){
    int n;
    cin >> n;
//  star(n);
    star2(n);

    return 0;
}

/*
Pattern: Half Diamond Star Pattern
*
**
***
****
*****
****
***
**
*
            */