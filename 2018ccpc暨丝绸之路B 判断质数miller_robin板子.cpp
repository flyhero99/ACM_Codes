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

const int N = 10;
const int P = 1000000007;
const int INF = 0x3f3f3f3f;
const ll LLINF = 0x3f3f3f3f3f3f3f3f;
const ld eps = 1e-8;

ll qmod(ll a,ll b,ll mod) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}


#define LL unsigned long long
const int S = 10;
//head

//your code goes here

//O(n)
const int maxn = 1e5+5;

bool vis[maxn];
int prime[maxn/10], tot = 0;

void init() {
    memset(vis, 0, sizeof(vis));
    tot = 0;
    for(int i = 2; i < maxn; ++i) {
        if(!vis[i]) prime[tot++] = i;
        for(int j = 0;j < tot; ++j) {
            if(i * prime[j] > maxn) break;
            vis[i*prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}

LL random(LL n) {
    return (LL) ((double)rand()/RAND_MAX*n+0.5);
}

LL multi(LL a, LL b, LL m) {//计算a*b%m
    LL ret = 0;
    while(b) {
        if(b & 1) ret = (ret+a) % m;
        b >>= 1;
        a = (a << 1) % m;
    }
    return ret;
}

LL quick_mod(LL a, LL b, LL m) {//计算a^b%m
    LL ans = 1;
    while(b) {
        if(b & 1) {
            ans = multi(ans, a, m);
            b--;
        }
        b >>= 1;
        a = multi(a, a, m);
    }
    return ans;
}

bool miller_rabbin(LL n) {
    if(n == 2) return true;
    if(n < 2 || !(n&1)) return false;
    LL m = n-1;
    int k = 0;
    while((m & 1) == 0) {
        k++;
        m >>= 1;
    }
    for(int i = 0; i < N; i++) {
        LL a = rand()%(n - 1) + 1;
        LL x = quick_mod(a, m, n);
        LL y = 0;
        for(int j = 0; j < k; j++) {
            y = multi(x, x, n);
            if(y == 1 && x != 1 && x != n-1) return false;
            x = y;
        }
        if(y != 1) return false;
    }
    return true;
}

//O(n)
int main() {
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // cout << miller_rabbin(9223372036854775783ll) << endl;
    init();
    int T; scanf("%d", &T);
    prime[0] = 2;
    while(T--) {
        ll n; scanf("%llu", &n);
        for(int i = 0; i < tot; ++i) {
            ll qwq = n - prime[i];
            // cout << qwq << ' ' << prime[i] << endl;
            if(miller_rabbin(qwq)) {
                printf("%d %llu\n", prime[i], qwq);
                break;
            }
        }
    }
    return 0;
}