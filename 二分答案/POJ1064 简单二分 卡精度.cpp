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

const int maxn = 20000+5;
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

int n, k;
int a[maxn];

int main() {
    // ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    while(scanf("%d %d", &n, &k) != EOF) {
        int maxx = 0;
        double t;
        for(int i = 1; i <= n; i++) {
            scanf("%lf", &t);
            a[i] = (int) 100*t;
            maxx = max(maxx, a[i]);
        }
        int lb = 1, ub = maxx, mid, res=0;
        while(ub-lb >= 0) {
            mid = (lb+ub) / 2;
            int cnt = 0;
            for(int i = 1; i <= n; i++) {
                cnt += (int) (a[i] / mid);
            }
            if(cnt >= k) { // 每次满足的时候记录答案
                res = max(res, mid);
                lb = mid+1;
            }
            else ub = mid-1;
        }
        printf("%.2f\n", (double)res/100.0);
    }
    return 0;
}