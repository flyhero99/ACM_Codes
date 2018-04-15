#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define mem(a, b) memset(a, b, sizeof(a))

const int maxn = 5000000+5;

template<class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i++)
        cout << a[i] << " ";
    cout << endl;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}

/*
将a^k分解成n+1个a的幂的和的形式
这n+1个数一定是a个1，a-1个a，a-1个a^2，...，以此类推
就是除1以外，其他a的幂都有a-1个
因此a^k = (a-1)*a + (a-1)*a^2 + ... + (a-1)*a^n + 1
因此a-1要被n整除，因此a的可能取值有n的因子个数种
*/

int t;
ll n, tot;
ll ans;
ll a[maxn], b[maxn];

void factor() {
    ll now = n; tot = 0;
    for(ll i = 2; i*i <= now; i++) {
        if(now % i == 0) {
            a[++tot] = i;
            b[tot] = 0;
            while(now % i == 0) {
                ++b[tot];
                now /= i;
            }
        }
    }
    if(now != 1) {
        a[++tot] = now;
        b[tot] = 1;
    }
}

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n);
        factor();
        ll ans = 1;
        for(int i = 1; i <= tot; i++) {
            ans *= (b[i]+1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}