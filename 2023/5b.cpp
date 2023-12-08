#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 

pair<ll, ll> do_conv(pair<ll, ll> rng, ll src, ll dest) {
    return {dest + (rng.first - src), dest + (rng.second - src)};
}

vector<vector<vector<ll>>> steps;

ll solve(pair<ll, ll> seed, int depth) {
    if (depth >= steps.size()) {
        return seed.first;
    }

    ll start = seed.first, end = seed.second;
    for (auto op : steps[depth]) {
        ll dest = op[0], src = op[1], srcend = src + op[2] - 1;
        if (src > end || srcend < start) {
            continue;
        }

        // fully covered by range
        if (src <= start && srcend >= end) { 
            return solve(do_conv({start, end}, src, dest), depth + 1);
        }

        // left side partially covered
        if (src <= start && srcend < end) {
            ll a = solve(do_conv({start, srcend}, src, dest), depth + 1);
            ll b = solve({srcend + 1, end}, depth);
            return min(a, b);
        }

        // // right side partially covered
        if (src > start && srcend >= end) {
            ll a = solve({start, src - 1}, depth);
            ll b = solve(do_conv({src, end}, src, dest), depth + 1);
            return min(a, b);
        }

        // // inside partially covered
        if (start < src && srcend < end) {
            ll a = solve({start, src - 1}, depth);
            ll b = solve(do_conv({src, srcend}, src, dest), depth + 1);
            ll c = solve({srcend + 1, end}, depth);
            return min(a, min(b, c));
        }
    }

    // not in any range for current step
    return solve(seed, depth + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;

    vector<pair<ll, ll>> seeds;
    getline(cin, line);
    istringstream iss(line);
    iss >> s;
    while (iss >> s) {
        ll range;
        iss >> range;
        seeds.push_back({stoll(s), stoll(s) + range - 1});
    }

    ll ans = 1e18;
    bool skip = true;
    vector<vector<ll>> step;
    while (getline(cin, line)) {
        istringstream iss(line);
        string s;
        if (line.empty()) {
            if (skip) {
                skip = false;
                continue;
            }
            step.erase(step.begin());
            steps.push_back(step);
            step = {};
        }
        else {
            vector<ll> a(3);
            iss >> a[0] >> a[1] >> a[2];
            step.push_back(a);
        }
    }
    step.erase(step.begin());
    steps.push_back(step);

    for (auto s : seeds) {
        ans = min(ans, solve(s, 0));
    }
    cout << ans << "\n";
}