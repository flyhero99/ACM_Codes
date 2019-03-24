#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define mod 1000000007
#define mem(a,b) memset(a,b,sizeof(a))

using namespace std;

const int maxn = 10010;

struct edge {
    int v, c;

    edge(int v, int c) {
        this->v = v;
        this->c = c;
    }
};

vector<edge> ver[maxn];
bool vis[maxn];
int dist[maxn], cnt[maxn];
int n, m;

void addEdge(int u, int v, int w) {
    ver[u].push_back(edge(v, w));
}

bool spfa(int st) {
    mem(dist, inf); dist[st] = 0; vis[st] = true; cnt[st] = 1;
    queue<int> q; q.push(st);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(int i = 0;i < ver[u].size();i++) {
            int v = ver[u][i].v; int c = ver[u][i].c;
            if(dist[v] > dist[u]+c) {
                dist[v] = dist[u] + c;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                    if(++cnt[v] > n) return false; // 存在负环回路
                }
            }
        }
    }
    return true;
}

int main() {
    while(scanf("%d %d", &n, &m) != EOF) {
        if(n==0 && m==0) return 0;
        for(int i = 1;i <= n;i++) ver[i].clear();
        int u, v, w;
        for(int i = 0;i < m;i++) {
            scanf("%d %d %d", &u, &v, &w);
            addEdge(u, v, w);
            addEdge(v, u, w);
        }
        spfa(1);
        printf("%d\n", dist[n]);
    }
    return 0;
}