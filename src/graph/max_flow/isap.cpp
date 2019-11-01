struct edge{
    int v, val, nxt;
};

int  d[N], head[N], gap[N], cur[N], pre[N];
edge e[M << 1];
int  tot;

inline void init(){
    memset(head, -1, sizeof(head));
    memset(d, 0, sizeof(d));
    memset(gap, 0, sizeof(gap));
    tot = 0;
}

void addEdge(int u, int v, int val){
    e[tot].v   = v;
    e[tot].val = val;
    e[tot].nxt = head[u];
    head[u]    = tot++;
}

int ISAP(int n, int src, int des){
    memcpy(cur, head, sizeof(head));
    int sum = 0;
    int u = pre[src] = src;
    gap[0] = n;
    
    while(d[src] < n){
        if(u == des){
            int aug = inf, v;
            for(u = pre[des], v = des; v != src; v = u, u = pre[u])     aug = min(aug, e[cur[u]].val);
            for(u = pre[des], v = des; v != src; v = u, u = pre[u]){
                e[cur[u]].val   -= aug;
                e[cur[u]^1].val += aug;
            }
            sum += aug;
            continue;
        }
        
        bool flag = false;
        for(int& i = cur[u]; ~i; i = e[i].nxt){
            int v = e[i].v;
            if(d[u] == d[v] + 1 && e[i].val){
                pre[v] = u;
                u = v;
                flag = true;
                break;
            }
        }
        
        if(!flag){
            int mind = n;
            for(int i = head[u]; ~i; i = e[i].nxt){
                int v = e[i].v;
                if(e[i].val && d[v] < mind){
                    mind = d[v];
                    cur[u] = i;
                }
            }
            if((--gap[d[u]]) == 0)      break;
            d[u] = mind + 1;
            gap[d[u]]++;
            u = pre[u];
        }
    }
    return sum;
}
