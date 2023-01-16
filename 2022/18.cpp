#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

const int N = 2e5, MX = 24;

int toKey(int x, int y, int z) {
    return x + y * MX + z * MX * MX;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    vector<vector<bool>> sides(N, vector<bool>(6, 0));
    vector<bool> isOuter(N, 0), coords(N, 0);

    int cnt = 0, mn = 1e9;
    while (getline(infile, line)) {
        stringstream ss(line);
        vector<int> pts;
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            pts.push_back(stoi(substr));
        }
        pts[0]++; pts[1]++; pts[2]++;

        int key = toKey(pts[0], pts[1], pts[2]);
        coords[key] = true;
        cnt++;
    }

    isOuter[0] = true;
    for (int i = 0; i < MX; ++i) {
        for (int x = 0; x < MX; ++x) {
            for (int y = 0; y < MX; ++y) {
                for (int z = 0; z < MX; ++z) {
                    int key = toKey(x, y, z);
                    if (coords[key]) continue;
                    if (x < MX - 1 && isOuter[toKey(x + 1, y, z)]) isOuter[key] = true;
                    if (x > 0 && isOuter[toKey(x - 1, y, z)]) isOuter[key] = true;
                    if (y < MX - 1 && isOuter[toKey(x, y + 1, z)]) isOuter[key] = true;
                    if (y > 0 && isOuter[toKey(x, y - 1, z)]) isOuter[key] = true;
                    if (z < MX - 1 && isOuter[toKey(x, y, z + 1)]) isOuter[key] = true;
                    if (z > 0 && isOuter[toKey(x, y, z - 1)]) isOuter[key] = true;
                }
            }
        }
    }

    ll touching = 0, outer = 0;
    for (int i = 0; i < N; ++i) {
        if (!coords[i]) continue;
        int key = i;
        int z = key / (MX*MX); key %= MX*MX;
        int y = key / MX; key %= MX;
        int x = key;
        
        for (int j = 0; j < 6; ++j) {
            int dir = j % 2;
            int diff = (j - (j % 2)) / 2;
            int op = (dir % 2 ? 1 : -1);

            int newX = x + (diff == 0 ? op : 0);
            int newY = y + (diff == 1 ? op : 0);
            int newZ = z + (diff == 2 ? op : 0);
            int newKey = toKey(newX, newY, newZ);

            outer += isOuter[newKey];

            if (coords[newKey] && !sides[newKey][dir + diff * 2]) {
               touching++;
               sides[newKey][dir + diff * 2] = 1;
            }
        }
    }

    cout << 6 * cnt - touching << "\n";
    cout << outer << "\n";
}