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

int arr[maxn][maxn];
pii pre[maxn][maxn];
bool vis[maxn][maxn];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void print() {
    stack<pii> s;
    pii tmp = mp(4, 4);
    while(1) {
        s.push(tmp);
        if(tmp.fi == 0 && tmp.se == 0) break;
        tmp = pre[tmp.fi][tmp.se];
    }

    while(!s.empty()) {
        cout << "(" << s.top().fi << ", " << s.top().se << ")" << endl;
        s.pop();
    }
}

void bfs(int x, int y) {
    queue<pii> q;
    q.push(mp(x, y));
    vis[x][y] = true;
    while(!q.empty()) {
        pii tmp = q.front(); q.pop();
        if(tmp.fi == 4 && tmp.se == 4) {
            print();
            return;
        }
        for(int i = 0; i < 4; i++) {
            int nx = tmp.fi+dx[i], ny = tmp.se+dy[i];
            if(0 <= nx && nx < 5 && 0 <= ny && ny < 5 && !vis[nx][ny] && arr[nx][ny] == 0) {
                q.push(mp(nx, ny));
                pre[nx][ny] = tmp;
                vis[nx][ny] = true;
            }
        }
    }
}

int main() {
    mem(arr, 0); mem(vis, 0); mem(pre, 0);
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            scanf("%d", &arr[i][j]);
        }
    }
    bfs(0, 0);
    return 0;
}