bool used[N];
Point pt[N], resPt[N];
void Andrew(int n, Point* resPt, int& m) {
    memset(used, false, sizeof(used));
    sort(pt + 1, pt + 1 + n);
    pstk = 0;
    stk[++pstk] = 1;
    for(int i = 2; i <= n; i++) {
        while(pstk > 1 && dcmp(cross(pt[stk[pstk]] - pt[stk[pstk - 1]], pt[i] - pt[stk[pstk]])) <= 0) {
            used[stk[pstk--]] = false;
        }
        used[i] = true;
        stk[++pstk] = i;
    }
    int tmp = pstk;
    for(int i = n - 1; i >= 1; i--) {
        if(used[i]) {
            continue;
        }
        while(pstk > tmp && dcmp(cross(pt[stk[pstk]] - pt[stk[pstk - 1]], pt[i] - pt[stk[pstk]])) <= 0) {
            used[stk[pstk--]] = false;
        }
        used[i] = true;
        stk[++pstk] = i;
    }
    m = pstk;
    for(int i = 1; i <= m; i++) {
        resPt[i] = pt[stk[i]];
    }
}
