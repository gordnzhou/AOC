#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

vector<pair<ll, char>> ops = {
    {2, '2'},
    {1, '1'},
    {0, '0'},
    {-1, '-'},
    {-2, '='}
};

vector<ll> bounds(1, 0LL);

// max length of SNAFU number
ll LEN = 30;

ll fromSnafu(string line) {
    ll pwr = 1, num = 0;
    for (ll i = line.size() - 1; i >= 0; --i) {
        ll x = 0;
        for (auto o : ops) {
            if (o.second == line[i]) {
                x = o.first;
                break;
            }
        }
        num += x * pwr;
        pwr *= 5;
    }
    return num;
}

string toSnafu(ll tar, string ret, ll tot) {
    if (tot == tar) {
        while (ret.length() < LEN) ret.push_back('0');

        for (int i = 0; i < ret.length(); ++i) {
            if (ret[i] != '0') {
                return ret.substr(i, ret.length() - i);
            }
        }
    }

    ll p = LEN - ret.length() - 1LL;
    for (int i = 0; i < ops.size(); ++i) {
        ll y = pow(5LL, p) * ops[i].first;
        ll mx = tot + y + 2LL * bounds[p], mn = tot + y - 2LL * bounds[p];
        if (mx < tar || mn > tar) continue;

        string s = toSnafu(tar, ret + ops[i].second, tot + y);
        if (s.length()) return s;
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    string line;
    ll tot = 0;
    while (getline(cin, line)) {
        tot += fromSnafu(line);
    }

    ll cur = 0, b = 1;
    for (int i = 0; i < LEN; ++i) {
        cur += b;
        bounds.push_back(cur);
        b *= 5LL;
    }

    cout << toSnafu(tot, "", 0LL) << "\n";
}