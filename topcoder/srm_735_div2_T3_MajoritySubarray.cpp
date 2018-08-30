//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

template<class T> void checkmin(T &a,const T &b) { if (b<a) a=b; } 
template<class T> void checkmax(T &a,const T &b) { if (b>a) a=b; }

class MajoritySubarray {
    public:
        long long getCount( int n, int seed, int m ) ;
};
//求多少子区间存在一个众数的数量大于区间长度的一半
/*
   (sum[i][0] -sum[j][0]) > (i - j) / 2
   2*(si -sj) > i - j;

   2si-i > 2sj-j;
   */
//n <= 1e5
template <typename T>
class fenwick {
    public:
        vector<T> fenw;
        int n;

        void init(int n) {
            this->n = n + 100010;
            fenw.resize(n + 100010);
        }

        void modify(int x, T v) {
            x += 100010;
            while (x < n) {
                fenw[x] += v;
                x |= (x + 1);
            }
        }

        T get(int x) {
            x += 100010;
            T v = 0;
            while (x >= 0) {
                v += fenw[x];
                x = (x & (x + 1)) - 1;
            }
            return v;
        }
};
int cnt[100010][50];
fenwick <int> bit[50];
long long MajoritySubarray::getCount(int n, int seed, int m) {
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = (seed >> 16) % m;
        seed = (1LL*seed * 1103515245 + 12345) % (1LL<<31);
    }
    for (int i = 0; i < 50; i++) {
        bit[i].init(3 * n + 1);
        bit[i].modify(0, 1);
    }
    long long ret = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 50; j++) {
            cnt[i][j] = cnt[i - 1][j];
        }
        cnt[i][a[i]]++;
        for (int j = 0; j < 50; j++) if(cnt[i][j]){
            ret += bit[j].get(2 * cnt[i][j] - i - 1);
        }
        for (int j = 0; j < 50; j++) {
            bit[j].modify(2 * cnt[i][j] - i, 1);
        }
    }
    return ret;
}

// BEGIN CUT HERE
namespace moj_harness {
    int run_test_case(int);
    void run_test(int casenum = -1, bool quiet = false) {
        if ( casenum != -1 ) {
            if ( run_test_case( casenum ) == -1 && !quiet )
                cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
            return;
        }

        int correct = 0, total = 0;
        for ( int i=0;; ++i ) {
            int x = run_test_case(i);
            if ( x == -1 ) {
                if ( i >= 100 ) break;
                continue;
            }
            correct += x;
            ++total;
        }

        if ( total == 0 ) {
            cerr << "No test cases run." << endl;
        } else if ( correct < total ) {
            cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
        } else {
            cerr << "All " << total << " tests passed!" << endl;
        }
    }

    int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
        cerr << "Example " << casenum << "... "; 

        string verdict;
        vector<string> info;
        char buf[100];

        if (elapsed > CLOCKS_PER_SEC / 200) {
            sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
            info.push_back(buf);
        }

        if ( expected == received ) {
            verdict = "PASSED";
        } else {
            verdict = "FAILED";
        }

        cerr << verdict;
        if (!info.empty()) {
            cerr << " (";
            for (int i=0; i<(int)info.size(); ++i) {
                if (i > 0) cerr << ", ";
                cerr << info[i];
            }
            cerr << ")";
        }
        cerr << endl;

        if (verdict == "FAILED") {
            cerr << "    Expected: " << expected << endl; 
            cerr << "    Received: " << received << endl; 
        }

        return verdict == "PASSED";
    }

    int run_test_case( int casenum ) {
        switch( casenum ) {
        
            case 0: {
                        int n                     = 5;
                        int seed                  = 200;
                        int m                     = 5;
                        long long expected__      = 8LL;

                        clock_t start__           = clock();
                        long long received__      = MajoritySubarray().getCount( n, seed, m );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 1: {
                        int n                     = 10;
                        int seed                  = 15;
                        int m                     = 3;
                        long long expected__      = 23LL;

                        clock_t start__           = clock();
                        long long received__      = MajoritySubarray().getCount( n, seed, m );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 2: {
                        int n                     = 8;
                        int seed                  = 12345678;
                        int m                     = 1;
                        long long expected__      = 36LL;

                        clock_t start__           = clock();
                        long long received__      = MajoritySubarray().getCount( n, seed, m );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 3: {
                        int n                     = 27;
                        int seed                  = 541;
                        int m                     = 50;
                        long long expected__      = 27LL;

                        clock_t start__           = clock();
                        long long received__      = MajoritySubarray().getCount( n, seed, m );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }

                    // custom cases

                    /*      case 4: {
                            int n                     = ;
                            int seed                  = ;
                            int m                     = ;
                            long long expected__      = LL;

                            clock_t start__           = clock();
                            long long received__      = MajoritySubarray().getCount( n, seed, m );
                            return verify_case( casenum, expected__, received__, clock()-start__ );
                            }*/
                    /*      case 5: {
                            int n                     = ;
                            int seed                  = ;
                            int m                     = ;
                            long long expected__      = LL;

                            clock_t start__           = clock();
                            long long received__      = MajoritySubarray().getCount( n, seed, m );
                            return verify_case( casenum, expected__, received__, clock()-start__ );
                            }*/
                    /*      case 6: {
                            int n                     = ;
                            int seed                  = ;
                            int m                     = ;
                            long long expected__      = LL;

                            clock_t start__           = clock();
                            long long received__      = MajoritySubarray().getCount( n, seed, m );
                            return verify_case( casenum, expected__, received__, clock()-start__ );
                            }*/
            default:
                    return -1;
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        moj_harness::run_test();
    } else {
        for (int i=1; i<argc; ++i)
            moj_harness::run_test(atoi(argv[i]));
    }
}
// END CUT HERE
