#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <regex>
using namespace std;
 
typedef long long ll; 


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    ll ans = 0, cur = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        string s;
        iss >> s;

        char a = ' ';
        char b = ' ';
        for (auto c : s) {
            if (isdigit(c)) {
                if (a == ' ') a = c;
                b = c;
            }
        }
        ans += stoi(string(1,a)+b);
    }

    cout << ans << "\n";
}