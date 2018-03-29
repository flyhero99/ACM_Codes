#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 105;

int n, k;
ll sum;
int vis[maxn], a[maxn];

void dfs(int i, int cnt, int sm) {
    if(cnt == k) {sum += sm; return;}
    if(i >= n) return;
    if(!vis[i]) {
        vis[i] = 1;
        dfs(i+1, cnt+1, sm*a[i]); //选a[i]
        dfs(i+1, cnt, sm); //不选a[i]
        vis[i] = 0; //回溯时取消标记
    }
    return;
}

int main() {
    while(scanf("%d %d", &n, &k) == 2) {
        mem(vis, 0);
        sum = 0;
        for(int i = 0;i < n;i++) scanf("%d", &a[i]);
        dfs(0, 0, 1);
        printf("%lld\n", sum);
    }
    return 0;
}