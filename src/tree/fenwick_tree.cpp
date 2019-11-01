ll tree[N];

inline int lowbit(int x) {
	return x & -x;
}
 
inline ll query(int x) {
	ll ret = 0;
	for(; x > 0; x -= lowbit(x)) {
		ret += tree[x];
	}
	return ret;
} 
 
inline void update(int x, ll val) {
	for(; x < N; x += lowbit(x)) {
		tree[x] += val;
	}
}
