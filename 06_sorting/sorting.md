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

# Add this to the side-by-side summary table

| | Merge Sort |
|--|--|
| Sorted region grows from | n/a — builds bottom-up from sorted sub-ranges |
| Placed elements final? | not until their final merge |
| How an element moves | copied into a buffer, then copied back |
| Best case | **O(n log n)** |
| Average | **O(n log n)** |
| Worst | **O(n log n)** |
| Space | **O(n)** + O(log n) stack |
| Swaps (worst) | 0 (it copies, ~n log n writes) |
| Stable | yes |
| Adaptive | no (yes, with the `arr[mid] <= arr[mid+1]` check) |

And add to **Pick by constraint:**

- **You need a guaranteed O(n log n) with no worst-case blowup, or you need stability, or the
  data doesn't fit in memory** → Merge Sort. It's the first sort here that's actually usable on
  large inputs.