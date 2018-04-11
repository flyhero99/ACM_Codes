#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 1000005;
const int maxm = 10005;

int t[maxn], p[maxm];
int Next[maxm];

void calNext(int m) {
    Next[0] = -1;
    int i = 0, j = -1;
    while(i < m) {
        if(j == -1 || p[i] == p[j]) {
            i++, j++;
            if(p[i] != p[j]) Next[i] = j;
            else Next[i] = Next[j];
        }
        else j = Next[j];
    }
}

int kmp(int n, int m) {
    int i = 0, j = 0;
    while(i < n && j < m) {
        if(t[i] == p[j] || j == -1) i++, j++;
        else j = Next[j];
    }
    if(j == m) return i-m+1;
    else return -1;
}

int main() {
    int n, m, c;
    scanf("%d", &c);
    while(c--) {
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i++) scanf("%d", &t[i]);
        for(int i = 0; i < m; i++) scanf("%d", &p[i]);
        if(m > n) printf("-1\n");
        else {
            calNext(m);
            printf("%d\n", kmp(n, m));
        }
    }
    return 0;
}