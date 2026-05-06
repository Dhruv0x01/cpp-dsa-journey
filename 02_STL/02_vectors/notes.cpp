#include <bits/stdc++.h>
using namespace std;

/*
================================================================
   STL NOTES — VECTOR
================================================================
Why learn vector deeply?
Understand every possible function of vector, because these
functions will be similar in all the other containers like
queue, list, map, set.

What is a vector?
- A container that stores values just like an array, BUT it is
  dynamic in nature — its size is NOT fixed.
- Unlike arrays (whose size is fixed, so you can't add new
  values once declared), a vector can grow/shrink at runtime.
- If there is a requirement where you do NOT know the size
  beforehand, vector is the right choice.
================================================================
*/

void explainVector() {

    // ----------------------------------------------------------
    // 1. DECLARATION + push_back() vs emplace_back()
    // ----------------------------------------------------------

    vector<int> v;          // declares an empty vector that holds ints
                            // this line creates an empty container

    v.push_back(1);         // pushes 1 into v
                            // container now: {1}  — no longer empty

    v.emplace_back(2);      // similar to push_back()
                            // dynamically increases the vector size and
                            // pushes 2 at the back
                            // container now: {1, 2}

    // NOTE: emplace_back() is slightly faster than push_back().


    // ----------------------------------------------------------
    // 2. VECTOR OF PAIRS
    // ----------------------------------------------------------

    vector<pair<int, int>> vp;

    vp.push_back({1, 2});   // for push_back() with pairs, we MUST wrap
                            // the values in {} — so it's {1, 2} inside ( )

    vp.emplace_back(3, 4);  // for emplace_back(), we can just enter the
                            // numbers inside ( ), no need of {}.
                            // On seeing two values, it automatically
                            // assumes them to be a pair.


    // ----------------------------------------------------------
    // 3. VECTOR PRE-FILLED WITH A VALUE   →   vector<T> name(size, value)
    // ----------------------------------------------------------

    vector<int> v1(5, 100); // creates a container of size 5
                            // with value 100 placed in all positions
                            // v1 = {100, 100, 100, 100, 100}
                            // indices go from 0 to 4


    // ----------------------------------------------------------
    // 4. VECTOR WITH ONLY SIZE (no value given)
    // ----------------------------------------------------------

    vector<int> v2(5);      // only size declared, no value given
                            // creates vector v2 of size 5 with value 0
                            // or any garbage value
                            // v2 = {0, 0, 0, 0, 0}  (0 or garbage,
                            // depending on compiler)
                            //
                            // Even though we declared size as 5, it can
                            // still change later — just call v2.push_back(...)
                            // and it will dynamically grow and add the new
                            // value at the end.


    // ----------------------------------------------------------
    // 5. COPYING ONE VECTOR INTO ANOTHER
    // ----------------------------------------------------------

    vector<int> v3(5, 20);  // v3 = {20, 20, 20, 20, 20}

    // What if I want to copy this container v3 into some other vector?
    vector<int> v4(v3);     // creates another container v4 which is a
                            // COPY of v3.
                            // v3 and v4 are two SEPARATE containers that
                            // happen to hold the same values.
                            // v4 = {20, 20, 20, 20, 20}


    // ----------------------------------------------------------
    // 6. ACCESSING VALUES IN A VECTOR
    // ----------------------------------------------------------

    // ---- Way 1: index access (same as arrays) ----
    //
    //   For v3 = {20, 20, 20, 20, 20}:
    //     v3[2] is 20, v3[4] is 20, etc.
    //
    //   Another example — if v = {1, 10, 20, 15, 16}:
    //     v[2] is 20 and v[4] is 16, and so on.

    // ---- Way 2: iterators ----
    //
    //   vector<int>::iterator it = v.begin();
    //
    // - v.begin() points to the memory address of the first element of v.
    // - So `it` stores an ADDRESS, not the value directly.
    // - If we print `it` (i.e. v.begin()), we get a memory address.
    // - To access the actual VALUE, we dereference it using *it,
    //   just like with pointers.
    //       it   →  holds the address
    //       *it  →  the value sitting at that address

    vector<int>::iterator it = v1.begin();
    it++;                   // move iterator one step forward
    cout << *it << " ";     // prints the value at the new address
                            // (second element of v1, which is 100)
    
    it = it + 2;
    cout << *it << " ";

    // ----------------------------------------------------------
    // 7. OTHER ITERATOR ENDPOINTS — end(), rbegin(), rend()
    // ----------------------------------------------------------

    // Say v1 = {20, 40, 50, 100, 1}

    vector<int>::iterator itEnd = v1.end();
    // v1.end() does NOT point to the address of 1 (the last element).
    // It points to some address just AFTER 1 (one past the last).
    // Hence to access 1, we need to do itEnd-- first, then *itEnd gives 1.


    // ---- Rarely used: .rbegin() and .rend() (reverse iterators) ----
    //
    // In a reverse iterator, ++ moves in REVERSE direction
    // (i.e. toward the front of the vector).

    vector<int>::reverse_iterator rit1 = v1.rbegin();
    // rbegin = reverse begin → points to the LAST element (the 1).
    // *rit1 gives 1.
    // Doing rit1++ moves BACKWARD toward 20.
    // i.e. on rit1++ it moves to 100.

    vector<int>::reverse_iterator rit2 = v1.rend();
    // rend = reverse end → points to one position BEFORE the first element (before 20).
    // Sentinel only — do NOT dereference it.
    // Used for loop termination, just like end().


    // ----------------------------------------------------------
    // 8. v1.back() — DIRECT ACCESS TO THE LAST ELEMENT
    // ----------------------------------------------------------

    cout << v1.back() << " ";
    // .back() means: give us the LAST element of the vector container.
    // For v1 = {20, 40, 50, 100, 1}, this prints 1.


    // ----------------------------------------------------------
    // 9. PRINTING A VECTOR — multiple ways   
    // ----------------------------------------------------------
    




}

int main() {
    explainVector();
    return 0;
}