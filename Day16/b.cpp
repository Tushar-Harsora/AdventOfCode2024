#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>

using namespace std;
using ll = long long;
const ll INF = 1'00'00'00'000 + 7;

struct Vec2 {
    int x;
    int y;
    Vec2() = default;
    Vec2(int x, int y): x(x), y(y) {}

    Vec2 operator+(const Vec2& other) {
        return {this->x + other.x, this->y + other.y};
    }
    Vec2 operator-(const Vec2& other) {
        return {this->x - other.x, this->y - other.y};
    }
};

bool operator==(const Vec2& lhs, const Vec2& other) {
    return lhs.x == other.x && lhs.y == other.y;
}

vector<Vec2> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void solve() {
    vector<string> g;
    string tmp;
    int n = 0, m = 0;
    Vec2 dest;
    Vec2 src;
    while(getline(cin, tmp)) {
        if(tmp == "")
            break;
        g.push_back(tmp);
        m = tmp.size();
        for(int i = 0; i < m; i++) {
            if(tmp[i] == 'S') {
                src = {n, i};
            } else if(tmp[i] == 'E') {
                dest = {n, i};
            }
        }
        n++;
    }

    auto inside = [&](int x, int y) -> bool {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    assert(n == g.size() && m == g[0].size());
    auto comparator = [](const vector<pair<ll, array<int, 3>>>& lhs, const vector<pair<ll, array<int, 3>>>& rhs) {
        return lhs.back().first > rhs.back().first;
    };
    priority_queue<vector<pair<ll, array<int, 3>>>, vector<vector<pair<ll, array<int, 3>>>>, decltype(comparator)> q;
    // vector<vector<int>> visited(n, vector<int>(m, 0));
    vector<vector<array<int, 4>>> dist(n, vector<array<int, 4>>(m, {INF, INF, INF, INF}));
    for(int i = 0; i < 3; i++) {
        q.push({{1000, array<int, 3>{src.x, src.y, (2 + i) % 4}}});
        dist[src.x][src.y][(2 + i) % 4] = 1000;
    }
    q.push({{0, array<int, 3>{src.x, src.y, 1}}});
    dist[src.x][src.y][1] = 0;

    set<array<int, 2>> seen;
    ll min_cost = INF;
    while(!q.empty()) {
        auto curr_path = q.top();
        ll cost = curr_path.back().first;
        array<int, 3> pos = curr_path.back().second;
        q.pop();

        if(pos[0] == dest.x && pos[1] == dest.y) {
            if(cost <= min_cost) {
                min_cost = cost;

                // cout << "Path Weight: " << cost << " : ";
                for(auto& path : curr_path) {
                    // printf("(%d,%d) -> ", path.second[0], path.second[1]);
                    seen.insert({path.second[0], path.second[1]});
                }

                // cout << endl;
            } else {
                // cout << "Path with greater len " << cost << " found" << endl;
            }
            continue;
        }

        // printf("%d, %d, %c = %lld\n", pos[0], pos[1], "NESW"[pos[2]], cost);

        // with 1000 move to next 3 directions
        // move forward
        array<int, 3> nextt = {pos[0] + dirs[pos[2]].x, pos[1] + dirs[pos[2]].y, pos[2]};
        if(inside(nextt[0], nextt[1]) && g[nextt[0]][nextt[1]] != '#' && dist[nextt[0]][nextt[1]][nextt[2]] >= cost + 1) {
            auto new_path = curr_path;
            for(int i = 0; i < 3; i++) {
                if(nextt[0] == 11 && nextt[1] == 2) {
                    cout << pos[0] << " " << pos[1] << endl;
                }
                dist[nextt[0]][nextt[1]][(pos[2] + i + 1) % 4] = min<ll>(dist[nextt[0]][nextt[1]][(pos[2] + i + 1) % 4], cost + 1000 + 1);
                new_path.push_back({cost + 1000 + 1, array<int, 3>{nextt[0], nextt[1], (pos[2] + i + 1) % 4}});
                q.push(new_path);
                new_path.pop_back();
                // q.push({cost + 1000 + 1, array<int, 3>{nextt[0], nextt[1], (pos[2] + i + 1) % 4}});
            }
            assert(new_path == curr_path);
            dist[nextt[0]][nextt[1]][nextt[2]] = cost + 1;
            new_path.push_back({cost + 1, nextt});
            q.push(new_path);
        }
    }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         if(seen.count({i, j})) {
    //             cout << 'O';
    //         } else {
    //             cout << g[i][j];
    //         }
    //     }
    //     cout << endl;
    // }

    cout << "Ans: " << seen.size() << endl;
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
