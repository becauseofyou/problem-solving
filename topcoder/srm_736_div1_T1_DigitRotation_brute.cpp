//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

template<class T> void checkmin(T &a,const T &b) { if (b<a) a=b; } 
template<class T> void checkmax(T &a,const T &b) { if (b>a) a=b; }

const int md = 998244353;
class DigitRotation {
public:
    int sumRotations( string X ) ;
};

inline void add(int &x, int y) {
    x += y;
    if (x >= md) {
        x -= md;
    }
}

int num[555][555];
int DigitRotation::sumRotations(string X) {
    int n = X.size();
    vector <int> p(n + 1);
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = 1LL * p[i - 1] * 10 % md;
    }
    for (int i = 0; i < n; i++) {
        int a = 0;
        for (int j = i + 1; j <= n; j++) {
            a = 1LL*a*10%md;
            add(a, X[j - 1]-'0');
            num[i][j] = a;
        }
    }

    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) if(!(X[k]=='0' && i==0)){
                int a = 1LL*num[0][i] * 10%md;
                add(a, X[k]-'0');
                int b = 1LL*a*p[j - i - 1]%md;
                add(b, num[i + 1][j]);
                int c = 1LL*b * 10%md;
                add(c, X[i] - '0');
                int d = 1LL*c * p[k - j - 1]%md;
                add(d, num[j + 1][k]);
                int e = 1LL*d * 10%md;
                add(e, X[j] - '0');
                int f = 1LL*e * p[n - k - 1]%md;
                add(f, num[k + 1][n]);
                add(ret, f);
            }
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
			string X                  = "123";
			int expected__            = 312;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string X                  = "3570";
			int expected__            = 10407;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string X                  = "5545";
			int expected__            = 21208;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string X                  = "1283749218734901238749213847902";
			int expected__            = 867286291;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string X                  = "4";
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			string X                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string X                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			string X                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = DigitRotation().sumRotations( X );
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
