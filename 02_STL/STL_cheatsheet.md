## STL Cheatsheet

## 1. pair
- **Header:** `#include <utility>` (already include via `<bits/stdc++.h>`)
- **What it is:** it holds two values (could be of diff types too) as one unit.

## Declaration & assignment & nested pair
pair<int, int> p = {1, 3};
pair<int, pair<int, int>> l = {4, {5, 1}};

## Access
p.first // 1
p.second // 3
l.first // 4
l.second.first // 5
l.second.second // 1

You can't print `p` directly -- must use `.first`/`.second`.
You can't print `l.second` directly, must drill down

## Pair array
pair <int, int> arr[] = {{1,2}, {4, 6}, {14, 155}};
arr[0].first // 1
arr[0].second // 2
arr[1].second // 6
arr[2].second // 155

You can't print arr[0] directly

## 2. vector
- **Header:** `#include <vector>` (already included via `<bits/stdc++.h>`)
- **What it is:** dynamic array — like an array but size is NOT fixed; grows/shrinks at runtime. Use when size isn't known beforehand.

## Declaration
vector<int> v;              // empty
vector<int> v1(5, 100);     // {100, 100, 100, 100, 100} -- size 5, all = 100
vector<int> v2(5);          // {0, 0, 0, 0, 0} or garbage -- size 5, no value given
vector<int> v4(v3);         // copy of v3 (separate container, same values)
vector<pair<int, int>> vp;  // vector of pairs

## Adding elements
v.push_back(1);             // appends at end
v.emplace_back(2);          // same, slightly faster (constructs in place)

vp.push_back({1, 2});       // pairs need {} with push_back
vp.emplace_back(3, 4);      // emplace_back: no {} needed, auto-pairs

## Access -- by index (same as array)
v1[2]   // third element

## Access -- by iterator
vector<int>::iterator it = v1.begin();   // address of first element
*it           // value at that address (dereference, like pointer)
it++;         // move one step forward
it = it + 2;  // jump 2 positions ahead

You can't print `it` directly -- it gives a memory address, not the value. Use `*it`.

## Endpoint iterators
v1.end()      // points to one PAST the last element -- NOT the last itself
              // to get last via end(): it = v1.end(); it--; *it

v1.rbegin()   // reverse begin → LAST element. *rit gives last value. rit++ moves BACKWARD.
v1.rend()     // reverse end → one BEFORE first element. Sentinel, don't dereference.

Reverse iterator has a different type: `vector<int>::reverse_iterator` (not `iterator`).
Never dereference `end()` or `rend()` -- they're past-the-edge sentinels.

## Direct last element
v1.back()     // returns last element directly (cleanest way)
