#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    ll ans1 = 0, ans2 = 0, cur = 0;
    vector<int> top;

    while (getline(cin, line)) {
        istringstream iss(line);
        string s;
        iss >> s;

        if (!s.length()) {
            top.push_back(cur);
            ans1 = max(ans1, cur);
            cur = 0;
        }
        else cur += stoi(s);
    }

    sort(top.begin(), top.end());
    for (int i = 0; i < 3; ++i) {
        ans2 += top[top.size() - i - 1];
    }
    cout << ans1 << " " << ans2 << "\n";
}