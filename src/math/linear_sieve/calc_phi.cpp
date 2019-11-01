int prime[N], phi[N];
int prime_tot;
bool used[N];

void euler(){
    memset(used, true, sizeof(used));
    prime_tot = 0;
    phi[1] = 1;

    for(int i = 2; i < N; i++){
        if(used[i]){
            prime[prime_tot++] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; i*prime[j] < N; j++){
            used[i*prime[j]] = false;
            if(i%prime[j] == 0){
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }else{
                phi[i*prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
