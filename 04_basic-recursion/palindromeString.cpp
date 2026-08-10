// Check if a given string is palindrome or not

#include <bits/stdc++.h>
#include <cctype>
using namespace std;

// If recursive function is non-void, then function itself ko jo call kroge usko return ke sath call krna

// Functional (function gonna return true or false)
// One parameter i
// Starting i=0 and ++
// For end it should be s.size() - i - 1
// If they are equal -> then its fine go next -> if not equal return false

bool isPalindrome(string s, int i=0){
    if(i>=s.size()/2) return true;
    if(tolower(s[i]) != tolower(s[s.size()-i-1])) return false;
    return isPalindrome(s, i+1); 
}
// when in recursion we reach end that is when i>=size/2 then it returns true and not print anything -> that true comes back till here 
// so this line becomes true
// hence we need to write return before it


int main(){
    string x;
    cout << "Enter a string: ";
    cin >> x;

    cout << isPalindrome(x);

    return 0;
}