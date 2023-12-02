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
        s = regex_replace(s, regex("one"), "oonee");
        s = regex_replace(s, regex("two"), "ttwoo");
        s = regex_replace(s, regex("three"), "tthreee");
        s = regex_replace(s, regex("four"), "ffourr");
        s = regex_replace(s, regex("five"), "ffivee");
        s = regex_replace(s, regex("six"), "ssixx");
        s = regex_replace(s, regex("seven"), "ssevenn");
        s = regex_replace(s, regex("eight"), "eeightt");
        s = regex_replace(s, regex("nine"), "nninee");
        s = regex_replace(s, regex("one"), "1");
        s = regex_replace(s, regex("two"), "2");
        s = regex_replace(s, regex("three"), "3");
        s = regex_replace(s, regex("four"), "4");
        s = regex_replace(s, regex("five"), "5");
        s = regex_replace(s, regex("six"), "6");
        s = regex_replace(s, regex("seven"), "7");
        s = regex_replace(s, regex("eight"), "8");
        s = regex_replace(s, regex("nine"), "9");
        char a = ' ';
        char b = ' ';
        for (
            }auto c : s) {
            if (isdigit(c)) {
                if (a == ' ') a = c;
                b = c;
            }
        }
        ans += stoi(string(1,a)+b);
    }

    cout << ans << "\n";
}