# Hashing — Cheatsheet

Core idea across everything: **pre-store answers once, then fetch instantly.**
Two phases every time → **Pre-compute** (count upfront) + **Fetch** (answer in O(1)).

---

# Part 1 — Number Hashing

**Problem:** how many times does a number appear in an array? (asked multiple times)

**Idea:** build a frequency array where **index = the number**, **value = its count**.

- Array size = `max possible value + 1`.
- Build it: `hash[arr[i]]++` for every element.
- Answer a query: read `hash[number]` → O(1).

### Dry run — `arr = [2, 5, 2, 2, 5]`, max value 5 → hash size 6

| See | Action | hash → `[0,1,2,3,4,5]` |
|-----|--------|------------------------|
| start | zeros | `[0,0,0,0,0,0]` |
| 2 | `hash[2]++` | `[0,0,1,0,0,0]` |
| 5 | `hash[5]++` | `[0,0,1,0,0,1]` |
| 2 | `hash[2]++` | `[0,0,2,0,0,1]` |
| 2 | `hash[2]++` | `[0,0,3,0,0,1]` |
| 5 | `hash[5]++` | `[0,0,3,0,0,2]` |

Query "how many `2`?" → `hash[2]` = **3**. Query "how many `5`?" → `hash[5]` = **2**.

### Complexity

| | Pre-compute | Per query | Total (q queries) |
|--|--|--|--|
| Brute force | — | O(n) | O(q × n) |
| Hashing | O(n) | O(1) | O(n + q) |

### Size limits (gotcha)

| Declared | `int` array | `bool` array |
|--|--|--|
| Inside `main()` (stack) | ~10⁶ | ~10⁷ |
| Global (outside `main`) | ~10⁷ | ~10⁸ |

- Bigger array needed → **declare it globally** (auto-initialized to 0, no `= {0}` needed).
- Exceed limit → **segmentation fault**.
- Value range up to **10⁹** → array won't fit → use **map / unordered_map** (Part 3).
- **Never size a stack array by a runtime variable** (e.g. `int arr[nums.size()+1]`) — that's a variable-length array (VLA), and standard C++ doesn't allow it (some compilers accept it as a non-portable extension, but judges like LeetCode reject it with a compile error). Array size must be a compile-time constant, or you need a `vector`/dynamic allocation sized at runtime instead.

---

# Part 2 — Character Hashing

**Problem:** how many times does a character appear in a string? (e.g. `s = "banana"`, count of `a` → 3)

**Idea:** same frequency array, but characters aren't numbers — so map each letter to an index.

- Only lowercase `a`–`z` → **26 possible characters** → hash array of size **26**.
- We want `a → 0`, `b → 1`, …, `z → 25`.

### The ASCII trick (the key part)

Every character has an ASCII value. In C++, a `char` in an int context *becomes* its ASCII number:

- `'a'` → 97, `'b'` → 98, … , `'z'` → 122
- `int x = 'a';` stores **97**.

To turn a letter into an index `0–25`, subtract `'a'` (which is 97):

```
s[i] - 'a'
```

- `'a' - 'a'` = 97 − 97 = **0**
- `'b' - 'a'` = 98 − 97 = **1**
- `'z' - 'a'` = 122 − 97 = **25**

So `hash[s[i] - 'a']++` drops each letter into the right slot. Using `'a'` instead of `97` is cleaner and means the same thing.

To **query** a character, do the same conversion: asking for `'a'` means reading `hash['a' - 'a']` = `hash[0]`.

### Dry run — `s = "banana"`, hash size 26 (showing only slots that change)

| See | `s[i]-'a'` | Action | changed slot |
|-----|-----------|--------|--------------|
| start | — | zeros | all 0 |
| b | 1 | `hash[1]++` | b = **1** |
| a | 0 | `hash[0]++` | a = **1** |
| n | 13 | `hash[13]++` | n = **1** |
| a | 0 | `hash[0]++` | a = **2** |
| n | 13 | `hash[13]++` | n = **2** |
| a | 0 | `hash[0]++` | a = **3** |

Final counts: a = 3, b = 1, n = 2. Query "how many `a`?" → `hash['a'-'a']` = `hash[0]` = **3**.

### Ranges for other character sets

| Character set | Hash size | Index formula |
|--|--|--|
| lowercase `a–z` | 26 | `c - 'a'` |
| uppercase `A–Z` | 26 | `c - 'A'` |
| letters + digits + symbols (all ASCII) | 256 | `c` directly (cast to `unsigned char`) |

If you need both upper and lower, either use size 256 or map them separately.

**Practical shortcut:** you don't have to normalize with `-'a'` at all if you just make the array wide enough to cover raw ASCII values directly — e.g. `vector<int> v(255, 0)` and index with `v[ch]` as-is. Costs a bit of unused space (most slots go untouched for a lowercase-only string) but saves the subtraction, and it's still O(1) contiguous-memory access. See the Practice Log below (LeetCode 387) for why this can end up faster in practice than even a size-26 array combined with a map-based approach.

---

# Part 3 — Number Hashing using `map` / `unordered_map`

**Why this exists:** array hashing dies when the numbers get big. Part 1's array needs
size = `max value + 1`, so a value of `10⁹` would need a billion-slot array — impossible to
allocate. The fix is an STL container that only stores the elements you actually see.

### The core difference (array vs map)

The array wastes space because it reserves a slot for **every** index up to the max,
even ones that never appear. The map stores **only the keys you insert**.

`arr = {12}` — one element, value 12:

| Approach | What gets allocated |
|--|--|
| Array hashing | slots `0,1,2,…,12` → size 13, twelve of them empty |
| Map hashing | just `{12: 1}` → one entry |

So with a map, **a big key costs the same as a small key.** Storing key `12` does *not*
mean storing `0` through `12` — only `12` itself lives in the map.

### How `mpp[arr[i]]++` works

`map<int,int> mpp;` → **key = the element**, **value = its frequency**.

The magic is that indexing a missing key **auto-creates it with value 0**, then `++` bumps it:

- Key not present → map inserts it with value `0`, then `++` makes it `1` (first sighting).
- Key already present → `++` just increases the stored frequency.

So one line, `mpp[arr[i]]++`, handles both "seen for the first time" and "seen again."

### Dry run — `arr = [1, 2, 3, 1, 3, 2]`

| See | `mpp[x]++` | map state (sorted keys) |
|-----|-----------|--------------------------|
| start | — | `{}` |
| 1 | `mpp[1]++` | `{1:1}` |
| 2 | `mpp[2]++` | `{1:1, 2:1}` |
| 3 | `mpp[3]++` | `{1:1, 2:1, 3:1}` |
| 1 | `mpp[1]++` | `{1:2, 2:1, 3:1}` |
| 3 | `mpp[3]++` | `{1:2, 2:1, 3:2}` |
| 2 | `mpp[2]++` | `{1:2, 2:2, 3:2}` |

Query "how many `1`?" → `mpp[1]` = **2**. Query "how many `2`?" → `mpp[2]` = **2**.

### `map` vs `unordered_map` (which to pick)

| | `map` | `unordered_map` |
|--|--|--|
| Ordering | keys sorted (ascending) | no order |
| Backed by | balanced BST (red-black tree) | hash table |
| Per operation | **O(log n)** | **O(1) average**, O(n) worst |
| Use when | you need sorted keys / ordered traversal | you just need fast lookups |

Rule of thumb: reach for `unordered_map` by default for pure frequency counting (faster).
Use `map` when you also want to walk the keys in sorted order.

### Time complexity, spelled out — and which to reach for first

**`map`:** storing or fetching is **O(log n)** in *every* case — best, average, and worst are
all the same, because it's a balanced tree and stays balanced no matter what you insert.

**`unordered_map`:** storing or fetching is **O(1)** on average and in the best case, but
**O(n)** in the worst case. That worst case comes from internal hash collisions — when many
different keys hash into the same bucket, lookups inside that bucket degrade toward a linear
scan through everything in it.

**Rule of thumb:** default to `unordered_map` first — its average case beats `map` in
practice for plain frequency counting, and true worst-case collision behavior is rare in
typical DSA inputs. Only fall back to `map` if `unordered_map` is somehow hitting time limits
(rare — usually only with adversarial/crafted inputs targeting a weak hash) or if you
specifically need sorted key order, which `unordered_map` can't give you.

### Gotcha — the "phantom key" side effect

`mpp[target]` **creates** `target` with value 0 if it doesn't exist — even when you're just
*reading*. So querying a missing element silently inserts it. Usually harmless for counting
(you get `0`, which is the right answer), but if map size matters, query with `.find()` or
`.count()` instead — neither one inserts.

### Querying safely — `[]` vs `.find()` vs `.count()`

| Way | Returns | Inserts missing key? | How to read the value |
|--|--|--|--|
| `mpp[target]` | the value | **yes** (as 0) | use directly |
| `mpp.find(target)` | an **iterator** | no | dereference → `it->second` |
| `mpp.count(target)` | `1` if present, `0` if not | no | still need `mpp[target]` after |

**`.find()` returns an iterator, not the value.** An iterator is a pointer-like handle to the
key–value pair. You can't print it directly — you check it against `mpp.end()` (the
"not found" marker), then reach into it:

- `it->first` → the **key**
- `it->second` → the **value** (the frequency)

```cpp
auto it = mpp.find(target);
if (it != mpp.end())            // found
    cout << it->second << endl; // frequency
else
    cout << 0 << endl;          // not present
```

**`.count()`** is simpler to read (returns 0 or 1, no iterator), but for `map` you'd then do
`mpp[target]` to get the value — two lookups instead of one. Fine at DSA scale, but `.find()`
does it in a single lookup:

```cpp
if (mpp.count(target))          // present?
    cout << mpp[target] << endl;
else
    cout << 0 << endl;
```

**Which to use:** for a plain "print the count" loop, `mpp[target]` alone is fine — a missing
key returns 0, which is the correct answer anyway. Switch to `.find()` / `.count()` only when
insertion-on-read would actually cause a problem (you care about map size later, or you must
tell "present with count 0" apart from "absent" — the latter never happens in pure frequency
counting, since stored counts are always ≥ 1).

### When to use what — full picture

| Situation | Best tool |
|--|--|
| Small value range (≤ ~10⁷) | array hashing (fastest, Part 1) |
| Only lowercase letters | size-26 array (Part 2) |
| Huge values (up to 10⁹) or unknown range | `unordered_map` |
| Need frequencies **and** sorted keys | `map` |

---

# Part 4 — Practice Log

Notes on problems solved so far, including the wrong turns taken on the way to the best
approach — the point isn't just "here's a solution," it's "here's why each successive version
was better than the last."

## LeetCode 217 — Contains Duplicate

**Problem:** does any value appear more than once in the array?

**Approaches tried, worst → best:**

1. **VLA (doesn't compile):** `int arr[nums.size()+1] = {0};` fails because array size must be
   a compile-time constant in standard C++ — you can't size a stack array with a runtime
   variable. Also conceptually off even ignoring the compile error: per Part 1, array size
   should be based on the **max value**, not the **element count** — and `nums[i]` can be
   negative on this problem, which array-indexing can't handle at all (no negative indices).
2. **`map<int,int>`, two passes:** fill frequencies in one loop, then loop again checking for
   any count > 1. Correct, but does unnecessary work — builds the *entire* map before checking
   anything, and uses `map` (O(log n) per op) when sorted order is never needed here.
3. **Best — `unordered_map<int,int>`, single pass, early exit:**
   `mpp[it]++;` then immediately check `if (mpp[it] > 1) return true;` in the same loop.
   No second pass needed — the duplicate check happens the instant it becomes true. Also
   swaps to `unordered_map` since order was never used, giving O(1) average per operation.

**Why the best approach wins:** one pass instead of two, early exit instead of always
finishing the fill, and `unordered_map` over `map` since sorted order was never needed.

## LeetCode 242 — Valid Anagram

**Problem:** do two strings use exactly the same letters, same frequency each?

**Approaches tried, worst → best:**

1. **Two `map<char,int>`, compared with `==`:** correct, but overkill — fixed 26-letter
   alphabet doesn't need a tree-based structure at all (Part 2's rule: small fixed alphabet →
   array, not map).
2. **Two `int[26]` arrays, compared with `==`:** introduces a bug — raw C arrays decay to
   pointers, so `hash1 == hash2` compares *memory addresses*, not contents, and will
   essentially always evaluate false. Needs a manual element-by-element loop or `std::equal`
   to actually compare correctly.
3. **Two `std::array<int,26>`, compared with `==`:** fixes the comparison bug, since
   `std::array` overloads `==` for genuine element-wise comparison. Still builds two separate
   structures just to compare them, though.
4. **Best — one `int[26]` (or `array<int,26>`), increment for `s`, decrement for `t`, check
   all-zero:** every letter from `s` cancels its matching letter from `t`; if any slot is
   left nonzero at the end, the strings aren't anagrams. Only one structure, one pass over
   each string, no second array needed just for comparison. Add an early
   `if (s.size() != t.size()) return false;` up front too — mismatched lengths can never be
   anagrams, so this skips the whole pass entirely in that case.

**Why the best approach wins:** array over map (fixed small alphabet beats tree overhead),
one structure instead of two (increment/decrement cancels out instead of building-then-
comparing), and an early length check to skip unnecessary work when the answer's already
known.

## LeetCode 387 — First Unique Character in a String

**Problem:** return the index of the first character that appears exactly once (or -1 if none).

**Approaches tried, worst → best:**

1. **`map<char, pair<int,int>>` storing frequency + last-seen index:** correct, but the
   stored index is redundant — the second loop already walks `s` with index `i`, so the
   moment you find a character with frequency 1, `i` itself *is* the answer. No need to have
   stored an index in the first loop at all.
2. **`map<char,int>` (frequency only), return `i` directly in the second loop:** drops the
   unnecessary pair/index tracking. Same two-pass O(n) structure, but less state to manage.
3. **`int[26]` (or `array<int,26>`) instead of map:** same two loops, but O(1) direct array
   access instead of O(log 26) tree traversal — textbook Part 2 use case (fixed small
   alphabet).
4. **Fastest in practice — `vector<int> v(255, 0)`, indexed directly by `ch` (no `-'a'`
   needed):** covers the full ASCII range so no normalization step is required. Ran at 0ms
   because array/vector access is direct pointer arithmetic on one contiguous memory block
   (cache-friendly), while `map` access means walking a red-black tree and chasing pointers
   to scattered heap-allocated nodes — same O(n) time complexity on paper, but a much smaller
   constant factor in practice.

**Why the best approach wins:** first remove unused state (the redundant stored index), then
swap map for array (fixed alphabet → array beats tree), then widen the array to the full
ASCII range to skip the `-'a'` normalization step entirely — each step trims either
unnecessary work or unnecessary structure without changing the underlying O(n) time
complexity, but shrinking the real-world constant factor each time.