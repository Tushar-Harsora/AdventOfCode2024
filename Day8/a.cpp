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

struct Point {
public:
    int x, y;
    Point(int x, int y): x(x), y(y) {}

    bool isin(int n, int m) {
        return x >= 0 && x < n && y >= 0 && y < m;
    }
    Point operator-(const Point& other) {
        return {this->x - other.x, this->y - other.y};
    }
    Point operator+(const Point& other) {
        return {this->x + other.x, this->y + other.y};
    }
    bool operator<(const Point& other) const {
        return this->x == other.x ? this->y < other.y : this->x < other.x;
    }
};

void solve() {
    ll ans = 0;
    vector<string> g;
    map<char, vector<Point>> towers;
    set<Point> antinodes;
    string tmp;
    while(cin >> tmp) {
        g.push_back(tmp);
    }
    int n = g.size(), m = g[0].size();

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] != '.') {
                towers[g[i][j]].emplace_back(i, j);
            }
        }
    }

    for(auto pr : towers) {
        char id = pr.first;
        vector<Point>& pos = pr.second;
        // printf("id: %c, points: %zu\n", id, pos.size());

        for(int i = 0; i < pos.size(); i++) {
            for(int j = i + 1; j < pos.size(); j++) {
                Point diff = pos[i] - pos[j];
                Point first = pos[i] + diff;
                Point second = pos[j] - diff;

                // printf("For pair: %d, %d x %d, %d == diff: %d, %d\n", pos[i].x, pos[i].y, pos[j].x, pos[j].y,
                    // diff.x, diff.y);
                if(first.isin(n, m)) {
                    // printf("    Adding1 %d, %d\n", first.x, first.y);
                    antinodes.insert(first);
                }
                if(second.isin(n, m)) {
                    // printf("    Adding2 %d, %d\n", second.x, second.y);

                    antinodes.insert(second);
                }
            }
        }
    }

    cout << antinodes.size() << endl;
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
