const int N = (int)1200 + 15;
const int M = (int)120000 + 15;
const int inf = 0x3f3f3f3f;

struct edge {
    int v, nxt, flow;
};

edge e[M * 2];
int head[N], tot, ht[N], ex[N], gap[N << 1];

struct cmp {
    inline bool operator () (int a, int b) const {
        return ht[a] < ht[b];
    }
};
priority_queue<int, vector<int>, cmp> que;
bool inq[N];

inline void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

inline void addEdge(int u, int v, int flow) {
    e[tot] = edge{v, head[u], flow};
    head[u] = tot++;
    e[tot] = edge{u, head[v], 0};
    head[v] = tot++;
}

inline bool bfsInit(int src, int des, int n) {
    memset(ht, 0x3f, sizeof(ht));
    queue<int> que;
    que.push(des);
    ht[des] = 0;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        for(int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if(e[i ^ 1].flow && ht[v] > ht[u] + 1) {
                ht[v] = ht[u] + 1;
                que.push(v);
            }
        }
    }
    return ht[src] != inf;
}

inline bool push(int u, int src, int des) {
    for(int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v, w = e[i].flow;
        if(!w || ht[u] != ht[v] + 1) {
            continue;
        }
        int k = min(w, ex[u]);
        ex[u] -= k;
        ex[v] += k;
        e[i].flow -= k;
        e[i ^ 1].flow += k;
        if(v != src && v != des && !inq[v]) {
            que.push(v);
            inq[v] = true;
        }
        if(!ex[u]) {
            return false;
        }
    }
    return true;
}

inline void relabel(int u) {
    ht[u] = inf;
    for(int i = head[u]; ~i; i = e[i].nxt) {
        if(e[i].flow) {
            ht[u] = min(ht[u], ht[e[i].v] + 1);
        }
    }
}

inline int hlpp(int src, int des, int n) {
    if(!bfsInit(src, des, n)) {
        return 0;
    }
    ht[src] = n;
    memset(gap, 0, sizeof(gap));
    for(int i = 1; i <= n; i++) {
        if(ht[i] != inf) {
            gap[ht[i]]++;
        }
    }
    for(int i = head[src]; ~i; i = e[i].nxt) {
        int v = e[i].v, w = e[i].flow;
        if(!w) {
            continue;
        }
        ex[src] -= w;
        ex[v] += w;
        e[i].flow -= w;
        e[i ^ 1].flow += w;
        if(v != src && v != des && !inq[v]) {
            que.push(v);
            inq[v] = true;
        }
    }
    while(!que.empty()) {
        int u = que.top();
        que.pop();
        inq[u] = false;
        if(push(u, src, des)) {
            if((--gap[ht[u]]) == 0) {
                for(int v = 1; v <= n; v++) {
                    if(v != src && v != des && ht[v] > ht[u] && ht[v] < n + 1) {
                        ht[v] = n + 1;
                    }
                }
            }
            relabel(u);
            gap[ht[u]]++;
            que.push(u);
            inq[u] = true;
        }
    }
    return ex[des];
}
