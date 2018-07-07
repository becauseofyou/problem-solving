#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 15;
char s[N][N];
int dir[4][2] = {1, 1, 1, -1, -1, 1, -1, -1};

int dfs(int x, int y) {
        int ret = 0;
        for(int i = 0;i < 4; i++) {
                int xx = x + dir[i][0];
                int yy = y + dir[i][1];
                if(xx < 0 || yy<0||xx>=10||yy>=10)      continue;
                if(s[xx][yy] == 'B') {
                        int tx = xx+dir[i][0];
                        int ty = yy+dir[i][1];
                        if(tx<0||ty<0||tx>=10||ty>=10)  continue;
                        if(s[tx][ty] == '#') {
                                s[xx][yy] = '#';
                                ret = max(ret, dfs(tx, ty)+1);
                                s[xx][yy] = 'B';
                        }
                }
        }
        return ret;
}
 
int main() {
        int t;
        scanf("%d", &t);
        while(t--) {
                for(int i = 0;i < 10; i++) {
                        scanf("%s", s[i]);
                }
                int ans = 0;
                for(int i = 0;i < 10; i++) {
                        for(int j = 0;j < 10; j++) if(s[i][j] == 'W'){
                                s[i][j] = '#';
                                int cur = dfs(i, j);
                                ans = max(ans, cur);
                                s[i][j] = 'W';
                        }
                }
                printf("%d\n", ans);
        }
        return 0;
}