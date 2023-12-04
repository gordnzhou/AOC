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
    vector<vector<bool> > good;
    for (int i = 0; i < h; ++i) {
    	vector<bool> row;
    	for (int j = 0; j < w; ++j) {
    		bool ok = false;
    		if (isdigit(grid[i][j])) {
    			for (int k = 0; k < 3; ++k) {
    				for (int l = 0; l < 3; ++l) {
    					int lr = j + l - 1, ud = i + k - 1;
    					if (0 <= lr && lr < w && 0 <= ud && ud < h) {
    						if (!isdigit(grid[ud][lr]) && grid[ud][lr] != '.') {
    							ok = true;
    						}
    					}
    				}
    			}
    		}
    		row.push_back(ok);
    	}
    	good.push_back(row);
    }

    int ans = 0;
    for (int i = 0; i < h; ++i) {
    	for (int j = 0; j < w; ++j) {
    		if (good[i][j]) {
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
    			ans += stoi(cur0 + cur);
    		}
    	}
    }
    cout << ans << "\n";
}