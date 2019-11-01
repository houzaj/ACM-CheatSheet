#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    int l, r;
    mutable int val;
    inline int len() const {
        return r - l + 1;
    }
    bool operator < (const Node& b) const {
        return l < b.l;
    }
};

set<Node> st;

inline set<Node>::iterator split(int pos) {
    auto it = st.lower_bound(Node{pos, 0, 0});
    if(it != st.end() && it->l == pos) {
        return it;
    }
    --it;
    ll v = it->val;
    int l = it->l, r = it->r;
    st.erase(it);
    st.insert(Node{l, pos - 1, v});
    return st.insert(Node{pos, r, v}).first;
}

inline void assignVal(int l, int r, int v) {
    auto itr = split(r + 1), itl = split(l);
    st.erase(itl, itr);
    st.insert(Node{l, r, v});
}

inline void reverse(int l, int r) {
    auto itr = split(r + 1), itl = split(l);
    for(auto it = itl; it != itr; it++) {
        it->val ^= 1;
    }
}

inline int sum(int l, int r) {
    auto itr = split(r + 1), itl = split(l);
    int res = 0;
    for(auto it = itl; it != itr; it++) {
        res += (it->val == 1) * it->len();
    }
    return res;
}


inline int calc(int l, int r) {
    auto itr = split(r + 1), itl = split(l);
    int res = 0, cnt = 0;
    for(auto it = itl; it != itr; it++) {
        if(it->val) {
            cnt += it->len();
        } else {
            cnt = 0;
        }
        res = max(res, cnt);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    while(cin >> n >> m) {
        st.clear();
        for(int i = 1, val; i <= n; i++) {
            cin >> val;
            st.emplace(Node{i, i, val});
        }

        while(m--) {
            // ...
    }
}
