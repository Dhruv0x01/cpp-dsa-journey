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