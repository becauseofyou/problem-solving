#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
const int N = 100+5;
int n, m;
int a[N*N][N<<1], b[N][N], val[N][N], c[11], x[N<<1], freex[N<<1], xx[N<<1];
bool vis[11111];
int id[11111];
string step[11111];

queue<int>  qu;
void bfs() {
    memset(vis, 0, sizeof(vis));
    while(!qu.empty())  qu.pop();
    vis[1234] = 1;
    qu.push(1234);
    while(!qu.empty()) {
        int cur = qu.front(); qu.pop();
        for(int i = 0;i < 4; i++) {
            int fuck = cur;
            for(int j = 3;j >= 0; j--)  c[j] = fuck%10, fuck /= 10;
            int &A = c[i], &B = c[(i+1)%4], &C = c[(i+2)%4];
            swap(A, B); swap(B, C);
            int to = 0;
            for(int j = 0;j < 4; j++)   to = to*10 + c[j];
            if(!vis[to]) {
                step[to] = step[cur] + (char)(i+'0');
                vis[to] = 1;
                qu.push(to);
           //     printf("to = %d ", to);
            //    cout<<step[to]<<endl;
            }
        }
    }
}

int var, equ;

void debug() {
    int i,j;
    puts("debug");
    for(i = 0;i < equ; i++) {
        for(j = 0;j < var+1;j ++)
            printf("%d ",a[i][j]);
        puts("");
    }
    puts("end");
}

bool gauss() {
    //debug();
    int i,j,k, row = 0 , col = 0;
    for(; row < equ && col < var; row++ , col++) {
        int maxr = row;
        for(i = row+1;i < equ; i++)
            if(a[i][col])
                maxr = i;
        if(a[maxr][col]==0) {
            row--;
            continue;
        }
        if(row!=maxr)
            for(i = col;i < var+1;i ++)
                swap(a[maxr][i], a[row][i]);
        for(i = row+1;i < equ; i++) {
            if(a[i][col]==0)
                continue;
            for(j = col;j < var+1;j ++)
                a[i][j] ^= a[row][j];
        }
    }
    //debug();
    for(i = row;i < equ; i++) if(a[i][var]) {
        return false;
    }
    if(row < var) {
        for(i = row-1;i >= 0;i --) {
            int num = 0 , id;
            for(j = row;j < var; j++)
                if(freex[j] && a[i][j])
                    num++ , id = j;
            if(num > 1)
                continue;
            freex[i] = 0;
        }
        int num = var-row , d = 0;
        for(j = var-1;j >= 0 && d < num; j--)
            if(freex[j])
                xx[d++] = j;
        int N = 1<<num;
        for(i = 0;i < 1; i++) {
            for(j = 0;j < num ; j++)
                if(i & (1<<j))
                    x[xx[j]] = 1;
                else
                    x[xx[j]] = 0;
            for(j = row-1;j >= 0; j--) {
                for(k = j;k < var; k++)
                    if(a[j][k])
                        break;
                int id = k;
                x[id] = a[j][var];
                for(k = id+1;k < var; k++)
                    if(a[j][k] && x[k])
                        x[id] ^= 1;
            }
        }
        return true;
    }
    for(i = var-1;i >= 0; i--) {
        x[i] = a[i][var];
        for(j = i+1;j < var; j++) if(a[i][j] && x[j])
            x[i] ^= 1;
    }
    return true;
}

vector<string>  pr;

string getstring(int val) {
    string ret;
    while(val) {
        ret = (char)(val%10 + '0') + ret;
        val /= 10;
    }
    return ret;
}

void deal(int x1, int x2, int y1, int y2, int zt) {
    string cur = step[zt];
    for(int i = 0;i < cur.size(); i++) {
        if(cur[i] == '0') {
            pr.push_back("R" + getstring(x2)); pr.push_back("C" + getstring(y1));
            pr.push_back("R" + getstring(x2)); pr.push_back("C" + getstring(y1));
        }
        else if(cur[i]=='1') {
            pr.push_back("C" + getstring(y2)); pr.push_back("R" + getstring(x2));
            pr.push_back("C" + getstring(y2)); pr.push_back("R" + getstring(x2));
        }
        else if(cur[i]=='2') {
            pr.push_back("R" + getstring(x1)); pr.push_back("C" + getstring(y2));
            pr.push_back("R" + getstring(x1)); pr.push_back("C" + getstring(y2));
        }
        else {
            pr.push_back("C" + getstring(y1)); pr.push_back("R" + getstring(x1));
            pr.push_back("C" + getstring(y1)); pr.push_back("R" + getstring(x1));
        }
    }
}

bool solve() {
    memset(a, 0, sizeof(a));
    memset(id, 0, sizeof(id));
    memset(freex, 0, sizeof(freex));
    int nn = (n+1)/2, mm = (m+1)/2;
    equ = 0;
    var = n+m;
    for(int i = 1;i <= nn; i++) {
        for(int j = 1;j <= mm; j++) {
            if(i == n-i+1) {
                if(j == m-j+1) {
                    if(b[i][j] != val[i][j])
                        return false;
                }
                else {
                    a[equ][i-1] = 1;
                    if(b[i][j]==val[i][m-j+1] && b[i][m-j+1]==val[i][j]) {
                        a[equ][n+m] = 1;
                    }
                    else if(b[i][j]==val[i][j] && b[i][m-j+1]==val[i][m-j+1]) {
                        a[equ][n+m] = 0;
                    }
                    else    return false;
                    equ++;
                }
            }
            else {
                if(j == m-j+1) {
                    a[equ][n+j-1] = 1;
                    if(b[i][j]==val[i][j] && b[n-i+1][j]==val[n-i+1][j]) {
                        a[equ][n+m] = 0;
                    }
                    else if(b[i][j]==val[n-i+1][j] && b[n-i+1][j]==val[i][j]) {
                        a[equ][n+m] = 1;
                    }
                    else    return false;
                    equ++;
                }
                else {
                    id[b[i][j]] = 1; id[b[n-i+1][j]] = 2;
                    id[b[n-i+1][m-j+1]] = 3;id[b[i][m-j+1]] = 4;
                    if(!id[val[i][j]] || !id[val[n-i+1][j]] || !id[val[n-i+1][m-j+1]] || !id[val[i][m-j+1]])
                        return false;
                    int nxt = id[val[i][j]]*1000+id[val[n-i+1][j]]*100+id[val[n-i+1][m-j+1]]*10+id[val[i][m-j+1]];
                    a[equ][i-1] = a[equ][n-i] = a[equ][n+j-1] = a[equ][n+m-j] = 1;
                    if(!vis[nxt]) {
                        a[equ][n+m] = 1;
                    }
                    else
                        a[equ][n+m] = 0;
                    equ++;
                    id[b[i][j]] = 0; id[b[n-i+1][j]] = 0;
                    id[b[n-i+1][m-j+1]] = 0;id[b[i][m-j+1]] = 0;
                }
            }
        }
    }
    if(!gauss())    return false;

    int f[11][11];
    for(int i = 1;i <= n; i++)
        for(int j = 1;j <= m; j++)
            f[i][j] = b[i][j];


    pr.clear();
    for(int i = 0;i < var; i++) if(x[i]) {
        if(i < n) {
            string cur = "R" + getstring(i+1);
            for(int j = 1;j <= mm; j++) swap(b[i+1][j], b[i+1][m-j+1]);
            pr.push_back(cur);
        }
        else {
            string cur = "C" + getstring(i-n+1);
            for(int j = 1;j <= nn; j++) swap(b[j][i-n+1], b[n-j+1][i-n+1]);
            pr.push_back(cur);
        }
    }
    for(int i = 1;i <= nn; i++) {
        for(int j = 1;j <= mm; j++) if(i!=n-i+1 && j!=m-j+1){
            id[b[i][j]] = 1; id[b[n-i+1][j]] = 2;
            id[b[n-i+1][m-j+1]] = 3;id[b[i][m-j+1]] = 4;
            int nxt = id[val[i][j]]*1000+id[val[n-i+1][j]]*100+id[val[n-i+1][m-j+1]]*10+id[val[i][m-j+1]];
            deal(i, n-i+1, j, m-j+1, nxt);
            id[b[i][j]] = 0; id[b[n-i+1][j]] = 0;
            id[b[n-i+1][m-j+1]] = 0;id[b[i][m-j+1]] = 0;
        }
    }
    printf("POSSIBLE ");
    printf("%d", pr.size());
    for(int i = 0;i < pr.size(); i++) {
        cout<<" "<<pr[i];
    }
    puts("");
    /*
    for(int i = 0;i < pr.size(); i++) {
        if(pr[i][0] == 'R') {
            int cur = pr[i][1]-'0';
            for(int j = 1;j <= mm; j++) swap(f[cur][j], f[cur][m-j+1]);
        }
        else {
            int cur = pr[i][1]-'0';
            for(int j = 1;j <= nn; j++) swap(f[j][cur], f[n-j+1][cur]);
        }
    }
    for(int i = 1;i <= n; i++) {
        for(int j = 1;j <= m; j++)
            printf("%d ", f[i][j]);
        puts("");
    }
    */
    return true;
}

int main() {
    bfs();
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &m, &n);
        for(int i = 1;i <= n; i++) {
            for(int j = 1;j <= m; j++)
                val[i][j] = (i-1)*m + j;
        }
        for(int i = 1;i <= n; i++) {
            for(int j = 1;j <= m; j++)
                scanf("%d", &b[i][j]);
        }
        if(!solve())    puts("IMPOSSIBLE");
    }
    return 0;
}