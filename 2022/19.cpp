#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

vector<vector<int>> costs(4);
vector<int> maxCost(3, 0);

int nextBuild(int time, vector<int> robs, vector<int> mats, int prev) {
    if (time <= 0) return mats[3];

    int ans = 0;
    for (int r = 0; r < 4; ++r) {
        // already too many robots of this type
        if (r < 3 && robs[r] >= maxCost[r]) continue;

        // too much of this robot's material
        if (r < 3 && mats[r] + time*robs[r] >= time * maxCost[r]) continue;

        // robot is more than 1 "step" above or below current robot
        if (abs(r - prev) > 1) continue;

        int newTime = time;
        vector<int> newMats, newRobs;
        copy(mats.begin(), mats.end(), back_inserter(newMats));
        copy(robs.begin(), robs.end(), back_inserter(newRobs));

        bool canMake = true;
        while (newTime > 0) {
            canMake = true;
            for (int i = 0; i < 4; ++i) {
                if (newMats[i] < costs[r][i]) canMake = false;
                newMats[i] += newRobs[i];
            }
            newTime--;
            if (canMake) break;
        }

        if (!canMake) {
            ans = max(ans, newMats[3]);
            continue;
        }

        newRobs[r]++;
        for (int j = 0; j < 3; ++j) {
            newMats[j] -= costs[r][j];
        }
        ans = max(ans, nextBuild(newTime, newRobs, newMats, r));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    ll ans1 = 0, ans2 = 1;
    while (getline(infile, line)) {
        istringstream iss(line);
        vector<string> lines;
        string s;
        while (iss >> s) {
            lines.push_back(s);
        }

        costs.clear();
        for (int i = 0; i < 3; ++i) maxCost[i] = 0;
        costs[0] = {stoi(lines[6]), 0, 0, 0};
        costs[1] = {stoi(lines[12]), 0, 0, 0};
        costs[2] = {stoi(lines[18]), stoi(lines[21]), 0, 0};
        costs[3] = {stoi(lines[27]), 0, stoi(lines[30]), 0};
        for (int r = 0; r < 3; ++r) {
            for (int i = 0; i < 4; ++i) maxCost[r] = max(maxCost[r], costs[i][r]);
        }
    
        ans1 += nextBuild(24, {1, 0, 0, 0}, {0, 0, 0, 0}, 0) * stoi(lines[1]);
        if (stoi(lines[1]) <= 3) {
            ans2 *= nextBuild(32, {1, 0, 0, 0}, {0, 0, 0, 0}, 0);
        }
    }
    cout << ans1 << '\n' << ans2 << '\n';
}