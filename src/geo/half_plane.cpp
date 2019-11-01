const int N = 1500 + 15;
const double eps = 1e-8;

struct Point{
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    Point operator - (const Point& b) {
        return Point(x - b.x, y - b.y);
    }
};
typedef Point Vector;

struct Line{
    Point a, b;
    double angle;
    void getAngle() {angle = atan2(b.y - a.y, b.x - a.x);}
    Line(){}
    Line(Point a, Vector b): a(a), b(b) {}
};

vector<Line> hp;
vector<Point> pt;
vector<Point> ans;
Line que[N];

int dcmp(double x) {
    return x < -eps ? -1 : x > eps;
}

double cross(Vector a, Vector b){
    return a.x * b.y - a.y * b.x;
}

double area(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

// 点是否在线的右边（不含在线上的情况）
bool isOnLineRight(Line u, Point v){
    return dcmp(cross(u.b - u.a, v - u.a)) < 0;
}

// 按极角顺时针排序
bool cmp(Line u, Line v) {
    int d = dcmp(u.angle - v.angle);
    if(d) return d > 0;
    return dcmp(cross(u.b - u.a, v.b - u.a)) < 0;
}

Point getLineIntersection(Line u, Line v){
    Point ret = u.a;
    double t = ((u.a.x-v.a.x) * (v.a.y-v.b.y)
               -(u.a.y-v.a.y) * (v.a.x-v.b.x))
             / ((u.a.x-u.b.x) * (v.a.y-v.b.y)
               -(u.a.y-u.b.y) * (v.a.x-v.b.x));
    ret.x += (u.b.x-u.a.x) * t, ret.y += (u.b.y-u.a.y) * t;
    return ret;
}

// 判断l2,l3的交点时候在l1的右边
bool judge(Line l1, Line l2, Line l3) {
    Point p = getLineIntersection(l2, l3);
    return isOnLineRight(l1, p);
}

void hpi(){//half-plane intersection
    ans.clear();
    sort(hp.begin(), hp.end(), cmp);
    int m = 0;
    // 平行的取第一个，与排序函数的写法有关，反正是取最左边的（严格的说，应该是向量的左边）
    for(int i = 0; i < hp.size(); i++){
        if(i && dcmp(hp[i].angle - hp[m - 1].angle) == 0)   continue;
        hp[m++] = hp[i];
    }
    hp.erase(hp.begin() + m, hp.end());

    que[1] = hp[0], que[2] = hp[1];
    int head = 1, tail = 2;
    for(int i = 2; i < hp.size(); i++){
        while(head < tail && judge(hp[i], que[tail - 1], que[tail]))     tail--;
        while(head < tail && judge(hp[i], que[head + 1], que[head]))     head++;
        que[++tail] = hp[i];
    }
    while(head < tail && judge(que[head], que[tail - 1], que[tail]))     tail--;
    while(head < tail && judge(que[tail], que[head + 1], que[head]))     head++;

    if(tail <= head + 1){ //若半平面交退化为点或线
        return;
    }

    // 为了方便记录，直接把最后一条线放到最前面，避免最后还要保存头尾两条线的交点
    que[head - 1] = que[tail];
    for(int i = head; i <= tail; i++){
        ans.push_back(getLineIntersection(que[i], que[i - 1]));
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        hp.clear();
        pt.clear();
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            double x, y;
            scanf("%lf%lf", &x, &y);
            pt.push_back(Point(x, y));
            if(i){
                hp.push_back(Line(pt[i], pt[i - 1]));
                hp[hp.size() - 1].getAngle();
            }
        }
        hp.push_back(Line(pt[0], pt[n - 1]));
        hp[hp.size() - 1].getAngle();
        hpi();

        double res = 0;
        for(int i = 2; i < ans.size(); i++){
            res += area(ans[0], ans[i - 1], ans[i]);
        }
        printf("%.2f\n", fabs(res / 2) + eps);
    }
    return 0;
}
