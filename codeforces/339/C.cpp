#include <bits/stdc++.h>
using namespace std;

#define sqr(x) ((x) * (x))
const double eps = 1e-8;
int sgn(double x) 
{
        return x < -eps ? -1 : x > eps;
}
struct Point;
typedef Point Vector;
struct Point 
{
	double x, y;
	void in() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("%.2lf %.2lf\n", x, y);
	}
	Point(double x = 0, double y = 0) : x(x), y(y) {
	}
        inline Vector rotate(double ang) {
                return Vector(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
        }
        inline double dot(const Vector &a) {
                return x * a.x + y * a.y;
        }
        inline bool operator == (const Point &a) const {
                return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
        }
        inline bool operator < (const Point &a) const {
                return sgn(x - a.x) < 0 || sgn(x - a.x) == 0 && sgn(y - a.y) < 0;
        }
        inline Vector operator + (const Vector &a) const {
                return Vector(x + a.x, y + a.y);
        }
        inline Vector operator - (const Vector &a) const {
                return Vector(x - a.x, y - a.y);
        }
        inline double operator * (const Vector &a) const {
                return x * a.y - y * a.x;
        }
        inline Vector operator * (double t) const {
                return Vector(x * t, y * t);
        }
        inline Vector operator / (double t) {
                return Vector(x / t, y / t);
        }
        inline double vlen() {
                return sqrt(x * x + y * y);
        }
        inline Vector norm() {
                return Point(-y, x);
        }

};

struct Cir
{
        Point ct;
        double r;
        void in() {
                ct.in();
                scanf("%lf", &r);
        }
};
struct Seg 
{
        Point s, e;
        Seg() {
        }
        Seg(Point s, Point e): s(s), e(e) {
        }
        void in() {
                s.in();
                e.in();
        }
};
struct Line
{
        int a, b, c;
};

inline bool cmpyx(const Point &a, const Point &b) 
{
        if(a.y != b.y) {
                return a.y < b.y;
        }
        return a.x < b.x;
}

double cross(Point a, Point b, Point c) 
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
bool same_dir(Vector a, Vector b) 
{						
	return sgn(a.x * b.y - b.x * a.y) == 0 && sgn(a.x * b.x) >= 0 && sgn(a.y * b.y) >= 0;
}
bool dot_on_seg(Point p, Seg L) 
{
        return sgn((L.s - p) * (L.e - p)) == 0 && sgn((L.s - p).dot(L.e - p)) <= 0;
}
double ppdis(Point a, Point b) 
{							
	return sqrt((a - b).dot(a - b));
}
double pldis(Point p,Point l1,Point l2)
{					
	return fabs(cross(p,l1,l2))/ppdis(l1,l2);
}
double pldis(Point p, Line ln)  
{								
	return fabs(ln.a * p.x + ln.b * p.y + ln.c) / sqrt(ln.a * ln.a + ln.b * ln.b);
}
bool point_in_circle(Point &a, Cir cr) 
{
	return sgn(ppdis(a, cr.ct) - cr.r) <= 0;
}
bool intersect(Point P, Vector v, Point Q, Vector w, Point &ret) 
{
        Vector u = P - Q;
        if(sgn(v * w) == 0) return false;
        double t = w * u / (v * w);
        ret = P + v * t;
        return true;
}
Point intersect(Point P, Vector v, Point Q, Vector w)
{
        Point ret;
        Vector u = P - Q;
        if(sgn(v * w) == 0) return false;
        double t = w * u / (v * w);
        ret = P + v * t;
        return ret;
}
//点到直线距离
Point disptoline(Point p, Seg l)
{
        return fabs(cross(p, l.s, l.e)) / ppdis(l.s, l.e);
}
//点到直线的垂足(最近点)
Point ptoline(Point p, Seg l)
{
        Point vec = l.s - l.e;
        return intersect(p, vec.norm(), l.s, vec);
}
//点到线段的最近点
Point ptoseg(Point p, Seg l)
{
        Point norm = (l.s - l.e).norm();
        if(sgn(norm * (p - l.s)) * sgn(norm * (p - l.e)) > 0) {
                double sa = ppdis(p, l.s);
                double sb = ppdis(p, l.e);
                return sgn(sa - sb) < 0 ? l.s : l.e;
        }
        return intersect(p, norm, l.s, l.e - l.s);
}

Point p[100010];
int main () {
	int n;
	Point p0;
	scanf("%d", &n);
	p0.in();
	for (int i = 0; i < n; i++) {
		p[i].in();
	}
	double mx = 0, mi = 1e100;
	for (int i = 0; i < n; i++) {
		mx = max(mx, ppdis(p0, p[i]));
		mi = min(mi, ppdis(p0, ptoseg(p0, Seg(p[i], p[(i+1)%n]))));
	}
	printf("%.8f\n", (mx*mx - mi*mi) * acos(-1.0) );
	return 0; 
}