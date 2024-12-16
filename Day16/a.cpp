#include <cassert>
#include <cstdio>
#include <iostream>

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
    priority_queue<pair<ll, array<int, 3>>, vector<pair<ll, array<int, 3>>>, greater<pair<ll, array<int, 3>>>> q;
    vector<vector<int>> visited(n, vector<int>(m, 0));
    vector<vector<ll>> dist(n, vector<ll>(m, INF));
    for(int i = 0; i < 3; i++) {
        q.push({1000, array<int, 3>{src.x, src.y, (2 + i) % 4}});
    }
    q.push({0, array<int, 3>{src.x, src.y, 1}});
    dist[src.x][src.y] = 0;

    ll final_cost = INF;
    while(!q.empty()) {
        ll cost = q.top().first;
        array<int, 3> pos = q.top().second;
        q.pop();
        if(pos[0] == dest.x && pos[1] == dest.y) {
            final_cost = min(final_cost, cost);
            continue;
        }

        // printf("%d, %d, %c = %lld\n", pos[0], pos[1], "NESW"[pos[2]], cost);

        // with 1000 move to next 3 directions
        // move forward
        array<int, 3> nextt = {pos[0] + dirs[pos[2]].x, pos[1] + dirs[pos[2]].y, pos[2]};
        if(inside(nextt[0], nextt[1]) && g[nextt[0]][nextt[1]] != '#' && dist[nextt[0]][nextt[1]] > cost + 1) {
            for(int i = 0; i < 3; i++) {
                q.push({cost + 1000 + 1, array<int, 3>{nextt[0], nextt[1], (pos[2] + i + 1) % 4}});
            }
            dist[nextt[0]][nextt[1]] = cost + 1;
            q.push({cost + 1, nextt});
        }
    }

    cout << "Ans: " << final_cost << endl;
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
