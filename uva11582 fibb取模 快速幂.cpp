#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define ull unsigned long long
const int maxn = 1005;

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

int cas;
ull a, b, c;
ull fib[maxn*maxn];

ull qpow(ull x, ull y, ull z) {
	ull ans = 1;
	while(y) {
		if(y & 1) {
			ans = ans*x%z;
		}
		x = x*x%z;
		y >>= 1;
	}
	return ans;
}

int main() {
	cas = read();
	while(cas--) {
		int len=1;
		cin >> a >> b >> c;
		fib[0] = 0, fib[1] = 1%c;
		for(int i = 2; i <= c*c+1; i++) {
			fib[i] = (fib[i-1]+fib[i-2]) % c;
			if(fib[i] == fib[1] && fib[i-1] == fib[0]) {
				len = i-1;
				break;
			}
		}
		ull ans = qpow( (ull) a % (ull)len, b, (ull) len);
		cout << fib[ans] << endl;
	}
	return 0;
}