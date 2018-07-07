#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;

char s[111111];
int main() {
        int t;
        scanf("%d", &t);
        while(t--) {
                scanf("%s", s);
                int len = strlen(s);
                int cnt = 0, x = 0, y = 0;
                for(int i = 0;i < len; i++) {
                        if(s[i] == 'R') x++;
                        else if(s[i] == 'L')    x--;
                        else if(s[i] == 'U')    y++;
                        else if(s[i] == 'D')    y--;
                        else    cnt++;
                }
                printf("%d %d %d %d\n", x-cnt, y-cnt, x+cnt, y+cnt);
        }
        return 0;
}