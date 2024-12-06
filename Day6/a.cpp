#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;
using ll = long long;

void solve() {
    ll ans = 0;
    int i = 0;
    set<array<int, 3>> visited;
    array<int, 3> curr;
    vector<string> g;
    string x, next_s = "URDL";
    while(cin >> x) {
        g.push_back(x);
        for(int j = 0; j < x.size(); j++)
            if(x[j] == '^') {
                curr = {i, j, 0};
            }
        i++;
    }
    int n = g.size(), m = g[0].size();
    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    while(true) {
        // Mark current position
        // cout << curr[0] << " " << curr[1] << " " << curr[2] << " " << next_s[curr[2]] << endl;
        g[curr[0]][curr[1]] = 'X';
        switch(curr[2]) {
            case 0: {curr[0]--; break;}
            case 2: {curr[0]++; break;}
            case 3: {curr[1]--; break;}
            case 1: {curr[1]++; break;}
            default: assert(false);
        }
        if(!inside(curr[0], curr[1])) {
            break;
        }
        if(visited.count(curr)) {
            break;
        }

        visited.insert(curr);
        switch(curr[2]) {
            case 0: {
                if(curr[0] - 1 >= 0 && g[curr[0] - 1][curr[1]] == '#')
                    curr[2] = curr[2] + 1;
                break;
            }
            case 2: {
                if(curr[0] + 1 < n && g[curr[0] + 1][curr[1]] == '#')
                    curr[2] = curr[2] + 1;
                break;
            }
            case 3: {
                if(curr[1] - 1 >= 0 && g[curr[0]][curr[1] - 1] == '#')
                    curr[2] = (curr[2] + 1) % 4;
                break;
            }
            case 1: {
                if(curr[1] + 1 < m && g[curr[0]][curr[1] + 1] == '#')
                    curr[2] = curr[2] + 1;
                break;
            }
            default: assert(false);
        }
        visited.insert(curr);

    }
    for(auto& row : g) {
        for(auto cell : row) {
            ans += cell == 'X';
        }
    }
    cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
#if 0
    scanf("%d", &t);
#endif
  while (t--)
    solve();
}
