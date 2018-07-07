#include <bits/stdc++.h>
using namespace std;

char s[110][110];
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < 4; i++) {
        for (int  j = 0; j < n; j++) {
            s[i][j] = '.';
        }
    }

    for (int i = 1; i <= (n-2)/2 && k >= 2; i++) {
        s[1][i] = s[1][n - 1 - i] = '#';
        k -= 2;
    }
    for (int i = 1; i <= (n-2)/2 && k >= 2; i++) {
        s[2][i] = s[2][n - 1 - i] = '#';
        k -= 2;
    }
    int row = 1;
    while(k > 0) {
        s[row][n / 2] = '#';
        k--;
        row++;
    }
    cout << "YES" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < n; j++) {
            cout << s[i][j] ;
        }
        cout << endl;
    }
    return 0;
}
