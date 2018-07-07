#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct myque{
    T q[500010];
    int fr = 0, ed = 0;
    bool empty() {
        return fr >= ed;
    }
    T back() {
        return q[ed - 1];
    }
    T front() {
        return q[fr];
    }
    void pop_back() {
        ed--;
    }
    void pop_front() {
        fr++;
    }
    void emplace_back(T ele) {
        q[ed++] = ele;
    }
    void insert(T ele) {
        while (!empty() && back().first <= ele.first) {
            pop_back();
        }
        emplace_back(ele);
    }
};

int main() {
    int n, d, k;
    cin >> n >> d >> k;
    vector <int> x(n + 1), s(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &s[i]);
    }
    int l = 0, r = (int) 1e9, best = -1;
    x[0] = 0;
    while ( l <= r ) {
        int m = l + r >> 1;
        int left = max(1, d - m);
        int right = d + m;
        vector <long long> dp(n + 1, -10000000000000LL);
        dp[0] = 0;
        myque<pair<long long,int> > Q;
        bool flag = false;
        int pt = 0;
        for (int  i = 1; i <= n; i++) {
            while (pt < i && x[pt] + left <= x[i]) {
                Q.insert(make_pair(dp[pt], x[pt]) );
                pt++;
            }
            while (!Q.empty() &&  x[i] - Q.front().second > right) {
                Q.pop_front();
            }
            if (!Q.empty())
                dp[i] = max(dp[i], Q.front().first + s[i]);
            if (dp[i] >= k) {
                flag = true;
                break;
            }
        }
        if (flag)
            best = m, r = m - 1;
        else
            l = m + 1;
    }
    cerr << best << endl;

    return 0;
}
