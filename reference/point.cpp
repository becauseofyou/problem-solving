 
#define DB double 
#define op operator
const DB eps = 1e-8;

int sgn(DB x) { return x < -eps ? -1 : x > eps; }
 
struct PT {
    DB x, y;
    PT(DB x = 0, DB y = 0) : x(x), y(y) {
    }
    void in() {
        scanf("%lf%lf", &x, &y);
    }
    bool op == (const PT &a) const {
        return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
    }
    bool op < (const PT &a) const {
        return sgn(x - a.x) < 0 || (sgn(x - a.x) == 0 && sgn(y - a.y) < 0);
    }
    PT op + (const PT &a) const {
        return PT(x + a.x, y + a.y);
    }
    PT op - (const PT &a) const {
        return PT(x - a.x, y - a.y);
    }
    DB op * (const PT &a) const {
        return x * a.y - y * a.x;
    }
    PT op / (DB t) {
        return PT(x / t, y / t);
    }
    DB dot(const PT &a) {
        return x * a.x + y * a.y;
    }
    DB length() {
        return sqrt (x*x + y*y);
    }
    PT norm() {
        return PT(-y, x);
    }
    PT rotate(DB ang) {
        return PT(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
    }
    void print () {
        printf("%lf %lf\n", x, y);
    }
};

