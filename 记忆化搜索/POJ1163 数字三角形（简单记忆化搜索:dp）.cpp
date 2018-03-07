/**
 * dp[i][j]为第i行第j列到底部的最大数字和
 * 状态转移方程dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + arr[i][j];
 */


// #include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
typedef long long ll;
const int maxn = 505;

int n;
int arr[maxn][maxn];
int d[maxn][maxn];

int dp(int i, int j) {
	if(d[i][j] != 0) return d[i][j];
	if(i == n-1) return arr[i][j];
	return d[i][j] = arr[i][j] + max(dp(i+1, j), dp(i+1, j+1));
}

int main() {
	while(cin >> n) {
		for(int i = 0;i < n;i++) {
			for(int j = 0;j <= i;j++) {
				cin >> arr[i][j];
			}
		}
		memset(d, 0, sizeof(d));
		dp(0, 0);
		cout << d[0][0] << endl;
	}
	return 0;
}