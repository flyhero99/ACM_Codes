#include<iostream>
#include<cstdio>

using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 105;
const int maxm = 105;

int n, m;
char mp[maxn][maxn];

void dfs(int x, int y) {
    mp[x][y] = '*';
    for(int dx = -1; dx <= 1; dx++) {
        for(int dy = -1; dy <= 1; dy++) {
            int nx = x+dx, ny = y+dy;
            if(0 <= nx && nx < n && 0 <= ny && ny < m && mp[nx][ny] == '@') dfs(nx, ny);
        }
    }
    return;
}

void solve() {
    int res = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mp[i][j] == '@') {
                dfs(i, j);
                res++;
            }
        }
    }
    cout << res << endl;
}

int main() {
    while(cin >> n >> m) {
        if(n == 0 && m == 0) return 0;
        for(int i = 0; i < n; i++) {
            scanf("%s", mp[i]);
        }
        solve();
    }
    return 0;
}