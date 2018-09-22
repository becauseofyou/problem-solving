#include <bits/stdc++.h>
using namespace std;

const int N = 2500;
const int md = (int) 1e9 + 7;

int dp[N][N];
int sum1[N], sum2[N];

void add(int &x, int y) {
    x += y;
    if (x >= md) {
        x -= md;
    }
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    for (int i = 0; i < (int)s1.length(); i++) {
        sum1[i + 1] = sum1[i] + (s1[i] == '(');
    }

    for (int i = 0; i < (int)s2.length(); i++) {
        sum2[i + 1] = sum2[i] + (s2[i] =='(');
    }

    int len1 = s1.length();
    int len2 = s2.length();
    s1 += '@';
    s2 += '@';
    dp[0][0] = 1;
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            int left = sum1[i] + sum2[j];
            int right = i + j - left;
            if (left < right) {
                continue;
            }
            int f = (s1[i] == '(') ? 1 : -1;
            int g = (s2[j] == '(') ? 1 : -1;
            if (left - right + f >= 0)  {
                add(dp[i + 1][j], dp[i][j]);
            } 
            if (left - right + g >= 0){
                add(dp[i][j + 1], dp[i][j]);
            }
        }
    }
    if (2 * (sum1[len1] + sum2[len2] ) == len1 + len2)
        cout << dp[len1][len2] << endl;
    else 
        cout << 0 << endl;
    return 0;
}
