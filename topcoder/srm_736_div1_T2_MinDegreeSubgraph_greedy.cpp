//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

template<class T> void checkmin(T &a,const T &b) { if (b<a) a=b; } 
template<class T> void checkmax(T &a,const T &b) { if (b>a) a=b; }

class MinDegreeSubgraph {
public:
    string exists( int n, long long m, int k ) ;
};
//求最少需要多少边使得无论怎么建图都能产生一个k个点的完全子图
//那就是往最差的情况去建，让点度都集中于一些点
//从前k-1个点往后面的每个点都连边
//前面k-1个点的度都是n-1,剩下的点的度都是k - 1
//再增加一条第k-1个点到第k个点的边即可产生完全图
//数量为:(n-1) + (n-2) + ... + (n - (k- 1)) + 1
bool all(int n, long long m, int k) {
    return k <= n - 1 && m >= (2LL*n-k) * (k - 1) / 2 + 1;
}

bool some(int n, long long m, int k) {
    return k <= n - 1 && m >= 1LL * k * (k + 1) / 2;
}


string MinDegreeSubgraph::exists(int n, long long m, int k) {
    if (all(n, m, k)) {
        return "ALL";
    } else if(some(n, m , k)) {
        return "SOME";
    } else {
        return "NONE";
    }
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
			int n                     = 3;
			long long m               = 3LL;
			int k                     = 2;
			string expected__         = "ALL";

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int n                     = 4;
			long long m               = 3LL;
			int k                     = 2;
			string expected__         = "SOME";

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int n                     = 6;
			long long m               = 10LL;
			int k                     = 3;
			string expected__         = "ALL";

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int n                     = 6;
			long long m               = 15LL;
			int k                     = 4;
			string expected__         = "ALL";

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int n                     = 17;
			long long m               = 53LL;
			int k                     = 11;
			string expected__         = "NONE";

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

      case 5: {
			int n                     = 10000;
			long long m               = 5LL;
			int k                     = 3;
			string expected__         = "NONE";

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
/*      case 6: {
			int n                     = ;
			long long m               = LL;
			int k                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			int n                     = ;
			long long m               = LL;
			int k                     = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = MinDegreeSubgraph().exists( n, m, k );
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
