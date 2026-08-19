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

# Side-by-side summary

| | Selection Sort | Bubble Sort | Insertion Sort |
|--|--|--|--|
| Sorted region grows from | left | right | left |
| Placed elements are final? | yes | yes | **no** — they still shift |
| How an element moves | one long-distance swap | many adjacent swaps | many adjacent swaps/shifts |
| Best case | O(n²) | O(n) *(needs `swapped` flag)* | **O(n)** *(falls out of the `break`)* |
| Average | O(n²) | O(n²) | O(n²) |
| Worst | O(n²) | O(n²) | O(n²) |
| Space | O(1) | O(1) | O(1) |
| Swaps (worst) | **n-1** | n(n-1)/2 | n(n-1)/2 |
| Stable | no (standard version) | yes | yes |
| Adaptive | no | only detects "fully sorted" | **yes** — O(n·k) for k-sorted data |

**Pick by constraint:**

- **Writes are expensive** (large structs, flash memory, network) → Selection Sort, at most
  `n-1` swaps.
- **Data is nearly sorted, or arrives one element at a time** → Insertion Sort. It's also the
  fastest of the three on small arrays in practice, which is why real library sorts fall back
  to it below ~16–32 elements.
- **Bubble Sort** → mostly a teaching algorithm. Insertion Sort beats it on essentially every
  metric while being just as simple.

All three are O(n²) and none should be used on large inputs — reach for `std::sort` (O(n log n))
or `std::stable_sort` when stability is needed.