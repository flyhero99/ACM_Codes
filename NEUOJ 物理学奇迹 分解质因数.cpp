#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 1e6+10;
const double eps = 1e-6;

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

// 1/k = 1/a + 1/b -> 1/k = 1/(k+c) + 1/(k+d) -> c*d = k*k -> 找c的个数

int t;
ll n, tot;
ll a[maxn], b[maxn];

void factor() {
// 分解质因数。tot为质因数总数，a[i]存质因数的值，b[i]存每个因子的个数。
// 约数个数定理：因子总数sum=（每个质因数个数+1）的乘积，小于sqrt(n)的因子总数=ceil(sum/2)。
    ll now = n;
    tot = 0;
    for(int i = 2;i*i <= now;i++) {
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
	while(scanf("%lld", &n) != EOF) {
		n = n*n;
		factor();
		ll sum = 1;
        for(int i = 1;i <= tot;i++) {
            sum *= (b[i]+1);
        }
        cout << (sum+1)/2 << endl;
	}
	return 0;
}