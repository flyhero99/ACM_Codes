#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define mod 1000000007
#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;


const int maxn = 100005;

int t;
ll n, tot;
ll a[maxn], b[maxn];

void factor() {
    ll tmp = (ll) ((double)sqrt(n) + 1), now = n;
    tot = 0;
    for(i = 2;i*i <= now;i++) {
        if(now % i == 0) {
            a[++tot] = i;
            b[tot] = 0;
            while(now % i == 0) {
                ++b[tot];
                now /= i;
            }
        }
    }
    if(now != 1) { // n是素数
        a[++tot] = now;
        b[tot] = 1;
    }
}

int main() {
    cin >> t;
    while(t--) {
        cin >> n;
        n = n*n;
        factor();
        ll sum = 1;
        for(int i = 1;i <= tot;i++) {
            sum *= (b[i]+1);
        }
        sum /= 2;
        sum += 1;
        cout << sum << endl;
    }
    return 0;
}