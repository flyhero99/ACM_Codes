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
    mp[x][y] = '.';
    for(int nx = -1;nx <= 1;nx++) {
        for(int ny = -1;ny <= 1;ny++) {
            int dx = x+nx;
            int dy = y+ny;
            if(0 <= dx && dx < n && 0 <= dy && dy < m && mp[dx][dy] == 'W') dfs(dx, dy); 
        }
    }
    return;
}

void solve() {
    int res = 0;
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < m;j++) {
            if(mp[i][j] == 'W') {
                dfs(i, j);
                res++;
            }
        }
    }
    printf("%d\n", res);
}

int main() {
    while(cin >> n >> m) {
        for(int i = 0;i < n;i++) {
            for(int j = 0;j < m;j++) {
                cin >> mp[i][j];
            }
            getchar();
        }
        solve();
    }
    return 0;
}