int m[N] = {23, 28, 33};
int a[N];
int m_tot = 23*28*33;

int extgcd(int a, int b, int& x, int& y){
    int d = a;
    if(!b){
        x = 1, y = 0;
    }else{
        d = extgcd(b, a%b, y, x);
        y -= a/b*x;
    }
    return d;
}

int res(){
    int ans = 0;
    for(int i = 0; i < N; i++){
        int mt = m_tot/m[i];
        int t, y;
        extgcd(mt, m[i], t, y);
        ans += a[i] * t * mt;
    }
    return (ans%m_tot + m_tot)%m_tot;
}
