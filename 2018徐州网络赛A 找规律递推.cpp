#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5;
const int mod = 1e9+7;

int n, k;
ll two[maxn], ans[maxn];

ll qpow(ll a, int b) {
    ll ans = 1;
    while(b) {
        if(b & 1) {
            ans = ans*a % mod;
        }
        b >>= 1;
        a = a*a % mod;
    }
    return ans;
}

void init() {
    two[0] = 1;
    for(int i = 1; i < maxn; i++) {
        two[i] = two[i-1]*2 % mod;
    }
}

ll solve(int n, int k) {
    ll ans;
    if(n == 1) { // n=1, 答案为2^k
        return two[k];
    }
    if(n == 2) { // n=2, 答案为2^k-1
        return two[k]*(two[k]-1) % mod;
    }
    return (two[k]*qpow(two[k]-1, n-2)%mod * max(two[k]-2, 0ll) % mod + solve(n-2, k)) % mod;
}

int main() {
    init();
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &k);
        printf("%lld\n", solve(n, k));
    }
    return 0;
}