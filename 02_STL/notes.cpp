#include <bits/stdc++.h> 
using namespace std;

// Pairs
void explainPair(){
    pair<int, int> p = {1, 3}; // Defining and assigning pairs, variable p contains {1, 3}
    cout << p.first << " " << p.second << endl;   // Access first and second element by variable.first and variable.second
    // Output: 1 3

    // Nested property of pair
    // Since it's a pair, it stored two numbers. To store three, what if {new number, {old pair}} 
    // Let's do this
    // Make sure to update the data type as this time the second thing is a pair of integers and not just an integer

    pair<int, pair<int, int>> l = {5, {1, 3}};
    cout << l.first << " " << l.second.first << " " << l.second.second << endl;
    // Output: 5 1 3

    // To print the individual inside another pair, l.second.first and l.second.first
    // You can't print the pair inside like l.second btw 

    // Declaring pair array 
    // We will declare an array whose each element consist of a pair
    pair<int, int> arr[] = {{1, 2}, {3, 4}, {5, 6}};
    cout << arr[0].first << " " << arr[2].second << " " << arr[1].first;
    // Output: 1 6 3

    // Again you can't print arr[0] on its own, you need to specify .first or .second
}
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

    // ---- 11. Insert Function ---------------------------
    //          .insert(adress, value) or .insert(adress, size, value) -> when you want 5 times 500 value so size is 5 and value is 500 (500, 500, 500, 500, 500)
    // An insert function in a vector is costly in terms of time

    v.insert(v.begin(), 10); // added 10 value at start 
    for(auto it:v){
      cout << it << " ";
    }
    cout << endl; // {10, 5, 6}

    v.insert(v.begin()+1, 4, 72); // we are adding (72, 72, 72, 72) starting from position begin+1
    for(auto it:v){
      cout << it << " ";
    }
    cout << endl; // {10, 72, 72, 72, 72, 5, 6}

    v.insert(v.end()-2, 53); // we added 53 in 2nd last pos as v.end() is just after last element 6, so it pushes 5, 6 further right
    for(auto it:v){
      cout << it << " ";
    }
    cout << endl; // {10, 72, 72, 72, 72, 53, 5, 6}
 


    // ( Not required alot )
    // Inserting one vector into another
    // let's say we are inserting vector copy into v (copy -> v)
    // v.insert(address of v where you want to insert,  address of the range of copy you want to be inserted);
    // v.insert(v.begin(), copy.begin(), copy.end());
    vector<int>copy(3, 67); // {67, 67, 67}

    v.insert(v.begin()+3, copy.begin(), copy.end());

    for(auto it:v){
      cout << it << " ";
    }
    cout << endl;  // {10, 72, 72, 67, 67, 67, 72, 72, 53, 5, 6}



    // ---- 12. Size of a vector -------------
    //             v.size();

    cout << v.size(); // 11
    cout << endl;


    // ---- 13. Remove last element ---------
    //            v.pop_back(); -> removes the last element

    v.pop_back(); // {10, 72, 72, 67, 67, 67, 72, 72, 53, 5}
    v3.pop_back(); // {20, 20, 20, 20}

    for(auto it:v){
      cout << it << " ";
    }
    cout << endl;

    // ---- 14. Swap two vectors -----------
    // v1 = {100, 100, 100, 100, 100}
    // v3 = {20, 20, 20, 20}
    
    v1.swap(v3);

    cout << "v1: ";
    for(auto it:v1){
      cout << it << " ";
    }
    cout << endl;

    cout << "v3: ";
    for (auto it:v3){
      cout << it << " ";
    }
    cout << endl;

    // Now
    // v1 = {20, 20, 20, 20}
    // v3 = {100, 100, 100, 100, 100}


    // -------- 15. Empty any vector ------------
    // Erases all the elements in the vector, the vector becomes empty
    // v.clear();

    v.clear(); 

    cout << "v: ";
    for(auto it:v){
      cout << it << " ";
    }
    cout << endl;
    // v = {};


    // v.empty()
    // This returns true or false depending if the vector is empty or not
    // if it is empty v.empty() returns true else false

    cout << v.empty(); // 1(true)
    cout << endl;

    cout << v3.empty(); // 0(false)
    cout << endl;


    // These were the functions that are generally required in a vector
}

void explainList(){
    // List is a container also dynamic in nature like vector -> it gives you front operation as well
    // An insert function in a vector is costly in terms of time complexity
    // .push_front() is really cheap in terms of time complexity

    list<int> ls;

    ls.push_back(2); // {2}
    ls.emplace_back(4); // {2, 4}

    ls.push_front(1); // {1, 2, 4}
    ls.emplace_front(10); // {10, 1, 2, 4}

    // Rest functions same as vector
    // begin, end, rbegin, rend, clear, insert, size, swap

    for(auto it:ls){
        cout << it << " ";
    }
    cout << endl; // {10, 1, 2, 4}
}

// Exactly similar to list and vector
void explainDeque(){
    deque<int>dq;
    dq.push_back(1); // {1}
    dq.emplace_back(2); // {1, 2}
    dq.push_front(3); // {3, 1, 2}
    dq.emplace_front(4); // {4, 3, 1, 2}

    for(auto it:dq){
        cout << it << " ";
    }
    cout << endl;


    dq.pop_back(); // {4, 3, 1}
    for(auto it:dq){
        cout << it << " ";
    }
    cout << endl;

    dq.pop_front(); // {3, 1}
    for(auto it:dq){
        cout << it << " ";
    }
    cout << endl;


    cout << dq.back() << endl; // 1
    cout << dq.front() << endl; // 3

    // Rest functions same as vector
    // begin, end, rbegin, rend, clear, insert, size, swap

}


// LIFO (last in first out)
// like pile of books 
// you placed first book at bottom, then next above it, and so on
// so the last book you place, will be at top and come out as first
void explainStack(){
    stack<int> st;

    

    // In stack there is generic three functions that we will deal with
    // push, pop, top 
    // Time complexity for all these above function in stack is Big O(1)

    // In others (vectors, list, deque) -> we had push_back, emplace_back, pop_back, pop_front, push_front, emplace_front(last 3 not in vectors), 
    // but here it's just push, emplace, pop -> no back/front

    // In stack pop() removes the top element

    st.push(1); // {1}
    st.push(2); // {2, 1}
    st.push(70); // {70, 2, 1}
    st.push(55); // {55, 70, 2, 1}
    st.emplace(21); // {21, 55, 70, 2, 1}

    cout << st.top() << endl; // 21

    // Indexing access is not allowed
    // st[index] is invalid here


    st.pop(); // {55, 70, 2, 1}, top one got removed
    cout << st.top() << endl; // 55


    cout << st.size() << endl; // 4

    cout << st.empty() << endl; // returns 0 or 1 depending if the stack is empty or not, // 0


    stack<int> st1, st2;

    for(int x: {1, 2, 3}) st1.push(x);

    for(int x: {6, 7, 8}) st2.push(x);

    
    // Stack has no iterators, so no range-based for loop can be used to print entire stack

    // st1 = {3, 2, 1}
    // st2 = {8, 7, 6}

    cout << st1.top() << endl; // 3
    cout << st2.top() << endl; // 8

    st1.swap(st2);

    // st1 = {8, 7, 6}
    // st2 = {3, 2, 1}

    cout << st1.top() << endl; // 8
    cout << st2.top() << endl; // 3

}

// Similar to stack but it follows FIFO
// first in first out
// Queue means like a line 
// So first person comes stand first and then next person and so on
void explainQueue(){
    queue<int> q;

    q.push(1); // {1}
    q.push(2); // {1, 2}
    q.push(5); // {1, 2, 5}
    q.emplace(10); // {1, 2, 5, 10}

    cout << q.back() << endl; // 10
    cout << q.front() << endl; // 1

    q.pop(); // it removes the first element
    // {2, 5, 10}

    cout << q.front() << endl; // 2

    q.pop(); // removes current first element
    // {5, 10}

    cout << q.front() << endl; // 5

    // size, swap, empty -> same as stack

}

int main(){
    //explainPair();
    //explainVector();
    //explainList();
    //explainDeque();
    //explainStack();
    explainQueue();

    return 0;
}







