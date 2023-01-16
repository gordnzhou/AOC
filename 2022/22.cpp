#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll; 

vector<pair<int, int>> D = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

const int N = 1e4;
int FACING = 0, SIZE;
vector<pair<int, int>> sqs, valid;
vector<vector<int>> adj = {
    {1, 2, 4, 5},
    {5, 3, 2, 0},
    {1, 3, 4, 0},
    {1, 5, 4, 2},
    {2, 3, 5, 0},
    {4, 3, 1, 0}
};

int getSq(pair<int, int> p) {
    for (int i = 0; i < sqs.size(); ++i) {
        if (sqs[i] == p) return i;
    }
    return -1;
}

string path(pair<int, int> cur, pair<int, int> tar, string res, int vis) {
    if (cur == tar) return res + "X";
    string ret = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    for (int i = 0; i < 4; ++i) {
        bool ok = false;
        pair<int, int> nw = {cur.first + D[i].first, cur.second + D[i].second};
        for (int j = 0; j < 6; ++j) {
            pair<int, int> v = valid[j];
            if (v == nw && !(vis & (1 << j))) {
                string x = res + to_string(i);
                string s = path(nw, tar, x, vis | (1 << j));
                if (s[s.length() - 1] == 'X') {
                    if (ret.length() >= s.length()) ret = s;
                }
            }
        } 
    }
    return ret;
}

int calcDir(pair<int, int> from, pair<int, int> to) {
    int i = getSq(from);
    string p1 = path(from, to, "", 0), p2 = path(sqs[(i + 3) % 6], to, "", 0);
    if (p1.length() <= p2.length()) return ((p1[0] - '0') + 2) % 4;
    else return (p2[0] - '0');
}

int localDir(pair<int, int> tar, int global) {
    int i = getSq(tar);
    string p1 = path(tar, sqs[0], "", 0), p2 = path(sqs[3], tar, "", 0);
    int U;
    if (p1.length() == p2.length() || i == 0 || i == 3) U = 0;
    else if (p1.length() < p2.length()) U = 3 - (p1[0] - '0');
    else U = 3 - (p2[0] - '0');
    return (global + U) % 4;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);

    ifstream infile("input.txt");
    string line;

    vector<vector<int>> grid(N, vector<int>(N, 0)), vis(N, vector<int>(N, 0));
    vector<string> steps;
    vector<pair<int, int>> horz(N, {1e9, 0}), vert(N, {1e9, 0});

    int i = 0, n = 0, m = 0;
    pair<int, int> pos = {0, 1e9};
    bool done = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        if (line.empty()) done = true;
        else if (done) {
            string temp;
            for (int j = 0; j < line.length(); ++j) {
                if (j == line.length() - 1) {
                        temp.push_back(line[j]);
                        steps.push_back(temp);
                        break;
                }
                else if (line[j] == 'L' || line[j] == 'R') {
                    steps.push_back(temp);
                    temp = {line[j]};
                    steps.push_back(temp);
                    temp = "";
                }
                else temp.push_back(line[j]);
            }
            n = i;
        }
        else {
            m = max(m, (int)line.length());
            for (int j = 0; j < line.length(); ++j) {
                if (line[j] == '.') {
                    if (!i) pos.second = min(pos.second, j);
                    grid[i][j] = 1;
                }
                else if (line[j] == '#') grid[i][j] = -1;

                if (line[j] != ' ') {
                    horz[i].first = min(horz[i].first, j);
                    horz[i].second = max(horz[i].second, j);
                    vert[j].first = min(vert[j].first, i);
                    vert[j].second = max(vert[j].second, i);
                }
            }
            i++;
        }
    }
    SIZE = __gcd(n, m);

    // number off squares
    set<pair<int, int>> used;
    for (int i = 0; i < n/SIZE; ++i) {
        for (int j = 0; j < m/SIZE; ++j) {
            if (grid[i*SIZE][j*SIZE] == 0) continue;
            valid.push_back({i, j});
            if (valid.size() == 1) {
                sqs.push_back(valid[0]);
                used.insert(valid[0]);
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        pair<int, int> v = valid[i];
        if (v != sqs[0] && abs(sqs[0].first - v.first) <= 1 && abs(sqs[0].second - v.second) <= 1) {
            sqs.push_back(v);
            used.insert(v);
        }
    }
    sqs.resize(6);
    for (auto v : valid) {
        if (used.count(v)) continue;
        for (int i = 0; i < 3; ++i) {
            int dy = abs(sqs[i].first - v.first), dx = abs(sqs[i].second - v.second);
            // cout << dx << "   " << dy << "\n";
            if ((!dy && dx == 2) || (!dx && dy == 2)) sqs[i + 3] = v;
            else if (max(dx, dy) == 2 && min(dx, dy) == 1) {
                string s = path(v, sqs[i], "", 0);
                if (s[0] == s[2]) {
                    sqs[i + 3] = v; 
                }   
            }
            else if (max(dx, dy) == 2 && min(dx, dy) == 2) {
                string s = path(v, sqs[i], "", 0);
                if (s[0] == s[3] && s[1] == s[2]) {
                    sqs[i + 3] = v; 
                }
            }
        }
    }
    if (sqs[1].second - sqs[0].second < 0) swap(sqs[1], sqs[4]);

    for (auto s : steps) {
        if (s == "L") {
            FACING = (((FACING - 1) % 4) + 4) % 4;
        }
        else if (s == "R") {
            FACING = (FACING + 1) % 4;
        }
        else {
            int steps = stoi(s);
            while (steps--) {
                vis[pos.first][pos.second] = 1;
                pair<int, int> next = {pos.first + D[FACING].first, pos.second + D[FACING].second};
                pair<int, int> sq = {pos.first/SIZE, pos.second/SIZE}, y = {next.first/SIZE, next.second/SIZE};
                if (sq != y || next.first < 0 || next.second < 0) {
                    pair<int, int> nsq = sqs[adj[getSq(sq)][localDir(sq, FACING)]];
                    int dir = calcDir(sq, nsq); 

                    int lDist;
                    if (FACING % 2) {
                        lDist = pos.second;
                        if (sq.second) lDist %= (sq.second * SIZE);
                    }
                    else {
                        lDist = pos.first;
                        if (sq.first) lDist %= (sq.first * SIZE);
                    }
                    if (FACING == 1 || FACING == 2) lDist = SIZE - 1 - lDist; 

                    next = {nsq.first*SIZE, nsq.second*SIZE};
                    if (dir == 0) next.second += SIZE - 1;
                    else if (dir == 1) next.first += SIZE - 1;

                    // dir == side entering from
                    if (dir == 1) next.second += lDist;
                    else if (dir == 2) next.first += lDist;
                    else if (dir == 0) next.first += SIZE - lDist - 1;
                    else next.second += SIZE - lDist - 1;

                    if (grid[next.first][next.second] == -1) break;
                    FACING = (dir + 2) % 4;
                }
                if (grid[next.first][next.second] == -1) break;
                pos = next;
            }

        }
    }

    cout << 1000*(pos.first + 1) + 4*(pos.second + 1) + FACING << "\n";
}

