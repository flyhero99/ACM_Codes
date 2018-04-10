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

char mmp[maxn][maxn];
int cas, n, m;
pii s, t;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool bfs(int x, int y) {
    queue<pii> q;
    q.push(mp(x, y));
    while(!q.empty()) {
        pii tmp = q.front(); q.pop();
        if(tmp.fi == t.fi && tmp.se == t.se) return true;
        for(int i = 0; i < 4; i++) {
            int nx = tmp.fi+dx[i], ny = tmp.se+dy[i];
            if(0 <= nx && nx < n && 0 <= ny && ny < m && mmp[nx][ny] != 'x') {
                mmp[nx][ny] = 'x';
                q.push(mp(nx, ny));
            }
        }
    }
    return false;
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
        if(bfs(s.fi, s.se)) {cout << "YES" << endl;}
        else cout << "NO" << endl;
    }
    return 0;
}