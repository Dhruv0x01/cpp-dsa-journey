#include <iostream>
using namespace std;

void pattern(int n){
    for(int i=1; i<=n; i++){
        for(int j=0; j<i; j++){
            cout << (i+j)%2 << " ";
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
// Pattern: Binary Number Triangle Pattern
1 
0 1 
1 0 1 
0 1 0 1 
1 0 1 0 1


*/