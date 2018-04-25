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
#define inf 0x3f3f3f3f

const int maxn = 100000+5;
const double eps = 1e-6;
const double pi = 3.141592653589793238462643385;

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

ll sum[maxn<<2], add[maxn<<2];
int n, m;

struct node {
	int l, r;
	int mid() {return (l+r) >> 1;}
}tr[maxn<<2];

void pushup(int rt) {sum[rt] = sum[rt<<1]+sum[rt<<1|1];}

void pushdown(int rt, int m) {
	if(add[rt]) {
		add[rt<<1] += add[rt];
		add[rt<<1|1] += add[rt];
		sum[rt<<1] += add[rt]*(m - (m>>1));
		sum[rt<<1|1] += add[rt] * (m>>1);
		add[rt] = 0;
	}
}

void build(int l, int r, int rt) {
	tr[rt].l = l, tr[rt].r = r; add[rt] = 0;
	if(l == r) {scanf("%lld", &sum[rt]); return;}
	int m = tr[rt].mid();
	build(l, m, rt<<1);
	build(m+1, r, rt<<1|1);
	pushup(rt);
}

void update(int c, int l, int r, int rt) {
	if(tr[rt].l == l && tr[rt].r == r) {
		add[rt] += (ll) c;
		sum[rt] += (ll) c * (r-l+1);
		return;
	}
	if(tr[rt].l == tr[rt].r) return;
	pushdown(rt, tr[rt].r-tr[rt].l+1);
	int m = tr[rt].mid();
	if(r <= m) update(c, l, r, rt<<1);
	else if(l > m) update(c, l, r, rt<<1|1);
	else {
		update(c, l, m, rt<<1);
		update(c, m+1, r, rt<<1|1);
	}
	pushup(rt);
}

ll query(int l, int r, int rt) {
	if(l == tr[rt].l && r == tr[rt].r) return sum[rt];
	pushdown(rt, tr[rt].r-tr[rt].l+1);
	int m = tr[rt].mid();
	ll res = 0;
	if(r <= m) res += query(l, r, rt<<1);
	else if(l > m) res += query(l, r, rt<<1|1);
	else {
		res += query(l, m, rt<<1);
		res += query(m+1, r, rt<<1|1);
	}
	return res;
}

int main() {
	// ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	while(scanf("%d %d", &n, &m) != EOF) {
		build(1, n, 1);
		while(m--) {
			char ss[2]; int x, y, z;
			scanf("%s", ss);
			if(ss[0] == 'Q') {
				scanf("%d %d", &x, &y);
				printf("%lld\n", query(x, y, 1));
				// cout << query(x, y, 1) << endl;
			}
			else if(ss[0] == 'C') {
				scanf("%d %d %d", &x, &y, &z);
				update(z, x, y, 1);
			}
		}
	}
	return 0;
}