#include <bits/stdc++.h>
using namespace std;

struct segtree {
    struct node {
        // don't forget to set default value (used for leaves)
        // not necessarily neutral element!
        int sum;
        int lazy;
        node() {
            sum = 0;
            lazy = 0;
        }
        void apply(int l, int r, int v) {
            lazy += v;
            sum += (r - l + 1) * v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        res.sum = a.sum + b.sum;
        return res;
    }

    inline void push(int x, int l, int r) {
        int m = (l + r) >> 1;
        int z = x + ((m - l + 1) << 1);
        // push from x into (x + 1) and z
        if (tree[x].lazy != 0) {
            tree[x + 1].apply(l, m, tree[x].lazy);
            tree[z].apply(m + 1, r, tree[x].lazy);
            tree[x].lazy = 0;
        }
    }

    inline void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
    }

    int n;
    vector<node> tree;

    void build(int x, int l, int r) {
        if (l == r) {
            return;
        }
        int m = (l + r) >> 1;
        int z = x + ((m - l + 1) << 1);
        build(x + 1, l, m);
        build(z, m + 1, r);
        pull(x, z);
    }

    node get(int x, int l, int r, int ll, int rr) {
        if (ll <= l && r <= rr) {
            return tree[x];
        }
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        push(x, l, r);
        node res;
        if (rr <= y) {
            res = get(x + 1, l, y, ll, rr);
        } else {
            if (ll > y) {
                res = get(z, y + 1, r, ll, rr);
            } else {
                res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
            }
        }
        pull(x, z);
        return res;
    }

    void modify(int x, int l, int r, int ll, int rr, int v) {
        if (ll <= l && r <= rr) {
            tree[x].apply(l, r, v);
            return;
        }
        int m = (l + r) >> 1;
        int z = x + ((m - l + 1) << 1);
        push(x, l, r);
        if (ll <= m) {
            modify(x + 1, l, m, ll, rr, v);
        }
        if (rr > m) {
            modify(z, m + 1, r, ll, rr, v);
        }
        pull(x, z);
    }

    segtree () {
    }
    segtree(int n) : n(n) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }

    void init (int n) {
        this->n = n;
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }

    template <typename M>
        segtree(const vector<M> &v) {
            n = v.size();
            assert(n > 0);
            tree.resize(2 * n - 1);
            build(0, 0, n - 1, v);
        }

    int get(int ll, int rr) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return get(0, 0, n - 1, ll, rr).sum;
    }

    void modify(int ll, int rr, int v) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        modify(0, 0, n - 1, ll, rr, v);
    }
};
int main() {
    vector <segtree> st(100000); //开100000颗线段树
    st[0].init(10); //建树 0~9区间
    st[0].modify(0, 9, 1);
    st[0].modify(0, 5, 2); //成段更新
    cout << st[0].get(0, 3) << endl; //测试
    return 0;
}
