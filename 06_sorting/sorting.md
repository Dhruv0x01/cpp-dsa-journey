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

---

# Insertion Sort

**Core idea:** take each element in turn and **insert** it into its correct position among the
elements already handled. Think of sorting a hand of playing cards: the cards in your left hand
are always sorted, you pick up the next card, and you slide it leftward until it sits in the
right place.

The array is mentally split in two:

```
[ sorted part | unsorted part ]
               ^
               the element being placed right now
```

Each pass grows the sorted part by exactly one element.

**Contrast with the other two:**

- Selection Sort also grows its sorted region from the left, but it *searches the unsorted part*
  for the right value to put next. Insertion Sort does the opposite — it takes whatever value
  comes next and *searches the sorted part* for where that value belongs.
- Bubble Sort also works purely by adjacent swaps, but it walks the *whole* remaining range
  every pass. Insertion Sort walks left only as far as it needs to, then stops. That single
  difference is what makes it genuinely fast on nearly-sorted data rather than just
  early-exiting once at the end.

## How it works

**Pass 0 (implicit):** index `0` alone is trivially a sorted array of size 1. Nothing to do —
which is why the outer loop starts at `i = 1`, not `i = 0`.

**Pass `i`:** treat `arr[0 … i-1]` as sorted and take `arr[i]` as the element to place. Compare
it with its left neighbour. If it's smaller, swap and repeat; keep walking left until either

- it's no longer smaller than the element on its left (correct spot found → `break`), or
- it has reached index `0` (it was the smallest so far).

**After pass `i`:** `arr[0 … i]` is sorted. Repeat until `i = n-1`.

Important subtlety: unlike Selection Sort, an element already in the "sorted" region is **not
in its final position** — later insertions will keep shifting it rightward. The region is
sorted *relative to itself*, not finalised.

## Why the early `break` is the whole point

Once `arr[j] >= arr[j-1]`, you can stop the inner loop immediately. The left part is already
sorted, so everything further left is also `<= arr[j-1] <= arr[j]` — there is nothing left that
could need to move. No other simple sort gets to stop this early inside a pass.

Consequence: on an already-sorted array every inner loop breaks after a single comparison, so
the whole thing costs `n-1` comparisons — **O(n) best case**, with no extra flag or bookkeeping
needed. Bubble Sort needs an explicit `swapped` flag to achieve the same thing; Selection Sort
can't achieve it at all.

## Dry run — `[13, 46, 24, 52, 20, 9]`

Sorted (relatively-ordered) region shown before `//`.

| Pass `i` | Element being inserted | Comparisons walking left | Array after pass |
|--|--|--|--|
| Start | — | — | `13 // 46 24 52 20 9` |
| 1 | `46` | `46 > 13` → stop immediately | `13 46 // 24 52 20 9` |
| 2 | `24` | `24 < 46` swap; `24 > 13` stop | `13 24 46 // 52 20 9` |
| 3 | `52` | `52 > 46` → stop immediately | `13 24 46 52 // 20 9` |
| 4 | `20` | `<52` swap, `<46` swap, `<24` swap, `>13` stop | `13 20 24 46 52 // 9` |
| 5 | `9` | `<52`, `<46`, `<24`, `<20`, `<13` — all swap, reaches index 0 | `9 13 20 24 46 52` — **sorted** |

Notice passes 1 and 3 cost one comparison each because the incoming element was already bigger
than everything before it. Bubble Sort has no equivalent shortcut *within* a pass.

**Cost of this run:** 13 comparisons and 9 swaps, versus Bubble Sort's fixed 15 comparisons on
the same input. Worst case for both is `n(n-1)/2 = 15`.

## Complexity

| | Time | Why |
|--|--|--|
| Best case | O(n) | already sorted → each inner loop breaks after 1 comparison → `n-1` comparisons, 0 swaps. No flag required, it falls out of the `break` |
| Average case | O(n²) | each element travels about half the sorted region on average → ~n²/4 comparisons |
| Worst case | O(n²) | reverse sorted → element `i` walks all the way to index 0 → `1+2+…+(n-1) = n(n-1)/2` comparisons *and* the same number of swaps |
| Space | O(1) | in-place; one loop counter each, no auxiliary array |

**Stable:** yes. The condition is strict `<`, so an element never swaps past an equal element.

**Adaptive:** yes, and more meaningfully than Bubble Sort. If every element is at most `k`
positions from its correct place, insertion sort runs in O(n·k) — it does real work
proportional to how out of order the data actually is. This is why it's the base case inside
real-world hybrid sorts: `std::sort` (introsort) switches to insertion sort for small
subarrays, and Timsort (Python, Java) builds its initial runs with it.

## Number of swaps

Worst case `n(n-1)/2` — same as Bubble Sort, since both move elements only by adjacent swaps.
But the *average* is far better because of the early break, and the swap-based version can be
improved further (see below).

### Optimisation: shift instead of swap

Every `swap` is three assignments (`tmp = a; a = b; b = tmp`). Since the element being inserted
is the same value in every swap of a pass, you can hold it in a temporary once, shift the
larger elements one slot right, and drop it in at the end — roughly **one third the writes**:

```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];              // hold the element being inserted
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];       // shift right, no swap
            j--;
        }
        arr[j + 1] = key;              // drop it into the gap
    }
}
```

The `j >= 0` check must come **first** in the `&&` — short-circuit evaluation is what stops
`arr[j]` being read at `j = -1`. Same algorithm, same complexity, fewer memory writes.

## Pseudocode outline

For each `i` from `1` to `n - 1`:
- For `j` from `i` down to `1`:
  - If `arr[j] < arr[j-1]`, swap them.
  - Otherwise break — `arr[j]` is already in its correct place.

## C++ implementation

```cpp
void insertionSort(int arr[], int n) {
    // i marks the element being inserted into the sorted left part.
    // Starts at 1 because arr[0] alone is already "sorted".
    for (int i = 1; i <= n - 1; i++) {

        // Walk arr[i] leftwards one swap at a time until it lands
        // in its correct position inside the sorted part.
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);   // still too far right, keep going
            } else {
                break;                      // correct spot found — left side is sorted,
            }                               // so nothing further left can need moving
        }
    }
}
```

Vector version:

```cpp
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
}
```

Both are safe for `n = 0` and `n = 1` — the outer loop simply never runs. (No `n - 2`
underflow risk here, unlike Bubble Sort, since the bound is `i < n`.)

## Driver program

```cpp
#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < n; i++) cin >> arr[i];

    insertionSort(arr);

    cout << "After insertion sort: " << endl;
    for (int x : arr) cout << x << " ";
    return 0;
}
```

---

# Merge Sort

**Core idea:** sorting a big array is hard; **merging two already-sorted arrays is easy**. So
split the array in half, sort each half (recursively, by the same logic), then merge the two
sorted halves back together. Keep splitting until each piece has one element — a one-element
array is sorted by definition, and that's the base case that stops the recursion.

This is the first **divide and conquer** algorithm in the course, and the first one that breaks
the O(n²) barrier. The three previous sorts all worked by repeatedly scanning and swapping
within one flat array. Merge sort doesn't scan for anything — it *restructures the problem*
into smaller copies of itself.

**Contrast with the previous three:**

- Selection / Bubble / Insertion all move elements by comparing them against *other individual
  elements*. Merge sort compares two *sorted blocks* against each other, which is what buys the
  speed: one pass over `n` elements resolves the order of two whole halves at once.
- All three earlier sorts are **in-place** (O(1) extra space). Merge sort is **not** — it needs
  an O(n) temporary buffer. That's the price of the speedup.
- All three earlier sorts do their work *going forward* through the array. Merge sort does all
  its actual work **on the way back up** out of the recursion.

## The two halves of the algorithm

Keep these mentally separate — this is where most confusion comes from:

| function | what it does | does it sort anything? |
|--|--|--|
| `mergeSort()` | splits the range in two, recurses on each half | **no** — it only divides |
| `merge()` | combines two adjacent sorted ranges into one sorted range | **yes** — all the real work |

`mergeSort` is pure bookkeeping. Every element that ends up in the right place was put there by
`merge`.

## How it works

**Divide:** given range `arr[low … high]`, compute `mid` and split into `arr[low … mid]` and
`arr[mid+1 … high]`. Note both ends are **inclusive** throughout, and `mid` belongs to the
*left* half — which is why the right half starts at `mid + 1`.

**Conquer:** recursively `mergeSort` each half. Trust that they come back sorted. (This is the
leap of faith recursion always asks for — don't try to trace all the way down in your head,
just assume the recursive call honours its contract.)

**Combine:** `merge` the two sorted halves into one sorted range.

**Base case:** `if (low >= high) return;` — a range of size 0 or 1 is already sorted, so there's
nothing to split and nothing to merge. Without this the recursion never terminates.

## Recursion tree — `[13, 46, 24, 52, 20, 9]`

```
                     [13,46,24,52,20,9]                  (0,5)  mid=2
                    /                  \
           [13,46,24]                  [52,20,9]         (0,2) (3,5)
           /        \                  /       \
      [13,46]      [24]           [52,20]      [9]       (0,1) (2,2) (3,4) (5,5)
      /     \                     /     \
   [13]     [46]               [52]     [20]             base cases: size 1
```

Going **down** = splitting (mergeSort). Going **back up** = merging (merge).
The merges happen in this order:

| # | merge call | left half | right half | result written back |
|--|--|--|--|--|
| 1 | `merge(0,0,1)` | `[13]` | `[46]` | `[13,46]` |
| 2 | `merge(0,1,2)` | `[13,46]` | `[24]` | `[13,24,46]` |
| 3 | `merge(3,3,4)` | `[52]` | `[20]` | `[20,52]` |
| 4 | `merge(3,4,5)` | `[20,52]` | `[9]` | `[9,20,52]` |
| 5 | `merge(0,2,5)` | `[13,24,46]` | `[9,20,52]` | `[9,13,20,24,46,52]` |

Note the whole left subtree finishes before the right subtree starts — that's just how the two
recursive calls are sequenced. Also: **5 merge calls for 6 elements**. In general a merge sort
on `n` elements performs exactly `n - 1` merges (one per internal node of the tree).

## The merge step in detail

This is the part worth understanding cold, because it reappears on its own in problems.

**The contract:** `merge(arr, low, mid, high)` assumes `arr[low…mid]` is sorted **and**
`arr[mid+1…high]` is sorted. It has no idea how they got that way and doesn't care.

**The trick:** because both halves are sorted, the smallest unused element in the whole range is
always sitting at the *front* of one half or the other. You never have to search. So: keep a
pointer at the front of each half, compare the two, take the smaller, advance that pointer.
Repeat.

**Three phases:**

1. **Two-pointer walk** — while *both* halves still have elements, take the smaller front
   element into `temp`.
2. **Drain the leftovers** — the loop above exits the moment one half runs dry. The other half
   still has elements, and they're already sorted *and* all larger than everything in `temp`,
   so just append them in order. Exactly one of the two drain loops actually runs.
3. **Copy back** — `temp` is a separate 0-indexed buffer; copy it into `arr[low…high]`.

### Walking the final merge — `merge(0, 2, 5)`

Left half `[13,24,46]` (indices 0–2), right half `[9,20,52]` (indices 3–5).

| step | `arr[left]` | `arr[right]` | comparison | take | `temp` after |
|--|--|--|--|--|--|
| 1 | `13` | `9` | `13 <= 9`? no | right `9` | `[9]` |
| 2 | `13` | `20` | `13 <= 20`? yes | left `13` | `[9,13]` |
| 3 | `24` | `20` | `24 <= 20`? no | right `20` | `[9,13,20]` |
| 4 | `24` | `52` | `24 <= 52`? yes | left `24` | `[9,13,20,24]` |
| 5 | `46` | `52` | `46 <= 52`? yes | left `46` | `[9,13,20,24,46]` |
| — | *exhausted* | `52` | left half empty → exit loop | — | — |
| drain | — | `52` | append remaining right half | `52` | `[9,13,20,24,46,52]` |

Then copy `temp` back into `arr[0…5]`. **Sorted.**

Five comparisons for six elements — a merge of a total of `k` elements costs at most `k - 1`
comparisons and exactly `k` writes.

### `<=` vs `<` — this is what makes merge sort stable

In `if (arr[left] <= arr[right])`, the `<=` means **on a tie, take from the left half**. Since
the left half holds elements that came earlier in the original array, equal elements keep their
original relative order. Change it to `<` and merge sort silently stops being stable. This is a
standard interview question.

### The `i - low` offset — the classic bug

`temp` is its own vector starting at index `0`, but you're writing back into `arr[low…high]`.
So the mapping is:

```
arr[low]     <- temp[0]
arr[low + 1] <- temp[1]
arr[i]       <- temp[i - low]
```

Forgetting the `- low` is *the* merge sort bug, and it's nasty because the top-level call has
`low == 0`, where the wrong version works fine. It only breaks in the recursive sub-calls, so
tiny test arrays may still pass.

## Why `mid + 1` and not `mid`

`mid` already belongs to the left half. Calling `mergeSort(arr, mid, high)` would put `mid` in
*both* halves — the range never shrinks, and you get infinite recursion / stack overflow. The
two halves must **partition** the range: every index in exactly one of them.

## Why `low + (high - low) / 2` instead of `(low + high) / 2`

Mathematically identical, but `low + high` can exceed `INT_MAX` and overflow when the array is
large. Harmless for practice arrays, but build the habit now — **this exact bug returns in
Binary Search (Step 4)**, and it's famous: it sat undetected in Java's standard library
`binarySearch` for nine years.

## Complexity

| | Time | Why |
|--|--|--|
| Best case | O(n log n) | no shortcuts exist — it splits and merges the same way regardless of input |
| Average case | O(n log n) | same |
| Worst case | O(n log n) | same — **guaranteed**, which quick sort can't promise |
| Space | **O(n)** | the `temp` buffer, plus O(log n) recursion stack |

### Deriving the O(n log n)

**Height of the tree = log₂n.** Each level halves the range, so from `n` you get
`n → n/2 → n/4 → … → 1`. The number of halvings needed is `log₂n`. For `n = 8`: 8 → 4 → 2 → 1,
that's 3 levels of splitting, and `log₂8 = 3`. ✓

**Work per level = O(n).** At any given level of the tree, the ranges are disjoint and together
cover all `n` elements. Merging them touches each element exactly once. So every level costs
O(n) total, no matter how many separate merges that level is split across:

| level | ranges | elements merged at this level |
|--|--|--|
| bottom | 8 ranges of 1 | 8 |
| next | 4 merges of 2 | 8 |
| next | 2 merges of 4 | 8 |
| top | 1 merge of 8 | 8 |

**Total = O(n) per level × O(log n) levels = O(n log n).**

That's the whole derivation, and it's the template for analysing *every* divide-and-conquer
algorithm you'll meet later.

### Space — the one real weakness

O(n) auxiliary space for `temp`. At the top-level merge, `temp` holds all `n` elements at once.
Compare: Selection, Bubble and Insertion are all O(1). Quick sort (next up) is also O(1)
auxiliary — that's its main argument over merge sort, alongside better cache behaviour.

Plus **O(log n) stack space** for the recursion depth. Rarely a problem, but it's a real cost
and worth mentioning if asked "is merge sort in-place?" — the honest answer is *no, on both
counts*.

> **Common optimisation:** declaring `vector<int> temp` inside `merge` means allocating a fresh
> vector on every one of the `n-1` merge calls. Allocating one buffer of size `n` up front and
> passing it by reference is measurably faster. Worth knowing exists; not worth doing while
> you're still learning the shape.

## Stability and adaptivity

**Stable:** yes — from the `<=`, as above. This is why `std::stable_sort` is a merge sort
variant while `std::sort` (introsort: quicksort + heapsort + insertion sort) is not stable.

**Adaptive:** no, not by default. An already-sorted array costs exactly the same as a random
one. There is a cheap fix though:

```cpp
if (arr[mid] <= arr[mid + 1]) return;   // left half entirely <= right half
merge(arr, low, mid, high);             // ...so they're already in order
```

If the largest element of the left half is already `<=` the smallest of the right half, the
merge is a no-op. On sorted input this makes the whole algorithm O(n). This one-line idea is
the seed of **Timsort** (Python's and Java's real sort), which detects already-sorted "runs" in
the input and merges those instead of blindly splitting to size 1.

## Number of swaps

**Zero.** Merge sort never swaps — it *copies*. Total writes are `O(n log n)` (each level
writes every element once into `temp` and once back). This makes it the odd one out against the
previous three, all of which move data purely by swapping.

## Pseudocode outline

**mergeSort(arr, low, high):**
- If `low >= high`, return — range of size ≤ 1 is already sorted.
- `mid = low + (high - low) / 2`
- `mergeSort(arr, low, mid)` — sort left half
- `mergeSort(arr, mid + 1, high)` — sort right half
- `merge(arr, low, mid, high)` — combine

**merge(arr, low, mid, high):**
- `left = low`, `right = mid + 1`, empty buffer `temp`
- While `left <= mid` **and** `right <= high`: push the smaller of `arr[left]` / `arr[right]`
  into `temp` (ties → left), advance that pointer.
- While `left <= mid`: push `arr[left++]`.
- While `right <= high`: push `arr[right++]`.
- For `i` from `low` to `high`: `arr[i] = temp[i - low]`.

## C++ implementation

```cpp
// PRECONDITION: arr[low..mid] is sorted AND arr[mid+1..high] is sorted.
void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    temp.reserve(high - low + 1);      // optional: avoids vector regrowth

    int left  = low;                   // pointer into the LEFT half
    int right = mid + 1;               // pointer into the RIGHT half

    // Phase 1: both halves still have elements — take the smaller front one.
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) { // <= keeps merge sort STABLE
            temp.push_back(arr[left++]);
        } else {
            temp.push_back(arr[right++]);
        }
    }

    // Phase 2: one half ran out. Drain the other — it's already sorted and
    // everything in it is larger than everything in temp.
    while (left  <= mid)  temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);

    // Phase 3: copy back. temp is 0-indexed, arr starts at low → offset by low.
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

// Sorts arr[low..high]. Both ends INCLUSIVE.
void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;                 // base case: size 0 or 1

    int mid = low + (high - low) / 2;        // overflow-safe midpoint

    mergeSort(arr, low, mid);                // sort left half
    mergeSort(arr, mid + 1, high);           // sort right half
    merge(arr, low, mid, high);              // combine the two sorted halves
}
```

Raw-array version (same logic, if you're following Striver's signature):

```cpp
void merge(int arr[], int low, int mid, int high);
void mergeSort(int arr[], int low, int high);
```

Everything inside is identical — `vector<int>&` just avoids the array-decays-to-pointer
awkwardness and works directly with LeetCode's signatures.

## Driver program

```cpp
#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    temp.reserve(high - low + 1);
    int left = low, right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) temp.push_back(arr[left++]);
        else                         temp.push_back(arr[right++]);
    }
    while (left  <= mid)  temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++) arr[i] = temp[i - low];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < n; i++) cin >> arr[i];

    mergeSort(arr, 0, n - 1);          // 0 and n-1 because both ends are inclusive

    cout << "After merge sort: " << endl;
    for (int x : arr) cout << x << " ";
    return 0;
}
```

Safe for `n = 0`: the call becomes `mergeSort(arr, 0, -1)` and `low >= high` returns
immediately.

## Where merge sort shows up beyond sorting

The `merge` function is a reusable tool in its own right — this is the real reason to learn it
properly rather than just memorising the sort.

- **LC 88 — Merge Sorted Array.** Literally just the merge step. Do this one next.
- **Count Inversions** (pairs `i < j` with `arr[i] > arr[j]`). In phase 1, every time you take
  from the *right* half, that element is smaller than **all** `mid - left + 1` remaining
  elements of the left half — so add that count. Turns an O(n²) brute force into O(n log n).
  This is the single most common merge-sort-based interview problem.
- **Count Reverse Pairs** (LC 493), **Count of Smaller Numbers After Self** (LC 315) — same
  trick, different counting condition.
- **External sorting** — sorting data too large to fit in RAM. You can merge two sorted files
  by streaming them with two pointers and never holding more than a couple of records in
  memory. No in-place algorithm can do this. It's why merge sort exists in practice.
- **Sorting linked lists** — merge sort is the *preferred* O(n log n) sort for linked lists,
  because merging requires only pointer rewiring (O(1) extra space, no random access needed).
  Quick sort needs random access to be efficient. See **LC 148 — Sort List** at Step 6.

## Merge sort vs quick sort (preview)

| | Merge Sort | Quick Sort |
|--|--|--|
| Worst case | **O(n log n)** guaranteed | O(n²) on bad pivots |
| Average | O(n log n) | O(n log n), smaller constant → usually **faster in practice** |
| Auxiliary space | O(n) | O(1) (+ O(log n) stack) |
| Stable | **yes** | no (standard version) |
| Splits | always exactly in half, by **position** | splits by **value** around a pivot; sizes vary |
| Work happens | on the way **up** (merge) | on the way **down** (partition) |

They're mirror images: merge sort does trivial splitting and clever combining; quick sort does
clever splitting and trivial combining (nothing at all, in fact — once partitioned around the
pivot, the halves need no recombination).

---

# Quick Sort

**Core idea:** pick one element as the **pivot**, then rearrange the array so that everything
smaller than the pivot sits to its left and everything larger sits to its right. The pivot is
now in its **final sorted position** — permanently, never to move again. Recurse on the left
part and the right part. When every element has had a turn as a pivot, the array is sorted.

There is **no combine step.** That's the whole trick. Once the two sides are each sorted
internally, the array is sorted, because the partition already guaranteed that everything left
of the pivot belongs left of it and everything right belongs right.

**The mirror image of merge sort:**

| | Merge Sort | Quick Sort |
|--|--|--|
| Divide | trivial — cut at `mid`, no thought required | **hard** — partition around a pivot |
| Combine | **hard** — the whole `merge` function | trivial — literally nothing |
| Work happens | on the way **back up** the recursion | on the way **down** |
| Splits by | **position** (always exactly half) | **value** (halves can be any size) |

Merge sort splits stupidly and combines cleverly. Quick sort splits cleverly and doesn't need
to combine at all. Both reach O(n log n), from opposite directions.

## The two halves of the algorithm

Same separation of concerns as merge sort — keep them apart in your head:

| function | what it does | does it sort anything? |
|--|--|--|
| `quickSort()` | recurses on the two sides of the pivot | **no** — pure bookkeeping |
| `partition()` | places ONE element (the pivot) in its final spot | **yes** — all the real work |

Every element ends up in the right place by being a pivot exactly once.

## How it works

**Choose a pivot.** This version uses `arr[low]`, the first element of the range. (Simplest
choice, and also the weakest — see the worst case below.)

**Partition.** Rearrange `arr[low…high]` so that:

```
[ elements <= pivot | pivot | elements > pivot ]
                      ^
                      returned index p — this element is DONE forever
```

**Recurse** on `arr[low…p-1]` and `arr[p+1…high]`. Note the pivot at index `p` is excluded from
both — it's already final, so re-examining it would be wasted work (and would break the
"range always shrinks" guarantee, causing infinite recursion).

**Base case:** `if (low >= high) return;` — a range of size 0 or 1 needs no work.

### The one big difference from merge sort

In merge sort, **nothing** is in its final position until the very last merge completes. In
quick sort, the pivot is final the instant `partition` returns. The sorted region isn't a
contiguous block growing from one side — it's a scattered set of already-placed pivots that
gradually fills in.

## The partition step in detail

This is the part to understand cold. Everything else is a three-line wrapper.

**The goal:** find where the pivot belongs, and get everything else onto the correct side of it,
in a single pass, without any extra memory.

**The idea:** run two pointers toward each other.

- `i` walks **rightward** from `low`, looking for an element that is **bigger** than the pivot —
  i.e. an element that's on the wrong side (it's on the left but belongs on the right).
- `j` walks **leftward** from `high`, looking for an element that is **`<=`** the pivot — again,
  wrong side (it's on the right but belongs on the left).

When both pointers have found a misplaced element and haven't crossed yet, **swap them** — one
exchange fixes two problems at once. Repeat until the pointers cross.

**When they cross**, `j` is sitting at the boundary: the last position holding a value `<=`
pivot. Swap the pivot (still parked at `low`) with `arr[j]`, and the pivot lands exactly on
that boundary. Return `j`.

### Why swap with `j` and not `i`

At the moment the loop exits, `j < i`. The `j` scan stops only on an element that is `<=` pivot,
so `arr[j] <= pivot` is guaranteed — safe to move to the left side. The `i` scan stops only on
an element `> pivot`, so `arr[i] > pivot`. Swapping the pivot with `arr[i]` would put a value
greater than the pivot *before* it. **Wrong.** It must be `j`.

### Why the conditions are asymmetric — `<=` on one side, `>` on the other

```cpp
while (arr[i] <= pivot && ...) i++;   // note <=
while (arr[j] >  pivot && ...) j--;   // note >  (strict)
```

Both pointers must be able to *step over* elements equal to the pivot, but only one side should
*stop* on them — otherwise arrays full of duplicates behave badly. With `<=` on the `i` scan,
`i` skips past equal elements; with strict `>` on the `j` scan, `j` stops on them. Make both
non-strict and you get infinite loops on all-equal input; make both strict and equal elements
pile up in a way that degrades the split.

Take `[5, 5, 5, 5]` with pivot `5`: the `i` scan runs to the bounds guard, `j` stops
immediately, they cross, and the pivot lands at `low` — the partition is lopsided but it
**terminates**, which is the important part.

### The bounds guards — `i <= high-1` and `j >= low+1`

These stop the scans from running off the end of the range.

- If the pivot is the **maximum** of the range, nothing is `> pivot`, so the `i` scan would run
  forever rightward. `i <= high-1` stops it.
- If the pivot is the **minimum**, nothing is `<= pivot` except the pivot itself, so the `j`
  scan would run leftward past `low`. `j >= low+1` stops it.

Forget either and you get out-of-bounds reads on exactly the inputs that look most innocent
(already-sorted arrays). This is the most common quick sort bug when re-coding from memory.

## Dry run — `[13, 46, 24, 52, 20, 9]`

### Call 1: `quickSort(0, 5)` — pivot `13`

| action | `i` | `j` | array after |
|--|--|--|--|
| start, pivot = `arr[0]` = `13` | 0 | 5 | `13 46 24 52 20 9` |
| `i` scans right past `13`, stops at `46` (>13). `j` stops at `9` (not >13). Not crossed → **swap** | 1 | 5 | `13 9 24 52 20 46` |
| `i` skips `9`, stops at `24` (>13). `j` walks left past `46,20,52,24`, stops at `9`. **Crossed** (i=2 > j=1) | 2 | 1 | `13 9 24 52 20 46` |
| swap pivot `arr[0]` ↔ `arr[1]` | — | — | `9 13 24 52 20 46` |

**Returns `p = 1`.** `13` is now permanently at index 1. Left side `[9]`, right side
`[24,52,20,46]`.

### Call 2: `quickSort(2, 5)` — pivot `24`

(`quickSort(0,0)` is a base case, returns immediately.)

| action | `i` | `j` | array after |
|--|--|--|--|
| start, pivot = `arr[2]` = `24` | 2 | 5 | `9 13 24 52 20 46` |
| `i` stops at `52` (>24). `j` skips `46`, stops at `20`. Not crossed → **swap** | 3 | 4 | `9 13 24 20 52 46` |
| `i` skips `20`, stops at `52`. `j` stops at `20`. **Crossed** | 4 | 3 | `9 13 24 20 52 46` |
| swap pivot `arr[2]` ↔ `arr[3]` | — | — | `9 13 20 24 52 46` |

**Returns `p = 3`.** `24` is final at index 3.

### Call 3: `quickSort(4, 5)` — pivot `52`

| action | `i` | `j` | array after |
|--|--|--|--|
| start, pivot = `arr[4]` = `52` | 4 | 5 | `9 13 20 24 52 46` |
| `i` scans past `52` but hits the guard `i <= high-1 = 4` → stops at 5. `j` stops at `46`. `i == j`, loop exits | 5 | 5 | `9 13 20 24 52 46` |
| swap pivot `arr[4]` ↔ `arr[5]` | — | — | `9 13 20 24 46 52` |

**Returns `p = 5`.** Then `quickSort(4,4)` and `quickSort(6,5)` are both base cases.

**Final: `9 13 20 24 46 52`** ✓

### Recursion tree for this run

```
                 quickSort(0,5)  pivot 13 -> lands at index 1
                /                                    \
      quickSort(0,0)                          quickSort(2,5)  pivot 24 -> index 3
        base case                            /                        \
                                  quickSort(2,2)              quickSort(4,5)  pivot 52 -> index 5
                                    base case                /               \
                                                    quickSort(4,4)      quickSort(6,5)
                                                      base case           base case
```

Notice this tree is **lopsided** — it leans right the whole way down. Depth 3 for only 6
elements. Every pivot happened to be near the small end of its range, so each partition peeled
off just one element instead of splitting in half. That's quick sort's weakness in miniature,
and it's exactly what the worst case below is about. Merge sort's tree for the same input is
perfectly balanced regardless of the values.

## Complexity

| | Time | Why |
|--|--|--|
| Best case | O(n log n) | pivot lands near the middle every time → range halves each level → `log n` levels × O(n) partition work per level |
| Average case | O(n log n) | on random input the pivot is "good enough" — even a consistent 25/75 split still gives O(n log n), just with a bigger constant |
| Worst case | **O(n²)** | pivot is the min or max every time → split is 0 and n-1 → `n` levels × O(n) work |
| Space | **O(1) auxiliary** + O(log n) stack (average), O(n) stack (worst) | partitions in place — no `temp` buffer |

### The recurrence

Partitioning a range of size `n` costs O(n) — each pointer walks part of the range, together
covering it once. So:

```
T(n) = T(size of left) + T(size of right) + O(n)
```

**Balanced:** `T(n) = 2·T(n/2) + O(n)` → the merge sort recurrence → **O(n log n)**.

**Degenerate:** `T(n) = T(0) + T(n-1) + O(n)` → `n + (n-1) + (n-2) + … = n(n-1)/2` → **O(n²)**.

### What actually triggers the worst case — the cruel irony

With `pivot = arr[low]`, the killer input is an **already-sorted array** (or reverse-sorted).

Every pivot is the minimum of its range, so every partition splits into `[]` and `[rest]`, and
the recursion depth becomes `n` instead of `log n`. Quick sort's *worst* input is the one every
other algorithm finds easiest — insertion sort does sorted input in O(n), merge sort in
O(n log n) as always, and quick sort blows up to O(n²).

Worse, the recursion depth `n` means **stack overflow**, not just slowness. At `n = 10⁵`
sorted input, this implementation crashes rather than merely running slowly.

### The fix — randomise the pivot

One line at the top of `partition`:

```cpp
swap(arr[low], arr[low + rand() % (high - low + 1)]);
```

Pick a random element from the range and move it to `low`, then proceed exactly as before. Now
no *specific* input is bad — an adversary can't hand you a killer array, because the pivot
doesn't depend on the input's arrangement. The O(n²) worst case still exists mathematically
but becomes vanishingly unlikely (probability of `k` consecutive terrible pivots decays
exponentially).

Other common strategies:

- **Median-of-three** — take the median of `arr[low]`, `arr[mid]`, `arr[high]`. Cheap,
  deterministic, and handles sorted input well. Common in real libraries.
- **Introsort** — what `std::sort` actually does. Runs quick sort, tracks recursion depth, and
  if it exceeds `2·log n` (meaning pivots have been bad), switches to heap sort to guarantee
  O(n log n). Below ~16 elements it switches to insertion sort. Best of all three worlds.

### Space — quick sort's main advantage

**O(1) auxiliary.** No `temp` buffer, unlike merge sort's O(n). All the rearranging happens by
swapping inside the original array. Combined with better cache locality (it works on
contiguous ranges instead of copying between two arrays), this is why quick sort usually beats
merge sort in wall-clock time despite the same asymptotic complexity.

The recursion stack is O(log n) on average but O(n) in the worst case. You can force it to
O(log n) always by recursing on the **smaller** side and looping on the larger:

```cpp
while (low < high) {
    int p = partition(arr, low, high);
    if (p - low < high - p) {           // recurse into the smaller side only
        quickSort(arr, low, p - 1);
        low = p + 1;                    // ...and loop on the bigger side
    } else {
        quickSort(arr, p + 1, high);
        high = p - 1;
    }
}
```

Worth knowing exists; not worth writing while you're learning the shape.

## Stability and adaptivity

**Stable:** **no.** Partition swaps elements across long distances, so two equal elements can
easily be reordered relative to each other. This is why `std::sort` (introsort) is *not*
stable while `std::stable_sort` (merge sort based) is. Making quick sort stable requires O(n)
extra space — at which point you may as well use merge sort.

**Adaptive:** **no — worse than no.** Sorted input isn't merely un-helpful, it's the *worst*
case for the naive pivot. Compare:

| input | Insertion Sort | Merge Sort | Quick Sort (pivot = arr[low]) |
|--|--|--|--|
| already sorted | **O(n)** | O(n log n) | **O(n²)** ← worst case |
| reverse sorted | O(n²) | O(n log n) | **O(n²)** ← worst case |
| random | O(n²) | O(n log n) | O(n log n) |

## Number of swaps

O(n log n) on average — each level of recursion performs at most `n/2` swaps in its partitions,
across `log n` levels. Worst case O(n²).

Compared to merge sort's zero swaps and `O(n log n)` copies: quick sort's swaps operate in
place, so the total *memory traffic* is lower even when the operation count is similar.

## Handling duplicates — 3-way partitioning

The version above puts elements equal to the pivot on the left side, so an array like
`[5,5,5,5,5]` degrades toward O(n²) — every partition peels off one element. **Dutch National
Flag** partitioning fixes this by splitting into three regions instead of two:

```
[ < pivot | == pivot | > pivot ]
```

Everything equal to the pivot is now final in one pass, so you recurse only on the strictly-
smaller and strictly-larger parts. On input with many duplicates this turns O(n²) into O(n).

**You already know this pattern from LC 75 (Sort Colors)** — sorting `0`s, `1`s and `2`s with
three pointers *is* a 3-way partition with the pivot fixed at `1`. Same algorithm, stripped to
its simplest case.

## Pseudocode outline

**partition(arr, low, high) → index:**
- `pivot = arr[low]`, `i = low`, `j = high`
- While `i < j`:
  - Advance `i` right while `arr[i] <= pivot` **and** `i <= high-1`
  - Advance `j` left while `arr[j] > pivot` **and** `j >= low+1`
  - If `i < j`, swap `arr[i]` and `arr[j]`
- Swap `arr[low]` and `arr[j]`
- Return `j`

**quickSort(arr, low, high):**
- If `low >= high`, return — size 0 or 1
- `p = partition(arr, low, high)`
- `quickSort(arr, low, p - 1)` — left side
- `quickSort(arr, p + 1, high)` — right side, pivot at `p` excluded from both

## C++ implementation

```cpp
// Places arr[low] at its final sorted position and returns that index.
// AFTER: everything in arr[low..p-1] is <= pivot, everything in arr[p+1..high] is > pivot.
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        // scan RIGHT for an element bigger than the pivot (it's on the wrong side).
        // i <= high-1 stops the scan running off the end when pivot is the maximum.
        while (arr[i] <= pivot && i <= high - 1) i++;

        // scan LEFT for an element <= the pivot (also on the wrong side).
        // j >= low+1 stops the scan when pivot is the minimum.
        while (arr[j] > pivot && j >= low + 1) j--;

        // both found something misplaced and haven't crossed -> one swap fixes both
        if (i < j) swap(arr[i], arr[j]);
    }

    // Loop exited => j has crossed below i, so arr[j] <= pivot is guaranteed.
    // That makes index j the boundary, i.e. the pivot's true home. (NOT arr[i] —
    // arr[i] > pivot, so swapping there would put a bigger value before the pivot.)
    swap(arr[low], arr[j]);
    return j;
}

// Sorts arr[low..high]. Both ends INCLUSIVE.
void quickSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;                 // base case: size 0 or 1

    int p = partition(arr, low, high);       // pivot is now FINAL at index p

    quickSort(arr, low, p - 1);              // sort everything left of the pivot
    quickSort(arr, p + 1, high);             // sort everything right of it
    // no combine step — the partition already guaranteed the ordering between sides
}
```

Raw-array version (Striver's signature) — identical body, just `int arr[]` instead of
`vector<int>&`:

```cpp
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
```

### Randomised-pivot version (use this one for anything real)

```cpp
int partition(vector<int>& arr, int low, int high) {
    // Move a RANDOM element of the range to low, then partition as usual.
    // Kills the O(n^2) worst case on sorted / reverse-sorted input.
    swap(arr[low], arr[low + rand() % (high - low + 1)]);

    int pivot = arr[low];
    int i = low, j = high;
    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) i++;
        while (arr[j] >  pivot && j >= low + 1)  j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}
```

### The other common form — Lomuto partition

Different partition scheme, same algorithm. Pivot is the **last** element, one pointer tracks
the boundary:

```cpp
int partitionLomuto(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;                       // boundary of the "<= pivot" region
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);           // drop the pivot just past the boundary
    return i + 1;
}
```

| | Hoare-style (above, Striver's) | Lomuto |
|--|--|--|
| Pivot | first element | last element |
| Pointers | two, moving toward each other | one scanning pointer + one boundary |
| Swaps | ~3× fewer | more |
| Reads more easily | no | **yes** |
| Handles duplicates | better | degrades badly on all-equal input |

Lomuto is easier to remember and is what CLRS teaches. The two-pointer form is faster and is
what Striver uses. Know both exist; write whichever you can reproduce correctly under pressure.

## Driver program

```cpp
#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low, j = high;
    while (i < j) {
        while (arr[i] <= pivot && i <= high - 1) i++;
        while (arr[j] >  pivot && j >= low + 1)  j--;
        if (i < j) swap(arr[i], arr[j]);
    }
    swap(arr[low], arr[j]);
    return j;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int p = partition(arr, low, high);
    quickSort(arr, low, p - 1);
    quickSort(arr, p + 1, high);
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < n; i++) cin >> arr[i];

    quickSort(arr, 0, n - 1);          // 0 and n-1 because both ends are inclusive

    cout << "After quick sort: " << endl;
    for (int x : arr) cout << x << " ";
    return 0;
}
```

Safe for `n = 0`: the call becomes `quickSort(arr, 0, -1)` and `low >= high` returns
immediately.

> Note on `int arr[n]`: that's a **VLA** (variable-length array), a C feature `g++` allows as an
> extension but which isn't standard C++ and is rejected by MSVC and some judges. Use
> `vector<int> arr(n)` — and `arr.data()` if a function signature demands a raw `int*`.

## Where quick sort shows up beyond sorting

The `partition` function is the reusable piece — more so than quick sort itself.

- **Quickselect — find the k-th smallest/largest in O(n) average.** Partition once. If the
  pivot lands at index `k`, you're done. Otherwise recurse into **only the side containing
  `k`** — you never sort the other half. Since you halve the work each time instead of doing
  both halves, `n + n/2 + n/4 + … = 2n` → **O(n) average**.
  This is **LC 215 — Kth Largest Element in an Array**, one of the most-asked interview
  questions. (A heap solves it in O(n log k); quickselect is the O(n) answer.)
- **LC 973 — K Closest Points to Origin.** Quickselect on distance.
- **LC 75 — Sort Colors.** The Dutch National Flag algorithm is a 3-way partition. Do this one
  at Step 2 and you've already met the idea.
- **LC 912 — Sort an Array.** Where you submit your own implementation. Use the randomised
  pivot — the judge's test cases include sorted input specifically to break naive quick sort.
- **`std::nth_element`** — the STL's quickselect. O(n) average, rearranges so the n-th element
  is in its sorted position. Worth knowing it exists.

## Merge sort vs quick sort — the decision

| | Merge Sort | Quick Sort |
|--|--|--|
| Worst case | **O(n log n)** guaranteed | O(n²) (mitigated by random pivot) |
| Average | O(n log n) | O(n log n), **smaller constant** |
| Auxiliary space | O(n) | **O(1)** |
| Stable | **yes** | no |
| Cache behaviour | poorer (copies between arrays) | **better** (in-place, contiguous) |
| Sorted input | O(n log n) | **O(n²)** with naive pivot |
| Linked lists | **ideal** — pointer rewiring, O(1) extra | poor — needs random access |
| External / on-disk data | **works** — streams sequentially | doesn't |

**In practice:** quick sort (as introsort) is the default for arrays — it's what `std::sort`
uses. Merge sort is the choice when you need stability (`std::stable_sort`), when sorting
linked lists, or when the data doesn't fit in memory.

---

# Side-by-side summary — all five

| | Selection | Bubble | Insertion | Merge | Quick |
|--|--|--|--|--|--|
| Sorted region grows from | left | right | left | n/a — bottom-up from sub-ranges | n/a — pivots land scattered |
| Placed elements final? | yes | yes | **no** — they still shift | not until their final merge | **yes** — pivot never moves again |
| How an element moves | one long-distance swap | many adjacent swaps | many adjacent swaps/shifts | copied to a buffer and back | long-distance swaps across the pivot |
| Best case | O(n²) | O(n) *(needs flag)* | **O(n)** | O(n log n) | O(n log n) |
| Average | O(n²) | O(n²) | O(n²) | **O(n log n)** | **O(n log n)** *(fastest constant)* |
| Worst | O(n²) | O(n²) | O(n²) | **O(n log n)** | O(n²) |
| Auxiliary space | O(1) | O(1) | O(1) | **O(n)** | **O(1)** + O(log n) stack |
| Swaps (worst) | **n-1** | n(n-1)/2 | n(n-1)/2 | 0 (copies, ~n log n writes) | O(n²) |
| Stable | no | yes | yes | **yes** | no |
| Adaptive | no | detects "fully sorted" only | **yes** — O(n·k) | no (yes w/ `arr[mid]<=arr[mid+1]` check) | no — sorted input is the **worst** case |
| Divide & conquer | no | no | no | **yes** | **yes** |

## Pick by constraint

- **Writes are expensive** (large structs, flash memory, network) → **Selection Sort**, at most
  `n-1` swaps.
- **Data is nearly sorted, or arrives one element at a time** → **Insertion Sort**. Also the
  fastest of the O(n²) three on small arrays, which is why real library sorts fall back to it
  below ~16–32 elements.
- **Bubble Sort** → mostly a teaching algorithm. Insertion Sort beats it on essentially every
  metric while being just as simple.
- **You need guaranteed O(n log n) with no worst-case blowup, or stability, or the data doesn't
  fit in memory, or you're sorting a linked list** → **Merge Sort**.
- **General-purpose array sorting, memory is tight, you want raw speed** → **Quick Sort** with a
  randomised pivot. This is what `std::sort` uses (as introsort).
- **In real code** → `std::sort` (O(n log n), introsort) or `std::stable_sort` when stability
  matters. Hand-written sorts are for understanding, not for production.

## The one-line summary of each

| | |
|--|--|
| Selection | repeatedly **select** the minimum and swap it to the front |
| Bubble | repeatedly **bubble** the maximum to the back via adjacent swaps |
| Insertion | repeatedly **insert** the next element into the sorted prefix |
| Merge | **split** blindly in half, **merge** the sorted halves cleverly |
| Quick | **partition** cleverly around a pivot, then nothing left to combine |