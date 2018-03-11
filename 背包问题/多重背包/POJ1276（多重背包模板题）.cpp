#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 100005;
const int maxm = 10005;

int cash, n;
int dp[maxn];
int c[maxn], w[maxn], num[maxn];

void ZeroOne_Pack(int cost, int weight) {
	for(int i = cash;i >= cost;i--) dp[i] = max(dp[i], dp[i-cost]+weight);
}

void Complete_Pack(int cost, int weight) {
	for(int i = cost;i <= cash;i++) dp[i] = max(dp[i], dp[i-cost]+weight);
}

int Multi_Pack() {
	memset(dp, 0, sizeof(dp));
	for(int i = 1;i <= n;i++) {
		if(num[i]*c[i] > cash) { //物品全装进去超重，说明物品无限，直接套完全背包
			Complete_Pack(c[i], w[i]);
		}
		else {
			int k = 1;
			while(k < num[i]) { //利用二进制思想，把物品分成1，2，4，8个，依次01背包，能凑出任何数值，降复杂度
				ZeroOne_Pack(k*c[i], k*w[i]);
				num[i] -= k;
				k <<= 1;
			}
			ZeroOne_Pack(num[i]*c[i], num[i]*w[i]);
		}
	}
	return dp[cash];
}

int main() {
	while(cin >> cash >> n) {
		for(int i = 1;i <= n;i++) {
			cin >> num[i] >> c[i];
			w[i] = c[i];
		}
		cout << Multi_Pack() << endl;
	}
	
	return 0;
}
