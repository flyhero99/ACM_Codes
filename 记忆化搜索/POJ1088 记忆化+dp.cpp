/*	
	dp[i][j]表示从第i行j列滑到底的最长长度
  	状态转移方程为：dp[i][j] = max(dp[i+1][j], dp[i][j+1], dp[i-1][j], dp[i][j-1]) + 1;
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

int r, c;
int arr[maxn][maxn];
int dp[maxn][maxn];
int dict[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};


int dfs(int x, int y) {
	if(dp[x][y] != 0) return dp[x][y];
	dp[x][y] = 1;
	for(int i = 0;i < 4;i++) {
		int dx = x + dict[i][0];
		int dy = y + dict[i][1];
		if(dx >= 1 && dx <= r && dy >= 1 && dy <= c) {
			if(arr[dx][dy] < arr[x][y]) dp[x][y] = max(dp[x][y], dfs(dx, dy) + 1);
		}
	}
	return dp[x][y];
}

int main() {
	while(cin >> r >> c) {
		for(int i = 1;i <= r;i++) {
			for(int j = 1;j <= c;j++) {
				cin >> arr[i][j];
			}
		}
		memset(dp, 0, sizeof(dp));
		int maxx = 0;
		for(int i = 1;i <= r;i++) {
			for(int j = 1;j <= c;j++) {
				int cur = dfs(i, j);
				if(cur > maxx) maxx = cur;
			}
		}
		cout << maxx << endl;
	}
	return 0;
}