#include <bits/stdc++.h>
using namespace std;

const int N = 55;
struct Edge {
    int to;
    bool important;
    bool opened;
    Edge(int to=0,bool important=false,bool opened=false): to(to),important(important),opened(opened) {
    }
};

vector <Edge> e[N]; 
int cnt[N];
int p[N], owe[N];
int ret;
//注意到重要的已经打开的边是无需再进行操作的
//假设有两条路径经过这条边，那么这两条路径完全可以转换成不经过这条边的两条路径
//比如下面这个例子
//   \     /
//     --- 
//   /     \
void dfs(int u, int f) { 
    int sum = 0;
    owe[u] = 0;
    for (auto it : e[u]) {
        if (it.to != f) {
            dfs(it.to, u);
            //重要的边需要打开 或者 下面有欠&&不重要的边
            int need = it.important && !it.opened || owe[it.to] && !it.important; 
            owe[u] ^= need;
            sum += need;
            //已经打开的重要的边无需再操作 如果下面有欠（延伸上来） 就在此终结
            if (it.opened && it.important) {
                ret += owe[it.to];
            }
        }
    }
    //横跨u的路径数量
    ret += sum / 2;
}
int main () {
    int n;
    string start, imp;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> p[i];
    }
    cin >> start >> imp;
    for (int i = 0; i < n - 1; i++) {
        e[i + 1].push_back(Edge(p[i], imp[i] == '1', start[i] == '1'));
        e[p[i]].push_back(Edge(i + 1, imp[i] == '1', start[i] == '1'));
    }
    dfs(0, -1);
    ret += owe[0];
    cout << ret << endl;
    return 0;
}
