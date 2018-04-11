#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 100005;

int cas, n;
int pre[maxn], group[maxn];

void init() {
	for(int i = 0; i <= n; i++) pre[i] = i;
	mem(group, 0);
}

int f(int x) {
	if(pre[x] == x) return x;
	int ff = f(pre[x]);
	group[x] = (group[x]+group[pre[x]]) % 2;
	return pre[x] = ff;
}

bool uunion(int x, int y, int type) {
	int fx = f(x), fy = f(y);
	if(fx == fy) {
		if(type == 0 && group[x] != group[y]) return true;
		if(type == 1 && group[x] == group[y]) return true;
		return false;
	}
	group[fx] = (type+group[x]+group[y]) % 2;
	pre[fx] = fy;
	return false;
}

int main() {
	cin >> cas;
	while(cas--) {
		cin >> n;
		int ans = 0, flag = 1;
		init();
		for(int i = 1; i <= n; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			if(flag) {
				if(f(u) == f(v)) {
					if(w == 0 && group[u] != group[v]) {
						ans = i;
						flag = 0;
					}
					if(w == 1 && group[u] == group[v]) {
						ans = i;
						flag = 0;
					}
				}
				else {
					if(uunion(u, v, w)) {
						ans = i;
						flag = 0;
					}
				}
			}
		}
		if(ans == 0) cout << "PERFECT!" << endl;
		else cout << ans << endl;
	}
	return 0;
}