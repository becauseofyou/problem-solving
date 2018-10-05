# NOIP图论基础

[TOC]

## 预备知识

- 邻接矩阵
- 邻接表
- 图的遍历

### 邻接矩阵



$n$ 个点, $m$条边的无向图, 使用一个二维数组adj\[i][j] 表示i与j之间有一条边 由i指向j,adj\[i][j]的值表示这条边的权值,如果是无向图,那么每条边双向都可以走

**邻接矩阵建图代码**

```cpp
int n, m, x, y, z;
scanf("%d%d", &n, &m);
memset(adj, -1, sizeof(adj)); //一开始假设用-1表示两两不连通
for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &x, &y, &z);
    adj[x][y] = adj[y][x] = z; 
}
```

**例子**

![image-20180930083135730](/Users/wuyiqi/Library/Application Support/typora-user-images/image-20180930083135730.png)


$$
\begin{matrix}
-1 & 100 & 200 \\
100 & -1 & -1 \\
200 & -1 & -1
\end{matrix}
$$

### 邻接表

邻接矩阵的好处是简单,劣势是假如图的点数比较多,边数比较少（我们称这种情况为图比较稀疏）的时候，实际上矩阵中的很多元素都是-1,有很多的空间浪费了,于是邻接表就有了用武之地.

邻接表本质上就是链表,它保存了每条边的信息,然后将一个点的邻接的边建成一个单向或者双向的链表,一般情况下我们用单向的链表就够用了,head[u]记录了点u周围的第一条边的编号，nxt[i]记录了i号边的下一条边的编号,pnt记录的是边的指向,weight记录的是边的边权,每次新增一条u->v的边之后就将新加入边的编号的下一条边设为u之前的第一条边的编号，再将u的第一条边的编号设为刚刚加入的边的编号，那么访问的时候就可以从head[u]开始一直nxt下去访问一个点所有的邻接点了。

```cpp
const int MAX_NODE = 100010; // 100000个点
const int MAX_EDGE = 200010;//100000条边，双向边开两倍空间
int head[MAX_NODE], nxt[MAX_EDGE], pnt[MAX_EDGE], weight[MAX_EDGE];
int E;
void add_edge(int a, int b, int c) {
    pnt[E] = b;
    nxt[E] = head[a];
    weight[E] = c;
    head[a] = E++;
}
int main() {
    E = 0;
    memset(head, -1, sizeof(head));
    int n, m, x, y, z;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
        add_edge(y, x, z);
    }
}
```

### 图的遍历

图的遍历根据具体问题的需要有两种方式，一种是深度优先遍历，另一种是广度优先遍历

**dfs遍历**

```cpp
void dfs(int u) {
    vis[u] = true;
    for (int i = head[u]; i != -1; i = nxt[i]) {//访问u所有的邻接边的信息
        int to = pnt[i];
        if (!vis[to]) {
            dfs(to);
        }
    }
}
```

**bfs遍历**

```cpp
void bfs(int s) {
    queue<int> q;
    memset(vis, false, sizeof(vis));
    q.push(s);
    vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; i != -1; i = nxt[i]) {
            int v = pnt[i];
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}
```



## 最短路径算法

### dijkstra

 单源最短路：求某个点到其他所有点的最短路

假如边权都为1，可以用广搜解决，否则就需要用到dijkstra算法

该算法每次确定一个点的最短路，用这个点的最短路距离再去更新邻接点的最短路，不断的迭代更新产生新的最短路

```cpp
const int inf = (int)1e9; // 根据具体题目而定
void dijkstra(int s, int n) { //s为起点,n为点数，mp数组为图的邻接矩阵
    for(int i = 0; i < n; i++) {
        d[i] = inf; 
    }
    d[s] = 0; 
    for (int step = 0; step < n; step++) { //每次都会找一个点确定它的最短路
        int id = -1;
        int mi = inf;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && d[i] < mi) {//寻找未访问的点中d值最小的点
                mi = d[i];
                id = i;
            }
        }
        if (id == -1) {//可能会出现找不到的情况，图不连通
            break;
        }
        vis[id] = true;//标记id这个点已经确定了最短路，以后不需要再理
        for (int i = 0; i < n; i++) {
            if (d[id] + mp[id][i] < d[i]) {
                d[i] = d[id] + mp[id][i];
            }
        }
    }
}
```



上述算法每一轮都会确定一个点的最短路，每一轮需要O(n)寻找最小值，因此复杂度是$O(n^2)$ 

### dijkstra的优化

我们可以尝试着对上述算法做以下两点优化

-  设计一个数据结构快速的寻找距离值最小的点
- 采用邻接表存储图，更新的时候只需要访问与自己相邻的点



找最值可以用STL的**priority_queue** 或者 **set** ,由于我们要找的最小值所在的下标，所以应该要将距离值与点的标号作为一个单元的元素一起插入数据结构，按照距离值从小到大取出。每次**更新成功**就插入新的元素，所以会存在插入元素之后这个元素的距离值又被更新了，那么堆里面就会同时存在两个相同编号，不同距离值的元素，但是由于我们维护了一个距离数组来实时的标记一个点的最短距离值，因此当从堆中取出的元素的距离值是大于当前实际的最短距离值的，这个元素就跳过即可。



 ```cpp
int dist[N];
void dijkstra(int s, int n) {
    priority_queue<pair<int,int> > q;//默认大根堆，如果元素是pair，默认按照第一个关键字排序
    for (int i = 0; i < n; i++) {
        dist[i] = inf;
    }
    dist[s] = 0;
    q.push(make_pair(-dist[s], s));//插入相反数就可以当作小根堆
    while(!q.empty()) {
        pair<int,int> now = q.top(); q.pop();
        int d = -now.first;
        int u = now.second;
        if (d != dist[u]) {
            continue;
        }
        for (int i = head[u]; i != -1; i = nxt[i]) {//u的最短路已经确定，用它来更新邻接点
            if (d + weight[i] < dist[pnt[i]]) {
                dist[pnt[i]] = d + weight[i];
                q.push(make_pair(-dist[pnt[i]], pnt[i]));
            }
        }
    }
}
 ```

### bellman ford

当边权存在负数的时候，图中可能会产生负环，这个时候dijkstra是没法判断负环的，bellman ford算法的核心思想是每个点的最短路最多被n-1个点更新，一开始设dist[s] = 0,然后执行n-1轮，每一轮都去枚举每一条边a->b,如果dist[a] + weight\[a][b] < dist[b]就更新dist[b],n-1轮之后，如果还有某条边能更新成功，说明存在负环

```cpp
int bellman_ford(int s, int t, int n) {//求s到t的最短路,一共有n个点
    bool flag = false;
    for (int i = 0; i < n; i++) {
        dist[i] = inf;
    }
    dist[s] = 0;
    for (int step = 0; step < n; step++) {//执行n轮更新
        flag = false;
        for (int u = 0; u < n; u++) {//枚举每一个点
            for (int i = head[u]; i != -1; i = nxt[i]) {//枚举每一条边
                int v = pnt[i];
                if (dist[u] + weight[i] < dist[v]) {//更新成功
                    dist[v] = dist[u] + weight[i];
                    flag = true;
                }
            }
        }
    }
    if (flag) {
        return -1; //第n次更新成功，说明有负环
    }
    return dist[t];
}
```

### floyd

佛洛依德算法可以求两两之间的最短路，相当运行枚举每一个点作为起点跑dijkstra，复杂度$O(n^3)$

floyd算法思路比较灵巧，我们先来看代码

```cpp
void floyd(int n) {//d数组一开始为原图的邻接矩阵
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
```

代码及其简短，我们来研究一下为何短短三个循环即可算出所有点对最短路。

我们假设某一个点对a->b的最短路$v_1->v_2->v_3->...->v_k...->v_m$

我们知道对于这个序列的任意一对点$v_i,v_j$ 它们的最短路肯定可以是$v_i,v_{i+1},v_{i+2}...v_j $ , 如果存在更短的，说明a->b 的最短路也可以被更新，与我们之前的假设矛盾

而且我们知道$v2\ v3..\ v_{m-1}$ 这些中间节点一定会以某个顺序在第一层循环中被枚举到,可以想象一开始有m条线段，每条线段都只有一个点**$v_i$** , 每当在最外层枚举到序列中的某个点$v_k$, 下面两层循环肯定会枚举到与k相邻的所有点， 那么$v_k$所在的线段就会与$v_{k-1}, v_{k+1}​$所在的线段连通起来,而且由于之前的线段上两两之间的最短路都已经算好了，线段在合并之后，k左边的点与k右边的点之间的最短路都会被 d\[i][k] + d\[k][j]更新成正确的最短路

