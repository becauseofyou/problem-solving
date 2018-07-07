#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
        int cas,ca = 0,n,m;
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d%d",&n,&m);
                int d = n/m,x = 0;
                vector<int> z;
                for (int i = 0; i < m; i ++) {
                        int v;
                        scanf("%d",&v);
                        z.push_back(v);
                }
                sort(z.begin(),z.end());
                vector<int> b;
                for (int i = 0; i < m; i ++) {
                        int v = z[i];
                        b.push_back(v-x);
                        x += d;
                }
                sort(b.begin(),b.end());
                int val = b[m-1]-b[0];
                printf("Case #%d: %d\n",++ca,val-(val/2));
        }
        return 0;
}