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