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


    ll time, dist;
    bool first = true;
    while (getline(cin, line)) {
        istringstream iss(line);
        string s, cur = "";
        iss >> s;
        while (iss >> s) {
            cur.append(s);
        }
        if (first) time = stoll(cur);
        else dist = stoll(cur);
        first = false;
    }

    ll ans = 0;
    for (ll i = 1; i < time; ++i) {
        if (time * i - i * i > dist) ans++;
    }

    cout << ans << "\n";
}