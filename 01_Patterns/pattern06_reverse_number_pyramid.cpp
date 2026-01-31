#include <iostream>
using namespace std;

void star(int n){
    for(int i=n; i>0; i--){
        for(int j=0; j<i; j++){
            cout << j+1;
        }
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;
    star(n);
    return 0;
}
/*
Pattern: Reverse Number Pyramid
12345
1234
123
12
1
*/