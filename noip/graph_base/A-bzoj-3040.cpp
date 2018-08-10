#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
const int M = 10000010;

int mp[N], mp2[N];
int n;
int sz;
long long d[N];
int head[N], nxt[M], pnt[M], w[M];
int E;

typedef pair<long long,int> T;
T value[N];

int push(T x) {
    int now = sz ++;
    while (now > 0) {
        int fa = (now - 1) >> 1;
        if (!(x < value[fa])) {
            break;
        }
        mp[mp2[fa]] = now;//原先映射到fa的点现在映射到now
        mp2[now] = mp2[fa];
        value[now] = value[fa];
        now = fa;
    }
    value[now] = x;
    return now;
}

inline bool empty() {
    return sz == 0;
}

void change (int id, T to) {//将id标号的点的值改成to,变小
    value[id] = to;
    while (id) {
        int fa = (id - 1) >> 1;
        if (value[id] < value[fa]) {
            swap(value[id], value[fa]);
            swap(mp[mp2[id]], mp[mp2[fa]]);
            swap(mp2[id], mp2[fa]);
        }
        id = fa;
    }
}

void pop() {
    T x = value[--sz];
    int now = 0;
    while (( (now << 1) | 1 )< sz) {
        int a = (now << 1) | 1, b = (now << 1) + 2;
        if (b < sz && value[b] < value[a]) { 
            a = b;
        }
        if (!(value[a] < x) ) {
            break;
        }
        mp[mp2[a]] = now;
        mp2[now] = mp2[a];
        value[now] = value[a];
        now = a;
    }
    mp[mp2[sz] ] = now;
    mp2[now] = mp2[sz];
    value[now] = x;
}

T top() {
    return value[0];
}



inline void read(int &x){
    char ch=getchar();x=0;
    for(;ch<'0'||ch>'9';ch=getchar());
    for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
}

inline void add_edge(int a, int b, int c) {
    pnt[E] = b;
    w[E] = c;
    nxt[E] = head[a];
    head[a] = E++;
} 

void dijkstra(int n) {
    fill(d, d + n, -1);
    d[0] = 0;
    push(make_pair(d[0], 0));
    while (!empty()) {
        T _top = top(); pop();
        int u = _top.second;
        if (_top.first > d[u]) {
            continue;
        }
        if (u == n - 1) {
            break;
        }
        for (int i = head[u]; ~i; i = nxt[i]) {
            int v = pnt[i];
            if (d[v] == -1) {
                d[v] = d[u] + w[i];
                mp[v] = push(make_pair(d[v], v));
                mp2[mp[v]] = v;
            } else if (d[v] > d[u] + w[i]) {
                d[v] = d[u] + w[i];
                change(mp[v], make_pair(d[v], v));
            }
        }
    }
    printf("%lld\n", d[n - 1]);
}

int main () {
    int n, m;
    scanf("%d%d", &n, &m);
    int T, rxa, rxc, rya, ryc, rp;
    scanf("%d%d%d%d%d%d", &T, &rxa, &rxc, &rya, &ryc, &rp);
    int x = 0, y = 0, z = 0, a, b, c;
    E = 0;
    memset(head, -1, sizeof(head));
    for (int i = 0; i < T; i++) {
        x = (1LL * x * rxa + rxc) % rp;
        y = (1LL * y * rya + ryc) % rp;
        a = min(x % n + 1, y % n + 1);
        b = max(x % n + 1, y % n + 1);
        a--; b--;
        add_edge(a, b, (int)1e8 - 100 * a);
    }
    int cnt = m - T;
    for (int i = 0; i < cnt; i++) {
        //        scanf("%d%d%d", &a, &b, &c);
        read(a);read(b); read(c);
        a--; b--;
        add_edge(a, b, c);
    }
    dijkstra(n);
    return 0;
}
