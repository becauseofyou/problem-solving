#include <bits/stdc++.h>
using namespace std;


const int N = 5010;



template <typename T>
class fenwick {
    public:
        vector<T> fenw;
        int n;

        fenwick(int n) : n (n) {
            fenw.resize(n, 0);
        }

        void modify(int x, T v) {
            while (x < n) {
                fenw[x] += v;
                x |= (x + 1);
            }
        }

        T get(int x) {
            T v = 0;
            while (x >= 0) {
                v += fenw[x];
                x = (x & (x + 1)) - 1;
            }
            return v;
        }
};

struct data {
    int dep;
    int val;
    data(int dep=0, int val=0): dep(dep), val(val) {
    }
    bool operator < (const data& cmp) const {
        return dep > cmp.dep;
    }
    void print() {
        cout << dep << " " << val << endl;
    }
};

vector <int> e[N];
long long ans[N], val[N];
int n, dep[N];

long long solve(vector <int>& now) {
    vector <data> a(now.size());
    for (int i = 0; i < (int)now.size(); i++) {
        a[i] = data(dep[now[i]],(int)val[now[i]]);
    }
    sort(a.begin(), a.end());
    int tot = (int)a.size();
    long long ret = 0;
    fenwick<int> tree_square_sum(n + 1);
    fenwick<int> tree_sum(n + 1);
    vector <int> cnt(n + 1, 0);
    for (int i = 0; i < tot; i++) {
        int k = i;
        while (k + 1 < tot && a[k].dep == a[k + 1].dep) {
            k++;
        }
        for (int j = i; j <= k; j++) {
            int sum = tree_sum.get(a[j].val - 1); 
            int square_sum = tree_square_sum.get(a[j].val - 1);
            ret += sum * (sum - 1) / 2 - (square_sum - sum) / 2;
        }
        for (int j = i; j <= k; j++) {
            tree_square_sum.modify(a[j].val, -cnt[a[j].val] * cnt[a[j].val]);

            cnt[a[j].val]++;
            tree_sum.modify(a[j].val, 1);
            tree_square_sum.modify(a[j].val, cnt[a[j].val] * cnt[a[j].val]);
        }
        i = k;
    }
    return ret;
}

int brute(vector <int> &now) {
    int ret = 0;
    int tot = (int)now.size();
    for (int i = 0; i < tot; i++) {
        for (int j = 0; j < tot; j++) {
            for (int k = 0; k < tot; k++) {
                if (now[i] != now[j] && now[i] != now[k] && now[j] != now[k]) {
                    if (dep[now[i]] < dep[now[j]] && dep[now[i]] < dep[now[k]]) {
                        if (val[now[i]] > val[now[j]] && val[now[j]] > val[now[k]]) {
                           //  cout << now[i] << " " << now[j] << " " << now[k] << endl;

                            ret++;
                        }
                    }
                }
            }
        }
    }
    return ret;
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
    // cout << "dd" << endl;
    // cout << ans[u] << " " << brute(now) << endl;
    //assert(ans[u] == brute(now));
    return now;
}

void init() {
     scanf("%d", &n);
    map<long long, int> mp;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &val[i]);
        if (mp.find(val[i]) == mp.end()) {
            mp[val[i]] = 1;
        }
    }
    int tot = 0;

    for (auto it : mp) {
        mp[it.first] = ++tot;
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
}

int main() {
    init() ;
    dfs(0, 0);
    for (int i = 0; i < n; i++) {
        printf("%lld ", ans[i]);
    }
    return 0;
}
