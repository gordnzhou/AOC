#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll; 


int solve(vector<ll> v) {
    if (count(v.begin(), v.end(), 0) == v.size()) {
        return 0;
    }
    vector<ll> v2;
    for (int i = 1; i < v.size(); ++i) {
        v2.push_back(v[i] - v[i - 1]);
    }
    return v[v.size() - 1] + solve(v2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;
    string s;

    ll ans = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<ll> v;
        ll n;
        while (iss >> n) {
            v.push_back(n);
        }
        ans += solve(v);
    }
    cout << ans << "\n";
}