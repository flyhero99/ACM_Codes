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

const int maxn = 10000+5;
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

int cas, n, f;
double cake[maxn];

int main() {
	cas = read();
	while(cas--) {
		n = read(); f = read(); f++;
		double max_cake = (double) 0.0;
		for(int i = 1; i <= n; i++) {
			scanf("%lf", &cake[i]);
			cake[i] *= cake[i];
			if(max_cake < cake[i]) max_cake = cake[i];
		}
		double low = 0.0, high = max_cake, mid;
		while(high-low > eps) {
			mid = (low+high) / 2;
			int cnt = 0;
			for(int i = 1; i <= n; i++) {
				cnt += (int) cake[i] / mid;
			}
			if(cnt < f) high = mid;
			else low = mid;
		}
		printf("%.4f\n", mid*pi);
	}
	return 0;
}