#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

void checkmin(int &x, int y) {
    if (x == -1 || y < x) {
        x = y;
    }
}

bool is[N][N];
int f[N];

int solve(int i)
{
    //当前要解决f[i]的问题
    //然后我们发现j->i是一个回文串
    //那么我们需要先解决f[j - 1]这个子问题
    if (i < 0) {
        return 0;
    }
    if (i == 0) {
        return 1;
    }
    if(f[i] != -1) {
        return f[i];
    }
    for (int j = 0; j <= i; j++) {
        if (is[j][i]) {
            checkmin(f[i], solve(j - 1) + 1);
        }
    }
    return f[i];
}
char s[N];
int main () {
    scanf("%s", s);
    int n = strlen(s);
    memset(is, false, sizeof(is));
    for (int i = 0; i < n; i++) {
        for (int j = 0;i-j>=0 && i+j<n; j++) {
            if (s[i-j] == s[i+j]) {
              //  printf("%d %d\n", i-j, i+j);
                is[i-j][i+j]=true;
            } else {
                break;
            }
        }

        int k = i + 1;
        for (int j = 0; i - j >= 0 && k + j < n; j++) {
            if (s[i - j] == s[k + j]) {
                is[i-j][k+j] = true;
            } else {
                break;
            }
        }
    }
    memset(f, -1, sizeof(f));
    printf("%d\n", solve(n - 1));
    return 0;
}
