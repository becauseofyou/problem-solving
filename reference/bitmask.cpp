
const int MAX_LOG = 20;
const int N = 1 << MAX_LOG;
int lowbit_id[N], Log[N];

void log_init() {
    Log[0] = -1;
    for (int i = 1; i < N; i++) {
        Log[i] = Log[i >> 1] + 1;
    }
    lowbit_id[0] = -1;
    for (int i = 1; i < N; i++) {
        lowbit_id[i] = Log[lowbit(i)];
    }
}
