#include <cassert>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

struct Gate;
struct Gate {
    string name;
    char operand;
    int value;
    Gate* lhs;
    Gate* rhs;

    Gate(string name, char operand, Gate* lhs, Gate* rhs) : name(name), operand(operand), lhs(lhs), rhs(rhs) {
        value = -1;
    }
    Gate(string name, char operand, Gate* lhs, Gate* rhs, int value) : name(name), operand(operand), value(value), lhs(lhs), rhs(rhs) { }
};

void trim(string& s) {
    while(s.front() == ' ')
        s.erase(s.begin());
    while(s.back() == ' ')
        s.pop_back();
}

int find_value(Gate* node) {
    if(!node)
        assert(false);

    if(node->operand == 'I') {
        return node->value;
    }

    // cout << node->name << " " << node->lhs << " " << node->rhs << endl;
    int lval = find_value(node->lhs);
    int rval = find_value(node->rhs);

    int ans = -1;
    switch (node->operand) {
        case '^': { ans = lval ^ rval; break; }
        case '|': { ans = lval || rval; break; }
        case '&': { ans = lval && rval; break; }
        default: {
            // cout << node->name << " '" << node->operand << "' " << node->lhs << endl;
            assert(false);
        }
    }
    node->value = ans;
    return ans;
}

void solve() {
    vector<Gate*> gates;
    vector<Gate*> zgates;
    map<string, int> mp;
    string tmp;
    while(getline(cin, tmp)) {
        if(tmp.size() == 0)
            continue;
        if(tmp.find(':') == string::npos) {
            string q = tmp.substr(0, tmp.find("->") - 1);
            string ans = tmp.substr(tmp.find("->") + 2);
            trim(ans);

            string rhs, lhs;
            char op;
            if(q.find("AND") != string::npos) {
                lhs = q.substr(0, q.find("AND") - 1);
                rhs = q.substr(q.find("AND") + 3);
                trim(lhs); trim(rhs);
                op = '&';
            } else if(q.find("XOR") != string::npos) {
                lhs = q.substr(0, q.find("XOR") - 1);
                rhs = q.substr(q.find("XOR") + 3);
                trim(lhs); trim(rhs);
                op = '^';
            } else {
                lhs = q.substr(0, q.find("OR") - 1);
                rhs = q.substr(q.find("OR") + 2);
                trim(lhs); trim(rhs);
                op = '|';
            }

            // printf("%s%c%s->%sx\n", lhs.c_str(), op, rhs.c_str(), ans.c_str());
            Gate *l = nullptr, *r = nullptr;
            Gate* ansp = nullptr;
            for(int i = 0; i < gates.size(); i++) {
                if(gates[i]->name == lhs) {
                    l = gates[i];
                }
                if(gates[i]->name == rhs) {
                    r = gates[i];
                }
                if(gates[i]->name == ans) {
                    ansp = gates[i];
                }
            }
            if(!l) {
                assert(!(lhs[0] == 'x' || lhs[0] == 'y'));
                l = new Gate(lhs, '?', nullptr, nullptr);
                gates.push_back(l);
            }
            if(!r) {
                assert(!(rhs[0] == 'x' || rhs[0] == 'y'));
                r = new Gate(rhs, '?', nullptr, nullptr);
                gates.push_back(r);
            }
            if(ansp == nullptr) {
                ansp = new Gate(ans, op, nullptr, nullptr);
                gates.push_back(ansp);
            } else assert(ansp->operand == '?');

            ansp->lhs = l;
            ansp->rhs = r;
            ansp->operand = op;

            if(ans[0] == 'z') {
                zgates.push_back(ansp);
            }
        } else {
            string lhs = tmp.substr(0, tmp.find(":"));
            int val = stoi(tmp.substr(tmp.find(':') + 1));
            // printf("%s: %d\n", lhs.c_str(), val);
            if(lhs[0] == 'x' || lhs[0] == 'y') {
                Gate* g = new Gate(lhs, 'I', nullptr, nullptr, val);
                gates.push_back(g);
            } else assert(false);
        }
    }

    sort(zgates.begin(), zgates.end(), [](Gate* lhs, Gate* rhs) {
        return lhs->name < rhs->name;
    });


    ll ans = 0;
    for(int i = 0; i < zgates.size(); i++) {
        int val = find_value(zgates[i]);
        assert(val == zgates[i]->value);
        if(val)
            ans |= 1LL << i;
        // cout << zgates[i]->name << ": " << zgates[i]->value << endl;
    }
    cout << "Gates: " << gates.size() << "\nOutput gates: " << zgates.size() << endl;
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
