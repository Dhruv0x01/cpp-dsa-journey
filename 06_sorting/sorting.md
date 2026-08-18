# Sorting — Cheatsheet

---

# Selection Sort

**Core idea:** "Selection" means select — at every step, select the minimum element from
whatever's left unsorted, and swap it into place at the front. Repeat, shrinking the unsorted
region by one each time, until the whole array is sorted.

## How it works

**Step 1:** scan the *entire* array, find the minimum element, and swap it with whatever
currently sits at index `0`. Index `0` now holds the correct (smallest) value and is
considered "sorted." Everything from index `1` onward is still unsorted.

**Step 2:** index `0` is already fixed, so scan only the *remaining* unsorted portion (index
`1` onward), find its minimum, and swap it into index `1`. Now indices `0` and `1` are both
sorted.

**Step 3 onward:** repeat the same idea — at each step, scan whatever's left unsorted, find
its minimum, and swap it into the next available front position. Each step locks in exactly
one more correctly-placed element and shrinks the unsorted region by one.

## Why `n - 1` steps, not `n`

Once the first `n - 1` elements are correctly placed, the single element left over is
automatically the largest remaining value — there's nothing left to compare it against, so no
swap is needed for it. That's why the outer loop runs `n - 1` times, not `n`.

## Dry run — `[13, 46, 24, 52, 20, 9]`

| Step | Action | Array after step |
|--|--|--|
| Start | — | `13 46 24 52 20 9` |
| 1 | min of whole array is `9` → swap with index 0 | `9 46 24 52 20 13` |
| 2 | min of remaining `[46,24,52,20,13]` is `13` → swap with index 1 | `9 13 24 52 20 46` |
| 3 | min of remaining `[24,52,20,46]` is `20` → swap with index 2 | `9 13 20 52 24 46` |
| 4 | min of remaining `[52,24,46]` is `24` → swap with index 3 | `9 13 20 24 52 46` |
| 5 | min of remaining `[52,46]` is `46` → swap with index 4 | `9 13 20 24 46 52` — **sorted** |

After 2 steps, the first two positions (`9`, `13`) already hold the two smallest values in the
array — every step after that just keeps extending the sorted front by one.

## Complexity

| | Time | Why |
|--|--|--|
| Best case | O(n²) | still scans the *entire* remaining unsorted portion every step, even if the array is already sorted — no early exit exists |
| Average case | O(n²) | same reasoning |
| Worst case | O(n²) | same reasoning |
| Space | O(1) | sorts in-place; only a constant number of extra variables needed (index trackers), no auxiliary array |

Selection sort's time complexity does **not** improve on an already-sorted input — unlike, say,
Bubble Sort with an early-exit flag, Selection Sort always performs the full scan-for-minimum
work at every step regardless of how sorted the array already is.

## Number of swaps — its one real advantage

At most `n - 1` swaps total — exactly one swap per outer-loop step (some implementations skip
the swap if the minimum is already sitting in the correct spot, but conceptually it's never
more than one swap per step). This is Selection Sort's main practical advantage over something
like Bubble Sort: far fewer total swaps, which matters when swapping is expensive (e.g.
swapping large objects/structs rather than plain integers).

## Pseudocode outline

For each starting index `i` from `0` to `n - 2`:
- Assume the minimum is at index `i` (track this as `minIdx`).
- Scan from `i + 1` to `n - 1`; whenever you find an element smaller than
  `arr[minIdx]`, update `minIdx` to that new index.
- After scanning the whole remaining portion, swap `arr[i]` and `arr[minIdx]`.

## C++ implementation

```cpp
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}
```

Note the nested loop shape — outer loop picks the position being filled (`i`), inner loop
searches the remaining unsorted portion for the minimum (`j` from `i+1` to `n-1`). This nested
structure is exactly why the algorithm ends up O(n²): the outer loop runs `n-1` times, and each
time, the inner loop scans an average of roughly `n/2` remaining elements.