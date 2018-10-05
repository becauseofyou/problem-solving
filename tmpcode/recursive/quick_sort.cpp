#include <bits/stdc++.h>
using namespace std;
 
const int N = 100010;
int a[N], b[N], c[N];

int get(int l, int r) {
    return l + rand() * rand() % (r-l+1);
}

void quick_sort(int l, int r) {
    if (l >= r) {
        return ;
    }
    int p = get(l, r);
    printf("l=%d r=%d p=%d\n", l, r, p);
    int value = a[p];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < value) i++;
        while (a[j] > value) j--;
        if (i <= j) {
            swap(a[i], a[j]);
            i++; j--;
        }
    }

    if (l < j) quick_sort(l, j);
    if (i < r) quick_sort(i, r);
    /*
    int bcnt = 0, ccnt = 0;
    int num = a[p];
    for (int i = l; i <= r; i++) {
        if (i == p) {
            continue;
        }
        if (a[i] < a[p]) {
            b[bcnt++] = a[i];
        } else {
            c[ccnt++] = a[i];
        }
    }
    for (int i = 0; i < bcnt; i++) {
        a[l + i] = b[i];
    }
    a[l + bcnt] = num; 
    for (int i = 0; i < ccnt; i++) {
        a[l + bcnt + 1 + i] = c[i];
    }
    int m = l + bcnt;
    quick_sort(l, m - 1);
    quick_sort(m + 1, r);
    */
}

int main() {
    //初始化随机种子
    srand(time(0));
    int n;
    scanf("%d", &n);
    size_t t1 = clock();
    for (int i = 0; i < n; i++) {
        a[i] = rand() * rand() % 100;
        //scanf("%d", &a[i]);
    }
    quick_sort(0, n - 1);
    
    size_t t2 = clock();

    printf("%.6f\n", 1.0*(t2 - t1) / CLOCKS_PER_SEC);
    for (int i = 0; i < n; i++) {
        printf("%d " ,a[i]);
    }
    puts("");
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
    t1 = clock();
    sort (b, b + n);
    t2 = clock();

    printf("%.6f\n", 1.0*(t2 - t1) / CLOCKS_PER_SEC);
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            puts("wrong answer");
            break;
        }
    }
    return 0;
}
