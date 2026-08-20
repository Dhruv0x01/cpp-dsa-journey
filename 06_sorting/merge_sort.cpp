// ============================================================
//   MERGE SORT  —  Divide & Conquer
//   Time:  O(n log n)   |   Space: O(n)  (the temp vector)
//   Stable: YES  (because of the `<=` in the compare below)
// ============================================================
//
// THE BIG IDEA:
//   Sorting a big array is hard. Merging two ALREADY-SORTED
//   arrays is easy. So:
//     1. Split the array in half.
//     2. Sort each half (recursively — same function).
//     3. Merge the two sorted halves back together.
//
//   The recursion keeps splitting until each piece has 1 element.
//   A 1-element array is sorted by definition. That's the base case.
//
//   Trace for [5, 2, 4, 1]:
//        [5,2,4,1]
//        /      \         <- mergeSort splits (going DOWN)
//     [5,2]     [4,1]
//     /  \      /  \  .
//    [5] [2]  [4]  [1]    <- base case: size 1, already sorted
//     \  /      \  /
//     [2,5]     [1,4]     <- merge combines (coming BACK UP)
//        \      /
//        [1,2,4,5]
//
//   Note: ALL the actual work happens on the way back UP.
//   mergeSort just splits; merge does the sorting.
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------------
// merge()
// PRECONDITION (this is the whole contract — remember it):
//   arr[low..mid]      is already sorted
//   arr[mid+1..high]   is already sorted
// JOB: combine those two sorted halves into one sorted run
//      occupying arr[low..high].
// ------------------------------------------------------------
void merge(int arr[], int low, int mid, int high) {

    vector<int> temp;                 // holds the merged result
    temp.reserve(high - low + 1);     // optional: pre-allocate, avoids regrowth

    int left  = low;        // reading pointer into the LEFT half
    int right = mid + 1;    // reading pointer into the RIGHT half

    // --- STEP 1: pick the smaller front element, repeatedly ---
    // Both halves are sorted, so the smallest unused element overall
    // is always at the FRONT of one half or the other.
    // Runs until one half is exhausted.
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            //  <=  (not <) is what makes merge sort STABLE:
            //  on a tie we take from the LEFT half, so equal
            //  elements keep their original relative order.
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // --- STEP 2: drain whichever half still has elements ---
    // We exited the loop because ONE side ran out. The other side
    // still holds elements — and they're already sorted AND all
    // bigger than everything in temp, so just append them in order.
    // Exactly one of these two loops will actually run.

    while (left <= mid) {            // left half had leftovers
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= high) {          // right half had leftovers
        temp.push_back(arr[right]);
        right++;
    }

    // --- STEP 3: copy temp back into the real array ---
    // temp is 0-indexed (temp[0], temp[1], ...) but we need to write
    // into arr[low..high]. So the offset is `low`:
    //     arr[low]   <- temp[0]
    //     arr[low+1] <- temp[1]
    //     arr[i]     <- temp[i - low]
    // Forgetting the `- low` is THE classic merge sort bug.
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

// ------------------------------------------------------------
// mergeSort()
// Sorts arr[low..high] in place. Both ends INCLUSIVE.
// ------------------------------------------------------------
void mergeSort(int arr[], int low, int high) {

    // BASE CASE: 0 or 1 element in this range -> nothing to sort.
    // (low == high means 1 element; low > high means empty.)
    // Without this the recursion never stops.
    if (low >= high) return;

    // Split point. Using low + (high-low)/2 instead of (low+high)/2
    // avoids integer overflow when low+high exceeds INT_MAX.
    // Doesn't matter for small arrays, but it's the habit to build —
    // this exact bug will bite you again in Binary Search (Step 4).
    int mid = low + (high - low) / 2;

    mergeSort(arr, low, mid);          // sort the left half
    mergeSort(arr, mid + 1, high);     // sort the right half
    merge(arr, low, mid, high);        // combine the two sorted halves

    // Why mid+1 and not mid? Because mid ALREADY belongs to the left
    // half. Passing mid to both sides would make the halves overlap
    // and the recursion would never shrink -> infinite recursion.
}

int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    // NOTE: `int arr[n]` is a VLA (variable length array). It works in
    // g++ as an extension but is NOT standard C++. Use vector instead —
    // it's what you'll use on LeetCode anyway.
    vector<int> arr(n);

    cout << "Enter array elements: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // arr.data() gives the raw int* the functions expect.
    // Range is 0 .. n-1 because both ends are inclusive.
    mergeSort(arr.data(), 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

// ============================================================
//   WHY O(n log n)?
//     - The array halves each level, so there are log2(n) levels.
//       (n=8 -> 8,4,2,1 = 3 levels of splitting)
//     - Each LEVEL touches every element exactly once during
//       merging, so each level costs O(n).
//     - Total = O(n) work x O(log n) levels = O(n log n).
//
//   WHY O(n) SPACE?
//     The temp vector. At the top-level merge it holds all n
//     elements. This is merge sort's one real weakness versus
//     quick sort, which sorts in place.
//
//   INTERVIEW POINTS WORTH KNOWING COLD:
//     - Stable, guaranteed O(n log n) even in the worst case.
//       (Quick sort is O(n^2) worst case.)
//     - The merge() function on its own solves LC 88
//       "Merge Sorted Array".
//     - Add a counter in the `else` branch of step 1 and you have
//       the classic "count inversions" problem — every time you
//       take from the right half, it jumps (mid - left + 1)
//       remaining left-half elements.
// ============================================================