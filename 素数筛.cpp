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
int prime[maxn];
int n;

void sieve1() {
	prime[0] = prime[1] = 0;
	prime[2] = 1;
	for(int i = 3;i <= n;i++) {
		prime[i] = i%2==0 ? 0 : 1;
	}
	for(int i = 3;i <= n/2+1;i++) {
		if(prime[i]) {
			for(int j = i+i;j <= n;j+=i) {
				prime[j] = 0;
			}
		}
	}
}

int main() {
	while(scanf("%d", &n) != EOF) {
		sieve1();
		for(int i = 2;i <= n;i++)
			if(prime[i]) cout << i << ' ';
		cout << endl;
	}
	return 0;
}