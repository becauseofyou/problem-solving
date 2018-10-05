#include <bits/stdc++.h>
using namespace std;

int d[33333];
//记忆化搜索
int f(int n) {
    if (d[n] != -1) {
        //如果被算过了，就直接返回答案
        return d[n];
    }
    if (n == 1) {
        return 1;
    }
    if (n == 2) {
        return 1;
    }

   d[n] = (f(n - 1) + f(n - 2)) % 100000;
   return d[n];
}

/*
g[1] = 1;
g[2] = 1;
g[3] = g[1] + g[2] + 1;
g[4] = g[3] + g[2] + 1;
g[5] = g[3] + g[4] + 1;
g[32] = g[31] + g[30] + 1;
*/
int main() {
    memset(d, -1, sizeof(d));
    /*
    vector <int> g(33, 0);
    g[1] = 1;
    g[2] = 1;
    for (int i = 3; i <= 32; i++) {
        g[i] = g[i - 1] + g[i - 2] + 1;
    }*/
    size_t t1 = clock();
    cout << f(10000) << endl;
    size_t t2 = clock();
    printf("%.6f\n",1.0* (t2 - t1) / CLOCKS_PER_SEC);
    return 0;
}
