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

class $CLASSNAME$ {
public:
    $RC$ $METHODNAME$( $METHODPARMS$ ) ;
};
$RC$ $CLASSNAME$::$METHODNAME$($METHODPARMS$) {
    
}

$BEGINCUT$
$TESTCODE$

$DEFAULTMAIN$
$ENDCUT$
