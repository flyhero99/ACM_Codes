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

const int maxn = 600005;

ll mod[600001];

int main() {
    int n;
    while(~scanf("%d", &n) && n) {
        int i;
        for(i = 1; ; i++) {
            mod[i] = mod[i/2]*10 + i%2;
            // x=(x/10)%n*10+i%2;
            // mod[i]表示十进制里长成二进制i这样的数
            if(mod[i] % n == 0) {
                break;
            }
        }
        printf("%lld\n", mod[i]);
    }
    return 0;
}