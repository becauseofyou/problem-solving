
#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int f[N][N];
char s[N];

bool pipei(int i, int j) {
    return s[i] == '(' && s[j] == ')' || 
        s[i] == '[' && s[j] == ']';
}

void checkmin(int &x, int y) {
    if (x == -1 || y < x) {
        x = y;
    }
}

int main () {
    scanf("%s", s);
    int n = strlen(s);
    memset(f, -1, sizeof(f));

    for (int i = 0; i < n; i++) {
        f[i][i]  = 1;
        f[i + 1][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int left = 0; left + len  - 1 < n; left++) {
            int right = left + len - 1;
            if (pipei(left, right) ) {
                checkmin(f[left][right], f[left + 1] [right - 1]);
            }
            for (int k = left; k < right; k++) {
                checkmin(f[left][right], f[left][k] + f[k+1][right] );
            }


        }
    }
    printf("%d\n", f[0][n - 1]);
    return 0;
}
