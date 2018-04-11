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
double dp[33][3][3][3][3][3][3][3];

void dfs(int att, int a, int b, int c, int d, int e, int f, int g) {
	int sum = a+b+c+d+e+f+g;
	if(sum == 0) { // 场上已经没有怪了
		dp[att][a][b][c][d][e][f][g] = 1.0;
		return;
	}
	if(att == 0 || att < sum) return; // 剪枝
	int tot = 1 + (a!=0) + (b!=0) + (c!=0) + (d!=0) + (e!=0) + (f!=0) + (g!=0); // 场上存活的怪数+脸，表示可能性总数
	if(a) { // 打a
		if(dp[att-1][a-1][b][c][d][e][f][g] == 0.0) {
			dfs(att-1, a-1, b, c, d, e, f, g);
		}
		dp[att][a][b][c][d][e][f][g] += dp[att-1][a-1][b][c][d][e][f][g] / (double)tot;
	}
	if(b) { // 打b
		if(dp[att-1][a][b-1][c][d][e][f][g] == 0.0) {
			dfs(att-1, a, b-1, c, d, e, f, g);
		}
		dp[att][a][b][c][d][e][f][g] += dp[att-1][a][b-1][c][d][e][f][g] / (double)tot;
	}
	if(c) { // 打c
		if(dp[att-1][a][b][c-1][d][e][f][g] == 0.0) {
			dfs(att-1, a, b, c-1, d, e, f, g);
		}
		dp[att][a][b][c][d][e][f][g] += dp[att-1][a][b][c-1][d][e][f][g] / (double)tot;
	}
	if(d) { // 打d
		if(dp[att-1][a][b][c][d-1][e][f][g] == 0.0) {
			dfs(att-1, a, b, c, d-1, e, f, g);
		}
		dp[att][a][b][c][d][e][f][g] += dp[att-1][a][b][c][d-1][e][f][g] / (double)tot;
	}
	if(e) { // 打e
		if(dp[att-1][a][b][c][d][e-1][f][g] == 0.0) {
			dfs(att-1, a, b, c, d, e-1, f, g);
		}
		dp[att][a][b][c][d][e][f][g] += dp[att-1][a][b][c][d][e-1][f][g] / (double)tot;
	}
	if(f) { // 打f
		if(dp[att-1][a][b][c][d][e][f-1][g] == 0.0) {
			dfs(att-1, a, b, c, d, e, f-1, g);
		}
		dp[att][a][b][c][d][e][f][g] += dp[att-1][a][b][c][d][e][f-1][g] / (double)tot;
	}
	if(g) { // 打g
		if(dp[att-1][a][b][c][d][e][f][g-1] == 0.0) {
			dfs(att-1, a, b, c, d, e, f, g-1);
		}
		dp[att][a][b][c][d][e][f][g] += dp[att-1][a][b][c][d][e][f][g-1] / (double)tot;
	}
	dfs(att-1, a, b, c, d, e, f, g);
    dp[att][a][b][c][d][e][f][g] += dp[att-1][a][b][c][d][e][f][g] / (double)tot;
}

int main() {
	cin >> cas;
	while(cas--) {
		cin >> n >> m;
		int a[15]; mem(a, 0);
		for(int i = 0; i < m; i++) a[i] = 2;
		mem(dp, 0);
		dfs(3*n, a[0], a[1], a[2], a[3], a[4], a[5], a[6]);
		printf("%.3f\n", dp[3*n][a[0]][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]]);
	}
	return 0;
}