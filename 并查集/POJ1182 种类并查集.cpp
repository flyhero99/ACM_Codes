#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 5e4+10;

template<class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i++)
        cout << a[i] << " ";
    cout << endl;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}

int n, m;
int pre[maxn], group[maxn];

void init() {
	for(int i = 0; i <= n; i++) pre[i] = i;
	mem(group, 0);
}

int f(int x) {
	if(pre[x] == x) return x;
	int ff = f(pre[x]);
	group[x] = (group[x]+group[pre[x]]) % 3;
	return pre[x] = ff;
}

bool uunion(int type, int x, int y) {
	int fx = f(x), fy = f(y);
	if(fx == fy) {
		if(type == 1 && group[x] != group[y]) return true;
		if(type == 2 && (group[y]+1)%3 != group[x]) return true;
		return false;
	}
	group[fx] = (group[y]-group[x]+2+type) % 3;
	pre[fx] = fy;
	return false;
}

int main() {
	scanf("%d %d", &n, &m);
	int ans = 0;
	init();
	for(int i = 0; i < m; i++) {
		int t, x, y;
		t = read(), x = read(), y = read();
		if(x > n || y > n || (t==2 && x==y)) {
			ans++;
			continue;
		}
        if(f(x) == f(y)) {
            if(t == 1 && group[x] != group[y]) ans++;
            if(t == 2 && (group[y]+1) % 3 != group[x]) ans++;
        }
        else {
            if(uunion(t, x, y)) ans++;
        }
	}
	printf("%d\n", ans);
	return 0;
}