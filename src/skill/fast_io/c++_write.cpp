char WritellBuffer[1024];
template <typename T>
inline void write(T a,char end){
    ll cnt=0,fu=1;
    if(a<0){putchar('-');fu=-1;}
    do{WritellBuffer[++cnt]=fu*(a%10)+'0';a/=10;}while(a);
    while(cnt){putchar(WritellBuffer[cnt]);--cnt;}
    if(end) putchar(end);
}
