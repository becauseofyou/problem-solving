#include <bits/stdc++.h>
using namespace std;


const int N = 5010;

struct data {
    int dep;
    int val;
    data(int dep=0, int val=0): dep(dep), val(val) {
    }
    bool operator < (const data& cmp) const {
        return dep > cmp.dep;
    }
};

vector <int> e[N];
long long ans[N], val[N];
int dep[N];


struct BIT {
    vector <int> b;
    int n;
    void init (int n) {
        b.resize(n, 0);
    }
};

void solve(vector <int>& now) {
    vector <data> a(now.size());
    for (int i = 0; i < (int)now.size(); i++) {
        a[i] = data(dep[now[i]],(int)val[now[i]]);
    }

    sort(a.begin(), a.end());

    int tot = (int)a.size();
    for (int i = 0; i < tot; i++) {
        int j = i;
        while(j + 1 < tot && a[j].dep == a[j + 1].dep) {
            j++;
        }
    }
}


void merge(vector<int> &a, vector<int> b) {
    for (int v: b) {
        a.push_back(v);
    }
}

vector<int> dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    vector<int> now;
    now.push_back(u);
    for (int v: e[u]) if(v != f) {
        merge(now, dfs(v, u));
    }
    ans[u] = solve(now);
    return now;
}

int main() {
    int n;
    scanf("%d", &n);
    map<long long, int> mp;
    int tot = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &val[i]);
        if (mp.find(val[i]) == mp.end()) {
            mp[val[i]] = tot++;
        }
    }
    for (int i = 0; i < n; i++) {
        val[i] = mp[val[i]];
    }
    int x, y;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        x--; y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(0, 0);
    return 0;
}
