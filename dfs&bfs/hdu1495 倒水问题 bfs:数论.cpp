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

const int maxn = 105;

// 1.常规bfs做法 6种操作 依次遍历

struct node {
    int a, b, c;
    int step;
}s[105];

int vis[maxn][maxn][maxn];
int a, b, c;
queue<node> q;

void bfs() {
    while(!q.empty()) q.pop();
    mem(vis, 0);
    node p1; p1.a = a, p1.b = 0, p1.c = 0, p1.step = 0;
    q.push(p1);
    vis[p1.a][0][0] = 1;
    while(!q.empty()) {
        p1 = q.front(); q.pop();
        if((p1.a==a/2&&p1.b==a/2) || (p1.a==a/2&&p1.c==a/2) || (p1.b==a/2&&p1.c==a/2)) {
            printf("%d\n", p1.step);
            return;
        }
        node p2;
        if(p1.a != 0) {
            if(p1.a > b-p1.b) {
                p2.a = p1.a - (b-p1.b);
                p2.b = b;
                p2.c = p1.c;
                p2.step = p1.step+1;
            }
            else {
                p2.a = 0;
                p2.b = p1.b + p1.a;
                p2.c = p1.c;
                p2.step = p1.step + 1;
            }
            if(!vis[p2.a][p2.b][p2.c]) {
                vis[p2.a][p2.b][p2.c] = true;
                q.push(p2);
            }
        }

        if(p1.a != 0) {
            if(p1.a > c-p1.c) {
                p2.a = p1.a-(c-p1.c);
                p2.b = p1.b;
                p2.c = c;
                p2.step = p1.step+1;
            }
            else {
                p2.a = 0;
                p2.b = p1.b;
                p2.c = p1.c+p1.a;
                p2.step = p1.step+1;
            }
            if(!vis[p2.a][p2.b][p2.c]) {
                vis[p2.a][p2.b][p2.c] = 1;
                q.push(p2);
            }
        }

        if(p1.b != 0) {
            if(p1.b > a-p1.a) {
                p2.b = p1.b-(a-p1.a);
                p2.a = a;
                p2.c = p1.c;
                p2.step = p1.step+1;
            }
            else {
                p2.b = 0;
                p2.a = p1.a+p1.b;
                p2.c = p1.c;
                p2.step = p1.step+1;
            }
            if(!vis[p2.a][p2.b][p2.c]) {
                vis[p2.a][p2.b][p2.c] = 1;
                q.push(p2);
            }
        }

        if(p1.b != 0) {
            if(p1.b > c-p1.c) {
                p2.b = p1.b - (c-p1.c);
                p2.a = a;
                p2.c = p1.c;
                p2.step = p1.step+1;
            }
            else {
                p2.b = 0;
                p2.a = p1.a;
                p2.c = p1.c + p1.b;
                p2.step = p1.step+1;
            }
            if(!vis[p2.a][p2.b][p2.c]) {
                vis[p2.a][p2.b][p2.c] = 1;
                q.push(p2);
            }
        }

        if(p1.c != 0) {
            if(p1.c > a-p1.a) {
                p2.c = p1.c-(a-p1.a);
                p2.a = a;
                p2.b = p1.b;
                p2.step = p1.step+1;
            }
            else {
                p2.c = 0;
                p2.a = p1.a+p1.c;
                p2.b = p1.b;
                p2.step = p1.step+1;
            }
            if(!vis[p2.a][p2.b][p2.c]) {
                vis[p2.a][p2.b][p2.c] = 1;
                q.push(p2);
            }
        }

        if(p1.c != 0) {
            if(p1.c > b-p1.b) {
                p2.c = p1.c-(b-p1.b);
                p2.a = p1.a;
                p2.b = b;
                p2.step = p1.step+1;
            }
            else {
                p2.c = 0;
                p2.a = p1.a;
                p2.b = p1.b+p1.c;
                p2.step = p1.step+1;
            }
            if(!vis[p2.a][p2.b][p2.c]) {
                vis[p2.a][p2.b][p2.c] = 1;
                q.push(p2);
            }
        }
    }
    printf("NO\n");
}

int main() {
    while(scanf("%d %d %d", &a, &b, &c) == 3 && (a+b+c)) {
        if(a % 2 == 1) {
            printf("NO\n");
            continue;
        }
        bfs();
    }
    return 0;
}



/* 2.神牛的数论做法
#include<cstdio>
#include<iostream>
using namespace std;
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
    int a,b,c;
    while(scanf("%d%d%d",&a,&b,&c),a+b+c)
    {
        a/=gcd(b,c);
        if(a&1)printf("NO\n");
        else printf("%d\n",a-1);
    }
    return 0;
}
*/