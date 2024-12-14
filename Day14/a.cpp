#include <algorithm>
#include <climits>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <cassert>

using namespace std;
using ll = long long;

struct Vec2 {
    int x;
    int y;
    Vec2(int x, int y): x(x), y(y) {}
};

struct Robot {
    Vec2 pos;
    Vec2 velocity;
    Robot(Vec2 pos, Vec2 velocity): pos(pos), velocity(velocity) {}
};

void print_grid(vector<Robot>& robots, int n, int m) {
    /* Debug */
    int rc = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            bool exists = [](vector<Robot>& robots, int i, int j) {
                for(Robot r : robots) {
                    if(r.pos.x == i && r.pos.y == j)
                        return true;
                }
                return false;
            }(robots, i, j);
            if(exists) {
                cout << (char)('A' + rc++);
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

void solve() {
    string line;
    ll ans = 1;
    // vector<vector<int>> g(7, vector<int>(11));
    ll n = 103, m = 101;
    vector<Robot> robots;
    while(true) {
        int x, y, vx, vy;
        int ret = scanf(" p=%d,%d v=%d,%d", &x, &y, &vx, &vy);

        if(ret == EOF)
            break;
        robots.push_back(Robot({y, x}, {vy, vx}));
    }

    // print_grid(robots, n, m);
    ll moves = 100;
    vector<ll> quadrants(4);
    for(Robot& r : robots) {
        r.pos.x = (n + r.pos.x + (r.velocity.x * moves % n)) % n;
        r.pos.y = (m + r.pos.y + (r.velocity.y * moves % m)) % m;

        int i = r.pos.x;
        int j = r.pos.y;
        if(i == n / 2 || j == m / 2)
            continue;
        int quadrant = 0;
        if(i > n / 2)
            quadrant += 2;
        if(j > m / 2)
            quadrant += 1;
        quadrants[quadrant]++;
    }

    // cout << endl;
    // print_grid(robots, n, m);

    for(int i = 0; i < 4; i++) {
        ans *= quadrants[i];
        printf("Q%d: %lld\n", i, quadrants[i]);
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
