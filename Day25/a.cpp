#include <cassert>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

// Function to convert a block of strings into an array<int, 5>
array<int, 5> convertBlock(const vector<string>& block) {
    array<int, 5> arr = {0, 0, 0, 0, 0};
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (block[i][j] != '.')
                arr[j]++;
        }
    }
    return arr;
}


void solve() {
    ll ans = 0;

    vector<array<int, 5>> lock, key;
    vector<string> block(7);  // 7 lines per block
    string line;

    while (getline(cin, line)) {
        if(line.size() == 0)
            continue;
        block[0] = line;
        for (int i = 1; i < 7; ++i) {
            getline(cin, block[i]);
        }

        // Convert the block to an array<int, 5>
        array<int, 5> arr = convertBlock(block);

        if (block[0] == "#####") {
            lock.push_back(arr);
        } else if (block[6] == "#####") {
            key.push_back(arr);
        }
    }

    cout << "Locks: " << lock.size() << endl;
    cout << "Keys: " << key.size() << endl;

    for(int i = 0; i < lock.size(); i++) {
        for(int j = 0; j < key.size(); j++) {
            bool good = true;
            for(int k = 0; k < 5; k++) {
                good &= (lock[i][k] + key[j][k] <= 6);
            }
            ans += good;
        }
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
