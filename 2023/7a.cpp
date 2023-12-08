#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 

vector<char> ranking = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

int get_rank(char c) {
    int ret = 0;
    for (auto r : ranking) {
        if (r == c) return ret;
        ret++;
    }
    return 0;
}

int get_type(string hand) {
    map<char, int> mp;
    for (auto c : hand) {
        ++mp[c];
    }
    if (mp.size() == 1) return 7;
    if (mp.size() == 2) {
        if (mp.begin()->second == 1 || mp.begin()->second == 4) return 6;
        else return 5;
    }
    if (mp.size() == 3) {
        bool has_triple = false;
        for (auto x : mp) {
            has_triple |= (x.second == 3);
        }
        if (has_triple) return 4;
        return 3;
    }
    if (mp.size() == 4) return 2;
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;


    vector<pair<string, ll>> inp;
    while (getline(cin, line)) {
        istringstream iss(line);
        pair<string, int> x;
        iss >> x.first >> x.second;
        inp.push_back(x);
    }

    sort(inp.begin(), inp.end(),
        [](const pair<string, ll> &a, const pair<string, ll> &b) 
    {
        int ta = get_type(a.first), tb = get_type(b.first);
        if (ta != tb) return ta > tb; 
        for (int i = 0; i < 5; ++i) {
            int ra = get_rank(a.first[i]), rb = get_rank(b.first[i]);
            if (ra != rb) return ra < rb;
        }
        return false;
    });

    ll ans = 0;
    for (ll i = 0; i < inp.size(); ++i) {
        cout << inp[i].first << " ";
        ans += inp[i].second * (ll)(inp.size() - i);
    }
    cout << ans << "\n";
}