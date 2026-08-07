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


void explainPQ(){
  // Similar to queue, but the guy who has the largest value stays at the top
  // Largest element stays at the top
  // Data is not stored in linear fashion, at inside tree is maintained

  // Maximum Heap
  priority_queue<int>pq;

  pq.push(5); // {5}
  pq.push(2); // {5, 2}
  pq.push(1); // {5, 2, 1}
  pq.push(13); // {13, 5, 2, 1}
  pq.push(10); // {13, 10, 5, 2, 1}

  cout << pq.top() << endl; // 13

  pq.pop(); // removed the top element (13 got removed)

  cout << pq.top() << endl; // 10


  // .size(), .empty(), .swap() functions same as others



  // If you want to store minimum element at top
  // Minimum Heap
  // Syntax -> priority_queue<int, vector<int>, greater<int>> pq;

  // Here min element stays at top
  // Known as Minimum Heap
  priority_queue<int, vector<int>, greater<int>> pq1;
  pq1.push(5); // {5}
  pq1.push(3); // {3, 5}
  pq1.push(10); // {3, 5, 10}
  pq1.push(2); // {2, 3, 5, 10}
  pq1.push(4); // {2, 3, 4, 5, 10}

  cout << pq1.top() << endl; // 2


// Time complexities:- 
// .push -> log(n)
// .top -> O(1)
// .pop -> log(n)
}

void explainSet(){
  // Set -> stores everything in sorted order, and only stores unique things(repetition not allowed)

  set<int>st; // Declaration

  // .insert() and .emplace() is used to add elements
  st.insert(1); // {1}
  st.insert(2); // {1, 2}
  st.insert(2); // {1, 2}
  st.emplace(4); // {1, 2, 4}
  st.insert(3); // {1, 2, 3, 4}

  // Not a linear container, a tree is maintained inside it

  // begin(), end(), rbegin(), rend(), size(), empty(), swap() are same as before

  // {1, 2, 3, 4}
  auto it = st.find(3); // this .find(number) is going to return a iterator pointing at that value

  // {1, 2, 3, 4}
  auto it1 = st.find(6);
  // if the element is not in the set, it will return an iterator that points to st.end(), i.e. an iterator that points to right after the end
  // currently it1 got returned an iterator that points to right after 4 i.e. right after the end

  int cnt = st.count(1); // if the element exist in the set, it going to give 1 else 0. Anything else is np as set only takes unique stuff


  // In .erase() you can send either element or iterator

  st.erase(2); 
  // Erases said element and maintains the sorted order, takes logarithmic time
  // {1, 3, 4}

  auto it2 = st.find(3); // returns an iterator pointing to 3
  st.erase(it2); // takes iterator and removes 3
  // {1, 4}
  // it takes constant time

  // [iterator a, iterator b) this is also possible
  set<int>st1;
  st1.insert(1); // {1}
  st1.insert(2); // {1, 2}
  st1.insert(10); // {1, 2, 10}
  st1.insert(21); // {1, 2, 10, 21}
  st1.insert(4); // {1, 2, 4, 10, 21}
  st1.insert(13); // {1, 2, 4, 10, 13, 21}

  auto it_a = st1.find(4);
  auto it_b = st1.find(21);

  // {1, 2, 4, 10, 13, 21}
  st.erase(it_a, it_b); // [it_a, it_b), first is inclusive and last not inclusive
  // {1, 2, 21}


  // .size(), .empty(), .swap(), .begin() all things same 

  // imp functions in set -> .find, .count, .erase, .insert


  // Syntax
  auto it_c = st.lower_bound(1);
  auto it_d = st.upper_bound(21);
  
  
  // In set, everything takes Log(n) times complexity
}

void explainMultiSet(){
  // It only obeys sorted rule, and no the unique rule
  // It stores everything in sorted order and repetition of element is allowed

  // Everything is same as set, it just can store multiple same elements too
  multiset<int>ms;

  ms.insert(1); // {1}
  ms.insert(2); // {1, 2}
  ms.insert(1); // {1, 1, 2}
  ms.insert(1); // {1, 1, 1, 2}
  ms.insert(3); // {1, 1, 1, 2, 3}
  ms.insert(2); // {1, 1, 1, 2, 2, 3}

  int cnt = ms.count(1); // gives 3
  cout << cnt << endl;

  // {1, 1, 1, 2, 2, 3}

  // {1, 1, 1, 3}
  ms.erase(2); // All 2's are erased
  int cnt_2 = ms.count(2);
  cout << cnt_2 << endl; // 0

  
  // {1, 1, 3}
  ms.erase(ms.find(1)); // Only a single 1 is erased
  int cnt_1 = ms.count(1); 
  cout << cnt_1 << endl; // 2 

  
  ms.insert(1); ms.insert(1); ms.insert(1); ms.insert(1); ms.insert(1); ms.insert(1);
  // {1, 1, 1, 1, 1, 1, 1, 1, 3}

  // Let's say we want to erase some instances of 1 
  auto it = ms.find(1); 
  auto stop = next(it, 4);
  ms.erase(it, stop); // erases [it, stop)

  // {1, 1, 1, 1, 3}

  int cnt_11 = ms.count(1);
  cout << cnt_11 << endl; // 4


  
  // rest all functions same as set
}

void explainUnorderedSet(){
  // All operations are similar to set(insert, etc)
  // They do not store in sorted order
  // Unique elements
  // It can have any random order, any element can be stored in any order, it doesn't matter how you fill
  // In most of the cases, time complexity is O(1)
  // Worst case -> O(N) happens once in a big moon

  unordered_set<int> st;

  // The lower_bound and upper_bound function do not work
}

void explainMap(){
  // It stores everything in respect of { key, value }
  // key and value can be of any datatype
  // The key has to be unique, value can be anything
  // For eg; roll numbers are key, hence unique, names are value -> could repeat with people of same name

  // Note:- Map stores unique key in sorted order

  // first datatype is for key, second is for value

  //map<int, int> mpp; 
  // int key, int value

  //map<int, pair<int, int>> mpp; 
  // int key
  // pair of integers value

  //map<pair<int, int>, int> mpp; 
  // key is pair of integers
  // value is integer

  // Ways to store
  map<int, int> mpp;

  mpp[1] = 2; 
  // It means for key 1, store value 2
  // {1:2}

  mpp.emplace(3, 10); // in emplace no need for {}
  // It means for key 3, store value 10
  // {1:2, 3:10}

  mpp.insert({4, 13});
  // For key 4, store value 13
  // {1:2, 3:10, 4:13}

  // it.first is the key
  // it.second is the value
  for(auto it:mpp){
    cout << it.first << ":" << it.second << endl;
  }
  /*
  1:2
  3:10
  4:13
  */

  map<pair<int, int>, int> mpp1;
  mpp1[{1, 2}] = 10;
  // for key (1, 2), store value 10
  // { (1,2): 10 }
  
  mpp1.emplace(make_pair(1, 3), 15); // emplace avoids the outer {}
  // for key (1, 3), store value 15

  mpp1.emplace(pair<int, int>{1, 4}, 16);
  // for key (1, 4), store value 16

  mpp1.insert({{2, 1}, 17});
  // It takes both inner {} and outer {}
  // for key (2, 1), store value 17

  mpp1.emplace(make_pair(2, 6), 81); // still will store in sorted order only
  mpp1.emplace(make_pair(2, 3), 21);
  mpp1.emplace(make_pair(6, 7), 69);

  // { (1,2):10, (1, 3):15, (1,4):16, (2,1):17, (2, 3):21, (2, 6):81, (6, 7): 69  }
  // it.first is the key which is pair here
  // it.second is the value
  for(auto it:mpp1){
    cout << "(" << it.first.first << "," << it.first.second << "):" << it.second << ", ";
  }
  // for (1, 2):10
  // it.first.first is 1 (key)
  // it.first.second is 2 (key)
  // it.second is 10 (value)
  cout << endl;


  // {1:2, 3:10, 4:13}
  // To access value through key
  cout << mpp[3] << endl; // gives value at key 3 -> 10
  cout << mpp[4] << endl; // 13

  // { (1,2):10, (1, 3):15, (1,4):16, (2,1):17, (2, 3):21, (2, 6):81, (6, 7): 69  }
  cout << mpp1[{1, 4}] << endl; // 16
  cout << mpp1[{2, 6}] << endl; // 81
  cout << mpp1[{2, 7}] << endl; // this key doesn't exist/it doesn't have any value stored -> prints null or zero means its empty



  // {1:2, 3:10, 4:13}
  // To find the address of a key
  auto it = mpp.find(4);
  // *it stores the whole element which is a pair here key:value, you can't cout a pair directly hence we used dereference
  cout << it->first << endl; // key 4
  cout << it->second << endl; // value 13 
  // Or
  cout << (*it).second << endl; // value 13

  // { (1,2):10, (1, 3):15, (1,4):16, (2,1):17, (2, 3):21, (2, 6):81, (6, 7): 69  }
  auto it_1 = mpp1.find({6, 7});

  // it_1 -> first; would be entire key which is a pair here hence we need first.first
  cout << it_1 -> first.first << endl; // 6(key)
  cout << it_1 -> first.second << endl; // 7(key)
  cout << it_1 -> second << endl; // 69 (value)

  // {1:2, 3:10, 4:13}
  auto it_2 = mpp.find(5); // since 5 is not available so this it_2 is just going to point to mpp.end() i.e point to just after the last element


  // erase, swap, size, empty, are same as above

  // Syntax
  auto it_4 = mpp.lower_bound(1);
  auto it_5 = mpp.upper_bound(2);

}

void explainMultiMap(){
  // Everything is same as map, only thing different is it can store duplicate keys
  // Stores everything in sorted order just like map

  // only map[key] cannot be used here
}

void explainUnorderedMap(){
  // Can store unique keys
  // Do not store in sorted order

  // Store in randomized order

  // In almost all cases, time complexity is O(1), worse case O(n) happens really less

  // Whereas in map, time complexity is log(n)
}

void explainExtra(){

  // To sort in c++ we can simply use sort(starting iterator, ending iterator)
  // first inclusive, last exclusive
  // [start, end)
  vector<int>v;
  v.push_back(5); 
  v.push_back(10);
  v.emplace_back(3);
  v.push_back(2);
  // {5, 10, 3, 2}
  sort(v.begin(), v.end()); // v.end() points to position just after last element
  // After sorting it became {2, 3, 5, 10}
  for(auto it:v){
    cout << it << " ";
  }
  cout << endl;

  // We can also sort some portion only
  vector<int>v1;
  v1.push_back(10);
  v1.push_back(5);
  v1.push_back(19);
  v1.push_back(1);
  v1.push_back(3);
  v1.push_back(-10);
  // {10, 5, 19, 1, 3, -10}
  // Let's say we only want to sort from 19 to 1

  sort(v1.begin()+1, v1.begin()+5);
  // {10, 1, 3, 5, 19, -10}

  for(auto it:v1){
    cout << it << " ";
  }

  cout << endl;

  // v = {2, 3, 5, 10}

  // What if we want to sort in descending order
  sort(v.begin(), v.end(), greater<int>());

  // v = {10, 5, 3, 2}
  for(auto it:v){
    cout << it << " ";
  }
  cout << endl;

  // We sorted ascending and descending order, now what if you want to sort it according to your own rules?

  pair<int, int> a[] = {{1, 2}, {2, 1}, {4, 1}};

  // Sort it according to second element in ascending order
  // If second element is same, then sort according to first element but in descending order

  // Acc to second element ascending order
  // {2, 1}, {4, 1}, {1, 2}

  // But when second element same, sort acc to first element in descending order
  // {4, 1}, {2, 1}, {1, 2} -> Final






  

}


int main(){
    //explainPair();
    //explainVector();
    //explainList();
    //explainDeque();
    //explainStack();
    //explainQueue();
    //explainPQ();
    //explainSet();
    //explainMultiSet();
    //explainUnorderedSet();
    //explainMap();
    //explainMultiMap();
    //explainUnorderedMap();
    explainExtra();

    return 0;
}







