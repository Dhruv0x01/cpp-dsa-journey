#include <bits/stdc++.h>
using namespace std;

// ---------- Brute force: count occurrences of target ----------
// Time: O(n) per query
int countNumber(int arr[], int size, int target) {
    int cnt = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) cnt++;
    }
    return cnt;
}

int main() {
    // Input array
    int size;
    cout << "Enter size: ";
    cin >> size;

    int arr[size];
    cout << "Enter elements: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    // ---------- Hashing: pre-compute frequencies ----------
    // Assumes numbers are in range 0..12 (so size 13).
    int hash[13] = {0};
    for (int i = 0; i < size; i++) {
        hash[arr[i]]++;
    }

    // ---------- Queries: fetch in O(1) ----------
    cout << "Enter number of elements you want the count of: ";
    int q;
    cin >> q;
    while (q--) {
        int number;
        cin >> number;
        cout << hash[number] << endl;
    }

    return 0;
}