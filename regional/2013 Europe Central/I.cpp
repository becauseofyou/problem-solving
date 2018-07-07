#pragma comment(linker, "/STACK:1000000000,1000000000")
#include <cstdlib>
#include <cmath>
#include <vector>
#include <functional>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
const int N = 10010;

struct Node;
Node* null;
int K;

struct Node {
    Node *c[2], *p;
    Node() {
        c[0] = c[1] = p = null;
        isRoot = sz;
    }
    Node(int _isRoot, int _sz, int _cnt, int _val) {
        c[0] = c[1] = p = null;
        isRoot = _isRoot;
        sz = _sz;
    }
    int isRoot, sz;
    int val;
    inline void setc(int d,Node *s) {
        c[d] = s;
        s->p = this;
    }
    inline bool d() {
        return p->c[1] == this;
    }
    void up() {
        sz = c[0]->sz + c[1]->sz + 1;
    }
    void clear() {
        sz = 1;
        isRoot = 0;
        c[0] = c[1] = p = null;
    }
}pool[N], *C ;

Node* idx[N];
Node* root;
void rot(Node *x) {
    Node *p = x->p;
    int f = x->d();
    std::swap(x->isRoot, p->isRoot);
    p->p->setc(p->d(), x);
    p->setc(f, x->c[!f]);
    x->setc(!f, p);
    p->up();
}

void splay(Node *x, Node *goal) {
    while(x->p != goal) {
        if(x->p->p == goal) {
            rot(x);
        } else {
            bool f = x->p->d();
            x->d() == f ? rot(x->p): rot(x);
            rot(x);
        }
    }
    x->up();
    if(goal == null) root = x;
}
void slect(int k, Node *goal) {
        Node *x = root;
        while(x->c[0]->sz + 1 != k) {
                if(k < x->c[0]->sz + 1) {
                        x = x->c[0];
                } else {
                        k -= x->c[0]->sz + 1;
                        x = x->c[1];
                }
        }
        splay(x, goal);
}
int a[N];
void build(Node *&x, int l, int r, Node *fa) {
        if(l > r)  {
                return ;
        }
        int m = (l + r) >> 1;
        x = new(C++) Node();
        x->p = fa;
        x->sz = 1;
        idx[a[m]] = x;
        x->val = a[m];
        build(x->c[0], l, m - 1, x);
        build(x->c[1], m + 1, r, x);
        x->up();
}
void debug(Node *x) {
        
    if(x->c[0] != null) debug(x->c[0]);
    printf("%d ", x->val);
//    printf("now : %d lson sz = %d val = %d\n",x, x->sz, x->val);
    if(x->c[1] != null) debug(x->c[1]);
}
int n;
std::vector<std::pair<int,int> > res;
void init() {
        res.clear();
        C = pool;
        null = new (C++) Node();
        root = new(C++) Node();
        root->isRoot = 1;
        root->setc(1, new(C++) Node());
        build(root->c[1]->c[0], 1, n, root->c[1]);
        root->c[1]->up(); root->up();
   //     debug(root);
   //     puts("");
}
// cut the number between L and R, and insert them after position p
void cut_insert(int L, int R, int p) {
    //    printf("%d %d %d\n", L, R, p);
        slect(L - 1, null);
        slect(R + 1, root);
        Node *stree = root->c[1]->c[0];
        root->c[1]->c[0] = null;
        slect(p, null);
        slect(p + 1, root);
        root->c[1]->setc(0, stree);
   //     debug(root);
   //     puts("");
}
void gao() {
        for(int i = 1; i <= n; i++) {
                splay(idx[i], null);
                int pos = idx[i]->c[0]->sz;
                while(pos != i) {
                   //     printf("i=%d pos=%d\n", i, pos);
                        int len = pos - i + 1;
                        cut_insert(pos - len/2 + 1 + 1, pos + 1, pos - len/2 * 2 + 1);
                        res.push_back(std::make_pair(pos - len/2*2 + 1, pos));
                        pos = pos - len / 2;
                }
     //           debug(root);
        }
}
int main() {
        int t;
        scanf("%d", &t);
        while(t--) {
                scanf("%d",&n);
                for(int i = 1; i <= n; i++) {
                        scanf("%d", &a[i]);
                }
                init();
                gao();
                printf("%d\n", res.size());
                for(int i = 0; i < res.size(); i++) {
                        printf("%d %d\n", res[i].first, res[i].second);
                }
        }
        return 0;
}

