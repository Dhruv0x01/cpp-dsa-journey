#include <iostream>

using namespace std;

void print1(int n){                    // In online compiler you will write only this part
    for(int i = 0; i<n; i++){               
        for(int j = 0; j<n; j++){           
          cout << "*";                       
        }                                   
        cout << endl;
    }                                      
}                                    // Till here

int main(){                                 
    int n;
    cin >> n;
    print1(n);
    return 0;
}

// Pattern 01: Solid Square
// *****
// *****
// *****
// *****
// *****



// We ask user for input then do it that way
/* step 2
connect them somehow to the rows
at 0th row, we are printing 4 stars
at 1st row, we are printing 4 stars
""""
""""

Enter 1st row, print 4 stars then go to 2nd row and repeat, all the way till 4th row.

Outer loop i is for rows and inner loop j is for columns
First we enter 1st row and then to j in 1st column 
we printed the entire 1st row as column kept changing, 
we only got out of inner loop once we printed in the 1st row 5 times,
then we got out got sent to next line then entered 2nd row and repeat
*/