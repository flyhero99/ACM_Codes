#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 105;

int cas;
int n, m, cnt;
char mmp[maxn][maxn];
// bool vis[maxn][maxn];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
pii s;

void bfs(int x, int y) {
	queue<pii> q;
	q.push(mp(s.fi, s.se));
	mmp[s.fi][s.se] = '#';
	while(!q.empty()) {
		pii tmp = q.front(); q.pop();
		for(int i = 0; i < 4; i++) {
			int nx = tmp.fi+dx[i], ny = tmp.se+dy[i];
			if(0 <= nx && nx < n && 0 <= ny && ny < m && mmp[nx][ny] != '#') {
				cnt++;
				q.push(mp(nx, ny));
				mmp[nx][ny] = '#';
				// cout << "nx, ny: " << nx << ' ' << ny << endl;
			}
		}
	}
	return;
}

int main() {
	cin >> cas;
	while(cas--) {
		cnt = 0;
		cin >> n >> m;
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				cin >> mmp[i][j];
				if(mmp[i][j] == 'S') s = mp(i, j);
			}
		}
		bfs(s.fi, s.se);
		cout << cnt << endl;
	}
	return 0;
}