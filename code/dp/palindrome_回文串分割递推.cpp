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
char s[N];
int main () {
    scanf("%s", s);
    int n = strlen(s);
    memset(is, false, sizeof(is));
    for (int i = 0; i < n; i++) {
        for (int j = 0;i-j>=0 && i+j<n; j++) {
            if (s[i-j] == s[i+j]) {
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

    f[0] = 1;
    for (int i = 1; i < n; i++) {
        // 当前要求f[i],  f[0] ~ f[i-1] 都已经求出来了
        if (is[0][i]) { 
            f[i] = 1;
            continue;
        }
        for (int j = i; j >= 1; j--) if(is[j][i]) {
            checkmin(f[i], f[j - 1] + 1);
        }
    }
    cout << f[n - 1] << endl;
    //printf("%d\n", solve(n - 1));
    return 0;
}
