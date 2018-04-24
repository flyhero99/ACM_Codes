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

const int maxn = 100000+5;
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

int l, n, m;
int a[maxn];

bool C(int d) {
	int last = 0;
	for(int i = 1; i < n-m; i++) {
		int current = last+1;
		while(current < n && a[current]-a[last] < d) { // 搜寻满足条件的最小位置
			++current;
		}
		if(current == n) return false; // 都不满足条件	
		last = current; // 继续搜寻下一个满足条件的最小位置，放置下一个空位
	}
	return true;
}

int main() {
	while(cin >> l >> n >> m) {
		for(int i = 1; i <= n; i++) cin >> a[i];
		++n; // 0号是起始点，所以加一
		a[n] = l; // 把终点加上
		++n; // N号是结束点，还要加一
		sort(a, a+n);
		int lft = 0, rgt = l+1;
		while(rgt-lft > 1) {
			int mid = (lft+rgt) / 2;
			if(C(mid)) lft = mid;
			else rgt = mid;
		}
		cout << lft << endl;
	}
	return 0;
}