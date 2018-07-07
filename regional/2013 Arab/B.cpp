#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Point {
        double x, y;
        Point(double x = 0, double y = 0): 
                x(x), y(y){}
        void print() {
                printf("x=%.2lf y=%.2lf\n",x,y);
        }
};
struct Seg{
        Point s, e;
        Seg() {
        }
        Seg(Point s, Point e) :
                s(s), e(e) {}
};
typedef Point Vector;
double dis(Point a, Point b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline Vector operator + (const Vector &a, const Vector &b) {
        return Vector(a.x + b.x, a.y + b.y);
}
inline Vector operator - (const Vector &a, const Vector &b) {
        return Vector(a.x - b.x, a.y - b.y);
}
inline Vector operator * (const Vector &a, double t) {
        return Vector(a.x * t, a.y * t);
}
inline Vector operator / (const Vector &a, double p) {
        return Vector(a.x / p, a.y / p);
}
inline int sgn(double x,double eps=1e-8) {
        return x < -eps ? -1 : x > eps;
}
bool operator < (const Point &a, const Point &b) {
        return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && sgn(a.y - b.y) < 0;
}
bool operator == (const Point &a, const Point &b) {
        return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
}
inline double cross(Vector a, Vector b) {
        return a.x * b.y - a.y * b.x;
}
inline double cross(Point o, Point a, Point b) {
        return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
inline double dot(Vector a, Vector b) {
        return a.x * b.x + a.y * b.y;
}
bool intersect(Point P, Vector v, Point Q, Vector w, Point &p) {
        Vector u = P - Q;
        if(sgn(cross(v, w)) == 0) return false;
        double t = cross(w, u) / cross(v, w);
        p = P + v * t;
        return true;
}
bool segcross(Point p1, Point p2, Point q1, Point q2) {
        return (
                        std::min(p1.x, p2.x) <= std::max(q1.x, q2.x) &&
                        std::min(q1.x, q2.x) <= std::max(p1.x, p2.x) &&
                        std::min(p1.y, p2.y) <= std::max(q1.y, q2.y) &&
                        std::min(q1.y, q2.y) <= std::max(p1.y, p2.y) && /* 跨立实验 */
                        sgn( cross(p1, q2, q1) * cross(p2, q2, q1) ) <= 0 && 
                        sgn( cross(q1, p2, p1) * cross(q2, p2, p1) ) <= 0  /* 叉积相乘判方向 */
               );
}
struct Rec {
        Point center;
        Seg seg[4];
}rec[26];
Point A, B;
struct Inter_Rec {
        int id;
        Point a, b;
        Inter_Rec(Point a, Point b, int id) : a(a), b(b), id(id) {
        }
        Inter_Rec() {
        }
        bool operator < (const Inter_Rec& cmp) const {
                double dis1 = dis(a, A);
                double tmp = dis(b, A);
                if(tmp < dis1) dis1 = tmp;
                double dis2 = dis(cmp.a, A);
                tmp = dis(cmp.b, A);
                if(tmp < dis2) dis2 = tmp;
                return dis1 < dis2;
        }
};

struct Gao {
        void init() {
                Point base = Point(1, 4);
                for(int i = 0; i < 5; i++) {
                        rec[i].center = base + Point(1, 0);
                        base = base + Point(1, 0);
                }
                base = Point(0, 3);
                for(int i = 5; i < 12; i++) {
                        rec[i].center = base + Point(1, 0);
                        base = base + Point(1, 0);
                }
                base = Point(0, 2);
                for(int i = 12; i < 19; i++) {
                        rec[i].center = base + Point(1, 0);
                        base = base + Point(1, 0);
                }
                base = Point(0, 1);
                for(int i = 19; i < 26; i++) {
                        rec[i].center = base + Point(1, 0);
                        base = base + Point(1, 0);
                }
                for(int i = 0; i < 26; i++) {
                        rec[i].seg[0] = Seg(Point(rec[i].center.x - 0.5, rec[i].center.y + 0.5)
                                        , Point(rec[i].center.x + 0.5, rec[i].center.y + 0.5) ) ;
                        rec[i].seg[1] = Seg(Point(rec[i].center.x + 0.5, rec[i].center.y + 0.5)
                                        , Point(rec[i].center.x + 0.5, rec[i].center.y - 0.5) );
                        rec[i].seg[2] = Seg(Point(rec[i].center.x + 0.5, rec[i].center.y - 0.5)
                                        , Point(rec[i].center.x - 0.5, rec[i].center.y - 0.5));
                        rec[i].seg[3] = Seg(Point(rec[i].center.x - 0.5, rec[i].center.y - 0.5)
                                        , Point(rec[i].center.x - 0.5, rec[i].center.y + 0.5));
                }
          /*      for(int i = 0; i < 26; i++) {
                        rec[i].center.print();
                }*/

        }
        void get_string(char *s) {
                fullString = "";
                int len = strlen(s);
                fullString += s[0];
                for(int i = 1; i < len; i++) {
                        int a = s[i - 1] - 'A';
                        int b = s[i] - 'A';
                        Seg ss = Seg(rec[a].center, rec[b].center);
                        A = rec[a].center;
                        B = rec[b].center;
                        vector<Inter_Rec> interRec;
                        for(int obj = 0; obj < 26; obj++) if(obj != a && obj != b){
                                vector<Point> pts;
                                for(int sg = 0; sg < 4; sg++) {
                                        if(segcross(ss.s, ss.e, rec[obj].seg[sg].s, rec[obj].seg[sg].e)) {
                                                Point p;
                                                intersect(ss.s, ss.e - ss.s, rec[obj].seg[sg].s, rec[obj].seg[sg].e - rec[obj].seg[sg].s, p);
                                                pts.push_back(p);
                                        }
                                }
                                if(pts.size() == 0) continue;
                                sort(pts.begin(), pts.end());
                                pts.erase(unique(pts.begin(), pts.end()), pts.end());
                                if(pts.size() == 2) {
                                        interRec.push_back(Inter_Rec(pts[0], pts[1], obj));
                                }
                        }
                        sort(interRec.begin(), interRec.end());
                        for(int j = 0; j < interRec.size(); j++) {
                                fullString += 'A' + interRec[j].id;
                        }
                        fullString += s[i];
                }
//                cout<< fullString << endl;
        }
        bool test_seq(char *s) {
                int n = fullString.length();
                int i = 0;
                for(int j = 0; j < n; j++) {
                        if(s[i] == fullString[j]) {
                                i++;
                        }
                        if(!s[i]) return true;
                }
                return false;
        }
        string fullString;
}gao;
char str[1010][110];
char acm[110];
int main() {
        int t, n;
        gao.init();
        scanf("%d",&t);
        while(t--) {
                scanf("%d%s", &n, acm);
                gao.get_string(acm);
                bool flag = false;
                for(int i = 0; i < n; i++) {
                        scanf("%s",str[i]);
                        if(!flag) {
                                if(gao.test_seq(str[i])) {
                                        printf("%s\n",str[i]);
                                        flag = true;
                                }
                        }
                }
                if(!flag) {
                        puts("NO SOLUTION");
                }
        }
        return 0;
}