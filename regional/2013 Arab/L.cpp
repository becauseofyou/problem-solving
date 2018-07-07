#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
        int cas;
        scanf("%d",&cas);
        while (cas--) {
                int n,x,y;
                scanf("%d%d%d",&n,&x,&y);
                vector<int> a;
                if (y==2) {
                        a.push_back(x);
                        int cnt = 1,p = 1;
                        while (cnt<n) {
                                while (p==x) p ++;
                                cnt ++;
                                a.push_back(p++);
                        }
                } else {
                        int cnt = 0,p = 1;
                        while (cnt<n) {
                                while (p==x) p ++;
                                cnt ++;
                                a.push_back(p++);
                        }
                }
                sort(a.begin(),a.end());
                for (int i = 0; i < n; i ++) {
                        printf("%d%c",a[i]," \n"[i==n-1]);
                }
        }
        return 0;
}