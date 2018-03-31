// #include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 10005;
const int maxm = 100005;

int n, m;
int cost[maxn];
int value[maxn];
int num[maxn]; // 每种物品的数量
int dp[maxm];

void ZeroOnePack(int c, int v) { // 对单个物品01背包
    for(int i = m; i >= c; i--) dp[i] = max(dp[i], dp[i-c]+v);
}

void CompletePack(int c, int v) { // 对单个物品完全背包
    for(int i = c; i <= m; i++) dp[i] = max(dp[i], dp[i-c]+v);
}

int MultiPack() {
    mem(dp, 0);
    for(int i = 1; i <= n; i++) { // 枚举每种物品
        if(num[i]*cost[i] > m) { // 物品全装进去超重，说明物品无限，直接套完全背包
            CompletePack(cost[i], value[i]);
        }
        else {
            int k = 1;
            while(k < num[i]) { // 利用二进制思想，把物品分成1，2，4，8个，依次01背包，能凑出任何数值，降低复杂度
                ZeroOnePack(k*cost[i], k*value[i]);
                num[i] -= k;
                k *= 2;
            }
            ZeroOnePack(num[i]*cost[i], num[i]*value[i]);
        }
    }
    return dp[m];
}

int main() {
    while(cin >> m >> n) {
        for(int i = 1;i <= n;i++) {
            cin >> num[i] >> cost[i];
            value[i] = cost[i];
        }
        cout << MultiPack() << endl;
    }
    return 0;
}
