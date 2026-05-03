#include <bits/stdc++.h>
using namespace std;

void explainPair(){
    pair<int, int> p = {5, 6};
    cout << p.first << endl;

    pair<int, float> l = {15, 19.24};
    cout << l.second << endl;

    pair<int, pair<float, int>> m[] = {{5, {19.23, 4}}, {69, {22.41, 5}}, {51, {2.14, 6}}};
    cout << m[1].first << " " << m[1].second.first << " " << m[2].second.second;

}

int main(){
    explainPair();
    return 0;
}