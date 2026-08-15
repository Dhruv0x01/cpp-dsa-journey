#include <bits/stdc++.h>
using namespace std;

// Character hashing (lowercase a-z)
// Map each letter to an index: 'a'->0, 'b'->1, ..., 'z'->25  via  s[i] - 'a'
// We could also take array of size 256 and that works for all kinds of input lowercase, uppercase, characters, etc

int main() {
    string s;
    cout << "Enter: ";
    cin >> s;

    // Pre-compute: frequency of each letter
    int hash[256] = {0};
    for (int i = 0; i < s.size(); i++) {
        hash[s[i]]++;
    }

    // Queries: fetch in O(1)
    int q;
    cout << "Enter the number of characters you want the count of: ";
    cin >> q;
    while (q--) {
        char cr;
        cin >> cr;
        cout << hash[cr] << endl;
    }

    // continue from 33:56 

    return 0;
}