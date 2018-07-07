//tc is healthy, just do it
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

class MulticoreProcessing {
public:
    long long fastestTime( long long jobLength, int corePenalty, vector <int> speed, vector <int> cores ) ;
};

/*The function may look like this, ternary search may not work, check [mid-10, mid+10] worked;
 * ---                             -----
 *                     -------
 *     ----- --------
 *          -
 *
 * calc the Derivative of y = L / (x * speed) + (x - 1) / penalty
 * when x = sqrt( L / speed / penalty ), y is minimum
 */
int64 calc (int64 jobLength, int64 x, int64 speed, int64 penalty) {
    return (jobLength + (speed * x) - 1) / (speed * x) + (x - 1) *penalty;
}

double calc2 (int64 jobLength, double x, int64 speed, int64 penalty) {
    return 1.0 * jobLength  / (speed * x) + (x - 1) *penalty;
}
long long MulticoreProcessing::fastestTime(long long jobLength, int corePenalty, vector <int> speed, vector <int> cores) {
    int64 ret = (int64) 2e18;
    int n = SIZE(speed);
    rep (i, n) {
        int best = -1;
        if (corePenalty) {
            best = (int64)sqrt(jobLength / (1LL * speed[i] * corePenalty) );
        } else {
            best = cores[i];
        }
        if (best > cores[i]) {
            best = cores[i];
        }
        for (int j = max(best - 10, 1); j <= min(cores[i], best + 10); j++) {
            checkmin(ret, calc(jobLength, j, speed[i], corePenalty));
        }
    }
    {
        int64 tmp = numeric_limits<long long> ::max();
        rep (i, n) {
            double l = 1, r = cores[i];
            int step = 100;
            double best;
            while (step --) {
                double mid = (l + r) * 0.5;
                double midmid = (mid + r) * 0.5;
                double  mv = calc2(jobLength, mid, speed[i], corePenalty);
                double  mmv = calc2(jobLength, midmid, speed[i], corePenalty);
                best = mid;
                if (mv < mmv) {
                    r = midmid;
                } else {
                    l = mid;
                }
            }
            int64 pos = best;
            for (int j = pos - 10; j <= pos + 10; j++) {
                if (j >= 1 && j <= cores[i]) {
                    checkmin(tmp, calc(jobLength, j, speed[i], corePenalty));
                }
            }
        }
        return tmp;
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
			long long jobLength       = 2000LL;
			int corePenalty           = 5;
			int speed[]               = {40,20};
			int cores[]               = {2,4};
			long long expected__      = 30LL;

			clock_t start__           = clock();
			long long received__      = MulticoreProcessing().fastestTime( jobLength, corePenalty, vector <int>( speed, speed + ( sizeof speed / sizeof speed[0] ) ), vector <int>( cores, cores + ( sizeof cores / sizeof cores[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			long long jobLength       = 2000LL;
			int corePenalty           = 5;
			int speed[]               = {10,20};
			int cores[]               = {2,4};
			long long expected__      = 40LL;

			clock_t start__           = clock();
			long long received__      = MulticoreProcessing().fastestTime( jobLength, corePenalty, vector <int>( speed, speed + ( sizeof speed / sizeof speed[0] ) ), vector <int>( cores, cores + ( sizeof cores / sizeof cores[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			long long jobLength       = 1000LL;
			int corePenalty           = 0;
			int speed[]               = {10};
			int cores[]               = {3};
			long long expected__      = 34LL;

			clock_t start__           = clock();
			long long received__      = MulticoreProcessing().fastestTime( jobLength, corePenalty, vector <int>( speed, speed + ( sizeof speed / sizeof speed[0] ) ), vector <int>( cores, cores + ( sizeof cores / sizeof cores[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			long long jobLength       = 10000LL;
			int corePenalty           = 5;
			int speed[]               = {39,37,44};
			int cores[]               = {8,16,6};
			long long expected__      = 63LL;

			clock_t start__           = clock();
			long long received__      = MulticoreProcessing().fastestTime( jobLength, corePenalty, vector <int>( speed, speed + ( sizeof speed / sizeof speed[0] ) ), vector <int>( cores, cores + ( sizeof cores / sizeof cores[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

     case 4: {
			long long jobLength       = 10000000000LL;
			int corePenalty           = 1;
			int speed[]               = {1};
			int cores[]               = {1000000000};
			long long expected__      = 199999LL;

			clock_t start__           = clock();
			long long received__      = MulticoreProcessing().fastestTime( jobLength, corePenalty, vector <int>( speed, speed + ( sizeof speed / sizeof speed[0] ) ), vector <int>( cores, cores + ( sizeof cores / sizeof cores[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
      case 5: {
			long long jobLength       =1000000000000000000LL;
			int corePenalty           = 123;
			int speed[]               ={40, 30, 25} ;
			int cores[]               = {10, 12, 4};
			long long expected__      =2500000000001107LL;

			clock_t start__           = clock();
			long long received__      = MulticoreProcessing().fastestTime( jobLength, corePenalty, vector <int>( speed, speed + ( sizeof speed / sizeof speed[0] ) ), vector <int>( cores, cores + ( sizeof cores / sizeof cores[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
/*      case 6: {
			long long jobLength       = LL;
			int corePenalty           = ;
			int speed[]               = ;
			int cores[]               = ;
			long long expected__      = LL;

			clock_t start__           = clock();
			long long received__      = MulticoreProcessing().fastestTime( jobLength, corePenalty, vector <int>( speed, speed + ( sizeof speed / sizeof speed[0] ) ), vector <int>( cores, cores + ( sizeof cores / sizeof cores[0] ) ) );
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
