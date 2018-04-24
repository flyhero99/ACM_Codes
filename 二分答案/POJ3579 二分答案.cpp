#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define ull unsigned long long
const int maxn = 100000+5;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}

int cas, n, m;
int a[maxn];

bool ok(int d) {
	int cnt = 0;
	for(int i = 0; i < n; i++) {
		cnt += (upper_bound(a+i, a+n, a[i]+d)-(a+i) - 1);
	}
	if(cnt >= m) return 1;
	else return 0;
}

int main() {
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		sort(a, a+n);
		int t = n*(n-1) / 2;
		m = (t+1) / 2;
		int l = -1, r = a[n-1]-a[0];
		while(r-l > 1) {
			int mid = (r+l) >> 1;
			if(ok(mid)) r = mid;
			else l = mid;
		}
		printf("%d\n", r);
	}
	return 0;
}