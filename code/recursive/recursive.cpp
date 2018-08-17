#include <bits/stdc++.h>
using namespace std;

int n;
bool vis[10];
int rec[10];

void dfs(int dep) {
    if (dep == n) {
        for (int i = 0; i < n; i++) {
            printf("%d ", rec[i]);
        }
        puts("");
        return ;
    }

    for (int i = 1; i <= n; i++) if (false == vis[i]) {
        rec[dep] = i;
        vis[i] = true;
        dfs(dep + 1);
        vis[i] = false;
    }

}

int main() {
    n = 5;
    //dfs(0);
    return 0;
}
