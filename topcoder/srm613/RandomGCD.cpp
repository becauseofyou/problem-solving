// Paste me into the FileEdit configuration dialog
#include <set>
#include <map>
#include <ctime>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

class RandomGCD {
public:
   int countTuples( int N, int K, int low, int high ) ;
};
typedef long long lld;
const int N = 100010;
const int mod = 1000000007;
int mu[N], p[N], pn;
bool flag[N];
void init() {
    pn = 0;
    mu[1] = 1;
    for(int i = 2; i < N; i++) {
        if(!flag[i]) {
            p[pn ++ ] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < pn && i * p[j] < N; j++) {
            flag[i * p [j]] = true;
            if(i % p[j] == 0) {
                mu[i * p[j]] = 0;
                break;
            } else {
                mu[i * p[j]] = -mu[i];
            }
        }
    }
}
lld POW(lld a, lld b){
    lld ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
int RandomGCD::countTuples(int N, int K, int L, int R) {
    init();
    lld ret = (K >= L && K <= R);
    for(int beishu = K; beishu <= 100000; beishu += K) {
        int count_of_Kbeishu = R / beishu - (L - 1) / beishu;
        if(count_of_Kbeishu >= 0) {
            ret += 1LL * mu[beishu / K] * (POW(count_of_Kbeishu, N) - count_of_Kbeishu) % mod;
        }
        ret = (ret % mod + mod) % mod;
    }
    return (int) ret;
}
// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
    using std::string;
    using std::vector;
    int run_test_case(int);
    void run_test(int casenum = -1, bool quiet = false) {
        if (casenum != -1) {
            if (run_test_case(casenum) == -1 && !quiet) {
                std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
            }
            return;
        }

        int correct = 0, total = 0;
        for (int i=0;; ++i) {
            int x = run_test_case(i);
            if (x == -1) {
                if (i >= 100) break;
                continue;
            }
            correct += x;
            ++total;
        }

        if (total == 0) {
            std::cerr << "No test cases run." << std::endl;
        } else if (correct < total) {
            std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
        } else {
            std::cerr << "All " << total << " tests passed!" << std::endl;
        }
    }

    int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
        std::cerr << "Example " << casenum << "... "; 

        string verdict;
        vector<string> info;
        char buf[100];

        if (elapsed > CLOCKS_PER_SEC / 200) {
            std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
            info.push_back(buf);
        }

        if (expected == received) {
            verdict = "PASSED";
        } else {
            verdict = "FAILED";
        }

        std::cerr << verdict;
        if (!info.empty()) {
            std::cerr << " (";
            for (size_t i=0; i<info.size(); ++i) {
                if (i > 0) std::cerr << ", ";
                std::cerr << info[i];
            }
            std::cerr << ")";
        }
        std::cerr << std::endl;

        if (verdict == "FAILED") {
            std::cerr << "    Expected: " << expected << std::endl; 
            std::cerr << "    Received: " << received << std::endl; 
        }

        return verdict == "PASSED";
    }

    int run_test_case(int casenum__) {
        switch (casenum__) {
            case 0: {
                        int N                     = 2;
                        int K                     = 2;
                        int low                   = 2;
                        int high                  = 4;
                        int expected__            = 3;

                        std::clock_t start__      = std::clock();
                        int received__            = RandomGCD().countTuples(N, K, low, high);
                        return verify_case(casenum__, expected__, received__, clock()-start__);
                    }
            case 1: {
                        int N                     = 2;
                        int K                     = 100;
                        int low                   = 2;
                        int high                  = 4;
                        int expected__            = 0;

                        std::clock_t start__      = std::clock();
                        int received__            = RandomGCD().countTuples(N, K, low, high);
                        return verify_case(casenum__, expected__, received__, clock()-start__);
                    }
            case 2: {
                        int N                     = 1;
                        int K                     = 5;
                        int low                   = 5;
                        int high                  = 5;
                        int expected__            = 1;

                        std::clock_t start__      = std::clock();
                        int received__            = RandomGCD().countTuples(N, K, low, high);
                        return verify_case(casenum__, expected__, received__, clock()-start__);
                    }
            case 3: {
                        int N                     = 73824;
                        int K                     = 17347;
                        int low                   = 9293482;
                        int high                  = 9313482;
                        int expected__            = 0;

                        std::clock_t start__      = std::clock();
                        int received__            = RandomGCD().countTuples(N, K, low, high);
                        return verify_case(casenum__, expected__, received__, clock()-start__);
                    }
            case 4: {
                        int N                     = 222;
                        int K                     = 222;
                        int low                   = 222;
                        int high                  = 22222;
                        int expected__            = 339886855;

                        std::clock_t start__      = std::clock();
                        int received__            = RandomGCD().countTuples(N, K, low, high);
                        return verify_case(casenum__, expected__, received__, clock()-start__);
                    }

                    // custom cases

                    /*      case 5: {
                            int N                     = ;
                            int K                     = ;
                            int low                   = ;
                            int high                  = ;
                            int expected__            = ;

                            std::clock_t start__      = std::clock();
                            int received__            = RandomGCD().countTuples(N, K, low, high);
                            return verify_case(casenum__, expected__, received__, clock()-start__);
                            }*/
                    /*      case 6: {
                            int N                     = ;
                            int K                     = ;
                            int low                   = ;
                            int high                  = ;
                            int expected__            = ;

                            std::clock_t start__      = std::clock();
                            int received__            = RandomGCD().countTuples(N, K, low, high);
                            return verify_case(casenum__, expected__, received__, clock()-start__);
                            }*/
                    /*      case 7: {
                            int N                     = ;
                            int K                     = ;
                            int low                   = ;
                            int high                  = ;
                            int expected__            = ;

                            std::clock_t start__      = std::clock();
                            int received__            = RandomGCD().countTuples(N, K, low, high);
                            return verify_case(casenum__, expected__, received__, clock()-start__);
                            }*/
            default:
                    return -1;
        }
    }
}


#include <cstdlib>
int main(int argc, char *argv[]) {
    if (argc == 1) {
        moj_harness::run_test();
    } else {
        for (int i=1; i<argc; ++i)
            moj_harness::run_test(std::atoi(argv[i]));
    }
}
// END CUT HERE
