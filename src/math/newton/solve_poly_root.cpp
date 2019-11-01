inline double fun(const vector<double>& a, double x) {
	double res = 0;
	for(int i = 0; i < (int)a.size(); i++) {
		res += pow(x, i) * a[i];
	}
	return res;
}

inline double newton(const vector<double>& a, const vector<double>& aDiff) {
	double x = -30;
	for(int i = 0; i < 1000000; i++) {
		double nx = x - fun(a, x) / fun(aDiff, x);
		if(dcmp(x - nx) == 0) {
			return nx;
		}
		x = nx;
	}
	return x;
}

inline vector<double> getRoots(vector<double> a) {
	vector<double> res;
	while(a.size() > 1) {
		vector<double> aDiff, na;
		for(int i = 1; i < (int)a.size(); i++) {
			aDiff.push_back(i * a[i]);
		}
		double x0 = newton(a, aDiff);
		res.push_back(x0);
		for(int i = a.size() - 1; i >= 1; i--) {
			a[i - 1] = a[i - 1] + x0 * a[i];
		}

		a.erase(a.begin());
	}
	return res;
}

