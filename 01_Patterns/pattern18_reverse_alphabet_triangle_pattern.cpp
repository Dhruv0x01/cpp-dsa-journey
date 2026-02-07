#include <iostream>
using namespace std;

void pattern(int n, char ch){
    for(int i=1; i<=n; i++){
        for(int j=0; j<i; j++){
            cout << ch << " ";
            ch++;
        }
        ch = ch - i - 1;
        cout << endl;
    }
}

int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    char ch = 'A' + n - 1;
    pattern(n, ch);
    return 0;
}

/*
// Pattern: Reverse Alphabet Triangle Pattern
n = 7
G 
F G
E F G
D E F G
C D E F G
B C D E F G
A B C D E F G

*/