#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 10005; // 最大物品种类数
const int maxm = 100005; // 最大背包容量

int n, m; // n-物品种类数量，m-背包最大容量
int cost[maxn];
int value[maxn];
int dp[maxm];

void CompletePack() {
    for(int i = 0; i < n; i++) { // 
        for(int j = cost[i]; j <= m; j++) { // 把01背包的过程反过来就是完全背包，因为同一物品可以选多次
            dp[j] = max(dp[j], dp[j-cost[i]] + value[i]);
        }
    }
}

int main() {
    while(cin >> m >> n) {
        for(int i = 0; i < n; i++) cin >> cost[i] >> value[i];
        CompletePack();
        cout << dp[m] << endl;
    }
    return 0;
}