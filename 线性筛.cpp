#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
typedef long long ll;
const int maxn = 1000005;

int mark[maxn];//标记数组
int prime[maxn];
int n;

int sieve() {
	int index = 0;//素数个数
	memset(mark, 0, sizeof(mark));
	for(int i = 2;i <= n;i++) {
		if(mark[i] == 0) //如果未标记则得到一个素数
			prime[index++] = i;
		for(int j = 0;j < index && prime[j]*i <= n;j++) {
			mark[i*prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	return index;
}

int main() {
	while(cin >> n) {
		int num = sieve();
		for(int i = 0;i < num;i++) {
			cout << prime[i] << ' ';
		}
		cout << endl;
	}
	return 0;
}