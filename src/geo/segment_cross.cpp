struct Point {
    double x, y;
};

int dcmp(double d) {
    if(fabs(d) < eps) return 0;
    return (d > 0) ? 1 : -1;
}

double cross(const Point &A, const Point &B, const Point &C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

int xycmp(double p, double mini, double maxi) {
    return dcmp(p - mini) * dcmp(p - maxi);
}

/*
前提条件：a在bc直线上
返回：
1表示a不在线段bc上
0表示a在b点或者c点上
-1表示a在线段bc上
*/
int betweencmp(const Point &a, const Point &b, const Point &c) {
    if(fabs(b.x - c.x) > fabs(b.y - c.y)) return xycmp(a.x, min(b.x, c.x), max(b.x, c.x));
    else return xycmp(a.y, min(b.y, c.y),max(b.y, c.y));
}

//判断线段ab是否与cd相交， 交点记在p
//返回值：0表示不相交； 1表示规范相交； 2表示非规范相交
//p为交点
int segcross(const Point &a, const Point &b, const Point &c, const Point &d, Point &p) {
    double s1, s2, s3, s4;
    int d1, d2, d3, d4;

    d1 = dcmp(s1 = cross(a, b, c));
    d2 = dcmp(s2 = cross(a, b, d));
    d3 = dcmp(s3 = cross(c, d, a));
    d4 = dcmp(s4 = cross(c, d, b));

    //判断规范相交：交点不会在端点上
    if((d1 ^ d2) == -2 && (d3 ^ d4) == -2)
    {
        p.x = (c.x * s2 - d.x * s1) / (s2-s1);
        p.y = (c.y * s2 - d.y * s1) / (s2-s1);
        return 1;
    }

    // 判断非规范相交：交点在端点上
    if(d1 == 0 && betweencmp(c, a, b) <= 0) {
        p = c;
        return 2;
    }
    if(d2 == 0 && betweencmp(d, a, b) <= 0) {
        p = d;
        return 2;
    }
    if(d3 == 0 && betweencmp(a, c, d) <= 0) {
        p = a;
        return 2;
    }
    if(d4 == 0 && betweencmp(b, c, d) <= 0) {
        p = d;
        return 2;
    }

    return 0;
}
