ll f[N], sum[N];
bool isprime[N];
int  prime[N], tot;
int  cnt[N];

int quickPow(int a, int b){
    int ans = 1, base = a;
    while(b){
        if(b&1)     ans = ans * base;
        base = base * base;
        b >>= 1;
    }
    return ans;
}

void init(){
    memset(isprime, true, sizeof(isprime));
    tot = 0, f[1] = 1, sum[1] = 1;
    for(int i = 2; i < N; i++){
        if(isprime[i]){
            prime[tot++] = i;
            cnt[i]++;
        }
        for(int j = 0; j < tot && i * prime[j] < N; j++){
            isprime[i * prime[j]] = false;
            if(i % prime[j] == 0){
                cnt[i * prime[j]] = cnt[i] + 1;
                break;
            }else{

                cnt[i * prime[j]] = 1;
            }
        }
    }

    for(int i = 0; i < tot && (ll)prime[i] * prime[i] < N; i++){
        f[prime[i] * prime[i]] = 1;
        ll cur = (ll)prime[i] * prime[i] * prime[i];
        while(cur < N){
            f[cur] = 0;
            cur = cur * prime[i];
        }
    }

    for(int i = 2; i < N; i++){
        if(isprime[i]){
            f[i] = 2;
        }
        for(int j = 0; j < tot && i * prime[j] < N; j++){
            if(i % prime[j] == 0){
                int pk = quickPow(prime[j], cnt[i * prime[j]]);
                f[i * prime[j]] = f[pk] * f[i * prime[j] / pk];
                break;
            }else{
                f[i * prime[j]] = f[i] * f[prime[j]];
            }
        }
        sum[i] = f[i] + sum[i - 1];
    }
}

