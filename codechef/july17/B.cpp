#include <bits/stdc++.h>
using namespace std;

char a[1000010];

int main () {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", a);
        int n = strlen(a);
        bool flag = false;
        for (int i = 0; i < n; i++) {
            if (a[i] != '=') {
                flag=true;
            }
        }
        if(!flag) {
            puts("1");
            continue;
        }
        int mx = 1;
        int now = 1;
        char last = a[0];
        for (int i = 1; i < n; i++) {
            if (a[i] == '=') {
                continue;
            }
            if (a[i] == last) {
                now++;
            } else {
                if (now > mx) {
                    mx = now;
                }
                now = 1;
            }
            last =  a[i];
        }
        if(now > mx) {
            mx = now;
        }
        printf("%d\n", mx + 1);
    }
    return 0;
}
