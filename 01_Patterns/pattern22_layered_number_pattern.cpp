#include <iostream>
using namespace std;

void pattern(int n){
    for(int i=0; i<2*n-1; i++){
        for(int j=0; j<2*n-1; j++){
            int top = i;
            int bottom = 2*n-2-i;
            int left = j;
            int right = 2*n-2-j;
            cout << (n - min( min(top, bottom), min(left, right)));
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

// Pattern: Pattern using minimum distance/ Layered Number Pattern
555555555
544444445
543333345
543222345
543212345
543222345
543333345
544444445
555555555

*/