/*
有一些细节的贪心题，比较考察综合能力
能上去也能下来的就都上去
能上去不能下来的分两种情况
1: 其他的army能覆盖子树内所有叶子，就全部都上去
2: 否则保留最小的一个
最后大的给大的，小的给小的   
*/
#include <bits/stdc++.h>
using namespace std;

vector <vector <pair<int,int> > > e;
vector <int> army;
vector <int>  L, R;
vector <long long> weight;
vector <vector <int> > parent;
int tot;
int n;
vector <int> son_army;
vector <bool> vis;
vector <long long> need;
vector <int> belong;
vector <pair<int,int> > ex;

void init () {
    parent.resize(18, vector <int> (n, 0));
    son_army.resize(n);
    vis.resize(n, false);
    e.resize(n);
    weight.resize(n);
    L.resize(n);
    R.resize(n);
    belong.resize(n);
}

void dfs(int u, int f, int type = -1) {
    belong[u] = type;
    parent[0][u] = f;
    bool leaf = true;
    int tmp = tot;
    son_army[u] = vis[u];
    for (auto it : e[u]) {
        int v = it.first;
        int w = it.second;
        if (v != f) {
            if (u == 0) {
                type = v;
            }
            leaf = false;
            weight[v] = weight[u] + w;
            dfs(v, u, type);
            son_army[u] += son_army[v];
        }
    }
    if (leaf) {
        L[u] = R[u] = ++tot;
    } else {
        L[u] = tmp + 1;
        R[u] = tot;
    }
}

bool can_override(vector <pair<int,int> > &inter, int left, int right) {
    if(inter.size() == 0) {
        return false;
    }
    sort(inter.begin(), inter.end());
    int pt = left;
    for (auto it : inter) {
        if (it.first <= pt) {
            pt = max(pt, it.second);
        }
    }
    return pt == right;
}

bool judge(long long t) {
    vector <long long> now_need;

    vector <vector <pair<int,int> > > inter(n, vector<pair<int, int> > ());
    vector <int> out(n, 0);
    vector <long long> value;
    vector <bool> used(n, false);
    for (auto it : e[0]) { // 1: no army
        if (son_army[it.first] == 0) {
            used[it.first] = true;
            now_need.emplace_back(it.second);
        }
    }

    vector <vector <int> > tmp(n, vector<int>());
    for (int v : army) {
        if (weight[v] < t) {
            if(t - weight[v] >= weight[belong[v]]) { // can go back
                value.emplace_back(t - weight[v]);
                out[belong[v]]++;
                if(out[belong[v]] == son_army[belong[v]]) { // 2 : all army go out
                    used[belong[v]] = true;
                    now_need.emplace_back(weight[belong[v]]);
                }
            } else { // can go out but can't go back
                tmp[belong[v]].emplace_back(t - weight[v]);
            }
        } else {
            int now = v;
            for (int i = 17; i >= 0; i--) {
                if (weight[v] - weight[parent[i][now]] <= t) {
                    now = parent[i][now];
                }
            }
            if (now == 0) {
                now = belong[v];
            }
            inter[belong[v]].emplace_back(make_pair(L[now], R[now]));
        }
    }

    //3 : can't overwrite all the interval
    for (auto it: ex) if (!used[it.first]){
        if (!can_override(inter[it.first], L[it.first], R[it.first]) ) {
            used[it.first] = true;
            if (tmp[it.first].size() == 0) {
                now_need.emplace_back(it.second);
            }
        } else {
            for (int i = 0; i < (int)tmp[it.first].size(); i++) {
                value.emplace_back(tmp[it.first][i]);
            }    
        }
    }

    for (auto it: e[0]) if(used[it.first] && tmp[it.first].size() > 0){
        used[it.first] = false;
        sort (tmp[it.first].begin(), tmp[it.first].end());
        for (int i = 1; i < (int)tmp[it.first].size(); i++) {// except the min, others go out 
            value.emplace_back(tmp[it.first][i]);
        }
    }


    sort(value.begin(), value.end(), [](long long a, long long b){return a > b;});
    sort(now_need.begin(), now_need.end() , [](long long a, long long b) {return a > b;});
    if (now_need.size() > value.size()) {
        return false;
    }
    for (int i = 0; i < (int)now_need.size(); i++) {
        if (now_need[i] > value[i]) {
            return false;
        }
    }
    return true;
}

void solve() {

    long long l = 0, r = (long long)1e14, best = -1;
    while (l <= r) {
        long long m = l + r >> 1;
        if (judge(m)) {
            best = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    printf("%lld\n", best);
}

int main () {
    int a, b, c;
    scanf("%d", &n);
    init ();
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        a --;
        b --;
        e[a].emplace_back(make_pair(b, c));
        e[b].emplace_back(make_pair(a, c));
    }

    int m, x;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        x--;
        vis[x] = true;
        army.emplace_back(x);
    }
    dfs(0, 0);
    for (int i = 1; i < 18; i++) {
        for (int j = 0; j < n; j++) {
            parent[i][j] = parent[i - 1][parent[i - 1][j]];
        }
    }
    for (auto it : e[0]) {
        if (son_army[it.first] > 0) {
            ex.emplace_back(it);
        }
    }
    solve();
    return 0;
}
