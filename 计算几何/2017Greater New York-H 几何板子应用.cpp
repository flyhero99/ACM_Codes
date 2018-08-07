#include <bits/stdc++.h>
using namespace std;

#define maxn 100005

const double eps = 1e-7;
const double INF = 1e20;
const double pi = acos (-1.0);

int dcmp (double x) {
    if (fabs (x) < eps) return 0;
    return (x < 0 ? -1 : 1);
}
inline double sqr (double x) {return x*x;}
double get_max (double _a, double _b) {
    return dcmp(_a-_b) > 0 ? _a : _b;
}

//*************点
struct Point {
    double x, y;
    Point (double _x = 0, double _y = 0):x(_x), y(_y) {}
    void input () {scanf ("%lf%lf", &x, &y);}
    void output () {printf ("%.2f %.2f\n", x, y);}
    bool operator == (const Point &b) const {
        return (dcmp (x-b.x) == 0 && dcmp (y-b.y) == 0);
    }
    bool operator < (const Point &b) const {
        return (dcmp (x-b.x) == 0 ? dcmp (y-b.y) < 0 : x < b.x);
    }
    Point operator + (const Point &b) const {
        return Point (x+b.x, y+b.y);
    }
    Point operator - (const Point &b) const {
        return Point (x-b.x, y-b.y);
    }
    Point operator * (double a) {
        return Point (x*a, y*a);
    }
    Point operator / (double a) {
        return Point (x/a, y/a);
    }
    double len2 () {//返回长度的平方
        return sqr (x) + sqr (y);
    }
    double len () {//返回长度
        return sqrt (len2 ());
    }
    Point change_len (double r) {//转化为长度为r的向量
        double l = len ();
        if (dcmp (l) == 0) return *this;//零向量返回自身
        r /= l;
        return Point (x*r, y*r);
    }
    Point rotate_left () {//顺时针旋转90度
        return Point (-y, x);
    }
    Point rotate_right () {//逆时针旋转90度
        return Point (y, -x);
    }
    Point rotate (Point p, double ang) {//绕点p逆时针旋转ang
        Point v = (*this)-p;
        double c = cos (ang), s = sin (ang);
        return Point (p.x + v.x*c - v.y*s, p.y + v.x*s + v.y*c);
    }
    Point normal () {//单位法向量
        double l = len ();
        return Point (-y/l, x/l);
    }
};

double cross (Point a, Point b) {//叉积
    return a.x*b.y-a.y*b.x;
}
double dot (Point a, Point b) {//点积
    return a.x*b.x + a.y*b.y;
}
double dis (Point a, Point b) {//两个点的距离
    Point p = b-a; return p.len ();
}
double degree_rad (double ang) {//角度转化为弧度   
    return ang/180*pi;
}
double rad_degree (double rad) {//弧度转化为角度
    return rad/pi*180;
}
double rad (Point a, Point b) {//两个向量的夹角
    return fabs (atan2 (fabs (cross (a, b)), dot (a, b)) );
}
bool parallel (Point a, Point b) {//向量平行
    double p = rad (a, b);
    return dcmp (p) == 0 || dcmp (p-pi) == 0;
}

//************直线 线段
struct Line {
    Point s, e;//直线的两个点
    double k;//极角 范围[-pi,pi]
    Line () {}
    Line (Point _s, Point _e) {
        s = _s, e = _e;
        k = atan2 (e.y - s.y,e.x - s.x);
    }
    //ax+by+c = 0
    Line (double a, double b, double c) {
        if (dcmp (a) == 0) {
            s = Point (0, -c/b);
            e = Point (1, -c/b);
        }
        else if (dcmp (b) == 0) {
            s = Point (-c/a, 0);
            e = Point (-c/a, 1);
        }
        else {
            s = Point (0, -c/b);
            e = Point (1, (-c-a)/b);
        }
        get_angle ();
    }
    //一个点和倾斜角确定直线
    Line (Point p, double ang) {
        k = ang;
        s = p;
        if (dcmp (ang-pi/2) == 0) {
            e = s + Point (0, 1);
        }
        else
            e = s + Point (1, tan (ang));
    }
    void input () {
        s.input ();
        e.input ();
    }
    void output () {
        printf ("%.2f,%.2f %.2f,%.2f\n", s.x, s.y, e.x, e.y);
    }
    void adjust () {
        if (e < s) swap (e, s);
    }
    double length () {//求线段长度
        return dis (s, e);
    }
    void get_angle () {
        k = atan2 (e.y - s.y,e.x - s.x);
    }
    double angle () {//直线的倾斜角
        if (dcmp (k) < 0) k += pi;
        if (dcmp (k-pi) == 0) k -= pi;
        return k;
    }
    Point operator &(const Line &b)const {//直线的交点(保证存在)
        Point res = s;
        double t = (cross (s - b.s, b.s - b.e))/cross (s - e, b.s - b.e); 
        res.x += (e.x - s.x)*t;
        res.y += (e.y - s.y)*t;
        return res;
    }
};

int relation (Point p, Line l) {//点和直线的关系
    //1:在左侧 2:在右侧 3:在直线上
    int c = dcmp (cross (p-l.s, l.e-l.s));
    if (c < 0) return 1;
    else if (c > 0) return 2;
    else return 3;
}

bool point_on_halfline (Point p, Line l) {//判断点在射线上
    int id = relation (p, l);
    if (id != 3) return 0;
    return dcmp (dot (p-l.s, l.e-l.s)) >= 0;
}

bool point_on_seg (Point p, Line l) {//判断点在线段上
    return dcmp (cross (p-l.s, l.e-l.s)) == 0 &&
    dcmp (dot (p-l.s, p-l.e)) <= 0;
    //如果忽略端点交点改成小于号就好了
}

bool parallel (Line a, Line b) {//直线平行
    return parallel (a.e-a.s, b.e-b.s);
}

int seg_cross_seg (Line a, Line v) {//线段相交判断
    //2:规范相交 1:不规范相交 0:不相交
    int d1 = dcmp (cross (a.e-a.s, v.s-a.s));
    int d2 = dcmp (cross (a.e-a.s, v.e-a.s));
    int d3 = dcmp (cross (v.e-v.s, a.s-v.s));
    int d4 = dcmp (cross (v.e-v.s, a.e-v.s));
    if ((d1^d2) == -2 && (d3^d4) == -2) return 2;
    return (d1 == 0 && dcmp (dot (v.s-a.s, v.s-a.e)) <= 0) ||
        (d2 == 0 && dcmp (dot (v.e-a.s, v.e-a.e)) <= 0) ||
        (d3 == 0 && dcmp (dot (a.s-v.s, a.s-v.e)) <= 0) ||
        (d4 == 0 && dcmp (dot (a.e-v.s, a.e-v.e)) <= 0);
}

int line_cross_seg (Line a, Line v) {//直线和线段相交判断 a直线v线段
    //2:规范相交 1:非规范相交 0:不相交
    int d1 = dcmp (cross (a.e-a.s, v.s-a.s));
    int d2 = dcmp (cross (a.e-a.s, v.e-a.s));
    if ((d1^d2) == -2) return 2;
    return (d1 == 0 || d2 == 0);
}

int line_cross_line (Line a, Line v) {//直线相交判断
    //0:平行 1:重合 2:相交
    if (parallel (a, v)) return relation (a.e, v) == 3;
    return 2;
}

Point line_intersection (Line a, Line v) {//直线交点
    //调用前确保有交点
    double a1 = cross (v.e-v.s, a.s-v.s);
    double a2 = cross (v.e-v.s, a.e-v.s);
    return Point ((a.s.x*a2-a.e.x*a1)/(a2-a1), (a.s.y*a2-a.e.y*a1)/(a2-a1));
}

int seg_intersectiong (Line a, Line b, Point &p) {//求线段交点
    //0:没有交点 1:规范相交 2:非规范相交
    //调用前确包只有一个交点
    int rel = seg_cross_seg (a, b);
    if (rel == 0) return 0;
    int cnt = 0;
    if (rel == 1) {
        if (point_on_seg (a.e, b)) p = a.e, cnt++;
        if (point_on_seg (a.s, b)) p = a.s, cnt++;
        if (point_on_seg (b.e, a)) p = b.e, cnt++;
        if (point_on_seg (b.s, a)) p = b.s, cnt++;
        return 2;
    }
    p = line_intersection (a, b);
    return 1;
}

double point_to_line (Point p, Line a) {//点到直线的距离
    return fabs (cross (p-a.s, a.e-a.s) / a.length ());
}

double point_to_seg (Point p, Line a) {//点到线段的距离
    if (dcmp (dot (p-a.s, a.e-a.s)) < 0 || dcmp (dot (p-a.e, a.s-a.e)) < 0)
        return min (dis (p, a.e), dis (p, a.s));
    return point_to_line (p, a);
}

Point projection (Point p, Line a) {//点在直线上的投影
    return a.s + (((a.e-a.s) * dot (a.e-a.s, p-a.s)) / (a.e-a.s).len2() );
}

Point symmetry (Point p, Line a) {//点关于直线的对称点
    Point q = projection (p, a);
    return Point (2*q.x-p.x, 2*q.y-p.y);
}

//***************圆
struct Circle {
    //圆心 半径
    Point p;
    double r;
    Circle () {}
    Circle (Point _p, double _r) : p(_p), r(_r) {}
    Circle (double a, double b, double _r) { //圆心坐标 半径确定圆
        p = Point (a, b);
        r = _r;
    }
    Circle (Point pt1, Point pt2, Point pt3) { //三点定圆 如果三点共线半径为-1
        double x1 = pt1.x, x2 = pt2.x, x3 = pt3.x;
        double y1 = pt1.y, y2 = pt2.y, y3 = pt3.y;
        double a = x1 - x2;
        double b = y1 - y2;
        double c = x1 - x3;
        double d = y1 - y3;
        double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
        double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
        double det = b * c - a * d;
        if (fabs (det) < eps) {
            r = -1;
            p = Point(0,0);
        }
        double x0 = -(d * e - b * f) / det;
        double y0 = -(a * f - c * e) / det;
        r = hypot (x1 - x0, y1 - y0); p = Point (x0, y0);
    }
    void input () {
        p.input ();
        scanf ("%lf", &r);
    }
    void output () {
        p.output ();
        printf (" %.2f\n", r);
    }
    bool operator == (const Circle &a) const {
        return p == a.p && (dcmp (r-a.r) == 0);
    }
    double area () {//面积
        return pi*r*r;
    }
    double circumference () {//周长
        return 2*pi*r;
    }
    bool operator < (const Circle &a) const {
        return p < a.p || (p == a.p && r < a.r);
    }
};

int relation (Point p, Circle a) {//点和圆的关系
    //0:圆外 1:圆上 2:圆内
    double d = dis (p, a.p);
    if (dcmp (d-a.r) == 0) return 1;
    return (dcmp (d-a.r) < 0 ? 2 : 0);
}

int relation (Line a, Circle b) {//直线和圆的关系
    //0:相离 1:相切 2:相交
    double p = point_to_line (b.p, a);
    if (dcmp (p-b.r) == 0) return 1;
    return (dcmp (p-b.r) < 0 ? 2 : 0);
}

int relation (Circle a, Circle v) {//两圆的位置关系
    //1:内含 2:内切 3:相交 4:外切 5:相离
    double d = dis (a.p, v.p);
    if (dcmp (d-a.r-v.r) > 0) return 5;
    if (dcmp (d-a.r-v.r) == 0) return 4;
    double l = fabs (a.r-v.r);
    if (dcmp (d-a.r-v.r) < 0 && dcmp (d-l) > 0) return 3;
    if (dcmp (d-l) == 0) return 2;
    if (dcmp (d-l) < 0) return 1;
    return 0;
}

Circle out_circle (Point a, Point b, Point c) {//三角形外接圆
    Line u = Line ((a+b)/2, ((a+b)/2) + (b-a).rotate_left ());
    Line v = Line ((b+c)/2, ((b+c)/2) + (c-b).rotate_left ());
    Point p = line_intersection (u, v);
    double r = dis (p, a);
    return Circle (p, r);
}

Circle in_circle (Point a, Point b, Point c) {//三角形内切圆
    Line u, v;
    double m = atan2 (b.y-a.y, b.x-a.x), n = atan2 (c.y-a.y, c.x-a.x);
    u.s = a;
    u.e = u.s+Point (cos ((n+m)/2), sin ((n+m)/2));
    v.s = b;
    m = atan2 (a.y-b.y, a.x-b.x), n = atan2 (c.y-b.y, c.x-b.x);
    v.e = v.s + Point (cos ((n+m)/2), sin ((n+m)/2));
    Point p = line_intersection (u, v);
    double r = point_to_seg (p, Line (a, b));
    return Circle (p, r);
}

int circle_intersection (Circle a, Circle v, Point &p1, Point &p2) {//两个圆的交点
    //返回交点个数 交点保存在引用中
    int rel = relation (a, v);
    if (rel == 1 || rel == 5) return 0;
    double d = dis (a.p, v.p);
    double l = (d*d + a.r*a.r - v.r*v.r) / (2*d);
    double h = sqrt (a.r*a.
                     r - l*l);
    Point tmp = a.p + (v.p-a.p).change_len (l);
    p1 = tmp + ((v.p-a.p).rotate_left ().change_len (h));
    p2 = tmp + ((v.p-a.p).rotate_right ().change_len (h));
    if (rel == 2 || rel == 4) return 1;
    return 2;
}

int line_cirlce_intersection (Line v, Circle u, Point &p1, Point &p2) {//直线和圆的交点
    //返回交点个数 交点保存在引用中
    if (!relation (v, u)) return 0;
    Point a = projection (u.p, v);
    double d = point_to_line (u.p, v);
    d = sqrt (u.r*u.r - d*d);
    if (dcmp (d) == 0) {
        p1 = a, p2 = a;
        return 1;
    }
    p1 = a + (v.e-v.s).change_len (d);
    p2 = a - (v.e-v.s).change_len (d);
    return 2;
}

int get_circle (Point a, Point b, double r1, Circle &c1, Circle &c2) {//得到过ab半径为r1的了两个圆
    //返回得到圆的个数 圆保存在两个引用中
    Circle x (a, r1), y (b, r1);
    int t = circle_intersection (x, y, c1.p, c2.p);
    if (!t) return 0;
    c1.r = c2.r = r1;
    return t;
}

int get_circle (Line u, Point q, double r1, Circle &c1, Circle &c2) {//得到和直线u相切 过点q 半径为r1的圆
    double d = point_to_line (q, u);
    if (dcmp (d-r1*2) > 0) return 0;
    if (dcmp (d) == 0) {
        c1.p = q + ((u.e-u.s).rotate_left ().change_len (r1));
        c2.p = q + ((u.e-u.s).rotate_right ().change_len (r1));
        c1.r = c2.r = r1;
        return 2;
    }
    Line u1 = Line (u.s + (u.e-u.s).rotate_left ().change_len (r1), u.e + (u.e-u.s).rotate_left ().change_len (r1));
    Line u2 = Line (u.s + (u.e-u.s).rotate_right ().change_len (r1), u.e + (u.e-u.s).rotate_right ().change_len (r1));
    Circle cc = Circle (q, r1);
    Point p1, p2;
    if (!line_cirlce_intersection (u1, cc, p1, p2))
        line_cirlce_intersection (u2, cc, p1, p2);
    c1 = Circle (p1, r1);
    if (p1 == p2) {
        c2 = c1;
        return 1;
    }
    c2 = Circle (p2, r1);
    return 2;
}

int get_circle (Line u, Line v, double r1, Circle &c1, Circle &c2, Circle &c3, Circle &c4) {//和直线u,v相切 半径为r1的圆
    if (parallel (u, v)) return 0;
    Line u1 = Line (u.s + (u.e-u.s).rotate_left ().change_len (r1), u.e + (u.e-u.s).rotate_left ().change_len (r1));
    Line u2 = Line (u.s + (u.e-u.s).rotate_right ().change_len (r1), u.e + (u.e-u.s).rotate_right ().change_len (r1));
    Line v1 = Line (v.s + (v.e-v.s).rotate_left ().change_len (r1), v.e + (v.e-v.s).rotate_left ().change_len (r1));
    Line v2 = Line (v.s + (v.e-v.s).rotate_right ().change_len (r1), v.e + (v.e-v.s).rotate_right ().change_len (r1));
    c1.r = c2.r = c3.r = c4.r = r1;
    c1.p = line_intersection (u1, v1);
    c2.p = line_intersection (u1, v2);
    c3.p = line_intersection (u2, v1);
    c4.p = line_intersection (u2, v2);
    return 4;
}

int get_circle (Circle cx, Circle cy, double r1, Circle &c1, Circle &c2) {//和两个圆外切 半径为r1的圆
    //确保两个圆外离
    Circle x (cx.p, r1+cx.r), y (cy.p, r1+cy.r);
    int t = circle_intersection (x, y, c1.p, c2.p);
    if (!t) return 0;
    c1.r = c2.r = r1;
    return t;
}

int tan_line (Point q, Circle a, Line &u, Line &v) {//过一点作圆切线
    int x = relation (q, a);
    if (x == 2) return 0;
    if (x == 1) {
        u = Line (q, q + (q-a.p).rotate_left ());
        v = u;
        return 1;
    }
    double d = dis (a.p, q);
    double l = a.r*a.r/d;
    double h = sqrt (a.r*a.r - l*l);
    u = Line (q, a.p + (q-a.p).change_len (l) + (q-a.p).rotate_left ().change_len (h));
    v = Line (q, a.p + (q-a.p).change_len (l) + (q-a.p).rotate_right ().change_len (h));
    return 2;
}

double area_circle (Circle a, Circle v) {//两圆相交面积
    int rel = relation (a, v);
    if (rel >= 4) return 0;
    if (rel <= 2) return min (a.area (), v.area ());
    double d = dis (a.p, v.p);
    double hf = (a.r+v.r+d)/2;
    double ss = 2*sqrt (hf*(hf-a.r)*(hf-v.r)*(hf-d));
    double a1 = acos ((a.r*a.r+d*d-v.r*v.r) / (2*a.r*d));
    a1 = a1*a.r*a.r;
    double a2 = acos ((v.r*v.r+d*d-a.r*a.r) / (2*v.r*d));
    a2 = a2*v.r*v.r;
    return a1+a2-ss;
}

double circle_traingle_area (Point a, Point b, Circle c) {//圆心三角形的面积
    //a.output (), b.output (), c.output ();
    Point p = c.p; double r = c.r; //cout << cross (p-a, p-b) << endl;
    if (dcmp (cross (p-a, p-b)) == 0) return 0;
    Point q[5];
    int len = 0;
    q[len++] = a;
    Line l(a, b);
    Point p1, p2;
    if (line_cirlce_intersection (l, c, q[1], q[2]) == 2) {
        if (dcmp (dot (a-q[1], b-q[1])) < 0) q[len++] = q[1];
        if (dcmp (dot (a-q[2], b-q[2])) < 0) q[len++] = q[2];
    }
    q[len++] = b;
    if (len == 4 && dcmp (dot (q[0]-q[1], q[2]-q[1])) > 0)
        swap (q[1], q[2]);
    double res = 0;
    for (int i = 0; i < len-1; i++) {
        if (relation (q[i], c) == 0 || relation (q[i+1], c) == 0) {
            double arg = rad (q[i]-p, q[i+1]-p);
            res += r*r*arg/2.0;
        }
        else {
            res += fabs (cross (q[i]-p, q[i+1]-p))/2;
        }
    } //cout << res << ".." << endl;
    return res;
}

//*************多边形
double polygon_area (Point *p, int n) {//多边形的有向面积,加上绝对值就是面积
    //n个点
    double area = 0;
    for (int i = 1; i < n-1; i++) {
        area += cross (p[i]-p[0], p[i+1]-p[0]);
    }
    return area/2;
}

int relation (Point q, Point *p, int n) {//点和多边形的关系(凸凹都可以)
    //0:外部 1:内部 2:边上 3:顶点
    for (int i = 0; i < n; i++) {
        if (p[i] == q)
            return 3;
    }
    for (int i = 0; i < n; i++) {
        if (point_on_seg (q, Line (p[i], p[(i+1)%n])))
            return 2;
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n;
        int k = dcmp (cross (q-p[j], p[i]-p[j]));
        int u = dcmp (p[i].y-q.y);
        int v = dcmp (p[j].y-q.y);
        if (k > 0 && u < 0 && v >= 0) cnt++;
        if (k < 0 && v < 0 && u >= 0) cnt--;
    }
    return cnt != 0;
}

int convex_cut (Line u, Point *p, int n, Point *po) {//直线切割多边形左侧
    //返回切割后多边形的数量
    int top = 0;
    for (int i = 0; i < n; i++) {
        int d1 = dcmp (cross (u.e-u.s, p[i]-u.s));
        int d2 = dcmp (cross (u.e-u.s, p[(i+1)%n]-u.s));
        if (d1 >= 0) po[top++] = p[i];
        if (d1*d2 < 0) po[top++] = line_intersection (u, Line (p[i], p[(i+1)%n]));
    }
    return top;
}

double convex_circumference (Point *p, int n) {//多边形的周长(凹凸都可以)
    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dis (p[i], p[(i+1)%n]);
    }
    return ans;
}

double area_polygon_circle (Circle c, Point *p, int n) {//多边形和圆交面积
    double ans = 0;
    for (int i = 0; i < n; i++) {
        int j = (i+1)%n; //cout << i << " " << j << "//" << endl;
        if (dcmp (cross (p[j]-c.p, p[i]-c.p)) >= 0)
            ans += circle_traingle_area (p[i], p[j], c);
        else
            ans -= circle_traingle_area (p[i], p[j], c);
    }
    return fabs (ans);
}

Point centre_of_gravity (Point *p, int n) {//多边形的重心(凹凸都可以)
    double sum = 0.0, sumx = 0, sumy = 0;
    Point p1 = p[0], p2 = p[1], p3;
    for (int i = 2; i <= n-1; i++) {
        p3 = p[i];
        double area = cross (p2-p1, p3-p2)/2.0;
        sum += area;
        sumx += (p1.x+p2.x+p3.x)*area;
        sumy += (p1.y+p2.y+p3.y)*area;
        p2 = p3;
    }
    return Point (sumx/(3.0*sum), sumy/(3.0*sum));
}

int convex_hull (Point *p, Point *ch, int n) {//求凸包
        //所有的点集 凸包点集 点集的点数
    sort (p, p+n);
    int m = 0;
    for (int i = 0; i < n; i++) {
        while (m > 1 && cross (ch[m-1]-ch[m-2], p[i]-ch[m-1]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    int k = m;
    for (int i = n-2; i >= 0; i--) {
        while (m > k && cross (ch[m-1]-ch[m-2], p[i]-ch[m-1]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    if (n > 1)
        m--;
    return m;
}

double rotate_calipers(Point *p, int m) {//旋转卡壳 平面距离平方最远点对
    //如果求距离加sqrt即可
    double ans = 0;
    int cur = 1;
    for (int i = 0; i < m; i++) {
        while (cross (p[i]-p[(i+1)%m], p[(cur+1)%m]-p[cur]) < 0)
            cur = (cur+1) % m;
        ans = max (ans, max (dis (p[i], p[cur]), dis (p[(i+1)%m], p[(cur+1)%m])));
    }
    return ans;
}

//判断一个点是否在凸多边形内部或者边界上 复杂度 O(logn)
bool Compl_inside_convex(const Point & p,Point *con, int n)
{ //点  多边形数组（凸包顺序） 多边形数目
    if(n<3) return false;
    if(cross(p-con[0],con[1]-con[0])>eps) return false;   //不在边界的话变成>-eps
    if(cross(p-con[0],con[n-1]-con[0])<-eps) return false; //不在边界的话变成<eps
    int i=2,j=n-1;
    int line=-1;
    while(i<=j)
    {
        int mid=(i+j)>>1;
        if(cross(p-con[0],con[mid]-con[0])>-eps)
        {
            line=mid;
            j=mid-1;
        }
        else i=mid+1;
    }
    return cross(p-con[line-1],con[line]-con[line-1])<eps;  //不在边界的话变成<-eps
}


bool get_dir (Point *p, int n) {//得到多边形的时针顺序
    //0:顺时针 1:逆时针
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += cross (p[i], p[(i+1)%n]);
    }
    if (dcmp (sum) > 0) return 1;
    return 0;
}

double poly_min_seg (Point *coin, int m) {
    //多边形的最短长度 可以是凹 复杂度O(n^2)
    //相当于硬币投影的最短长度
    double ans = INF;
    Point *ch;
    int cnt = convex_hull (coin, ch, m);
    for (int i = 0; i < cnt; i++) {
        int j = (i+1)%cnt;
        double tmp = 0;
        for (int k = 0; k < cnt; k++) if (k != i && k != j) {
            tmp = max (tmp, point_to_line (ch[k], Line (ch[i], ch[j])));
        }
        ans = min (ans, tmp);
    }
    return ans;
}

double poly_max_seg (Point *hole, int n) {
    //多边形的最长长度 可以是凹 复杂度O(n^3)
    //相当于孔洞提供的最长内部线段
    double ans = 0;
    vector <Point> gg;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (i != j) {
            Line cur (hole[i], hole[j]);
            gg.clear ();
            for (int x = 0; x < n; x++) {
                int y = (x+1)%n;
                int in1, in2;
                in1 = relation (hole[x], cur);
                in2 = relation (hole[y], cur);
                if (in1 == 3) gg.push_back (hole[x]);
                if (in2 == 3) gg.push_back (hole[y]);
                if (in1 == 3 || in2 == 3) {
                    continue;
                }
                int id = line_cross_seg (cur, Line (hole[x], hole[y]));
                if (id == 2) {
                    Point p = line_intersection (cur, Line (hole[x], hole[y]));
                }
            }
            sort (gg.begin (), gg.end ());
            int Max = gg.size ();
            double tmp = 0;
            for (int i = 0; i < Max-1; i++) {
                Point p = Point (gg[i].x+gg[i+1].x, gg[i].y+gg[i+1].y)/2;
                int id = relation (p, hole, n);
                if (id == 0) {
                    ans = max (ans, tmp);
                    tmp = 0;
                }
                else {
                    tmp += dis (gg[i], gg[i+1]);
                }
            }
            ans = max (ans, tmp);
        }
    }
    return ans;
}

//半平面交,直线的左边代表有效区域 
bool HPIcmp (const Line &a, const Line &b) {
    if (fabs(a.k - b.k) > eps)
        return a.k < b.k;
    return cross (a.s - b.s, b.e - b.s) < 0; 
}
Line Q[maxn];
void HPI(Line line[], int n, Point res[], int &resn) {
    //半平面数组 半平面个数 半平面交顶点 半平面交顶点个数
    for (int i = 0; i < n; i++) line[i].get_angle ();
    int tot = n; 
    sort(line,line+n,HPIcmp); 
    tot = 1;
    for(int i = 1;i < n;i++){
        if(fabs(line[i].k - line[i-1].k) > eps)
            line[tot++] = line[i];
    }
    int head = 0, tail = 1; 
    Q[0] = line[0];
    Q[1] = line[1];
    resn = 0;
    for (int i = 2; i < tot; i++) {
        if (fabs(cross (Q[tail].e-Q[tail].s, Q[tail-1].e-Q[tail-1].s)) < eps || fabs(cross (Q[head].e-Q[head].s, Q[head+1].e-Q[head+1].s)) < eps)
            return;
        while(head < tail && (cross ((Q[tail]&Q[tail-1])-line[i].s, line[i].e-line[i].s)) > eps) tail--;
        while(head < tail && (cross ((Q[head]&Q[head+1]) - line[i].s, line[i].e-line[i].s)) > eps)
        head++; 
        Q[++tail] = line[i];
    }
    while(head < tail && (cross ((Q[tail]&Q[tail-1]) - Q[head].s, Q[head].e-Q[head].s)) > eps)
        tail--;
    while(head < tail && (cross ((Q[head]&Q[head-1]) -Q[tail].s, Q[tail].e-Q[tail].e)) > eps) 
        head++;
    if(tail <= head + 1)
        return; 
    for(int i = head; i < tail; i++)
        res[resn++] = Q[i]&Q[i+1]; 
    if(head < tail - 1)
        res[resn++] = Q[head]&Q[tail];
}

//最大空凸包面积 最大的内部没有别的点(边界可以包含)的凸包面积 复杂度O(n^3)
Point List[maxn]; double opt[maxn][maxn]; int seq[maxn], len; double max_area;
bool cmp (Point a, Point b) {
    int tmp = dcmp (cross (a, b));
    if (tmp != 0) return tmp > 0;
    tmp = dcmp (b.len2 ()-a.len2 ());
    return tmp > 0;
}
bool lessY (Point a, Point b) {
    return dcmp (b.y-a.y) > 0 || (dcmp (b.y-a.y) == 0 && dcmp (b.x-a.x) > 0);
}
void solve (Point *p, int n, int vv) {
    int t, i, j, _len; double v;
    for (len = i = 0; i < n; i++) {
        if (lessY (p[vv], p[i])) List[len++] = p[i]-p[vv];
    }
    for (i = 0; i < len ;i++) {
        for (j = 0; j< len; j++) {
            opt[i][j] = 0;
        }
    }
    sort (List, List+len, cmp);
    for (t = 1; t < len; t++) {
        _len = 0;
        for (i = t-1; i >= 0 && dcmp (cross (List[t], List[i])) == 0; i--);
        while (i >= 0) {
            v = cross (List[i], List[t])/2;
            seq[_len++] = i;
            for (j = i-1; j >= 0 && dcmp (cross (List[i]-List[t], List[j]-List[t])) > 0; j--);
            if (j >= 0) v += opt[i][j];
            get_max (max_area, v);
            opt[t][i] = v;
            i = j;
        }
        for (i = _len-2; i >= 0; i--) {
            get_max (opt[t][seq[i]], opt[t][seq[i+1]]);
        }
    }
}
double max_empty_convexhull_area (Point *p, int n) {
    //点集 点数 求最大面积的时候调用这个接口
    max_area = 0;
    for (int i = 0; i < n; i++) solve (p, n, i);
    return max_area;
}

int main() {
    int t; cin >> t;
    while(t--) {
        int id;
        double bx, cx, cy;
        cin >> id >> bx >> cx >> cy;
        Point a(0.0, 0.0), b(bx, 0.0), c(cx, cy);
        Circle o(a, b, c);
        Circle nqy = in_circle(a, b, c);
        Point i = nqy.p;
        // cout << i.x << ' ' << i.y << endl;
        Line ai(a, i), bi(b, i), ci(c, i);
        Point m, n, p;
        Point m1, m2, n1, n2, p1, p2;
        line_cirlce_intersection(ai, o, m1, m2);
        m = (a == m2) ? m1 : m2;
        line_cirlce_intersection(bi, o, n1, n2);
        n = (b == n2) ? n1 : n2;
        line_cirlce_intersection(ci, o, p1, p2);
        p = (c == p2) ? p1 : p2;
        // cout << m.x << ' ' << m.y << "  " << n.x << ' ' << n.y << "  " << p.x << ' ' << p.y << endl;
        Line mn(m, n), mp(m, p), np(n, p), ab(a, b), ac(a, c), bc(b, c);
        Point g = mn&ac, h = mn&bc, j = mp&bc, k = mp&ab, e = np&ab, f = np&ac;
        printf("%d %.4f %.4f %.4f %.4f %.4f %.4f\n", id, dis(e, f), dis(f, g), dis(g, h), dis(h, j), dis(j, k), dis(k, e));
    }
    return 0;
}