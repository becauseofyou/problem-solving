#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int a[N], b[N], c[N];
long long ret =0;
void merge_sort(int l, int r) {
    if (l >= r) {
        return ;
    }
    int m = (l + r) / 2;
    merge_sort(l, m);   
    merge_sort(m + 1, r);
    int bcnt = 0, ccnt = 0;
    for (int i = l; i <= m; i++) {
        b[bcnt++] = a[i];
    }
    for (int i = m + 1; i <= r; i++) {
        c[ccnt++] = a[i];
    }
    int j = 0, pt = l;
    for (int i = 0; i < bcnt; i++) {
        while (j < ccnt && c[j] < b[i]) {
            a[pt++] = c[j];
            j++;
        }
        ret += j;
        a[pt++] = b[i];
    }
    while (j < ccnt) {
        a[pt++] = c[j];
        j++;
    }
}

int main () {
    int n, k;
    while(scanf("%d", &n)==1) {
        if(n == 0) break;
        ret = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        merge_sort(0, n - 1);
        printf("%lld\n", ret);
    }
    return 0;
}
