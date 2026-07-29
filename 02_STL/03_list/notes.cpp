#include <bits/stdc++.h>
using namespace std;

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

int main(){
    explainList();
    return 0;
}