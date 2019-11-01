double a, b, c, d;

inline double f(double x) {
    return (c * x + d) / (a * x + b);
}

inline double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) * (f(l) + f(r) + 4 * f(mid)) / 6;
}

inline double calc(double l, double r, double eps, double ans) {
    double mid = (l + r) / 2;
    double lres = simpson(l, mid), rres = simpson(mid, r);
    if(fabs(lres + rres - ans) <= 15 * eps) {
        return lres + rres + (lres + rres - ans) / 15;
    }
    return calc(l, mid, eps / 2, lres) + calc(mid, r, eps / 2, rres);
}

int main() {
    double l, r;
    while(~scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r)) {
        printf("%.6f\n", calc(l, r, 1e-6, simpson(l, r)));
    }
}
