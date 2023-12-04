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

    map<string, string> rep = {
        {"one", "o1ne"},
        {"two", "t2wo"},
        {"three", "t3hree"},
        {"four", "f4our"},
        {"five", "f5ive"},
        {"six", "s6ix"},
        {"seven", "s7even"},
        {"eight", "e8ight"},
        {"nine", "n9ine"}
    };

    ll ans = 0, cur = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        string s;
        iss >> s;

        for (auto r: rep) {
            s = regex_replace(s, regex(r.first), r.second);
        }
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