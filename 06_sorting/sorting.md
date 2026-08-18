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

---

# Bubble Sort

**Core idea:** it pushes the **maximum to the last** position by repeated **adjacent swaps**.
Walk left-to-right through the array comparing every neighbouring pair `(arr[i], arr[i+1])`; if
they're out of order, swap them. The biggest element keeps getting carried rightward on each
comparison until it lands at the end — like a bubble rising to the surface. Repeat, shrinking
the region you walk by one each time.

Contrast with Selection Sort: Selection Sort *picks* the minimum and drops it at the front in
one swap. Bubble Sort never picks anything — it only ever compares neighbours, and the correct
element ends up in place as a side effect of many small swaps.

## How it works

**Pass 1:** walk from index `0` to index `n-2`, comparing `arr[i]` with `arr[i+1]` each time.
Every time the left one is bigger, swap. By the end of this single walk, the largest element in
the array is guaranteed to be sitting at index `n-1`. Why guaranteed? Because the moment the
walk reaches the maximum, that maximum wins every subsequent comparison and gets dragged along
all the way to the end.

**Pass 2:** index `n-1` is now locked and correct, so there's no point comparing it again. Walk
only from `0` to `n-3` this time. By the end, the second-largest element lands at index `n-2`.

**Pass 3 onward:** same idea — each pass locks in one more element at the back, so each pass
walks a range one shorter than the last. The sorted region grows from the *right*, which is the
mirror image of Selection Sort (whose sorted region grows from the left).

## Why the inner loop shrinks — deriving `i <= n - 2 - j`

Two separate things are going on, and it's worth keeping them apart:

**Why `n - 2` and not `n - 1`:** the comparison is `arr[i] > arr[i+1]`, so the loop body reads
index `i+1`. If `i` were allowed to reach `n-1`, you'd read `arr[n]` — out of bounds. So the
largest safe value of `i` in the very first pass is `n-2`.

**Why subtract `j`:** after `j` passes have completed, the last `j` elements are already
finalised at the back. Comparing into them is wasted work, so the walk stops `j` positions
earlier. Hence pass `j` runs `i` from `0` up to `n - 2 - j`.

| pass `j` | inner range | last index touched (`i+1`) | element locked in |
|--|--|--|--|
| 0 | `0 … n-2` | `n-1` | largest |
| 1 | `0 … n-3` | `n-2` | 2nd largest |
| 2 | `0 … n-4` | `n-3` | 3rd largest |
| … | … | … | … |
| `n-2` | `0 … 0` | `1` | 2nd smallest |

## Why `n - 1` passes, not `n`

Same argument as Selection Sort. Once the largest `n - 1` elements have each been bubbled into
their final position at the back, the one element left at index `0` has nothing left to be
compared against — it's automatically the smallest. So the outer loop runs `j` from `0` to
`n-2`, which is `n - 1` passes.

## Dry run — `[13, 46, 24, 52, 20, 9]`

Sorted (locked) region shown after `//`.

### Pass 1 — `j = 0`, `i` from `0` to `4`

| `i` | compare | in order? | array after |
|--|--|--|--|
| 0 | `13, 46` | yes | `13 46 24 52 20 9` |
| 1 | `46, 24` | no → swap | `13 24 46 52 20 9` |
| 2 | `46, 52` | yes | `13 24 46 52 20 9` |
| 3 | `52, 20` | no → swap | `13 24 46 20 52 9` |
| 4 | `52, 9` | no → swap | `13 24 46 20 9 52` |

Result: `13 24 46 20 9 // 52` — **52 is locked.** Notice how `52` got picked up at `i = 2` and
then rode every remaining comparison to the end. That's the "bubbling."

### Pass 2 — `j = 1`, `i` from `0` to `3`

| `i` | compare | in order? | array after |
|--|--|--|--|
| 0 | `13, 24` | yes | `13 24 46 20 9 // 52` |
| 1 | `24, 46` | yes | `13 24 46 20 9 // 52` |
| 2 | `46, 20` | no → swap | `13 24 20 46 9 // 52` |
| 3 | `46, 9` | no → swap | `13 24 20 9 46 // 52` |

Result: `13 24 20 9 // 46 52` — **46 is locked.**

### Pass 3 — `j = 2`, `i` from `0` to `2`

| `i` | compare | in order? | array after |
|--|--|--|--|
| 0 | `13, 24` | yes | `13 24 20 9 // 46 52` |
| 1 | `24, 20` | no → swap | `13 20 24 9 // 46 52` |
| 2 | `24, 9` | no → swap | `13 20 9 24 // 46 52` |

Result: `13 20 9 // 24 46 52` — **24 is locked.**

### Pass 4 — `j = 3`, `i` from `0` to `1`

| `i` | compare | in order? | array after |
|--|--|--|--|
| 0 | `13, 20` | yes | `13 20 9 // 24 46 52` |
| 1 | `20, 9` | no → swap | `13 9 20 // 24 46 52` |

Result: `13 9 // 20 24 46 52` — **20 is locked.**

### Pass 5 — `j = 4`, `i` from `0` to `0`

| `i` | compare | in order? | array after |
|--|--|--|--|
| 0 | `13, 9` | no → swap | `9 13 // 20 24 46 52` |

Result: `9 13 20 24 46 52` — **sorted.**

`n = 6`, and it took exactly `5 = n - 1` passes. Total comparisons: `5 + 4 + 3 + 2 + 1 = 15`,
which is `n(n-1)/2`.

## The `swapped` flag — early exit optimisation

Declare a `bool swapped = false` **at the top of each pass** (inside the outer loop, so it
resets every round). Set it to `true` whenever a swap happens. If a full pass finishes with
`swapped` still `false`, break out immediately.

**Why this is valid:** a pass that made zero swaps means *every adjacent pair it examined was
already in order*. And "every adjacent pair is in order" is precisely the definition of a
sorted array. Since nothing moved, every remaining pass would compare the exact same values in
the exact same positions and also find nothing to do — pure wasted work.

### Dry run of the flag — `[2, 1, 3, 4, 5]`, `n = 5`

**Pass 1** (`j = 0`, `i` from `0` to `3`), `swapped = false`:

| `i` | compare | action |
|--|--|--|
| 0 | `2 > 1` | swap → `1 2 3 4 5`, set `swapped = true` |
| 1 | `2 > 3` | no |
| 2 | `3 > 4` | no |
| 3 | `4 > 5` | no |

End of pass: `swapped == true` → keep going. Fair enough, something did change, so we can't yet
be sure the array is sorted.

**Pass 2** (`j = 1`, `i` from `0` to `2`), `swapped` reset to `false`:

| `i` | compare | action |
|--|--|--|
| 0 | `1 > 2` | no |
| 1 | `2 > 3` | no |
| 2 | `3 > 4` | no |

End of pass: `swapped == false` → **break.**

| | comparisons | passes |
|--|--|--|
| without flag | `4 + 3 + 2 + 1 = 10` | 4 |
| with flag | `4 + 3 = 7` | 2 |

On an already-sorted array the very first pass swaps nothing, so you break after `n - 1`
comparisons — that's the O(n) best case.

**Two gotchas:**

- `swapped` must be declared/reset **inside** the outer loop. Declare it before the outer loop
  and it stays `true` forever after the first swap, so the check never fires.
- It does nothing for the worst case. A reverse-sorted array swaps on every single pass, so
  `swapped` is always `true` and all `n-1` passes run — still O(n²).

## Complexity

| | Time | Why |
|--|--|--|
| Best case | O(n) *(with flag)* / O(n²) *(without)* | already-sorted input → first pass makes zero swaps → early exit after `n-1` comparisons. Without the flag there's no way to detect this and it grinds through all passes |
| Average case | O(n²) | roughly half the pairs are out of order each pass, so no early exit |
| Worst case | O(n²) | reverse-sorted input → every comparison swaps → all `n-1` passes run in full, `n(n-1)/2` comparisons |
| Space | O(1) | in-place; only a loop counter and a bool |

Bubble Sort is **stable** — equal elements never swap past each other, because the condition is
strict `>` rather than `>=`. Selection Sort in its standard swap-based form is *not* stable.

## Number of swaps — its main weakness

Worst case `n(n-1)/2` swaps — potentially a swap on *every single comparison*. Compare that to
Selection Sort's at-most `n-1` swaps. This is the trade-off between the two:

| | Bubble Sort | Selection Sort |
|--|--|--|
| Comparisons | ~n²/2 | ~n²/2 |
| Swaps | up to n²/2 | at most n-1 |
| Adapts to sorted input | yes, O(n) with flag | no, always O(n²) |
| Stable | yes | no (standard version) |

So: Bubble Sort wins when the data is nearly sorted or stability matters; Selection Sort wins
when swapping is expensive (large structs/objects rather than plain `int`s).

## Pseudocode outline

For each pass `j` from `0` to `n - 2`:
- Set `swapped = false`.
- For each `i` from `0` to `n - 2 - j`:
  - If `arr[i] > arr[i+1]`, swap them and set `swapped = true`.
- If `swapped` is still `false`, break — the array is already sorted.

## C++ implementation

```cpp
void bubbleSort(int arr[], int n) {
    for (int j = 0; j <= n - 2; j++) {     // n-1 passes
        bool swapped = false;              // resets at the start of each pass
        for (int i = 0; i <= n - 2 - j; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;               // no swaps this pass ⇒ already sorted
    }
}
```

Vector version (preferred over raw arrays — `int arr[n]` is a VLA, a C feature that `g++`
allows as an extension but which isn't standard C++):

```cpp
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int j = 0; j <= n - 2; j++) {
        bool swapped = false;
        for (int i = 0; i <= n - 2 - j; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```

Both are safe for `n = 0` and `n = 1`: the outer condition `j <= n-2` is false immediately.
(`n` must be a signed `int` for this — with an unsigned type, `n - 2` underflows to a huge
value when `n < 2`. That's why `int n = arr.size();` above, rather than using `size_t`.)

### The other common loop form (Striver's)

Identical algorithm, just counting the boundary downward instead of counting passes upward:

```cpp
for (int i = n - 1; i >= 1; i--) {         // i = last index still in play
    for (int j = 0; j <= i - 1; j++) {
        if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
    }
}
```

The two forms are related by `i = n - 1 - j`:

| pass # | ascending form `j` | its inner range | descending form `i` | its inner range |
|--|--|--|--|--|
| 1 | `0` | `0 … n-2` | `n-1` | `0 … n-2` |
| 2 | `1` | `0 … n-3` | `n-2` | `0 … n-3` |
| 3 | `2` | `0 … n-4` | `n-3` | `0 … n-4` |
| … | … | … | … | … |
| last | `n-2` | `0 … 0` | `1` | `0 … 0` |

Same ranges, same comparisons, same `n-1` passes. Neither is more correct. The descending form
reads a bit more directly ("everything from `i` onward is already sorted"); the ascending form
makes the pass count obvious.

## Driver program

```cpp
#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int j = 0; j <= n - 2; j++) {
        bool swapped = false;
        for (int i = 0; i <= n - 2 - j; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < n; i++) cin >> arr[i];

    bubbleSort(arr);

    cout << "After bubble sort: " << endl;
    for (int x : arr) cout << x << " ";
    return 0;
}
```

> `#include <bits/stdc++.h>` is a GCC-only header — fine for competitive programming and
> practice, but in real projects include what you actually use (`<vector>`, `<iostream>`,
> `<utility>` for `std::swap`).