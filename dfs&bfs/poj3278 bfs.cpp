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

const int maxn = 1e5+5;

int st, ed;
int step[maxn];
bool vis[maxn];
queue<int> q;

bool check(int n) {
    if(vis[n] || n > 100000 || n < 0) return 0;
    return 1;
}

int bfs() {
    while(!q.empty()) q.pop();
    mem(step, 0); mem(vis, 0);
    q.push(st);
    step[st] = 0, vis[st] = 1;
    while(!q.empty()) {
        int tmp = q.front(); q.pop();
        if(tmp == ed) return step[tmp];
        int p1 = tmp-1, p2 = tmp+1, p3 = 2*tmp;
        if(0 <= p1 && p1 <= 100000) {
            if(!vis[p1]) {
                q.push(p1);
                step[p1] = step[tmp] + 1;
                vis[p1] = 1;
            }
        }
        if(0 <= p2 && p2 <= 100000) {
            if(!vis[p2]) {
                q.push(p2);
                step[p2] = step[tmp] + 1;
                vis[p2] = 1;
            }
        }
        if(0 <= p3 && p3 <= 100000) {
            if(!vis[p3]) {
                q.push(p3);
                step[p3] = step[tmp] + 1;
                vis[p3] = 1;
            }
        }
    }
    return -1;
}

int main() {
    while(cin >> st >> ed) {
        if(st >= ed) cout << st-ed << endl;
        else cout << bfs() << endl;
    }
    return 0;
}