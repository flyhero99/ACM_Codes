#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstring>
#include<utility>

using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 205;

int n, m;
pii st, ed;
int dist[maxn][maxn];
int save[maxn][maxn];
char mmp[maxn][maxn];
bool vis[maxn][maxn];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void bfs(int x, int y) {
    mem(dist, 0); mem(vis, 0);
    pii u = mp(x, y);
    queue<pii> q; q.push(u);
    vis[x][y] = true; dist[x][y] = 0;
    while(!q.empty()) {
        pii tmp = q.front(); q.pop();
        for(int i = 0;i < 4;i++) {
            int nx = tmp.fi+dx[i], ny = tmp.se+dy[i];
            if(0 <= nx && nx < n && 0 <= ny && ny < m && !vis[nx][ny] && mmp[nx][ny] != '#') {
                dist[nx][ny] = dist[tmp.fi][tmp.se]+1;
                q.push(mp(nx, ny));
                vis[nx][ny] = true;
            }
        }
    }
}

int main() {
    while(cin >> n >> m) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> mmp[i][j];
                if(mmp[i][j] == 'Y') {
                    st.fi = i; st.se = j;
                }
                if(mmp[i][j] == 'M') {
                    ed.fi = i; ed.se = j;
                }
            }
        }
        mmp[ed.fi][ed.se] = '#';
        bfs(st.fi, st.se);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                save[i][j] = dist[i][j];
                dist[i][j] = 0;
            }
        }
        mmp[ed.fi][ed.se] = '.';
        mmp[st.fi][st.se] = '#';
        bfs(ed.fi, ed.se);
        int minn = inf;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(mmp[i][j] == '@') {
                    // cout << "min: " << minn << endl;
                    // cout << "i: " << i << " j: " << j << endl;
                    // cout << "Y: " << save[i][j] << " M: " << dist[i][j] << endl;
                    if(save[i][j] == 0 || dist[i][j] == 0) continue;
                    minn = min(minn, save[i][j]+dist[i][j]);
                }
            }
        }
        cout << minn*11 << endl;
    }
    return 0;
}