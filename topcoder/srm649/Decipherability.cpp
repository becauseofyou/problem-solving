// tc is healthy, just do it

#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-11;
#define ALL(v) v.begin(),v.end()
#define SIZE(A) (int(A.size()))
#define LENGTH(A) (int(A.length()))
#define FILL(A, x) memset(A, x, sizeof(A))
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

class Decipherability {
public:
    string check( string s, int K ) ;
};

int f[55][55];
int get_lcs(string a, string b) {
    int n = LENGTH(a);
    int m = LENGTH(b);
    FILL(f, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == a[j - 1]) {
                checkmax(f[i][j], f[i - 1][j - 1] + 1);
            }
            checkmax(f[i][j], f[i - 1][j]);
            checkmax(f[i][j], f[i][j - 1]);
        }
    }
    return f[n][m];
}

string Decipherability::check(string s, int K) {
    int n = LENGTH(s);
    // need to consider K's range ???
    // do it later

    if (K == n) {
        return "Certain";
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) if (s[i] == s[j]) {
            int lcs_suffix = get_lcs(s.substr(i + 1), s.substr(j + 1));
            int lcs_preffix = get_lcs(s.substr(0, i), s.substr(0, j));
            if (lcs_preffix + lcs_suffix + 1 >= n - K) {
                return "Uncertain";
            }
        }
    }
    return "Certain";
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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			string s                  = "snuke";
			int K                     = 2;
			string expected__         = "Certain";

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string s                  = "aba";
			int K                     = 1;
			string expected__         = "Certain";

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string s                  = "aba";
			int K                     = 2;
			string expected__         = "Uncertain";

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string s                  = "abcdabcd";
			int K                     = 3;
			string expected__         = "Certain";

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string s                  = "koukyoukoukokukikou";
			int K                     = 2;
			string expected__         = "Uncertain";

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			string s                  = "wolfsothe";
			int K                     = 8;
			string expected__         = "Uncertain";

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 6: {
			string s                  = "aa";
			int K                     = 2;
			string expected__         = "Certain";

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 7: {
			string s                  = ;
			int K                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			string s                  = ;
			int K                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 9: {
			string s                  = ;
			int K                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = Decipherability().check( s, K );
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
