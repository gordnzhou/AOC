#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 


map<string, pair<ll, string>> mp;
vector<pair<string, ll>> ops;

ll calc(string name) {
    if (mp[name].first != 0) return mp[name].first;

    ll val = 0;
    string a = mp[name].second.substr(0, 4);
    string b = mp[name].second.substr(7, 4);
    char op = mp[name].second[5];

    if (op == '*') val = calc(a) * calc(b);
    else if (op == '+') val = calc(a) + calc(b);
    else if (op == '-') val = calc(a) - calc(b);
    else val = calc(a) / calc(b);

    return val;
}

bool calc2(string name) {
    if (name == ME) {
        return true;
    }
    if (mp[name].first != 0) return false;

    ll val = 0;
    string a = mp[name].second.substr(0, 4);
    string b = mp[name].second.substr(7, 4);
    char op = mp[name].second[5];

    if (calc2(a)) {
        string s = {op, '0'};
        ops.push_back({s, calc(b)});
        return true;
    }
    else if (calc2(b)) {
        string s = {op, '1'};
        ops.push_back({s, calc(a)});
        return true;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    while (getline(infile, line)) {
        istringstream iss(line);
        if (line.length() > 16) {
            mp[line.substr(0, 4)] = {0, line.substr(6, line.length() - 6)};
        }
        else {
            mp[line.substr(0, 4)] = {stoi(line.substr(6, line.length() - 6)), "a"};
        }
    }

    cout << calc("root") << "\n";
    calc2("root");
    double ans = ops[ops.size() - 1].second;
    for (int x = 0; x < 2; ++x) {
        ll l = 0, r = 1e18;
        while (l <= r) {
            ll mid = l + (r - l)/2LL;
            double tot = mid;
            for (int i = 0; i < ops.size() - 1; ++i) {
                if (ops[i].first[0] == '+') tot += ops[i].second;
                else if (ops[i].first[0] == '*') tot *= ops[i].second;
                else if (ops[i].first[0] == '-') {
                    if (ops[i].first[1] == '0') tot -= ops[i].second;
                    else tot = ops[i].second - tot;
                }
                else {
                    if (ops[i].first[1] == '0') tot /= ops[i].second;
                    else tot = ops[i].second / tot;
                }
            }

            if (tot == ans) {
                cout << mid << "\n";
                break;
            }

            // result can be either increasing or decreasing as your number increases
            if (x) {
                if (tot > ans) l = mid + 1;
                else r = mid - 1;
            }
            else {
                if (tot < ans) l = mid + 1;
                else r = mid - 1;
            }
        }
    }
}