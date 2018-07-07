#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <ctime>
using namespace std;

class SumOfArrays
{
public: 
    string findbestpair(int n, vector <int> Aseed, vector <int> Bseed);
    
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arr1[] = {1,1,1,1,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1,1,1,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "3 2"; verify_case(0, Arg3, findbestpair(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {1,1,1,1,1,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,1,1,1,1,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "2 4"; verify_case(1, Arg3, findbestpair(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 3; int Arr1[] = {1,2,0,0,1,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,1,0,0,1,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "3 2"; verify_case(2, Arg3, findbestpair(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 14; int Arr1[] = {5,6,2,4,6,11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {6,5,2,4,2,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "9 7"; verify_case(3, Arg3, findbestpair(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 100000; int Arr1[] = {6274,99908,61138,86540,56297,100000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {28275,25494,65423,61118,64925,100000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "3027 102148"; verify_case(4, Arg3, findbestpair(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
    SumOfArrays ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
typedef int type;
struct comp{
    double x, y;
    comp(double _x=0, double _y=0) : x(_x), y(_y) {}
};
namespace FFT{
    const int N = 1<<18;
    const double pi2 = 3.1415926535897932 * 2;
    comp a[N], b[N], tmp[N];
    int n, bn;
    type res[N];
    inline comp W(int n, bool inv) {
        double ang = inv ? -pi2 / n : pi2 / n;
        return comp(cos(ang), sin(ang));
    }
    int bitrev(int x) {
        int ans = 0;
        for (int i=1; i<=bn; ++i)
            ans <<= 1, ans |= x & 1, x >>= 1;
        return ans;
    }
    void dft(comp *a,bool inv) {
        int step, to; comp w, wi, A, B;
        for (int i=0; i<n; ++i) {
            to = bitrev(i);
            if (to > i) std::swap(a[to], a[i]);
        }
        for (int i=1; i<=bn; ++i) {
            wi = W(1<<i, inv); w = comp(1, 0);
            step = 1 << (i-1);
            for (int k=0; k<step; ++k) {
                for (int j=0; j<n; j+=1<<i) {
                    int t = j | k, d = j|k|step;
                    A = a[t];
                    B.x  = w.x * a[d].x - w.y * a[d].y;
                    B.y  = w.x * a[d].y + w.y * a[d].x;
                    a[t].x = A.x + B.x, a[t].y = A.y + B.y;
                    a[d].x = A.x - B.x, a[d].y = A.y - B.y;
                }
                comp tmp;
                tmp.x = w.x * wi.x - w.y * wi.y;
                tmp.y = w.x * wi.y + w.y * wi.x;
                w = tmp;
            }
        }
    }
    int mul(int n1, int *x1, int n2, int *x2) {
        n = std::max(n1, n2);
        for (bn = 0; (1<<bn) < n; ++bn); ++bn;
        n = 1 << bn;
        for (int i=0; i<n; ++i) a[i] = b[i] = comp(0, 0);
        for (int i=0; i<n1; ++i) a[i] = comp(x1[i], 0);
        for (int i=0; i<n2; ++i) b[i] = comp(x2[i], 0);
        dft(a, false); dft(b, false);
        for (int i=0; i<n; ++i) {
            tmp[i].x = a[i].x * b[i].x - a[i].y * b[i].y;
            tmp[i].y = a[i].x * b[i].y + a[i].y * b[i].x;
        }
        dft(tmp, true);
        for (int i=0; i<n; ++i) res[i] = (type)(tmp[i].x/n + 0.1);
        for (--n; n && !res[n]; --n);
        return n+1;
    }
}
const int N = 100010;
int a[N], b[N], aa[N], bb[N];
int n;
int mx;
void get(vector<int> src, int *cnt) {
  std::fill(cnt, cnt + mx, 0);
  int a = src[0], b = src[1];
  cnt[a]++; cnt[b]++;
  for(int i = 2; i < n; i++) {
    int c = (1LL * b * src[2] + 1LL * a * src[3] + src[4]) % src[5];
    cnt[c]++;
    a = b; b = c;
  }
}
int cnt[2*N];
string SumOfArrays::findbestpair(int n, vector <int> Aseed, vector <int> Bseed)
{
  ::n = n;
  get(Aseed, a); get(Bseed, b);
  mx = 0;
  for(int i = 0; i < N; i++) {
    if(a[i] || b[i]) mx = i;
  }
  mx++;
  memset(cnt, 0, sizeof(cnt));
  for(int i = 1; i <= 10; i++) {
    for(int j = 0; j < mx; j++) {
      aa[j] = (a[j] >= i);
      bb[j] = (b[j] >= i);
    }
    int tot = FFT::mul(mx, aa, mx, bb);
    for(int j = 0; j < tot; j++) cnt[j] += FFT::res[j];
  }
  vector<int> idx, idx1;
  for(int i = 0; i < N; i++) {
    if(a[i] > 10) {
      idx.push_back(i);
    }
    if(b[i] > 10) {
      idx1.push_back(i);
    }
  }
  for(int i = 0; i < (int)idx.size(); i++) {
    for(int j = 0; j < (int)idx1.size(); j++) {
      cnt[idx[i] + idx1[j]] += min(a[idx[i]], b[idx1[j]]) - 10;
    }
  }
  pair<int,int> ret = make_pair(0, 0);
  for(int i = 0; i < 2*N; i++) ret = max(ret, make_pair(cnt[i],i) );
  string ans;
  char buffer[10];
  sprintf(buffer,"%d",ret.first);
  ans += string(buffer);
  ans += " ";
  sprintf(buffer,"%d",ret.second);
  ans += string(buffer);
  return ans;
}
