#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;
using ll = long long;

void print_grid(const vector<vector<char>>& g) {
    for(auto& row : g) {
        for(auto& cell : row) {
            cout << (char)cell;
        }
        cout << endl;
    }

    cout << endl;
}

array<array<int, 2>, 4> dirs = {
    array<int, 2>{-1, 0},
    array<int, 2>{0, 1},
    array<int, 2>{1, 0},
    array<int, 2>{0, -1}};

int bfs(const vector<vector<char>>& g) {
    int n = g.size();
    vector<vector<int>> visited(n, vector<int>(n, 0));
    queue<array<int, 2>> q;
    q.push({0, 0});
    visited[0][0] = true;
    int level = 0;
    while(!q.empty()) {
        queue<array<int, 2>> nq;
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            if(curr[0] == n - 1 && curr[1] == n - 1)
                return level;

            for(int i = 0; i < 4; i++) {
                int nx = curr[0] + dirs[i][0], ny = curr[1] + dirs[i][1];
                if(nx >= 0 && nx < n && ny >= 0 && ny < n && g[nx][ny] != '#' && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    nq.push({nx, ny});
                }
            }
        }
        level++;
        q = nq;
    }

    assert(false);
    return -1;
}

void solve() {
    bool small_test = false;
    int n = small_test ? 7 : 71;
    vector<vector<char>> g(n, vector<char>(n, '.'));
    vector<array<int, 2>> block;
    string tmp;
    while(getline(cin, tmp)) {
        int x = atoi(tmp.c_str());
        int y = atoi(tmp.c_str() + tmp.find(',') + 1);
        block.push_back({x, y});
    }

    int blocks_to_consider = small_test ? 12 : 1024;
    for(int i = 0; i < blocks_to_consider; i++) {
        g[block[i][1]][block[i][0]] = '#';
    }

    // print_grid(g);
    cout << "Ans: " << bfs(g) << endl;
}

int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);
  int t = 1;
#if 0
    scanf("%d", &t);
#endif
  while (t--)
    solve();
}
