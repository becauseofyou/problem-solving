//tc is healthy, just do it
//求m个数不能在自己位置 n个数随便排的错排
//dp[i] 表示有i个数有限制的方案数 无限制的数始终是n个
//考虑第i个有限制的数的放法，要么放到之前的某个有限制的位置，这个就是错排
//要么放到无限制的位置上去，一共有n种放法

#include <bits/stdc++.h>
using namespace std;

class DerangementsDiv2 {
public:
    int count( int n, int m );
};

const int md = 1000000007;
int dp[55];

int DerangementsDiv2::count(int n, int m) {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[0] = 1LL * dp[0] * i % md;
    }
    dp[1] =  1LL * n * dp[0] % md;
    for (int i = 2; i <= m; i++) {
        dp[i] = 1LL * (i - 1) * (dp[i - 1] + dp[i - 2]) % md + 1LL * n * dp[i - 1] % md;
        dp[i] %= md;
    }
    return dp[m];
}
/*
 //容斥:枚举几个恰好在自己位置
int DerangementsDiv2::count(int n, int m) {
    vector <int> fac(n + m + 1);
    fac[0] = 1;
    for (int i = 1; i <= n + m; i++) {
        fac[i] = 1LL *  fac[i - 1] * i % md;
    }
    vector <vector <int> > bino (m + 1, vector <int> (m + 1, 0));
    bino[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        bino[i][0] = bino[i][i] = 1;
        for (int j = 1; j < i; j++) {
            bino[i][j] = (bino[i - 1][j] + bino[i - 1][j - 1]) % md;
        }
    }
    int ret = 0;
    for (int i = 0; i <= m; i++) {
        int tmp = 1LL * bino[m][i] * fac[(n + m - i)] % md;
        if (i & 1) {
            ret = ret - tmp;
        } else {
            ret = ret + tmp;
        }
        ret = (ret % md + md) % md;
    }
    return ret;
}*/

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
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
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
			int n                     = 0;
			int m                     = 2;
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int n                     = 2;
			int m                     = 1;
			int expected__            = 4;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int n                     = 1;
			int m                     = 2;
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int n                     = 3;
			int m                     = 5;
			int expected__            = 21234;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int n                     = 20;
			int m                     = 27;
			int expected__            = 88437461;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			int n                     = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int n                     = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			int n                     = ;
			int m                     = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DerangementsDiv2().count( n, m );
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
