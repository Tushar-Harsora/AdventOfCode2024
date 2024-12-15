#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;
using ll = long long;

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

void print_grid(const vector<string>& g) {
    for(int i = 0; i < g.size(); i++) {
        for(int j = 0; j < g[i].size(); j++) {
            cout << g[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

vector<Vec2> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void do_operation(vector<string>& g, Vec2& robot, int dir_ind) {
    Vec2 curr_dir = dirs[dir_ind];
    Vec2 comp = dirs[(dir_ind + 2) % 4];
    Vec2 np = robot + curr_dir;
    if(g[np.x][np.y] == '#')
        return;
    while(g[np.x][np.y] == 'O') {
        np = np + curr_dir;
    }
    if(g[np.x][np.y] == '#')
        return;
    // printf("x=%d, y=%d\n", np.x, np.y);
    assert(g[np.x][np.y] == '.');
    // cout << "After assert" << endl;
    while(g[np.x + comp.x][np.y + comp.y] != '@') {
        // printf("swapping %d,%d <-> %d,%d\n", np.x, np.y, np.x + comp.x, np.y + comp.y); fflush(stdout);
        swap(g[np.x][np.y], g[np.x + comp.x][np.y + comp.y]);
        np = np + comp;
    }
    swap(g[np.x][np.y], g[np.x + comp.x][np.y + comp.y]);
    robot = np;
}

void solve() {
    vector<string> g;
    string tmp;
    int n = 0, m = 0;
    Vec2 robot;
    while(getline(cin, tmp)) {
        if(tmp == "")
            break;
        g.push_back(tmp);
        m = tmp.size();
        for(int i = 0; i < m; i++) {
            if(tmp[i] == '@') {
                robot = Vec2(n, i);
            }
        }
        n++;
    }

    auto inside = [&](const Vec2& point) -> bool {
        return point.x >= 0 && point.x < n && point.y >= 0 && point.y < m;
    };

    // assert(n == g.size() && m == g[0].size());
    char cd;
    while(scanf(" %c", &cd) != EOF) {
        // printf("%c robot: %d, %d\n", cd, robot.x, robot.y); fflush(stdout);
        switch(cd) {
            case '^': {
                do_operation(g, robot, 0);
                break;
            }
            case '>': {
                do_operation(g, robot, 1);
                break;
            }
            case 'v': {
                do_operation(g, robot, 2);
                break;
            }
            case '<': {
                do_operation(g, robot, 3);
                break;
            }
            default: {
                cout << "Wrong input" << endl;
                assert(false);
            }
        }
        // print_grid(g);
    }

    // print_grid(g);

    ll ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(g[i][j] == 'O') {
                ans += (100 * i) + j;
            }
        }
    }

    cout << "Ans: " << ans << endl;
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
