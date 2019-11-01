const int N = (int)5000 + 3;
const int M = (int)50000 + 3;

struct Node {
    int u;
    ll d;
    bool operator < (const Node& b) const {
        return d > b.d;
    }
};
struct edge {
    int v, nxt, flow;
    ll cost;
};

int flow[N];
int pre[N], cur[N];
ll dis[N], h[N];
edge e[M * 4];
int head[N], tot;

inline void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

inline void addEdge(int u, int v, int flow, ll cost) {
    e[tot] = edge{v, head[u], flow, cost};
    head[u] = tot++;
    e[tot] = edge{u, head[v], 0, -cost};
    head[v] = tot++;
}

bool dijkstra(int src, int des, int n) {
    priority_queue<Node> que;
    fill(dis + 1, dis + n + 1, 1LL << 30);
    fill(flow + 1, flow + n + 1, 1LL << 30);
    dis[src] = 0, pre[src] = src;
    que.push(Node{src, 0});
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
            if(e[i].flow && dis[v] > dis[u] + e[i].cost + h[u] - h[v]) {
                dis[v] = dis[u] + e[i].cost + h[u] - h[v];
                flow[v] = min(flow[u], e[i].flow);
                pre[v] = u;
                cur[v] = i;
                que.push(Node{v, dis[v]});
            }
        }
    }
    return dis[des] != (1LL << 30);
}

pair<int, ll> solve(int src, int des, int n) {
    int maxFlow = 0;
    ll minCost = 0;
    while(dijkstra(src, des, n)) {
        int aug = flow[des];
        maxFlow += aug;
        minCost += aug * (dis[des] - h[src] + h[des]);
        for(int u = pre[des], v = des; v != src; v = u, u = pre[u]) {
            e[cur[v]].flow -= aug;
            e[cur[v] ^ 1].flow += aug;
        }
        for(int i = 1; i <= n; i++) {
            h[i] += dis[i];
        }
    }
    return make_pair(maxFlow, minCost);
}
