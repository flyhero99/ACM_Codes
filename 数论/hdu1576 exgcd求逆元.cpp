#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5;
const int mod = 1e9+7;

int gcd(int a, int b) {
    while(b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) { x = 1; y = 0; return a; }
    ll ans = exgcd(b, a%b, x, y);
    ll tmp = x;
    x = y;
    y = tmp - (a/b)*y;
    return ans;
}


int main() {
    int t; scanf("%d", &t);
    for(int kas = 0; kas < t; kas++) {
        ll a, n;
        scanf("%lld %lld", &n, &a);
        ll x, y;
        exgcd(a, 9973, x, y);
        x = (x%9973 + 9973) % 9973;
        cout << x * n % 9973 << endl;
    }
    return 0;
}