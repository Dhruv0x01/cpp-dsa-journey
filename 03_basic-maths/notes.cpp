#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int count(int n){
    int count=0;
    while(n!=0){
        count++;
        n = n/10;
    }
    return count;
    /*
    int count = (int)(log10(n) + 1);
    return count;
    */
}
// Time complexity is log10(n)
    // As we are dividing by 10
    // If number of iterations is based on division, the log(n) will come in time complexity

    // Whenever there is division, if the division is happening by 2 -> time complexity is log2(n) [base is 2]
    // """""""                                                  by 10 -> time complexity is log10(n) [base is 10]


int reverseNumber(int n){
    int revNum, digit;
    while(n!=0){
        digit = n%10;
        revNum = (revNum*10) + digit;
        n /= 10;
    }
    return revNum;
}

bool palindrome(int x){
    int originalNum, digit;
    long long revNum;

    if(x<0) return false;

    originalNum = x;
    while(x>0){
        digit = x%10;
        revNum = (revNum*10) + digit;
        x /= 10;
    }
    
    return originalNum == revNum;
    
}

bool isArmstrong(int n){
    int originalNum, x;
    originalNum = n;
    x = n;

    int numOfDigit = 0;

    int digit;
    long sum = 0;

    while(x > 0){
        numOfDigit++;
        x /= 10;
    }

    while(n > 0){
        digit = n%10;
        sum += pow(digit, numOfDigit);
        n /= 10;
    }

    return sum == originalNum;

}

vector<int> divisorNumber(int n){
    vector<int>v;
    for(int i=1; i<=sqrt(n); i++){
        if(n%i == 0){
            v.push_back(i);
            if(i != n/i) v.push_back(n/i);
        } 
    }
    sort(v.begin(), v.end());
    return v;
}

bool isPrime(int n){
    bool isPrime = 1;
    if(n==1 || n==-1){
        isPrime = 0;
    }
    for(int i=2; i<n; i++){
        if(n%i == 0){
            isPrime = 0;
        }
    }
    return isPrime;
}

/* Brute Approach (high time complexity)
int gcd(int a, int b){
    vector<int>v1;
    int gcd;
    for(int i=1; i*i<=a; i++){
        if(a%i == 0){
            v1.push_back(i);
            if(i != a/i ) v1.push_back(a/i);
    }
        }
        
    sort(v1.begin(), v1.end());

    vector<int>v2;
    for(int i=1; i*i<=b; i++){
        if(b%i == 0){
            v2.push_back(i);
            if(i != b/i ) v2.push_back(b/i);
        } 
        
    }
    sort(v2.begin(), v2.end());

    for(auto it1=v1.begin(); it1!=v1.end(); it1++){
        for(auto it2=v2.begin(); it2!=v2.end(); it2++){
            if(*it1 == *it2){
                gcd = *it1;
            }
        }
    }

    return gcd;
}
*/


// HCF(Highest common factor) / GCD(Greatest common divisor) [Both are same thing]
// n1 and n2 -> have your loop go from 1 to larger(n1, n2) -> for each check if both is divisible or not

// But in worst case, it's still have time complexity as O(min(n1, n2))
// So not good
/*
int gcd(int a, int b){
int result = 1;
    for(int i=min(a, b); i>=1; i--){
        if(a%i == 0 && b%i == 0){
            result = i;
            break;
        }
    }
    return result;
}
*/

// We need to use Euclidean Algorithm
// It states that hcf(n1, n2) = hcf(n1-n2, n2) where n1>n2
// What you will do is -> take two number -> apply euclidean algo -> get it smaller -> keep doing it until one of the number becomes 0, then the other is the hcf
// Lets take the case of gcd(52, 10) -> gcd(42, 10) -> gcd(32, 10) -> gcd(22, 10) -> gcd(12, 10) -> gcd(2, 10) gcd(10, 2) -> gcd(8, 2) -> gcd(6, 2) -> gcd(4, 2) -> gcd(2, 2) -> gcd(0, 2)
// So here it ends up taking alot of time -> there is a way where we can simply just jump from first to here| by doing 52%10, then reverse and 2%10 to reach here    |  -> instead of subtracting just take remainder


// So we can roughly say -> gcd(a, b) = gcd(a%b, b) where a>b
// greater % smaller -> you will reach a point where the first element becomes smaller and second greater -> no need to swap and then again do greater%smaller
// When one of them becomes zero, the other is the hcf

// let's dry run gcd(52, 10)
// First -> it will go in as both positive -> first if works this time 52 = 52%10 = 2
// After this since none became 0 -> we continue inside while loop only
// Now a = 2, b = 10
// Now we will go into the second case of b>a
// b = b%a = 10%2 = 0
// As one became 0 we need to come out of loop
// No need to swap as after change that will just mean we will do the other case
int gcd(int a, int b){
    while(a>0 && b>0){
        if(a>b){
           a = a%b;
        }else{
           b = b%a;
        }
    }
    // Outside while loop means one of them is 0 now
    if(a==0) return b;
    if(b==0) return a;
}
// Time complexity of this approach -> logphi(min(a, b))

int main(){
    int n;
    cout << "Enter number: ";
    cin >> n;

    int n1;
    cout << "Enter second number: ";
    cin >> n1;

    //cout << count(n); 
    //cout << reverseNumber(n);
    //cout << palindrome(n);
    //cout << isArmstrong(n);
    /*for(auto it:divisorNumber(n)){
        cout << it << " ";
    }
    */
   //cout << isPrime(n);
   cout << gcd(n, n1);
    


    return 0;
}