#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int N = 1010; //left 
const int M = 1010; //right
vector<int> edge[N];
bool visy[M];
int mx[N], my[M];

bool dfs(int s) {
    for (auto t: edge[s]) {
        if(!visy[t]) {
            visy[t] = true;
            if(my[t] == -1 || dfs(my[t])) {
                mx[s] = t;
                my[t] = s;
                return true;
            }
        }
    }
    return false;
}

int max_match(int n, int m) {
    fill(mx, mx + n, -1);
    fill(my, my + m, -1);
    int ret = 0;
    for (int i = 0; i < n; i++) {
        fill(visy, visy + m, false);
        if (dfs(i)) {
            ret++;
        }
    }
    return ret;
}

int main () {
    return 0;
}
