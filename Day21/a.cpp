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

vector<vector<int>> positions = {
    {1, 3},
    {0, 2},
    {1, 2},
    {2, 2},
    {0, 1},
    {1, 1},
    {2, 1},
    {0, 0},
    {1, 0},
    {2, 0},
    {2, 3},
};

string get_first_robot(string& in) {
    string ret;
    array<int, 2> pos = {2, 3};
    // perform all right moves first
    // also perform all up moves first
    for(int i = 0; i < in.size(); i++) {
        int lookup = in[i] == 'A' ? 10 : in[i] - '0';
        int dx = positions[lookup][0] - pos[0];
        int dy = positions[lookup][1] - pos[1];
        // printf("dx: %d, dy: %d\n", dx, dy);
        if(dx < 0) {
            if(pos[1] != 3) {
                ret += string(-dx, '<');
                dx = 0;
            }
        }
        if(dy < 0) {
            // cout << "B" << endl;;
            // cout << string(-dy, '<') << endl;
            ret += string(-dy, '^');
        }
        if(dy > 0) {
            // cout << "C" << endl;;
            ret += string(dy, 'v');
        }
        if(dx < 0) {
            // cout << "C" << endl;;
            ret += string(-dx, '<');
        }
        if(dx > 0) {
            // cout << "A" << endl;
            ret += string(dx, '>');
        }
        ret.push_back('A');
        pos = {positions[lookup][0], positions[lookup][1]};
    }

    return ret;
}

array<int, 2> get_pos_second_board(char ch) {
    switch(ch) {
        case '^': return {1, 0};
        case 'A': return {2, 0};
        case '<': return {0, 1};
        case 'v': return {1, 1};
        case '>': return {2, 1};
    }

    assert(false);
    return {-1, -1};
}

string second_robot(string in) {
    string ret;
    array<int, 2> pos = get_pos_second_board('A');
    for(int i = 0; i < in.size(); i++) {
        auto dest = get_pos_second_board(in[i]);
        int dx = dest[0] - pos[0];
        int dy = dest[1] - pos[1];

        // to to right and down first if possible
        if(dx > 0) {
            ret += string(dx, '>');
        }
        if(dy > 0) {
            ret += string(dy, 'v');
        }
        if(dx < 0) {
            ret += string(-dx, '<');
        }
        if(dy < 0) {
            ret += string(-dy, '^');
        }
        ret.push_back('A');
        pos = dest;
    }

    return ret;
}

// 141424
void solve() {
    ll ans = 0;

    vector<string> commands;
    string tmp;
    while(cin >> tmp) {
        commands.push_back(tmp);
    }

    for(int z = 0; z < commands.size(); z++) {
        string in = commands[z];
        ll num = stoi(in);
        string steps = get_first_robot(in);
        string steps2 = second_robot(steps);
        string steps3 = second_robot(steps2);
        cout << steps3 << endl;
        cout << steps2 << endl;
        cout << steps << endl;
        cout << in << endl;
        cout << endl;
        cout << in << ": " << steps3 << endl;
        printf("%lld * %zu = %lld\n", num, steps3.size(), num * steps3.size());
        ans += num * steps3.size();
    }

    cout << "Ans: " << ans << endl;
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
