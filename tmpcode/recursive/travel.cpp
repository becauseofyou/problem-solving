#include <bits/stdc++.h>
using namespace std;

const int N = 110;

int ch[N][2];
int cnt[N];


void pre_order(int u) {
    if (u == 0) {
        return ;
    }
    printf("%d ", u);
    pre_order(ch[u][0]);
    pre_order(ch[u][1]);
}

void in_order(int u) {
    if (u == 0) {
        return ;
    }
    in_order(ch[u][0]);
    printf("%d ", u);
    in_order(ch[u][1]);
}

void post_order(int u) {
    if (u == 0) {
        return ;
    }
    post_order(ch[u][0]);
    post_order(ch[u][1]);
    printf("%d ", u);
}

int main() {
    int n;
    int a, b, c;
    scanf("%d", &n);
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        ch[a][0] = b;
        ch[a][1] = c;
        ++cnt[b];
        ++cnt[c];
    }
    int root = -1;
    for (int i = 1; i <= n; i++) if(cnt[i] == 0) {
        root = i;
    }

    pre_order(root); puts("");
    in_order(root); puts("");
    post_order(root);
    return 0;
}
