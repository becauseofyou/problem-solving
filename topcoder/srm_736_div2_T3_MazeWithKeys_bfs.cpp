//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

template<class T> void checkmin(T &a,const T &b) { if (b<a) a=b; } 
template<class T> void checkmax(T &a,const T &b) { if (b>a) a=b; }

class MazeWithKeys {
public:
    int startingPoints( vector <string> a ) ;
};

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, m;
bool vis[55][55];
vector <string> mp;
int door[26][2];
int key[26];

bool bfs(int i, int j, bool cross_door) {
    memset(vis, false, sizeof(vis));
    memset(door, -1, sizeof(door));
    memset(key, -1, sizeof(key));
    queue <pair<int,int> > q;
    q.push(make_pair(i, j));
    vis[i][j] = true;
    while (!q.empty()) {
        pair<int, int> fr = q.front();
        q.pop();
        int x = fr.first;
        int y = fr.second;
        for (int i = 0; i < 4; i++) {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m) {
                continue;
            }
            if (vis[tx][ty] || mp[tx][ty] == '#') {
                continue;
            }
            if (mp[tx][ty] == '*') {
                return true;
            }
            if (mp[tx][ty] == '.') {
                vis[tx][ty] = true;
                q.push(make_pair(tx, ty));
            } else {
                if (mp[tx][ty] >= 'A' && mp[tx][ty] <= 'Z') {
                    int id = mp[tx][ty] - 'A';
                    door[id][0] = tx;
                    door[id][1] = ty;
                    if (cross_door && key[id] != -1) {
                        vis[tx][ty] = true;
                        q.push(make_pair(tx, ty));
                    }
                }
                if (mp[tx][ty] >= 'a' && mp[tx][ty] <= 'z') {
                    int id = mp[tx][ty] - 'a';
                    vis[tx][ty] = true;
                    q.push(make_pair(tx, ty));
                    key[id] = 1;
                    if (cross_door && door[id][0] != -1) {
                        vis[door[id][0]][door[id][1]] = true;
                        q.push(make_pair(door[id][0], door[id][1]));
                    }
                }
            }
        }
    }
    return false;
}

int MazeWithKeys::startingPoints(vector <string> a) {
    mp = a;
    n = (int)a.size();
    m = (int)a[0].length();
    int ret = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) if(a[i][j] == '.') {
            if (bfs(i, j, 1) && !bfs(i, j, 0)) {
                ret++;
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
                        string a[]                = {"...#.A.",  ".#B#.#.",  ".#.#.#.",  ".#.#.#.",  ".#b#.#.",  "a#...#*"} ;
                        int expected__            = 10;

                        clock_t start__           = clock();
                        int received__            = MazeWithKeys().startingPoints( vector <string>( a, a + ( sizeof a / sizeof a[0] ) ) );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 1: {
                        string a[]                = {"..*",  ".a.",  "A.."} ;
                        int expected__            = 0;

                        clock_t start__           = clock();
                        int received__            = MazeWithKeys().startingPoints( vector <string>( a, a + ( sizeof a / sizeof a[0] ) ) );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 2: {
                        string a[]                = {".A*C.",  ".#B#.",  ".#.#.",  "a..b."} ;
                        int expected__            = 10;

                        clock_t start__           = clock();
                        int received__            = MazeWithKeys().startingPoints( vector <string>( a, a + ( sizeof a / sizeof a[0] ) ) );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }
            case 3: {
                        string a[]                = {"a#a#*",  "#..#.",  "a..A."} ;
                        int expected__            = 4;

                        clock_t start__           = clock();
                        int received__            = MazeWithKeys().startingPoints( vector <string>( a, a + ( sizeof a / sizeof a[0] ) ) );
                        return verify_case( casenum, expected__, received__, clock()-start__ );
                    }

                    // custom cases

                    /*      case 4: {
                            string a[]                = ;
                            int expected__            = ;

                            clock_t start__           = clock();
                            int received__            = MazeWithKeys().startingPoints( vector <string>( a, a + ( sizeof a / sizeof a[0] ) ) );
                            return verify_case( casenum, expected__, received__, clock()-start__ );
                            }*/
                    /*      case 5: {
                            string a[]                = ;
                            int expected__            = ;

                            clock_t start__           = clock();
                            int received__            = MazeWithKeys().startingPoints( vector <string>( a, a + ( sizeof a / sizeof a[0] ) ) );
                            return verify_case( casenum, expected__, received__, clock()-start__ );
                            }*/
                    /*      case 6: {
                            string a[]                = ;
                            int expected__            = ;

                            clock_t start__           = clock();
                            int received__            = MazeWithKeys().startingPoints( vector <string>( a, a + ( sizeof a / sizeof a[0] ) ) );
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
