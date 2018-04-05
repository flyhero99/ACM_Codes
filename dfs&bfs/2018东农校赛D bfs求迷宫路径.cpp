#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 505;
const int maxm = 505;

int cas;
int n, m;
pii s, t;
char mmp[maxn][maxn];
// bool vis[maxn][maxn];
bool flag;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void bfs(int x, int y) {
	queue<pii> q;
	q.push(mp(x, y));
	// vis[x][y] = true;

	while(!q.empty()) {
		pii tmp = q.front(); q.pop();
		// cout << "tmp: " << tmp.fi << ' ' << tmp.se << endl;
		if(tmp.fi == t.fi && tmp.se == t.se) {
			flag = 1;
			return;
		}
		for(int i = 0; i < 4; i++) {
			int nx = tmp.fi+dx[i], ny = tmp.se+dy[i];
			if(0 <= nx && nx < n && 0 <= ny && ny < m && mmp[nx][ny] != 'x') {
				mmp[nx][ny] = 'x';
				q.push(mp(nx, ny));
				// vis[nx][ny] = true;
			}
		}
	}
}

int main() {
	cin >> cas;
	while(cas--) {
		cin >> n >> m;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				cin >> mmp[i][j];
				if(mmp[i][j] == 's') {
					s.fi = i; s.se = j;
				}
				else if(mmp[i][j] == 't') {
					t.fi = i; t.se = j;
				}
			}
		}
		flag = 0;
		bfs(s.fi, s.se);
		printf("%s\n", flag ? "YES" : "NO");
	}
	return 0;
}

/*
1
3 5
s...x
x...x
...tx
*/