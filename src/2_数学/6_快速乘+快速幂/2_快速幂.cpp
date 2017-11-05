ll Pow(ll a, ll n, ll mod) {
	ll t = 1;
	for (; n; n >>= 1, a = (a * a % mod))
		if (n & 1) t = (t * a % mod);
	return t;
}
