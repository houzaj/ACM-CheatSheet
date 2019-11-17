const int N = (int)5000 + 3;
const int M = (int)1e6 + 3;
const ll inf = 1LL << 60;

struct Node {
    int u;
    ll d;
    bool operator < (const Node& b) const {
        return d > b.d;
    }
};
struct edge {
    int v, nxt;
    ll flow, cost;
};

edge e[M << 1];
int head[N], tot;
int cur[N];
bool used[N];
ll dis[N], h[N];

inline void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

inline void addEdge(int u, int v, ll flow, ll cost) {
    e[tot] = edge{v, head[u], flow, cost};
    head[u] = tot++;
    e[tot] = edge{u, head[v], 0, -cost};
    head[v] = tot++;
}

bool dijkstra(int src, int des) {
    priority_queue<Node> que;
    fill(dis, dis + N, inf);
    memcpy(cur, head, sizeof(head));
    dis[des] = 0;
    que.push(Node{des, 0});
    while(!que.empty()) {
        Node ele = que.top();
        que.pop();
        int u = ele.u;
        ll d = ele.d;

        if(d > dis[u]) {
            continue;
        }

        for(int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if(e[i^1].flow && dis[v] > dis[u] - e[i].cost + h[u] - h[v]) {
                dis[v] = dis[u] - e[i].cost + h[u] - h[v];
                que.push(Node{v, dis[v]});
            }
        }
    }
    return dis[src] != inf;
}

int dfs(int u, int des, ll low, ll& totalCost) {
    if(u == des) {
        return low;
    }
    used[u] = true;
    int sum = 0;
    for(int& i = cur[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        ll du = (dis[u] - h[des] + h[u]);
        ll dv = (dis[v] - h[des] + h[v]);
        if(!used[v] && e[i].flow && du - e[i].cost == dv) {
            int aug = dfs(v, des, min(e[i].flow, low - sum), totalCost);
            if(aug) {
                e[i].flow -= aug;
                e[i ^ 1].flow += aug;
                sum += aug;
                totalCost += 1LL * aug * e[i].cost;
            }
            if(sum == low) {
                break;
            }
        }
    }
    used[u] = false;
    return sum;
}

inline void initH(int src, int des, int n) {
    static bool inq[N];
    fill(dis, dis + n + 1, inf);
    dis[des] = 0;
    queue<int> que;
    que.push(des);
    inq[des] = true;
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        inq[u] = false;
        for(int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if(e[i^1].flow && dis[v] > dis[u] - e[i].cost) {
                dis[v] = dis[u] - e[i].cost;
                if(!inq[v]) {
                    inq[v] = true;
                    que.push(v);
                }
            }
        }
    }
    for(int i = 0; i <= n; i++) {
        h[i] = dis[i];
    }
}

inline pair<ll, ll> solve(int src, int des, int n) {
    //initH(src, des, n);    //非负权图可不执行
    pair<ll, ll> pr(0LL, 0LL);
    while(dijkstra(src, des)) {
        while(true) {
            ll x = dfs(src, des, inf, pr.second);
            pr.first += x;
            if(!x) {
                break;
            }
        }
        for(int i = 0; i <= n; i++) {
            h[i] += dis[i];
        }
    }
    return pr;
}