ll quickPow(int a, int b, int p) {
	int ans = 1, base = a;
	while(b) {
		if(b & 1) {
			ans = (ll)ans * base % p;
		}
		base = (ll)base * base % p;
		b >>= 1;
	}
	return ans;
}

ll quickPow(int a, int b) {
	ll ans = 1, base = a;
	while(b) {
		if(b & 1) {
			ans = min((ll)ans * base, (ll)1e7);
		}
		base = min((ll)base * base, (ll)1e7);
		b >>= 1;
	}
	return ans;
}

pair<int, ll> fun(int a, int b, int p) {
	if(b == 0) {
		return make_pair(a % p, a);
	}
	if(p == 1) {
		auto ret = make_pair(0, (ll)1e7);
		if(a == 1) {
			ret.second = a;
		} else if(b <= 10) {
			ret.second = a;
			for(int i = 0; i < b; i++) {
				ret.second = quickPow(ret.second, a);
			}
		}
		return ret;
	}
	
	auto ele = fun(a, b - 1, phi[p]);
	if(ele.second < phi[p]) {
		ele.first = quickPow(a, ele.first, p);
		ele.second = quickPow(a, ele.second);
	} else {
		ele.first = quickPow(a, ele.first % phi[p] + phi[p], p);
		ele.second = quickPow(a, ele.second);
	}
	return ele;
}
