#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;

    vector<ll> seeds;
    getline(cin, line);
    istringstream iss(line);
    iss >> s;
    while (iss >> s) {
        seeds.push_back(stoll(s));
    }

    ll ans = 1e18;
    bool skip = true;
    vector<vector<ll>> conv;
    while (getline(cin, line)) {
        istringstream iss(line);
        string s;
        if (line.empty()) {
            if (skip) {
                skip = false;
                continue;
            }
            // stuff here
            conv.erase(conv.begin());

            for (int i = 0; i < seeds.size(); i++) {
                for (auto c : conv) {
                    ll dest = c[0], src = c[1], rng = c[2];
                    int diff = seeds[i] - src;
                    if (0 <= diff && diff < rng) {
                        seeds[i] = dest + diff;
                        break;
                    }
                }
            }
            conv = {};
        }
        else {
            vector<ll> a(3);
            iss >> a[0] >> a[1] >> a[2];
            conv.push_back(a);
        }
    }


    for (int i = 0; i < seeds.size(); i++) {
        for (auto c : conv) {
            ll dest = c[0], src = c[1], rng = c[2];
            int diff = seeds[i] - src;
            if (0 <= diff && diff < rng) {
                seeds[i] = dest + diff;
                break;
            }
        }
    }
    for (auto s : seeds) {
        ans = min(ans, s);
    }
    cout << ans << "\n";
}