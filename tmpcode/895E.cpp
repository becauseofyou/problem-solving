#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;

struct segtree {
    struct node {
        // don't forget to set default value (used for leaves)
        // not necessarily neutral element!
        double sum;
        double mul, add;
        node() {
            sum = 0;
            mul = 1;
            add = 0;
        }
        void apply_mul(int l, int r, double v) {
            mul *= v;
            add *= v;
            sum *= v;
        }

        void apply_add(int l, int r, double v) {
            add += v;
            sum += v * (r - l + 1);
        }
    };

    inline void push(int x, int l, int r) {
        int m = (l + r) >> 1;
        int z = x + ((m - l + 1) << 1);
        // push from x into (x + 1) and z
        if (fabs(tree[x].mul - 1) > eps) {
            tree[x + 1].apply_mul(l, m, tree[x].mul);
            tree[z].apply_mul(m + 1, r, tree[x].mul);
            tree[x].mul = 1;
        }
        if (fabs(tree[x].add) > eps) {
            tree[x + 1].apply_add(l, m, tree[x].add);
            tree[z].apply_add(m + 1, r, tree[x].add);
            tree[x].add = 0;
        }
    }

    node unite(const node &a, const node &b) const {
        node res;
        res.sum = a.sum + b.sum;
        return res;
    }


    inline void pull(int x, int z) {
        tree[x] = unite(tree[x + 1], tree[z]);
    }

    int n;
    vector<node> tree;

    void build(int x, int l, int r, const vector <double> &v) {
        if (l == r) {
            tree[x].sum = v[l];
            return;
        }
        int m = (l + r) >> 1;
        int z = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(z, m + 1, r, v);
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

    void modify_mul(int x, int l, int r, int ll, int rr, double v) {
        if (ll <= l && r <= rr) {
            tree[x].apply_mul(l, r, v);
            return;
        }
        int m = (l + r) >> 1;
        int z = x + ((m - l + 1) << 1);
        push(x, l, r);
        if (ll <= m) {
            modify_mul(x + 1, l, m, ll, rr, v);
        }
        if (rr > m) {
            modify_mul(z, m + 1, r, ll, rr, v);
        }
        pull(x, z);
    }

    void modify_add(int x, int l, int r, int ll, int rr, double v) {
        if (ll <= l && r <= rr) {
            tree[x].apply_add(l, r, v);
            return;
        }
        int m = (l + r) >> 1;
        int z = x + ((m - l + 1) << 1);
        push(x, l, r);
        if (ll <= m) {
            modify_add(x + 1, l, m, ll, rr, v);
        }
        if (rr > m) {
            modify_add(z, m + 1, r, ll, rr, v);
        }
        pull(x, z);
    }

    segtree () {
    }

    template <typename M>
        segtree(const vector<M> &v) {
            n = v.size();
            assert(n > 0);
            tree.resize(2 * n - 1);
            build(0, 0, n - 1, v);
        }

    node get(int ll, int rr) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return get(0, 0, n - 1, ll, rr);
    }

    void modify_mul(int ll, int rr, double v) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        modify_mul(0, 0, n - 1, ll, rr, v);
    }

    void modify_add(int ll, int rr, double v) {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        modify_add(0, 0, n - 1, ll, rr, v);
    }
};
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    vector <double> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &a[i]);
    }
    segtree st(a);
    while (q--) {
        int tp, l1, r1, l2, r2, l, r;
        scanf("%d", &tp);
        if (tp == 1) {
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            l1--; r1--; l2--; r2--;
            int lena = r1 - l1 + 1;
            int lenb = r2 - l2 + 1;
            double suma = st.get(l1, r1).sum;
            double sumb = st.get(l2, r2).sum;

            st.modify_mul(l1, r1, 1.0 * (lena - 1) / lena);
            st.modify_add(l1, r1, sumb / lena / lenb);

            st.modify_mul(l2, r2, 1.0 * (lenb - 1) / lenb);
            st.modify_add(l2, r2, suma / lena / lenb);
        } else {
            scanf("%d%d", &l, &r);
            l--; r--;
            printf("%.8f\n", st.get(l, r).sum);
        }
    }
    return 0;
}
