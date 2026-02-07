#include <iostream>
using namespace std;

void pattern(int n){
    int a = 1;
    for(int i=1; i<=n; i++){
        for(int j=0; j<i; j++){
            cout << a << " ";
            a++;
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
// Pattern: Continuous Number Triangle Pattern
1 
2 3
4 5 6
7 8 9 10
11 12 13 14 15


*/