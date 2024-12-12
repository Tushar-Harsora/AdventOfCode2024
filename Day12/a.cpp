#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
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

bool isin(int i, int j, int n, int m) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

void dfs(const vector<string>& g, vector<vector<int>>& cover, int i, int j, int island) {
    // cout << "    " << i << " " << j << endl;
    for(int x = 0; x < 4; x++) {
        int nx = i + dx[x], ny = j + dy[x];
        if(nx >= 0 && nx < g.size() && ny >= 0 && ny < g[0].size() && g[nx][ny] == g[i][j] && cover[nx][ny] == -1) {
            cover[nx][ny] = island;
            dfs(g, cover, nx, ny, island);
        }
    }
}

// Returns: perimeter: Perimeter of blocks
//          n_plants: number of plant in blocks
pair<ll, ll> dfs2(vector<vector<int>>& cover, vector<vector<bool>>& visited, const int i, const int j, int edge_delta = 0) {
    int my_num = cover[i][j];
    ll my_peri = 0;
    ll n_plants = 1;        // me
    int n = cover.size(), m = cover[0].size();
    for(int x = 0; x < 4; x++) {
        int nx = i + dx[x], ny = j + dy[x];
        if(nx >= 0 && nx < cover.size() && ny >= 0 && ny < cover[0].size()) {
            my_peri += cover[nx][ny] != my_num;
        } else {
            my_peri += 1;
        }
    }

    for(int x = 0; x < 4; x++) {
        int nx = i + dx[x], ny = j + dy[x];
        if(nx >= 0 && nx < cover.size() && ny >= 0 && ny < cover[0].size() && cover[nx][ny] == my_num && !visited[nx][ny]) {
            visited[nx][ny] = true;
            auto ret = dfs2(cover, visited, nx, ny);
            my_peri += ret.first;
            n_plants += ret.second;
        }
    }

    return {my_peri, n_plants};
}

void solve() {
    ll ans = 0;
    string tmp;
    vector<string> g;
    while(cin >> tmp)
        g.push_back(tmp);

    int region = 1, n = g.size(), m = g[0].size();
    vector<vector<int>> cover(n, vector<int>(m, -1));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(cover[i][j] == -1) {
                // cout << "dfs1: " << i << " " << j << endl;
                cover[i][j] = region;
                dfs(g, cover, i, j, region);
                region++;
            }
        }
    }


    vector<vector<bool>> visited(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(!visited[i][j]) {
                visited[i][j] = true;
                auto [perimeter, n_plants] = dfs2(cover, visited, i, j);
                printf("A region of %c plants with price %lld * %lld = %lld.\n", g[i][j], n_plants, perimeter, perimeter * n_plants);
                ans += perimeter * n_plants;
            }
        }
    }



    cout << ans << endl;
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);
  int t = 1;
#if 0
    scanf("%d", &t);
#endif
  while (t--)
    solve();
}
