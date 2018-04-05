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
const double eps = 1e-5;
int w[maxn], v[maxn];
int n, k;
double y[maxn];

bool check(double r) {
	for(int i = 0; i < n; i++) {
		y[i] = v[i]-r*w[i];
	}
	sort(y, y+n);
	reverse(y, y+n);
	double sum=0;
	for(int i = 0; i < k; i++) {
		sum += y[i];
	}
	return sum >= 0;
}

int main() {
	int cas; cin >> cas;
	while(cas--) {
		cin >> n >> k;
		for(int i = 0; i < n; i++)
			cin >> w[i] >> v[i];
		double lb=0, ub=1e6;
		while(ub - lb > eps) {
			double mid = (lb+ub) / 2;
			if(check(mid)) lb = mid;
			else ub = mid;
		}
		printf("%.2f\n", ub);
	}
	return 0;
}