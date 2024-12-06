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

    auto next_obstacle = [&g, inside](array<int, 3> pos) -> bool {
        switch(pos[2]) {
            case 0: {pos[0]--; break;}
            case 2: {pos[0]++; break;}
            case 3: {pos[1]--; break;}
            case 1: {pos[1]++; break;}
            default: assert(false);
        }
        if(inside(pos[0], pos[1]) && g[pos[0]][pos[1]] == '#')
            return true;
        return false;
    };

    auto does_loop = [inside, next_obstacle, n, m, &g](array<int, 3> pos) {
        set<array<int, 3>> visited;
        visited.insert(pos);
        // auto pos = curr;
        while(inside(pos[0], pos[1])) {
            // turn if next is obstacle
            while(next_obstacle(pos)) {
                switch(pos[2]) {
                    case 0:
                    case 1:
                    case 2:
                    {
                        pos[2] = pos[2] + 1;
                        break;
                    }
                    case 3: {
                        pos[2] = 0;
                        break;
                    }
                    default: assert(false);
                }
            }

            // go forward
            switch(pos[2]) {
                case 0: {pos[0]--; break;}
                case 2: {pos[0]++; break;}
                case 3: {pos[1]--; break;}
                case 1: {pos[1]++; break;}
                default: assert(false);
            }
            if(visited.count(pos))
                return true;
            visited.insert(pos);
        }
        return false;
    };

    // cout << does_loop(curr) << endl;;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] != '#' && g[i][j] != '^') {
                assert(g[i][j] == '.');
                g[i][j] = '#';

                if(does_loop(curr)) {
                    // printf("loops %d, %d\n", i, j);
                    ans += 1;
                }

                g[i][j] = '.';
            }
        }
        cout << (((double)i / n) * 100.) << "% completed" << endl;
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
