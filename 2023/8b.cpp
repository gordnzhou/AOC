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

    string steps;
    cin >> steps;

    // REMOVE {'(', ')', ',', '='} FROM PUZZLE INPUT
    map<string, vector<string>> adj;
    while (getline(cin, line)) {
        istringstream iss(line);
        string n, l, r;
        cin >> n >> l >> r;
        adj[n] = {l, r};
    }

    ll ans = 1;
    for (auto n : adj) {
        if (n.first[2] != 'A') continue;

        ll cnt = 0;
        string cur = n.first;
        while (true) {
            if (cur[2] == 'Z') {
                ans = ans * cnt / gcd<int64_t>(cnt, ans);
                break;
            }

            if (steps[cnt % steps.length()] == 'L') {
                cur = adj[cur][0];
            }
            else cur = adj[cur][1];
            cnt++;
        }
    }

    cout << ans << "\n";
}