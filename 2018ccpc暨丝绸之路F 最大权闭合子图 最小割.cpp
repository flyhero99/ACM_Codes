#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <cassert>
using namespace std;

#define rep(i,a,b) for(int i = (a); i <= (b); ++i)
#define per(i,a,b) for(int i = (b); i >= (a); --i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef long long ll;
typedef long double ld;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef pair<PII,int> PIII;

const int N = 100005;
const int P = 1000000007;
//const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-8;

ll qmod(ll a,ll b,ll mod) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}

//head

//your code goes here


//最大流板子
//用#define type xxx替代流的类型(int, double, long long)
//记得init()
//极其关键：边数开两倍
#define type ll
const ll INF = LLINF;
const int maxn = 2005;
const int maxm = 50005;
int n;
int s, t;
struct Edge {
    int from, to, next;
    type cap, flow;
    void get (int u, int a, int b, type c, type d) {
        from = u; to = a; next = b; cap = c; flow = d;
    }
}edge[maxm];
int tol;
int head[maxn];
int gap[maxn], dep[maxn], pre[maxn], cur[maxn];

void init () {
    tol = 0;
    memset (head, -1, sizeof head);
}

void add_edge (int u, int v, type w, type rw=0) {
    //cout << u << " " << v << " " << w << endl;
    edge[tol].get(u, v,head[u],w,0);head[u]=tol++;
    edge[tol].get(v, u,head[v],rw,0);head[v]=tol++;
}

type sap (int start, int end, int N) {
    memset (gap, 0, sizeof gap);
    memset (dep, 0, sizeof dep);
    memcpy (cur, head, sizeof head);
    int u = start;
    pre[u] = -1;
    gap[0] = N;
    type ans = 0;
    while (dep[start] < N) {
        if (u == end) {
            type Min = INF;
            for (int i = pre[u]; i != -1; i = pre[edge[i^1].to])
                if (Min > edge[i].cap - edge[i].flow)
                   Min = edge[i].cap-edge[i].flow;
            for (int i = pre[u]; i != -1; i = pre[edge[i^1].to]) {
                edge[i].flow += Min;
                edge[i^1].flow -= Min;
            }
            u = start;
            ans += Min;
            continue;
        }
        bool flag = false;
        int v;
        for (int i = cur[u]; i != -1; i = edge[i].next) {
            v = edge[i].to;
            if (edge[i].cap - edge[i].flow && dep[v]+1 == dep[u]) {
                flag = true;
                cur[u] = pre[v] = i;
                break;
            }
        }
        if (flag) {
            u = v;
            continue;
        }
        int Min = N;
        for (int i = head[u]; i != -1; i = edge[i].next)
            if (edge[i].cap - edge[i].flow && dep[edge[i].to] < Min) {
                  Min = dep[edge[i].to];
                  cur[u] = i;
             }
        gap[dep[u]]--;
        if (!gap[dep[u]]) return ans;
        dep[u] = Min+1;
        gap[dep[u]]++;
        if (u != start) u = edge[pre[u]^1].to;
    }
    return ans;
}

ll e1[205], e2[205];

int main() {
    int T; scanf("%d",&T);
    while(T--) {
        init();
        int n, m; scanf("%d %d", &n, &m);
        int s = 0, t = n+m+1;
        ll sum = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%lld",&e1[i]);
            ll x = e1[i];
            sum += e1[i];
            add_edge(s, i, x);
        }
        for(int i = 1; i <= m; ++i) {
            scanf("%lld", &e2[i]);
            ll x = e2[i];
            add_edge(n+i, t, x);
        }
        for(int i = 1; i <= n; ++i) {
            int a, b; scanf("%d %d", &a, &b);
            while(a--) {
                ll x; scanf("%lld", &x);
                add_edge(i, n+x, INF);
            }
            while(b--) {
                ll x; scanf("%lld",&x);
                add_edge(i, x, INF);
            }
        }
        cout << sum-sap(s, t, n+m+2) << endl;
    }
    return 0;
}
