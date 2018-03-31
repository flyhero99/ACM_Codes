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
int cost[maxn];
int value[maxn];
int dp[maxm];

void ZeroOnePack() {
    for(int i = 0; i < n; i++) { // 枚举每种物品
        for(int j = m; j >= cost[i]; j--) { // 枚举容量至装不下当前物品
            dp[j] = max(dp[j], dp[j-cost[i]] + value[i]);
        }
    }
}

int main() {
    while(cin >> n >> m) {
    	mem(dp, 0);
        for(int i = 0; i < n; i++) cin >> cost[i] >> value[i];
        ZeroOnePack();
    	cout << dp[m] << endl;
    }
	return 0;
}
	
