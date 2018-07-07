#include <bits/stdc++.h>
using namespace std;

string s[100010];
int mx[2000100];
int id[2000010];

int main () {
    int n, pos;
    cin >> n;
    int max_pos = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        int k;
        cin >> k;
        int len = (int)s[i].length();
        for (int j = 0; j < k; j++) {
            scanf("%d", &pos);
            if (pos > max_pos) {
                max_pos = pos;
            }
            if (len > mx[pos]) {
                mx[pos] = len;
                id[pos] = i;
            }
        }
    }
    int now_max = 0;
    for (int i = 1; i <= max_pos; i++) {
        if (mx[i] == 0) {
            cout << 'a';
        } else {
            for (int j = 0; j < mx[i]; j++) {
                if (mx[i + j] + i + j > i + mx[i]) {
                    i = i + j;
                    j = 0;
                }
                cout << s[id[i]][j];
            }
            i = i + mx[i];
            i--;
        }
    }
    return 0;
}
