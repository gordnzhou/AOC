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

    map<string, vector<string>> adj;
    while (getline(cin, line)) {
        istringstream iss(line);
        string n, l, r;
        cin >> n >> l >> r;
        adj[n] = {l, r};
    }

    string cur = "AAA";
    int ans = 0;
    while (cur != "ZZZ") {
        if (steps[ans % steps.length()] == 'L') {
            cur = adj[cur][0];
        }
        else cur = adj[cur][1];
        ans++;
    }
    cout << ans << "\n";
}