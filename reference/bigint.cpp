const int L = 1210;
struct bint {
	int a[L];
	bint() {
		for (int i = 0; i < L; i++)
			a[i] = 0;
	}
	bint(int x) {
		for (int i = 0; i < L; i++)
			a[i] = 0;
		int len = 0;
		while(x > 0) {
			a[len++] = x % 10;
			x /= 10;
		}
	}
	bint(string s) {
		for (int i = 0; i < L; i++) {
			a[i] = 0;
		}
		int m = (int)s.size();
		for (int  i = 0; i < m; i++) {
			a[i] = s[m - 1 - i] - '0';
		}
	}

	bool operator ==(const bint &A) const {
		for (int i = 0; i < L; i++) {
			if (a[i] != A.a[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator < (const bint &A) const {
		for (int i = L - 1; i >= 0; i--) {
			if (a[i] != A.a[i]) {
				return a[i] < A.a[i];
			}
		}
		return false;
	}
	bint operator + (const bint &A) const {
		bint R;
		for (int i = 0; i < L; i++)
			R.a[i] = a[i] + A.a[i];
		for (int i = 0; i < L - 1; i++) {
			R.a[i + 1] += R.a[i] / 10;
			R.a[i] %= 10;
		}
		R.a[L - 1] %= 10;
		return R;
	}



	bint operator - (const bint &A) const {
		bint R;
		int owe = 0;
		for (int i = 0; i < L; i++) {
			R.a[i] = a[i] - A.a[i] - owe;
			owe = 0;
			if (R.a[i] < 0) {
				R.a[i] += 10;
				owe = 1;
			} 
		}
		return R;
	}

	bint operator * (const bint &A) const {
		bint R;
		for (int i = 0; i < L; i++)
			for (int j = 0; i + j < L; j++)
				R.a[i + j] += a[i] * A.a[j];
		for (int i = 0; i < L - 1; i++) {
			R.a[i + 1] += R.a[i] / 10;
			R.a[i] %= 10;
		}
		R.a[L - 1] %= 10;
		return R;
	}

	bint operator * (const int &x) const {
		bint R = *this;
		for (int i = 0; i < L; i++) {
			R.a[i] *= x;
		}
		for (int i = 0; i < L - 1; i++) {
			R.a[i + 1] += R.a[i] / 10;
			R.a[i] %= 10; 
		}
		R.a[L - 1] %= 10;
		return R;
	}

	bint operator / (const int &x) const {
		bint R = *this;
		int r = 0;
		for (int i = L - 1; i >= 0; i--) {
			r = (r * 10 + a[i]) ;
			R.a[i] = r / x;
			r %= x;
		}
		return R;
	}

	bint operator / (const bint &A) const {
		bint P = *this, Q = A;
		if (P < Q) {
			return bint(0);
		}
		if (P == Q) {
			return bint(1);
		}
		int delta = get_len() - Q.get_len();
		for (int i = 0; i < delta; i++) {
			Q = Q * 10;
		}
		int bei = 0;
		bint R = bint();
		for (int i = delta; i >= 0; i--) {
			while (!(P < Q)) {
				bei++;
				P = P - Q;
			}
			R.a[i] = bei;
			bei = 0;
			Q = Q / 10;
		}
		return R;
	}

	bint operator % (const bint &A) const {
		bint P = *this, Q = A;		
		if (P < Q) {
			return P;
		}
		if (P == Q) {
			return bint(0);
		}
		int delta = get_len() - Q.get_len();
		for (int i = 0; i < delta; i++) {
			Q = Q * 10;
		}
		for (int i = delta; i >= 0; i--) {
			while (!(P < Q)) {
				P = P - Q;
			}
			Q = Q / 10;
		}
		return P;
	}

	int operator % (const int &x) const {
		int r = 0;
		for (int i = L - 1; i >= 0; i--) {
			r = (r * 10 + a[i]) % x;
		}
		return r;
	}

	int get_len() const {
		int ret = L;
		while(ret >= 1 && a[ret - 1] == 0) {
			ret--;
		}
		return ret;
	}
	void print() {
		int m = L - 1;
		while(m >= 1 && a[m] == 0) m--;
		for (int i = m; i >= 0; i--)
			printf("%d", a[i]);
		printf("\n");
	}
};