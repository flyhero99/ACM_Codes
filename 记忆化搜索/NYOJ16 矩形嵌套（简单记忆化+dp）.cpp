/*	
	b[i][j]表示第i个矩形可以嵌套在第j个矩形中
  	状态转移方程为：dp[i] = max(dp[j]) + 1;
*/

// #include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;
typedef long long ll;
const int maxn = 105;

int a[maxn][2];
int b[maxn][maxn];
int dp[maxn];

int t, n;

int dfs(int i) {
	if(dp[i] > 0) return dp[i];
	dp[i] = 1;
	for(int j = 0;j < n;j++) {
		if(b[i][j] == 1) dp[i] = max(dp[i], dfs(j)+1);
	}
	return dp[i];
}

void init() {
	for(int i = 0;i < n;i++) {
		for(int j = 0;j < n;j++) {
			if((a[i][0] < a[j][0] && a[i][1] < a[j][1]) || (a[i][0] < a[j][1] && a[i][1] < a[j][0]))
				b[i][j] = 1;
		}
	}
}

int main() {
	cin >> t;
	while(t--) {
		int maxx = 0;
		cin >> n;
		for(int i = 0;i < n;i++) cin >> a[i][0] >> a[i][1];
		memset(b, 0, sizeof(b));
		memset(dp, 0, sizeof(dp));
		init();
		for(int i = 0;i < n;i++) dfs(i);
		for(int i = 0;i < n;i++) {
			if(dp[i] > maxx) maxx = dp[i];
		}
		cout << maxx << endl;
	}
	return 0;
}