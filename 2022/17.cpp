#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

const int N = 1e5, WIDTH = 7;

ll TAR = 1000000000000;

map<ll, pair<ll, ll>> SEEN;
bool grid[WIDTH][N] = {false};

vector<string> shapes[5] = {
    {"####"},
    {".#.", "###", ".#."},
    {"..#", "..#", "###"},
    {"#", "#", "#", "#"},
    {"##", "##"}
};

bool canPlace(int x, int y, int j) {
    vector<string> shape = shapes[j];
    for (int i = 0; i < shape.size(); ++i) {
        for (int j = 0; j < shape[i].length(); ++j) {
            if (shape[i][j] == '.') continue;

            int newX = x + j;
            int newY = y + shape.size() - i - 1;
            if (newX >= 7 || newX < 0 || newY < 0 || grid[newX][newY]) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line, s;

    while (getline(infile, line)) {
        istringstream iss(line);
        iss >> s;
    }

    int ans1 = 0;
    ll cnt = 0, h = -1, dirPos = 0, ans2 = 0;
    while (cnt < TAR) {
        int x = 2, y = h + 4;
        while (true) {
            bool toRight = s[dirPos % s.length()] == '>';

            if (toRight && canPlace(x + 1, y, cnt % 5)) x++;
            else if (!toRight && canPlace(x - 1, y, cnt % 5)) x--;
            dirPos++;

            if (canPlace(x, y - 1, cnt % 5)) y--;
            else break;
        }

        vector<string> shape = shapes[cnt % 5];
        for (int i = 0; i < shape.size(); ++i) {
            for (int j = 0; j < shape[i].length(); ++j) {
                if (shape[i][j] == '.') continue;

                ll newX = x + j;
                ll newY = y + shape.size() - i - 1;
                grid[newX][newY] = true;
                h = max(h, newY);
            }
        }

        ll key = 0, LIM = 10;
        for (ll i = 0; i < WIDTH; ++i) {
            ll pos = 1e4;
            for (ll j = 0; j < LIM; ++j) {
                if (h - j < 0) break;
                if (grid[h - j]) pos = min(pos, h - j + 1);
            }
            if (pos == 1e4) pos = 0;
            key += pos * pow(LIM + 1LL, i);
        }
        key += (cnt % 5) * pow(LIM + 1LL, 7LL);
        key += (dirPos % s.length()) * pow(LIM + 1LL, 7LL) * 6;

        // no need to repeat if there's a cycle!
        if (SEEN.count(key) && !ans2) {
            ll dh = h - SEEN[key].first;
            ll dcnt = cnt - SEEN[key].second;
            ans2 = ((TAR - cnt) / dcnt) * dh;
            cnt += ((TAR - cnt) / dcnt) * dcnt;
        }
        else SEEN.insert({key, {h, cnt}});

        if (cnt == 2022) ans1 = h - 1;
        cnt++;
    }

    cout << ans1 << "\n";
    cout << h + ans2 + 1 << "\n";
}   