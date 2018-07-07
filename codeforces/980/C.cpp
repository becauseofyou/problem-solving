#include <bits/stdc++.h>
using namespace std;

int v[333];
int main()
{
    int n, k, x =-1;
    scanf("%d%d",&n,&k);
    memset(v, -1, sizeof(v));
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        if (v[x] != -1) 
        {
            printf("%d ", v[x]);
            continue;
        }
        int low = max(0, x - k + 1);
        int pos = x;
        for (int j = x; j >= low; j--)  {
            if (v[j] == -1) {
                pos = j;
            } else {
                int p;
                for (p = j; p >= 0 && x - p <= k; p--) if(v[p] == v[j]) {

                } else {
                    break;
                }
                int len = x - p;
                if(len <= k)
                    pos = p + 1;
                break;
            }
        }
        for (int j = pos; j <= x; j++) {
            v[j] = pos;
        }
        printf("%d ", pos);
    }
    return 0;
}
