#include <bits/stdc++.h>
using namespace std;

/*
================================================================
  STL — VECTOR  (dynamic array: grows/shrinks at runtime)
  Use when you don't know the size beforehand.
  These functions repeat in list, map, set, queue too.
----------------------------------------------------------------
  DECLARE:
    vector<int> v;            // empty
    vector<int> v(5);         // size 5, filled 0 (or garbage)
    vector<int> v(5, 100);    // size 5, filled 100
    vector<int> v4(v3);       // copy of v3 (separate container)
    vector<pair<int,int>> vp; // vector of pairs

  ACCESS:
    v[i]                      // index, like arrays
    v.back()                  // last element
    *v.begin()                // first element (via iterator)

  ITERATORS:
    begin()  -> first
    end()    -> ONE PAST last (don't deref)
    rbegin() -> last  (++ goes backward)
    rend()   -> one BEFORE first (don't deref)
    it holds ADDRESS,  *it holds VALUE
================================================================
*/

void explainVector() {

    // ---- 1. push_back vs emplace_back ------------------------
    vector<int> v21;
    v21.push_back(1);         // {1}
    v21.emplace_back(2);      // {1,2}  — slightly faster, builds in place

    // ---- 2. vector of pairs ----------------------------------
    vector<pair<int,int>> vp;
    vp.push_back({1, 2});     // push_back needs {} around the pair
    vp.emplace_back(3, 4);    // emplace_back doesn't — auto-makes the pair

    // ---- 3. pre-filled  vector<T>(size, value) ---------------
    vector<int> v1(5, 100);   // {100,100,100,100,100}  idx 0..4

    // ---- 4. size only (no value) -----------------------------
    vector<int> v2(5);        // {0,0,0,0,0}  (0 or garbage). Can still grow later.

    // ---- 5. copy a vector ------------------------------------
    vector<int> v3(5, 20);    // {20,20,20,20,20}
    vector<int> v4(v3);       // v4 = copy of v3, fully separate

    // ---- 6. access: index vs iterator ------------------------
    // v3[2] -> 20        (index)
    vector<int>::iterator it = v1.begin();  // it = address of first
    it++;                     // move forward one
    cout << *it << " ";       // 100  (*it = value at address)
    it = it + 2;
    cout << *it << " ";       // jump forward 2 more

    // ---- 7. end / rbegin / rend ------------------------------
    // for v1 = {20,40,50,100,1}
    vector<int>::iterator itEnd = v1.end();     // one PAST last -> itEnd-- to reach 1
    vector<int>::reverse_iterator rit = v1.rbegin(); // -> 1, ++ moves toward front
    vector<int>::reverse_iterator re  = v1.rend();   // before-first sentinel, don't deref

    // ---- 8. back() -------------------------------------------
    cout << v1.back() << " "; // last element
    cout << endl;

    // ---- 9. printing a vector --------------------------------
    vector<int> v;
    v.push_back(1);v.push_back(2); v.push_back(3); v.push_back(4); v.push_back(5);v.push_back(6);   // {1,2,3,4,5,6}

    // full iterator form
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;

    // auto = compiler figures out the type for you
    for (auto it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;

    // For each loop, range-based for: it IS the value here, not an iterator
    for (auto it : v)
        cout << it << " ";
    cout << endl;
    // What `it` does: `it` walks through v one element at a time, and each time around, `it` holds the actual value and not an address

    // v = {1, 2, 3, 4, 5, 6}
    // ---- 10. deletion in a vector----------------------
    // .erase(address)
    v.erase(v.begin()+1); // it deleted the second number inside vector v which is 2 here
    for(auto it:v){
      cout << it << " ";
    }
    cout << endl;
    // Updated vector v = {1, 3, 4, 5, 6}

    // range
    v.erase(v.begin(), v.begin()+3); 
    // First inclusive, last exclusive
    // [v.begin(), v.begin()+3)
    for(auto it:v){
      cout << it << " ";
    }
    cout << endl;

    // Updated vector v = {5, 6}

}

int main() {
    explainVector();
    return 0;
}