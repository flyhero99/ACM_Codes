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

const int maxn = 105;
const int maxm = 105;

int dx[6] = {1, 0, 0, -1, 0, 0};
int dy[6] = {0, 1, 0, 0, -1, 0};
int dz[6] = {0, 0, 1, 0, 0, -1};
char arr[maxn][maxn][maxn];
bool vis[maxn][maxn][maxn];
struct node {
    int x, y, z, step;
};
int sx, sy, sz;
int ex, ey, ez;
int k, n, m;

int check(int x, int y, int z) {
    if(x<0 || y<0 || z<0 || x>=k || y>= n || z>=m || arr[x][y][z] == '#' || vis[x][y][z])
        return 0;
    return 1;
}

int bfs(int x, int y, int z) {
    queue<node> q;
    node a; a.x = x; a.y = y; a.z = z; a.step = 0;
    vis[sx][sy][sz] = 1;
    q.push(a);
    while(!q.empty()) {
        a = q.front(); q.pop();
        if(a.x == ex && a.y == ey && a.z == ez) return a.step;
        for(int i = 0; i < 6; i++) {
            node tmp = a;
            tmp.x = a.x+dx[i]; tmp.y = a.y+dy[i]; tmp.z = a.z+dz[i];
            if(check(tmp.x, tmp.y, tmp.z)) {
                vis[tmp.x][tmp.y][tmp.z] = 1;
                tmp.step = a.step+1;
                q.push(tmp);
            }
        }
    }
    return 0;
}

int main() {
    while(scanf("%d %d %d", &k, &n, &m) != EOF) {
        if(n==0 && m==0 && k==0) return 0;
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < n; j++) {
                scanf("%s", arr[i][j]);
                for(int r = 0; r < m; r++) {
                    if(arr[i][j][r] == 'S') {
                        sx = i; sy = j; sz = r;
                    }
                    else if(arr[i][j][r] == 'E') {
                        ex = i; ey = j; ez = r;
                    }
                }
            }
        }
        mem(vis, 0);
        int ans = bfs(sx, sy, sz);
        if(ans) printf("Escaped in %d minute(s).\n", ans);
        else printf("Trapped!\n");
    }
}