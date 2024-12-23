#include <cassert>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

// Sorting networks TAOCP
void sort3(array<int, 3>& v) {
    if(v[0] > v[2])
        swap(v[0], v[2]);
    if(v[0] > v[1])
        swap(v[0], v[1]);
    if(v[1] > v[2])
        swap(v[1], v[2]);
}

void solve() {
    ll ans = 0;

    vector<string> pcs;
    map<int, set<int>> graph;

    string tmp;
    while(cin >> tmp) {
        string l = tmp.substr(0, tmp.find('-'));
        string r = tmp.substr(tmp.find('-') + 1);
        // cout << l << " - " << r << endl;

        if(find(pcs.begin(), pcs.end(), l) == pcs.end()) {
            pcs.push_back(l);
        }
        if(find(pcs.begin(), pcs.end(), r) == pcs.end()) {
            pcs.push_back(r);
        }
        auto lit = find(pcs.begin(), pcs.end(), l);
        auto rit = find(pcs.begin(), pcs.end(), r);

        int lind = distance(pcs.begin(), lit);
        int rind = distance(pcs.begin(), rit);
        graph[lind].insert(rind);
        graph[rind].insert(lind);
    }

    vector<vector<int>> g(graph.size());
    for(auto& pr : graph) {
        int key = pr.first;
        for(auto& val : pr.second) {
            g[key].push_back(val);
        }
    }

    int n = g.size();

    set<array<int, 3>> s;
    for(int i = 0; i < n; i++) {
        if(pcs[i][0] != 't')
            continue;

        for(int j = 0; j < g[i].size(); j++) {
            for(int k = j + 1; k < g[i].size(); k++) {
                int node1 = g[i][j], node2 = g[i][k];
                if(graph[node1].count(node2) == 0)
                    continue;
                // sort 3
                array<int, 3> cand = {i, node1, node2};
                sort3(cand);
                s.insert(cand);
            }
        }
    }

    cout << "Ans: " << s.size() << endl;
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
