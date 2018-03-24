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

vector<edge> ver[22*22];
int n, m;
bool vis[22*22];
int dist[22*22];

void spfa(int st) {
    mem(dist, inf); dist[st] = 0; vis[st] = true;
    queue<int> q; q.push(st);

    while(!q.empty()) {
        int u = q.front(); q.pop(); vis[u] = false;
        for(int i = 0;i < ver[u].size();i++) {
            int v = ver[u][i].v; int c = ver[u][i].c;
            if(dist[v] > dist[u]+2520/c) {
                dist[v] = dist[u]+2520/c;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }

        }
    }
}

void read() {
    int x;
    char ch[2];
    for(int i = 1;i <= (n+1)*(m+1);i++) ver[i].clear();
    for(int i = 1;i <= m;i++) { //先处理第一行
        scanf("%d", &x);
        scanf("%s", &ch);
        if(x == 0) continue;
        if(ch[0] == '*') {
            ver[i].push_back(edge(i+1, x));
            ver[i+1].push_back(edge(i, x));
        }
        if(ch[0] == '>') ver[i].push_back(edge(i+1, x));
        if(ch[0] == '<') ver[i+1].push_back(edge(i, x));
    }
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= (m+1);j++) {
            scanf("%d", &x);
            scanf("%s", &ch);
            if(x == 0) continue;
            int p = (i-1)*(m+1) + j;
            int q = i*(m+1) + j;
            if(ch[0] == '*') {
                ver[p].push_back(edge(q, x));
                ver[q].push_back(edge(p, x));
            }
            if(ch[0] == '^') ver[q].push_back(edge(p, x));
            if(ch[0] == 'v') ver[p].push_back(edge(q, x));
        }
        for(int j = 1;j <= m;j++) {
            scanf("%d", &x);
            scanf("%s", &ch);
            if(x == 0) continue;
            int p = i*(m+1) + j;
            int q = i*(m+1) + j + 1;
            if(ch[0] == '*') {
                ver[p].push_back(edge(q, x));
                ver[q].push_back(edge(p, x));
            }
            if(ch[0] == '<') ver[q].push_back(edge(p, x));
            if(ch[0] == '>') ver[p].push_back(edge(q, x));
        }
    }
    return;
}

int main() {
    while(scanf("%d %d", &n, &m) == 2) {
        if(n==0 && m==0) break;
        read();
        spfa(1);
        if(dist[(n+1)*(m+1)] == inf) printf("Holiday\n");
        else printf("%d blips\n", dist[(n+1)*(m+1)]);
    }
}