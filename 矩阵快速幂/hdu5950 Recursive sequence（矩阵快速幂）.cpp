#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 105;
const ll mod = 2147493647;

struct mat {
	ll a[7][7];
};

mat init() {
	mat res;
	memset(res.a, 0, sizeof(res.a));
	for(int i = 0;i < 7;i++) {
		res.a[i][i] = 1;
	}
	return res;
}

mat mul(mat aa, mat bb) {
	mat ans;
	for(int i = 0;i < 7;i++) {
		for(int j = 0;j < 7;j++) {
			ans.a[i][j] = 0;
			for(int k = 0;k < 7;k++) {
				aa.a[i][k] %= mod;
				bb.a[k][j] %= mod;
				ans.a[i][j] = (ans.a[i][j] + (aa.a[i][k]*bb.a[k][j])%mod) % mod;
			}
		}
	}
	return ans;
}

mat qpow(mat aa, ll bb) {
	mat res = init();
	while(bb) {
		if(bb & 1) {
			res = mul(res, aa);
		}
		aa = mul(aa, aa);
		bb >>= 1;
	}
	return res;
}

int main() {
	mat coef = {1, 2, 1, 4, 6, 4, 1,
				1, 0, 0, 0, 0, 0, 0,
				0, 0, 1, 4, 6, 4, 1,
				0, 0, 0, 1, 3, 3, 1,
				0, 0, 0, 0, 1, 2, 1,
				0, 0, 0, 0, 0, 1, 1,
				0, 0, 0, 0, 0, 0, 1};
	int t;
	scanf("%d", &t);
	ll n, x, y;
	while(t--) {
		cin >> n >> x >> y;
		if(n == 1) cout << x << endl;
		else if(n == 2) cout << y << endl;
		else {
			mat ans = qpow(coef, n-2);
			ll res = 0;
			res = (res + (ans.a[0][0]*y)%mod) % mod;
			res = (res + (ans.a[0][1]*x)%mod) % mod;
			res = (res + (ans.a[0][2]*16)%mod) % mod;
			res = (res + (ans.a[0][3]*8)%mod) % mod;
			res = (res + (ans.a[0][4]*4)%mod) % mod;
			res = (res + (ans.a[0][5]*2)%mod) % mod;
			res = (res + (ans.a[0][6]*1)%mod) % mod;
			cout << res << endl;
		}
	}
	return 0;
}