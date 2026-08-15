// Number Hashing using map (query with .find so missing elements aren't inserted)

#include <bits/stdc++.h>
using namespace std;

int main() {
    int size;
    cout << "Enter size: ";
    cin >> size;

    int arr[size];

    cout << "Enter array elements: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    map<int, int> mpp;

    for (int i = 0; i < size; i++) {
        mpp[arr[i]]++;
    }

    int q;
    cout << "Enter the number of element you want to know the count of: ";
    cin >> q;

    while (q--) {
        int target;
        cout << "Enter element you want to know the count of: ";
        cin >> target;

        auto it = mpp.find(target);

        if (it != mpp.end()) {
            cout << it->second << endl;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}



