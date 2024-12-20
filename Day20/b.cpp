#include <cassert>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;
using ll = long long;

vector<array<int, 2>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// 939823 < ans < 1070147
void solve() {
    int ans = 0;
    vector<string> g;
    string tmp;
    array<int, 2> start, end;
    int n = 0, m = 0;
    while(cin >> tmp) {
        g.push_back(tmp);
        m = tmp.size();
        for(int i = 0; i < tmp.size(); i++){
            if(tmp[i] == 'S') {
                start = {n, i};
            } else if(tmp[i] == 'E') {
                end = {n, i};
            }
        }

        n++;
    }

    auto isin = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    const ll INF = 1000000000 + 5;
    vector<vector<ll>> dist(n, vector<ll>(m, INF));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<array<int, 2>> q;
    q.push({start[0], start[1]});
    visited[start[0]][start[1]] = true;
    dist[start[0]][start[1]] = 0;

    ll level = 0;
    while(!q.empty()) {
        queue<array<int, 2>> nq;
        while(!q.empty()) {
            auto curr = q.front();
            dist[curr[0]][curr[1]] = level;
            q.pop();

            for(int i = 0; i < 4; i++) {
                int nx = curr[0] + dirs[i][0], ny = curr[1] + dirs[i][1];
                if(isin(nx, ny) && g[nx][ny] != '#' && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    nq.push({nx, ny});
                }
            }
        }
        q = nq;
        level++;
    }

    array<ll, 10000> cheats = {0};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == '#')
                continue;

            // start should be '.' and end should also be '.'
            // vector<ll> neighs;
            for(int dx = -20; dx <= 20; dx++) {
                for(int dy = -20; dy <= 20; dy++) {
                    if(abs(dx) + abs(dy) <= 20) {
                        int nx = i + dx, ny = j + dy;
                        if(isin(nx, ny) && g[nx][ny] != '#') {
                            assert(dist[nx][ny] != INF);
                            if(dist[i][j] < dist[nx][ny]) {
                                ll save = dist[nx][ny] - (dist[i][j] + (abs(dx) + abs(dy)));
                                cheats[save]++;
                            }
                        }
                    }
                }
            }
        }
    }

    for(int i = 100; i < cheats.size(); i++) {
        ans += cheats[i];
    }

    cout << "Ans: " << ans << endl;
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
