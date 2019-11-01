int st[N], low[N], cnt[N], nodeChildNums[N];
int dfn;
bool isCut[N], isRoot[N], used[N];

inline void read(int& x) {
    scanf("%d", &x);
}

inline void addEdge(int u, int v) {
    e[tot] = edge{v, head[u]};
    head[u] = tot++;
}

void Tarjan(int u, int pre) {
    st[u] = low[u] = ++dfn;
    int childNums = 0;
    for(int i = head[u]; ~i; i = e[i].nxt) {
        int v = e[i].v;
        if(st[v] == 0) {
            childNums++;
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] >= st[u]) {
                nodeChildNums[u]++;
                isCut[u] = true;
            }
        } else if(v != pre && st[v] < st[u]) {
            low[u] = min(low[u], st[v]);
        }
    }
    if(pre == -1 && childNums == 1) {
        isCut[u] = false;
    }
}

int main() {
    int u, v, csn = 1;
    while(true) {
        tot = dfn = 0;
        for(int i = 1; i < N; i++) {
            head[i] = -1;
            st[i] = nodeChildNums[i] = 0;
            isRoot[i] = isCut[i] = false;
        }

        v = -1;
        while(scanf("%d", &u) && u) {
            scanf("%d", &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        if(v == -1) {
            break;
        }

        if(csn != 1) {
            puts("");
        }
        printf("Network #%d\n", csn++);
        for(int i = 1; i < N; i++) {
            if(st[i] == 0) {
                isRoot[i] = true;
                Tarjan(i, -1);
            }
        }

        bool flag = true;
        for(int i = 1; i <= 1000; i++) {
            if(isCut[i]) {
                flag = false;
                printf("  SPF node %d leaves %d subnets\n", i, nodeChildNums[i] + (isRoot[i] == false));
            }
        }
        if(flag) {
            puts("  No SPF nodes");
        }
    }
    return 0;
}
