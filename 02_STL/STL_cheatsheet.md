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

