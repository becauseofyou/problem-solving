#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;

int a[111];
int main() {
        int t, n, easy, hard;
        scanf("%d", &t);
        while(t--) {
                scanf("%d%d%d", &n, &easy, &hard);
                bool flag1, flag2;
                for(int i = 1;i <= n; i++)      scanf("%d", &a[i]);
                if(a[1] == easy)        flag1 = true;
                else    flag1 = false;
                if(a[n] == hard)        flag2 = true;
                else    flag2 = false;
                if(flag1 && flag2)      puts("BOTH");
                else if(flag1 && !flag2)        puts("EASY");
                else if(!flag1 && flag2)        puts("HARD");
                else    puts("OKAY");
        }
        return 0;
}

