#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 400+5;

int a[maxn][maxn];
bool vis[maxn][maxn];
int n, m, st, ed;
int dx[8] = {-2, -1, 1, 2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void bfs() {
    queue<pii> q;
    mem(vis, 0);
    pii u = mp(st, ed);
    a[st][ed] = 0;
    q.push(u);
    vis[st][ed] = true;
    while(!q.empty()) {
        pii tmp = q.front(); q.pop();
        for(int i = 0; i < 8; i++) {
            int nx = tmp.fi+dx[i], ny = tmp.se+dy[i];
            if(0 <= nx && nx < n && 0 <= ny && ny < m && !vis[nx][ny]) {
                a[nx][ny] = a[tmp.fi][tmp.se]+1;
                q.push(mp(nx, ny));
                vis[nx][ny] = true;
            }
        }
    }
    return;
}

int main() {
    while(scanf("%d %d %d %d", &n, &m, &st, &ed) == 4) {
        mem(a, -1);
        st--; ed--;
        bfs();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                printf("%-5d", a[i][j]);
            }
            cout << endl;
        }
    }
    return 0;
}