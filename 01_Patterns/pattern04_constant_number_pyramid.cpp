#include <iostream>
using namespace std;

void print1(int n, int x){
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            cout << x << " ";
        }
        cout << endl;
        x++;
    }
}


int main(){
    int n;
    cin >> n;
    print1(n, 1);

    return 0;
}

/*
Pattern 04: Constant Number Pyramid
1 
2 2 
3 3 3 
4 4 4 4 
5 5 5 5 5
*/