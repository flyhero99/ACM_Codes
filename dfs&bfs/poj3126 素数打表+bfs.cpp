#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstring>
#include<utility>

using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define inf 0x3f3f3f3f
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 10005;

struct node {
    int num;
    int step;
}a[maxn];

bool notPrime[maxn], vis[maxn];
int cas, ans;
queue<node> q;
node st, ed;
bool flag;

void init() {
    mem(notPrime, false);
    notPrime[0] = notPrime[1] = true;
    for(int i = 2;i <= 9999;i++) {
        if(notPrime[i]) continue;
        for(int j = 2*i; j <= 9999;j += i) notPrime[j] = true;
    }
}

bool bfs() {
    mem(vis, 0);
    while(!q.empty()) q.pop();
    q.push(st);
    while(!q.empty()) {
        node p = q.front(); q.pop();
        if(p.num < 1000 || p.num > 10000 || notPrime[p.num] || vis[p.num]) continue;
        vis[p.num] = true;
        if(p.num == ed.num) {
            ans = p.step;
            return true;
        }
        for(int i = 1;i <= 9;i++) {
            node tmp;
            tmp.num = (i*1000 + p.num) % 10000;
            tmp.step = p.step + 1;
            q.push(tmp);

            tmp.num = (p.num/1000)*1000 + (p.num%1000 + 100*i)%1000;
            q.push(tmp);

            tmp.num = (p.num/100)*100 + (p.num%100 + 10*i) % 100;
            q.push(tmp);

            tmp.num = (p.num/10)*10 + (p.num%10 + i) % 10;
            q.push(tmp);
        }
    }
    return false;
}

int main() {
    scanf("%d", &cas);
    while(cas--) {
        cin >> st.num >> ed.num;
        st.step = ed.step = 0;
        init();
        if(st.num == ed.num) {
            printf("0\n");
            continue;
        }
        if(bfs()) printf("%d\n", ans);
        else printf("Impossible\n");
    }
    return 0;
}