template <typename T>
class fenwick {
    public:
        vector<T> fenw;
        int n;

        fenwick(int n) : n (n) {
            fenw.resize(n);
        }

        void modify(int x, T v) {
            while (x < n) {
                fenw[x] += v;
                x |= (x + 1);
            }
        }

        T get(int x) {
            T v = 0;
            while (x >= 0) {
                v += fenw[x];
                x = (x & (x + 1)) - 1;
            }
            return v;
        }
};
