#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 

ll solve(string row, vector<int> key, string rsf) {
    if (row.empty()) {
        vector<int> key2;
        int cur = 0;
        for (int i = 0; i < rsf.size(); ++i) {
            if (rsf[i] == '#') {
                cur++;
            }
            else {
                if (cur) key2.push_back(cur);
                cur = 0;
            }
        }
        if (cur) key2.push_back(cur);

        ll ret = key2.size() == key.size();
        for (int i = 0; i < min(key2.size(), key.size()); ++i) {
            ret &= key[i] == key2[i];
        }
        return ret;
    }

    if (row[0] == '?') {
        ll a = solve(row.substr(1, row.length() - 1), key, rsf + '.');
        ll b = solve(row.substr(1, row.length() - 1), key, rsf + '#');
        return a + b;
    }
    return solve(row.substr(1, row.length() - 1), key, rsf + row[0]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;


    ll ans = 0;
    while (getline(cin, line)) {
        string row;
        istringstream iss(line);

        iss >> row;

        // REMOVE ALL COMMAS FROM PUZZLE INPUT
        vector<int> key;
        int x;
        while (iss >> x) {
            key.push_back(x);
        }

        ans += solve(row, key, "");
    }


    cout << ans << "\n";
}