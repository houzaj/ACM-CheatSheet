ll mu[N], sum[N];
bool isprime[N];
int prime[N], tot;

void init(){
    memset(isprime, true, sizeof(isprime));
    tot = 0, mu[1] = 1, sum[1] = 1;
    for(int i = 2; i < N; i++){
        if(isprime[i]){
            prime[tot++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < tot && i * prime[j] < N; j++){
            isprime[i * prime[j]] = false;
            if(i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                break;
            }else{
                mu[i * prime[j]] = -mu[i];
            }
        }
        sum[i] = sum[i - 1] + mu[i];
    }
}
