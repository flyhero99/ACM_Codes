#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define mod 1000000007
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 1000005;

ll a[maxn], c[maxn], tot, M;
int n, k;

int main() {
	while(scanf("%d %d", &n, &k) != EOF) {
		k++; tot = 0;
		for(int i = 1;i <= n;i++) scanf("%lld", &a[i]);
		if(k == 1) {
			for(int i = 1;i <= n;i++) tot += a[i];
			M = tot/n;
			c[0] = 0;
			for(int i = 1;i < n;i++) {
				c[i] = c[i-1]+a[i]-M;
			}
			sort(c, c+n);
			ll x1 = c[n/2], ans=0;
			for(int i = 0;i < n;i++) ans += abs(x1-c[i]);
			printf("%lld\n", ans);
		}
		else if(n % k != 0) {
			ll b[maxn]; int j = 1;
			for(int i = 1;;) {
				b[j++] = a[i];
				if((i+k)%n == 0) i = n;
				else i = (i+k)%n;
				if(i == 1) break;
			}
			for(int i = 1;i <= n;i++) tot += b[i];
			M = tot/n;
			c[0] = 0;
			for(int i = 1;i < n;i++) {
				c[i] = c[i-1]+a[i]-M;
			}
			sort(c, c+n);
			ll x1 = c[n/2], ans=0;
			for(int i = 0;i < n;i++) ans += abs(x1-c[i]);
			printf("%lld\n", ans);
		}
		else if(n % k == 0) {
			int tmp = n/k; ll ans = 0;
			for(int x = 0;x < k;x++) { // 共有k个环，每个环内n/k (tmp) 个元素
				ll b[n/k+5]; int j = 1;
				for(int i = 1;;) {
					b[j++] = a[x+i];
					i += k;
					if(i > n) break;
				}
				// for(int i = 1;i <= tmp;i++) cout << b[i] << ' ';
				// cout << endl;
				for(int i = 1;i <= tmp;i++) tot += b[i];
				M = tot/tmp;
				c[0] = 0;
				for(int i = 1;i < tmp;i++) {
					c[i] = c[i-1]+b[i]-M;
				}
				sort(c, c+n);
				ll x1 = c[tmp/2], aans=0;
				for(int i = 0;i < tmp;i++) {
					aans = abs(x1-c[i]);
				}
				ans += aans;
				tot = 0;
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}