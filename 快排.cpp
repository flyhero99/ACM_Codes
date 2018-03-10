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

int a[10];

void quicksort(int st, int ed) {
	if(st < ed) {
		int base = a[st];
		int tmp;
		int i = st, j = ed;
		do {
			while(a[i] < base && i < ed) {
				i++;
			}
			while(a[j] > base && j > st) {
				j--;
			}
			if(i <= j) {
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
				i++;
				j--;
			}
		}while(i <= j);
		if(st < j) quicksort(st, j);
		if(ed > i) quicksort(i, ed);
	}
}

int main() {
	for(int i = 0;i < 10;i++) cin >> a[i];
	cout << "start" << endl;
	quicksort(0, 9);
	cout << "end" << endl;
	for(int i = 0;i < 10;i++) cout << a[i] << ' ';
	cout << endl;
	return 0;
}