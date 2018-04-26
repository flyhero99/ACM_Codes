#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define ull unsigned long long
#define inf 0x3f3f3f3f

const int maxn = 100000+5;
const double eps = 1e-6;
const double pi = 3.141592653589793238462643385;

template <class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}

int t, n, q;
ll sum[maxn<<2], add[maxn<<2];

void pushup(int rt) {sum[rt] = sum[rt<<1] + sum[rt<<1|1];}

// a[l,r]+=c则是+=，a[l,r]=c则是=。
void pushdown(int rt, int len) {
    if(add[rt]) {
        add[rt<<1] += add[rt]; // +=
        add[rt<<1|1] += add[rt]; // +=
        sum[rt<<1] += add[rt]*(len - (len>>1)); // +=
        sum[rt<<1|1] += add[rt]*(len>>1); // +=
        add[rt] = 0;
    }
}

void build(int l, int r, int rt) {
    add[rt] = 0;
    if(l == r) {
        scanf("%lld", &sum[rt]);
        // sum[rt] = 1;
        return;
    }
    int m = (l+r) >> 1;
    build(l, m, rt<<1);
    build(m+1, r, rt<<1|1);
    pushup(rt);
}

//a[L,R]区间每个数变为c，[l,r]为树上区间，rt为根结点
void update(int L, int R, int c, int l, int r, int rt) {
    if(L <= l && r <= R) {
        add[rt] += c; // +=
        sum[rt] += (ll)c*(r-l+1); // +=
        return;
    }
    pushdown(rt, r-l+1);
    int m = (l+r)>>1;
    if(L <= m) update(L, R, c, l, m, rt<<1);
    if(R > m) update(L, R, c, m+1, r, rt<<1|1);
    pushup(rt);
}

ll query(int L, int R, int l, int r, int rt) {
    if(L <= l && r <= R) return sum[rt];
    pushdown(rt, r-l+1);
    int m = (l+r)>>1;
    ll ans = 0;
    if(L <= m) ans += query(L, R, l, m, rt<<1);
    if(R > m) ans += query(L, R, m+1, r, rt<<1|1);
    return ans;
}

int main() {
    int t; scanf("%d", &t);
    for(int cas = 1; cas <= t; cas++) {
        scanf("%d", &n);
        build(1, n, 1);
        char ss[10];
        int x, y;
        printf("Case %d:\n", cas);
        while(1) {
            scanf("%s", ss);
            if(ss[0] == 'E') break;
            else if(ss[0] == 'Q') {
                scanf("%d %d", &x, &y);
                printf("%lld\n", query(x, y, 1, n, 1));
            }
            else if(ss[0] == 'A') {
                scanf("%d %d", &x, &y);
                update(x, x, y, 1, n, 1);
            }
            else if(ss[0] == 'S') {
                scanf("%d %d", &x, &y);
                update(x, x, -y, 1, n, 1);
            }
        }
    }
    return 0;
}