#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxt = 100005;
const int maxm = 10005;

int t, m;
int c[maxm];
int v[maxm];
int dp[maxt];

int main() {
	while(cin >> t >> m) {
		for(int i = 0;i < m;i++) cin >> c[i] >> v[i];
		for(int i = 0;i < m;i++) {
			for(int j = c[i];j <= t;j++) dp[j] = max(dp[j], dp[j-c[i]]+v[i]);
		}
		cout << dp[t] << endl;
	}
	return 0;
}