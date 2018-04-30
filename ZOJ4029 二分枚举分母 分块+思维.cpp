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

const int maxn = 500000+5;
const double eps = 1e-6;
const double pi = 3.141592653589793238462643385;
const int mod = 1e9;

template <class T>
void show(T a[], int len) {
    for(int i = 1; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}

int t;
int n, m, p;
int a[maxn];
ll sum[32][maxn];

ll qpow(ll a, int b) { // 这里不用取模，因为pow求的是p^i = ai，ai不会超过2e9
    ll ans = 1;
    while(b) {
        if(b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
        if(ans > 20001001000) return -1;
    }
    return ans;
}

int main() {
    t = read();
    while(t--) {
        n = read(); m = read();
        for(int i = 1; i <= n; i++) {
            a[i] = read();
        }
        sort(a+1, a+n+1);
        for(int i = 1; i <= 31; i++) { // 排序后预处理出分母logp(ai)每个值的前缀和
            sum[i][0] = 0;
            for(int j = 1; j <= n; j++) {
                sum[i][j] = (sum[i][j-1] + a[j]/i) % mod;
            }
        }
        ll ans = 0;
        for(int i = 1; i <= m; i++) {
            scanf("%d", &p);
            ll res = 0;
            for(int j = 1; j <= 31; j++) { // 枚举logp(ai)找到logp(ai)等于i的一段a
                ll down = qpow(p, j-1);
                ll up = qpow(p, j); // a[i]的上界和下界
                // cout << down << ' ' << up << endl;
                if(down == -1) break;
                int l = 1, r = n+1, mid;
                if(down != -1) {
                    while(l < r) {
                        mid = (l+r) >> 1;
                        if(a[mid] > down) r = mid;
                        else l = mid+1;
                    }
                }
                int L = r;
                l = 1, r = n+1;
                if(up != -1) {
                    while(l < r) {
                        mid = (l+r) >> 1;
                        if(a[mid] > up) r = mid;
                        else l = mid+1;
                    }
                }
                int R = r-1;
                if(L > n) break;
                if(L > R) continue;
                res = (res + sum[j][R] - sum[j][L-1]) % mod;
                res = (res+mod) % mod;
            }
            ans = (ans + i*res%mod) % mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}