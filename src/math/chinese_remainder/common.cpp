// x = a[i] mod m[i]

ll a[N], m[N];

ll extgcd(ll a, ll b, ll& x, ll& y){
    ll d = a;
    if(!b){
        x = 1, y = 0;
    }else{
        d = extgcd(b, a%b, y, x);
        y -= a/b*x;
    }
    return d;
}

ll crt(ll n){
    if(n == 1){
        return (m[0] > a[0] ? a[0] : -1);
    }else{
        for(int i = 1; i < n; i++){
            if(m[i] <= a[i])    return -1;
            
            ll x, y;
            ll d = extgcd(m[0], m[i], x, y);
            if((a[i] - a[0])%d != 0)    return -1;
            ll t = m[i]/d;
            ll k = ((a[i] - a[0])/d*x%t + t)%t;
            a[0] = m[0] * k + a[0];
            m[0] = m[0] * m[i]/d;
            a[0] = (a[0]%m[0] + m[0])%m[0];
        }
    }
    return a[0];
}

