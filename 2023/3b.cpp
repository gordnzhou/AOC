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

    //140
    int lines = 140;

    vector<vector<char> > grid;
    while (lines--) {
    	string line;
    	cin >> line;
        string cur = "";
        vector<char> row;
        for (int i = 0; i < line.length(); ++i) {
        	row.push_back(line[i]);
        }
        grid.push_back(row);
    }

    int w = grid[0].size(), h = grid.size();
    vector<vector<int> > vals(h, vector<int>(w, 0));
    for (int i = 0; i < h; ++i) {
    	for (int j = 0; j < w; ++j) {
    		if (isdigit(grid[i][j])) {
    			string cur = "", cur0 = "";

    			int x = j, y = j - 1;
    			while (y >= 0 && isdigit(grid[i][y])) {
    				cur0.push_back(grid[i][y]);
    				y--;
    			}
    			while (x < w && isdigit(grid[i][x])) {
    				cur.push_back(grid[i][x]);
    				x++;
    				j++;
    			}
    			j--;
    			reverse(cur0.begin(), cur0.end());
    			int num = stoi(cur0 + cur);
    			for (int k = y + 1; k < x; ++k) {
    				vals[i][k] = num;
    			}
    		}
    	}
    }

    int ans = 0;

    for (int i = 0; i < h; ++i) {
    	for (int j = 0; j < w; ++j) {
 
    		if (grid[i][j] == '*') {
    			vector<int> adj;
    			for (int k = 0; k < 3; ++k) {
    				for (int l = 0; l < 3; ++l) {
    					int lr = j + l - 1, ud = i + k - 1;
    					if (0 <= lr && lr < w && 0 <= ud && ud < h) {
    						if (isdigit(grid[ud][lr]) && 
    							find(adj.begin(), adj.end(), vals[ud][lr]) == 
    								adj.end()) {
    							adj.push_back(vals[ud][lr]);
    						}
    					}
    				}
    			}
    			if (adj.size() == 2) {
    				ans += adj[0] * adj[1];
    			}
    		}
    	}
    }

    cout << ans << "\n";
}