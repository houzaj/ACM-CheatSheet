int d[N];

struct Node {
    int u, w;

    bool operator < (const Node& b) const {
        if(d[u] + w != d[b.u] + b.w) {
            return d[u] + w > d[b.u] + b.w;
        }
        return w > b.w;
    }
};

struct edge{
    int v, w, nxt;
};

struct Graph {
    edge e[N];
    int head[N], tot;

    inline void init() {
        tot = 0;
        memset(head, -1, sizeof(head));
    }

    inline void addEdge(int u, int v, int w) {
        e[tot] = edge{v, w, head[u]};
        head[u] = tot++;
    }
};

Graph g, ginv;
bool inque[N];
int cnt[N];

void solveD(int des) {
    memset(d, 0x3f, sizeof(d));
    memset(inque, false, sizeof(inque));
    queue<int> que;

    d[des] = 0;
    que.push(des);
    inque[des] = true;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        inque[u] = false;

        for(int i = ginv.head[u]; ~i; i = ginv.e[i].nxt) {
            int v = ginv.e[i].v;
            if(d[v] > d[u] + ginv.e[i].w) {
                d[v] = d[u] + ginv.e[i].w;
                if(inque[v] == false) {
                    que.push(v);
                    inque[v] = true;
                }
            }
        }
    }
}

int solve(int src, int des, int k) {
    memset(cnt, 0, sizeof(cnt));
    priority_queue<Node> que;
    que.push(Node{src, 0});

    while(!que.empty()) {
        int u = que.top().u;
        int w = que.top().w;
        que.pop();

        cnt[u]++;
        if(cnt[u] == k && u == des) {
            return w;
        }

        for(int i = g.head[u]; ~i; i = g.e[i].nxt) {
            int v = g.e[i].v;
            que.push(Node{v, w + g.e[i].w});
        }
    }
    return false;
}
