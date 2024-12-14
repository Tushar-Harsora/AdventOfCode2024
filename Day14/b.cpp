#include <algorithm>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <thread>
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

bool has_robot(const vector<Robot>& robots, int i, int j) {
    for(Robot r : robots) {
        if(r.pos.x == i && r.pos.y == j)
            return true;
    }
    return false;
};

void print_grid(vector<Robot>& robots, int n, int m) {
    /* Debug */
    // int rc = 0;
    printf("\033[0;0H\033[2J");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            bool exists = has_robot(robots, i, j);
            cout << ".X"[exists];
        }
        cout << endl;
    }
}

int robots_in_radius(const vector<Robot>& robots, int x, int y, int radius) {
    int ret = 0;
    for(const Robot& r : robots) {
        bool closer = (r.pos.x - x < radius && r.pos.x - x > -radius) && (r.pos.y - y < radius && r.pos.y - y > -radius);
        ret += closer;
    }

    return ret;
}

void print_to_file(const vector<Robot>& robots, int n, int m, int move) {
    ofstream of("images/Move"+to_string(move)+".bmp");
    assert(of.is_open());
    //  size to be filled later
    uint8_t bmp_header[] = {0x42, 0x4d,
        132, 122, 0, 0,  // size of file (with header)
        0, 0,           // Unused
        0, 0,           // Unused
        0x36, 0, 0, 0   // offset where color data is started 0x36=54
    };
    // of << bmp_header;
    uint8_t dib_header[] = {
        0x28, 0, 0, 0,      // dib_header_size
        101, 0, 0, 0,       // image width
        103, 0, 0, 0,       // image height
        1, 0,               // 1 color plane
        24, 0,              // 24 bit color (3 * BPP)
        0, 0, 0, 0,         // no compression
        240, 119, 0, 0,     // raw image data size including padding
        0x13, 0x0b, 0, 0,   // print image resolution
        0x13, 0x0b, 0, 0,   // print image resolution
        0, 0, 0, 0,         // 0 colors in palette
        0, 0, 0, 0,         // 0 means all colors are important
    };

    for(auto b : bmp_header)
        of << b;
    for(auto b : dib_header)
        of << b;

    uint8_t black[] = {0, 0, 0};
    uint8_t white[] = {0xFF, 0xFF, 0xFF};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(has_robot(robots, i, j)) {
                of << black[0] << black[1] << black[2];
            } else {
                of << white[0] << white[1] << white[2];
            }
        }
        // 1 byte padding to make 101 columns * 3 bytes multiple of 4
        of << (uint8_t)0;
    }

    of.close();
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
    ll moves = 1'00'000;
    ll max_till_now = 0, max_ind = 0;
    for(int x = 0; x < moves; x++) {
        for(Robot& r : robots) {
            r.pos.x = (n + r.pos.x + (r.velocity.x % n)) % n;
            r.pos.y = (m + r.pos.y + (r.velocity.y % m)) % m;
        }

        int nrobos = robots_in_radius(robots, n / 2, m / 2, 20);
        if(nrobos > max_till_now) {
            max_till_now = nrobos;
            max_ind = x;
            print_to_file(robots, n, m, x);
            printf("%d robots in 20 radius after %d moves\n", nrobos, x + 1);
        }
    }
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
