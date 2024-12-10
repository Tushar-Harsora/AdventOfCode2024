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

array<int, 4> dx = {-1, 1, 0, 0};
array<int, 4> dy = {0, 0, -1, 1};
int dfs(const vector<vector<int>>&g, int i, int j) {
    if(g[i][j] == 9) {
        return 1;
    }

    int n = g.size(), m = g[0].size(), ret = 0;
    for(int x = 0; x < 4; x++) {
        int nx = i + dx[x], ny = j + dy[x];
        if(nx >= 0 && nx < n && ny >= 0 && ny < m && g[i][j] + 1 == g[nx][ny]) {
            ret += dfs(g, nx, ny);
        }
    }
    return ret;
}

void solve() {
    ll ans = 0;

    vector<vector<int>> g;
    string tmp;
    while(cin >> tmp) {
        vector<int> curr;
        for(char ch : tmp) {
            curr.push_back(ch - '0');
        }
        g.push_back(curr);
    }

    int n = g.size(), m = g[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == 0) {
                ans += dfs(g, i, j);
            }
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
