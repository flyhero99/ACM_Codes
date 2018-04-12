/*
求k种物品的最大平均性价比
最大化平均值 二分
*/
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

int w[maxn], v[maxn];
int cas, n, k;
double y[maxn];

bool cmp(const double &a, const double &b) {
	return a > b;
}

bool check(double ans) { // sum(v[i])/sum(w[i]) >= x 然后找最大的x
	for(int i = 0; i < n; i++) {
		y[i] = (double) v[i] - ans*w[i];
	}
	sort(y, y+n, cmp);
	double sum = 0;
	for(int i = 0; i < k; i++) {
		sum += y[i];
	}
	return sum >= 0;
}

int main() {
	cas = read();
	while(cas--) {
		n = read(); k = read();
		for(int i = 0; i < n; i++) {
			w[i] = read(); v[i] = read();
		}
		double l = 0.0, r = 1.0*1e6;
		while(r-l > eps) { // 二分答案
			double mid = (l+r) / 2;
			if(check(mid)) { // 答案比现在大
				l = mid;
			}
			else r = mid; // 答案比现在小
		}
		printf("%.2f\n", r);
	}
}