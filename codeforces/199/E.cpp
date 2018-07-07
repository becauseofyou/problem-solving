#include <cstdio>
#include <cstring>
#include <algorithm>
using std::max;
using std::min;
const int N = 100010;
const int inf = 100000000;
struct node 
{
    node *fa,*c[2];
    int lz,max_dep,id,is,dep,nil;
    int key; // the minimum depth of red node in the subtree
    int ans; // the minimum red_dep - 2*dep[lca];
    void setc(int d,node *s){
        c[d] = s;
        s->fa = this;
    }
    bool d() {
        return fa->c[1] == this;
    }
    void rot() {
        node *y = fa;
        int f = d();
        y->setc(f,c[!f]);
        fa = y->fa;
        if(y->is) y->is=0,is=1;
        else fa->c[y->d()]=this;
        this->setc(!f,y);
        y->up();
    }
    void init(node *x,int _id,int _dep);
    void P();
    void splay();
    void up() ;
    void down(int k);
    void push();
    void debug();
}NODE[N],*null=NODE;
void node::init(node *x,int _id,int _dep)
{
    id = _id; nil = 0;
    ans = lz = key = inf; is = 1;
    max_dep = _dep; dep = _dep;
    c[0] = c[1]  = x;
}
void node::up()
{
    max_dep = max(c[0]->max_dep,c[1]->max_dep);
    max_dep = max(dep,max_dep);
    ans = inf;
    if(key != inf && key-2*dep < ans) ans = key - 2*dep;
    ans = min(ans,min(c[0]->ans,c[1]->ans));
}
void node::down(int k) 
{
    if(k < key) key = k;
    if(k < lz)  lz = k;
    if(k-2*max_dep < ans) ans = k-2*max_dep;
}
void node::push()
{
    if(lz != inf) {
        c[0]->down(lz);
        c[1]->down(lz);
        lz = inf;
    }
}
void node::P()
{
    if(!is) fa->P();
    push();
}
void node::splay() 
{
    P();
    while(!is) {
        if(fa->is)  rot();
        else if(fa->d()==d())fa->rot(),rot();
        else rot(),rot();
    }
    up();
}
void node::debug() 
{
    printf("now=%d lc=%d rc=%d ans=%d key=%d\n",id,c[0]->id,c[1]->id,ans,key);
    if(!c[0]->nil) c[0]->debug();
    if(!c[1]->nil) c[1]->debug();
}

node *access(node *u)
{
    node *v = null;
    for(;!u->nil;u=u->fa){
        u->splay();
        u->c[1]->is = 1;
        (u->c[1]=v)->is=0;
        u->up();
        v = u;
    }
    return v;
}
int head[N] , nxt[2*N], pnt[2*N], E, dep[N];
void add(int a,int b)
{
    pnt[E] = b;
    nxt[E] = head[a];
    head[a] = E++;
}
void dfs(int u,int f) 
{
    (NODE+u)->fa = NODE + f;
    dep[u] = dep[f] + 1;
    for(int i=head[u];~i;i=nxt[i])if(pnt[i]-f)dfs(pnt[i],u);
}
void init(int n)
{
    null->nil = 1; null->id = 0; null->ans = inf;
    for(int i = 1; i <= n; i++) NODE[i].init(null,i,dep[i]);
}
int main()
{
    int n, m, u, op;
    while(scanf("%d%d",&n,&m)!=EOF) {
        std::fill(head,head+1+n,-1);
        E = 0;
        for(int i = 1,a,b; i < n; i++) {
            scanf("%d%d",&a,&b);
            add(a,b); add(b,a);
        }
        dep[0]=-1,dfs(1,0);
 //       for(int i = 1; i <= n; i++) printf("dep[%d]=%d\n",i,dep[i]);puts("");
        init(n);
        access(NODE+1)->down(dep[1]);
  //      puts("debug");
        while(m--) {
            scanf("%d%d",&op,&u);
            if(op == 1) 
                access(NODE+u)->down(dep[u]);
            else 
                printf("%d\n",access(NODE+u)->ans + dep[u]);
            //(NODE+u)->splay();
            //(NODE+u)->debug();
        }
    }
    return 0;
}
