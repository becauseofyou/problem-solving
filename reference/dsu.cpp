class dsu {
    public:
        vector<int> p;
        int n;
        vector< vector<int> > seq;

        dsu(int n) : n(n) {
            p.resize(n);
            iota(p.begin(), p.end(), 0);
            seq.resize(n);
            for (int i = 0; i < n; i++) {
                seq[i].push_back(i);
            }
        }

        inline int get(int x) {
            return (x == p[x] ? x : (p[x] = get(p[x])));
        }

        inline bool unite(int x, int y) {
            x = get(x);
            y = get(y);
            if (x != y) {
                p[x] = y;
                seq[y].insert(seq[y].end(), seq[x].begin(), seq[x].end());
                return true;
            }
            return false;
        }
};
