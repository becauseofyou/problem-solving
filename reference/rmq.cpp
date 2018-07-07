
namespace rmq {
    const int MAX_LOG = 23;
    int b[MAX_LOG][N], Log[N];

    void rmq_init(int a[], int n) {
        Log[0] = -1;
        for (int i = 1; i < N; i++) {
            Log[i] = Log[i >> 1] + 1;
        }
        for (int i = 0; i < n; i++) {
            b[0][i] = i;
        }
        for (int i = 1; i < MAX_LOG; i++) {
            int limit = n - (1 << i);
            for (int j = 0; j <= limit; j++) {
                if (a[b[i - 1][j]] < a[b[i - 1][j + (1 << i >> 1)]]) {
                    b[i][j] = b[i - 1][j];
                } else {
                    b[i][j] = b[i - 1][j + (1 << i >> 1)];
                }
            }
        }
    }

    int get_minimum(int a[], int l, int r) {
        int m = Log[r - l + 1];
        return std::min(a[b[m][l]], a[b[m][r - (1 << m) + 1]]);
    }

    int get_minimum_position(int a[], int l, int r) {
        int m = Log[r - l + 1];
        return a[b[m][l]] < a[b[m][r - (1 << m) + 1]] ? b[m][l] : b[m][r - (1 << m) + 1];
    }
}