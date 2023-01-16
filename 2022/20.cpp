#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

const int KEY = 811589153;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    vector<pair<ll, int>> a;
    int idx = 0;
    while (getline(infile, line)) {
        ll x = stoi(line);
        x *= KEY;
        a.push_back({x, idx});
        idx++;
    }
    int n = a.size();

    int mix = 10;
    while (mix--) {
        for (int i = 0; i < n; ++i) {
            int pos;
            for (int j = 0; j < n; ++j) {
                if (a[j].second == i) {
                    pos = j;
                    break;
                }
            }

            bool fwd = (a[pos].first > 0);
            ll steps = abs(a[pos].first) % (n - 1);
            while (steps--) {
                int next = pos - 1;
                if (fwd) next = pos + 1;
                next = ((next % n) + n) % n;
                swap(a[pos], a[next]);
                pos = next;
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!a[i].first) {
            for (int j = 1; j <= 3; ++j) {
                ans += a[(i + j*1000) % n].first;
            }
        }
    }
    cout << ans << "\n";
}