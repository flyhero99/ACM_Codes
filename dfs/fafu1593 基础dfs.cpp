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

bool flag;
int n, k, sum;
int a[maxn], vis[maxn];

bool dfs(int i, int sum) {
    if(i < n && !vis[i]) {
        vis[i] = 1;
        if(sum+a[i] == k) return flag=true;
        else if(sum+a[i] < k) {
            dfs(i+1, sum);//sum加a[i]后继续往下找
            dfs(i+1, sum+a[i]);//sum不加a[i]后继续往下找
        }
        else dfs(i+1, sum);
        vis[i] = 0;
    }
    return flag;
}

int main() {
    while(~scanf("%d", &n)) {
        for(int i = 0;i < n;i++) scanf("%d", &a[i]);
        scanf("%d", &k);
        flag = 0;
        mem(vis, 0);
        dfs(0, 0);
        if(flag) cout << "Of course,I can!" << endl;
        else cout << "Sorry,I can't!" << endl;
    }
    return 0;
}