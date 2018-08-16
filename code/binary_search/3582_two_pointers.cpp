#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int  a[N];


void checkmin(int &x, int y) {
    if (y < x) {
        x = y;
    }
}

int main() {
    int n, S;
    scanf("%d%d", &n, &S);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int pt = 1;
    int sum = 0;
    int ret = n;
    //每一个i对应的左端点是单调的
    //均摊 复杂度 O(n)
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        while (pt < i && sum - a[pt] >= S) {
            sum -= a[pt];
            pt++;
        }
        checkmin(ret, i - pt + 1);
    }
    printf("%d\n", ret);
    return 0;
}

