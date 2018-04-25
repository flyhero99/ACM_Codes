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
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define ull unsigned long long
#define inf 0x3f3f3f3f

const int maxn = 200000+5;
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

int sum[maxn << 2];
int a[maxn];
int n, m;

void pushup(int root) {sum[root] = max(sum[root<<1], sum[root<<1|1]);}

void build(int l, int r, int rt) {
    if(l == r) {sum[rt] = a[l]; return;}
    int m = (l+r) >> 1;
    build(l, m, rt<<1);
    build(m+1, r, rt<<1|1);
    pushup(rt);
}

void update(int L, int C, int l, int r, int root) {
    if(l == r) {
        sum[root] = C;
        return;
    }
    int m = (l+r) >> 1;
    if(L <= m) update(L, C, l, m, root<<1);
    else update(L, C, m+1, r, root<<1|1);
    pushup(root);
}

int query(int L, int R, int l, int r, int root) {
    if(L <= l && r <= R) return sum[root];
    int m = (l+r) >> 1;
    int ans = 0;
    if(L <= m) ans = max(ans, query(L, R, l, m, root<<1));
    if(R > m) ans = max(ans, query(L, R, m+1, r, root<<1|1));
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while(cin >> n >> m) {
        for(int i = 1; i <= n; i++) cin >> a[i];
        build(1, n, 1);
        // for(int i = 0; i <= 30; i++) cout << sum[i] << ' ';
        // cout << endl;
        while(m--) {
            char c[2];
            int x, y;
            cin >> c >> x >> y;
            if(c[0] == 'Q') {
                // cout << "cnm" << endl;
                // x = read(); y = read();
                // cout << x <<' ' << y << endl;
                cout << query(x, y, 1, n, 1) << endl;;
            }
            else if(c[0] == 'U') {
                // x = read(); y = read();
                update(x, y, 1, n, 1);
            }
        }
    }
    return 0;
}