#include <bits/stdc++.h>
using namespace std;


map<int, long long> dp[22][2];
long long x, y;
long long two[60], three[60], five[60], seven[60];
vector <int> dig;

bool check(int a, int b, int c, int d) {
    long long tmp = 1LL * two[a] * three[b] * five[c] * seven[d];
    return x <= tmp && tmp <= y;
}

int encode(int a, int b, int c, int d) {
    return a*60*60*60 + b*60*60 + c*60 + d;
}

long long dfs(int len, int a, int b, int c, int d, bool lim, bool begin, bool has_zero) {
    if (len == 0) {
        if (has_zero) {
            return x <= 0 && 0 <= y;
        }
        if (!begin) {
            return x <= 0 && 0 <= y;
        }
        cout << a << " " << b << " " << c << " " << d << endl;
        return check(a, b, c, d);
    }
    if (!lim) {
        if (dp[len][has_zero].find(encode(a, b, c, d)) != dp[len][has_zero].end()) {
            return dp[len][has_zero][encode(a, b, c, d)];
        }
    }
    long long ret = 0;
    int mx = lim ? dig[len - 1] : 9;
    for (int i = 0; i <= mx; i++) {
        int aa=0,bb=0,cc=0,dd=0;
        if(begin || i > 0) {
            int num = i;
            if(num > 0) {
                while(num % 2 == 0) aa++, num/=2;
                while(num % 3 == 0) bb++, num/=3;
                while(num % 5 == 0) cc++, num/=5;
                while(num % 7 == 0) dd++, num/=7;
            } 
        }
        ret += dfs(len - 1, a+aa, b+bb, c+cc, d+dd, lim && i == mx, begin || i > 0, has_zero || i == 0);
    }

    if(!lim) {
        dp[len][has_zero][encode(a,b,c,d)] = ret;
    }
    return ret;

}
long long solve (long long n) {
    if (n < 0) {
        return 0;
    }
    dig.clear();
    while (n) {
        dig.push_back(n % 10);
        n /= 10;
    }
    return dfs((int)dig.size(), 0, 0, 0, 0, true, false, false);
}


int main() {
    two[0] = 1;
    three[0] = 1;
    five [0] = 1;
    seven[0] = 1;
    for (int i = 1; i < 60; i++) {
        two[i] = two[i - 1] * 2;
        three[i] = three[i - 1] * 3;
        five[i] = five[i - 1] * 5;
        seven[i] = seven[i - 1] * 7;
    }
    long long l, r;
    cin >> l >> r >> x >> y;
    cout << solve(r) - solve(l - 1) << endl;

    return 0;
}
