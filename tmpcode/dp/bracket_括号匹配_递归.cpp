
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

int solve(int i, int j) {
    if (i > j) {
        return 0;
    }
    if (i == j) {
        return 1;
    }
    if (f[i][j] != -1) {
        return f[i][j];
    }

    if (pipei(i, j)) {
        checkmin(f[i][j], solve(i + 1, j - 1) );
    }

    for (int k = i ; k < j; k++) {
        checkmin(f[i][j], solve(i, k) + solve(k + 1, j));
    }
    return f[i][j];
}
int main () {
    scanf("%s", s);
    int n = strlen(s);
    memset(f, -1, sizeof(f));
    int ret = solve(0, n - 1);
    printf("%d\n", ret);
    return 0;
}
