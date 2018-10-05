#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int a[N], b[N];

int find (int a[], int l, int r, int num) {
    int best = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (a[mid] == num) {
            best = mid;
            r = mid - 1;
        } else if (a[mid] < num) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return best;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    
    sort (b, b + n);
    /*
    int tot = 1;
    for (int i = 1; i < n; i++) {
        if (b[i] != b[i - 1]) {
            b[tot++] = b[i];
        }
    }*/
    for (int i = 0; i < n; i++) {
        a[i] = find(b, 0, n - 1, a[i]) + 1;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}
