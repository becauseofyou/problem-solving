//tc is healthy, just do it
//{10} 2  answer is 5
//{10} -> used one split {4 6}  -> used two{3, 3, 3} -> {2, 2, 2} -> {1, 1, 1} -> {0, 0, 0}
//{10} -> used one split {5,5}  -> used two{4, 2, 3} -> {3, 1, 2} -> {2, 0, 1} -> {1, 0, 0} -> {0, 0, 0}
//binary search the answer MIDDLE, and judge for each sequence whether we can remove them all in MIDDLE time.
//obviously the SPLIT oprtation is very good, but the time to used it is limited, so when write check funcion 
//we need to calc the minimum SPLIT times we can use to remove a sequence in MIDDLE time limit,
//we can use another binary search to do it
//
// so the key point is to write the function
// bool can(int count_splits, int value_to_remove, int time_limit)
//
//
//first I was thinking a greedy method naively that I must make x / 2 in every split,
//it doesn't work in the up case {10} 2
//the better way is don't care about the numbers created in the process, because the total sum never change
//and we want them to be as equal as possible
//so just calc the max number of carts we can make, and then distribute the sum to them.
//a new binary search way from kmjp
//https://community.topcoder.com/tc?module=ProblemDetail&rd=16313&pm=13656
#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-11;
typedef long long int64;

#define rep(i, n) for (int i = 0; i < n; i++)

#define ALL(v) v.begin(),v.end()
#define SIZE(A) (int(A.size()))
#define LENGTH(A) (int(A.length()))
#define FILL(A, x) memset(A, x, sizeof(A))

#define pii pair<int, int>
#define pLL pair<int64, int64>
#define mp make_pair
#define fi first
#define se second
#define pb push_back

#define iread(x) scanf("%d", &x)
#define iiread(x, y) scanf("%d%d", &x, &y) 
#define sread(s) scanf("%s", s);
#define ssread(s, t) scanf("%s%s", s, t)

template<class T> T sqr(const T &x) { return x*x; } 
template<class T> T lowbit(const T &x) { return (x^(x-1))&x; } 
template<class T> int countbit(const T &n) { return (n==0)?0:(1+countbit(n&(n-1))); } 
template<class T> void checkmin(T &a,const T &b) { if (b<a) a=b; } 
template<class T> void checkmax(T &a,const T &b) { if (b>a) a=b; }

class CartInSupermarket {
public:
    int calcmin( vector <int> a, int b ) ;
};


bool can(int count_splits, int x, int time_limit) {
    int time = 0;
    int count_parts = 1;
    while(count_parts <= count_splits) {
        if (count_parts >= x) {
            return time + 1 <= time_limit;
        }
        count_splits -= count_parts;
        count_parts *= 2;
        ++time;
    }
    // in this turn, (count_parts-count_splits) sequences remove on cart, 
    // count_splits sequences split into two sequences
    x = x - (count_parts - count_splits);
    count_parts += count_splits;
    return (time + 1) + (x + count_parts - 1) / count_parts <= time_limit;
}

bool judge (int time_limit, vector <int> a, int splits_limit) {
    int remain_splits = splits_limit;
    for (int v: a) {
        int best = (1LL<<31) - 1;
        for (int i = 30; i >= 0; i--) if (can(best  - (1 << i), v, time_limit)) {
            best -= 1 << i;
        }
        if (remain_splits < best) return false;
        remain_splits -= best;
    }
    return true;
}

int CartInSupermarket::calcmin(vector <int> a, int b) {
    cout << judge(1, a, b);
    int ret = (1LL<<31) - 1;
    for (int i = 30; i >= 0; i--) {
        if (judge(ret - (1 << i), a, b)) {
            ret -= 1 << i;
        }
    }
    return ret;
}

// BEGIN CUT HERE
namespace moj_harness {
    int run_test_case(int);
    void run_test(int casecount = -1, bool quiet = false) {
        if ( casecount != -1 ) {
            if ( run_test_case( casecount ) == -1 && !quiet )
                cerr << "Illegal input! Test case " << casecount << " does not exist." << endl;
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

    int verify_case(int casecount, const int &expected, const int &received, clock_t elapsed) { 
        cerr << "Example " << casecount << "... "; 

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

    int run_test_case( int casecount ) {
        switch( casecount ) {
            case 0: {
                        int a[]                   = {8};
                        int b                     = 3;
                        int expected__            = 4;

                        clock_t start__           = clock();
                        int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                        return verify_case( casecount, expected__, received__, clock()-start__ );
                    }
            case 1: {
                        int a[]                   = {6,6,5};
                        int b                     = 3;
                        int expected__            = 4;

                        clock_t start__           = clock();
                        int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                        return verify_case( casecount, expected__, received__, clock()-start__ );
                    }
            case 2: {
                        int a[]                   = {12,5,6,2,6,8};
                        int b                     = 4;
                        int expected__            = 6;

                        clock_t start__           = clock();
                        int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                        return verify_case( casecount, expected__, received__, clock()-start__ );
                    }
            case 3: {
                        int a[]                   = {15,20,11,13,18,24,25,21,22,10,15,14,19};
                        int b                     = 0;
                        int expected__            = 25;

                        clock_t start__           = clock();
                        int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                        return verify_case( casecount, expected__, received__, clock()-start__ );
                    }
            case 4: {
                        int a[]                   = {671122748,846444748,84701624,608579554,672060899,967957440,31438849,734849843,376589643,904285209 ,80693344,211737743,85405464,444633541,293184188,935462519,146753109,972886045,496631016,601669536 ,257574086,958464570,6294570,546189534,668105964,601197313,784337929,921840143,70408284,722040626 ,253400894,56411549,811940644,152086353,122638884,776352066,118932182,177589709,538122558,127914469 ,523761221,290027568,734517444,819458123,699130727,784698122,810265337,283326309,593596316,368671876};
                        int b                     = 6478;
                        int expected__            = 3805054;

                        clock_t start__           = clock();
                        int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                        return verify_case( casecount, expected__, received__, clock()-start__ );
                    }

                    // custom cases

                          case 5: {
                            int a[]                   = {4,5,5};
                            int b                     = 2;
                            int expected__            = 4;

                            clock_t start__           = clock();
                            int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                            return verify_case( casecount, expected__, received__, clock()-start__ );
                            }
                          case 6: {
                            int a[]                   = {1};
                            int b                     = 0;
                            int expected__            = 1;

                            clock_t start__           = clock();
                            int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                            return verify_case( casecount, expected__, received__, clock()-start__ );
                            }
                    /*      case 7: {
                            int a[]                   = ;
                            int b                     = ;
                            int expected__            = ;

                            clock_t start__           = clock();
                            int received__            = CartInSupermarket().calcmin( vector <int>( a, a + ( sizeof a / sizeof a[0] ) ), b );
                            return verify_case( casecount, expected__, received__, clock()-start__ );
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
