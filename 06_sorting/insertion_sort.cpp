/*
====================================================================
INSERTION SORT
====================================================================

IDEA
----
Think of sorting a hand of playing cards. You keep the cards on the
left already sorted, pick up the next card, and slide it left until
it sits in the right place.

So the array is mentally split into two parts:

    [ sorted part | unsorted part ]
                  ^
                  the element we are currently placing

Each pass grows the sorted part by exactly one element.


WALKTHROUGH:  14, 9, 15, 12, 6, 8, 13
--------------------------------------

Pass 0 (start): sorted part = [14]
    A single element is always sorted, so nothing to do.

Pass 1: pick 9   ->  [14 | 9, 15, 12, 6, 8, 13]
    9 < 14, so swap them.
    Result: 9, 14, 15, 12, 6, 8, 13

Pass 2: pick 15  ->  [9, 14 | 15, ...]
    15 > 14, it is already in the right spot. Stop immediately.
    Result: 9, 14, 15, 12, 6, 8, 13

Pass 3: pick 12  ->  [9, 14, 15 | 12, ...]
    12 < 15 -> swap:  9, 14, 12, 15
    12 < 14 -> swap:  9, 12, 14, 15
    12 > 9  -> stop (everything further left is smaller)
    Result: 9, 12, 14, 15, 6, 8, 13

Pass 4: pick 6
    6 < 15 -> swap:  9, 12, 14, 6, 15
    6 < 14 -> swap:  9, 12, 6, 14, 15
    6 < 12 -> swap:  9, 6, 12, 14, 15
    6 < 9  -> swap:  6, 9, 12, 14, 15
    Result: 6, 9, 12, 14, 15, 8, 13

Pass 5: pick 8
    8 keeps bubbling left past 15, 14, 12 and stops after 6.
    Result: 6, 8, 9, 12, 14, 15, 13

Pass 6: pick 13
    13 bubbles left past 15 and 14, stops after 12.
    Result: 6, 8, 9, 12, 13, 14, 15   <- sorted


KEY POINT
---------
Once an element is NOT smaller than its left neighbour we can `break`,
because the whole left side is already sorted. This early exit is what
makes insertion sort O(n) on an already-sorted array.


COMPLEXITY
----------
Time:  Best  O(n)    - already sorted, inner loop breaks right away
       Worst O(n^2)  - reverse sorted, every element travels all the way left
       Average O(n^2) 
Space: O(1)          - sorts in place
Stable: yes (equal elements never swap, since we only swap on strict <)
====================================================================
*/

#include <bits/stdc++.h>
using namespace std;

void insertionSort(int arr[], int n) {
    // i marks the element we are inserting into the sorted left part.
    // Start at 1 because arr[0] alone is already "sorted".
    for (int i = 1; i <= n - 1; i++) {

        // Move arr[i] leftwards, one swap at a time, until it lands
        // in its correct position inside the sorted part.
        for (int j = i; j > 0; j--) {

            if (arr[j] < arr[j - 1]) {
                // Current element is smaller than its left neighbour,
                // so it still needs to move further left.
                swap(arr[j], arr[j - 1]);
            } else {
                // It is >= its left neighbour. Since the left part is
                // already sorted, this is the correct spot -> stop early.
                break;
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    int arr[n];

    cout << "Enter array elements: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    insertionSort(arr, n);

    cout << "After insertion sort: " << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}