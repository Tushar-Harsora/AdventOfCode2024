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
    int x, y;
    vector<vector<int>> queries;
    map<int, vector<int>> g;
    char buffer[1024];
    // Input is read by chatgpt
    int reading_pairs = 1; // Flag to determine if we're reading pairs or groups
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = 0;

        if (reading_pairs) {
            // Process pairs
            if (strchr(buffer, '|')) {
                int a, b;
                if (sscanf(buffer, "%d|%d", &a, &b) == 2) {
                    g[a].push_back(b);
                }
            } else {
                // Switch to reading groups if no '|' is found
                reading_pairs = 0;
            }
        }

        vector<int> query;
        if (!reading_pairs) {
            // Process groups
            char *token = strtok(buffer, ",");
            while (token) {
                query.push_back(atoi(token));
                token = strtok(NULL, ",");
            }

            // Store the group
            queries.push_back(query);
        }
    }

    ll ans = 0;
    for(auto& q : queries) {
        set<int> seen;
        bool good = true;
        for(int i = 0; i < q.size(); i++) {
            auto it = g.find(q[i]);
            if(it == g.end()) {
                seen.insert(q[i]);
                continue;
            }
            for(int dependents : it->second) {
                good &= (seen.find(dependents) == seen.end());
            }
            seen.insert(q[i]);
        }

        if(good) {
            // assert(q.size() % 2 == 1);
            cout << q[q.size() / 2] << endl;
            ans += q[q.size() / 2];
        }
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
