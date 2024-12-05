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

    auto check_good = [&](const vector<int>& v) {
        set<int> seen;
        for(int i = 0; i < v.size(); i++) {
            auto it = g.find(v[i]);
            if(it == g.end()) {
                seen.insert(v[i]);
                continue;
            }
            for(int dependents : it->second) {
                if(seen.find(dependents) != seen.end())
                    return false;
            }
            seen.insert(v[i]);
        }
        return true;
    };

    ll ans = 0;
    for(auto& q : queries) {
        bool good = true;
        {
            set<int> seen;
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
            if(good)
                continue;
        }
        good = true;
        do{
            good = true;
            map<int, int> seen;
            for(int i = 0; i < q.size(); i++) {
                auto it = g.find(q[i]);
                if(it == g.end()) {
                    seen[q[i]] = i;
                    continue;
                }
                for(int dependents : it->second) {
                    auto it = seen.find(dependents);
                    if(it != seen.end()) {
                        swap(q[i], q[it->second]);
                        good = false;
                        break;
                    }
                }
                seen[q[i]] = i;
            }
        } while(!good);

        if(good) {

            // assert(q.size() % 2 == 1);
            // cout << q[q.size() / 2] << endl;
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
