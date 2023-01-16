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

    vector<vector<string>> adj;
    vector<ll> p;
    map<string, int> idxs;

    int c = 0, cnt = 0, start = 0;
    while (getline(infile, line)) {
        istringstream iss(line);
        vector<string> lines;
        string s;
        while (iss >> s) {
            lines.push_back(s);
        }

        vector<string> v;
        for (int i = 2; i < lines.size(); ++i) {
            v.push_back(lines[i]);
        }

        adj.push_back(v);
        p.push_back(stoi(lines[1]));
        idxs.insert({lines[0], c});
        if (lines[0] == "AA") start = c;
        c++;
    }

    vector<int> nonzeros(p.size(), -1);
    int nzcnt = 0;
    for (int i = 0; i < p.size(); ++i) {
        if (p[i] == 0) continue;
        nonzeros[i] = nzcnt;
        nzcnt++;
    }

    int N = 27, M = idxs.size(), L = (1LL << nzcnt);
    
    vector<vector<vector<ll>>> dp(N, vector<vector<ll>>(M, vector<ll>(L, -1LL)));
    dp[0][start][0] = 0LL;

    for (int i = 0; i < N - 1; ++i) {
        for (int k = 0; k < L; ++k) {
            for (int j = 0; j < M; ++j) {
                if (dp[i][j][k] == -1) continue;

                // move to another valve
                for (auto a : adj[j]) {
                    dp[i + 1][idxs[a]][k] = max(dp[i][j][k], dp[i + 1][idxs[a]][k]);
                }

                // open valve
                int pos = nonzeros[j];
                if (pos == -1LL || (k & (1LL << pos))) continue;

                // bitmask to represent opened valves
                int newK = k | (1LL << pos);
                dp[i + 1][j][newK] = max(dp[i + 1][j][newK], dp[i][j][k] + p[j] * (N - 2LL - i));
            }
        }
    }

    vector<ll> a(L, 0LL);
    for (int k = 0; k < L; ++k) {
        for (int j = 0; j < M; ++j) {
            a[k] = max(a[k], dp[N - 1][j][k]);
        }
    }

    ll ans = 0;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            if (i & j) continue;
            ans = max(ans, a[i] + a[j]);
        }
    }
    cout << ans << "\n";
}