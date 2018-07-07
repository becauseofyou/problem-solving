// tc is healthy, just do it
/*
 * 题意: 给你一个A数组 构造一个B 使得 A数组异或这个B之后得到的新数组能产生最多的顺序对
 *
 * 
 * 做法: 从高到低考虑 可以发现如果两个位置之前的高位都相同 
 * 现在开始不同 就不用考虑这两个数之后的位的比较了
 * 因此在同一层中可以分成若干组 每组中的数在之前的高位上都是相同的
 * 我们根据当前每组的顺序 逆序之和的大小来决定当前位的决策
 */
#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-11;
#define ALL(v) v.begin(),v.end()
#define SIZE(A) (int(A.size()))
#define LENGTH(A) (int(A.length()))
#define PII pair<int, int>
#define MP make_pair
#define fi first
#define se second
typedef long long int64;
template<class T> T sqr(const T &x) { return x*x; } 
template<class T> T lowbit(const T &x) { return (x^(x-1))&x; } 
template<class T> int countbit(const T &n) { return (n==0)?0:(1+countbit(n&(n-1))); } 
template<class T> void checkmin(T &a,const T &b) { if (b<a) a=b; } 
template<class T> void checkmax(T &a,const T &b) { if (b>a) a=b; }

class XorSequence {
public:
    long long getmax( int N, int sz, int A0, int A1, int P, int Q, int R ) ;
};

vector < vector<int> > team, nxt_team;

long long XorSequence::getmax(int N, int sz, int A0, int A1, int P, int Q, int R) {
    vector <int> num(sz);
    num[0] = A0; num[1] = A1;
    for (int i = 2; i < sz; i++) {
        num[i] = 1LL * num[i - 2] * P % N;
        num[i] = num[i] + 1LL * num[i - 1] * Q % N;
        num[i] %= N;
        num[i] = (num[i] + R) % N;
    }
    team.clear();
    vector <int> ta;
    for (int i = 0; i < sz; i++) {
        ta.emplace_back(i);
    }
    long long ret = 0;
    team.emplace_back(ta);
    for (int i = 30; i >= 0; i--) {
        nxt_team.clear();
        long long order = 0;
        long long inverse = 0;
        for (auto ta: team) {
            int ones = 0;
            long long order_pair = 0;
            long long inverse_pair = 0;
            vector <int> ta1, ta2;
            for (int j = 0; j < SIZE(ta); j++) {
                int id = ta[j];
                if (num[id] >> i & 1) {
                    order_pair += j - ones;
                    ta1.emplace_back(id);
                } else {
                    inverse_pair += ones;
                    ta2.emplace_back(id);
                }
                ones += (num[id] >> i & 1);
            }
            order += order_pair;
            inverse += inverse_pair;
            if (SIZE(ta1))
                nxt_team.emplace_back(ta1);
            if (SIZE(ta2))
                nxt_team.emplace_back(ta2);
        }
        ret += max(order, inverse);
        team = nxt_team;
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
                        int N                     = 4;
                        int sz                    = 6;
                        int A0                    = 3;
                        int A1                    = 2;
                        int P                     = 0;
                        int Q                     = 1;
                        int R                     = 3;
                        long long expected__      = 8LL;

                        clock_t start__           = clock();
                        long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 1: {
                        int N                     = 8;
                        int sz                    = 8;
                        int A0                    = 2;
                        int A1                    = 5;
                        int P                     = 3;
                        int Q                     = 1;
                        int R                     = 4;
                        long long expected__      = 13LL;

                        clock_t start__           = clock();
                        long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 2: {
                        int N                     = 8;
                        int sz                    = 7;
                        int A0                    = 3;
                        int A1                    = 0;
                        int P                     = 1;
                        int Q                     = 2;
                        int R                     = 4;
                        long long expected__      = 12LL;

                        clock_t start__           = clock();
                        long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 3: {
                        int N                     = 32;
                        int sz                    = 15;
                        int A0                    = 7;
                        int A1                    = 9;
                        int P                     = 11;
                        int Q                     = 2;
                        int R                     = 1;
                        long long expected__      = 60LL;

                        clock_t start__           = clock();
                        long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 4: {
                        int N                     = 131072;
                        int sz                    = 131072;
                        int A0                    = 7;
                        int A1                    = 7;
                        int P                     = 1;
                        int Q                     = 0;
                        int R                     = 0;
                        long long expected__      = 0LL;

                        clock_t start__           = clock();
                        long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 5: {
                        int N                     = 131072;
                        int sz                    = 131070;
                        int A0                    = 411;
                        int A1                    = 415;
                        int P                     = 398;
                        int Q                     = 463;
                        int R                     = 9191;
                        long long expected__      = 4302679760LL;

                        clock_t start__           = clock();
                        long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }

                    // custom cases

                    /*      case 6: {
                            int N                     = ;
                            int sz                    = ;
                            int A0                    = ;
                            int A1                    = ;
                            int P                     = ;
                            int Q                     = ;
                            int R                     = ;
                            long long expected__      = LL;

                            clock_t start__           = clock();
                            long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                            return verify_case( casenum, expected__, received__, clock()-start__ );
                            }*/
                    /*      case 7: {
                            int N                     = ;
                            int sz                    = ;
                            int A0                    = ;
                            int A1                    = ;
                            int P                     = ;
                            int Q                     = ;
                            int R                     = ;
                            long long expected__      = LL;

                            clock_t start__           = clock();
                            long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
                            return verify_case( casenum, expected__, received__, clock()-start__ );
                            }*/
                    /*      case 8: {
                            int N                     = ;
                            int sz                    = ;
                            int A0                    = ;
                            int A1                    = ;
                            int P                     = ;
                            int Q                     = ;
                            int R                     = ;
                            long long expected__      = LL;

                            clock_t start__           = clock();
                            long long received__      = XorSequence().getmax( N, sz, A0, A1, P, Q, R );
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
