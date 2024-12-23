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

bool find_fcc(map<int, set<int>>& graph, set<int>& included, int target_len, int index) {
    if(included.size() == target_len) {
        return true;
    }

    for(int neigh : graph[index]) {
        if(included.count(neigh) == 0) {
            bool good = true;
            for(int node : included) {
                good &= (graph[node].count(neigh) == 1);
            }
            if(!good)
                continue;
            included.insert(neigh);
            if(find_fcc(graph, included, target_len, neigh))
                return true;
            included.erase(neigh);
        }
    }

    return false;
}

void BronKerbosch(map<int, set<int>>& graph, set<int>& ans, const set<int> all_nodes,
                    set<int>& R, set<int>& P, set<int>& X) {
    if(P.size() == 0 && X.size() == 0) {
        if(R.size() > ans.size())
            ans = R;
        return;
    }

    for(auto it = P.begin(); it != P.end(); ) {
        int vertex = *it;
        set<int> newP;
        set<int> newX;
        for(auto node : graph[vertex]) {
            if(P.count(node))
                newP.insert(node);
        }
        for(auto node : graph[vertex]) {
            if(X.count(node))
                newX.insert(node);
        }

        R.insert(vertex);
        BronKerbosch(graph, ans, all_nodes, R, newP, newX);
        R.erase(vertex);

        it = P.erase(it);
        X.insert(vertex);
    }
}

bool verify_fully_connected(map<int, set<int>>& graph, set<int>& nodes) {
    bool good = true;
    for(int src : nodes) {
        for(int dest : nodes) {
            if(src == dest)
                continue;
            good &= (graph[src].count(dest) == 1 && graph[dest].count(src) == 1);
        }
    }

    return good;
}

void print_ans(const set<string>& ans) {
    cout << "Ans: ";
    for(auto computer : ans)
        cout << computer << ",";
    cout << endl;
}

void solve() {
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

    set<int> ans;
    set<int> all_vertices;
    for(auto it : graph)
        all_vertices.insert(it.first);
    set<int> R, P, X;
    for(auto& it : graph)
        P.insert(it.first);
    BronKerbosch(graph, ans, all_vertices, R, P, X);

    set<string> connected_nodes;
    for(int node : ans) {
        connected_nodes.insert(pcs[node]);
    }
    cout << "Ans: ";
    for(string node : connected_nodes) {
        cout << node << ",";
    }
    cout << endl;
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
