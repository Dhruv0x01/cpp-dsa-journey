# STL Cheatsheet

---

## 1. pair

- **Header:** `#include <utility>` (already included via `<bits/stdc++.h>`)
- **What it is:** holds two values (can be different types) as one unit.

### Declaration, assignment & nested pair
```cpp
pair<int, int> p = {1, 3};
pair<int, pair<int, int>> l = {4, {5, 1}};
```

### Access
```cpp
p.first          // 1
p.second         // 3
l.first          // 4
l.second.first   // 5
l.second.second  // 1
```

- You **can't** print `p` directly — must use `.first` / `.second`.
- You **can't** print `l.second` directly — must drill down.

### Pair array
```cpp
pair<int, int> arr[] = {{1,2}, {4,6}, {14,155}};
arr[0].first   // 1
arr[0].second  // 2
arr[1].second  // 6
arr[2].second  // 155
```

- You **can't** print `arr[0]` directly.
- It's a **C-style array**, so no `.begin()`/`.end()` member functions — use `std::begin(arr)` / `std::end(arr)`, or `arr` / `arr + n` with pointer arithmetic, when passing to algorithms like `sort()`.

---

## 2. vector

- **Header:** `#include <vector>` (already included via `<bits/stdc++.h>`)
- **What it is:** a dynamic array — like an array, but the size is **NOT fixed**; it grows/shrinks at runtime. Use it when you don't know the size beforehand.
- **Note:** most of these functions repeat in `list`, `map`, `set`, `queue` too — learn them once here.

### Declaration
```cpp
vector<int> v;              // empty
vector<int> v1(5, 100);     // {100,100,100,100,100} — size 5, all = 100
vector<int> v2(5);          // {0,0,0,0,0} or garbage — size 5, no value given
vector<int> v4(v3);         // copy of v3 (separate container, same values)
vector<pair<int,int>> vp;   // vector of pairs
```

### Adding elements
```cpp
v.push_back(1);        // appends at end
v.emplace_back(2);     // same, slightly faster (constructs in place)

vp.push_back({1, 2});  // pairs need {} with push_back
vp.emplace_back(3, 4); // emplace_back: no {} needed, auto-makes the pair
```

### Access — by index (same as array)
```cpp
v1[2];   // third element
```

### Access — by iterator
```cpp
vector<int>::iterator it = v1.begin();  // address of first element
*it;          // value at that address (dereference, like a pointer)
it++;         // move one step forward
it = it + 2;  // jump 2 positions ahead
```

- You **can't** print `it` directly — it holds a memory **address**, not the value. Use `*it`.
- Rule of thumb: `it` = address, `*it` = value.

### Endpoint iterators
```cpp
v1.end();     // one PAST the last element — NOT the last itself
              // to reach the last via end():  it = v1.end(); it--; *it

v1.rbegin();  // reverse begin → LAST element. *rit gives last value. rit++ moves BACKWARD.
v1.rend();    // reverse end → one BEFORE first element. Sentinel, don't dereference.
```

- Reverse iterators have a **different type**: `vector<int>::reverse_iterator` (not `iterator`).
- **Never** dereference `end()` or `rend()` — they are past-the-edge sentinels.

### Direct last element
```cpp
v1.back();    // returns the last element directly (cleanest way)
```

### Printing a vector
Given `v = {1, 2, 3, 4, 5, 6}` — three ways to loop:

```cpp
// 1. Full iterator form
for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    cout << *it << " ";        // needs *it (it is an address)

// 2. auto — compiler figures out the iterator type for you
for (auto it = v.begin(); it != v.end(); it++)
    cout << *it << " ";        // still an iterator → still needs *it

// 3. Range-based for — here `it` IS the value, not an iterator
for (auto it : v)
    cout << it << " ";         // no * needed — it holds the actual value
```

- **Key difference:** in forms 1 & 2, `it` is an iterator (address) → use `*it`.
  In form 3 (range-based), `it` is a **copy of the value** each pass → use `it` directly.

### Deletion — `.erase()`
Given `v = {1, 2, 3, 4, 5, 6}`

```cpp
// Single element — pass one address
v.erase(v.begin() + 1);      // deletes element at index 1 (the value 2)
// v = {1, 3, 4, 5, 6}

// Range — [first, last)  → first INCLUSIVE, last EXCLUSIVE
v.erase(v.begin(), v.begin() + 3);   // deletes indices 0,1,2
// v = {5, 6}
```

- Range erase: the **last** iterator is NOT deleted (exclusive).

### Insert — `.insert()`
Starting from `v = {5, 6}`

```cpp
// insert(address, value) — one value at a position
v.insert(v.begin(), 10);
// v = {10, 5, 6}

// insert(address, count, value) — 'count' copies of a value
v.insert(v.begin() + 1, 4, 72);       // four 72s starting at index 1
// v = {10, 72, 72, 72, 72, 5, 6}

// insert relative to end()  (end() is just past the last element)
v.insert(v.end() - 2, 53);            // pushes 5, 6 further right
// v = {10, 72, 72, 72, 72, 53, 5, 6}
```

**Inserting one vector into another** (less common):
```cpp
// insert(destination address, source begin, source end)
vector<int> copy(3, 67);              // {67, 67, 67}
v.insert(v.begin() + 3, copy.begin(), copy.end());
// copy's range gets spliced into v at index 3
```

### Size — `.size()`
```cpp
v.size();     // number of elements currently in the vector
```

### Remove last element — `.pop_back()`
```cpp
v.pop_back();   // removes the last element (no argument needed)
// {..., x, y}  →  {..., x}
```

### Swap two vectors — `.swap()`
```cpp
// v1 = {100,100,100,100,100}
// v3 = {20,20,20,20}
v1.swap(v3);
// v1 = {20,20,20,20}
// v3 = {100,100,100,100,100}
```

- Swaps the entire contents of the two vectors (they exchange values).

### Empty a vector — `.clear()` and check with `.empty()`
```cpp
v.clear();     // erases ALL elements → vector becomes {}

v.empty();     // returns true (1) if empty, false (0) if it has elements
```

```cpp
// after v.clear():
v.empty();     // 1  (true)
v3.empty();    // 0  (false, still has elements)
```

---

## Quick Reference — vector functions

| Function | What it does |
|---|---|
| `push_back(x)` / `emplace_back(x)` | add `x` at the end (`emplace_back` slightly faster) |
| `v[i]` | access by index |
| `begin()` / `end()` | iterator to first / one-past-last |
| `rbegin()` / `rend()` | reverse: last / one-before-first |
| `back()` | last element directly |
| `erase(pos)` | delete one element |
| `erase(first, last)` | delete range `[first, last)` (last exclusive) |
| `insert(pos, val)` | insert one value |
| `insert(pos, n, val)` | insert `n` copies of `val` |
| `insert(pos, b, e)` | insert another range `[b, e)` |
| `size()` | number of elements |
| `pop_back()` | remove last element |
| `swap(other)` | exchange contents with `other` |
| `clear()` | remove all elements |
| `empty()` | `true` if empty, else `false` |

---

## 3. list

- **Header:** `#include <list>` (already included via `<bits/stdc++.h>`)
- **What it is:** another dynamic container like `vector`, but it **also gives you cheap front operations**.
- **Why use it over vector:** in a vector, inserting/adding at the **front** is costly (everything has to shift over). In a list, `push_front()` / `emplace_front()` are **cheap** — that's the main reason to reach for `list`.
- Internally it's a doubly-linked list, which is why front insertion is cheap but **there is no `[]` index access** (you must walk with iterators).

### Adding at the back (same as vector)
```cpp
list<int> ls;
ls.push_back(2);       // {2}
ls.emplace_back(4);    // {2, 4}
```

### Adding at the front (the extra power over vector)
```cpp
ls.push_front(1);      // {1, 2, 4}
ls.emplace_front(10);  // {10, 1, 2, 4}
```

- `push_front` / `emplace_front` add at the **start**. Vector does **not** have these.
- As with vector, the `emplace_` versions construct in place (slightly faster; no `{}` needed for pairs).

### Printing a list
```cpp
for (auto it : ls)
    cout << it << " ";     // {10, 1, 2, 4}
```

- Same range-based loop as vector — `it` holds the value directly.
- Iterator loops (`begin()`/`end()` with `*it`) work too.
- **Cannot** use `ls[i]` — no index access on a list. Use iterators.

### Same functions as vector
These behave exactly like the vector versions:

```cpp
ls.begin()  ls.end()  ls.rbegin()  ls.rend()   // iterators
ls.insert(pos, val)                             // insert
ls.size()                                       // element count
ls.swap(other)                                  // exchange contents
ls.clear()   ls.empty()                         // empty out / check
ls.front()   ls.back()                          // first / last element
ls.pop_back()                                   // remove last
ls.pop_front()                                  // remove first  (vector has no pop_front)
```

---

## Quick Reference — list functions

| Function | What it does |
|---|---|
| `push_back(x)` / `emplace_back(x)` | add `x` at the **end** |
| `push_front(x)` / `emplace_front(x)` | add `x` at the **front** (cheap — list's advantage) |
| `front()` / `back()` | first / last element directly |
| `pop_back()` | remove last element |
| `pop_front()` | remove first element (**vector has no pop_front**) |
| `begin()` / `end()` | iterator to first / one-past-last |
| `rbegin()` / `rend()` | reverse: last / one-before-first |
| `insert(pos, val)` | insert at a position |
| `size()` | number of elements |
| `swap(other)` | exchange contents with `other` |
| `clear()` | remove all elements |
| `empty()` | `true` if empty, else `false` |

> **No `ls[i]`** — list has no index access. Walk it with iterators or a range-based loop.

---

## 4. deque

- **Header:** `#include <deque>` (already included via `<bits/stdc++.h>`)
- **What it is:** "double-ended queue" — dynamic like `vector`, but cheap push/pop at **both** ends.
- Unlike `list`, a deque **does** support `dq[i]` index access and random-access iterators — it's stored as blocks of contiguous memory internally, not linked nodes.

### Adding/removing at both ends
```cpp
deque<int> dq;
dq.push_back(1);     // {1}
dq.emplace_back(2);  // {1, 2}
dq.push_front(3);    // {3, 1, 2}
dq.emplace_front(4); // {4, 3, 1, 2}

dq.pop_back();        // {4, 3, 1}
dq.pop_front();       // {3, 1}
```

### Direct access
```cpp
dq.front();   // 3
dq.back();    // 1
dq[0];        // index access works, unlike list
```

### Same functions as vector
```cpp
dq.begin()  dq.end()  dq.rbegin()  dq.rend()
dq.insert(pos, val)   dq.size()   dq.swap(other)
dq.clear()   dq.empty()
```

---

## Quick Reference — deque functions

| Function | What it does |
|---|---|
| `push_back(x)` / `emplace_back(x)` | add at the end |
| `push_front(x)` / `emplace_front(x)` | add at the front (cheap, like list) |
| `pop_back()` / `pop_front()` | remove from end / front |
| `front()` / `back()` | first / last element directly |
| `dq[i]` | index access (deque supports this; list doesn't) |
| `begin()` / `end()` / `rbegin()` / `rend()` | iterators |
| `insert(pos, val)` / `size()` / `swap()` / `clear()` / `empty()` | same as vector |

---

## 5. stack

- **Header:** `#include <stack>` (already included via `<bits/stdc++.h>`)
- **What it is:** a **container adaptor** — a restricted wrapper (built on `deque` by default) exposing only LIFO (Last In, First Out) access. Like a pile of books: last one placed is the first one removed.
- **No iterators, no `[]` indexing** — you can only touch the top.

### Core operations — all O(1)
```cpp
stack<int> st;
st.push(1);      // {1}
st.push(2);      // {2, 1}
st.emplace(21);  // {21, 2, 1}   -- emplace, no back/front variants exist

st.top();        // 21  -- peek top element
st.pop();        // removes the top element (returns nothing)
st.size();       // number of elements
st.empty();      // 1 if empty, 0 if not
```

- Note the naming difference from vector/list/deque: it's `push` / `emplace` / `pop` — **no** `_back` or `_front` suffix.
- `pop()` removes the top but doesn't return it — call `.top()` first if you need the value.

### Swap
```cpp
st1.swap(st2);   // exchanges contents of two stacks
```

---

## Quick Reference — stack functions

| Function | What it does |
|---|---|
| `push(x)` / `emplace(x)` | add to top |
| `pop()` | remove top element (no return value) |
| `top()` | peek at top element |
| `size()` / `empty()` / `swap(other)` | same idea as vector |

> **No iterators, no `st[i]`** — can't loop over a stack directly.

---

## 6. queue

- **Header:** `#include <queue>` (already included via `<bits/stdc++.h>`)
- **What it is:** a container adaptor (built on `deque` by default) exposing FIFO (First In, First Out) access. Like a line of people — first to join is first to leave.
- **No iterators, no `[]` indexing.**

### Core operations
```cpp
queue<int> q;
q.push(1);       // {1}
q.push(2);       // {1, 2}
q.emplace(10);   // {1, 2, 10}

q.front();       // 1  -- first element
q.back();        // 10 -- last element
q.pop();         // removes the FIRST element (front)
```

- Same `push`/`emplace`/`pop` naming pattern as stack — no `_back`/`_front` suffix on push/emplace, but you get **both** `front()` and `back()` for peeking.
- `size()`, `swap()`, `empty()` — same as stack.

---

## Quick Reference — queue functions

| Function | What it does |
|---|---|
| `push(x)` / `emplace(x)` | add to the back |
| `pop()` | remove from the front |
| `front()` / `back()` | peek first / last element |
| `size()` / `empty()` / `swap(other)` | same idea as vector |

> **No iterators, no `q[i]`.**

---

## 7. priority_queue

- **Header:** `#include <queue>` (already included via `<bits/stdc++.h>`)
- **What it is:** similar interface to `queue`, but internally maintains a **heap** (tree structure, not linear storage). Default is a **max-heap** — the largest element always sits at the top.

### Max-heap (default)
```cpp
priority_queue<int> pq;
pq.push(5);   // {5}
pq.push(2);   // {5, 2}
pq.push(13);  // {13, 5, 2}

pq.top();     // 13 -- largest element
pq.pop();     // removes the top (largest) element
```

### Min-heap
```cpp
// syntax: priority_queue<Type, vector<Type>, greater<Type>>
priority_queue<int, vector<int>, greater<int>> pq1;
pq1.push(5);
pq1.push(3);
pq1.push(10);

pq1.top();    // 3 -- smallest element stays on top
```

### Time complexities
| Operation | Complexity |
|---|---|
| `push()` | O(log n) |
| `top()` | O(1) |
| `pop()` | O(log n) |

- `size()`, `empty()`, `swap()` — same as before.
- **No iterators, no `[]` indexing.**

---

## 8. set

- **Header:** `#include <set>` (already included via `<bits/stdc++.h>`)
- **What it is:** stores elements in **sorted order**, and enforces **uniqueness** (no duplicates). Internally a tree, not a linear array.

### Insert
```cpp
set<int> st;
st.insert(1);   // {1}
st.insert(2);   // {1, 2}
st.insert(2);   // {1, 2}  -- duplicate ignored
st.emplace(4);  // {1, 2, 4}
```

### Find — returns an iterator
```cpp
auto it = st.find(3);   // iterator pointing AT 3, if it exists
auto it1 = st.find(6);  // if not found, returns an iterator == st.end()
```

### Count — existence check
```cpp
int cnt = st.count(1);  // 1 if present, 0 if not (set has no duplicates, so max is 1)
```

### Erase — by value or by iterator
```cpp
st.erase(2);          // erase by value — O(log n)
st.erase(it);          // erase by iterator (once you have it) — O(1)
st.erase(it_a, it_b);  // erase a range [it_a, it_b) — first inclusive, last exclusive
```

### lower_bound / upper_bound
```cpp
auto it_c = st.lower_bound(1);   // iterator to first element >= 1
auto it_d = st.upper_bound(21);  // iterator to first element > 21
```

- `begin()`, `end()`, `rbegin()`, `rend()`, `size()`, `empty()`, `swap()` — same as before.
- **All operations are O(log n).**

---

## Quick Reference — set functions

| Function | What it does |
|---|---|
| `insert(x)` / `emplace(x)` | add element (ignored if duplicate) |
| `find(x)` | iterator to `x`, or `end()` if not found |
| `count(x)` | 1 if present, 0 if not |
| `erase(x)` | erase by value |
| `erase(it)` | erase by iterator |
| `erase(it_a, it_b)` | erase range `[it_a, it_b)` |
| `lower_bound(x)` / `upper_bound(x)` | first element `>= x` / `> x` |
| `begin()`/`end()`/`size()`/`empty()`/`swap()` | same as vector |

---

## 9. multiset

- **Header:** `#include <set>`
- **What it is:** exactly like `set`, except **duplicates are allowed**. Still kept in sorted order.

```cpp
multiset<int> ms;
ms.insert(1); ms.insert(1); ms.insert(1); ms.insert(2);
// {1, 1, 1, 2}

ms.count(1);        // 3

ms.erase(2);         // erases ALL instances of 2
ms.erase(ms.find(1)); // erases only ONE instance of 1 (the one the iterator points to)

// Erasing a specific number of instances:
auto it = ms.find(1);
auto stop = next(it, 4);   // iterator 4 positions ahead of it
ms.erase(it, stop);        // erases [it, stop) — removes 4 instances
```

- **Key gotcha:** `erase(value)` wipes out *every* copy; `erase(iterator)` removes just *one*. Use `next(it, n)` to build a range when you want to erase a specific count.
- All other functions same as `set`.

---

## 10. unordered_set

- **Header:** `#include <unordered_set>`
- **What it is:** like `set` (unique elements), but stored in **no particular order** — implemented via hashing, not a tree.
- Time complexity is O(1) on average for insert/find/erase; O(n) worst case (rare, happens on hash collisions).
- **`lower_bound()` / `upper_bound()` do NOT work** here — there's no ordering to exploit.
- Use `set` when you need sorted order or bound queries; use `unordered_set` when you just need fast membership checks and don't care about order.

---

## 11. map

- **Header:** `#include <map>` (already included via `<bits/stdc++.h>`)
- **What it is:** stores `{key, value}` pairs. Keys are **unique** and kept in **sorted order**. Value can repeat freely.

### Declaring & storing
```cpp
map<int, int> mpp;             // int key, int value
map<int, pair<int,int>> mpp2;  // int key, pair value
map<pair<int,int>, int> mpp1;  // pair key, int value

mpp[1] = 2;                 // store 2 at key 1
mpp.emplace(3, 10);         // no {} needed
mpp.insert({4, 13});        // needs {}

mpp1[{1, 2}] = 10;                    // pair key via []
mpp1.emplace(make_pair(1, 3), 15);    // emplace avoids outer {}
mpp1.insert({{2, 1}, 17});            // insert needs both inner & outer {}
```

### Printing
```cpp
for (auto it : mpp)
    cout << it.first << ":" << it.second << endl;   // it.first = key, it.second = value

// with a pair key:
for (auto it : mpp1)
    cout << "(" << it.first.first << "," << it.first.second << "):" << it.second;
```

### Access by key
```cpp
mpp[3];         // value at key 3
mpp1[{1, 4}];   // value at key (1,4)
mpp[100];       // key doesn't exist → returns 0/null AND silently inserts key 100 with default value
```

- **Gotcha:** using `mpp[key]` on a non-existent key **creates** that key with a default value as a side effect. Use `find()` if you just want to check existence without inserting.

### Find — returns iterator to the {key, value} pair
```cpp
auto it = mpp.find(4);
it->first;     // key   → 4
it->second;    // value → 13
(*it).second;  // same as it->second

// if not found, iterator == mpp.end()
```

- Since an iterator here points to a whole pair, you dereference with `->` (or `(*it).`) rather than printing `*it` directly.

### lower_bound / upper_bound
```cpp
auto it_4 = mpp.lower_bound(1);
auto it_5 = mpp.upper_bound(2);
```

- `erase()`, `swap()`, `size()`, `empty()` — same idea as `set`.
- **Most important functions:** `find`, `count`, `erase`, `insert`, `[]`.
- All operations O(log n).

---

## Quick Reference — map functions

| Function | What it does |
|---|---|
| `mpp[key] = val` | insert/update — **creates key if missing** |
| `insert({key, val})` | add pair (needs `{}`) |
| `emplace(key, val)` | add pair (no `{}` needed) |
| `find(key)` | iterator to `{key,val}`, or `end()` if not found |
| `it->first` / `it->second` | key / value from an iterator |
| `count(key)` | 1 if present, 0 if not |
| `erase(key)` / `erase(it)` | remove by key or iterator |
| `lower_bound(key)` / `upper_bound(key)` | same idea as set |
| `begin()`/`end()`/`size()`/`empty()`/`swap()` | same as vector |

---

## 12. multimap

- **Header:** `#include <map>`
- **What it is:** like `map`, but **duplicate keys are allowed**. Still stored in sorted-by-key order.
- **Key restriction:** `mpp[key]` does **NOT** work on multimap (ambiguous — which duplicate would it return?). Use `insert()`/`emplace()` and iterate or use `equal_range()`/`find()` instead.
- Everything else (erase, size, swap, iterators) behaves like `map`.

---

## 13. unordered_map

- **Header:** `#include <unordered_map>`
- **What it is:** like `map` (unique keys) but with **no ordering guarantee** — hash-based storage.
- Average O(1) for insert/find/erase; worst case O(n) (rare).
- Compare to `map`'s guaranteed O(log n) — trade sorted order for average speed.
- `lower_bound()`/`upper_bound()` don't apply here either.

---

## 14. Sorting, Comparators & Useful Algorithms

- **Header:** `#include <algorithm>` (already included via `<bits/stdc++.h>`)

### Basic sort
```cpp
vector<int> v = {5, 10, 3, 2};
sort(v.begin(), v.end());
// v = {2, 3, 5, 10}
```

- `sort(start, end)` — range is `[start, end)`, `end()` is one-past-the-last so it's naturally excluded.

### Sorting only a portion
```cpp
vector<int> v1 = {10, 5, 19, 1, 3, -10};
sort(v1.begin() + 1, v1.begin() + 5);   // sorts indices 1..4 only
// v1 = {10, 1, 3, 5, 19, -10}
```

### Descending order
```cpp
sort(v.begin(), v.end(), greater<int>());
// v = {10, 5, 3, 2}
```

### C-style arrays
Arrays aren't classes, so no `.begin()`/`.end()` member functions — use free functions instead:
```cpp
int arr[4] = {10, 20, 420, 100};
sort(begin(arr), end(arr));     // or: sort(arr, arr + 4);
```

### Custom comparator
Write your own **comparator** — a function that takes two elements and returns `bool`: `true` means "first argument comes before the second."

```cpp
bool comp(const pair<int,int>& p1, const pair<int,int>& p2) {
    if (p1.second != p2.second) return p1.second < p2.second;  // ascending by second
    return p1.first > p2.first;                                 // descending by first, on tie
}

pair<int,int> a[] = {{1,2},{2,1},{4,1},{5,6},{7,9},{10,9},{9,6},{11,2}};
sort(begin(a), end(a), comp);
// sorted by .second ascending; ties broken by .first descending
```

- Pass by `const&` for objects/pairs — avoids copying on every comparison.
- **Must satisfy strict weak ordering:** for genuinely equal elements, `comp` must return `false` both ways — otherwise `sort()` has undefined behavior.

### __builtin_popcount
Counts the number of `1` bits in a number's binary representation.
```cpp
__builtin_popcount(7);      // 3   (7 = 0111)
__builtin_popcountll(x);    // same, but for long long
```

### next_permutation
Generates the next lexicographically greater permutation of a sequence; returns `false` once there's no next one (i.e. the sequence is fully descending).
```cpp
string s = "123";
do {
    cout << s << endl;
} while (next_permutation(s.begin(), s.end()));
// 123, 132, 213, 231, 312, 321
```

- **Important:** to get *all* permutations, the sequence must start in **sorted order**. Starting from an unsorted string (e.g. `"231"`) only gives the permutations from that point onward, not all of them.
```cpp
string s = "321";
sort(s.begin(), s.end());   // sort first → "123"
// now the do-while above gives every permutation
```

### max_element / min_element
Returns an **iterator** (not the value) to the largest/smallest element in a range — dereference with `*` to get the value.
```cpp
int arr[4] = {10, 20, 420, 100};

max_element(begin(arr), end(arr));    // iterator pointing at 420
*max_element(begin(arr), end(arr));   // 420 — the actual value

*min_element(begin(arr), end(arr));   // 10
```

- Both accept an optional comparator too, same as `sort`.
- Watch variable naming: don't name a variable `max` or `min` — it shadows `std::max`/`std::min` and will break later calls to those functions in the same scope.

---

## Quick Reference — container adaptors & associative containers at a glance

| Container | Order | Duplicates | Index `[]` | Iterators |
|---|---|---|---|---|
| `stack` | LIFO | n/a | ❌ | ❌ |
| `queue` | FIFO | n/a | ❌ | ❌ |
| `priority_queue` | heap (max by default) | n/a | ❌ | ❌ |
| `set` | sorted | ❌ unique | ❌ | ✅ |
| `multiset` | sorted | ✅ allowed | ❌ | ✅ |
| `unordered_set` | none | ❌ unique | ❌ | ✅ |
| `map` | sorted by key | ❌ unique keys | ✅ (`mpp[key]`) | ✅ |
| `multimap` | sorted by key | ✅ duplicate keys | ❌ | ✅ |
| `unordered_map` | none | ❌ unique keys | ✅ (`mpp[key]`) | ✅ |
| `deque` | insertion order | ✅ allowed | ✅ | ✅ |