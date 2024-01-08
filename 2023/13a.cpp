 #include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 

vector<ll> row, col;

int solve() {
    int ans = 0;

    for (int i = 0; i < row.size() - 1; ++i) {
        bool ok = true;
        for (int j = 0; j < row.size(); ++j) {
            if (i - j < 0 || i + j + 1 >= row.size()) continue;
            ok &= row[i - j] == row[i + j + 1];
        }
        if (ok) ans += (i + 1) * 100;
    }

    for (int i = 0; i < col.size() - 1; ++i) {
        bool ok = true;
        for (int j = 0; j < col.size(); ++j) {
            if (i - j < 0 || i + j + 1 >= col.size()) continue;
            ok &= col[i - j] == col[i + j + 1];
        }
        if (ok) {
            ans += i + 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;

    int ans = 0;
    ll i = 0;
    while (getline(cin, line)) {
        if (line.empty()) {
            ans += solve();
            row.clear();
            col.clear();
            i = 0;
            continue;
        }

        ll j = 0;
        for (auto c : line) {
            if (i >= row.size()) {
                row.push_back((1LL << j) * (c == '#'));
            }
            else row[i] += (1LL << j) * (c == '#');
            if (j >= col.size()) {
                col.push_back((1LL << i) * (c == '#'));
            }
            else col[j] += (1LL << i) * (c == '#');
            j++;
        }
        i++;
    }
    ans += solve();
    cout << ans << "\n";
}