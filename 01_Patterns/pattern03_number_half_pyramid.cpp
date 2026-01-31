#include <iostream>
using namespace std;

void print3(int n){           // method 1 with extra variable
    for(int i = 0; i < n; i++){
        int x = 1;
        for(int j = 0; j <= i; j++){
            cout << x << " ";
            x++;
        }
        cout << endl;
    }
}

void print4(int n){          // method 2 
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            cout << j << " ";
        }
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;
//  print3(n); 
    print4(n); 

    return 0;
}

/* Pattern 03: Number Half Pyramid
1 
1 2 
1 2 3 
1 2 3 4 
1 2 3 4 5
*/

/* 
So basically 1st row, we printed 1
2nd row, we printed 1 2
3rd row, 1 2 3
and so one

when we go to next row( mean come out of inner loop), we need to go to next line and start printing from 1 again, 
refresh value
*/