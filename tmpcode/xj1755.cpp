#include <cstdio>
#include <vector>
#include <cmath>
#define sqr(x) ((x) * (x))
const double EPS = 1e-3;
const double PI = acos(-1.0);
const double HALF = PI * 0.5;

inline int sgn(double x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point;
typedef Point Vector;
struct Point {
    double x, y;
    void in() {
        scanf("%lf%lf", &x, &y);
    }
    void print() {
        printf("%.2lf %.2lf\n", x, y);
    }
    Point(double x = 0, double y = 0) : x(x), y(y) {
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
};

struct Triangle {
    double len, ang;
    void in () {
        scanf("%lf%lf", &len, &ang);
        len /= 2; ang /= 2;
    }
};

bool Intersect(Point P, Vector v, Point Q, Vector w, Point &ret) {
    Vector u = P - Q;
    if(sgn(v * w) == 0) return false;
    double t = w * u / (v * w);
    ret = P + v * t;
    return true;
}

struct Seg {
    Point s, e;
    Seg() {
    }
    Seg(Point s, Point e): s(s), e(e) {
    }
};

bool DotOnSeg(Point p, Seg L) {
    return sgn((L.s - p) * (L.e - p)) == 0 && sgn((L.s - p).dot(L.e - p)) <= 0;
}

double PointToPoint(Point a, Point b) {							
    return sqrt((a - b).dot(a - b));
}

int n;
Point from, end, s, e, vec;
double ret, ang;
std::vector <Triangle> san;

void Calc(int dir, bool flag) {
    for (int i = 1; i < n; i++) {
        e = s + Point (san[i].len * (flag?1:-1), -san[i].len / tan(san[i].ang) ) ;
        Point inter = Point(-1, -1);
        bool flag = Intersect (from, vec, s, e - s, inter);
        if (flag && DotOnSeg (inter, Seg(s, e))) {
            ret += PointToPoint(inter, e);
            s = e + (Vector(san[i].len, 0) * dir);
            from = e; //数据太水了 这里不写也过了
        } else {
            s = e + (Vector(san[i].len, 0) * dir);
        }
    }
}

int main () {
    scanf("%lf", &ang);
    if(sgn(ang - HALF) > 0) {
        ang = PI - ang;
    }
    scanf("%d", &n);
    san.resize(n);
    for (int i = 0; i < n; i++) {
        san[i].in();
    }
    ret = 0;
    //计算右边
    //设第一个三角形的右端点为from
    std::vector <Triangle>::iterator  it = san.begin();
    ret += it->len / sin(it->ang);
    from = Point(10000.0, 10000.0);
    vec = Point(-sin(HALF - ang), -cos(HALF - ang));
    s = from - Vector(it->len, 0);
    Calc(-1, true);

    //计算左边
    //设第一个三角形的左端点为from
    if(sgn(ang - (HALF - it->ang) ) >= 0) { // 第一个三角形是否能覆盖到
        ret += it->len / sin (it->ang);
        s = from + Vector (it->len, 0);
    } else {
        s = from + Vector (0, -it->len / tan(it->ang) );
    }

    Calc(1, false);
    printf("%.1f\n", ret);
    return 0;
}

