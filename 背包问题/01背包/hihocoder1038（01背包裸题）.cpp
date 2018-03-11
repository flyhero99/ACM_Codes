#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 505;
const int maxm = 100005;

int n, m;
int need[maxn];
int value[maxn];
int dp[maxm];

int main() {
    while(cin >> n >> m) {
    	memset(dp, 0, sizeof(dp));
    	for(int i = 0;i < n;i++) cin >> need[i] >> value[i];
    	for(int i = 0;i < n;i++) {
    		for(int j = m;j >= need[i];j--) dp[j] = max(dp[j], dp[j-need[i]]+value[i]);
    	}
    	cout << dp[m] << endl;
    }
	return 0;
}
	
