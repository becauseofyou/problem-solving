#include <bits/stdc++.h>
using namespace std;

void solve(int n, int p) {
    int edge = 0;
    for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                printf("%d %d\n", i + 1, j + 1);
                if (++edge == 2 * n + p) {
                    return ;
                }
            }
        }
}
int main() {
    int t, n, p;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &p);
        solve(n, p);
    }
    return 0;
}