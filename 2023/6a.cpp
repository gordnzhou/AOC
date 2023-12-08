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


    vector<int> times, dists;
    bool first = true;
    while (getline(cin, line)) {
        istringstream iss(line);
        string s;
        iss >> s;
        while (iss >> s) {
            if (first) times.push_back(stoi(s));
            else dists.push_back(stoi(s));
        }
        first = false;
    }

    ll ans = 1;
    for (int i = 0; i < times.size(); ++i) {
        int cnt = 0;
        for (int j = 1; j < times[i]; ++j) {
            if (times[i] * j - j * j > dists[i]) cnt++;
        }
        ans *= cnt;
    }

    cout << ans << "\n";
}